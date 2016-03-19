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

#ifndef GTRANSITION_H
#define GTRANSITION_H

#include "GObject.h"
#include "Transition.h"

class State;
class TransitionInfo;


/**
 * @class GTransition
 * @brief The graphical Object of a transition (arrow).
 *
 */ 
class GTransition : public GObject, public Transition
{
  public:
    GTransition();
//    GTransition(const GTransition&);
    GTransition(State* , State* , TransitionInfo*, double , double, double, 
      double , QString, bool str=TRUE);
    GTransition(State* , State* , TransitionInfo*, double , double, double, 
      double, double, double, double, double , QString, bool str=TRUE);

    void setStartPos(double , double );
    void setEndPos(double x, double y); 
    void setEndPosX(double x);
    void setEndPosY(double y);
    /// Returns the end position (arrowhead) of the transition
    void getEndPos(double& x, double& y) { x = endx; y = endy; };
    /// Sets the position of the first control point
    void setCPoint1(double x, double y) { control1x = x; control1y = y; };
    /// Sets the x coordinate of the position of the first control point
    void setCPoint1X(double x) { control1x = x; };
    /// Sets the y coordinate of the position of the first control point
    void setCPoint1Y(double y) { control1y = y; };
    /// Returns the position of the first control point
    void getCPoint1(double& x, double& y) { x = control1x; y = control1y; };
    /// Sets the position of the second control point
    void setCPoint2(double x, double y) { control2x = x; control2y = y; };
    /// Sets the x coordinate of the position of the second control point
    void setCPoint2X(double x) { control2x = x; };
    /// Sets the y coordinate of the position of the second control point
    void setCPoint2Y(double y) { control2y = y; };
    /// Returns the position of the first control point
    void getCPoint2(double& x, double& y) { x = control2x; y = control2y; };
    /// Returns TRUE if the transition is straight otherwise FALSE
    bool isStraight() { return straight; };
    /** If @a s is TRUE declares the transition as straight otherwise declare
      it as not straight */
    void setStraight(bool s=TRUE) { straight = s; };

    void move(double , double );
    void moveStart(double , double, bool move_cont_rel=TRUE,
      bool move_cont=FALSE, bool move_cont_both=TRUE);
    void moveEnd(double , double , bool move_cont_rel=TRUE, 
      bool move_cont=FALSE, bool move_cont_both=TRUE);
    void moveCPoint1(double , double );
    void moveCPoint2(double , double );

    bool contains(double , double);
    void bezierCurve(double, double& , double&);
    int onControlPoint(double, double, double);

    void straighten();

    QString getToolTipInfo(Machine* m=NULL, Options* opt=NULL);
    QRect getToolTipRect(const QPoint& );
    
    /// Returns the description of the transition
    QString getDescription() {return description; };
    /// Sets the descriptionn of the transition
    void setDescription(QString d) {description = d; };

    /// Returns TRUE if the transition is being dragged
    bool isDragged() { return dragged; };
    /// Sets the dragged state to @a ds
    void setDragged(bool ds) { dragged = ds; };

    /// Returns the testbench export mark
    int getMark() { return mark; };
    /// Sets the testbench export mark
    void setMark(const int m) { mark = m; };
    /// Returns the testbench export mark
    int getMarkMax() { return mark_max; };
    bool checkMark() {return mark>=mark_max; }
    void setMarkMax();

  private:
    /// X coordinate of the first control point
    double control1x; 
    /// Y coordinate of the first control point
    double control1y;
    /// X coordinate of the second control point
    double control2x;
    /// Y coordinate of the second control point
    double control2y;
    /// X coordinate of the end point
    double endx;
    /// Y coordinate of the end point
    double endy;
    /// If TRUE the transition will be drawn as straight line (not as bezier curve)
    bool straight;
    /// Description
    QString description;
    /// IF TRUE the transition is being dragged by the user
    bool dragged;
    /// Marker for testbench export
    int mark;
    /// Maximum value for marker counter
    int mark_max;
};


#endif
