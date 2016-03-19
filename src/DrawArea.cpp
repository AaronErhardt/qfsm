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
#include <QApplication>

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
#include "MimeMachine.h"


DrawArea::DrawArea(QWidget*parent,MainWindow*m,const char*name) :QWidget(parent)
{
  main = m;
  setBackgroundColor(m->palette().window().color());
  oldCursor = QCursor(Qt::ArrowCursor);

  setMouseTracking(TRUE);

  resetState();

  zoom = new Zoom;
  selection = new Selection(this);
  draw = new Draw( this, main->getOptions());
  grid = new Grid(main->getOptions());
  tooltip = new ToolTipSV(this);

  connect(this, SIGNAL(setMode(int)), main, SLOT(setMode(int)) );
  connect(selection, SIGNAL(updateAll()), main, SLOT(updateAll()));
}




/// Resets all variables storing the state of the view
void DrawArea::resetState()
{
  left_down = FALSE;
  middle_down = FALSE;
  drag = FALSE;
  drag_middle = FALSE;
  lastStateClicked=NULL;
  lastTransitionClicked=NULL;
  lastTransitionDragged=NULL;
  lastTransitionControl=0;
  lastObjectRClicked=NULL;
  dragTransition=NULL;
  dragITransition=NULL;
  dragRect=FALSE;
  onSelection=FALSE;
  dragMultiple=FALSE;
  savedState.tlist.clear();
  //  savedState.tlist.setAutoDelete(FALSE);
}

/// Resets the scrollview (by reseting the state and deselecting all objects)
void DrawArea::reset()
{
  resetState();
  updateBackground();
  selection->deselectAll(main->project->machine);
}

/// Updates the background
void DrawArea::updateBackground()
{
  if (main)
  {
    QColor bgcol;
    if (main->project && main->project->machine)
      bgcol.setRgb(255, 255, 255);
    else
      bgcol.setRgb(220, 220, 220);
    setBackgroundColor(bgcol);
  }
}

/// Destructor
DrawArea::~DrawArea()
{
  delete zoom;
  delete selection;
  delete draw;
  delete grid;
  delete tooltip;
}

/**
 * Returns the context object (when right clicked on an object)
 *
 * @param type Type of the object returned (see #ObjectType)
 * @returns The object
 */
GObject* DrawArea::getContextObject(int& type)
{
  return selection->getContextObject(type);
}


/**
 * Updates canvas size.
 * Updates the size of the scroll view according to the canvas size stored in
 * the machine
 */
/*
void DrawArea::updateCanvasSize()
{
*/
  // not used anymore
  // do not resize draw area according to content (machine) but
  // only when parent (scrollview) changes size
  /*
  Project* p=main->project;
  if (!p)
    return;

  int x, y;
  double sx, sy;
  double scale;

  p->machine->getCanvasSize(x, y);
  sx = (double)x;
  sy = (double)y;

  scale = zoom->getScale();

  resize(int(sx*scale), int(sy*scale));
  qDebug("new size: "+QString::number(width())+" "+QString::number(height()));
  */
//}


/// Invoked when user presses a mouse button
void DrawArea::mousePressEvent(QMouseEvent* e)
{
//  MainWindow* main = (MainWindow*)parent();
  Machine* m=NULL;
  QPoint p, offset; //, pcont;
  double scale;
  double mx, my, destx, desty;
  double mousex, mousey;
  scale = zoom->getScale();
  p = e->pos();
  if (e->button()==Qt::MidButton && (left_down || drag))
    return;
  else if (e->button()==Qt::RightButton && (left_down || drag || middle_down ||
                                            drag_middle))
    return;

  {
    dragStartX=(double)p.x()/scale;
    dragStartY=(double)p.y()/scale;
    if (main->getOptions()->getViewGrid())
    {
      grid->getPoint(dragStartX, dragStartY, mousex, mousey);
      dragStartgX = mousex;
      dragStartgY = mousey;
    }
    else
    {
      mousex = (double)p.x()/scale;
      mousey = (double)p.y()/scale;
      dragStartgX = dragStartX;
      dragStartgY = dragStartY;
    }
  }
  lastMovePosX = mousex;
  lastMovePosY = mousey;
  lastMousePosX = (double)p.x()/scale;
  lastMousePosY = (double)p.y()/scale;
//  offset = QPoint(contentsX(), contentsY());
//  offset = mapTo(widget(),QPoint(0,0));
  offset=QPoint(0,0);

  if (!main->project)
    return;

  m = main->project->machine;
  if (!m)
    return;


  switch (e->button())
  {
  case Qt::LeftButton:
    resetContext();
    lastLClicked = p;
    switch(main->getMode())
    {
    case DocStatus::Select:
      if (!drag_middle)
      {
        left_down=TRUE;
        firstTransitionDraw=TRUE;

        onSelection=selection->onSelection(m, p, scale);

        lastTransitionControl = selection->selectControl(m, p, scale,
                                                         lastTransitionClicked);

        if (dragMultiple)
        {
          //	    lastTransitionControl=0;

          dragTransition=NULL;

          if (onSelection) //selection->onSelection(p, scale))
          {
            selection->updateBoundingRect(selectionRect,
                                          m->getPhantomState());
            //	      onSelection=TRUE;
          }
          else if (lastTransitionControl==0)
          {
            if (!main->shiftPressed())
              dragMultiple=FALSE;
            //	      onSelection=FALSE;
          }
          drawControlLines=FALSE;
        }
        else if (main->shiftPressed())	// adding selection if
        {					// zero or one object is selected
          dragMultiple=TRUE;
          onSelection=FALSE;
        }
        if (!dragMultiple && !main->shiftPressed())	// select single
        {						// state or transition
          int type=NoT;
          GObject* obj=NULL;
          if (!lastTransitionControl)
            obj = selection->select(this, m, p, scale,
                                    type);

          if (type==StateT)
          {
            lastStateClicked = (GState*)obj;
            selection->updateBoundingRect(selectionRect,
                                          m->getPhantomState());
            //selectionRect = lastStateClicked->getMaxRect();
          }
          else if (type==TransitionT)
            lastTransitionClicked = (GTransition*)obj;
          else if (type==ITransitionT)
          {
            lastStateClicked = NULL;
          }
          else
            lastStateClicked = NULL;

          drawControlLines=TRUE;
        }
        else
          lastStateClicked=NULL;

        // Save position of control points
        if (lastTransitionClicked)
        {
          /*
        if (lastTransitionControl==1)
        {
        */
          lastTransitionClicked->getCPoint1(lastMovePosCont1X,
                                            lastMovePosCont1Y);
          /*
        }
        else if (lastTransitionControl==4)
        {
        */
          lastTransitionClicked->getCPoint2(lastMovePosCont2X,
                                            lastMovePosCont2Y);
          //}
          lastTransitionClicked->getPos(lastStartPointX, lastStartPointY);
          lastTransitionClicked->getEndPos(lastEndPointX, lastEndPointY);
          lastTransitionClicked->getCPoint1(lastCont1X, lastCont1Y);
          lastTransitionClicked->getCPoint2(lastCont2X, lastCont2Y);
        }
      }
      break;
    case DocStatus::Pan:
      left_down=TRUE;
      break;
    case DocStatus::NewState:
      if (!drag_middle)
      {
        if (main->statemanager->addState(mousex, mousey))
          main->project->setChanged();
      }
      break;
    case DocStatus::NewTransition:
      if (!drag_middle)
      {
        lastStateClicked = m->getState(lastLClicked, scale);
        if (lastStateClicked)
        {
          lastStateClicked->getPos(mx, my);

          GState::circleEdge(mx, my, lastStateClicked->getRadius(),
                             p.x()/scale, p.y()/scale, destx, desty);

          lastTransitionDragged = new GTransition(lastStateClicked, NULL,
                                                  NULL, destx, desty, destx, desty, "");
          firstTransitionDraw=TRUE;
        }

        if (lastStateClicked)
          left_down=TRUE;
      }
      break;
    case DocStatus::Zooming:
      int spx, spy;
      QPoint sp;
      if (main->controlPressed())
      {
        zoom->zoom(this, p, FALSE);
        //emit scrollWidget(int(p.x()*zoom->getScale()-width()/2), int(p.y()*zoom->getScale()-height()/2));
        spx = int((p.x())/ZOOM_FACTOR);
	spy = int((p.y())/ZOOM_FACTOR);
      }
      else
      {
        zoom->zoom(this, p, TRUE);
        //emit scrollWidget(int(p.x()*zoom->getScale()-width()/2), int(p.y()*zoom->getScale()-height()/2));
        spx = int((p.x())*ZOOM_FACTOR);
	spy = int((p.y())*ZOOM_FACTOR);
	//sp = mapToParent(p);
      }
      emit scrollWidgetTo(spx, spy);
      setUpdatesEnabled(TRUE);
      repaint();
      break;
    }
    //      main->updateAll();
    break;
  case Qt::RightButton:
    switch(main->getMode())
    {
    case DocStatus::Simulating:
      break;
    default:
      if (!drag && !drag_middle)
        showContext(p);
      break;
    }
    break;
  case Qt::MidButton:
    if (!(left_down || drag))
    {
      middle_down=TRUE;
      resetContext();
      oldCursor = cursor();
      setCursor(Qt::SizeAllCursor);
    }
    break;
  default:
    break;
  }
}


