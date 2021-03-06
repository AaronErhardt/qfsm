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

#include <QRect>
#include <qobject.h>
#include <qpoint.h>

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
  GObject(double, double); // , QObject* parent=0, const char* name=0 );
  virtual ~GObject();

  /// Gets @a x and @a y coordinate of object.
  void getPos(double &x, double &y) {
    x = xpos;
    y = ypos;
  };
  /// Sets @a x and @a y coordinate of object.
  virtual void setPos(const double x, const double y) {
    xpos = x;
    ypos = y;
  };
  /// Sets the x coordinate of the position
  virtual void setXPos(const double x) { xpos = x; };
  /// Sets the y coordinate of the position
  virtual void setYPos(const double y) { ypos = y; };
  //    virtual void alignToGrid(Grid* g);
  /// Returns true if object is selected otherwise false
  bool isSelected() { return selected; };
  /// If @a select is true selects object otherwise deselects it.
  void select(bool select = true) { selected = select; };
  /// Toggles the select state
  void toggleSelect() { selected = !selected; };
  /// Returns true if object is deleted otherwise false.
  bool isDeleted() { return deleted; };
  /// If @a d is true deletes object otherwise undeletes it.
  void setDeleted(bool d = true) { deleted = d; };

  virtual void move(double, double);
  /// Returns the tooltip string for this object
  virtual QString getToolTipInfo(Machine *m = NULL, Options *opt = NULL) = 0;
  /// Returns the tooltip rectangle (if the mouse leaves this rectangle the TT
  /// is closed).
  virtual QRect getToolTipRect(const QPoint &p) = 0;

protected:
  /// X coordinate of the position
  double xpos;
  /// Y coordinate of the position
  double ypos;
  /// If true the object is selected
  bool selected;
  /// If true the object is marked as deleted (and not drawn)
  bool deleted;
};

#endif
