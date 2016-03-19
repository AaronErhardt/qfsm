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

#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <q3scrollview.h>
#include <qrect.h>
//Added by qt3to4:
#include <QMouseEvent>
#include <QPaintEvent>
#include <QDrag>

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

class Zoom;
class Draw;
class GTransition;
class MainWindow;
class Grid;
class ToolTipSV;
class Selection;

/**
 * @class DrawArea
 * @brief Stores all the information concerning the drawing area (inside the scroll view) and is responsible for the user interaction.
 */


class DrawArea : public QWidget
{
  Q_OBJECT
  public:
    DrawArea(QWidget* parent=0,MainWindow*m=0, const char* name=0);
    ~DrawArea();

    void resetState();
    void reset();
    void updateBackground();
    /// Sets the state to dragging multiple objects
    void setDragMultiple(bool dm=TRUE) { dragMultiple=dm; }
    /// Returns TRUE if user drags several objects at once otherwise FALSE
    bool getDragMultiple() { return dragMultiple; }
    /// Returns TRUE is user drags something
    bool getDrag() { return drag; }
    /// Returns current selection
    Selection* getSelection() { return selection; }
    double getScale();
    /// Returns the current selection rectangle
    DRect getSelectionRect() { return selectionRect; }
    /// Sets the current seleciton rectangle
    void setSelectionRect(DRect r) { selectionRect=r; }

    void drawTransition(GTransition* , bool clear=FALSE);
    void drawInitialTransition(GITransition* , bool clear=FALSE);

    QRect tooltipRect(const QPoint& p, QString& info );

    void showContext(QPoint p);
    GObject* getContextObject(int& type);
    void resetContext();
    bool event(QEvent *event);

  private:
    /// Stores the most recent cursor (panning with middle mouse button)
    QCursor oldCursor;
    /// Position where the left mouse button was clicked most recently
    QPoint lastLClicked;
    /// TRUE if the left mouse button is down
    bool left_down;
    /// TRUE if the middle mouse button is down
    bool middle_down;
    /// If TRUE mouse dragging is initiated
    bool drag;
    /// If TRUE mouse dragging (with middle button) is initiated
    bool drag_middle;
    /// X coordinate of drag start position (aligned to grid)
    double dragStartgX;
    /// Y coordinate of drag start position (aligned to grid)
    double dragStartgY;
    /// X coordinate of drag start position
    double dragStartX;
    /// Y coordinate of drag start position
    double dragStartY;
    /// X coordinate of the last mouse position (with snap to grid)
    double lastMovePosX;
    /// Y coordinate of the last mouse position (with snap to grid)
    double lastMovePosY;
    /// X coordinate of the last mouse position (without snap to grid)
    double lastMousePosX;
    /// Y coordinate of the last mouse position (without snap to grid)
    double lastMousePosY;
    /// X coordinate of the last clicked position of the first control point of a transition
    double lastMovePosCont1X;
    /// Y coordinate of the last clicked position of the first control point of a transition
    double lastMovePosCont1Y;
    /// X coordinate of the last clicked position of the second control point of a transition
    double lastMovePosCont2X;
    /// Y coordinate of the last clicked position of the second control point of a transition
    double lastMovePosCont2Y;

    /// X coordinate of the last position of the start point of a transition
    double lastStartPointX;
    /// Y coordinate of the last position of the start point of a transition
    double lastStartPointY;
    /// X coordinate of the last position of the end point of a transition
    double lastEndPointX;
    /// Y coordinate of the last position of the end point of a transition
    double lastEndPointY;
    /// X coordinate of the last position of the first control point of a transition
    double lastCont1X;
    /// Y coordinate of the last position of the first control point of a transition
    double lastCont1Y;
    /// X coordinate of the last position of the second control point of a transition
    double lastCont2X;
    /// Y coordinate of the last position of the second control point of a transition
    double lastCont2Y;
    /// Last bounding rectangle of the descriptor text ("Reset") of the initial transition
    QRect lastITextRect;

    /// Pointer to the state that was clicked most recently (with the left mouse button)
    GState* lastStateClicked;
    /// Pointer to the object that was clicked most recently (with the right mouse button)
    GObject* lastObjectRClicked;
    /// Pointer to the transition that was dragged most recently
    GTransition* lastTransitionDragged;
    /// Pointer to the transition that was clicked most recently
    GTransition* lastTransitionClicked;
    /// Temporary transition (when dragging)
    GTransition* dragTransition;
    /// Temporary initial transition (when dragging)
    GITransition* dragITransition;
    /// Saved Objects for undo
    GState savedState;
    /// Saved initial transition
    GITransition savedITrans;
    /// Control of the transition that was clicked most recently
    int lastTransitionControl;
    /// If TRUE, this is the first step when dragging a transition
    bool firstTransitionDraw;
    /// If TRUE, the (dotted) control lines of a transition are drawn (when dragging)
    bool drawControlLines;
    /// If TRUE, a rectangle is being dragged
    bool dragRect;
    /// If TRUE, a multiple selection has been made
    bool dragMultiple;
    /// If TRUE, the user has clicked on the selection
    bool onSelection;
    /// Selection rectangle
    DRect selectionRect;

    /// Main window
    MainWindow* main;
    /// Zoom object
    Zoom* zoom;
    /// Selection
    Selection* selection;
    /// Draw object
    Draw* draw;
    /// Grid object
    Grid* grid;
    /// Tooltip window
    ToolTipSV* tooltip;

    void mousePressEvent(QMouseEvent* );
    void mouseMoveEvent(QMouseEvent* );
    void mouseReleaseEvent(QMouseEvent* );
    void mouseDoubleClickEvent(QMouseEvent* );
    void paintEvent(QPaintEvent* );

  signals:
    /// Emited when the mode of the document changes
    void setMode(int );
    /// Emited when the canvas size changed
    void updateCanvasSize(int,int, double);
    /// Emited when zoomed to a certain percentage
    void zoomedToPercentage(int);
    /// Emitted to scroll contents window
    void scrollWidget(int,int);
    void scrollWidgetTo(int,int);

  public slots:
    void zoomIn(QPoint = QPoint(-1,-1));
    void zoomOut(QPoint = QPoint(-1,-1));
    void zoomReset();
    //void updateCanvasSize();
    void objectsPasted();
    void allSelected();
    void contextMenuHiding();
    void escapePressed();
    void resizeContents(int,int,bool allow_smaller=true);
    void resizeContentsNotSmaller(int w, int h) { resizeContents(w, h, false); };
};



#endif // DRAWAREA_H

