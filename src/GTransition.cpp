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

#include "GTransition.h"
#include "GState.h"
#include "Const.h"
#include "TransitionInfo.h"
#include "Options.h"
#include "IOInfoList.h"


/**
 * Standard constructor.
 */
GTransition::GTransition()
	    :GObject(0,0), Transition(NULL, NULL, NULL)
{
  control1x = control1y = control2x = control2y = 0;
  endx = endy = 0;
  straight = TRUE;
  description = "";
  dragged=FALSE;
  mark=0;
  mark_max=0;
}



/**
 * Constructor.
 * Initialises a new transition object setting the control points between start
 * and end point.
 * @param s starting state
 * @param e end state
 * @param i info about the transition (condition)
 * @param startx x coordinate of starting point
 * @param starty y coordinate of starting point
 * @param ex x coordinate of end point
 * @param ey y coordinate of end point
 * @param str if TRUE declares the transition as straight otherwise declares it
 * as not straight
 */
GTransition::GTransition(State* s, State* e, TransitionInfo* i,
			 double startx, double starty, 
			 double ex, double ey, QString d, bool str/*=TRUE*/)
           :GObject(startx,starty), Transition(s, e, i) 
{
  control1x = startx+(ex-startx)/3;
  control1y = starty+(ey-starty)/3;
  control2x = startx+(ex-startx)*2/3;
  control2y = starty+(ey-starty)*2/3;
  endx = ex;
  endy = ey;
  straight = str;
  description = d;
  dragged=FALSE;
  mark=0;
  mark_max=0;
}


/**
 * Contructor.
 * Initialises a new transition object.
 * @param s starting state
 * @param e end state
 * @param i info about the transition (condition)
 * @param startx x coordinate of starting point
 * @param starty y coordinate of starting point
 * @param c1x x coordinate of first control point
 * @param c1y y coordinate of first control point
 * @param c2x x coordinate of second control point
 * @param c2y y coordinate of second control point
 * @param ex x coordinate of end point
 * @param ey y coordinate of end point
 * @param str if TRUE declares the transition as straight otherwise declares it
 * as not straight
 */
GTransition::GTransition(State* s, State* e, TransitionInfo* i,
                         double startx, double starty, 
			 double c1x, double c1y, double c2x, double c2y,
			 double ex, double ey, QString d, bool str/*=TRUE*/)
           :GObject(startx,starty), Transition(s, e, i)
{
  control1x = c1x;
  control1y = c1y;
  control2x = c2x;
  control2y = c2y;
  endx = ex;
  endy = ey;
  straight=str;
  description = d;
  dragged = FALSE;
  mark=0;
  mark_max=0;
}

/*
GTransition::GTransition(const GTransition& t)
  : GObject(t.xpos, t.ypos), Transition(t)
{
  control1x = t.control1x;
  control1y = t.control1y;
  control2x = t.control2x;
  control2y = t.control2y;
  endx = t.endx;
  endy = t.endy;
  straight = t.straight;
}
*/


/**
 * Sets the start position of the transition.
 * If the transition is straight the control points are set accordingly.
 */
void GTransition::setStartPos(double x, double y)
{
  xpos = x;
  ypos = y;

  if (straight)
  {
    control1x = xpos+(endx-xpos)/3;
    control1y = ypos+(endy-ypos)/3;
    control2x = xpos+(endx-xpos)*2/3;
    control2y = ypos+(endy-ypos)*2/3;
  }
}

/**
 * Sets the end point of the transition.
 * If the transition is straight the control points are set accordingly.
 */
void GTransition::setEndPos(double x, double y)
{
  endx = x;
  endy = y;

  if (straight)
  {
    control1x = xpos+(endx-xpos)/3;
    control1y = ypos+(endy-ypos)/3;
    control2x = xpos+(endx-xpos)*2/3;
    control2y = ypos+(endy-ypos)*2/3;
  }
}

/// Sets the x coordinate of the position of the end point
void GTransition::setEndPosX(double x)
{
  endx = x;

  if (straight)
  {
    control1x = xpos+(endx-xpos)/3;
    control1y = ypos+(endy-ypos)/3;
    control2x = xpos+(endx-xpos)*2/3;
    control2y = ypos+(endy-ypos)*2/3;
  }
}

