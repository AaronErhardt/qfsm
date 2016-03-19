/*
Copyright (C) 2000,2001 Stefan Duffner 

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include <qpoint.h>

#include "Machine.h"
#include "GState.h"
#include "Project.h"
#include "UndoBuffer.h"
#include "GITransition.h"
#include "Convert.h"
#include "TransitionInfoBin.h"
#include "TransitionInfoASCII.h"
#include "Const.h"
#include "ICheck.h"
#include "IOInfoList.h"
#include "Options.h"


/// Constructor.
Machine::Machine(QObject* parent/*=NULL*/, const char* n/*=0*/)
	: QObject(parent, n)
{
  name = "";
  version = "";
  project = (Project*)parent;
  num_input=0;
  num_output=0;
  num_moore_output = 0;
  initial_state=NULL;
  initial_transition=NULL;
  phantom_state = new GState(this);
  state_font.setFamily("Helvetica");
  state_font.setPointSize(8);
  state_font.setStyleHint(QFont::Helvetica);
  //state_font.setStyleStrategy(QFont::PreferBitmap);
  transition_font.setFamily("Helvetica");
  transition_font.setPointSize(8);
  transition_font.setStyleHint(QFont::Helvetica);
  //transition_font.setStyleStrategy(QFont::PreferBitmap);
  arrow_type=1;
  type = 1;  // set to ASCII machine by default
  drawITrans = TRUE;
  checker=NULL;

//  state_list.setAutoDelete(TRUE);

}

/**
 * Constructor.
 * @param parent parent object
 * @param n name of machine
 * @param t type of machine
 * @param nb number of bits for states
 * @param ni number of input bits
 * @param inames names of input bits
 * @param no number of output bits
 * @param scs state code size in bits
 * @param onames names of output bits
 * @param sf font used for drawing the state names
 * @param tf font used for drawing the transition conditions
 * @param atype arrow type (0: unfilled, 1: filled)
 */
Machine::Machine(QObject* parent, const QString n, QString v, QString a, QString d, int t, int nb, QString onamesm, int ni,  		 QString inames, int no,QString onames, QFont sf, QFont tf, int atype)
	: QObject(parent)
{
  name = n;
  version = v;
  author = a;
  description = d;
  type = t;
  num_moore_output = nb;
  num_input = ni;
  num_output = no;
  setMooreOutputNames(nb, onamesm);
  setMealyInputNames(ni, inames);
  setMealyOutputNames(no, onames);
  project = (Project*)parent;
  initial_state=NULL;
  initial_transition=NULL;
  phantom_state = new GState(this);
  state_font = sf;
  transition_font = tf;
  arrow_type=atype;
  drawITrans = TRUE;
  checker=NULL;

//  state_list.setAutoDelete(TRUE);
}


/// Destructor
Machine::~Machine()
{
  if (initial_transition)
    delete initial_transition;
  delete phantom_state;
}


/// Sets number of bits used for state coding to @a nb.
void Machine::setNumMooreOutputs(int nb)
{
  /*
  QListIterator<GState> i(state_list);
  GState* s;
  QString string;

  for(; i.current(); ++i)
  {
    s = i.current();
    
    string = Convert::intToBinStr(s->getCode(), nb);
    s->setSCode(string);
  }
  */

  num_moore_output = nb;
}

/**
 * Sets number of input bits to @a ni.
 */
void Machine::setNumInputs(int ni)
{
//  if (type==Binary)
  {
    QListIterator<GState*> i(state_list);
    GState* s;
    GTransition* t;
    TransitionInfo* info;

    for(; i.hasNext();)
    {
      s = i.next();
      
      QListIterator<GTransition*> j(s->tlist);

      for(; j.hasNext();)
      {
	t = j.next();
	info = t->getInfo();
	info->setInputsSize(/*num_input,*/ ni);
      }
    }
    num_input = ni;

  }
}


/**
 * Sets number of output bits to @a no.
 */