/// Invoked when user moves the mouse.
void DrawArea::mouseMoveEvent(QMouseEvent* e)
{
  //  time_t t1 = clock();
//  MainWindow* main = NULL;
  Machine* m = NULL;

 // main = (MainWindow*)parent();
  if (main && main->project)
    m = main->project->machine;
  QPoint p;
  double scale = zoom->getScale();
  p = e->pos();
  if (main->project)
    main->getStatusBar()->setPosition(p.x()/scale, p.y()/scale);
  else
    main->getStatusBar()->setPosition(-1, -1);
  main->getStatusBar()->repaint();
  double mousex, mousey;
  if (main->getOptions()->getViewGrid())
    grid->getPoint(p.x()/scale, p.y()/scale, mousex, mousey);
  else
  {
    mousex = (double)p.x()/scale;
    mousey = (double)p.y()/scale;
  }
  QRect udrect;  // rectangle to update when calling repaintContents()
  udrect = QRect(0, 0, width(), height());

  switch (main->getMode())
  {
  case DocStatus::Select:

    if (left_down)
    {
      drag=TRUE;
      left_down=FALSE;
      if (lastTransitionControl==11 || lastTransitionControl==14)
      {
        dragITransition = new GITransition(*m->getInitialTransition());
      }
      else if (lastTransitionClicked && lastTransitionControl)
      {
        dragTransition = new GTransition(*lastTransitionClicked);
      }
      else if (lastStateClicked)
      {
        if (selection->countStates()==1) // && selection->countTransitions()==0)
        {
          double xpos, ypos, xlock, ylock, movex, movey;
          GState* s;
          s = selection->getSList().front();
          s->getPos(xpos, ypos);
          grid->getPoint(xpos, ypos, xlock, ylock);


          if (fabs(xpos-xlock) > 1e-1 || fabs(ypos-ylock) > 1e-1)
          {
            movex = xlock-xpos; // + (mousex-lastMovePosX);
            movey = ylock-ypos; // + (mousey-lastMovePosY);
            lastMovePosX -= movex;
            lastMovePosY -= movey;
            dragStartgX -= movex;
            dragStartgY -= movey;
          }
        }

        savedState.copyAttributes(lastStateClicked);
        savedState.copyTransitions(lastStateClicked, TRUE);
        if (m->getInitialTransition())
          savedITrans = *m->getInitialTransition();
        onSelection=selection->onSelection(m, p, scale);
      }
    }
    else if (drag && m)
    {


      //      QPainter pa(viewport());
      double sx=0, sy=0, edgex, edgey;
      double xdiff = mousex-lastMovePosX;
      double ydiff = mousey-lastMovePosY;
      double loopendx, loopendy, loopstartx, loopstarty;
      double c1x, c1y, c2x, c2y;
      double iedgex, iedgey;
      GState* sover;
      QRect window;




      if (lastTransitionControl)
      {
        sover = main->project->machine->getState(p, scale);
        int cont = lastTransitionControl;

        if (!dragITransition)     // draw normal Transition
        {

          lastTransitionClicked->setDragged(TRUE);
        }
        else              // draw initial transition
        {
          sover = m->getInitialState();
          sover->getPos(sx, sy);
          GState::circleEdge(sx, sy, sover->getRadius(), mousex, mousey,
                             iedgex, iedgey);
          m->getInitialTransition()->setDragged(TRUE);
        }

        firstTransitionDraw=FALSE;

        if (sover)
        {
          sover->getPos(sx, sy);

          // if we have a loop we don't want to snap to the grid
          if ((cont==1 && dragTransition->getEnd()==sover) ||
              (cont==4 && dragTransition->getStart()==sover))
          {
            GState::circleEdge(sx, sy, sover->getRadius(),
                               p.x()/scale, p.y()/scale, edgex, edgey);
          }
          else // snap to the grid (if it's on)
          {
            GState::circleEdge(sx, sy, sover->getRadius(), mousex, mousey,
                               edgex, edgey);
          }
        }

        if (cont==1)
        {
          if (!dragTransition->isStraight())
          {
            double diffcx, diffcy;
            double contposx, contposy;

            diffcx = lastMovePosCont1X - lastLClicked.x()/scale;
            diffcy = lastMovePosCont1Y - lastLClicked.y()/scale;
            if (sover)
            {
              contposx = edgex;
              contposy = edgey;
            }
            else
            {
              contposx = mousex;
              contposy = mousey;
            }
            dragTransition->setCPoint1(contposx + diffcx,
                                       contposy + diffcy);
          }
          if (!sover)             // trans. not on state
          {
            dragTransition->setStartPos(mousex, mousey);
            drawControlLines=FALSE;
          }
          else if (dragTransition->getEnd()!=sover ||
                   !dragTransition->isStraight())    // trans. on state but no loop
          {
            dragTransition->setStartPos(edgex, edgey);
            drawControlLines=FALSE;
          }
          else                // loop
          {
            if (dragTransition->getEnd()==sover)
              drawControlLines=TRUE;

            GState::circleEdge(sx, sy, sover->getRadius(),
                               p.x()/scale, p.y()/scale, loopendx, loopendy, 40);
            sover->calcLoop(sx, sy, sover->getRadius(), p.x()/scale,
                            p.y()/scale, c1x, c1y, c2x, c2y);

            dragTransition->setStartPos(edgex, edgey);
            dragTransition->setEndPos(loopendx, loopendy);
            dragTransition->setCPoint1(c1x, c1y);
            dragTransition->setCPoint2(c2x, c2y);
          }
        }
        else if (cont==2)
          dragTransition->moveCPoint1(xdiff, ydiff);
        else if (cont==3)
          dragTransition->moveCPoint2(xdiff, ydiff);
        else if (cont==4)
        {
          if (!dragTransition->isStraight())
          {
            double diffcx, diffcy;
            double contposx, contposy;

            diffcx = lastMovePosCont2X - lastLClicked.x()/scale;
            diffcy = lastMovePosCont2Y - lastLClicked.y()/scale;

            if (sover)
            {
              contposx = edgex;
              contposy = edgey;
            }
            else
            {
              contposx = mousex;
              contposy = mousey;
            }
            dragTransition->setCPoint2(contposx + diffcx,
                                       contposy + diffcy);
          }
          if (!sover)
          {
            dragTransition->setEndPos(mousex, mousey);
            drawControlLines=FALSE;
          }
          else if (dragTransition->getStart()!=sover || !dragTransition->isStraight())
          {
            dragTransition->setEndPos(edgex, edgey);
            drawControlLines=FALSE;
          }
          else
          {
            if (dragTransition->getStart()==sover)
              drawControlLines=TRUE;

            GState::circleEdge(sx, sy, sover->getRadius(),
                               p.x()/scale, p.y()/scale, loopstartx, loopstarty, -40);
            sover->calcLoop(sx, sy, sover->getRadius(), loopstartx,
                            loopstarty, c1x, c1y, c2x, c2y);

            dragTransition->setStartPos(loopstartx, loopstarty);
            dragTransition->setEndPos(edgex, edgey);
            dragTransition->setCPoint1(c1x, c1y);
            dragTransition->setCPoint2(c2x, c2y);
          }

        }
        else if (cont==11)        // start of initial trans.
        {
          dragITransition->setPos(mousex, mousey);
        }
        else if (cont==14)        // end of initial trans.
        {
          dragITransition->setEndPos(iedgex, iedgey);
        }


        double stx, sty, enx, eny;
        double co1x, co1y, co2x, co2y;
        QRect rtmp, last1, last2;
        if (!dragITransition)
        {
          dragTransition->getPos(stx, sty);
          dragTransition->getEndPos(enx, eny);
          dragTransition->getCPoint1(co1x, co1y);
          dragTransition->getCPoint2(co2x, co2y);
          udrect.setCoords((int)stx, (int)sty, (int)enx, (int)eny);
          rtmp.setCoords((int)co1x, (int)co1y, (int)co2x, (int)co2y);
          udrect = udrect.united(rtmp);
          last1.setCoords((int)lastStartPointX, (int)lastStartPointY, (int)lastEndPointX, (int)lastEndPointY);
          last2.setCoords((int)lastCont1X, (int)lastCont1Y, (int)lastCont2X, (int)lastCont2Y);

          udrect = udrect.united(last1);
          udrect = udrect.united(last2);
        }
        else
        {
          dragITransition->getPos(stx, sty);
          dragITransition->getEndPos(enx, eny);
          udrect.setCoords((int)stx, (int)sty, (int)enx, (int)eny);
          last1.setCoords((int)lastStartPointX, (int)lastStartPointY, (int)lastEndPointX, (int)lastEndPointY);
          udrect = udrect.united(last1);
          if (!lastITextRect.isNull())
          {
            udrect = udrect.united(lastITextRect);
            lastITextRect = QRect();
          }
        }
        udrect.normalize();
        udrect.adjust(-2-2*CPOINT_SIZE, -2-2*CPOINT_SIZE, +4+2*CPOINT_SIZE, +4+2*CPOINT_SIZE);

        /*        if (!dragITransition)     // draw normal transition
        {
          draw->drawTransition(m, dragTransition, &pa, contentsX(),
                               contentsY(), scale,
                                         TRUE, TRUE, drawControlLines);
        }
        else              // draw initial transition
        {
          if (m->getDrawITrans())
            draw->drawInitialTransition(m, dragITransition, &pa, contentsX(),
                                        contentsY(), scale, TRUE, firstTransitionDraw, TRUE);
        }
*/

      }
      else        // draw State being dragged
      {
        //GState* s;

        QList<GState*> l = selection->getSList();
        QListIterator<GState*> i(selection->getSList());

        if (!onSelection)//if (!dragMultiple)  // draw Rectangle for selection
        {
          dragRect=TRUE;

          //      QPen pen(QColor(0,0,0), 1);

          QRect r1;
          r1.setCoords((int)dragStartX, (int)dragStartY, (int)lastMousePosX, (int)lastMousePosY);
          r1 = r1.normalize();

          selectionRect.setCoords(dragStartX, dragStartY, (double)p.x()/scale,
                                  (double)p.y()/scale);
          selectionRect.normalize();

          QRect r2;
          r2.setCoords((int)selectionRect.left(), (int)selectionRect.top(),
                       (int)selectionRect.right(), (int)selectionRect.bottom());

          //      pa.setRasterOp(Qt::NotXorROP);
          /*          pa.setCompositionMode(QPainter::CompositionMode_Xor);
          pa.drawRect(r1);
          pa.drawRect(r2);*/

          udrect = r1.united(r2);
          udrect.adjust(-1, -1, +2, +2);
        }
        else if (onSelection)     // draw Multi-Selection-Rectangle
        {
          double movex, movey;
          QPoint mainPoint;
          //         QPen pen(QColor(0,0,0), 1, Qt::DotLine);

          //      pa.setRasterOp(Qt::NotXorROP);
          /*          pa.setCompositionMode(QPainter::CompositionMode_Xor);
          pa.setPen(pen);

          pa.drawRect(selectionRect.getQRect());
*/
          // selection is a single state. align its center to the grid

          {
            movex = mousex-lastMovePosX;
            movey = mousey-lastMovePosY;
          }

          QRect oldselrect, newselrect;
          oldselrect = selectionRect.getQRect();

          selectionRect.moveBy(movex, movey);

          newselrect = selectionRect.getQRect();
          udrect = oldselrect;
          udrect = udrect.united(newselrect);
          udrect.normalize();
          udrect.adjust(-2, -2, +4, +4);
          //          pa.drawRect(selectionRect.getQRect());
          mainPoint=mapTo(main,p);

          if(mainPoint.x()<0 || mainPoint.y()<0 || mainPoint.x()>main->width() || mainPoint.y()>main->height())
          {

            if(e->modifiers().testFlag(Qt::ControlModifier))
              main->runDragOperation(true);
            else main->runDragOperation(false);
         //   {

              // emulate the mouse release event that has been consumed by the dropEvent
              QMouseEvent *ev=new QMouseEvent(QEvent::MouseButtonRelease,mapFromGlobal(cursor().pos()),Qt::LeftButton,QApplication::mouseButtons(),QApplication::keyboardModifiers());
              QApplication::postEvent(this,ev);
              return;
          //  }
          //  else{

           //   qDebug("Drag operation ignored");
           //   return;
           // }


          }


        }
      }

      lastMovePosX = mousex; //(double)p.x()/scale;
      lastMovePosY = mousey; //(double)p.y()/scale;
      lastMousePosX = (double)p.x()/scale;
      lastMousePosY = (double)p.y()/scale;
      firstTransitionDraw=FALSE;

      udrect.setRect(int(udrect.x()*scale), int(udrect.y()*scale), int(udrect.width()*scale), int(udrect.height()*scale));
      repaint(udrect, false);
    }
    break;
  case DocStatus::Pan:
    if (left_down)
    {
      drag=TRUE;
      left_down=FALSE;
      //dragStartX = (double)p.x()/scale;
      //dragStartY = (double)p.y()/scale;
    }
    else if (drag)
    {
      //scrollContentsBy(int(lastMousePosX*scale-p.x()), int(lastMousePosY*scale-p.y()));
      emit scrollWidget(int(lastMousePosX*scale-p.x()),int(lastMousePosY*scale-p.y()));
    }
    break;
  case DocStatus::NewTransition:
    if (left_down)
    {
      drag=TRUE;
      left_down=FALSE;
    }
    else if (drag)
    {
      //      QPainter pa(viewport());
      double scale = zoom->getScale();
      double dx, dy;
      double c1x, c1y, c2x, c2y;
      GState* sover;
      QRect lastrect, rtmp;

      sover = main->project->machine->getState(p, scale);

      if (lastStateClicked)
      {
        double mx, my, mx2, my2, edgex, edgey, destx, desty;
        lastStateClicked->getPos(mx, my);
        destx = mousex; //p.x()/scale;
        desty = mousey; //p.y()/scale;

        double lastx1, lasty1, lastx2, lasty2;
        double lastc1x, lastc1y, lastc2x, lastc2y;
        lastTransitionDragged->getPos(lastx1, lasty1);
        lastTransitionDragged->getEndPos(lastx2, lasty2);
        lastTransitionDragged->getCPoint1(lastc1x, lastc1y);
        lastTransitionDragged->getCPoint2(lastc2x, lastc2y);
        lastrect.setCoords((int)lastx1, (int)lasty1, (int)lastx2, (int)lasty2);
        rtmp.setCoords((int)lastc1x, (int)lastc1y, (int)lastc2x, (int)lastc2y);
        lastrect = lastrect.united(rtmp);

        // start from state (edgex, edgey)
        if (!sover || sover==lastStateClicked)
        {
          GState::circleEdge(mx, my, lastStateClicked->getRadius(),
                             p.x()/scale, p.y()/scale, edgex, edgey);
        }

        if (sover && sover!=lastStateClicked)
        {
          sover->getPos(mx2, my2);
          GState::circleEdge(mx2, my2, sover->getRadius(),
                             mousex , mousey , destx, desty);
          GState::circleEdge(mx, my, lastStateClicked->getRadius(),
                             mx2, my2, edgex, edgey);
        }

        if (sover==lastStateClicked)
        {
          //      destx = edgex;
          //          desty = edgey;
          GState::circleEdge(mx, my, sover->getRadius(),
                             p.x()/scale, p.y()/scale, destx, desty, 40);
          sover->calcLoop(mx, my, sover->getRadius(), p.x()/scale,
                          p.y()/scale, c1x, c1y, c2x, c2y);
          lastTransitionDragged->setStraight(FALSE);
        }
        else
        {
          lastTransitionDragged->setStraight();

          dx = (destx-edgex);
          dy = (+1)*(desty-edgey);

          c1x = edgex+dx*2/3;
          c1y = edgey+dy*2/3;
          c2x = edgex+dx/3;
          c2y = edgey+dy/3;
        }

        /*        if (!firstTransitionDraw)
        {
          draw->drawTransition(m, lastTransitionDragged, &pa, contentsX(),
                               contentsY(), scale, m->getNumInputs(), m->getNumOutputs(),
                                         TRUE, FALSE);
        }
*/        firstTransitionDraw=FALSE;



          lastTransitionDragged->setPos(edgex, edgey);

          lastTransitionDragged->setCPoint1(c1x, c1y);
          lastTransitionDragged->setCPoint2(c2x, c2y);

          lastTransitionDragged->setEndPos(destx, desty);

          udrect.setCoords((int)edgex, (int)edgey, (int)destx, (int)desty);
          rtmp.setCoords((int)c1x, (int)c1y, (int)c2x, (int)c2y);
          udrect = udrect.united(rtmp);
          udrect = udrect.united(lastrect);
          udrect.normalize();
          udrect.adjust(-15, -15, +30, +30);
          udrect.setRect(int(udrect.x()*scale), int(udrect.y()*scale), int(udrect.width()*scale), int(udrect.height()*scale));

          repaint(udrect, false);

          /*        draw->drawTransition(m, lastTransitionDragged, &pa, contentsX(),
                             contentsY(), scale, m->getNumInputs(), m->getNumOutputs(),
                                       TRUE, FALSE);
*/
        }
    }
  }

  if (dragTransition)
  {
    dragTransition->getPos(lastStartPointX, lastStartPointY);
    dragTransition->getEndPos(lastEndPointX, lastEndPointY);
    dragTransition->getCPoint1(lastCont1X, lastCont1Y);
    dragTransition->getCPoint2(lastCont2X, lastCont2Y);
  }
  else if (dragITransition)
  {
    dragITransition->getPos(lastStartPointX, lastStartPointY);
    dragITransition->getEndPos(lastEndPointX, lastEndPointY);
  }

  /*  switch (main->getMode())
  {
    case DocStatus::Select:
      if (left_down)
      {
  drag=TRUE;
  left_down=FALSE;
  if (lastTransitionControl==11 || lastTransitionControl==14)
  {
    dragITransition = new GITransition(*m->getInitialTransition());
  }
  else if (lastTransitionClicked && lastTransitionControl)
  {
    dragTransition = new GTransition(*lastTransitionClicked);
  }
  else if (lastStateClicked)
  {
      if (selection->countStates()==1) // && selection->countTransitions()==0)
      {
        double xpos, ypos, xlock, ylock, movex, movey;
        GState* s;
        s = selection->getSList().front();
        s->getPos(xpos, ypos);
        grid->getPoint(xpos, ypos, xlock, ylock);

        if (fabs(xpos-xlock) > 1e-1 || fabs(ypos-ylock) > 1e-1)
        {
    movex = xlock-xpos; // + (mousex-lastMovePosX);
    movey = ylock-ypos; // + (mousey-lastMovePosY);
    lastMovePosX -= movex;
    lastMovePosY -= movey;
    dragStartgX -= movex;
    dragStartgY -= movey;
        }
      }

    savedState.copyAttributes(lastStateClicked);
    savedState.copyTransitions(lastStateClicked, TRUE);
    if (m->getInitialTransition())
      savedITrans = *m->getInitialTransition();
    onSelection=selection->onSelection(m, p, scale);
  }
      }
      else if (drag && m)
      {
        repaint();
      }

    QPainter pa(viewport());
  double sx=0, sy=0, edgex, edgey;
  double xdiff = mousex-lastMovePosX;
  double ydiff = mousey-lastMovePosY;
  double loopendx, loopendy, loopstartx, loopstarty;
  double c1x, c1y, c2x, c2y;
  double iedgex, iedgey;
  GState* sover;
        QRect window;

  window = pa.window();
  pa.setViewport(-contentsX(), -contentsY(), int(window.width()*scale),
  int(window.height()*scale));

        if (lastTransitionControl)
  {
          sover = main->project->machine->getState(p, scale);
          int cont = lastTransitionControl;

    if (!dragITransition)		// draw normal Transition
    {
      draw->drawTransition(m, dragTransition, &pa, contentsX(),
        contentsY(), scale,
        TRUE, !firstTransitionDraw, drawControlLines, firstTransitionDraw);
    }
    else				// draw initial transition
    {
      if (m->getDrawITrans())
        draw->drawInitialTransition(m, dragITransition, &pa, contentsX(),
    contentsY(), scale, TRUE, firstTransitionDraw, TRUE);

      sover = m->getInitialState();
      sover->getPos(sx, sy);
      GState::circleEdge(sx, sy, sover->getRadius(), mousex, mousey,
        iedgex, iedgey);
    }

          firstTransitionDraw=FALSE;

    if (sover)
    {
      sover->getPos(sx, sy);

      // if we have a loop we don't want to snap to the grid
      if ((cont==1 && dragTransition->getEnd()==sover) ||
         (cont==4 && dragTransition->getStart()==sover))
      {
        GState::circleEdge(sx, sy, sover->getRadius(),
    p.x()/scale, p.y()/scale, edgex, edgey);
      }
      else // snap to the grid (if it's on)
      {
        GState::circleEdge(sx, sy, sover->getRadius(), mousex, mousey,
    edgex, edgey);
      }
    }

    if (cont==1)
    {
      if (!dragTransition->isStraight())
      {
        double diffcx, diffcy;
        double contposx, contposy;

        diffcx = lastMovePosCont1X - lastLClicked.x()/scale;
        diffcy = lastMovePosCont1Y - lastLClicked.y()/scale;
        if (sover)
              {
                contposx = edgex;
    contposy = edgey;
        }
        else
        {
                contposx = mousex;
    contposy = mousey;
        }
        dragTransition->setCPoint1(contposx + diffcx,
    contposy + diffcy);
      }
      if (!sover)				// trans. not on state
      {
        dragTransition->setStartPos(mousex, mousey);
        drawControlLines=FALSE;
      }
      else if (dragTransition->getEnd()!=sover ||
        !dragTransition->isStraight())	// trans. on state but no loop
      {
        dragTransition->setStartPos(edgex, edgey);
        drawControlLines=FALSE;
      }
      else				// loop
      {
        if (dragTransition->getEnd()==sover)
          drawControlLines=TRUE;

        GState::circleEdge(sx, sy, sover->getRadius(),
         p.x()/scale, p.y()/scale, loopendx, loopendy, 40);
        sover->calcLoop(sx, sy, sover->getRadius(), p.x()/scale,
        p.y()/scale, c1x, c1y, c2x, c2y);

        dragTransition->setStartPos(edgex, edgey);
        dragTransition->setEndPos(loopendx, loopendy);
        dragTransition->setCPoint1(c1x, c1y);
        dragTransition->setCPoint2(c2x, c2y);
      }
    }
    else if (cont==2)
      dragTransition->moveCPoint1(xdiff, ydiff);
    else if (cont==3)
      dragTransition->moveCPoint2(xdiff, ydiff);
    else if (cont==4)
    {
      if (!dragTransition->isStraight())
      {
        double diffcx, diffcy;
        double contposx, contposy;

        diffcx = lastMovePosCont2X - lastLClicked.x()/scale;
        diffcy = lastMovePosCont2Y - lastLClicked.y()/scale;

        if (sover)
              {
                contposx = edgex;
    contposy = edgey;
        }
        else
        {
                contposx = mousex;
    contposy = mousey;
        }
        dragTransition->setCPoint2(contposx + diffcx,
    contposy + diffcy);
      }
      if (!sover)
      {
        dragTransition->setEndPos(mousex, mousey);
        drawControlLines=FALSE;
      }
      else if (dragTransition->getStart()!=sover || !dragTransition->isStraight())
      {
        dragTransition->setEndPos(edgex, edgey);
        drawControlLines=FALSE;
      }
      else
      {
        if (dragTransition->getStart()==sover)
          drawControlLines=TRUE;

        GState::circleEdge(sx, sy, sover->getRadius(),
         p.x()/scale, p.y()/scale, loopstartx, loopstarty, -40);
        sover->calcLoop(sx, sy, sover->getRadius(), loopstartx,
        loopstarty, c1x, c1y, c2x, c2y);

        dragTransition->setStartPos(loopstartx, loopstarty);
        dragTransition->setEndPos(edgex, edgey);
        dragTransition->setCPoint1(c1x, c1y);
        dragTransition->setCPoint2(c2x, c2y);
      }

    }
    else if (cont==11)		// start of initial trans.
    {
      dragITransition->setPos(mousex, mousey);
    }
    else if (cont==14)		// end of initial trans.
    {
      dragITransition->setEndPos(iedgex, iedgey);
    }


    if (!dragITransition)		// draw normal transition
    {
      draw->drawTransition(m, dragTransition, &pa, contentsX(),
        contentsY(), scale,
        TRUE, TRUE, drawControlLines);
          }
    else				// draw initial transition
    {
      if (m->getDrawITrans())
        draw->drawInitialTransition(m, dragITransition, &pa, contentsX(),
    contentsY(), scale, TRUE, firstTransitionDraw, TRUE);
    }


  }
  else		// draw State being dragged
  {
    //GState* s;

    QList<GState*> l = selection->getSList();
    QListIterator<GState*> i(selection->getSList());

     if (!onSelection)//if (!dragMultiple)	// draw Rectangle for selection
    {
      dragRect=TRUE;

      QPen pen(QColor(0,0,0), 1);

      QRect r1;
      r1.setCoords((int)dragStartX, (int)dragStartY, (int)lastMousePosX, (int)lastMousePosY);
      r1 = r1.normalize();

      selectionRect.setCoords(dragStartX, dragStartY, (double)p.x()/scale,
        (double)p.y()/scale);
      selectionRect.normalize();

            QRect r2;
      r2.setCoords((int)selectionRect.left(), (int)selectionRect.top(),
        (int)selectionRect.right(), (int)selectionRect.bottom());

//	    pa.setRasterOp(Qt::NotXorROP);
        pa.setCompositionMode(QPainter::CompositionMode_Xor);
      pa.drawRect(r1);
      pa.drawRect(r2);
    }
          else if (onSelection)		// draw Multi-Selection-Rectangle
    {
      double movex, movey;
            QPen pen(QColor(0,0,0), 1, Qt::DotLine);

//	    pa.setRasterOp(Qt::NotXorROP);
        pa.setCompositionMode(QPainter::CompositionMode_Xor);
      pa.setPen(pen);

      pa.drawRect(selectionRect.getQRect());

      // selection is a single state. align its center to the grid

      {
        movex = mousex-lastMovePosX;
        movey = mousey-lastMovePosY;
      }

            selectionRect.moveBy(movex, movey);
      pa.drawRect(selectionRect.getQRect());

    }
        }

  lastMovePosX = mousex; //(double)p.x()/scale;
  lastMovePosY = mousey; //(double)p.y()/scale;
  lastMousePosX = (double)p.x()/scale;
  lastMousePosY = (double)p.y()/scale;
  firstTransitionDraw=FALSE;
      }
      break;
    case DocStatus::Pan:
      if (left_down)
      {
  drag=TRUE;
  left_down=FALSE;
  //dragStartX = (double)p.x()/scale;
  //dragStartY = (double)p.y()/scale;
      }
      else if (drag)
      {
  scrollBy(int(lastMousePosX*scale-p.x()), int(lastMousePosY*scale-p.y()));
      }
      break;
    case DocStatus::NewTransition:
      if (left_down)
      {
  drag=TRUE;
  left_down=FALSE;
      }
      else if (drag)
      {
  QPainter pa(viewport());
  double scale = zoom->getScale();
  double dx, dy;
  double c1x, c1y, c2x, c2y;
  GState* sover;

        sover = main->project->machine->getState(p, scale);

  if (lastStateClicked)
  {
    double mx, my, mx2, my2, edgex, edgey, destx, desty;
    lastStateClicked->getPos(mx, my);
    destx = mousex; //p.x()/scale;
    desty = mousey; //p.y()/scale;

    // start from state (edgex, edgey)
    if (!sover || sover==lastStateClicked)
    {
      GState::circleEdge(mx, my, lastStateClicked->getRadius(),
        p.x()/scale, p.y()/scale, edgex, edgey);
    }

    if (sover && sover!=lastStateClicked)
    {
      sover->getPos(mx2, my2);
      GState::circleEdge(mx2, my2, sover->getRadius(),
        mousex , mousey , destx, desty);
      GState::circleEdge(mx, my, lastStateClicked->getRadius(),
        mx2, my2, edgex, edgey);
    }

    if (sover==lastStateClicked)
    {
//	    destx = edgex;
//          desty = edgey;
      GState::circleEdge(mx, my, sover->getRadius(),
       p.x()/scale, p.y()/scale, destx, desty, 40);
      sover->calcLoop(mx, my, sover->getRadius(), p.x()/scale,
      p.y()/scale, c1x, c1y, c2x, c2y);
      lastTransitionDragged->setStraight(FALSE);
    }
          else
    {
      lastTransitionDragged->setStraight();

      dx = (destx-edgex);
      dy = (+1)*(desty-edgey);

      c1x = edgex+dx*2/3;
      c1y = edgey+dy*2/3;
      c2x = edgex+dx/3;
      c2y = edgey+dy/3;
    }

    if (!firstTransitionDraw)
    {
      draw->drawTransition(m, lastTransitionDragged, &pa, contentsX(),
        contentsY(), scale, m->getNumInputs(), m->getNumOutputs(),
        TRUE, FALSE);
          }
    firstTransitionDraw=FALSE;

    lastTransitionDragged->setPos(edgex, edgey);

          lastTransitionDragged->setCPoint1(c1x, c1y);
          lastTransitionDragged->setCPoint2(c2x, c2y);

    lastTransitionDragged->setEndPos(destx, desty);

    draw->drawTransition(m, lastTransitionDragged, &pa, contentsX(),
      contentsY(), scale, m->getNumInputs(), m->getNumOutputs(),
      TRUE, FALSE);

        }
      }
  }
  */

  if (middle_down)
  {
    middle_down = FALSE;
    drag_middle = TRUE;
    //dragStartX = (double)p.x()/scale;
    //dragStartY = (double)p.y()/scale;
  }
  else if (drag_middle)
  {
    //scrollContentsBy(int(lastMousePosX*scale-p.x()), int(lastMousePosY*scale-p.y()));
    emit scrollWidget(int(lastMousePosX*scale-p.x()), int(lastMousePosY*scale-p.y()));
  }
}