/// Sets the y coordinate of the position of the end point
void GTransition::setEndPosY(double y)
{
  endy = y;

  if (straight)
  {
    control1x = xpos+(endx-xpos)/3;
    control1y = ypos+(endy-ypos)/3;
    control2x = xpos+(endx-xpos)*2/3;
    control2y = ypos+(endy-ypos)*2/3;
  }
}

/**
 * Moves the transition with all its points by @a x rightwards and @a y 
 * downwards.
 */
void GTransition::move(double x, double y)
{
  xpos += x;
  ypos += y;
  control1x += x;
  control1y += y;
  control2x += x;
  control2y += y;
  endx += x;
  endy += y;
}


/**
 * Moves the start point of the transition.
 * @param x x value to move by
 * @param y y value to move by
 * @param move_cont_rel if TRUE and transition is straight the control 
 *   points are moved relative to the start and end point otherwise the control
 *   points aren't moved relatively
 * @param move_cont if TRUE moves the control points by @a x, @a y otherwise
 *   the control points aren't moved at all
 * @param move_cont_both if TRUE both control points are moved otherwise only
 *   the first one is moved
 */
void GTransition::moveStart(double x, double y, bool move_cont_rel/*=TRUE*/,
                      bool move_cont/*=FALSE*/, bool move_cont_both/*=TRUE*/)
{
  xpos += x;
  ypos += y;

  if (straight && !move_cont)
  {
    if (move_cont_rel)
    {
      control1x += x*2/3;
      control1y += y*2/3;
      control2x += x/3;
      control2y += y/3;
    }
  }
  if (move_cont)
  {
    control1x += x;
    control1y += y;
    if (move_cont_both)
    {
      control2x += x;
      control2y += y;
    }
  }
}

/**
 * Moves the end point of the transition.
 * @param x x value to move by
 * @param y y value to move by
 * @param move_cont_rel if TRUE and transition is straight the control 
 *   points are moved relative to the start and end point otherwise the control
 *   points aren't moved relatively
 * @param move_cont if TRUE moves the control points by @a x, @a y otherwise
 *   the control points aren't moved at all
 * @param move_cont_both if TRUE both control points are moved otherwise only
 *   the second one is moved
 */
void GTransition::moveEnd(double x, double y, bool move_cont_rel/*=TRUE*/,
		  bool move_cont/*=FALSE*/, bool move_cont_both/*=TRUE*/)
{
  endx += x;
  endy += y;

  if (straight && !move_cont)
  {
    if (move_cont_rel)
    {
      control1x += x/3;
      control1y += y/3;
      control2x += x*2/3;
      control2y += y*2/3;
    }
  }
  if (move_cont)
  {
    control2x += x;
    control2y += y;
    if (move_cont_both)
    {
      control1x += x;
      control1y += y;
    }
  }
}


/**
 * Moves the first control point.
 */
void GTransition::moveCPoint1(double x, double y)
{
  control1x += x;
  control1y += y;
  straight = FALSE;
}


/**
 * Moves the second control point.
 */
void GTransition::moveCPoint2(double x, double y)
{
  control2x += x;
  control2y += y;
 
  straight = FALSE;
}



/**
 * Returns TRUE if the point with the coordinates @a x and @a y lies on the
 * transition.
 */
bool GTransition::contains(double x, double y)
{
  double bx1, by1, bx2, by2;
  double dx, dy, m;
  double t=-0.0;
  double xmin, xmax;
  double ymin, ymax;
  const double ot = 2;
  double otminy, otmaxy;

  otminy = ypos<endy ? ypos : endy;
  otmaxy = ypos>endy ? ypos : endy;
  if (fabs(xpos-endx)<ot && fabs(xpos-control1x)<ot && fabs(xpos-control2x)<ot
      && control1y>otminy && control1y<otmaxy 
      && control2y>otminy && control2y<otmaxy
      && y>otminy && y<otmaxy && fabs(xpos-x)<ot)
    return TRUE;			// orthogonal line

  bezierCurve(t, bx2, by2);

  do
  {
    bx1 = bx2; 
    by1 = by2;

    t += 0.1;
    bezierCurve(t, bx2, by2);

    dx = (bx2-bx1);
    dy = (by2-by1);

    if (dx!=0)
      m = dy / dx;
    else
      m = 1000000;

    xmin = (bx1 < bx2 ? bx1 : bx2);
    xmax = (bx1 > bx2 ? bx1 : bx2);

    if (fabs(dx)<0.01)			// orthogonal line
    {
      //qDebug("ortho");
      ymin = (by1 < by2 ? by1 : by2);
      ymax = (by1 > by2 ? by1 : by2);

      if (fabs(x-bx1)<5 && y>ymin && y>ymax)
        return TRUE;
    }
    else if ((fabs(y - (m*(x-bx1)+by1))<6 ||
              fabs(x - ((y-by1)/m + bx1))<4) && x>xmin && x<xmax)  
      return TRUE;
    
  } while (t<=0.9);
    

  return FALSE;
}


