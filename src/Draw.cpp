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

#include <math.h>
#include <float.h>
#include <qnamespace.h>
#include <q3ptrlist.h>
#include <qpainter.h>
#include <qnamespace.h>
#include <qdatetime.h>
//Added by qt3to4:
#include <Q3PointArray>
//#include <qvaluelist.h>
 
#include "Draw.h"
#include "GState.h"
#include "Machine.h"
#include "ScrollView.h"
#include "Const.h"
#include "Options.h"
//#include "Convert.h"
#include "TransitionInfo.h"
#include "GITransition.h"
#include "Grid.h"


/**
 * Constructor.
 * Initialises the Draw object.
 * @param parent parent widget
 * @param opt application options
 */
Draw::Draw(QObject* parent, Options* opt)
    : QObject(parent)
{
  options = opt;
  grid_calculated = false;
}


/**
 * Draws all states.
 * @param m machine containing the states
 * @param p QPainter specifying what to draw on
 * @param contx current x scroll position
 * @param conty current y scroll position
 * @param scale current scale factor
 */
void Draw::drawStates(Machine* m, QPainter* p, int contx, int conty, 
                 double scale)
{
  if (!m)
    return;
  
  p->setBrush(Qt::NoBrush);
  p->setRenderHint(QPainter::Antialiasing);

  QList<GState*> l = m->getSList();
  QString statestr, scode, smoore;
  QPen selpen(QColor(255,0,0), 1);
  QPen blackpen(QColor(0,0,0), 1);
  QBrush oldBrush, shadowBrush;
  GState* s;

  double xpos, ypos;
  
  QMutableListIterator<GState*> i(l);
  i.toBack();


  for(; i.hasPrevious();)
  {
    s = i.previous();
    if (!s->isDeleted())
    {
      QRect window;
      s->getPos(xpos, ypos);
      QPen pen = s->getPen();
      QFont font = m->getSFont();
      QBrush b = s->getBrush();
      int lw = s->getLineWidth();
      int r = s->getRadius();
      QString name = s->getStateName();
      scode = s->getCodeStr();
      smoore = s->getMooreOutputsStr(m, options);

      p->setFont(font);

      window = p->window();
      p->setViewport(-contx, -conty, int(window.width()*scale), 
      int(window.height()*scale));

      oldBrush = p->brush();

      if (options->getStateShadows())
      {
        p->setPen(Qt::NoPen);
        shadowBrush = QBrush(options->getStateShadowColor());
        p->setBrush(shadowBrush);
        p->drawEllipse(int(xpos-r+5), int(ypos-r+5), 2*r, 2*r);
      }

      p->setBrush(b);
      pen.setWidth(lw);
      if(s->getMark())
        p->setPen(selpen);
      else p->setPen(pen);
      p->drawEllipse(int(xpos-r), int(ypos-r), 2*r, 2*r);
      if (s->isFinalState())
        p->drawEllipse(int(xpos-r+4), int(ypos-r+4), 2*r-8, 2*r-8);

      p->setBrush(oldBrush);

      DRect re;
      re = s->getMaxRect();

      QRect trect1, trect2;

      if (m->getType()!=Text 
        && (options->getViewMoore() || options->getViewStateEncoding()))
      {
        trect1.setCoords((int)re.left(), (int)re.top(), (int)re.right(), 
        (int)(re.top()+(re.bottom()-re.top())/2-2));
        trect2.setCoords((int)re.left(), (int)(re.top()+(re.bottom()-re.top())/2+2), 
        (int)re.right(), (int)re.bottom());
      }
      else
      {
        trect1.setCoords((int)re.left(), (int)re.top(), (int)re.right(), (int)re.bottom());
      }

      p->setPen(blackpen);

      if (m->getType()==Text)
      {
	QString ena=s->getEntryActions(), exa=s->getExitActions();
	if (!ena.isEmpty())
	  name += "\nEntry: "+ena;
	if (!exa.isEmpty())
	  name += "\nExit:  "+exa;
      }
      p->drawText(trect1, Qt::AlignCenter | Qt::TextWordWrap | Qt::TextWrapAnywhere, name);

      if (m->getType()!=Text
         && (options->getViewMoore() || options->getViewStateEncoding()))
      {
        int dist=5;
        if (s->isFinalState())
          dist=7;
//	p->moveTo(int(xpos-r+dist), int(ypos));
//	p->lineTo(int(xpos+r-dist), int(ypos));
      p->drawLine(int(xpos-r+dist), int(ypos),int(xpos+r-dist), int(ypos));

	  if (options->getViewMoore() && options->getViewStateEncoding())
	    statestr = "/";
	  else
	    statestr = "";
      }
      if (options->getViewMoore())
      {
        statestr = smoore + statestr;
      }
      if (options->getViewStateEncoding())
      {
        statestr = statestr + scode;
      }
      if (m->getType()!=Text 
          && (options->getViewMoore() || options->getViewStateEncoding()))
          p->drawText(trect2, Qt::AlignCenter|Qt::TextWordWrap|Qt::TextWrapAnywhere, statestr);

      if (s->isSelected() && p->device()->devType()!=QInternal::Printer)
      {
	double bscale=scale;
	if (bscale>1.0)
	  bscale=1.0;
	p->setPen(selpen);
	p->drawRect((int)(int(xpos-r)-3/bscale), (int)(int(ypos-r)-3/bscale), 
	    int(2*r+6/bscale), int(2*r+6/bscale));
      }
    }
  }

}



/**
 * Draws a single state.
 * @param m machine which contains state
 * @param s state to draw
 * @param p QPainter
 * @param contx current x scroll position
 * @param conty current y scroll position
 * @param scale current scale factor
 * @param drawxor if TRUE draws in xor mode otherwise draws with the respective
 * color.
 */
