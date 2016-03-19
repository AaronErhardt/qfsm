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

#include "Options.h"
#include "Grid.h"

/**
 * Constructor.
 * Initialises the Grid object.
 * @param opt application options which store the grid size and color.
 */
Grid::Grid(Options* opt)
{
  options = opt;
}


/**
 * Gets the nearest point on the grid to any point.
 * @param x x coordinate of point
 * @param y y coordinate of point
 * @param gx x coordinate of the nearest point on the grid
 * @param gy y coordinate of the nearest point on the grid
 */
void Grid::getPoint(double x, double y, double& gx, double& gy)
{
  double gridunit;
  gridunit = options->getGridSize();

  gx = int((x + gridunit/2)/ gridunit)*gridunit;
  gy = int((y + gridunit/2)/ gridunit)*gridunit;
}


