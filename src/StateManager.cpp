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

#include "StateManager.h"
#include "MainWindow.h"
#include "Project.h"
#include "Machine.h"
#include "Convert.h"
#include "UndoBuffer.h"
#include "TransitionInfo.h"
#include "IOInfoBin.h"
#include "IOInfoASCII.h"
#include "IOInfoText.h"
#include "DrawArea.h"


//#include "dialogs/DStateProperties.h"
#include "StatePropertiesDlgImpl.h"


/// Constructor
StateManager::StateManager(MainWindow* parent)
	    : QObject(parent)
{
//    state_props = new DStateProperties;
    state_props = new StatePropertiesDlgImpl((QWidget*)parent, 0, TRUE);
    state_props->setMainWindow(parent);
    main = parent;
}


/**
 * Adds a state at position @a x, @a y.
 */
bool StateManager::addState(double x, double y)
{
  QString name, scode, smooreout, description;
  QString sradius, slw;
  Convert conv;
  int code;
  IOInfo* mooreout;
  int radius;
  int lw;
  QColor col;
  QPen pen(QColor(0,0,0), 1);
  int mtype;
  QString ena="", exa="";
  
  if (!main->project)
    return FALSE;

  mtype = main->project->machine->getType();

  state_props->setColor(QColor(0,0,0));
  state_props->selectFirst();
  //state_props->setCodeMaxLength(main->project->machine->getNumBits());
  state_props->setMode(StatePropertiesDlgImpl::StateAdd);
  state_props->setName(getNewName());
  state_props->setDescription(""); //"Enter your description here...");
  if (mtype==Binary)
    state_props->setCode(getNewBinCode());
  else
    state_props->setCode(QString::number(getNewCode()));
  state_props->setEntryActions("");
  state_props->setExitActions("");
  if (mtype==Text)
  {
    state_props->setEntryMaxLength(MAX_TEXT_OUTPUTLENGTH);
    state_props->setExitMaxLength(MAX_TEXT_OUTPUTLENGTH);
  }
  else
  {
    state_props->setEntryMaxLength(0);
    state_props->setExitMaxLength(0);
  }
  state_props->setMooreOutputs("");
  state_props->setMooreOutputsMaxLength(main->project->machine->getNumMooreOutputs());

  int result = state_props->exec();

  if (result)
  {
    name = state_props->getName();
    description = state_props->getDescription();
    scode = state_props->getCode();
    smooreout = state_props->getMooreOutputs();
    sradius = state_props->getRadius();
    slw = state_props->getLineWidth();
    col = state_props->getColor();
    pen.setColor(col);

    if (mtype==Binary)
    {
      code = conv.binStrToInt(scode);
      mooreout = new IOInfoBin(IO_MooreOut);
      mooreout->setBin(smooreout, main->project->machine->getNumMooreOutputs());
	//conv.binStrToX10(main->project->machine->getNumMooreOutputs(), smooreout);
    }
    else if (mtype==Ascii)
    {
      code = scode.toInt();
      mooreout = new IOInfoASCII(IO_MooreOut, smooreout);
    }
    else // mtype==Text
    {
      code = scode.toInt();
      mooreout = new IOInfoText(IO_MooreOut, smooreout);

      ena = state_props->getEntryActions();
      exa = state_props->getExitActions();
    }

    radius = sradius.toInt();
    lw = slw.toInt();
    pen.setWidth(lw);
    
    main->project->machine->addState(name, description, code, mooreout, x, y, radius, main->getScrollView()->getDrawArea()->getScale(), pen, FALSE, TRUE, ena, exa);
    main->project->setChanged();
    main->updateAll();
    main->repaintViewport();
    
    return TRUE;
  }
  return FALSE;
}


/**
 * Sets the state @a s in machine @a m as initial state.
 */
void StateManager::setInitialState(Machine* m, GState* s)
{
  double oldx, oldy, newx, newy;
  double tposx, tposy;
  int r1, r2;
  double dx, dy;
  GITransition* it;
  GState* is;

  if (!m)
    return;

  it = m->getInitialTransition();
  is = m->getInitialState();
  main->project->getUndoBuffer()->setInitialState(it);

  if (is)
  {
    is->getPos(oldx, oldy);
    r1 = is->getRadius();
    s->getPos(newx, newy);
    r2 = s->getRadius();

    it->getEndPos(tposx, tposy);

    dx = tposx-oldx;
    dy = tposy-oldy;

    it->move(newx-oldx-dx+(r2/(double)r1*dx), newy-oldy-dy+(r2/(double)r1*dy));
  }
  else
  {
    it = new GITransition(m->getPhantomState(), s);
    m->setInitialTransition(it);
  }
  m->setInitialState(s);
}


