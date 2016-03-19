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
/*
Qt 4 Port by Rainer Strobel

added a dummy copy constructor, because the standard
copy constructor generated compiler errors
replaced Qt3 iterators through Qt 4 iterators
the list tlist and reflists store pointers of type QTransition.
This means that they have to be deleted with delete. There is no
AutoDelete feature for them.

in all constructors:
removed tlist.setAutoDelete(TRUE) and reflist.setAutoDelete(FALSE)
because the AutoDelete feature does not exist in Qt 4 and the new QList
uses references instead of pointers

in method copyTransitions:
removed setAutoDelete; the list items were deleted by qDeleteAll

in method copyTransitionAttributes:
modified code for compatibility with the new iterators

in method addTransition:
The Qt 4-QList saves references instead of pointers.
The list elements were deleted when the parent list is deleted,
but sometimes it may be needed to call delete during runtime.
*/
#ifndef GSTATE_H
#define GSTATE_H

#include <qpoint.h>
#include <qpen.h>
#include <qbrush.h>
#include <qfont.h>
#include <q3ptrlist.h>

#include "State.h"
#include "GObject.h"
#include "GTransition.h"
#include "DRect.h"

class DrawArea;
class Machine;
class TransitionInfo;
class Project;
class IOInfo;


/**
 * @class GState
 * @brief Graphical Object of a state.
 *
 * A state is drawn as a circle with its name and its code in it.
 */
class GState : public QObject, public State, public GObject
{
  Q_OBJECT

  public:
    GState(Machine* m, const QString, QString, int code, IOInfo* moore, double , double , int , QPen, bool end, QString ena, QString exa);
    GState(Machine* m);
    GState();
    GState(GState&gs);

    /// Returns pen to draw the state
    QPen& getPen() { return pen; };
    /// Sets the pen to draw the state
    void setPen(const QPen& p) { pen = p; };
    /// Returns the brush to draw the state
    QBrush& getBrush() { return brush; };
    /// Sets the brush to draw the state
    void setBrush(const QBrush& b) { brush = b; };
//    QString& getSCode() { return scode; };
//    void setSCode(const QString s) { scode = s; };
    /// Returns the radius.
    int getRadius() { return radius; };
    /// Sets the radius
    void setRadius(const int r) { radius = r; };
    /// Returns the linewidth
    int getLineWidth() { return pen.width(); };
    /// Sets the line width
    void setLineWidth(const int l) { pen.setWidth(l); };
    /// Returns the color of the state
    QColor getColor() { return pen.color(); };
    /// Sets the color of the state
    void setColor(QColor c) { pen.setColor(c); };
    /// Returns the integrity check mark
    bool getMark() { return mark; };
    /// Sets integrity check mark
    void setMark(const bool m) { mark = m; };

    void copyTransitions(GState*, bool =FALSE);
    void copyTransitionAttributes(GState*, QList<GTransition*>*);
    void copyAttributes(GState*);
    void debugTransitions(/*int, int numout */);

    void addTransition(Project*, GState* , TransitionInfo*, double sx, double sy,
      double ex, double ey, double c1x=0, double c1y=0, double c2x=0, double c2y=0, QString="", bool straight=TRUE, 
      bool withundo=TRUE);
    void addTransition(Project*, GTransition* t, bool withundo=TRUE);
    void move(double , double, DrawArea* , Machine* m, bool redraw=TRUE,
              bool firstRedraw=FALSE);
    void removeTransition(GTransition* );
    void removeTransitionEnd(GTransition* );
    DRect getMaxRect();
    int countTransitions();
    int countRefTransitions();
    void setTransitionsToRadius(Machine*, int );
    bool hasDefaultTransition();
    bool hasAnyTransition();

    QString getToolTipInfo(Machine* m=NULL, Options* opt=NULL);
    QRect getToolTipRect(const QPoint& );

    static void circleEdge(double , double, int, double, double, 
      double& , double& , double addphi=0);
    static void calcLoop(double, double, int, double, double, double&, 
      double&, double&, double&);

    GState* next(IOInfo* in, IOInfo*& out);
    void updateDefaultTransition();

    /// List of transitions starting from that state (this state is responsible for deleting these)
    QList<GTransition*> tlist;
    /// List of transitions ending in this state (this state must not delete these)
    QList<GTransition*> reflist;


  private:
    /// Pen used to draw the circle and the line in the middle
    QPen pen;
    /// Brush used for the background color
    QBrush brush;
    /// Radius of the circle
    int radius;
    /// Maker for machine integrity check and testbench export
    bool mark;
};

#endif
