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

#include <qpen.h>
#include <qbrush.h>
#include <qcolor.h>
#include <q3ptrlist.h>
#include <qregexp.h>

#include "GState.h"
#include "GObject.h"
#include "ScrollView.h"
#include "Const.h"
#include "Machine.h"
#include "Convert.h"
#include "Project.h"
#include "UndoBuffer.h"
#include "TransitionInfoBin.h"
#include "IOInfoList.h"
#include "DrawArea.h"

/**
 * Constructor.
 * @param n name of the state
 * @param c code of the state
 * @param x x coordinate
 * @param y y coordinate
 * @param r radius
 * @param p pen to draw the state with
 */
GState::GState(Machine* m, const QString n, QString d, int c, IOInfo* moore, double x, 
    	       double y, int r, QPen p, bool end, QString ena, QString exa)
      : QObject(), State(m, n, d, c, moore, end, ena, exa), GObject(x, y)
{
  machine = m;
  pen = p;
  brush.setColor(QColor(255,255,255));
  brush.setStyle(Qt::SolidPattern);
//  scode = Convert::intToBinStr(c, numbits);
  radius = r;
  mark=false;

//  tlist.setAutoDelete(TRUE);
//  reflist.setAutoDelete(FALSE);
}

/**
 * Constructor.
 * Initialises a standard GState
 */
GState::GState(Machine* m) : QObject(), State(m), GObject(0,0)
{
  machine = m;
  pen.setColor(QColor(0,0,0));
  pen.setWidth(1);
  brush.setColor(QColor(255,255,255));
  brush.setStyle(Qt::SolidPattern);
//  scode = ""; 
  radius = 40;
  mark=false;

//  tlist.setAutoDelete(TRUE);
//  reflist.setAutoDelete(FALSE);
}

/// Constructor
GState::GState() : QObject(), State(), GObject(0,0)
{
  pen.setColor(QColor(0,0,0));
  pen.setWidth(1);
  brush.setColor(QColor(255,255,255));
  brush.setStyle(Qt::SolidPattern);
//  scode = ""; 
  radius = 40;
  mark=false;

//  tlist.setAutoDelete(TRUE);
//  reflist.setAutoDelete(FALSE);
}

/// Copy Constructor (dummy)
GState::GState(GState&gs) : QObject(), State(), GObject(0,0)
{

  setPen(gs.getPen());
  setBrush(gs.getBrush());
  setRadius(gs.getRadius());
  setLineWidth(gs.getLineWidth());
  setMark(gs.getMark());

//  tlist.setAutoDelete(TRUE);
//  reflist.setAutoDelete(FALSE);
}


/**
 * Makes a deep copy of the transitions of a state.
 * A deep copy is also made of the transitions ending at this state.
 * @param s state containing the transitions to copy
 * @param deleteold if TRUE deletes the old transitions in this state otherwise
 * not.
 */
void GState::copyTransitions(GState* s, bool deleteold/*=FALSE*/)
{
  QMutableListIterator<GTransition*> i(s->tlist);
  QMutableListIterator<GTransition*> j(s->reflist);

  GTransition *t, *tmp, *tr;

//  tlist.setAutoDelete(deleteold);
//  reflist.setAutoDelete(deleteold); //FALSE);
  if(deleteold)
  {
    qDeleteAll(tlist);
    qDeleteAll(reflist);
  }
  
  tlist.clear();
  reflist.clear();

  for(; i.hasNext();)
  {
    t = i.next();
    
    tmp = new GTransition();
    *tmp = *t;

    tlist.append(tmp);
  }

  for(; j.hasNext();)
  {
    tr = j.next();

    if (tr->getEnd()!=this)
    {
      tmp = new GTransition();
      *tmp = *tr;

      reflist.append(tmp); //tr); //tmp);
    }
  }
//  tlist.setAutoDelete(TRUE);
//  reflist.setAutoDelete(TRUE);
}

/**
 * Copys the attributes of transitions.
 * The attributes of the transitions in the list @clist are copied into the 
 * transitions in of the state @a s.
 * @param s state containing the transitions which will be copied into
 * @param clist list containing the transitions which will be copied
 */
