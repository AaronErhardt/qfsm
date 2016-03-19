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

removed constructor of struct dtlist, which disables the AutoDelete feature
of QList. In Qt 4, this feature does no longer exist.
All QList use pointers as items, now.

removed setAutoDelete calls in constructor of class Undo
*/

#ifndef UNDO_H
#define UNDO_H

#include <q3ptrlist.h>
#include <qstringlist.h>
#include "GTransition.h"
#include "GState.h"
#include "GITransition.h"

class Project;

/**
 * @enum UndoAction
 * @brief Action which the undo object can undo.
 */
enum UndoAction {AddState, AddTransition, ChangeState, ChangeTransition,
		 ChangeTransitions, MoveMultiple, 
		 DeleteSelection, DeleteState, DeleteTransition,
		 ChangeInitialTransition, SetInitialState, SetFinalStates,
		 ChangeMachine, Paste};

/**
 * @struct dtlist
 * @brief Two list of transition pointers.
 */
struct dtlist {
  /// Constructor
//  dtlist() {tlist.setAutoDelete(FALSE); rlist.setAutoDelete(FALSE); };
  /// First list of transitions
  QList<GTransition*> tlist;
  /// Second list of transition
  QList<GTransition*> rlist;
};


/**
 * @class Undo
 * @brief Stores the information about an undo action.
 */
class Undo
{
  public:
    Undo(Project*);
    ~Undo();

    /// Sets the undo action.
    void setAction(int a) { action=a; };
    /// Returns the undo action.
    int getAction() { return action; };
    /// Sets the modified flag.
    void setModified(bool m) { modified=m; };
    /// Returns the modified flag.
    bool getModified() { return modified; };
    /// Sets the state.
    void setState(GState* s) { state=s; };
    /// Returns the state.
    GState* getState() { return state; };
    /// Sets the second state.
    void setState2(GState* s) { state2=s; };
    /// Returns the second state.
    GState* getState2() { return state2; };
    /// Sets the initial state
    void setInitialState(GState* s) { istate=s; };
    /// Returns the initial state
    GState* getInitialState() { return istate; };
    /// Sets the transition
    void setTransition(GTransition* t) { transition = t; };
    /// Returns the transition
    GTransition* getTransition() { return transition; };
    /// Sets the second transition
    void setTransition2(GTransition* t) { transition2 = t; };
    /// Returns the second transition
    GTransition* getTransition2() { return transition2; };
    /// Sets the initial transition
    void setInitialTransition(GITransition* t) { itrans= t; };
    /// Returns the initial transition
    GITransition* getInitialTransition() { return itrans; };
    /// Sets the second initial transition
    void setInitialTransition2(GITransition* t) { itrans2 = t; };
    /// Returns the second initial transition
    GITransition* getInitialTransition2() { return itrans2; };
    /// Gets the coordinates which store the distance objects were moved by
    void getMovedBy(double& x, double& y) { x=movedbyx; y=movedbyy; };
    /// Returns the coordinates which store the distance objects were moved by
    void setMovedBy(double x, double y) { movedbyx=x; movedbyy=y; };
    void getMachineInfo(Machine*& m, QString& n, int& t, int& nb, QStringList& olistm, 
	int& ni, QStringList& ilist, int& no, QStringList& olist, QFont& sf, QFont& tf, 
	int& at, bool& dit);
    void setMachineInfo(Machine* m, QString n, int t, int nb, QStringList olistm, int ni, 
      QStringList ilist, int no, QStringList olist, QFont sf, QFont tf, int at, bool dit);
    /// Sets the number of bits (moore outputs) to @a nb
    void setNumMooreOutputs(int nb) { nummooreout=nb; };
    /// Returns the number of bits (moore outputs)
    int getNumMooreOutputs() { return nummooreout; };
    /// Sets the number of input bits to @a ni
    void setNumInputs(int ni) {numin = ni; };
    /// Returns the number of input bits
    int getNumInputs() { return numin; };
    /// Sets the number of output bits to @a ni
    void setNumOutputs(int no) {numout = no; };
    /// Returns the number of output bits
    int getNumOutputs() { return numout; };
    

    /// Returns the project.
    Project* getProject() { return project; };
    /// Returns the list of transitions which contain copied information.
    QList<GTransition*>* getCopyList() { return &copylist; };
    /// Returns the list of states.
    QList<GState*>* getSList() { return &slist; };
    /// Returns the second list of states.
    QList<GState*>* getSList2() { return &slist2; };
    /// Returns the list of transitions.
    QList<GTransition*>* getTList() { return &tlist; };
    /// Returns the second list of transitions.
    QList<GTransition*>* getTList2() { return &tlist2; };

  public:
    /// Returns the two lists of transition. 
    QList<dtlist*>* getDoubleTList() { return &doubletlist; };

  private:
    /// Action this undo object can undo
    int action;
    /// Pointer to the project
    Project* project;
    /// TRUE if the project was modified before the action
    bool modified;		
    /// State
    GState* state;
    /// State 2
    GState* state2;
    /// Initial state
    GState* istate;
    /// Transition
    GTransition* transition;
    /// Transition 2
    GTransition* transition2;
    /// Initial transition
    GITransition *itrans;
    /// Initial transition 2
    GITransition *itrans2;
    /// Copy of pointers to save the order of the copied transitions (Change state)
    QList<GTransition*> copylist;
    /// List of states (for ChangeMultiple)
    QList<GState*> slist; 	
    /// List of states 2
    QList<GState*> slist2;
    /// List of transitions
    QList<GTransition*> tlist;
    /// List of transitions 2
    QList<GTransition*> tlist2;
    /// Pair of transition lists
    QList<dtlist*> doubletlist;
    /// Moved by x
    double movedbyx;
    /// Moved by y
    double movedbyy;

    /// Machine
    Machine* machine;
    /// Machine name
    QString mname;
    /// Type of the machine
    int type;
    /// Number of input bits of a machine
    int numin;
    /// Number of output bits of a machine
    int numout;
    /// Number of moore output bits of a machine
    int nummooreout;
    /// State font
    QFont sfont;
    /// Transition font
    QFont tfont;
    /// Arrow type
    int arrowtype;
    /// Draw initial transition
    bool ditrans;
    /// String list 1
    QStringList strlist1;
    /// String list 2
    QStringList strlist2;
    /// String list 3
    QStringList strlist3;
};

#endif
