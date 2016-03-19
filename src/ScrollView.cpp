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

#include <q3scrollview.h>
#include <qrect.h>
//Added by qt3to4:
#include <QMouseEvent>
#include <QPaintEvent>
#include <QDragEnterEvent>
#include <QDropEvent>

#include <list>
#include "ScrollView.h"
#include "MainWindow.h"
#include "DocStatus.h"
#include "GState.h"
#include "Project.h"
#include "Machine.h"
#include "Selection.h"
#include "Const.h"
#include "Zoom.h"
#include "Draw.h"
#include "TransitionInfoBin.h"
#include "UndoBuffer.h"
#include "StatusBar.h"
#include "Grid.h"
#include "ToolTipSV.h"
#include "DrawArea.h"
#include "MainWindow.h"
#include "MimeMachine.h"


/// Constructor
ScrollView::ScrollView(QWidget* parent, const char* name)
    :QScrollArea(parent)
{
  drawArea=new DrawArea(this,(MainWindow*)parent,"");
  this->setWidget(drawArea);
  main=(MainWindow*)parent;

  setWidgetResizable(false);
  //setWidgetResizable(true);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    if(widget()!=NULL)
    widget()->resize(CONT_WIDTH, CONT_HEIGHT);
  parent->resize(CONT_WIDTH+40, CONT_HEIGHT+80);

  connect(drawArea,SIGNAL(scrollWidget(int,int)),this,SLOT(scrollContents(int,int)));
  connect(drawArea,SIGNAL(scrollWidgetTo(int,int)),this,SLOT(scrollContentsTo(int,int)));

}



/// Scroll view contents by a distance of @param dx, @param dy
void ScrollView::scrollContents(int dx,int dy)
{
  horizontalScrollBar()->setValue(horizontalScrollBar()->value()+dx);
  verticalScrollBar()->setValue(verticalScrollBar()->value()+dy);
}

/// Scroll view contents to @param x, @param y
void ScrollView::scrollContentsTo(int x,int y)
{
  horizontalScrollBar()->setValue(x-width()/2);
  verticalScrollBar()->setValue(y-height()/2);
}

/// Updates the background
void ScrollView::updateBackground()
{
  if (main)
  {
    QColor bgcol;
    if (main->project && main->project->machine)
      bgcol.setRgb(255, 255, 255);
    else
      bgcol.setRgb(220, 220, 220);
    setBackgroundColor(bgcol);

    drawArea->updateBackground();
  }
}


void ScrollView::resizeEvent(QResizeEvent*e)
{
  //qDebug("ScrollView::resizeEvent() called");
  updateSize(e);
}


void ScrollView::updateSize(QResizeEvent* e)
{
  double scale;
  int sx,sy;
  int x,y;
  int new_width,new_height;

  /*
  new_width=maximumViewportSize().width();
  new_height=maximumViewportSize().height();

  if(!main->project)
  {
    drawArea->resizeContents(new_width,new_height);
    return;
  }
  if(!main->project->machine)
    return;
  */
  if (!main->project || !main->project->machine)
    return;

  main->project->machine->getCanvasSize(x, y);
  scale = drawArea->getScale();

  sx = (int)((double)x*scale);
  sy = (int)((double)y*scale);

  /*
  new_width=maximumViewportSize().width();
  new_height=maximumViewportSize().height();
  */
  new_width = viewport()->contentsRect().width();
  new_height = viewport()->contentsRect().height();

  if(new_width<=sx)
    new_width=sx;
  if(new_height<=sy)
    new_height=sy;

  //if(new_width!=sy || new_height!=sy || new_width>drawArea->width() || new_height>drawArea->height())
  {
    drawArea->resizeContents(new_width,new_height);
    //main->project->machine->updateCanvasSize(new_width,new_height);
  }
  if (e)
    QScrollArea::resizeEvent(e);


  //qDebug("SV:resizeEvent: "+QString::number(new_width)+" "+QString::number(new_height)+" "+QString::number(sx)+" "+QString::number(sy)+" draw area: "+QString::number(drawArea->width())+" "+QString::number(drawArea->height()));


//  main->project->machine->updateCanvasSize(new_width,new_height,drawArea->getScale());

}



