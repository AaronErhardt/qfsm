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

replaced Qt 3 iterator by Qt 4 iterators
removed setAutoDelete(FALSE) calls
*/

#ifndef ICHECK_H
#define ICHECK_H

#include <QObject>
#include <qwidget.h>
#include <q3ptrlist.h>
#include "Options.h"
#include "ICheckDlgImpl.h"

class Machine;
class GState;
class MainWindow;

/**
 * @class ICheck
 * @brief Integrity check routines.
 */
class ICheck
{

  public:
    ICheck(QWidget* parent);
    virtual ~ICheck();

    virtual int checkMachine(Machine* m);
    /// Shows the integrity check dialog
    void showDlg() { icheckdlg->show(); };
    /// Hides the integrity check dialog
    void hideDlg() {icheckdlg->hide();};

    void connectMachine(Machine*m);
    void disconnectMachine(Machine*m);

  //private slots:
    //void dialogReturned(int) {resetMarks();}

  private:
    virtual bool checkUnambiguousCond(Machine* m, Options* opt);
    virtual bool checkInitialState(Machine* m);
    virtual bool checkFinalState(Machine* m);
    virtual bool checkDeadLocks(Machine* m);
    virtual bool checkStateCodes(Machine* m);

    virtual double checkCompleteness(Machine* m);
    virtual double checkStatesReachable(Machine* m);
    virtual double checkFinalStatesReachable(Machine* m);
    virtual double checkConnections(Machine* m);

    bool isStateReachable(Machine* , GState* from, GState* state, QList<GState*>* visited);
    //bool isStateBlocking(GState* state, QList<GState*> visited, QList<GState*> blocking_states);
    void resetMarks();

    /// Integrity check dialog
    ICheckDlgImpl* icheckdlg;
    /// Pointer to the main window
    MainWindow* main;
    /// Protocol of the last integrity check
    QString protocol;
};

#endif