void Machine::setNumOutputs(int no)
{
//  if (type==Binary)
  {
    QListIterator<GState*> i(state_list);
    GState* s;
    GTransition* t;
    TransitionInfo* info;

    for(; i.hasNext();)
    {
      s = i.next();
      
      QListIterator<GTransition*> j(s->tlist);

      for(; j.hasNext();)
      {
	t = j.next();
	info = t->getInfo();
	info->setOutputsSize(/*num_output,*/ no);
      }
    }

    num_output = no;
  }
}




/**
 * Adds a new state to the machine.
 * @param sname state name
 * @param code state code
 * @param mooreout moore outputs
 * @param xpos x position 
 * @param ypos y position
 * @param radius radius of circle
 * @param scale current scale
 * @param pen pen used to draw the state
 */
bool Machine::addState(const QString sname, QString sdescription, int code, 
    		           IOInfo* mooreout, double xpos, double ypos, int radius, 
		               double scale, QPen pen, bool endstate, bool withundo/*=TRUE*/,
			       QString entry_actions/*=""*/, QString exit_actions/*=""*/)
{
  GState* s = new GState(this, sname, sdescription, code, mooreout, xpos, ypos, radius, pen, endstate, entry_actions, exit_actions);
  state_list.append(s);
  
  if (countStates()==1)
  {
    initial_state = s;
    initial_transition = new GITransition(phantom_state, s);
  }

  if (withundo)
    project->getUndoBuffer()->addState(this, s);

  updateCanvasSize(int(xpos+radius+50), int(ypos+radius+50), scale);
  return TRUE;
}


/**
 * Adds a state to the machine.
 *
 * @param s State to add
 * @param withundo If TRUE this step can be undone
 * @returns TRUE if successful
 */
bool Machine::addState(GState* s, bool withundo/*=TRUE*/)
{
  double xpos, ypos, radius;

  if (s)
    state_list.append(s);
  else
    return FALSE;
  
  s->getPos(xpos, ypos);
  radius = s->getRadius();

  if (countStates()==1)
  {
    initial_state = s;
    initial_transition = new GITransition(phantom_state, s);
  }

  if (withundo)
    project->getUndoBuffer()->addState(this, s);

  updateCanvasSize(int(xpos+radius+50), int(ypos+radius+50), 1.0);
  return TRUE;
}

/**
 * Removes state @a s from the machine.
 */
void Machine::removeState(GState* s)
{
  if (!s)
    return;

  QListIterator<GTransition*> ti(s->tlist);
  QListIterator<GTransition*> tir(s->reflist);
  int i;

  GTransition* t;

  if (!s)
    return;

//  s->tlist.setAutoDelete(FALSE);

  while (ti.hasNext())
  {
    t = ti.next();

//    s->tlist.removeRef(t);
     s->tlist.removeAll(t);
    t->setStart(phantom_state);
    phantom_state->tlist.append(t);
  }

  while (tir.hasNext())
  {
    t = tir.next();
    
//    s->reflist.removeRef(t);
    s->reflist.removeAll(t);
    t->setEnd(NULL);
  }

//  s->tlist.setAutoDelete(TRUE);
  s->select(FALSE);
  s->setDeleted();

  if (s==initial_state)
  {
    initial_state=NULL;
    delete initial_transition;
    initial_transition=NULL;
  }
}


/// Returns the number of states in the machine.
int Machine::countStates()
{
  QListIterator<GState*> i(state_list);

  int count=0;
  for(;i.hasNext();)
  {
    if (!i.next()->isDeleted())
      count++;
  }
  return count;
}


/**
 * Returns the state which lies on (near to) the point @p at the scale @a scale.
 */