/// Invoked when user releases a mouse button.
void DrawArea::mouseReleaseEvent(QMouseEvent* e)
{


 // MainWindow* main = (MainWindow*)parent();
  Project* project = main->project;
  GState* s;
  Machine* m;
  double scale = zoom->getScale();
  double mousex, mousey;
  //  double mx, my, edgex, edgey, mx2, my2, edgex2, edgey2;
  QPoint p;
  p = e->pos();

  if (main->getOptions()->getViewGrid())
    grid->getPoint(p.x()/scale, p.y()/scale, mousex, mousey);
  else
  {
    mousex = (double)p.x()/scale;
    mousey = (double)p.y()/scale;
  }

  if (!project)
    return;

  m = project->machine;
  if (!m)
    return;


  switch (e->button())
  {
  case Qt::LeftButton:
    left_down=FALSE;

    switch (main->getMode())
    {
        case DocStatus::Select:
      if (drag)
      {
        drag=FALSE;
        GState* sover;
        sover = main->project->machine->getState(p, scale);

        if (dragTransition)
        {

          GState* stmp;
          if (lastTransitionControl==1)
          {
            stmp = (GState*)lastTransitionClicked->getStart();
            if (stmp)			// clear old starting state
            {
              stmp->tlist.removeAll(lastTransitionClicked);
              dragTransition->setStart(NULL);
            }
            if (sover)			// append transition to state
            {
              sover->tlist.append(lastTransitionClicked);
              dragTransition->setStart(sover);
            }
            else				// append trans.to phantom state
            {
              GState* ph;
              ph = main->project->machine->getPhantomState();
              ph->tlist.append(lastTransitionClicked);
              dragTransition->setStart(ph);
            }
          }
          else if (lastTransitionControl==4)
          {
            stmp = (GState*)lastTransitionClicked->getEnd();
            if (stmp)
            {
              stmp->removeTransitionEnd(lastTransitionClicked);
              dragTransition->setEnd(NULL);
            }
            dragTransition->setEnd(sover);
            if (sover)
              sover->reflist.append(lastTransitionClicked);
          }
          lastTransitionClicked->setDragged(FALSE);

          main->project->getUndoBuffer()->changeTransition(
              lastTransitionClicked);

          *lastTransitionClicked = *dragTransition;

          delete dragTransition;
          emit updateCanvasSize(p.x()+100, p.y()+100, scale);
          dragTransition=NULL;

          main->project->setChanged();
        }
        else if (dragITransition)		// initial trans. dragged
        {
          m->getInitialTransition()->setDragged(FALSE);

          main->project->getUndoBuffer()->changeInitialTransition(m->getInitialTransition());

          *m->getInitialTransition() = *dragITransition;

          delete dragITransition;
          emit updateCanvasSize(p.x()+100, p.y()+100, scale);
          dragITransition=NULL;
          main->project->setChanged();
        }
        else if (dragRect)
        {
          selectionRect.normalize();
          if (selection->selectRect(main->project->machine, selectionRect,
                                    main->shiftPressed()))
            dragMultiple=TRUE;
        }
        else if (/*dragMultiple &&*/ onSelection) // move /*multiple*/ selection
        {
          double movebyx, movebyy;
          movebyx = mousex - dragStartgX;
          movebyy = mousey - dragStartgY;

          selection->move(movebyx, movebyy, this, main->project->machine);

          main->project->getUndoBuffer()->moveMultiple(
              &selection->getSList(), &selection->getTList(),
              movebyx, movebyy);

          emit updateCanvasSize((int)selectionRect.right()+100,
                                (int)selectionRect.bottom()+100, scale);
          main->project->setChanged();
        }
        /*
            else if (lastStateClicked)
            {
            project->getUndoBuffer()->changeState(&savedState,
            lastStateClicked, &savedITrans);
            main->project->setChanged();

            double x, y;
            int radius;
            lastStateClicked->getPos(x, y);
            radius = lastStateClicked->getRadius();
            emit updateCanvasSize(int(x+radius+100), int(y+radius+100),scale);
//	      if (!onSelection)
//	        main->updateAll();
          }
        */

        dragRect=FALSE;
        //viewport()->repaint();
        repaint(false);
      }
      else if (main->shiftPressed())
      {
        selection->selectAdd(this, main->project->machine, p, scale);
        dragMultiple=TRUE;
        //	    main->updateAll();
      }
      else
      {

        dragMultiple=FALSE;
        //	    selection->deselectAll(main->project->machine);
        //	    viewport()->repaint();
        //	    if (!onSelection)
        //	      main->updateAll();
      }

      //          left_down=FALSE;
      //          drag=FALSE;
      break;
        case DocStatus::Pan:
      if (drag)
        drag=FALSE;
      break;
        case DocStatus::NewTransition:
      if (drag)
      {
        drag=FALSE;
        s = main->project->machine->getState(e->pos(), scale);
        if (lastStateClicked && s)
        {
          double sx, sy, ex, ey, c1x, c1y, c2x, c2y;
          /*
              lastStateClicked->getPos(mx, my);
              s->getPos(mx2, my2);
              mousex = p.x()/scale;
              mousey = p.y()/scale;

              GState::circleEdge(mx, my, lastStateClicked->getRadius(),
              p.x()/scale, p.y()/scale, edgex, edgey);
              GState::circleEdge(mx2, my2, s->getRadius(),
              mx, my, edgex2, edgey2);
          */
          lastTransitionDragged->getPos(sx, sy);
          lastTransitionDragged->getEndPos(ex, ey);
          lastTransitionDragged->getCPoint1(c1x, c1y);
          lastTransitionDragged->getCPoint2(c2x, c2y);

          if (main->transmanager->addTransition(lastStateClicked, s,
                                                main->project->machine->getNumInputs(),
                                                main->project->machine->getNumOutputs(),
                                                sx, sy, ex, ey, c1x, c1y, c2x, c2y))
            main->project->setChanged();

        } delete lastTransitionDragged;
        lastTransitionDragged=NULL;
        //viewport()->repaint();
        repaint(false);
      }
      //	  left_down=FALSE;
      //	  drag=FALSE;
      break;
    }
    break;
  case Qt::MidButton:
    middle_down = FALSE;
    drag_middle = FALSE;
    setCursor(oldCursor);
    break;
  default:
    break;
  }
  main->updateAll();

}



