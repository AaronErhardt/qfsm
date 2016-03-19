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

#include "MainWindow.h"
#include "Machine.h"
#include "Error.h"
#include "GState.h"
#include "GTransition.h"
#include "Convert.h"
#include "TransitionInfo.h"
#include "IOInfoBin.h"
#include "IOInfoASCII.h"
#include "Selection.h"
#include "Simulator.h"
#include "SimulatorDlgImpl.h"
#include "DrawArea.h"


/**
 * Constructor.
 * @param m pointer to main window
 */
Simulator::Simulator(MainWindow* m)
	 : QObject(m)
{
  main = m;
  simdlg = new SimulatorDlgImpl((QWidget*)main);
  current_state=NULL;

  connect(simdlg, SIGNAL(closing()), this, SLOT(stopSimulation()) );
  connect(simdlg, SIGNAL(inputSent()), this, SLOT(next()) );
  connect(simdlg, SIGNAL(resetPressed()), this, SLOT(reset()) );
}

/// Destructor
Simulator::~Simulator()
{
  delete simdlg;
}


/**
 * Starts simulation.
 * Opens the simulation dialog and resets the machine @a m.
 * @return TRUE if simulation was started, FALSE if an error occured.
 */
bool Simulator::startSimulation(Machine* m)
{
  Error err;
  int olen;
  int count=0;
  QString out;

  if (!m)
    return FALSE;
  machine=m;


  if (m->getInitialState()==NULL)
  {
    err.info(tr("You have to define an initial state."));
    return FALSE;
  }

  m->updateDefaultTransitions();

  enableButtons();
  simdlg->init();

  main->getScrollView()->getDrawArea()->getSelection()->deselectAll(machine);
  main->repaintViewport();
  setCurrentState(m->getInitialState());
  olen = m->getNumOutputs();
  while (count<olen)
  {
    out += "0";
    count++;
  }
  if (!simdlg->isOBinChecked())
    out = out.right(count/4);

  simdlg->setOutputs(out);

//  sim_dlg->show();
  simdlg->show();

  return TRUE;
}

/**
 * Stops the running simulation.
 */
void Simulator::stopSimulation()
{
  main->setMode(DocStatus::Select);
  main->getScrollView()->getDrawArea()->getSelection()->deselectAll(machine);
  main->repaintViewport();

  simdlg->stopTimer();
  simdlg->hide();

  main->updateAll();
}


/**
 * Enables the respective number of the bit buttons.
 */
void Simulator::enableButtons()
{
  int num;
  num = machine->getNumInputs();


  simdlg->enable0(num>0);
  simdlg->enable1(num>1);
  simdlg->enable2(num>2);
  simdlg->enable3(num>3);
  simdlg->enable4(num>4);
  simdlg->enable5(num>5);
  simdlg->enable6(num>6);
  simdlg->enable7(num>7);
  simdlg->enable8(num>8);
  simdlg->enable9(num>9);
  simdlg->enable10(num>10);
  simdlg->enable11(num>11);
  simdlg->enable12(num>12);
  simdlg->enable13(num>13);
  simdlg->enable14(num>14);
  simdlg->enable15(num>15);

  simdlg->enableFrequency(TRUE);
  simdlg->enableSend(TRUE);
}

/// Sets @a s the current state of the simulation.
void Simulator::setCurrentState(GState* s)
{
  if (current_state)
    current_state->select(FALSE);

  current_state = s;
  s->select();

  simdlg->setStateName(s->getStateName());
  simdlg->setStateCode(s->getCodeStr(machine->getType()));
  if (s->isFinalState())
    simdlg->setState(SimulatorDlgImpl::Finished);
  else
    simdlg->setState(SimulatorDlgImpl::Busy);
}


/**
 * Proceeds with the next step in the simulation.
 * Reads the inputs from the inputs field and sends them to the machine.
 */