/*
void Draw::drawState(Machine* m, GState* s, QPainter* p, int contx, int conty, 
               double scale, bool drawxor)
{

	
  QString scode, smoore, statestr;
  QPen selpen(QColor(255,0,0), 1);
  QPen blackpen(QColor(0,0,0), 1);

  double xpos, ypos;
  
  if (!s || s->isDeleted())
    return;

  QRect window;
  s->getPos(xpos, ypos);
  QPen pen = s->getPen();
  QFont font = m->getSFont();
  QBrush b = s->getBrush();
  int lw = s->getLineWidth();
  int r = s->getRadius();
  QString name = s->getStateName();
  scode = s->getCodeStr();
  smoore = s->getMooreOutputsStr();

  pen.setWidth(lw);
  if(s->getMark())
    p->setPen(selpen);
  else p->setPen(pen);
  p->setBrush(b);
  p->setFont(font);

  window = p->window();
  p->setViewport(-contx, -conty, int(window.width()*scale), 
    int(window.height()*scale));


    if (drawxor)
//    p->setRasterOp(Qt::NotXorROP);
    p->setCompositionMode(QPainter::CompositionMode_Xor);
  else
//    p->setRasterOp(Qt::CopyROP);
    p->setCompositionMode(QPainter::CompositionMode_SourceOver);


  p->drawEllipse(int(xpos-r), int(ypos-r), 2*r, 2*r);
  if (s->isEndState())
    p->drawEllipse(int(xpos-r+4), int(ypos-r+4), 2*r-8, 2*r-8);

  DRect re;
  re = s->getMaxRect();

  QRect trect1, trect2;

  if (m->getType()!=Text 
      && (options->getViewMoore() || options->getViewStateEncoding()))
  {
    trect1.setCoords((int)re.left(), (int)re.top(), (int)re.right(), 
      (int)(re.top()+(re.bottom()-re.top())/2-2));
    trect2.setCoords((int)re.left(), (int)(re.top()+(re.bottom()-re.top())/2+2), 
      (int)re.right(), (int)re.bottom());
  }
  else
  {
    trect1.setCoords((int)re.left(), (int)re.top(), (int)re.right(), (int)re.bottom());
  }

  p->setPen(blackpen);
  p->drawText(trect1, Qt::AlignCenter | Qt::TextWordWrap, name);


  if (drawxor)
//    p->setRasterOp(Qt::NotXorROP);
    p->setCompositionMode(QPainter::CompositionMode_Xor);


  if (m->getType()!=Text 
      && (options->getViewMoore() || options->getViewStateEncoding()))
  {
    int dist=5;
    if (s->isEndState())
      dist=7;
//    p->moveTo(int(xpos-r+dist), int(ypos));
//    p->lineTo(int(xpos+r-dist), int(ypos));
    p->drawLine(int(xpos-r+dist), int(ypos),int(xpos+r-dist), int(ypos));

    statestr = "/";
  }
  if (options->getViewMoore())
  {
    statestr = smoore + statestr;
  }
  if (options->getViewStateEncoding())
  {
    statestr = statestr + scode;
  }
  if (m->getType()!=Text 
      && (options->getViewMoore() || options->getViewStateEncoding()))
    p->drawText(trect2, Qt::AlignCenter, statestr);

  if (s->isSelected())
  {
    double bscale=scale;
    if (bscale>1.0)
      bscale=1.0;
    p->setPen(selpen);
    p->drawRect((int)(int(xpos-r)-3/bscale), (int)(int(ypos-r)-3/bscale), 
	(int)(2*r+6/bscale), (int)(2*r+6/bscale));
  }

}
*/



/**
 * Draws all transitions in machine.
 * @param m machine containing the transitions
 * @param p QPainter
 * @param contx current x scroll position
 * @param conty current y scroll position
 * @param scale current scale factor
 * @param numin number of input bits
 * @param numout number of output bits
 */