/// Invoked when users double clicks with the mouse.
void DrawArea::mouseDoubleClickEvent(QMouseEvent* e)
{
//  MainWindow* main = (MainWindow*)parent();
  Project* project = main->project;
  Machine* m;
  double scale = zoom->getScale();
  QPoint p;
  int type;
  GObject* obj;
  p = e->pos();

  if (!project)
    return;

  m = project->machine;
  if (!m)
    return;

  switch (e->button())
  {
  case Qt::LeftButton:
    switch(main->getMode())
    {
    case DocStatus::Select:
      obj = m->getObject(p, scale, type);
      switch (type)
      {
      case StateT:
        main->statemanager->editState((GState*)obj);
        break;
      case TransitionT:
        main->transmanager->editTransition(m, (GTransition*)obj);
        break;
      }
      break;
        default:
      break;
    }
    break;
      default:
    break;
  }
}

void DrawArea::escapePressed()
{
 // MainWindow* main = NULL;
  Machine* m = NULL;

//  main = (MainWindow*)parent();
  if (main && main->project)
    m = main->project->machine;

  switch (main->getMode())
  {
  case DocStatus::Select:
    if (drag)
    {
      drag=FALSE;

      if (dragTransition)
      {
        lastTransitionClicked->setDragged(FALSE);
        delete dragTransition;
        dragTransition=NULL;
      }
      else if (dragITransition)		// initial trans. dragged
      {
        if (m)
          m->getInitialTransition()->setDragged(FALSE);
        delete dragITransition;
        dragITransition=NULL;
      }
      else if (dragRect)
      {
      }
      else if (/*dragMultiple &&*/ onSelection) // move /*multiple*/ selection
        dragRect=FALSE;
      //viewport()->repaint();
      repaint(false);
    }
    dragMultiple=FALSE;
    break;
  case DocStatus::Pan:
    if (drag)
      drag=FALSE;
    break;
  case DocStatus::NewTransition:
    if (drag)
    {
      drag=FALSE;
      delete lastTransitionDragged;
      lastTransitionDragged=NULL;
      //viewport()->repaint();
      repaint(false);
    }
    break;
  }

  if (drag_middle)
  {
    drag_middle = FALSE;
    setCursor(oldCursor);
  }
}

