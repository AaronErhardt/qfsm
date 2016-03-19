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

#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <qobject.h>
#include <qstring.h>
#include "GState.h"

//class DStateProperties;
class StatePropertiesDlgImpl;
class MainWindow;
class Machine;


/**
 * @class StateManager
 * @brief Control class for states.
 */
class StateManager : public QObject
{
  Q_OBJECT
  public:
    StateManager(MainWindow* );

    bool addState(double , double );
    void setInitialState(Machine* , GState* );
    void setFinalStates(Machine* , const QList<GState*>& sl);
    void editState(GState*);
    QString getNewName();
    QString getNewBinCode();
    int getNewCode();

  private:
    /// Pointer to the main window
    MainWindow* main;
    /// State properties dialog
    StatePropertiesDlgImpl* state_props;

};





#endif
