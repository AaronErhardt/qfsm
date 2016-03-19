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

#include <qrect.h>

#include "GITransition.h"
#include "GObject.h"
#include "GState.h"
#include "Transition.h"
#include "Const.h"


/// Constructor
GITransition::GITransition()
	    : GObject(0,0), Transition(NULL, NULL, NULL)
{
  dragged = FALSE;
  endx = 0; endy = 0;
}

/**
 * Constructor.
 * Initialises GITransition object.
 * @param s starting state (must be phantom state)
 * @param e end state (is initial state)
 */
GITransition::GITransition(State* s, GState* e)
	    : GObject(0, 0), Transition(s, (State*)e, NULL)
{
  double ex, ey;
  int radius;

  e->getPos(ex, ey);
  radius = e->getRadius();

  xpos = ex-radius-ITRANS_DEFAULT_LENGTH;
  ypos = ey;
  endx = ex-radius;
  endy = ey;
  dragged = FALSE;
}


/// Destructor
GITransition::~GITransition()
{

}


/**
 * Moves object by x rightwards and y downwards
 */
void GITransition::move(double x, double y)
{
  xpos += x;
  ypos += y;
  endx += x;
  endy += y;
}


/**
 * Checks if a point lies upon the initial transition.
 * @param x x coordinate of the point
 * @param y y coordinate of the point
 */
bool GITransition::contains(double x, double y)
{
  double dx, dy, m;
  double xmin, xmax, ymin, ymax;
  double gy, b;

  dx = endx-xpos;
  dy = endy-ypos;
  xmin = (endx<xpos? endx : xpos);
  xmax = (endx>xpos? endx : xpos);
  ymin = (endy<ypos? endy : ypos);
  ymax = (endy>ypos? endy : ypos);

  if (dx)
    m = dy/dx;
  else
  {
    // orthogonal line
    if (y>ymin && y<ymax)
      return TRUE;			
    else
      return FALSE;
  }

  if (x > xmin && x < xmax)
  {
    b = ypos - xpos * m;

    gy = m*x + b;
    if (y > gy-5 && y < gy+5)
      return TRUE;
  }
  return FALSE;
}



/**
 * Checks if a point lies upon one of the control points.
 * @param x x coordinate of the point
 * @param y y coordinate of the point
 * @param scale current scale factor
 */ 
int GITransition::onControlPoint(double x, double y, double scale)
{
  int rectsize;
  rectsize = int((double)CPOINT_SIZE/scale)+1;

  if (rectsize==0)
    rectsize=1;

  if (x>xpos-rectsize && x<xpos+rectsize &&
    y>ypos-rectsize && y<ypos+rectsize)
    return 11;
  else if (x>endx-rectsize && x<endx+rectsize && 
    y>endy-rectsize && y<endy+rectsize)
    return 14;
  
  return 0;
}



/// Returns the tooltip string for this object
QString GITransition::getToolTipInfo(Machine* , Options*)
{
  return "";
}

/// Returns the tooltip rectangle
QRect GITransition::getToolTipRect(const QPoint& p)
{
  return QRect(p.x()-3, p.y()-3, 6, 6);
}