/// Resizes the contents widget of the scoll area
void DrawArea::resizeContents(int x,int y, bool allow_smaller/*=true*/)
{
  int w, h;
  if (allow_smaller)
  {
    w = x;
    h = y;
  }
  else
  {
    w = std::max(x, width());
    h = std::max(y, height());
  }
  resize(w,h);

  //qDebug("inside DrawArea: resize contents: "+QString::number(x)+" "+QString::number(y) + "  w " + QString::number(width()) + " h " + QString::number(height()));
}

/// Invoked when viewport needs to be repainted
void DrawArea::paintEvent(QPaintEvent* pe)
{
  QRect r;
  int contx, conty;
  double scale;
  QRect itextrect;
  //QPoint offset = mapTo(widget(),QPoint(0,0));
  QPoint offset(0,0);

//  MainWindow* main = (MainWindow*)parent();
  Options* opt = main->getOptions();

  r = pe->rect();
  Machine* m=NULL;
  if (main->project)
    m = main->project->machine;

  if (m)
  {
    QPainter pa(this);
    pa.setBrush(Qt::NoBrush);
    pa.setRenderHint(QPainter::Antialiasing);

    scale = zoom->getScale();
    QList<GState*> l = selection->getSList();
    //    QListIterator<GState> i(selection->getSList());
    contx = offset.x();
    conty = offset.y();
    scale = zoom->getScale();

    if (opt->getViewGrid() && zoom->getScale()*opt->getGridSize()>4 )
      draw->drawGrid(grid, &pa, contx, conty, scale);
    draw->drawStates(m, &pa, contx, conty, scale);
    draw->drawTransitions(m, &pa, contx, conty, scale);
    if (m->getDrawITrans())
    {
      draw->drawInitialTransition(m, m->getInitialTransition(), &pa, contx, conty,
                                  scale, itextrect, FALSE);
      lastITextRect = itextrect;
    }

    if (drag)
    {
      QRect window = pa.window();

      pa.setViewport(-contx, -conty, int(window.width()*scale), int(window.height()*scale));

      if (main->getMode()==DocStatus::NewTransition)	// draw new Transition
      {
        offset = QPoint(0,0);
        draw->drawTransition(m, lastTransitionDragged, &pa, offset.x(),
                             offset.y(), scale, m->getNumInputs(), m->getNumOutputs(),
                             FALSE, FALSE);
      }
      //      else if (main->getMode()==DocStatus::Select) // BUG FIX
      else if (lastTransitionControl && main->getMode()==DocStatus::Select)
      {						// draw Trans. being dragged
        offset = QPoint(0,0);
        if (!dragITransition)     // draw normal Transition
        {

          draw->drawTransition(m, dragTransition, &pa, offset.x(),
                               offset.y(), scale,/* m->getNumInputs(), m->getNumOutputs(),*/
                               FALSE, TRUE, drawControlLines);
        }
        else
        {
          draw->drawInitialTransition(m, dragITransition, &pa, offset.x(),
                                      offset.y(), scale,/* m->getNumInputs(), m->getNumOutputs(),*/
                                      itextrect, TRUE, TRUE, TRUE);
        }
      }
      else if (l.isEmpty())		// draw selection rect.
      {
        QRect r2;
        QPen pen(QColor(0,0,0), 1);
        pa.setPen(pen);
        pa.setBrush(Qt::NoBrush);
        r2.setCoords((int)selectionRect.left(), (int)selectionRect.top(),
                     (int)selectionRect.right(), (int)selectionRect.bottom());
        pa.drawRect(r2);
      }
      else if (onSelection)		// draw multi-selection rect.
      {
        QPen pen(QColor(0,0,0), 1, Qt::DotLine);
        pa.setPen(pen);
        pa.setBrush(Qt::NoBrush);
        pa.drawRect(selectionRect.getQRect());
      }
    }
  }
}