GState* Machine::getState(QPoint p, double scale)
{
  GState* s=NULL;
  double x, y;
  int radius;
  double btop, bbottom, bleft, bright;

  QListIterator<GState*> i(state_list);

  for(; i.hasNext();)
  {
    s = i.next();
    if (!s->isDeleted())
    {
      s->getPos(x,y);
      radius = s->getRadius();
      bleft = int((x-radius)*scale);
      btop = int((y-radius)*scale);
      bright = int((x+radius)*scale);
      bbottom = int((y+radius)*scale);

      if (p.x()>bleft && p.x()<bright && p.y()>btop && p.y()<bbottom)
	return s;
    }
  }
  return NULL;
}


/// Returns a list of end states of this machine
QList<GState*> Machine::getFinalStates()
{
  QList<GState*> ltmp;
//  ltmp.setAutoDelete(FALSE);

  QListIterator<GState*> it(state_list);
  for(; it.hasNext();)
  {
    if (it.peekNext()->isFinalState())
      ltmp.append(it.next());
	else it.next();
  }
  return ltmp;
}


/**
 * Returns the graphical object which lies on a point.
 * The type of the object will be stored in @a type.
 * @param p point the resulting object will lie on (near to)
 * @param scale current scale
 * @param type type of the object
 */
GObject* Machine::getObject(QPoint p, double scale, int& type)
{
  GState* s=NULL;
  GTransition* t=NULL;
  double x, y;
  int radius;
  double btop, bbottom, bleft, bright;

  QListIterator<GState*> i(state_list);

  for(; i.hasNext();)
  {
    s = i.next();
    if (!s->isDeleted())
    {
      s->getPos(x,y);
      radius = s->getRadius();
      bleft = int((x-radius)*scale);
      btop = int((y-radius)*scale);
      bright = int((x+radius)*scale);
      bbottom = int((y+radius)*scale);
      
      if (p.x()>bleft && p.x()<bright && p.y()>btop && p.y()<bbottom)
      {
	type = StateT;
	return s;
      }

      QListIterator<GTransition*> it(s->tlist);
      
      for(; it.hasNext();)
      {
	t = it.next();
	if (!t->isDeleted() && t->contains(p.x()/scale, p.y()/scale))
	{
	  type = TransitionT;
	  return t;
	}
      }
    }
  }
 
  QListIterator<GTransition*> ip(phantom_state->tlist);
    
  for(; ip.hasNext();)
  {
    t = ip.next();
    if (!t->isDeleted() && t->contains(p.x()/scale, p.y()/scale))
    {
      type = TransitionT;
      return t;
    }
  }

  if (initial_transition && initial_transition->contains(p.x()/scale, p.y()/scale))
  {
    type = ITransitionT;
    return initial_transition;
  }

  type=NoT;
  return NULL;
}


/// Returns the state with the code @a code.
GState* Machine::getState(int code)
{
  QListIterator<GState*> i(state_list);
  GState* s;

  for(; i.hasNext();)
  {
    s = i.next();
    if (!s->isDeleted() && s->getEncoding()==code)
      return s;
  }
  return NULL;
}

/// 
/// Returns the state with the name @name
GState* Machine::getState(QString name)
{
  QListIterator<GState*> i(state_list);
  GState* s;

  for(; i.hasNext();)
  {
    s = i.next();
    if (!s->isDeleted() && s->getStateName()==name)
      return s;
  }
  return NULL;
}



/// Attaches (graphically) the initial transition to the initial state.
void Machine::attachInitialTransition()
{
  if (!initial_transition || !initial_state)
    return;

  double xs, ys, xe, ye;
  double xst, yst;
  int rad;
  double dist;
  double resx, resy;

  initial_transition->getPos(xs, ys);
  initial_transition->getEndPos(xe, ye);

  initial_state->getPos(xst, yst);
  rad = initial_state->getRadius();

  dist = sqrt((xe-xst)*(xe-xst)+(ye-yst)*(ye-yst));
  if (dist>rad+5)
  {
    double diffx, diffy;
    GState::circleEdge(xst, yst, rad, xe, ye, resx, resy);
    diffx = resx-xe;
    diffy = resy-ye;
    initial_transition->setEndPos(resx, resy);
    initial_transition->setPos(xs+diffx, ys+diffy);
  }
}


