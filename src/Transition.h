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

#ifndef TRANSITION_H
#define TRANSITION_H

#include <qstring.h>

class State;
class TransitionInfo;


/**
 * @class Transition
 * @brief Class storing information about a transition.
 *
 * Base class for the graphical object GTransition.
 */
class Transition
{
  public:
    Transition(State*, State*, TransitionInfo*);
    Transition(const Transition& );
    ~Transition();

    Transition& operator=(const Transition& );

    /// Returns starting state
    State* getStart() { return start; };
    /// Sets starting state
    void setStart(State* s) { start = s; };
    /// Returns end state
    State* getEnd() { return end; };
    /// Sets end state.
    void setEnd(State* s) { end = s; };
    /// Returns transition info (condition)
    TransitionInfo* getInfo() { return info; };
    /// Sets the transition condition to @a i
    void setInfo(TransitionInfo* i) { info=i; };
    
    static int conditionValid(int type, QString , bool input=TRUE);

  protected:
    /// Start state
    State* start;
    /// End state
    State* end;
    /// Inputs and outputs of the transition condition 
    TransitionInfo* info;
};


#endif