/**
 * Draw a transition.
 * @param t transition to draw.
 * @param clear if TRUE it is the first transition in a sequence (draging)
 *   otherwise it is not.
 */
void DrawArea::drawTransition(GTransition* t, bool clear/*=FALSE*/)
{
  QPainter pa(this);
  QPoint offset = QPoint(0,0);

//  MainWindow* main = NULL;
//  main = (MainWindow*)parent();
  Machine* m=NULL;

  if (main && main->project)
    m = main->project->machine;
  if (!m)
    return;

  int cx, cy;
  double scale;

  cx = offset.x();
  cy = offset.y();
  scale = zoom->getScale();

  firstTransitionDraw=clear;
  draw->drawTransition(m, t, &pa, cx, cy, scale, /*m->getNumInputs(),
    m->getNumOutputs(),*/ TRUE, FALSE, FALSE, firstTransitionDraw);
  firstTransitionDraw=FALSE;
}

/**
 * Draw initial transition.
 * @param t transition to draw.
 * @param clear if TRUE it is the first transition in a sequence (draging)
 *   otherwise it is not.
 */
void DrawArea::drawInitialTransition(GITransition* t, bool clear/*=FALSE*/)
{
  QPainter pa(this);
  QPoint offset(0,0);

 // MainWindow* main = NULL;
//  main = (MainWindow*)parent();
  Machine* m=NULL;
  QRect itextrect;

  if (main && main->project)
    m = main->project->machine;
  if (!m)
    return;

  if (!m->getDrawITrans())
    return;

  int cx, cy;
  double scale;

  cx = offset.x();
  cy = offset.y();
  scale = zoom->getScale();

  firstTransitionDraw=clear;
  draw->drawInitialTransition(m, t, &pa, cx, cy, scale, itextrect, TRUE,
                              firstTransitionDraw, TRUE);
  firstTransitionDraw=FALSE;
}