void Draw::drawTransitions(Machine* m, QPainter* p, int contx, int conty, 
                 double scale/*, int numin, int numout*/)
{
  if (!m)
    return;

  QRect window;

  State *ph;
  ph = (State*)m->getPhantomState();

  p->setBrush(Qt::NoBrush);
  p->setRenderHint(QPainter::Antialiasing);



  double xpos, ypos;
  double ex, ey;
  double c1x, c1y, c2x, c2y;
  GState* s;
  GTransition* t;
  QBrush br_control(QColor(255,0,0));
  QBrush br_end(QColor(0,255,0));
  Q3PointArray parray(4);
  int rectsize;
//  double g1x, g1y, g2x, g2y;
  
//  QListIterator<GState> is(m->getSList());
  QMutableListIterator<GState*> is(m->getSList());

  QPen pen(QColor(0,0,0), 1);
  QPen redpen(QColor(255,0,0));
  QPen cline_pen(QColor(255,0,0), 1, Qt::DotLine);

  window = p->window();
  p->setViewport(-contx, -conty, int(window.width()*scale), 
    int(window.height()*scale));

//  for(; is.current(); ++is)
  for(; is.hasNext();)
  {
//    s = is.current();
    s = is.next();
//    QListIterator<GTransition> itrans(s->tlist);
    QMutableListIterator<GTransition*> itrans(s->tlist);

//    for (; itrans.current(); ++itrans)
    for (; itrans.hasNext();)
    {
//      t = itrans.current();
      t = itrans.next();

      if (!t->isDeleted() && !t->isDragged())
      {
	t->getPos(xpos, ypos);
	t->getCPoint1(c1x, c1y);
	t->getCPoint2(c2x, c2y);
	t->getEndPos(ex, ey);
    
    if(t->getStart()==ph|| t->getEnd()==ph || t->getStart()==NULL|| t->getEnd()==NULL )
      p->setPen(redpen);
    else 
      p->setPen(pen);
 


//	p->setPen(pen);
	parray.setPoint(0, (int)xpos, (int)ypos);
	parray.setPoint(1, (int)c1x, (int)c1y);
	parray.setPoint(2, (int)c2x, (int)c2y);
	parray.setPoint(3, (int)ex, (int)ey);

	p->drawCubicBezier(parray, 0);

	// Arrow
	drawArrow(t, p, pen, m->getArrowType());

	// Condition

	drawCondition(m, t, p, contx, conty, scale/*, numin, numout*/);

	if (t->isSelected() && p->device()->devType()!=QInternal::Printer)
	{
	  rectsize = int(CPOINT_SIZE/scale+0.5);
	  if (rectsize==0)
	    rectsize=1;

	  p->setBrush(br_end);

	  p->drawRect((int)(xpos-rectsize), (int)(ypos-rectsize), rectsize*2, rectsize*2);
	  p->drawRect((int)(ex-rectsize), (int)(ey-rectsize), rectsize*2, rectsize*2);
	  p->setBrush(br_control);
	  p->drawRect((int)(c1x-rectsize), (int)(c1y-rectsize), rectsize*2, rectsize*2);
	  p->drawRect((int)(c2x-rectsize), (int)(c2y-rectsize), rectsize*2, rectsize*2);

	  p->setPen(cline_pen);
//	  p->moveTo((int)xpos, (int)ypos);
//	  p->lineTo((int)c1x, (int)c1y);
//	  p->moveTo((int)ex, (int)ey);
//	  p->lineTo((int)c2x, (int)c2y);
      p->drawLine((int)xpos, (int)ypos,(int)c1x, (int)c1y);
      p->drawLine((int)ex, (int)ey,(int)c2x, (int)c2y);
        }
      }
    }
  }

    // phantom states

//  QListIterator<GTransition> iphantom(m->getPhantomState()->tlist);
  QMutableListIterator<GTransition*> iphantom(m->getPhantomState()->tlist);

//  for (; iphantom.current(); ++iphantom)
  for (; iphantom.hasNext();)
  {
//    t = iphantom.current();
    t = iphantom.next();


    if (!t->isDeleted())
    {
	t->getPos(xpos, ypos);
	t->getCPoint1(c1x, c1y);
	t->getCPoint2(c2x, c2y);
	t->getEndPos(ex, ey);

	p->setPen(redpen);
	parray.setPoint(0, (int)xpos, (int)ypos);
	parray.setPoint(1, (int)c1x, (int)c1y);
	parray.setPoint(2, (int)c2x, (int)c2y);
	parray.setPoint(3, (int)ex, (int)ey);

	p->drawCubicBezier(parray, 0);

	// Arrow
	drawArrow(t, p, pen, m->getArrowType());
	
	// Condition

	drawCondition(m, t, p, contx, conty, scale/*, numin, numout*/);

	if (t->isSelected() && !t->isDragged())
	{
	  rectsize = int(CPOINT_SIZE/scale+0.5);
	  if (rectsize==0)
	    rectsize=1;

	  p->setBrush(br_end);
	  p->drawRect((int)(xpos-rectsize), (int)(ypos-rectsize), rectsize*2, rectsize*2);
	  p->drawRect((int)(ex-rectsize), (int)(ey-rectsize), rectsize*2, rectsize*2);
	  p->setBrush(br_control);
	  p->drawRect((int)(c1x-rectsize), (int)(c1y-rectsize), rectsize*2, rectsize*2);
	  p->drawRect((int)(c2x-rectsize), (int)(c2y-rectsize), rectsize*2, rectsize*2);

	  p->setPen(cline_pen);
//	  p->moveTo((int)xpos, (int)ypos);
//	  p->lineTo((int)c1x, (int)c1y);
//	  p->moveTo((int)ex, (int)ey);
//	  p->lineTo((int)c2x, (int)c2y);
      p->drawLine((int)xpos, (int)ypos,(int)c1x, (int)c1y);
      p->drawLine((int)ex, (int)ey,(int)c2x, (int)c2y);
	}
      }
    }
}


/**
 * Draws a single transition.
 * @param m machine containing the transition
 * @param t transition to draw
 * @param p QPainter
 * @param contx current x scroll position
 * @param conty current y scroll position
 * @param scale current scale factor
 * @param numin number of input bits
 * @param numout number of output bits
 * @param drawxor if TRUE draws in xor otherwise not
 * @param dotted if TRUE draws a dotted otherwise a solid line
 * @param control_lines if TRUE draws with the control lines otherwise it draws
 * only the transition line
 * @param first if TRUE it draws the first line of a sequence (e.g. when
 * dragging) i.e. it erases the visible transition.
 */

void Draw::drawTransition(Machine* m, GTransition* t, QPainter* p, int contx, 
		 int conty, double scale,
		 bool drawxor, bool dotted,
		 bool control_lines, bool first)
{
  if (!t || t->isDeleted())
    return;
  p->setBrush(Qt::NoBrush);
  p->setRenderHint(QPainter::Antialiasing,false);

  QRect window;

  double startposx, startposy, endposx, endposy;
  
  State *ph;

  
  QPen pen(QColor(0,0,0), 1);
  QPen redpen(QColor(255,0,0), 1);
  QPen dotpen(QColor(0,0,0), 1, Qt::DotLine);
  QPen cline_pen(QColor(255,0,0), 1, Qt::DotLine);
  QBrush br_control(QColor(255,0,0));
  QBrush br_end(QColor(0,255,0));
  
  ph = (State*)m->getPhantomState();
  if(t->getStart()==ph || t->getEnd()==ph)
    pen.setColor(QColor(255,0,0));


  double c1x, c1y, c2x, c2y;
  int rectsize;

  t->getPos(startposx, startposy);
  t->getCPoint1(c1x, c1y);
  t->getCPoint2(c2x, c2y);
  t->getEndPos(endposx, endposy);

/*
  if (first)
  {
//    p->setRasterOp(Qt::SetROP);
    p->setCompositionMode(QPainter::CompositionMode_SourceOver);
  } 
  else if (drawxor)
 //   p->setRasterOp(Qt::NotXorROP);
    p->setCompositionMode(QPainter::CompositionMode_Xor);

  else
//    p->setRasterOp(Qt::CopyROP);
    p->setCompositionMode(QPainter::CompositionMode_SourceOver);
*/
  
  window = p->window();
  p->setViewport(-contx, -conty, int(window.width()*scale),
  int(window.height()*scale));

  Q3PointArray parray(4);
  parray.setPoint(0, (int)startposx, (int)startposy);
  parray.setPoint(1, (int)c1x, (int)c1y);
  parray.setPoint(2, (int)c2x, (int)c2y);
  parray.setPoint(3, (int)endposx, (int)endposy);

  if (dotted)
    p->setPen(dotpen);
  else
  {
    if(t->getStart()==ph|| t->getEnd()==ph || t->getStart()==NULL|| t->getEnd()==NULL )
       p->setPen(redpen);
    p->setPen(pen);
  }

  // Transition
  p->drawCubicBezier(parray, 0);

  // Arrow
  drawArrow(t, p, pen, m->getArrowType());

  // Condition

  if (!dotted)
    drawCondition(m, t, p, contx, conty, scale);

  if (t->isSelected())
  {
    rectsize = int(CPOINT_SIZE/scale+0.5);
    if (rectsize==0)
      rectsize=1;

    p->setPen(pen);
    p->setBrush(br_end);
    p->drawRect((int)(startposx-rectsize),(int)(startposy-rectsize), rectsize*2, rectsize*2);
    p->drawRect((int)(endposx-rectsize), (int)(endposy-rectsize), rectsize*2, rectsize*2);

    p->setBrush(br_control);
    p->drawRect((int)(c1x-rectsize), (int)(c1y-rectsize), rectsize*2, rectsize*2);
    p->drawRect((int)(c2x-rectsize), (int)(c2y-rectsize), rectsize*2, rectsize*2);

    if (!t->isStraight() || control_lines)
    {
      p->setPen(cline_pen);
//      p->moveTo((int)startposx, (int)startposy);
//      p->lineTo((int)c1x, (int)c1y);
//      p->moveTo((int)endposx, (int)endposy);
//      p->lineTo((int)c2x, (int)c2y);
      p->drawLine((int)startposx, (int)startposy,(int)c1x, (int)c1y);
      p->drawLine((int)endposx, (int)endposy,(int)c2x, (int)c2y);
    }
  }
}



