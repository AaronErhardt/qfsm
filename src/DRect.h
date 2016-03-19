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

#ifndef DRECT_H
#define DRECT_H

#include <qrect.h>

/**
 * @class DRect
 * @brief Rectangle containing coordinates in double format.
 *
 */
class DRect
{
  public:
    DRect();
    DRect(double, double, double, double);

    void moveBy(double, double);
    void normalize();
    bool contains(double, double);
    void setCoords(double, double, double, double);
    double left() /** Returns x coordinate of left border. */ { return x1; };
    double top() /** Returns y coordinate of top border. */{ return y1; };
    double right() /** Returns x coordinate of right border. */ { return x2; };
    double bottom() /** Returns y coordinate of bottom border.*/ { return y2; };
    QRect getQRect();
    QRect getQRect(double);

  private:
    /// X coordinate of the first point
    double x1;
    /// X coordinate of the second point
    double x2;
    /// Y coordinate of the first point
    double y1;
    /// Y coordinate of the second point
    double y2;

};



#endif