void GState::copyTransitionAttributes(GState* s, QList<GTransition*>* clist)
{
  QMutableListIterator<GTransition*> si(s->tlist);
  QMutableListIterator<GTransition*> sj(s->reflist);
  QMutableListIterator<GTransition*> ci(*clist); 	// destination pointers

  GTransition *t1, *t2;

//  for (; si.current(); ++si)
  for (; si.hasNext();)
  {
//    t1 = ci.current();
//    t2 = si.current();
    t1 = ci.peekNext();
    t2 = si.next();

//    if (!t2)
    if (!ci.hasNext())
      return;

    *t1 = *t2;
//    ++ci;
    ci.next();
  }
//  for (; sj.current(); ++sj)
  for (; sj.hasNext();)
  {
//    t1 = ci.current();
//    t2 = sj.current();
    t1 = ci.peekNext();
    t2 = sj.next();

    *t1 = *t2;
//    if (!t2)
    if (!ci.hasNext())
      return;

//    ++ci;
    ci.next();
  }
}

/// Used for debugging
void GState::debugTransitions(/*int numin, int numout*/)
{
  QMutableListIterator<GTransition*> i(tlist);
  QMutableListIterator<GTransition*> j(reflist);

  GTransition *t;
  double x, y, ex, ey, c1x, c1y, c2x, c2y;
  TransitionInfo* info;

  qDebug("tlist\n");
  for(; i.hasNext();)
  {
    t = i.next();

    t->getPos(x, y);
    t->getEndPos(ex, ey);
    t->getCPoint1(c1x, c1y);
    t->getCPoint2(c2x, c2y);
    info = t->getInfo();

    qDebug("Adresse:     %p", t);
    qDebug("Start:       %p", t->getStart());
    qDebug("Ende:        %p", t->getEnd());
    qDebug("Inputs:      %s", info->getInputsStrBin(/*numin*/).latin1());
    qDebug("Outputs:     %s", info->getOutputsStrBin(/*numout*/).latin1());
    qDebug(" ");
  }

  qDebug("reflist\n");
  for(; j.hasNext();)
  {
    t = j.next();

    t->getPos(x, y);
    t->getEndPos(ex, ey);
    t->getCPoint1(c1x, c1y);
    t->getCPoint2(c2x, c2y);
    info = t->getInfo();

    qDebug("Adresse:     %p", t);
    qDebug("Start:       %p", t->getStart());
    qDebug("Ende:        %p", t->getEnd());
    qDebug("Inputs:      %s", info->getInputsStrBin(/*numin*/).latin1());
    qDebug("Outputs:     %s", info->getOutputsStrBin(/*numout*/).latin1());
    qDebug(" ");
  }

}


/**
 * Returns the number of all (non-deleted) transitions which start at this state
 */
int GState::countTransitions()
{
  QMutableListIterator<GTransition*> i(tlist);

  int count=0;
  for(; i.hasNext();)
  {
    if (!i.next()->isDeleted())
      count++;
  }
  return count;
}

/**
 * Returns the number of all (non-deleted) transitions which end at this state
 */
int GState::countRefTransitions()
{
  QMutableListIterator<GTransition*> i(reflist);

  int count=0;
  for(; i.hasNext();)
  {
    if (!i.next()->isDeleted())
      count++;
  }
  return count;
}


/**
 * Copys attributes of the state @a s.
 */
void GState::copyAttributes(GState* s)
{
  machine = s->machine;
    xpos = s->xpos;
    ypos = s->ypos;
    sname = s->sname;
    sdescription = s->sdescription;
    code = s->code;
    moore_outputs = s->moore_outputs;

    pen = s->pen;
    brush = s->brush;
    radius = s->radius;
    entry_actions = s->entry_actions;
    exit_actions = s->exit_actions;
//    scode = s->scode;
}


/**
 * Adds a new transition in this state
 * @param p project which contains this state
 * @param s state where the transition ends
 * @param i information about the transition (condition)
 * @param sx x coordinate of the starting point
 * @param sy y coordinate of the starting point
 * @param ex x coordinate of the ending point
 * @param ey y coordinate of the ending point
 * @param c1x x coordinate of the first control point
 * @param c1y y coordinate of the first control point
 * @param c2x x coordinate of the second control point
 * @param c2y y coordinate of the second control point
 * @param str if TRUE the transition will be straight otherwise the transition
 *   will be treated as not straight
 * @param withundo If TRUE this step will be put into the undo buffer.
 */
