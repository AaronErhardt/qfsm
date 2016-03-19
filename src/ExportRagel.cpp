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
#include <fstream>
#include <qregexp.h>
#include <qmessagebox.h>

#include "ExportRagel.h"
#include "Machine.h"
#include "TransitionInfo.h"
//#include "AppInfo.h"
#include "IOInfo.h"
#include "Options.h"
#include "Error.h"
#include "UndoBuffer.h"

//using namespace std;


ExportRagel::ExportRagel(Options* opt)
  	  : Export(opt)
{
  create_action=false;
  lang_action=0;
}


bool ExportRagel::validateMachine(Machine* m)
{
  QMutableListIterator<GState*> is(m->getSList());
  bool result = TRUE;
  QString msg = tr("The state name \'%1\' is invalid as it is has a special meaning for the Ragel state machine compiler.");
  QString msg2 = tr("The name of state \'%1\' begins with an invalid character.");

  for(; is.hasNext();)
  {
    // verify if there is no state called 'start' or 'final'
    //   and if every state name begins with a letter
    QString n = is.next()->getStateName();
    if (n=="start")
    {
      result = FALSE;
      if (Error::warningOkCancel(msg.arg("start"))==QMessageBox::Cancel)
	return FALSE;
    }
    else if (n=="final")
    {
      result = FALSE;
      if (Error::warningOkCancel(msg.arg("final"))==QMessageBox::Cancel)
	return FALSE;
    }
    QString firstletter;
    firstletter = n[0];
    QRegExp regexp("[a-zA-Z_]");
    if (!regexp.exactMatch(firstletter))
    {
      result = FALSE;
      if (Error::warningOkCancel(msg2.arg(n))==QMessageBox::Cancel)
	return FALSE;
    }
  }
  return result;
}


/// Writes all the relevant data into the tdf file.
void ExportRagel::doExport()
{
  using namespace std;

  create_action=options->getRagelCreateAction();
  lang_action=options->getRagelLangAction();
  if (options->getRagelDefaultTransitions())
  {
    machine->addDefaultTransitionsToEveryState();
    machine->updateDefaultTransitions();
  }

  writeHeader("#");

  *out << endl << "%%{" << endl;

  writeName();
  writeMain();

  *out << endl << "}%%" << endl;

  // remove the added default transitions (using the undo buffer)
  if (options->getRagelDefaultTransitions())
  {
    UndoBuffer* u = machine->getProject()->getUndoBuffer();
    for(int i=0; i<machine->getNumStates(); i++)
      u->undo();
    machine->updateDefaultTransitions();
  }
}


QString ExportRagel::fileFilter()
{
  return "Ragel (*.rl)";
}
QString ExportRagel::defaultExtension()
{
	return "rl";
}


/// Writes the SUBDESIGN line to the output stream
void ExportRagel::writeName()
{
  using namespace std;

  QString n;

  n = machine->getName();

  n = n.replace(QRegExp("\\s"), "_");

  *out << "machine " << n.latin1() << ";" << endl << endl;
}




/// Writes the definition of the subdesign (from BEGIN to END) to the output stream
void ExportRagel::writeMain()
{
  using namespace std;

  *out << "main :=" << endl;

  writeTransitions();

  *out << ";" << endl;
}