/// Shows the context menu for point @a point
void DrawArea::showContext(QPoint point)
{
  Project* p;
  Machine* m;
  GObject* obj;
  int otype;

  p = main->project;
  if (!p)
    return;
  m = p->machine;
  if (!m)
    return;

  obj = m->getObject(point, zoom->getScale(), otype);
  if (obj && !obj->isSelected())
  {
    selection->deselectAll(m);
    switch (otype)
    {
    case StateT:
      selection->select((GState*)obj);
      break;
    case TransitionT:
      selection->select((GTransition*)obj);
      break;
    default:
      break;
    }
  }

  lastObjectRClicked = obj;
  selection->setContextObject(obj, otype);

  //viewport()->repaint();
  repaint(false);
  main->updateAll();

  switch(otype)
  {
  case StateT: main->showContextState(); break;
  case TransitionT: main->showContextTrans(); break;
  default: main->showContext(); break;
  }
  setFocus();
}


/// Called when the context menu is closing
void DrawArea::contextMenuHiding()
{
  resetContext();
}

/// Resets the context (used for context menu)
void DrawArea::resetContext()
{
  lastObjectRClicked = NULL;
  selection->setContextObject(NULL, 0);
}


/**
 * Zoom in the view at point @a p.
 * If p = (-1,-1) the middle of the view is taken.
 */