/**
 * Bezier curve function.
 * @param t parameter (ranges from 0 to 1)
 * @param x resulting x coordinate
 * @param y resulting y coordinate
 */
void GTransition::bezierCurve(double t, double& x, double& y)
{
  x = pow(1-t,3)*xpos + 3*pow(1-t,2)*t*control1x + 3*(1-t)*t*t*control2x +
    pow(t,3)*endx;
  y = pow(1-t,3)*ypos + 3*pow(1-t,2)*t*control1y + 3*(1-t)*t*t*control2y +
    pow(t,3)*endy;
}



/**
 * Returns the number of the control point which lies on @a x, @a y at the
 * specified scale @a scale.
 * 1: start point
 * 2: first control point
 * 3: second control point
 * 4: end point
 */
int GTransition::onControlPoint(double x, double y, double scale)
{
  int rectsize;
  rectsize = int((double)CPOINT_SIZE/scale)+1;

  if (rectsize==0)
    rectsize=1;

  if (x>xpos-rectsize && x<xpos+rectsize &&
    y>ypos-rectsize && y<ypos+rectsize)
    return 1;
  else if (x>control1x-rectsize && x<control1x+rectsize && 
    y>control1y-rectsize && y<control1y+rectsize)
    return 2;
  else if (x>control2x-rectsize && x<control2x+rectsize && 
    y>control2y-rectsize && y<control2y+rectsize)
    return 3;
  else if (x>endx-rectsize && x<endx+rectsize && 
    y>endy-rectsize && y<endy+rectsize)
    return 4;
  
  return 0;
}


/**
 * Straightens the transition.
 * If start and end state are the same a loop is generated.
 */
void GTransition::straighten()
{
  if (start!=end)
  {
    control1x = xpos + (endx - xpos)/3;
    control1y = ypos + (endy - ypos)/3;
    control2x = xpos + (endx - xpos)*2/3;
    control2y = ypos + (endy - ypos)*2/3;
  }
  else
  {
    double x, y;
    int rad;
    double loopendx, loopendy;
    GState* tmp = (GState*)start;
  
    tmp->getPos(x, y);
    rad = tmp->getRadius();

    GState::circleEdge(x, y, tmp->getRadius(),
       xpos, ypos, loopendx, loopendy, 40);

    tmp->calcLoop(x, y, rad, xpos, ypos, control1x, control1y, control2x,
      control2y);

    endx = loopendx;
    endy = loopendy;
  }
  
  straight = TRUE;
}


QString GTransition::getToolTipInfo(Machine* m/*=NULL*/, Options* opt/*=NULL*/)
{
  QString sin, sout;
  QString sep;
  QString res;
  if (m==NULL || opt==NULL)
  {
    res = info->getInputsStr(NULL) + "/" + info->getOutputsStr(NULL);
    return res;
  }

  sin = info->getCompleteInputsStr(m, opt);
  sout = info->getOutputsStr(m, opt);

  sep = info->getSeparator(opt);

//  if (opt->getDisplayIONames())
  {
    if (sin.isEmpty())
      res = sout;
    if (sout.isEmpty())
      res = sin;
    else if (!sin.isEmpty())
      res = sin + sep + sout;
  }
  /*
  else
    res = sin + sep + sout;
    */
  if (!description.isEmpty())
  {
    res += "\n" + description;
  }

  return res;
}


QRect GTransition::getToolTipRect(const QPoint& p)
{
  return QRect(p.x()-3, p.y()-3, 6, 6);
}

/// Sets the testbench export mark
void GTransition::setMarkMax()
{
  IOInfoList list;
  info->getInputInfo()->split(list,(GState*)start);
  mark_max=list.size();
//  qDebug("Mark max of "+start->getStateName()+": "+QString::number(mark_max));

  while (!list.isEmpty())
    delete list.takeFirst();
}


