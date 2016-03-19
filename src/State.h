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

#ifndef STATE_H
#define STATE_H

#include <qstring.h>

#include "IOInfoBin.h"

class Machine;

/**
 * @class State
 * @brief Stores information about a State
 */
class State
{
  public:
    State(Machine* m, const QString, QString, int cd, IOInfo* mooreout, bool ends, QString ena="", QString exa="");
    State(Machine* m);
    State(const State& );
    State();
    ~State();

    State& operator=(const State& );

    /// Sets the name of the state
    void setStateName(QString n ) { sname = n; };   
    /// Returns the name of the state
    QString getStateName() { return sname; };
    /// Sets the description of the state
    void setDescription(QString d ) { sdescription = d; };   
    /// Returns the description of the state
    QString getDescription() { return sdescription; };
    /// Sets the code of the state
    void setEncoding(int c);
    /// Returns the code of the state.
    int getEncoding() { return code; };
    /// Sets the moore outputs of the state
    void setMooreOutputs(IOInfo* o) { moore_outputs = o; };   
    /// Returns the moore outputs of the state.
    IOInfo* getMooreOutputs() { return moore_outputs; };
    /// Sets/clears the 'end state' flag
    void setFinalState(bool fs=TRUE) { finalstate = fs; };
    /// Toggles the 'end state' flag
    void toggleFinalState() { finalstate=!finalstate; };
    /// Returns TRUE if this state is an end state, otherwise FALSE
    bool isFinalState() { return finalstate; }

    QString getCodeStr(int type=-1);
    QString getMooreOutputsStr(Machine* m=NULL, Options* opt=NULL);

    /// Returns the entry actions of the state
    QString getEntryActions() { return entry_actions; };
    /// Sets the entry actions of the state
    void setEntryActions(QString ea) { entry_actions = ea; };
    /// Returns the exit actions of the state
    QString getExitActions() { return exit_actions; };
    /// Sets the exit actions of the state
    void setExitActions(QString ea) { exit_actions = ea; };


    static bool codeValid(int mtype, QString );
    static bool mooreOutputValid(int mtype, QString );

  protected:
    /// Pointer to the machine this state belongs to
    Machine* machine;
    /// Name 
    QString sname;
    /// Description
    QString sdescription;
    /// Coding of the state 
    int code;
    /// Moore outputs of the state
    IOInfo* moore_outputs;
    /// If TRUE, this state is a final state
    bool finalstate;
    /// Entry actions (used for Free-text-type machines and SMC export)
    QString entry_actions;
    /// Exit actions (used for Free-text-type machines and SMC export)
    QString exit_actions;
};



#endif
