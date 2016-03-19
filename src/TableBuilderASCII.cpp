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

#include <qregexp.h>

#include "IOInfo.h"
#include "GState.h"
#include "Options.h"
#include "Machine.h"
#include "TableBuilderASCII.h"

/// Constructor
TableBuilderASCII::TableBuilderASCII(QObject* par, Machine* m, Options* opt)
  		 : TableBuilder(par, m, opt)
{
}

/// Destructor
TableBuilderASCII::~TableBuilderASCII()
{
}

QString TableBuilderASCII::fileFilter()
{
  return "ASCII State Table (*.txt)";
}

QString TableBuilderASCII::defaultExtension()
{
	return "txt";
}


QString TableBuilderASCII::getHead()
{
  QListIterator<IOInfo*> ioit(eventlist);
  QListIterator<GState*> sit(machine->getSList());
  IOInfo* info;
  GState* s;
  QString sheadhead, shead;
  QString col_label=tr("Events");
  QString row_label=tr("States");
  int rowcount = eventlist.count();
  QString notstr = options->getInversionDescriptor();
  QString nottmp;

  if (options->getStateTableOrientation()==1)
  {
    col_label=tr("States");
    row_label=tr("Events");
    rowcount = machine->getNumStates();
  }

  sheadhead = "\""+row_label + "/" + col_label+"\"";
  if (options->getStateTableOrientation()==0)
  {
    for(; ioit.hasNext();)
    {
      info = ioit.next();
      
      if (info->isInverted())
        nottmp=notstr;
      else
        nottmp="";
      shead += ";\"" + nottmp + " " + info->convertToString(machine, options)+"\"";
    }
  }
  else
  {
    for(; sit.hasNext();)
    {
      s = sit.next();
      if (!s->isDeleted())
	shead += ";\""+ s->getStateName()+"\"";
    }
  }

  shead = sheadhead + shead + "\n";

  return shead;
}

QString TableBuilderASCII::getFoot()
{
  QString sfoot;
  sfoot = "\n";

  return sfoot;
}


QString TableBuilderASCII::getRow(GState* s)
{
  QListIterator<IOInfo*> ioit(eventlist);
  IOInfo* io;
  GState* next;
  QString srow;
  IOInfo* io_out;

  srow = s->getStateName();

  for(;ioit.hasNext();)
  {
    io = ioit.next();
    if ((next = s->next(io, io_out))!=NULL)
    {
      srow += ";\"" + next->getStateName();

      if (options->getStateTableIncludeOut())
        srow += " " + io_out->convertToString(machine, options);
      srow+="\"";
    }
    else
      srow += ";\"-\"";
  }
//  srow.replace(QRegExp("_"), "\\_");
  srow += "\n";
  return srow;
}



QString TableBuilderASCII::getRow(IOInfo* io)
{
  //QListIterator<IOInfo> ioit(eventlist);
  QListIterator<GState*> sit(machine->getSList());
  //IOInfo* io;
  GState *s, *next;
  QString srow;
  IOInfo* io_out;
  QString notstr = options->getInversionDescriptor();
  QString nottmp;

  if (io->isInverted())
    nottmp=notstr;
  else
    nottmp="";
  srow = "\""+nottmp + " " + io->convertToString(machine, options)+"\"";

  for(;sit.hasNext();)
  {
    s = sit.next();
    if (!s->isDeleted())
    {
      if ((next = s->next(io, io_out))!=NULL)
      {
	srow += ";\"" + next->getStateName();

	if (options->getStateTableIncludeOut())
	  srow += " " + io_out->convertToString(machine, options);
	srow+="\"";
      }
      else
	srow += ";\"-\"";
    }
  }
//  srow.replace(QRegExp("_"), "\\_");
  srow += "\n";
  return srow;
}