void GState::addTransition(Project* p, GState* s, TransitionInfo* i,
			   double sx, double sy, double ex, 
			   double ey, double c1x/*=0*/, double c1y/*=0*/,
			   double c2x/*=0*/, double c2y/*=0*/, QString description/*=""*/,
			   bool str/*=TRUE*/, bool withundo/*=TRUE*/)
{
  GTransition* t;
  if (c1x==0 && c1y==0 && c2x==0 && c2y==0)
  {
    t = new GTransition(this, s, i, /*numin, in, numout, out,*/ sx, sy, 
      ex, ey, description, str);
  }
  else
  {
    t = new GTransition(this, s, i, /*numin, in, numout, out,*/ sx, sy, 
      c1x, c1y, c2x, c2y, ex, ey, description, str);
  }

  tlist.append(t);
  if (withundo)
    p->getUndoBuffer()->addTransition(t);

  if (s)
    s->reflist.append(t);
}

/**
 * Adds a transition to the state.
 *
 * @param p Project that contains the state
 * @param t Transition to add
 * @param withundo If TRUE this step will be put into the undo buffer.
 */
void GState::addTransition(Project* p, GTransition* t, bool withundo/*=TRUE*/)
{
  tlist.append(t);
  if (withundo)
    p->getUndoBuffer()->addTransition(t);

  GState* e = (GState*)t->getEnd();
  if (e)
    e->reflist.append(t);
}


/**
 * Moves the state.
 * @param x x value to move
 * @param y y value to move
 * @param sv respective scrollview
 * @param m machine constaining this state
 * @param redraw if TRUE the scrollview will be redrawn otherwise it won't
 * @param firstRedraw if TRUE it is the first movement of a series
 */
void GState::move(double x, double y, DrawArea* sv, Machine* m,
                  bool redraw/*=TRUE*/, bool firstRedraw/*=FALSE*/)
{
  GTransition* t;
  QMutableListIterator<GTransition*> it(reflist);
  QMutableListIterator<GTransition*> i(tlist);

  // move Transitions starting at this state

  for (;i.hasNext();)
  {
    t = i.next();

    if (redraw)
      sv->drawTransition(t, firstRedraw);

    if (t->getEnd()==NULL && sv->getDragMultiple()) 
    {						// transitions w/o dest
      if (t->isSelected())
      {
	t->moveStart(x, y, FALSE, TRUE);
        t->moveEnd(x, y, FALSE, FALSE);
      }
      else
        t->moveStart(x, y);
    }
    else if (t->getEnd()!=this) 		// no loops
    {
      if ( sv->getDragMultiple() && ((GState*)t->getEnd())->isSelected() &&
        !t->isStraight() )
      {
        t->moveStart(x, y, FALSE, TRUE, FALSE);
      }
      else if (t->isStraight())
        t->moveStart(x, y);
      else
        t->moveStart(x, y, FALSE, TRUE, FALSE);
    }
    else					// loops
    {
      t->moveStart(x, y, FALSE, TRUE);
    }

    if (redraw)
      sv->drawTransition(t);
  }

  // move Transitions ending at thie state

  for (;it.hasNext();)
  {
    t = it.next();
    if (redraw)
      sv->drawTransition(t, firstRedraw);

    if (t->getStart()==m->getPhantomState() && sv->getDragMultiple() )
    {					// transition from phantom state
      if (t->isSelected())
      {
	t->moveStart(x, y, FALSE, FALSE);
	t->moveEnd(x, y, FALSE, TRUE);
      }
      else
	t->moveEnd(x, y);
    }
    else if (t->getStart()!=this)		// no loops
    {
      if (t->isStraight())
        t->moveEnd(x, y);
      else
        t->moveEnd(x, y, FALSE, TRUE , FALSE);
    }
    else					// loops
    {
      t->moveEnd(x, y, FALSE);
    }

    if (redraw)
      sv->drawTransition(t);
  }

  if (m->getInitialState()==this)
  {
    GITransition* it = m->getInitialTransition();
    if (redraw && m->getDrawITrans())
      sv->drawInitialTransition(it, firstRedraw);
    it->move(x, y);
    if (redraw && m->getDrawITrans())
      sv->drawInitialTransition(it);
  }

  GObject::move(x, y);
}



