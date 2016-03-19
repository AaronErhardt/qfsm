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

added #include <QRect>
*/

#ifndef GOBJECT_H
#define GOBJECT_H

#include <qobject.h>
#include <qpoint.h>
#include <QRect>

class Grid;
class Machine;
class Options;

/**
 * @class GObject
 * @brief Base class for all graphical objects.
 *
 */
class GObject //: public QObject
{
//  Q_OBJECT
  public:
    GObject(double , double ); // , QObject* parent=0, const char* name=0 );
    virtual ~GObject();

    /// Gets @a x and @a y coordinate of object.
    void getPos(double& x, double& y) { x=xpos; y=ypos; };
    /// Sets @a x and @a y coordinate of object.
    virtual void setPos(const double x, const double y) { xpos = x; ypos = y; };
    /// Sets the x coordinate of the position
    virtual void setXPos(const double x) { xpos = x; };
    /// Sets the y coordinate of the position
    virtual void setYPos(const double y) { ypos = y; };
//    virtual void alignToGrid(Grid* g);
    /// Returns TRUE if object is selected otherwise FALSE
    bool isSelected() { return selected; };
    /// If @a select is TRUE selects object otherwise deselects it.
    void select(bool select=TRUE) { selected = select; };
    /// Toggles the select state
    void toggleSelect() { selected=!selected; };
    /// Returns TRUE if object is deleted otherwise FALSE.
    bool isDeleted() { return deleted; };
    /// If @a d is TRUE deletes object otherwise undeletes it.
    void setDeleted(bool d=TRUE) { deleted = d; };

    virtual void move(double , double );
    /// Returns the tooltip string for this object
    virtual QString getToolTipInfo(Machine* m=NULL, Options* opt=NULL)=0;
    /// Returns the tooltip rectangle (if the mouse leaves this rectangle the TT is closed).
    virtual QRect getToolTipRect(const QPoint& p)=0;

  protected:
    /// X coordinate of the position
    double xpos;
    /// Y coordinate of the position
    double ypos;
    /// If TRUE the object is selected
    bool selected;
    /// If TRUE the object is marked as deleted (and not drawn)
    bool deleted;
};


#endif
