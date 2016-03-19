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

#include "GObject.h"
#include "Grid.h"

/**
 * Constructor.
 * Initialises GObject object with the coordinates @x and @y.
 */
GObject::GObject(double x, double y) //, QObject* par/*=0*/, const char* nam/*=0*/)
//       : QObject(par, nam)
{
  xpos = x;
  ypos = y;
  selected = FALSE;
  deleted = FALSE;
}

/// Destructor
GObject::~GObject()
{
}

/**
 * Moves the object by x rightwards and y downwards.
 */
void GObject::move(double x, double y)
{
  xpos += x;
  ypos += y;
}

/*
void GObject::alignToGrid(Grid* g)
{
  double newxpos, newypos;
  g->getPoint(xpos, ypos, newxpos, newypos);
  xpos = newxpos;
  ypos = newypos;
}
*/