void DrawArea::zoomIn(QPoint p/*=(-1,-1)*/)
{
  int spx, spy;
  if (p.x()==-1)
    p = lastLClicked;
  setUpdatesEnabled(false);
  zoom->zoom(this, p, TRUE);

  spx = int((p.x())*ZOOM_FACTOR);
  spy = int((p.y())*ZOOM_FACTOR);
  emit scrollWidgetTo(spx, spy);
  emit zoomedToPercentage(int(zoom->getScale()*100+0.5));
  setUpdatesEnabled(TRUE);
  repaint();
}

/**
 * Zoom out the view at point @a p
 * If p = (-1,-1) the middle of the view is taken.
 */
void DrawArea::zoomOut(QPoint p/*=(-1,-1)*/)
{
  int spx, spy;
  if (p.x()==-1)
    p = lastLClicked;
  setUpdatesEnabled(false);
  zoom->zoom(this, p, FALSE);

  spx = int((p.x())/ZOOM_FACTOR);
  spy = int((p.y())/ZOOM_FACTOR);
  emit scrollWidgetTo(spx, spy);
  emit zoomedToPercentage(int(zoom->getScale()*100+0.5));
  setUpdatesEnabled(TRUE);
  repaint();
}

/**
 * Set Zoom to 100%
 */
void DrawArea::zoomReset()
{
  setUpdatesEnabled(false);
  zoom->resetZoom(this);
  emit zoomedToPercentage(100);
  setUpdatesEnabled(TRUE);
  repaint();
}

/// Returns the current scale.
double DrawArea::getScale()
{
  return zoom->getScale();
}


/// Called when several objects have been pasted into this scrollview
void DrawArea::objectsPasted()
{
  dragMultiple=TRUE;
}

/// Called when all objects have been selected
void DrawArea::allSelected()
{
  dragMultiple=TRUE;
  //viewport()->repaint();
  repaint(false);
}

/// Returns the tooltip rectangle of the point @a p
QRect DrawArea::tooltipRect(const QPoint& p, QString& tinfo)
{
  Machine* m=NULL;
  int otype;
  GObject* obj;
//  QPoint offset(contentsX(), contentsY());
  QPoint offset(0,0);
  QRect result, result_scaled;
  QRect invalid(0, 0, -1, -1);
  double scale = zoom->getScale();
  QPoint p_norm;

  if (!main->getOptions()->getToolTips())
    return invalid;

  if (!main->project)
    return invalid;

  m = main->project->machine;

  if (!m)
    return invalid;

  obj = m->getObject(p, scale, otype);

  if (otype==NoT || !obj)
    return invalid;

  tinfo = obj->getToolTipInfo(m, main->getOptions());

  p_norm = QPoint(int(p.x()/scale), int(p.y()/scale));
  result = obj->getToolTipRect(p_norm/*+offset*/);
  result.normalize();

  result_scaled.setLeft(int(result.left()*scale));
  result_scaled.setTop(int(result.top()*scale));
  result_scaled.setWidth(int(result.width()*scale));
  result_scaled.setHeight(int(result.height()*scale));
  result_scaled.moveBy(-offset.x(), -offset.y());


  return result_scaled;
}

bool DrawArea::event(QEvent *event)
{
 if (event->type() == QEvent::ToolTip) {
     QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
     QString tinfo;
     tooltipRect(helpEvent->pos(), tinfo); 
     QToolTip::showText(helpEvent->globalPos(), tinfo);
 }
 return QWidget::event(event);
}