// 
// Name:		circleEdge
// Description:		calculates a point at the edge of the state relative 
//			to the position (mousex, mousey)
//		
// x, y			state position
// rad			state radius
// mousex, mousey 	mouse position (inside state)
// destx, desty		return values 
// addphi		angle to add (in deg)
//
/**
 * Calculates a point at the edge of the state relative to the position (@a
 * mousex, @a mousey).
 * @param x state x position
 * @param y state y position
 * @param rad state radius
 * @param mousex mouse x position (inside state)
 * @param mousey mouse y position (inside state)
 * @param destx resulting x coordinate 
 * @param desty resulting y coordinate
 * @param addphi angle to add to the point. (relative to center of circle)
 */
void GState::circleEdge(double x, double y, int rad, double mousex, 
                double mousey, double& destx, double& desty, 
		double addphi/*=0*/)
{
  double m;
  double phi;

  if (x==mousex && y==mousey)
    mousey+=1;

  if (mousex!=x)
    m = (mousey-y)/(mousex-x);
  else
    m = (mousey-y)/0.000001;

  phi = atan(m);
  phi += (addphi*PI/180);

  destx = rad * cos(phi);
  desty = rad * sin(phi);

  if (mousex<x)
  {
    destx*=(-1);
    desty*=(-1);
  }

  destx += x;
  desty += y;
}

/**
 * Calculates a loop.
 * Calculates the position of the control points in order to get a loop.
 * @param x x position of the state
 * @param y y position of the state
 * @param rad radius of the state
 * @param mousex x position of the mouse
 * @param mousey y position of the mosue
 * @param c1x x coordinate of the first control point
 * @param c1y y coordinate of the first control point
 * @param c2x x coordinate of the second control point
 * @param c2y y coordinate of the second control point
 */
void GState::calcLoop(double x, double y, int rad, double mousex, 
                double mousey, double& c1x, double& c1y, double& c2x, 
		double& c2y)
{
  double m;
  double phi;
  double phi1, phi2;

  if (x==mousex && y==mousey)
    mousey+=1;

  if (mousex!=x)
    m = (mousey-y)/(mousex-x);
  else 
    m = (mousey-y)/0.000001;

  phi = atan(m);
  if (mousex<x)
  {
    phi += PI;
  }
  phi1 = phi-(15*PI/180);
  phi2 = phi+(55*PI/180);

  c1x = (rad+80) * cos(phi1);
  c1y = (rad+80) * sin(phi1);
  c2x = (rad+80) * cos(phi2);
  c2y = (rad+80) * sin(phi2);

  c1x += x;
  c1y += y;
  c2x += x;
  c2y += y;
}


/**
 * Removes the transition @a trem from the list of this state.
 */
void GState::removeTransition(GTransition* trem)
{
  GState* s;
  s = (GState*)trem->getEnd();

  trem->select(FALSE);
  trem->setDeleted();
}
      
/**
 * Removes the transition @a trem which ends at this state from the list
 */
void GState::removeTransitionEnd(GTransition* trem)
{
//  reflist.removeRef(trem);
    reflist.removeAll(trem);
}


/**
 * Returns the bounding rectangle of this state.
 */
DRect GState::getMaxRect()
{
  double x1, x2, y1, y2;
  double k;

  k = radius / sqrt(2.0);
  if (isFinalState())
    k-=2;

  x1 = xpos - k;
  y1 = ypos - k;
  x2 = xpos + k;
  y2 = ypos + k;

  DRect r(x1, y1, x2, y2);
  return r;
}


bool GState::hasDefaultTransition()
{
  QListIterator<GTransition*> it(tlist);
  GTransition* t;

  for(; it.hasNext(); )
  {
    t = it.next();
    if (!t->isDeleted() && t->getInfo()->getInputInfo()->isDefault())
      return true;
  }
  return false;   
}

bool GState::hasAnyTransition()
{
  QListIterator<GTransition*> it(tlist);
  GTransition* t;

  for(; it.hasNext(); )
  {
    t = it.next();
    if (!t->isDeleted() && t->getInfo()->getInputInfo()->getAnyInput())
      return true;
  }
  return false;   
}



