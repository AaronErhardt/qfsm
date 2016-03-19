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

#include <iostream>
#include <qregexp.h>

#include "ExportSMC.h"
#include "Machine.h"
#include "TransitionInfo.h"
//#include "AppInfo.h"
#include "IOInfo.h"

//using namespace std;


ExportSMC::ExportSMC(Options* opt)
  	  : Export(opt)
{
}

/// Writes all the relevant data into the tdf file.
void ExportSMC::doExport()
{
  writeMain();
}


QString ExportSMC::fileFilter()
{
  return "SMC (*.sm)";
}
QString ExportSMC::defaultExtension()
{
	return "sm";
}


/// Writes the reset state and the transitions to the output stream
void ExportSMC::writeMain()
{
  using namespace std;

  GState* initial=NULL;

  writeHeader("//", "");

  initial = machine->getInitialState();

  *out << "%class " << machine->getName().latin1() << endl;
  *out << endl;
  /*
  *out << "%fsmclass " << machine->getName().latin1() << endl;
  *out << endl;
  */
  *out << "%start MainMap::" << initial->getStateName().latin1() << endl;
  *out << endl;
  *out << "%map MainMap" << endl;
  *out << "%%" << endl;

  writeTransitions();

  *out << "%%" << endl;
}


/// Writes the transitions to the output stream
void ExportSMC::writeTransitions()
{
  using namespace std;

  GState* s;
  GTransition* t;
  QString tinfoi, tinfoo, sn1, sn2;
  State* stmp;
  TransitionInfo* tinfo;
  IOInfo* iosingle;
  IOInfo* tioinfo;
  bool first;
  QStringList tinfoo_list, action_list;
  QString tinfoi_processed, tinfoo_processed;
  QStringList::iterator sit;
  QString ena, exa, act;
  
  QMutableListIterator<GState*> is(machine->getSList());

  for(; is.hasNext();)
  {
    s = is.next();
    if (s->isDeleted())
      continue;

    sn1 = s->getStateName();
    sn1.replace(QRegExp(" "), "_");

    *out << sn1.latin1() << endl;

    QMutableListIterator<GTransition*> it(s->tlist);

    // entry actions
    ena = s->getEntryActions();
    if (!ena.isEmpty())
    {
      *out << "Entry\n{" << endl;
      action_list = ena.split(',');
      sit = action_list.begin();
      while (sit!=action_list.end())
      {
	act = (*sit).trimmed();
	act.replace(QRegExp(" "), "_");
	*out << "  " << act.latin1() << ";" << endl;
	++sit;
      }
      *out << "}" << endl;
    }
    // exit actions
    exa = s->getExitActions();
    if (!exa.isEmpty())
    {
      *out << "Exit\n{" << endl;
      action_list = exa.split(',');
      sit = action_list.begin();
      while (sit!=action_list.end())
      {
	act = (*sit).trimmed();
	act.replace(QRegExp(" "), "_");
	*out << "  " << act.latin1() << ";" << endl;
	++sit;
      }
      *out << "}" << endl;
    }

    // transitions
    *out << "{" << endl;
    for(; it.hasNext();)
    {
      t = it.next();
      tinfo = t->getInfo();
      tioinfo = tinfo->getInputInfo();

      if (!t->isDeleted() && t->getEnd())
      {
	tinfoi = tinfo->getInputsStr();
	tinfoo = tinfo->getOutputsStr();
	tinfoo_list = tinfoo.split(',');

	tinfoi_processed = tinfoi.trimmed();
	tinfoi_processed.replace(QRegExp(" "), "_");
	stmp = t->getEnd();

	if ((!tinfoi.isEmpty() || tioinfo->isDefault()) && stmp)
	{
	  sn2 = stmp->getStateName();
	  sn2.replace(QRegExp(" "), "_");
	  if (tioinfo->isDefault()) // default transition
	    *out << "  Default" << endl;
	  else // not default transition
	    *out << "  " << tinfoi_processed.latin1() << endl; 
	  *out << "    " << sn2.latin1() << endl;
	  *out << "    {" << endl;
	  if (!tinfoo.isEmpty())
	  {
	    sit = tinfoo_list.begin();
	    while (sit!=tinfoo_list.end())
	    {
	      tinfoo_processed = (*sit).trimmed();
	      tinfoo_processed.replace(QRegExp(" "), "_");
	      *out << "      " << tinfoo_processed.latin1() << ";" << endl;
	      ++sit;
	    }
	  }
	  *out << "    }" << endl;
	}
      }
    }
    *out << "}" << endl << endl;
  }

}