/**
 * Draws a condition for a given transition.
 * @param m machine containing the transition with the condition
 * @param t transition owning the condition
 * @param p QPainter
 * @param contx current x scroll position
 * @param conty current y scroll position
 * @param scale current scale factor
 * @param numin number of input bits
 * @param numout number of output bits
 */
void Draw::drawCondition(Machine* m, GTransition* t, QPainter* p, int contx, 
			 int conty, double scale/*,int numin, int numout*/)
			 
{
  if (!t || t->isDeleted())
    return;

  QRect window;
  double mx, my, condx, condy;
  QString sin, sep, sout;
  QString cond;
  int numout;
  TransitionInfo* info;
  QRect bound;
  QBrush br(QColor(255,255,255));
  QPen pen(QColor(0,0,0), 1);
//  QPen Qt::white(Qt::white, 1);
  //int count, in_len, out_len;
  //QStringList::iterator it;
  //bool first;

  numout = m->getNumOutputs();

  window = p->window();
  p->setViewport(-contx, -conty, int(window.width()*scale), 
  int(window.height()*scale));

  QFont font; //("Helvetica");
  font = m->getTFont();
  info = t->getInfo();

  p->setRenderHint(QPainter::Antialiasing);
  p->setFont(font);
  p->setBrush(br);
  p->setPen(pen);

  if (info)
  {
    if (t->isStraight() && (t->getStart()!=t->getEnd()))
    {
      double txpos, typos, tendx, tendy;
      t->getPos(txpos, typos);
      t->getEndPos(tendx, tendy);
      mx = txpos + 0.5*(tendx-txpos);
      my = typos + 0.5*(tendy-typos);
    }
    else
      t->bezierCurve(0.5, mx, my);

    if (options->getViewMealyIn())
      sin = info->getCompleteInputsStr(m, options);
    if (options->getViewMealyOut())
      sout = info->getOutputsStr(m, options);


    sep = info->getSeparator(options);


      if (options->getViewMealyIn() && options->getViewMealyOut() && sin.length()>0 && sout.length()>0)
	cond = sin + sep + sout;
      else
      {
	if (!options->getViewMealyIn() || sin.length()<=0)
	  cond = sep + sout;
	if (!options->getViewMealyOut() || sout.length()<=0)
	  cond = sin;
      }
      cond.replace("|"," | ");

    //qDebug(sin+" "+sout + "   cond: "+cond);
    /*
    else
      cond = sin + sep + sout;
      */

    //bound = p->fontMetrics().boundingRect(cond);
    bound = p->fontMetrics().boundingRect((int)mx, (int)my, 1000, 100, //cond);
	  Qt::TextDontClip|Qt::AlignCenter, cond);
    
//    qDebug("%d %d", bound.width(), bound.height());
    condx = mx - (double)bound.width()/2;
    //condy = my + (double)bound.height()/2;
    condy = my - (double)bound.height()/2;

    if ((options->getViewMealyIn() || options->getViewMealyOut())
	&& (!cond.isEmpty() && !(sin.isEmpty() && sout.isEmpty())))  // don't draw empty condition
    {
      if (options->getDrawBox())
	p->setPen(Qt::DotLine); 
      else
	p->setPen(Qt::white);
      //p->drawRect((int)(condx-5), (int)(condy-bound.height()-5), 
//	bound.width()+10, bound.height()+10);
      p->drawRect((int)(condx-5), (int)(condy-5), 
	bound.width()+10, bound.height()+10);
      p->setPen(pen);
      //p->drawText((int)condx, (int)condy, cond);
      p->drawText((int)condx, (int)condy, bound.width(), bound.height(),
	  Qt::TextDontClip|Qt::AlignCenter, cond);
      /*
      if (options->getDisplayIONames() && !sin.isEmpty() && !sout.isEmpty())
      {
	p->setPen(Qt::DotLine);
	p->drawLine((int)condx, (int)condy+bound.height()/2,
	    (int)condx+bound.width(), (int)condy+bound.height()/2);
      }
      */
    }
  }
}



/**
 * Draws the initial transition with the text 'start'.
 * @param m machine containing the transition
 * @param t intial transition
 * @param p QPainter
 * @param contx current x scroll position
 * @param conty current y scroll position
 * @param scale current scale factor
 * @param textrect bounding rectangle of the resulting text ("Reset")
 * @param drawxor if TRUE draws in xor mode otherwise not
 * @param first if TRUE draws the first transition in a sequence (e.g. when
 * dragging)
 * @param transptext draws text transparently
 */
