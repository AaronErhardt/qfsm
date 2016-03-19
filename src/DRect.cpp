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

#include "DRect.h"


/**
 * Standard contructor.
 * Sets all coordinates to 0.
 */
DRect::DRect()
{
  x1 = y1 = x2 = y2 = 0;
}

/**
 * Contructor.
 * @param dx1 x coordinate of first point 
 * @param dy1 y coordinate of first point 
 * @param dx2 x coordinate of second point 
 * @param dy2 y coordinate of second point 
 */
DRect::DRect(double dx1, double dy1, double dx2, double dy2)
{
  x1 = dx1;
  y1 = dy1;
  x2 = dx2;
  y2 = dy2;
}


/**
 * Moves rectangle by @a x rightwards and @a y downwards
 */
void DRect::moveBy(double x, double y)
{
  x1+=x;
  x2+=x;
  y1+=y;
  y2+=y;
}


/**
 * Normalizes rectangle.
 * Changes coordinates so that the first point is the upper left an the second
 * the lower right one.
 */
void DRect::normalize()
{
  double tmp;

  if (x2<x1)
  {
    tmp=x1;
    x1 = x2;
    x2 = tmp;
  }
  if (y2<y1)
  {
    tmp=y1;
    y1 = y2;
    y2 = tmp;
  }
}

/**
 * Checks if the point with the coordinates @a x and @a y lies in the rectangle.
 */
bool DRect::contains(double x, double y)
{
  double minx, maxx, miny, maxy;

  minx = (x1<x2 ? x1 : x2);
  maxx = (x1>x2 ? x1 : x2);
  miny = (y1<y2 ? y1 : y2);
  maxy = (y1>y2 ? y1 : y2);

  if (x>minx && x<maxx && y>miny && y<maxy)
    return TRUE;

  return FALSE;
}


/**
 * Sets the coordinates.
 */
void DRect::setCoords(double dx1, double dy1, double dx2, double dy2)
{
  x1 = dx1;
  y1 = dy1;
  x2 = dx2;
  y2 = dy2;
}

/**
 * Returns a QRect object with the rounded coordinates of the rectangle.
 */
QRect DRect::getQRect()
{
  QRect r;
  r = QRect(int(x1), int(y1), int(x2-x1), int(y2-y1));
  return r;
}


/**
 * Returns a QRect object with the coordinates adapted to the current scale.
 */
QRect DRect::getQRect(double scale)
{
  QRect r;
  r = QRect(int(x1*scale), int(y1*scale), int((x2-x1)*scale), int((y2-y1)*scale));
  return r;
}
