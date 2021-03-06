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

replaced a p->moveTo() and p->lineTo() through a single
p->drawLine() command
p->setRasterOp() has been replaced by p->setCompositionMode(),
but the mode SetROP does no longer exist

in method drawStates:
changed i.toLast to i.toBack
changed i.current to i.hasPrevious in for loop
and used i.previous command for access, which moves the iterator
in method drawState:
in method drawTransitions:
changed QListIterator to QMutableListIterator which returns no const element,
replaced current requests through next requests and adapted the for loops
in method drawCondition:
removed declaration of Qt::white
*/

#ifndef DRAW_H
#define DRAW_H

#include <qobject.h>
#include <qpainter.h>

class Machine;
class GState;
class ScrollView;
class GTransition;
class Options;
class GITransition;
class Grid;
class Transition;

/**
 * @class Draw
 * @brief Drawing class responsible for all graphical representation.
 *
 */

class Draw : public QObject {
  Q_OBJECT
public:
  Draw(QObject *, Options *);

  void drawStates(Machine *, QPainter *, int, int, double);
  //    void drawState(Machine* m, GState* , QPainter* , int , int , double ,
  //     bool drawxor=true);
  void drawTransitions(Machine *, QPainter *, int, int, double /*, int, int*/);
  void drawTransition(Machine *, GTransition *, QPainter *, int, int, double,
                      /*int, int,*/ bool drawxor = true, bool dotted = true,
                      bool control_lines = false, bool first = false);
  void drawArrow(GTransition *, QPainter *, QPen, int);
  void drawArrow(GITransition *, QPainter *, QPen, int);
  void drawCondition(Machine *m, GTransition *, QPainter *, int, int,
                     double /*, int, int*/);
  void drawInitialTransition(Machine *m, GITransition *, QPainter *, int contx,
                             int conty, double scale, QRect &textrect,
                             bool drawxor = false, bool first = false,
                             bool transptext = false);
  void drawGrid(Grid *, QPainter *, int, int, double);

  void calcArrow(GTransition *, double &, double &, double &, double &,
                 double &xm, double &ym);
  void calcArrow(GITransition *, double &, double &, double &, double &,
                 double &xm, double &ym);
  void calcArrow(double p1x, double p1y, double p2x, double p2y, double &xl,
                 double &yl, double &xr, double &yr, double &xm, double &ym);

  void drawHeadline(Machine *, QPainter *); // , double);
  QRect getBoundingBox(Machine *, QPainter *);

private:
  /// Pointer to the application options
  Options *options;
  bool grid_calculated; // not used (yet)
  QPixmap grid_pixmap;  // not used (yet)
};

#endif