void Simulator::next()
{
  QString in, out;
  int numin, numout;
  GState* next_state;
  Convert conv;
  IOInfo* ioinfo;
  IOInfoBin iobin(IO_MealyIn);
  IOInfoASCII ioascii(IO_MealyIn);
  Error err;

  numin = machine->getNumInputs();
  numout = machine->getNumOutputs();

  in = simdlg->getInputs();
//  bin = new char[numin+1];
  if (simdlg->isIBinChecked())
  {
    
    if (Transition::conditionValid(Binary, in, FALSE))
    {
      if (!simdlg->isClockOn())
        err.info(tr("Input is not in binary format."));
      else
        //simdlg->setInputs("");
	simdlg->clearInput();
      return;
    }
    iobin = conv.binStrToX10(numin, in, IO_MealyIn);
    ioinfo = &iobin;
  }
  else if (simdlg->isIHexChecked())
  {
    QString intmp=in;
    intmp = intmp.replace(QRegExp("[0-9a-fA-F\\s]"), "");
    if (!intmp.isEmpty())
    {
      if (!simdlg->isClockOn())
        err.info(tr("Input is not in hexadecimal format."));
      else
        //simdlg->setInputs("");
	simdlg->clearInput();
      return;
    }
    iobin = conv.hexStrToX10(numin, in, IO_MealyIn);
    ioinfo = &iobin;
  }
  else  // ASCII
  {
    ioascii.setInfo(in); 
    ioinfo = &ioascii;
    if (!ioascii.isSingle())
    {
      if (!ioascii.getInfo().isEmpty() && !simdlg->isClockOn())
        err.info(tr("The input is not a single character.")); //
      else
        //simdlg->setInputs("");
	simdlg->clearInput();
      return;
    }
  }

//  IOInfoBin ioinfo(bin, numin);

  next_state = next(ioinfo, out);

  if (next_state)
  {
    simdlg->setOutputs(out);
    setCurrentState(next_state);
    main->repaintViewport();

  }
  if (simdlg->isClockOn() && simdlg->isIASCIIChecked())
  {
    simdlg->resetBits();
    simdlg->clearInput();
  }
  else
    simdlg->selectFirst();
//  delete [] bin;
}

/**
 * Proceeds with the next step.
 * @param in input info (e.g. bits)
 * @param out output information (mealy)
 * @return Next state. If no transition matches the input information the
 * current state remains the same
 */
GState* Simulator::next(IOInfo* in, QString& out)
{
  GTransition* t;
  bool has_default=false;
  GTransition*default_transition;

  if (!current_state)
    return NULL;

  QListIterator<GTransition*> i(current_state->tlist);

  while(i.hasNext())
  {
    t = i.next();

//    if (!t->isDeleted() && t->getInfo()->matches(in))
    if(!t->isDeleted())
    {
      if(t->getInfo()->getInputInfo()->isDefault())
      {
        has_default=true;
        default_transition=t;
      }

      if (t->getInfo()->matches(in))
      {
        if (simdlg->isOBinChecked())
          out = t->getInfo()->getOutputsStrBin();
        else if (simdlg->isOHexChecked())
          out = t->getInfo()->getOutputsStrHex();
        else out = t->getInfo()->getOutputsStrASCII();

        return (GState*)t->getEnd();
      }
    }
  }
  if(has_default)
    return (GState*)default_transition->getEnd();

  return NULL;
}


/// Resets the simulator.
void Simulator::reset()
{
  int olen;
  int count=0;
  QString out;

  olen = machine->getNumOutputs();
  while (count<olen)
  {
    out += "0";
    count++;
  }
  if (!simdlg->isOBinChecked())
    out = out.right(count/4);

  simdlg->setOutputs(out);

  setCurrentState(machine->getInitialState());
  main->repaintViewport();
}


/// Closes the simulator dialog.
void Simulator::closeDlg()
{
  simdlg->hide();
}

