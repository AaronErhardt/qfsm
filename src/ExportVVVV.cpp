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

#include "ExportVVVV.h"
#include "Machine.h"
#include "TransitionInfo.h"
//#include "AppInfo.h"
#include "IOInfo.h"
#include "Options.h"

//using namespace std;


ExportVVVV::ExportVVVV(Options* opt)
  	  : Export(opt)
{
}

/// Writes all the relevant data into the tdf file.
void ExportVVVV::doExport()
{
  writeMain();
}


QString ExportVVVV::fileFilter()
{
  return "vvvv Automata code (*.txt)";
}
QString ExportVVVV::defaultExtension()
{
	return "txt";
}


/// Writes the vvvv Automata code to the output stream
void ExportVVVV::writeMain()
{
  using namespace std;

  GState* reset=NULL;
  GState* s;
  GTransition* t;
  QString tinfoi, tinfoo, sn1, sn2, reset_sn;
  State* stmp;
  TransitionInfo* tinfo;
  bool first;
  QString reset_event_name, reset_action_name;

  // output reset state first
  reset = machine->getInitialState();
  sn1 = reset->getStateName();
  sn1.replace(QRegExp(" "), "_");
  reset_sn = sn1;
  reset_event_name = options->getVVVVResetEvent();
  if (reset_event_name.isEmpty())
    reset_event_name = "Reset";
  reset_action_name = options->getVVVVResetAction();
  if (reset_action_name.isEmpty())
    reset_action_name = "DoReset";
  
  QMutableListIterator<GTransition*> it(reset->tlist);

  for(; it.hasNext();)
  {
    t = it.next();
    tinfo = t->getInfo();

    if (!t->isDeleted() && t->getEnd())
    {
      tinfoi = tinfo->getInputsStr();
      tinfoo = tinfo->getOutputsStr();
      tinfoi.replace(QRegExp(" "), "_");
      tinfoo.replace(QRegExp(" "), "_");
      stmp = t->getEnd();

      if (!tinfoi.isEmpty() && stmp)
      {
	sn2 = stmp->getStateName();
	sn2.replace(QRegExp(" "), "_");

	if (tinfoo.isEmpty())
	  tinfoo = "Do" + sn2;

	*out << sn1.latin1() << " " << tinfoi.latin1() << " " << sn2.latin1() << " " << tinfoo.latin1() << endl;
      }
    }
  }

  // output all other states
  QMutableListIterator<GState*> is(machine->getSList());

  for(; is.hasNext();)
  {
    s = is.next();
    if (s->isDeleted())
      continue;
    sn1 = s->getStateName();
    sn1.replace(QRegExp(" "), "_");

    QMutableListIterator<GTransition*> it(s->tlist);

    if (s==reset)  // reset state has already been output
      continue;

    if (options->getVVVVReset())
    {

      *out << sn1.latin1() << " " << reset_event_name.latin1() << " " << reset_sn.latin1() << " " << reset_action_name.latin1() << " " << endl;
    } 

    for(; it.hasNext();)
    {
      t = it.next();
      tinfo = t->getInfo();

      if (!t->isDeleted() && t->getEnd())
      {
	tinfoi = tinfo->getInputsStr();
	tinfoo = tinfo->getOutputsStr();
	tinfoi.replace(QRegExp(" "), "_");
	tinfoo.replace(QRegExp(" "), "_");
	stmp = t->getEnd();

	if (!tinfoi.isEmpty() && stmp)
	{
	  sn2 = stmp->getStateName();
	  sn2.replace(QRegExp(" "), "_");

	  if (tinfoo.isEmpty())
	    tinfoo = "Do" + sn2;

	  *out << sn1.latin1() << " " << tinfoi.latin1() << " " << sn2.latin1() << " " << tinfoo.latin1() << endl;
	}
      }
    }
  }

}


