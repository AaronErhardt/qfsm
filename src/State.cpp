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

#include <math.h>
#include <string.h>

#include "State.h"
#include "Transition.h"
#include "Convert.h"
#include "Machine.h"
#include "TransitionInfo.h"
#include "Utils.h"

/**
 * Constructor.
 * Initialises a state object with name @a n and code @a c.
 */
State::State(Machine* m, const QString n, QString d, int c, IOInfo* mooreout, bool ends, QString ena/*=""*/, QString exa/*=""*/)
{
  machine = m;
  sname = n;
  sdescription = d;
  moore_outputs = mooreout;
  finalstate=ends;
  

   int stateCodeSize=machine->getNumEncodingBits();

  code=c;
  entry_actions = ena;
  exit_actions = exa;
}

/// Constructor
State::State(Machine* m)
{
  machine=m;
  sname = "";
  sdescription="";
  code = 0;
  finalstate=FALSE;
  moore_outputs=NULL;
  entry_actions="";
  exit_actions="";
}

/// Standard constructor.
State::State()
{
  machine=NULL;
  sname = "";
  sdescription="";
  code = 0;
  finalstate=FALSE;
  moore_outputs=NULL;
  entry_actions="";
  exit_actions="";
}

/// Copy constructor.
State::State(const State& st)  
{
  machine = st.machine;
  sname = st.sname;
  sdescription = st.sdescription;
  code = st.code;

  if (st.moore_outputs)
    moore_outputs = st.moore_outputs->clone();
  else
    moore_outputs = NULL;

  finalstate=st.finalstate;
  entry_actions = st.entry_actions;
  exit_actions = st.exit_actions;
}


/// Overloaded assignment operator.
State& State::operator=(const State& st) 
{
  if (this != &st)
  {
    machine=st.machine;
    sname = st.sname;
    sdescription = st.sdescription;
    code = st.code;

    if (st.moore_outputs)
      moore_outputs = st.moore_outputs->clone();
    else
      moore_outputs = NULL;

    finalstate=st.finalstate;
    entry_actions = st.entry_actions;
    exit_actions = st.exit_actions;
  }
  return *this;
}

/// Destructor
State::~State()
{
}


/**
 * Validates the code in string @a s.
 * 
 * @param mtype Machine type
 * @param s String to validate
 * @returns TRUE if the code is valid, otherwise FALSE
 */
bool State::codeValid(int mtype, QString s)
{
  if (mtype==Binary)
  {
    return Utils::binStringValid(s);
  }
  else
  {
    int icode;
    bool ok;
    icode = s.toInt(&ok);

    return ok;
  }
}

/**
 * Validates string @a s, that represents a moore output
 *
 * @param mtype Machine type
 * @param s String to validate
 * @returns TRUE if the moore output is valid, otherwise FALSE
 */
bool State::mooreOutputValid(int mtype, QString s)
{
  if (mtype==Binary)
  {
    return Utils::binStringValid(s);
  }
  else
  {
    return (Transition::conditionValid(mtype, s, FALSE)==0);
  }
}



/**
 * Returns a string representing the coding of the state
 *
 * @param type If 'Binary' a binary string is returned, otherwise an integer string.
 * @returns The resulting string
 */
QString State::getCodeStr(int type/*=-1*/)
{
  Convert conv;
  QString res;
  int stateCodeSize;
  stateCodeSize=machine->getNumEncodingBits();

  if (type==-1)
    type = machine->getType();

  switch (type)
  {
    case Binary:
      res = conv.intToBinStr(code, stateCodeSize);
      return res;
    default:
      res.setNum(code);
      return res;
  }
}

void State::setEncoding(int c)
{

  code=c;
}

/**
 * Returns a string representing the moore outputs of the state
 *
 * @returns The resulting string
 */
QString State::getMooreOutputsStr(Machine* m/*=NULL*/, Options* opt/*=NULL*/)
{
  Convert conv;
  QString res;

  //res = conv.X10ToBinStr(moore_outputs);
  res = moore_outputs->convertToString(m, opt);
  return res;
}