/// Sets the canvas (scroll view) size to @a x, @a y.
void Machine::setCanvasSize(int x, int y)
{
  if (x<CANVAS_MINX)
    x=CANVAS_MINX;
  if (y<CANVAS_MINY)
    y=CANVAS_MINY;
  canvas_size.setWidth(x);
  canvas_size.setHeight(y);

  emit newCanvasSize(x, y);
}


/**
 * Updates the canvas size with a new point.
 * If the point with the coordinates @a x and @a y at the scale @a scale lies 
 * outside the current scroll view, the size will be adjusted accordingly
 */
void Machine::updateCanvasSize(int x, int y, double scale)
{
  if (x>canvas_size.width())
  {
    canvas_size.setWidth(x);
    emit newCanvasSize(int(canvas_size.width()*scale), int(canvas_size.height()*scale));
  }
  if (y>canvas_size.height())
  {
    canvas_size.setHeight(y);
    emit newCanvasSize(int(canvas_size.width()*scale), int(canvas_size.height()*scale));
  }
  //qDebug("Machine:updateCanvasSize(%d,%d,%f)",x,y,scale);
}

/**
 * Updates the canvas size.
 * The coordinates are already transformed into scale factor 1.0
 */
void Machine::updateCanvasSize(int x, int y)
{
  bool change = false;
  int x_=canvas_size.width(), y_=canvas_size.height();
  if (x>canvas_size.width())
  {
    canvas_size.setWidth(x);
    change=true;
  }
  if (y>canvas_size.height())
  {
    canvas_size.setHeight(y);
    change=true;
  }

  if (change)
    emit newCanvasSize(x_, y_);
  //qDebug("Machine:updateCanvasSize(%d,%d)",x,y);
} 

/**
 * Calculates the canvas size according to the states and transitions in the
 * machine.
 */
void Machine::calcCanvasSize()
{
  QListIterator<GState*> i(state_list);
  GState* s;
  GTransition* t;
  double x, y, ex, ey, c1x, c1y, c2x, c2y;
  int radius;

  setCanvasSize(0,0);

  for(; i.hasNext();)
  {
    s = i.next();
    s->getPos(x, y);
    radius = s->getRadius();

    x += radius + CANVAS_MARGIN;
    y += radius + CANVAS_MARGIN;

    updateCanvasSize(int(x), int(y));

    QListIterator<GTransition*> j(s->tlist);

    for(; j.hasNext();)
    {
      t = j.next();
  /*    t->getPos(x, y);
      t->getEndPos(ex, ey);
      t->getCPoint1(c1x, c1y);
      t->getCPoint2(c2x, c2y);
      x += CANVAS_MARGIN; y += CANVAS_MARGIN;
      ex += CANVAS_MARGIN; ey += CANVAS_MARGIN;
      c1x += CANVAS_MARGIN; c1y += CANVAS_MARGIN;
      c2x += CANVAS_MARGIN; c2y += CANVAS_MARGIN;

      updateCanvasSize(int(x), int(y));
      updateCanvasSize(int(ex), int(ey));
  */
      updateCanvasSize(int(c1x), int(c1y));
      updateCanvasSize(int(c2x), int(c2y));
	  
	  double bx1, by1, bx2, by2;
	  double d=-0.0;
	
	  t->bezierCurve(d, bx2, by2);
	  do
	  {
		  bx1 = bx2; 
		  by1 = by2;

		  updateCanvasSize((int)bx1,(int)by1);

		  d += 0.05;
		  t->bezierCurve(d, bx2, by2);

	  } while (d<=0.9);
    }
  }

  // phantom state

  s = phantom_state;
  s->getPos(x, y);
  radius = s->getRadius();

  x += radius + CANVAS_MARGIN;
  y += radius + CANVAS_MARGIN;

  updateCanvasSize(int(x), int(y));

  QListIterator<GTransition*> k(s->tlist);

  for(; k.hasNext();)
  {
    t = k.next();
    t->getPos(x, y);
    t->getEndPos(ex, ey);
    t->getCPoint1(c1x, c1y);
    t->getCPoint2(c2x, c2y);
    x += CANVAS_MARGIN; y += CANVAS_MARGIN;
    ex += CANVAS_MARGIN; ey += CANVAS_MARGIN;
    c1x += CANVAS_MARGIN; c1y += CANVAS_MARGIN;
    c2x += CANVAS_MARGIN; c2y += CANVAS_MARGIN;

    updateCanvasSize(int(x), int(y));
    updateCanvasSize(int(ex), int(ey));
    updateCanvasSize(int(c1x), int(c1y));
    updateCanvasSize(int(c2x), int(c2y));
  }
  updateCanvasSize(canvas_size.width()+50, canvas_size.height()+50, 1.0);
}