/// Writes the CASE part to the output stream
void ExportRagel::writeTransitions()
{
  using namespace std;

  GState* s;
  State* stmp;
  GTransition* t;
  QString tinfoi, tinfoo, sn;
  TransitionInfo* tinfo;
  QString iosingle;
  IOInfo* tioinfo;
//  Convert conv;
  bool first;
  bool sfirst=TRUE;
  bool tfirst;

  //*out << "\tCASE fsm IS" << endl;
  
  QMutableListIterator<GState*> is(machine->getSList());

  for(; is.hasNext();)
  {

    s = is.next();
    if (s->isDeleted())
      continue;

    sn = s->getStateName();
    sn.replace(QRegExp(" "), "_");
    //if (s->countTransitions()>0)
    {
      if (!sfirst)
	*out << "," << endl;
      if (machine->getInitialState()==s)
	*out << "start:" << endl;
      *out << sn.latin1() << ": (" << endl;
    }
    if (s->countTransitions()==0)
    {
      *out << "  \"\" @not_accept -> final"; // << sn;
    }

    QMutableListIterator<GTransition*> it(s->tlist);
    tfirst=TRUE;

    for(; it.hasNext();)
    {
      t = it.next();
      tinfo = t->getInfo();
      tioinfo = tinfo->getInputInfo();

      if (!t->isDeleted() && t->getEnd())
      {
	QStringList strlist;
	strlist = tioinfo->getRagelConditions();
	
	QStringList::iterator ioit;

	if (!tfirst)
	  *out << " | " << endl;

	*out << "  ";  // indent
	if (strlist.count()>1)
	  *out << "( ";

	first = TRUE;
	for(ioit = strlist.begin(); ioit!=strlist.end(); ++ioit)
	{
	  iosingle = *ioit;

	  if (!first)
	  {
	    if (tioinfo->isInverted())
	      *out << " & ";
	    else
	      *out << " | ";
	  }

	  /*
	  if (iosingle[0]!='^' && iosingle[0]!='[')
	    *out << "(";
	    */

//      *out << iosingle;
      *out << iosingle.latin1();

	  /*
	  if (iosingle[0]!='^' && iosingle[0]!='[')
	    *out << ")";
	    */

	  first=FALSE;
	}

	if (strlist.count()>1)
	  *out << " )";

	// next state
	stmp = t->getEnd();
	if (stmp)
        {
	  sn = stmp->getStateName();
          sn.replace(QRegExp(" "), "_");
        }
	//if (stmp!=s)
	if (stmp->isFinalState())
	  *out << " @accept ";
	else
	  *out << " @not_accept ";
	*out << " -> " << sn.latin1();

	tfirst=FALSE;
      }
    }

    //if (s->countTransitions()>0)
      *out << ")";

    sfirst=FALSE;
  }

}


int ExportRagel::writeActionFile(const char* filename, const char* ragelfile)
{
  using namespace std;

  ofstream aout(filename);

  if (!aout)
    return -1;

  QString n;
  n = machine->getName();
  n = n.replace(QRegExp("\\s"), "_");

  if (lang_action==1) // Java
  {
    aout << "public class FSM_" << n.latin1() << endl;
    aout << "{" << endl;
    aout << endl;
  }

  aout << "%%{" << endl << endl;
  aout << "machine " << n.latin1() << ";" << endl << endl;
  aout << "action accept { res = 1; }" << endl;
  aout << "action not_accept { res = 0; }" << endl << endl;
  aout << "include \"" << ragelfile << "\";" << endl << endl;
  aout << "}%%" << endl << endl << endl;

  if (lang_action==0) // C/C++
  {
    aout << "#include <stdio.h>" << endl;
    aout << "#include <string.h>" << endl;
    aout << endl;
  }
  aout << "%% write data;" << endl;
  aout << endl;

  switch (lang_action)
  {
    case 0: // C/C++
      aout << "int parse(char* string)" << endl;
      break;
    case 1: // Java
      aout << "public int parse(String string)" << endl;
      break;
    case 2:
      aout << "def parse( data )" << endl;
      break;
  }

  switch (lang_action)
  {
    case 0:
    case 1:
      aout << "{" << endl;
      aout << "  int cs;" << endl;
      aout << "  int res=0;" << endl;
      break;
    case 2:
      aout << "  cs=0;" << endl;
      aout << "  res=0;" << endl;
      break;
  }

  switch (lang_action)
  {
    case 0:
      aout << "  char *p, *pe;" << endl;
      aout << endl;
      aout << "  p = string;" << endl;
      aout << "  pe = p + strlen(string);" << endl;
      break;
    case 1:
      aout << "  int p, pe;" << endl;
      aout << endl;
      aout << "  p = 0;" << endl;
      aout << "  pe = string.length();" << endl;
      aout << endl;
      aout << "  char data[] = new char[pe];" << endl;
      aout << "  for(int i=0; i<pe; i++)" << endl;
      aout << "    data[i] = string.charAt(i);" << endl;
      break;
    case 2:
      aout << "  p = 0;" << endl;
      aout << "  pe = data.length();" << endl;
  }

  aout << endl;
  aout << "  %% write init;" << endl;
  aout << "  %% write exec;" << endl;
  aout << endl;
  aout << "  return res;" << endl;

  switch (lang_action)
  {
    case 0: // C/C++
    case 1:
      aout << "}" << endl << endl;
      break;
    case 2:
      aout << "end" << endl << endl;
      break;
  }

  if (lang_action==1) // Java
    aout << "}" << endl;  // end of class definition

  return 0;
}




