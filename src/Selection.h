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

replaced Qt 3 iterators by Qt 4 iterators
*/


#ifndef SELECTION_H
#define SELECTION_H

#include <q3ptrlist.h>
#include <qobject.h>

//#include "ScrollView.h"
#include "Machine.h"

class DrawArea;
class GState;


/**
 * @class Selection
 * @brief Class responsible for all informations and operations concerning the 
 * selection.
 */
class Selection : public QObject
{
  Q_OBJECT
  public:
    Selection(QWidget*, const char* name=0);
    ~Selection();

    /// Returns a list containing all selected states
    QList<GState*>& getSList() { return ssel_list; }
    /// Returns a list containing all selected transitions
    QList<GTransition*>& getTList() { return tsel_list; }
    /// Returns TRUE if initial transition is selected otherwise FALSE
    bool isITransSelected() { return itrans; }
    /// If @s is TRUE selects initial transition otherwise deselects it
    void selectITrans(bool s=TRUE) { itrans = s; }
    bool isStateSelected(State* );
    bool isTransitionSelected(Transition* );

    GObject* select(DrawArea* , Machine* , QPoint , double, int& );
    void select(GState*, bool sel=TRUE);
    void select(GTransition*, bool sel=TRUE);
    void select(GITransition*, bool sel=TRUE);
    bool selectRect(Machine*, DRect& , bool add);
    bool selectAdd(DrawArea* , Machine*, QPoint, double );
//    bool selectRectAdd(ScrollView*, Machine*, QPoint, double );
    int selectControl(Machine* , QPoint, double, GTransition*&);
    bool selectAll(Machine*, DRect& bound);
    bool deselect(GState*);
    bool deselect(GTransition*);
    bool deselect(GITransition*);
    void deselectAll(Machine* );

    bool onSelectionOld(QPoint, double);
    bool onSelection(Machine*, QPoint, double);
    void move(double, double, DrawArea* , Machine* );
    void getBoundingRect(double&, double&, double&, double&, GState* );
    void updateBoundingRect(DRect&, GState* );

    /// Returns the number of selected states.
    int countStates() { return ssel_list.count(); };
    /// Returns the number of selected transitions.
    int countTransitions() { return tsel_list.count(); };
    /// Returns the number of all selected objects.
    int count() { return ssel_list.count()+tsel_list.count(); };
    /// Deselects all selections.
    void clear() { ssel_list.clear(); tsel_list.clear(); };

    /// Sets the context object
    void setContextObject(GObject* obj, int type) { context_object = obj; co_type=type; };
    /// Returns the context object
    GObject* getContextObject(int& type) { type = co_type; return context_object; };

  private:
    void setMinMax(double, double, double&, double&, double&, double&);

    /// List of selected states
    QList<GState*> ssel_list;
    /// List of selected transitions
    QList<GTransition*> tsel_list;
    /// If TRUE, the initial transition is selected
    bool itrans;

    /// Context object (object under cursor when clicking the right mouse button)
    GObject* context_object;
    /// Type of context object (see #ObjectType)
    int co_type;

  signals:
    /// Emited when the main window needs to be updated
    void updateAll();
};


#endif