/// Returns the number of states in the machine
int Machine::getNumStates()
{
  QListIterator<GState*> i(state_list);
  GState* s;
  int count=0;

  for(; i.hasNext();)
  {
    s = i.next();

    if (!s->isDeleted())
      count++;
  }
  return count;
}



/**
 * Completes the moore output names string.
 * Output names that are not given are named "s_out" + the bit number
 *
 * @param num Number of moore outputs (state coding bits)
 * @param string Input string
 */
void Machine::setMooreOutputNames(int num, QString string)
{
  int length, count=0;
  QString s, tmp;

  length = string.length();

  output_names_moore.clear();
  output_names_moore=translateNames(string);
/*  s = "";
  for(int i=0; i<length; i++)
  {
    if (count>=num)
      return;

    if (string[i]==',')
    {
      s = s.stripWhiteSpace();
      if (s.isEmpty())
        s = "s_out"+tmp.setNum(num-count-1);
      replaceChar(s, ' ', '_');
      output_names_moore.append(s);
      count++;
      s="";
    }
    else
      s += string[i];
  }
  if (s!="")
  {
    s = s.stripWhiteSpace();
    replaceChar(s, ' ', '_');
    output_names_moore.append(s);
  }
*/  if (output_names_moore.count()<(unsigned int)num)
  {
    for(int i=output_names_moore.count(); i<num; i++)
    {
      tmp.setNum(num-i-1);
      output_names_moore.append("s_out"+tmp);
    }
  }
  else if(output_names_moore.count()>(unsigned int)num && num!=-1)
  {
    while(output_names_moore.count()>(unsigned int)num)
      output_names_moore.removeLast();
  }
}


/// Returns the moore output names separated by @a separator
QString Machine::getMooreOutputNames(QString separator/*=", "*/)
{
/*  QStringList::Iterator it;
  QString s;

  for(it = output_names_moore.begin(); it!=output_names_moore.end(); ++it)
  {
    if (it!=output_names_moore.begin())
      s += separator;

    s += *it;
  }
  return s;*/
  return retranslateNames(output_names_moore);
}

/// Returns the synchronized moore output names separated by @a separator
QString Machine::getMooreOutputNamesAsync(QString separator/*=", "*/)
{
/*  QStringList::Iterator it;
  QString s;

  for(it = output_names_moore.begin(); it!=output_names_moore.end(); ++it)
  {
    QString tmp = *it;

    tmp += "_async";

    if (it!=output_names_moore.begin())
      s += separator;

    s += tmp;
  }
  return s;*/
  QString tmp=retranslateNames(output_names_moore);
  tmp.replace(",",separator+"_async");
  tmp="_async"+tmp;
  return tmp;
}

