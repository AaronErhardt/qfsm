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

#ifndef GITRANSITION_H
#define GITRANSITION_H

#include <qpoint.h>
#include <qrect.h>

#include "GObject.h"
#include "Transition.h"

class State;
class GState;

/**
 * @class GITransition
 * @brief Stores information about the graphical object of the initial transition.
 *
 */ 
class GITransition : public GObject, public Transition
{
  public:
    GITransition();
    GITransition(State* , GState*);
    ~GITransition();

    void getEndPos(double& x, double& y) /// Gets coordinates of end point
      { x=endx; y=endy; };
    void setEndPos(double x, double y) /// Sets coordinates of end point
      { endx=x; endy=y; };
    /// Sets the x coordinate of the end point
    void setEndPosX(double x) 
      { endx = x; };
    /// Sets the y coordinate of the end point
    void setEndPosY(double y)
      { endy = y; };
    
    void move(double, double);
    bool contains(double, double);
    int onControlPoint(double, double , double);

    QString getToolTipInfo(Machine* =NULL, Options* =NULL);
    QRect getToolTipRect(const QPoint& );
    
    /// Returns TRUE if the transition is being dragged
    bool isDragged() { return dragged; };
    /// Sets the dragged state to @a ds
    void setDragged(bool ds) { dragged = ds; };

  private:
    /// End x position
    double endx;
    /// End y position
    double endy;
    
    /// IF TRUE the transition is being dragged by the user
    bool dragged;
};


#endif
