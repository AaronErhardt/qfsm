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

#include "MachineManager.h"
#include "Project.h"
#include "Machine.h"
#include "MainWindow.h"
#include "Error.h"
#include "UndoBuffer.h"
#include "TransitionInfo.h"
//#include "dialogs/DMachineProperties.h"
#include "MachinePropertiesDlgImpl.h"

/// Constructor
MachineManager::MachineManager(QObject* parent, const char* name)
	      : QObject(parent, name)
{
  main = (MainWindow*)parent;
//  machine_props = new DMachineProperties;
  machine_props = new MachinePropertiesDlgImpl((QWidget*)parent, 0, TRUE) ;
}


/// Destructor
MachineManager::~MachineManager()
{
  delete machine_props;
}

/**
 * Adds a new machine to the project @a p
 */
int MachineManager::addMachine(Project* p)
{
  int result;
  QString n, v, a, d;
  int nb, ni, no;
  QFont f("Helvetica", 8);
  f.setStyleHint(QFont::Helvetica);
  //f.setStyleStrategy(QFont::PreferBitmap);
  QFont sf, tf;
  int atype=1;
  QString inames, onames, onamesm;
  int type;
  bool draw_it;
  int ires;
  Error err;

  machine_props->enableType(TRUE);
  machine_props->setType(0);
  machine_props->setNumMooreOutputs(0);
  machine_props->setMooreOutputNames("");
  machine_props->setNumInputs(1);
  machine_props->setMealyInputNames("");
  machine_props->setNumOutputs(0);
  machine_props->setMealyOutputNames("");
  machine_props->setSFont(f);
  machine_props->setTFont(f);
  machine_props->selectFirst();
  machine_props->setArrowType(atype);
  machine_props->setDrawITrans(TRUE);
  machine_props->setName("FSM");

 
  while(true)
  {
    result = machine_props->exec();

    if (result)
    {
      n = machine_props->getName();
      if(n.length()<=0)
        n="FSM";
      v = machine_props->getVersion();
      a = machine_props->getAuthor();
      d = machine_props->getDescription();
      type = machine_props->getType();
      nb = machine_props->getNumMooreOutputs();
      ni = machine_props->getNumInputs();
      no = machine_props->getNumOutputs();
      onamesm = machine_props->getMooreOutputNames();
      inames = machine_props->getMealyInputNames();
      onames = machine_props->getMealyOutputNames();
      sf = machine_props->getSFont();
      tf = machine_props->getTFont();
      atype = machine_props->getArrowType();
      draw_it = machine_props->getDrawITrans();

      p->addMachine(n, v, a, d, type, nb, onamesm, ni, inames, no, onames,sf, tf, atype, draw_it);

      p->getMain()->updateIOView(p->machine);

      if(nb!=p->machine->translateNames(onamesm).size() ||
        ni!=p->machine->translateNames(inames).size() ||
        no!=p->machine->translateNames(onames).size())
      {
        ires = err.warningOkCancel(
          tr("Warning.\nThe number of bits does not match the number of signal names. \nDo you want to proceed?"));
        if (ires == QMessageBox::Ok)
          break;
        else continue;
      }
    }
    break;
}

  return result;
}
  

/**
 * Edits the machine in the project @a p.
 */
void MachineManager::editMachine(Project* p)
{
  bool result;
  int mtype, numbit, numin, numout;
  int nnumbit, nnumin, nnumout;
  QString name, nname, version, author, description, nversion, nauthor, ndescription;
  Machine* m;
  Error err;
  int ires;
  QFont sf, tf;
  int atype;
  QString inames, onames, onamesm;
  QStringList ilist, olist;
  bool draw_it;

  m = p->machine;

  numbit = m->getNumMooreOutputs();
  machine_props->enableType(FALSE);
  mtype = m->getType();
  numin = m->getNumInputs();
  numout = m->getNumOutputs();
  name = m->getName();
  version = m->getVersion();
  author = m->getAuthor();
  description = m->getDescription();
  sf = m->getSFont();
  tf = m->getTFont();
  atype = m->getArrowType();
  onamesm = m->getMooreOutputNames();
  inames = m->getMealyInputNames();
  onames = m->getMealyOutputNames();
  ilist = m->getInputNameList();
  olist = m->getOutputNameList();
  numbit = m->getNumMooreOutputs();
  numin = m->getNumInputs();
  numout = m->getNumOutputs();
  draw_it = m->getDrawITrans();

  machine_props->setName(name);
  machine_props->setVersion(version);
  machine_props->setAuthor(author);
  machine_props->setDescription(description);
  machine_props->setType(mtype);
  machine_props->setNumMooreOutputs(numbit);
  machine_props->setNumInputs(numin);
  machine_props->setNumOutputs(numout);
  machine_props->setMooreOutputNames(onamesm);
  machine_props->setMealyInputNames(inames);
  machine_props->setMealyOutputNames(onames);
  machine_props->setSFont(sf);
  machine_props->setTFont(tf);
  machine_props->setArrowType(atype);
  machine_props->setDrawITrans(draw_it);
  machine_props->selectFirst();

  result = machine_props->exec();

  if (result)
  {
     nname = machine_props->getName();
	 if(nname.length()<=0)
		 nname="FSM";
     nversion = machine_props->getVersion();
     mtype = machine_props->getType();
     nnumbit = machine_props->getNumMooreOutputs();
     nnumin = machine_props->getNumInputs();
     nnumout = machine_props->getNumOutputs();
     nauthor = machine_props->getAuthor();
     ndescription = machine_props->getDescription();
     
     QList <GState*> states=m->getSList();


     if (nnumbit<numbit || nnumin<numin || nnumout<numout)
     {
       ires = err.warningOkCancel(
         tr("Warning.\nReducing the number of bits may result in data loss. \nDo you want to proceed?"));
       if (ires != QMessageBox::Ok)
         return;
     }
     
     if(nnumbit!=m->translateNames(machine_props->getMooreOutputNames()).size() || 
        nnumin !=m->translateNames(machine_props->getMealyInputNames() ).size() ||
        nnumout!=m->translateNames(machine_props->getMealyOutputNames()).size())
     {
       ires = err.warningOkCancel(
         tr("Warning.\nThe number of bits does not match the number of signal names. \nDo you want to proceed?"));
       if (ires != QMessageBox::Ok)
         return;
     }       
     
     p->getUndoBuffer()->changeMachine(m);

     m->setName(nname);
     m->setVersion(nversion);
     m->setAuthor(nauthor);
     m->setDescription(ndescription);
     m->setType(mtype);
     m->setNumMooreOutputs(nnumbit);
     m->setNumInputs(nnumin);
     m->setNumOutputs(nnumout);
     m->setMooreOutputNames(nnumbit, machine_props->getMooreOutputNames());
     m->setMealyInputNames(nnumin, machine_props->getMealyInputNames());
     m->setMealyOutputNames(nnumout, machine_props->getMealyOutputNames());
     m->setSFont(machine_props->getSFont());
     m->setTFont(machine_props->getTFont());
     m->setArrowType(machine_props->getArrowType());
     m->setDrawITrans(machine_props->getDrawITrans());

     if (!m->getDrawITrans())
       m->getInitialTransition()->select(FALSE);

     p->getMain()->updateIOView(m);
     main->project->setChanged();
  }
}

  