void Draw::drawInitialTransition(Machine* m, GITransition* t, QPainter* p, 
		int contx, int conty, double scale, QRect& textrect, 
		bool drawxor/*=TRUE*/, bool first/*=FALSE*/, bool transptext/*=FALSE*/)
{
  if (!t)
    return;

  if (t->isDragged())
    return;

  QRect window;

  double startposx, startposy, endposx, endposy;
  double mg, dx, dy;
  
  QPen pen(QColor(0,0,0), 1);
  QPen cline_pen(QColor(255,0,0), 1, Qt::DotLine);
  QBrush br_control(QColor(255,0,0));
  QBrush br_end(QColor(0,255,0));

  textrect = QRect();  // null rectangle

  int rectsize;

  t->getPos(startposx, startposy);
  t->getEndPos(endposx, endposy);

  window = p->window();
  p->setViewport(-contx, -conty, int(window.width()*scale), 
  int(window.height()*scale));

  /*
  if (first)
  {
//    p->setRasterOp(Qt::SetROP);
    p->setCompositionMode(QPainter::CompositionMode_SourceOver);
  } 
  else if (drawxor)
//    p->setRasterOp(Qt::NotXorROP);
    p->setCompositionMode(QPainter::CompositionMode_Xor);
*/
  
  p->setRenderHint(QPainter::Antialiasing);
  p->setPen(pen);

  // Transition
  p->drawLine((int)startposx, (int)startposy, (int)endposx, (int)endposy);

  // Arrow
  drawArrow(t, p, pen, m->getArrowType());

  // Text 
  if (!drawxor)
  {
    double textposx=0, textposy=0;

    QFont font = m->getTFont(); //("Helvetica", 14);
    p->setFont(font);
    Qt::BGMode bg = p->backgroundMode();
    if (!transptext)
      p->setBackgroundMode(Qt::OpaqueMode);
    dx = endposx - startposx;
    dy = endposy - startposy;
    if (dx)
      mg=dy/dx;
    else
      mg = 1000000;

    double extx, exty;
    QRect boundrect;
    extx = START_DISTANCE/sqrt(1+mg*mg);
    exty = START_DISTANCE/sqrt(1+1/(mg*mg));

    boundrect = p->boundingRect((int)textposx, (int)textposy, 1000, 100,
	Qt::AlignLeft| Qt::AlignVCenter, 
	options->getInitialDescriptor());

    if (dx>0)
      textposx = startposx-boundrect.width() - extx;
    else
      textposx = startposx/*-boundrect.width()*/ + extx;
    if (dy>0)
      textposy = startposy-boundrect.height()/2 - exty;
    else
      textposy = startposy-boundrect.height()/2 + exty;

    p->drawText((int)textposx, (int)textposy, boundrect.width(),
	boundrect.height(), 
	Qt::AlignLeft | Qt::AlignVCenter, options->getInitialDescriptor());
    //p->drawText((int)textposx, (int)textposy, options->getStartDescriptor());
    p->setBackgroundMode(bg);
    textrect.setRect((int)textposx, (int)textposy, boundrect.width(), boundrect.height());
  }


  // control points
  if (t->isSelected() && p->device()->devType()!=QInternal::Printer)
  {
    rectsize = int(CPOINT_SIZE/scale+0.5);
    if (rectsize==0)
      rectsize=1;

    p->setPen(pen);
    p->setBrush(br_end);
    p->drawRect((int)(startposx-rectsize), (int)(startposy-rectsize), rectsize*2, rectsize*2);
    p->drawRect((int)(endposx-rectsize), (int)(endposy-rectsize), rectsize*2, rectsize*2);
  } 
}


/**
 * Draws the grid.
 * @param grid grid object of the view
 * @param p QPainter
 * @param contx current x scroll position
 * @param conty current y scroll position
 * @param scale current scale factor
 */
void Draw::drawGrid(Grid* gr, QPainter* p, int contx, int conty, double scale)
{
  QRect window;
  QPen pen(options->getGridColor(), 1);
  double gu;
  double cx, cy;
  double guscale;
  double halfcross_size = 0.1; // percentage of cross size w.r.t grid spacing

  p->setRenderHint(QPainter::Antialiasing,false);

  window = p->window();
  //p->setViewport(-contx, -conty, int(window.width()*scale), int(window.height()*scale));

  p->setPen(pen);
  gu = options->getGridSize();
  gr->getPoint(contx/scale, conty/scale, cx, cy); // get the top-left grid point

  int numpointsx = float((contx+window.width())/scale-cx)/gu;
  int numpointsy = float((conty+window.height())/scale-cy)/gu;
  int numpoints = numpointsx*numpointsy;

  while (gu*scale<6)
    gu *= 2;

  /*
  for (double i=cx; i<(contx+window.width())/scale; i+=gu)
  {
    for(double j=cy; j<(conty+window.height())/scale; j+=gu)
    {
      //p->drawLine((int)(i-1), (int)j,(int)(i+1), (int)j);
      //p->drawLine((int)i, (int)(j-1),(int)i, (int)(j+1));
      p->drawPoint((int)i, (int)j);
    }
  }
  */
  for (int i=0; i<numpointsx; i++)
    for (int j=0; j<numpointsy; j++)
    {
      guscale=gu*scale;
      p->drawLine(int(cx+(i-halfcross_size)*guscale), int(cy+j*guscale), int(cx+(i+halfcross_size)*guscale), int(cy+j*guscale));
      p->drawLine(int(cx+i*guscale), int(cy+(j-halfcross_size)*guscale), int(cx+i*guscale), int(cy+(j+halfcross_size)*guscale));
      //p->drawPoint(int(cx+i*gu*scale), int(cy+j*gu*scale));
    }
}



/**
 * Calculates the 2 coordinates for the arrow of a transition
 * @param t transition
 * @param xl x coordinate for left line
 * @param yl y coordinate for left line
 * @param xr x coordinate for right line
 * @param yr y coordinate for right line
 * @param xm x coordinate for middle line (for pointed arrows)
 * @param ym y coordinate for middle line (for pointed arrows)
 */
void Draw::calcArrow(GTransition* t, double& xl, double& yl, double& xr,
                     double& yr, double& xm, double& ym)
{
  double g1x, g1y, g2x, g2y;

  t->bezierCurve(0.9, g1x, g1y);
  t->bezierCurve(1.0, g2x, g2y);

  calcArrow(g1x, g1y, g2x, g2y, xl, yl, xr, yr, xm, ym);
}


/**
 * Calculates the 2 coordinates for the arrow of the initial transition
 * @param t transition
 * @param xl x coordinate for left line
 * @param yl y coordinate for left line
 * @param xr x coordinate for right line
 * @param yr y coordinate for right line
 * @param xm x coordinate for middle line (for pointed arrows)
 * @param ym y coordinate for middle line (for pointed arrows)
 */
