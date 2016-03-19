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

#ifndef TRANSITIONMANAGER_H
#define TRANSITIONMANAGER_H

#include <q3ptrlist.h>

class GState;
class GTransition;
class MainWindow;
//class DTransitionProperties;
class TransitionPropertiesDlgImpl;
class Machine;


/**
 * @class TransitionManager
 * @brief Control class for transitions.
 */
class TransitionManager
{
  public:
    TransitionManager(MainWindow* );
    ~TransitionManager();

    bool addTransition(GState* , GState* , int, int, double, double, double,
      double, double, double, double, double);
    void straightenSelection(QList<GTransition*>* );
    void editTransition(Machine*, GTransition* );

  private:
    /// Pointer to the main window
    MainWindow* main;
    /// Transition properties dialog
    TransitionPropertiesDlgImpl* trans_props;
};


#endif
