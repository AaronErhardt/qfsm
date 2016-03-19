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

added Qt:: to Qt all constants

in method contentsMouseReleaseEvent:
replaced removeRef by the code needed for the Qt 4-QList-class
replaced all Qt 3-iterators by Qt 4-iterators

all paint commands have been removed from contentsMouseMoveEvent,
because painting is only possible inside a paintEvent.
contentsMouseMoveEvent calls repaint, instead.

*/

#ifndef SCROLLVIEW_H
#define SCROLLVIEW_H

#include <q3scrollview.h>
#include <qcursor.h>
//Added by qt3to4:
#include <QMouseEvent>
#include <QPaintEvent>
#include <QScrollArea>
#include <QResizeEvent>

#include "DRect.h"
#include "GState.h"
#include "GITransition.h"
#include "Selection.h"



class ScrollView :public QScrollArea
{

  Q_OBJECT

  DrawArea*drawArea;
  MainWindow*main;

  public:
    ScrollView(QWidget* parent=0, const char* name=0);

    DrawArea*getDrawArea()
    { return drawArea; }

    void updateBackground();
    void updateSize(QResizeEvent* e=NULL);

  public slots:
    void scrollContents(int dx,int dy);
    void scrollContentsTo(int x,int y);

  protected:
    virtual void resizeEvent(QResizeEvent*);


};


#endif