void Draw::calcArrow(GITransition* t, double& xl, double& yl, double& xr,
                     double& yr, double& xm, double& ym)
{
  double g1x, g1y, g2x, g2y;

  t->getPos(g1x, g1y);
  t->getEndPos(g2x, g2y);

  calcArrow(g1x, g1y, g2x, g2y, xl, yl, xr, yr, xm, ym);
}


/**
 * Calculates arrowhead coordinates.
 * Calculates from 2 coordinates of the end of the transition the 2
 * coordinates to draw an arrow.
 * @param p1x x coordinate of the first point on the transition
 * @param p1y y coordinate of the first point on the transition
 * @param p2x x coordinate of the second point on the transition
 * @param p2y y coordinate of the second point on the transition
 * @param xl x coordinate of the left part of the arrow
 * @param yl y coordinate of the left part of the arrow
 * @param xl x coordinate of the right part of the arrow
 * @param yl y coordinate of the right part of the arrow
 * @param xm x coordinate of the middle part of the arrow (for pointed arrows)
 * @param ym y coordinate of the middle part of the arrow (for pointed arrows)
 */
void Draw::calcArrow(double p1x, double p1y, double p2x, double p2y, 
		     double& xl, double& yl, double& xr, double& yr,
		     double& xm, double& ym)
{
  double mg;
  double phi, phil, phir;
  double arrow_x1, arrow_x2, arrow_y1, arrow_y2, arrow_xm, arrow_ym;
  double ex, ey;

  if (p2x-p1x!=0)
    mg = (p1y-p2y)/(p2x-p1x);
  else 
    mg = (p2y<p1y ? 1 : -1)*100000;

  phi = atan(mg);
  if (p2x<p1x)
    phi = phi + PI;
  phil = phi-(ARROW_ANGLE/180*PI);
  phir = phi+(ARROW_ANGLE/180*PI);

  arrow_x1 = ARROW_LENGTH * cos(phil);
  arrow_y1 = ARROW_LENGTH * sin(phil);
  arrow_x2 = ARROW_LENGTH * cos(phir);
  arrow_y2 = ARROW_LENGTH * sin(phir);
  arrow_xm = 0.66*ARROW_LENGTH * cos(phi);
  arrow_ym = 0.66*ARROW_LENGTH * sin(phi);

//  t->getEndPos(ex, ey);
  ex = p2x;
  ey = p2y;
  xl = ex-arrow_x1;
  yl = ey+arrow_y1;
  xr = ex-arrow_x2;
  yr = ey+arrow_y2;
  xm = ex-arrow_xm;
  ym = ey+arrow_ym;
}


/**
 * Draws the arrowhead for a transition.
 * @param t transition
 * @param p QPainter
 * @param pen pen of that transition
 * @param type type of transition: 0 means not filled, 1 means filled
 */
void Draw::drawArrow(GTransition* t, QPainter* p, QPen pen, int type)
{
  double endposx, endposy;
  double arrow_x1, arrow_y1, arrow_x2, arrow_y2, arrow_xm, arrow_ym;

  if (!t)
    return;


  t->getEndPos(endposx, endposy);

  calcArrow(t, arrow_x1, arrow_y1, arrow_x2, arrow_y2, arrow_xm, arrow_ym);

  Q3PointArray pa(3);
  Q3PointArray pa4(4);
  QBrush br(QColor(0,0,0));
  QBrush brwhite(QColor(255,255,255));

  if (type==0 || type==1 || type==2)
    pa.setPoints(3, (int)arrow_x1, (int)arrow_y1, (int)endposx, (int)endposy,
      (int)arrow_x2, (int)arrow_y2);
  else
    pa4.setPoints(4, (int)arrow_x1, (int)arrow_y1, (int)endposx, (int)endposy,
      (int)arrow_x2, (int)arrow_y2, (int)arrow_xm, (int)arrow_ym);
  

//  p->setRenderHint(QPainter::Antialiasing);
  p->setPen(pen);
  p->setBrush(br);

  switch(type)
  {
    case 0:   // line
//      p->moveTo((int)arrow_x1, (int)arrow_y1);
//      p->lineTo((int)endposx, (int)endposy);
//      p->lineTo((int)arrow_x2, (int)arrow_y2);
      p->drawLine((int)arrow_x1, (int)arrow_y1,(int)endposx, (int)endposy);
      p->drawLine((int)endposx, (int)endposy,(int)arrow_x2, (int)arrow_y2);
      break;
    case 1:   // filled
      p->drawPolygon(pa);
      break;
    case 2:   // white
      p->setBrush(brwhite);
      p->drawPolygon(pa);
      break;
    case 3:   // filled pointed
      p->drawPolygon(pa4);
      break;
    case 4:   // white pointed
      p->setBrush(brwhite);
      p->drawPolygon(pa4);
      break;
  }


}

/**
 * Draws the arrowhead for the initial transition.
 * @param t transition
 * @param p QPainter
 * @param pen pen of the transition
 * @param type type of transition: 0 means not filled, 1 means filled
 */
void Draw::drawArrow(GITransition* t, QPainter* p, QPen pen, int type)
{
  double endposx, endposy;
  double arrow_x1, arrow_y1, arrow_x2, arrow_y2, arrow_xm, arrow_ym;

  if (!t)
    return;

  t->getEndPos(endposx, endposy);

  calcArrow(t, arrow_x1, arrow_y1, arrow_x2, arrow_y2, arrow_xm, arrow_ym);

  Q3PointArray pa(3);
  Q3PointArray pa4(4);
  QBrush br(QColor(0,0,0));
  QBrush brwhite(QColor(255,255,255));

  if (type==0 || type==1 || type==2)
    pa.setPoints(3, (int)arrow_x1, (int)arrow_y1, (int)endposx, (int)endposy, 
      (int)arrow_x2, (int)arrow_y2);
  else
    pa4.setPoints(4, (int)arrow_x1, (int)arrow_y1, (int)endposx, (int)endposy,
      (int)arrow_x2, (int)arrow_y2, (int)arrow_xm, (int)arrow_ym);


  p->setRenderHint(QPainter::Antialiasing);
  p->setPen(pen);
  p->setBrush(br);

  switch(type)
  {
    case 0:   // line
//      p->moveTo((int)arrow_x1, (int)arrow_y1);
//      p->lineTo((int)endposx, (int)endposy);
//      p->lineTo((int)arrow_x2, (int)arrow_y2);
      p->drawLine((int)arrow_x1, (int)arrow_y1,(int)endposx, (int)endposy);
      p->drawLine((int)endposx, (int)endposy,(int)arrow_x2, (int)arrow_y2);
      break;
    case 1:   // black
      p->drawPolygon(pa);
      break;
    case 2:   // white
      p->setBrush(brwhite);
      p->drawPolygon(pa);
      break;
    case 3:   // filled pointed
      p->drawPolygon(pa4);
      break;
    case 4:   // white pointed
      p->setBrush(brwhite);
      p->drawPolygon(pa4);
      break;
  }
}