/** 
 * Sets transitions to the boundary of this state.
 * Sets all transitions which start and end at this state to the boundary of
 * the circle of this state.
 * @param m machine containing this state
 * @param radius new radius
 */
void GState::setTransitionsToRadius(Machine* m, int radius)
{
  GTransition* t;
  GITransition* it;
  double tx, ty, tnx, tny;
  
  QMutableListIterator<GTransition*> i(tlist);
  for(;i.hasNext();)
  {
    t=i.next();
    t->getPos(tx, ty);
    GState::circleEdge(xpos, ypos, radius, tx, ty, tnx, tny);
    if (t->getEnd()!=this)
      t->setPos(tnx, tny);
    else
      t->move(tnx-tx, tny-ty);
  }
  QMutableListIterator<GTransition*> j(reflist);
  for(;j.hasNext();)
  {
    t=j.next();
    t->getEndPos(tx, ty);
    GState::circleEdge(xpos, ypos, radius, tx, ty, tnx, tny);
    if (t->getStart()!=this)
      t->setEndPos(tnx, tny);
  }
  if (m->getInitialState()==this)
  {
    it = m->getInitialTransition();
    it->getEndPos(tx, ty);
    GState::circleEdge(xpos, ypos, radius, tx, ty, tnx, tny);
    it->setEndPos(tnx, tny);
  }
}

QString GState::getToolTipInfo(Machine* /*m=NULL*/, Options* /*opt=NULL*/)
{
  QString result;
  QString desc;
  QString dname, ddesc, dmooreout, dcode;
  unsigned int longest=0;
  int valuepos;
  QString padding;

  dname = tr("Name:");
  ddesc = tr("Description:");
  dmooreout = tr("Moore Outputs:");
  dcode = tr("Code:");

  desc = sdescription;

  if (dname.length() > longest)
    longest = dname.length();
  if (!desc.isEmpty() && ddesc.length() > longest)
    longest = ddesc.length();
  if (!(machine && machine->getType()==Text))
  {
    if (dmooreout.length() > longest)
      longest = dmooreout.length();
    if (dcode.length() > longest)
      longest = dcode.length();
  }

  valuepos = longest+1;
  
  result  = dname + padding.fill(' ', valuepos-dname.length()) + sname + "\n";
  if (!desc.isEmpty())
  {
    desc.replace(QRegExp("\n"), "\n" + padding.fill(' ', valuepos));
    result += ddesc + padding.fill(' ', valuepos-ddesc.length()) + desc + "\n";
  }
  if (!(machine && machine->getType()==Text))
  {
    result += dmooreout + padding.fill(' ', valuepos-dmooreout.length()) + getMooreOutputsStr() + "\n";
    result += dcode + padding.fill(' ', valuepos-dcode.length()) + getCodeStr();
  }

  return result;
}

QRect GState::getToolTipRect(const QPoint& )
{
  return QRect(int(xpos)-radius, int(ypos)-radius, radius*2, radius*2);
}


/// Returns the following state assuming inputs @a in are input to the machine
GState* GState::next(IOInfo* in, IOInfo*& out)
{
  GTransition* t;

  QMutableListIterator<GTransition*> i(tlist);
  TransitionInfo* tinfo;

  for(; i.hasNext();)
  {
    t = i.next();

    tinfo = t->getInfo();
    if (!t->isDeleted() && tinfo->matches(in))
    {  
      out = tinfo->getOutputInfo();
      return (GState*)t->getEnd();
    }
  }
  return NULL;
}


void GState::updateDefaultTransition()
{
  GTransition* t;

  QMutableListIterator<GTransition*> i(tlist);
  TransitionInfo* tinfo;
  IOInfo* def_info=NULL;
  IOInfoList list;
//  list.setAutoDelete(TRUE);

  for(; i.hasNext();)
  {
    t = i.next();

    tinfo = t->getInfo();
    if (!t->isDeleted() && tinfo->getInputInfo()->isDefault())
      def_info = tinfo->getInputInfo();
  }
  if (!def_info)
    return;

  i.toFront();
  for(; i.hasNext();)
  {
    t = i.next();

    tinfo = t->getInfo();
    if (!t->isDeleted() && !tinfo->getInputInfo()->isDefault())
      list.append(tinfo->getInputInfo()->clone());
  }
  def_info->updateDefaultInfo(list);
}