/// Returns a list of Input/Output names created from the QString @a names
QStringList Machine::translateNames(QString names)
{
  QStringList ret;
  if(names.length()<=0)
    return ret;
  QStringList parts=names.split(",",QString::SkipEmptyParts);
  QStringList::const_iterator i;
  int pos1,pos2,pos3,indexstart,indexend;
  bool ok;
  
  for(i=parts.constBegin(); i!=parts.constEnd(); ++i)
  {
    ok=false;
    pos1=i->find('[');
    pos2=i->find("..",pos1);
    pos3=i->find(']',pos2);

    if(pos1 !=-1 && pos2 !=-1 && pos3!=-1)
    {
      indexstart=(i->mid(pos1+1,pos2-pos1-1)).toInt(&ok);
      if(ok==true)
      {
        indexend=(i->mid(pos2+2,pos3-pos2-2)).toInt(&ok);
        if(indexstart<indexend)
          ok=false;
        if(ok==true)
        {
          for(int c=indexstart; c>=indexend; c--)
            ret.append((i->left(pos1)).stripWhiteSpace()+"["+QString::number(c)+"]");
        }
      }
    }
    if(!ok)
        ret.append(i->stripWhiteSpace());
  }
  
  return ret;
}

/// Returns a list of Input/Output names created from the QString @a names
QString Machine::retranslateNames(QStringList names)
{
  QString ret="";

  QStringList::const_iterator i;
  int pos1,pos2,indexstart,indexend;
  QString arrayName="",oldArrayName;
  bool ok,indexStarted=false;
  
  for(i=names.constBegin(); i!=names.constEnd(); ++i)
  {
    ok=false;
    pos1=i->find('[');
    pos2=i->find(']',pos1);
    oldArrayName=arrayName;
    arrayName=i->left(pos1);

    if(pos1!=-1 && pos2!=-1)
    {
      if(indexStarted && arrayName!=oldArrayName)
      {
        ret+=(arrayName+"["+QString::number(indexstart)+".."+QString::number(indexend)+"]");
        if(i+1!=names.constEnd())
          ret+=",";
        indexStarted=false;
      }
      if(!indexStarted)
      {
        indexstart=i->mid(pos1+1,pos2-pos1-1).toInt(&ok);
        indexend=-1;
        if(ok==true)
          indexStarted=true;
      }
      else 
      {
        int indextmp=i->mid(pos1+1,pos2-pos1-1).toInt(&ok);
        if(ok==true)
          indexend=indextmp;
      }
    }

    if((i+1==names.constEnd() || ok==false) && indexStarted==true)
    {
      if(indexend==-1)
        ret+=arrayName;
      else ret+=oldArrayName+"["+QString::number(indexstart)+".."+QString::number(indexend)+"]";

      if(!(i+1==names.constEnd() && ok==true))
      {
        indexStarted=false;
        ret+=",";
      }


    }
    
    if(!indexStarted )
    {
      ret+=(*i);
      if(i+1!=names.constEnd())
        ret+=",";
    }
  }
  return ret;
}

QString Machine::getStateEncodingOutputNames(QString separator/*=", "*/)
{
  //int count=0;
  QString s;
  bool first=TRUE;


  for(int i=0; i<getNumEncodingBits(); i++)
  {
    QString tmp;

    tmp.setNum(i);
    if (!first)
      s += separator;

    s += "s"+tmp;
    first = FALSE;
  }
  return s;
}


int Machine::getNumEncodingBits()
{
  QListIterator<GState*> i(state_list);
  GState* s;
  int emax=-1;
  int scode, bits=0, c;

  for(; i.hasNext();)
  {
    s = i.next();
     if (!s->isDeleted())
    {
      scode = s->getEncoding();

      if (scode>emax)
  emax = scode;
    }
   }
  if (emax<0)
    emax=1;



//   bits = int(log((float)emax)/log(2.0)) +1;
//   qDebug("float "+QString::number(log((float)emax)/log(2.0)+1.,'g',15));
//   qDebug("integer "+QString::number(bits));

   for(c=0; c<8*sizeof(int); c++)
   {
     if(emax>>c==0)
     {
       bits=c;
       break;
     }
   }
//      qDebug("integer2 "+QString::number(bits));


  if (bits<1)
     bits=1;

  return bits;
}