/**
 * Draws the Headline for a Machine.
 * @param m machine containing the transition with the condition
 * @param p QPainter
 */
void Draw::drawHeadline(Machine* m, QPainter* p) //, double scale)
{
    QRect window;
    window = p->window();
//    QDate date = QDate::currentDate();
//    QString date2 = QString().sprintf("%d.%d.%d", date.day(), date.month(), date.year());
//    QTime time = QTime::currentTime();
    QDateTime datetime = QDateTime::currentDateTime();
    QString datetimestr;
    datetimestr = datetime.toString(Qt::LocalDate);

    QString name, version;
    name = m->getName();
    version = m->getVersion();

    QFont font; //("Helvetica");
    font = m->getTFont();
    //scale font size?
    p->setFont(font);
    p->setRenderHint(QPainter::Antialiasing);

    QRect dtrect = window;

    //moved text
    p->drawText(dtrect.width()/40, dtrect.width()/40, name + " \tVersion "+ version);
//    p->drawText(window.width()/scale - 140, 0, date2 + "  " + time.toString());
//    p->drawText(window.width()/scale - 140, 0, datetimestr);
    dtrect.setRight(dtrect.right()-dtrect.width()/40);
    dtrect.setTop(dtrect.top()+dtrect.width()/40);
    p->drawText(dtrect, Qt::AlignRight | Qt::AlignTop | Qt::TextSingleLine, datetimestr);
}