/**
 * Sets the states in state list @a sl in machine @a m as final states.
 */
void StateManager::setFinalStates(Machine* m, const QList<GState*>& sl)
{
  if (!m || sl.isEmpty())
    return;

  main->project->getUndoBuffer()->setFinalStates(sl);

  QListIterator<GState*> it(sl);
  for(; it.hasNext();)
  {
    it.next()->toggleFinalState();
  }
  main->project->setChanged();
}


/// Edit the properties of state @a s.
void StateManager::editState(GState* s)
{
  QString name, scode, smooreout, description;
  QString sradius, slw;
  Convert conv;
  IOInfo* mooreout;
  int radius;
  int lw;
  QColor col;
  int mtype;
  int code=0;

  mtype = main->project->machine->getType();

  state_props->selectFirst();
  //state_props->setCodeMaxLength(main->project->machine->getNumBits());
  state_props->setName(s->getStateName());
  state_props->setDescription(s->getDescription());
  state_props->setCode(s->getCodeStr());
  state_props->setMooreOutputs(s->getMooreOutputsStr());
  state_props->setMooreOutputsMaxLength(main->project->machine->getNumMooreOutputs());
  sradius.setNum(s->getRadius());
  state_props->setRadius(sradius);
  slw.setNum(s->getLineWidth());
  state_props->setLineWidth(slw);
  state_props->setColor(s->getColor());
  state_props->setState(s);
  state_props->setMode(StatePropertiesDlgImpl::StateEdit);
  state_props->setEntryActions(s->getEntryActions());
  state_props->setExitActions(s->getExitActions());

  int result = state_props->exec();

  if (result)
  {
    name = state_props->getName();
    description = state_props->getDescription();
    scode = state_props->getCode();
    smooreout = state_props->getMooreOutputs();
    sradius = state_props->getRadius();
    slw = state_props->getLineWidth();
    col = state_props->getColor();

    if (mtype==Binary)
    {
      code = conv.binStrToInt(scode);
      mooreout = new IOInfoBin(IO_MooreOut);
      mooreout->setBin(smooreout, main->project->machine->getNumMooreOutputs());
    }
    else if (mtype==Ascii)
    {
      code = scode.toInt();
      mooreout = new IOInfoASCII(IO_MooreOut, smooreout);
    }
    else
    {
      code = scode.toInt();
      mooreout = new IOInfoText(IO_MooreOut, smooreout);
    }

    //mooreout = conv.binStrToX10(main->project->machine->getNumMooreOutputs(), smoore);

    radius = sradius.toInt();
    lw = slw.toInt();
    
    main->project->getUndoBuffer()->changeState(s, s,
      main->project->machine->getInitialTransition());

    s->setStateName(name);
    s->setDescription(description);
//    s->setSCode(scode);
    s->setEncoding(code);
    s->setMooreOutputs(mooreout);

    s->setRadius(radius);
    s->setTransitionsToRadius(main->project->machine, radius);
  
    s->setLineWidth(lw);
    s->setColor(col);
    s->setEntryActions(state_props->getEntryActions());
    s->setExitActions(state_props->getExitActions());

    main->project->setChanged();
    main->updateAll();
    main->repaintViewport();
  }
}


/// Generates a name for a new state.
QString StateManager::getNewName()
{
  int numstates;
  Machine* m;
  QString s;

  m = main->project->machine;

  numstates = m->getNumStates();

  s.setNum(numstates);
  s = tr("State_") + s;

  return s;
}

/// Generates a decimal code for a new state
int StateManager::getNewCode()
{
  Machine* m;

  m = main->project->machine;

  return m->getNewCode();
}

/// Generates a binary code for a new state
QString StateManager::getNewBinCode()
{
  int code;
  Convert conv;
  QString result;
  Machine* m;
  int bits;

  m = main->project->machine;
  code = getNewCode();
  bits = int(log((float)code)/log(2.0))+1;
  if (bits<1)
    bits=1;

  result = conv.intToBinStr(code, bits); //m->getNumBits());

  return result;
}