/**
 * Completes the mealy input names.
 *
 * @param num Number of mealy inputs of the machine
 * @param string Input string
 */
void Machine::setMealyInputNames(int num, QString string)
{
  int length, count=0;
  QString s, tmp;

  length = string.length();

  input_names.clear();
  input_names=translateNames(string);
//  s = "";
/*  for(int i=0; i<length; i++)
  {
    if (count>=num)
      return;

    if (string[i]==',')
    {
      s = s.stripWhiteSpace();
      if (s.isEmpty())
        s = "i_"+tmp.setNum(num-count-1);
      replaceChar(s, ' ', '_');
      input_names.append(s);
      count++;
      s="";
    }
    else
      s += string[i];
  }
  if (s!="")
  {
    s = s.stripWhiteSpace();
    replaceChar(s, ' ', '_');
    input_names.append(s);
  }
  
*/  if (input_names.count()<(unsigned int)num)
  {
    for(int i=input_names.count(); i<num; i++)
    {
      tmp.setNum(num-i-1);
      input_names.append("i_"+tmp);
    }
  }
  else if(input_names.count()>(unsigned int)num && num!=-1)
  {
    while(input_names.count()>(unsigned int)num)
      input_names.removeLast();
  }
}


/// Returns the mealy input names separated by @a separator
QString Machine::getMealyInputNames(QString separator/*=", "*/)
{
/*  QStringList::Iterator it;
  QString s;

  for(it = input_names.begin(); it!=input_names.end(); ++it)
  {
    if (it!=input_names.begin())
      s += separator;

    s += *it;
  }
  return s;*/
  return retranslateNames(input_names);
}

/**
 * Completes the mealy output names.
 *
 * @param num Number of mealy outputs of the machine
 * @param string Input string
 */
void Machine::setMealyOutputNames(int num, QString string)
{
  int length, count=0;
  QString s, tmp;

  length = string.length();

  output_names.clear();
  output_names=translateNames(string);
  s = "";
/*  for(int i=0; i<length; i++)
  {
    if (count>=num)
      return;

    if (string[i]==',')
    {
      s = s.stripWhiteSpace();
      if (s.isEmpty())
        s = "o_"+tmp.setNum(num-count-1);
      replaceChar(s, ' ', '_');
      output_names.append(s);
      count++;
      s="";
    }
    else
      s += string[i];
  }
  if (s!="")
  {
    s = s.stripWhiteSpace();
    replaceChar(s, ' ', '_');
    output_names.append(s);
  }
*/
      if (output_names.count()<(unsigned int)num)
  {
    for(int i=output_names.count(); i<num; i++)
    {
      tmp.setNum(num-i-1);
      output_names.append("o_"+tmp);
    }
  }
  else if(output_names.count()>(unsigned int)num && num!=-1)
  {
    while(output_names.count()>(unsigned int)num)
      output_names.removeLast();
  }
}


/// Returns the mealy output names separated by @a separator
QString Machine::getMealyOutputNames(QString separator/*=", "*/)
{
/*  QStringList::Iterator it;
  QString s;

  for(it = output_names.begin(); it!=output_names.end(); ++it)
  {
    if (it!=output_names.begin())
      s += separator;

    s += *it;
  }
  return s;*/
  return retranslateNames(output_names);
}

/// Replaces in string @a s all occurences of @a c1 with @a c2
void Machine::replaceChar(QString& s, QChar c1, QChar c2)
{
  int len;

  len = s.length();

  for(int i=0; i<len; i++)
  {
    if (s[i]==c1)
      s[i]=c2;
  }
}


/// Returns a new state code (as integer value)
int Machine::getNewCode()
{
  GState* s;
  int code=0;

  do
  {
    s = getState(code);
    code++;
  } while (s!=NULL);
  code--;

  return code;
}