QRect Draw::getBoundingBox(Machine* m, QPainter* p)
{
  QRect result;
  double minx = DBL_MAX;
  double maxx = 0;
  double miny = DBL_MAX;
  double maxy = 0;
  bool shadows = options->getStateShadows();
  int addshadowx=0, addshadowy=0; 
  if (shadows)
    addshadowx=addshadowy=5;

  QList<GState*> l = m->getSList();
  GState* s;

  double xpos, ypos;
  int radius;
  double sx, sy, ex, ey;
  QRect brect_tmp;
  
  if (m->getDrawITrans())
  {
    // initial transition;
    GITransition* gi = m->getInitialTransition();
    gi->getPos(sx, sy);
    gi->getEndPos(ex, ey);
    minx = MIN(minx,sx);
    maxx = MAX(maxx,sx);
    miny = MIN(miny,sy);
    maxy = MAX(maxy,sy);
    // end initial transition


    // start descriptor
    if (!options->getInitialDescriptor().isEmpty())
    {
      double textposx=0, textposy=0;
      double dx, dy, mg;

      QFont font = m->getTFont(); //("Helvetica", 14);
      p->setFont(font);
      dx = ex - sx;
      dy = ey - sy;
      if (dx)
	mg=dy/dx;
      else
	mg = 1000000;

      double extx, exty;
      QRect boundrect;
      extx = START_DISTANCE/sqrt(1+mg*mg);
      exty = START_DISTANCE/sqrt(1+1/(mg*mg));

      boundrect = p->boundingRect((int)ROUND(textposx), (int)ROUND(textposy), 3000, 100,
	  Qt::AlignLeft| Qt::AlignVCenter, 
	  options->getInitialDescriptor());

      if (dx>0)
	textposx = sx-boundrect.width() - extx;
      else
	textposx = sx + extx;
      if (dy>0)
	textposy = sy-boundrect.height()/2 - exty;
      else
	textposy = sy-boundrect.height()/2 + exty;
      brect_tmp.setRect((int)ROUND(textposx-0.05*boundrect.width()), (int)ROUND(textposy-0.05*boundrect.height()), int(boundrect.width()+0.1*boundrect.width()), int(boundrect.height()+0.1*boundrect.height()));

      result.setCoords(ROUND(minx), ROUND(miny), ROUND(maxx), ROUND(maxy));
      result = result.unite(brect_tmp);
      minx = result.left();
      miny = result.top();
      maxx = result.right();
      maxy = result.bottom();
    }
    // end start descriptor
  }

	
//  QListIterator<GState> i(l);
  QMutableListIterator<GState*> i(l);


//  for(; i.current(); ++i)
  for(; i.hasNext();)
  {
//    s = i.current();
    s = i.next();

    if (s->isDeleted())
      continue;

    s->getPos(xpos, ypos);
    radius = s->getRadius();

    minx = MIN(minx,xpos-radius);
    maxx = MAX(maxx,xpos+radius+addshadowx);
    miny = MIN(miny,ypos-radius);
    maxy = MAX(maxy,ypos+radius+addshadowy);

//    QListIterator<GTransition> j(s->tlist);
    QMutableListIterator<GTransition*> j(s->tlist);

    
//    for(; j.current(); ++j)
    for(; j.hasNext();)
    {
//      GTransition* trans = j.current();
      GTransition* trans = j.next();
      
      if (trans->isDeleted())
	continue;

      trans->getPos(sx, sy);
      trans->getEndPos(ex, ey);

      if (trans->isStraight() && trans->getStart()!=trans->getEnd())
      {
	minx = MIN(minx,sx);
	maxx = MAX(maxx,sx);
	miny = MIN(miny,sy);
	maxy = MAX(maxy,sy);
	minx = MIN(minx,ex);
	maxx = MAX(maxx,ex);
	miny = MIN(miny,ey);
	maxy = MAX(maxy,ey);
      }
      else
      {
	double bx1, by1, bx2, by2;
	double dx, dy, m;
	double t=-0.0;
	
	trans->bezierCurve(t, bx2, by2);

	do
	{
	  bx1 = bx2; 
	  by1 = by2;

	  minx = MIN(minx,bx1);
	  maxx = MAX(maxx,bx1);
	  miny = MIN(miny,by1);
	  maxy = MAX(maxy,by1);

	  t += 0.05;
	  trans->bezierCurve(t, bx2, by2);

	} while (t<=0.9);
      }

      QRect bound;
      QString cond;
      QString sinp, sep, sout;
      double mx, my, condx, condy;
      QBrush br(QColor(255,255,255));
      QPen pen(QColor(0,0,0), 1);
      TransitionInfo* info;
      QFont font; //("Helvetica");
      font = m->getTFont();
      info = trans->getInfo();

      p->setFont(font);
      p->setBrush(br);
      p->setPen(pen);

      if (info)
      {
	if (trans->isStraight() && (trans->getStart()!=trans->getEnd()))
	{
	  mx = sx + 0.5*(ex-sx);
	  my = sy + 0.5*(ey-sy);
	}
	else
	  trans->bezierCurve(0.5, mx, my);

	if (options->getViewMealyIn())
	{
	  sinp = info->getInputsStr(m, options);
	  if (info->getInputInfo()->isInverted())
	    sinp = options->getInversionDescriptor() + " " + sinp;
	  else if (info->getInputInfo()->getAnyInput())
	    sinp = options->getAnyInputDescriptor();
	  else if (info->getInputInfo()->isDefault())
	    sinp = options->getDefaultTransitionDescriptor();
	}
	if (options->getViewMealyOut())
	  sout = info->getOutputsStr(m, options);

	sep = info->getSeparator(options);

	{
	  if (sinp.isEmpty())
	    cond = sout;
	  if (sout.isEmpty())
	    cond = sinp;
	  else if (!sinp.isEmpty())
	    cond = sinp + sep + sout;
	}

	bound = p->fontMetrics().boundingRect((int)ROUND(mx), (int)ROUND(my), 1000, 100, //cond);
	      Qt::TextDontClip|Qt::AlignCenter, cond);
	condx = mx - (double)bound.width()/2;
	condy = my - (double)bound.height()/2;
	brect_tmp.setRect((int)ROUND(condx-5), (int)ROUND(condy-5), bound.width()+10, bound.height()+10);
	
	result.setCoords(ROUND(minx), ROUND(miny), ROUND(maxx), ROUND(maxy));
	result = result.unite(brect_tmp);
	minx = result.left();
	miny = result.top();
	maxx = result.right();
	maxy = result.bottom();
      }

    }
  }

  // phantom state
  s = m->getPhantomState();
  s->getPos(xpos, ypos);

//  QListIterator<GTransition> j(s->tlist);
  QMutableListIterator<GTransition*> j(s->tlist);
  
//  for(; j.current(); ++j)
  for(; j.hasNext();)
  {
//    GTransition* trans = j.current();
    GTransition* trans = j.next();
    if (trans->isDeleted())
      continue;

    trans->getPos(sx, sy);
    trans->getEndPos(ex, ey);

    if (trans->isStraight() && trans->getStart()!=trans->getEnd())
    {
      minx = MIN(minx,sx);
      maxx = MAX(maxx,sx);
      miny = MIN(miny,sy);
      maxy = MAX(maxy,sy);
      minx = MIN(minx,ex);
      maxx = MAX(maxx,ex);
      miny = MIN(miny,ey);
      maxy = MAX(maxy,ey);
    }
    else
    {
      double bx1, by1, bx2, by2;
      double dx, dy, m;
      double t=-0.0;
      
      trans->bezierCurve(t, bx2, by2);

      do
      {
	bx1 = bx2; 
	by1 = by2;

	minx = MIN(minx,bx1);
	maxx = MAX(maxx,bx1);
	miny = MIN(miny,by1);
	maxy = MAX(maxy,by1);

	t += 0.1;
	trans->bezierCurve(t, bx2, by2);

      } while (t<=0.9);
    }

    QRect bound;
    QString cond;
    QString sinp, sep, sout;
    double mx, my, condx, condy;
    QBrush br(QColor(255,255,255));
    QPen pen(QColor(0,0,0), 1);
    TransitionInfo* info;
    QFont font; //("Helvetica");
    font = m->getTFont();
    info = trans->getInfo();

    p->setFont(font);
    p->setBrush(br);
    p->setPen(pen);

    if (info)
    {
      if (trans->isStraight() && (trans->getStart()!=trans->getEnd()))
      {
	mx = sx + 0.5*(ex-sx);
	my = sy + 0.5*(ey-sy);
      }
      else
	trans->bezierCurve(0.5, mx, my);

      if (options->getViewMealyIn())
      {
	sinp = info->getInputsStr(m, options);
	if (info->getInputInfo()->isInverted())
	  sinp = options->getInversionDescriptor() + " " + sinp;
	else if (info->getInputInfo()->getAnyInput())
	  sinp = options->getAnyInputDescriptor();
	else if (info->getInputInfo()->isDefault())
	  sinp = options->getDefaultTransitionDescriptor();
      }
      if (options->getViewMealyOut())
	sout = info->getOutputsStr(m, options);

      sep = info->getSeparator(options);

      {
	if (sinp.isEmpty())
	  cond = sout;
	if (sout.isEmpty())
	  cond = sinp;
	else if (!sinp.isEmpty())
	  cond = sinp + sep + sout;
      }

      bound = p->fontMetrics().boundingRect((int)ROUND(mx), (int)ROUND(my), 1000, 100, //cond);
	    Qt::TextDontClip|Qt::AlignCenter, cond);
      condx = mx - (double)bound.width()/2;
      condy = my - (double)bound.height()/2;
      brect_tmp.setRect((int)ROUND(condx-5), (int)ROUND(condy-5), bound.width()+10, bound.height()+10);
      
      result.setCoords(ROUND(minx), ROUND(miny), ROUND(maxx), ROUND(maxy));
      result = result.unite(brect_tmp);
      minx = result.left();
      miny = result.top();
      maxx = result.right();
      maxy = result.bottom();
    }

  }
  // end phantom state


  result.setCoords(ROUND(minx+5), ROUND(miny+5), ROUND(maxx-5), ROUND(maxy-5));
  return result;
}

