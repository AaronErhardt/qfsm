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

changed QList<GTransition> and QList<GState> to QList<GTransition*> and QList<GState*>
replaced Qt 3 iterators by Qt 4 iterators

in constructor of class UndoBuffer:
removed setAutoDelete call

in method tidyUp:
replaced while (l->remove()); by the code which removes all elements
from a Qt 4 QList

in method undo:
replaced remove() call by delete list.takeLast(), as it always removes
the last item

in method undoChangeTransition:
removed setAutoDelete calls
changed the removeRef calls to removeAll calls, as all these calls
were used with autoDelete disabled

in method undoDeleteSelection:
removed setAutoDelete calls and replaced removeRef calls by removeAll calls

in method undoPaste:
replaced removeRef call by the code wich removes and delets an item from a 
Qt 4 QList
*/

#ifndef UNDOBUFFER_H
#define UNDOBUFFER_H

#include <qobject.h>
#include <q3ptrlist.h>
#include "Undo.h"

class MainWindow;
class GState;


/** 
 * @class UndoBuffer
 * @brief Stores all undo information and handles the undo process. 
 */
class UndoBuffer 
{
  public:
    UndoBuffer(QObject* );
    ~UndoBuffer();

    /// Returns TRUE if the undo list is empty, otherwise FALSE
    bool isEmpty() { return undolist.isEmpty(); };
    /// Clears the undo list
    void clear() { tidyUp(); undolist.clear(); };
    void tidyUp();

    void addState(Machine* m, GState* );
    void addTransition(GTransition* );
    void changeState(GState*, GState*, GITransition*);
    void changeTransition(GTransition* );
    void changeInitialTransition(GITransition*);
    void changeTransitions(QList<GTransition*>*);
    void moveMultiple(QList<GState*>*, QList<GTransition*>*, double, double);
    void deleteSelection(QList<GState*>*, QList<GTransition*>*);
    void deleteState(GState* );
    void deleteTransition(GTransition* );
    void setInitialState(GITransition* );
    void setFinalStates(const QList<GState*>& sl);
    void changeMachine(Machine* );
    void paste(QList<GState*>*, QList<GTransition*>*, GState* oldistate, 
      GState* newistate, GITransition* olditrans, GITransition* newitrans,
      int oldnumbits, int oldnumin, int oldnumout);

    void undo();

    void undoAddState(Undo*);
    void undoAddTransition(Undo*);
    void undoChangeState(Undo*);
    void undoChangeTransition(Undo*);
    void undoChangeInitialTransition(Undo*);
    void undoChangeTransitions(Undo*);
    void undoMoveMultiple(Undo*);
    void undoDeleteSelection(Undo*);
    void undoDeleteState(Undo*);
    void undoDeleteTransition(Undo*);
    void undoSetInitialState(Undo*);
    void undoSetFinalStates(Undo*);
    void undoChangeMachine(Undo*);
    void undoPaste(Undo*);

  private:
    /// Pointer to the project
    Project* project;
    /// List of undo objects
    QList<Undo*> undolist;
};

#endif