/// Search for state codes that were not unique and replace them
void Machine::correctCodes()
{
  int newCode,bits;
  GState *s1,*s2,*sc;
  QListIterator <GState*> i1(state_list);
  
  while(i1.hasNext())
  {
    s1=i1.next();
    QListIterator <GState*> i2(state_list);
    i2.findNext(s1);
    //qDebug(s1->getStateName()+" "+QString::number(s1->getEncoding()));
    while(i2.hasNext())
    {
      s2=i2.next();
      if(s2->getEncoding() == s1->getEncoding())
      {

        s2->setEncoding(getNewCode());

      }
    }
  }
}

///returns true when every state code of the machine is unique
bool Machine::checkStateCodes()
{
  int newCode,bits;
  GState *s1,*s2;
  QListIterator <GState*> i1(state_list);
  
  while(i1.hasNext())
  {
    s1=i1.next();
	if(s1->isDeleted())
		continue;
    QListIterator <GState*> i2(state_list);
    i2.findNext(s1);
    while(i2.hasNext())
    {
      s2=i2.next();
	  if(s2->isDeleted())
		  continue;
      if(s2->getEncoding() == s1->getEncoding())
        return FALSE;
    }
  }
  
  return TRUE;
}


/// Checks the integrity of the machine and displays the results in a dialog
void Machine::checkIntegrity(ICheck* c)
{
  checker=c;
  checker->connectMachine(this);
  checker->checkMachine(this);
  checker->showDlg();
}

void Machine::checkFinished(int)
{
  resetMarks();
  if(checker!=NULL)
    checker->disconnectMachine(this);
  emit repaint();
}


/// Returns a list of all events covered by a transition of the machine
void Machine::getEventList(IOInfoList& list, Options* opt)
{
  QListIterator<GState*> i(state_list);
  GState* s;
  GTransition* t;
  IOInfo *info;
  IOInfoList iolist;
//  iolist.setAutoDelete(TRUE);

  list.clear();

  for(; i.hasNext();)
  {
    s = i.next();

    if (!s->isDeleted())
    {
      QListIterator<GTransition*> ti(s->tlist);

      for(; ti.hasNext();)
      {
        t = ti.next();

        if (!t->isDeleted())
        {
          info = t->getInfo()->getInputInfo();
          if (type==Text)  // "free text" machine
          {
            if (!list.contains(info))
            {
              list.append(info->clone());
            }
          }
          else  // no "free text" machine
          {
            
            if (!iolist.contains(info))
            {
              iolist.append(info->clone());
            }
          }
        } // end if t !deleted
      }
    } // end if s !deleted
  }
  if (type!=Text)
    IOInfo::expandList(iolist, list, opt->getStateTableResolveInverted());
}

/**
 * Sets the marks of all states of the Machine to false
 *
 */
void Machine::resetMarks()
{
  QMutableListIterator<GState*> is(getSList());
  GState* s;
  GTransition*t;

  while(is.hasNext())
  {
    s = is.next();
    s->setMark(FALSE);
    QMutableListIterator<GTransition*> it(s->tlist);

    while(it.hasNext())
    {
      t=it.next();
      t->setMarkMax();
      t->setMark(0);

    }
  }
}



void Machine::updateDefaultTransitions()
{
  QListIterator<GState*> i(state_list);
  GState* s;

  for(; i.hasNext();)
  {
    s = i.next();
    if (!s->isDeleted())
      s->updateDefaultTransition();
  }
}

void Machine::addDefaultTransitionsToEveryState()
{
  if (type!=0 && type!=1)
    return;

  QListIterator<GState*> i(state_list);
  GState* s;
  TransitionInfo* ti;

  for(; i.hasNext();)
  {
    s = i.next();
    if (!s->isDeleted())
    {
      if (type==0)
	ti = new TransitionInfoBin();
      else
	ti = new TransitionInfoASCII();
      ti->getInputInfo()->setDefault(true);
      s->addTransition(project, s, ti, 0, 0, 0, 0, 0, 0, 0, 0, "", true, true);
    }
  }
}





