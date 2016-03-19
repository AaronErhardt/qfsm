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
#include "TableBuilderLatex.h"
#include "Machine.h"

/// Constructor
TableBuilderLatex::TableBuilderLatex(QObject* par, Machine* m, Options* opt)
  		 : TableBuilder(par, m, opt)
{
}

/// Destructor
TableBuilderLatex::~TableBuilderLatex()
{
}

QString TableBuilderLatex::fileFilter()
{
  return "Latex State Table (*.tex)";
}

QString TableBuilderLatex::defaultExtension()
{
	return "tex";
}


QString TableBuilderLatex::getHead()
{
  QListIterator<IOInfo*> ioit(eventlist);
  QListIterator<GState*> sit(machine->getSList());
  IOInfo* info;
  GState* s;
  QString sheadhead, shead;
  bool first=FALSE;
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

  sheadhead = "\\begin{tabular}{|l||";
  for(int i=0; i<rowcount; i++)
    sheadhead+="c|";
  sheadhead+="}\n";
  sheadhead += "\\hline \n";
  sheadhead += " & \\multicolumn{" + QString::number(rowcount) + "}{|c|}{" +
    col_label + "} \\\\ \n" ;
  sheadhead += "\\cline{2-" + QString::number(rowcount+1) + "}\n";
  sheadhead += row_label;

  if (options->getStateTableOrientation()==0)
  {
    for(; ioit.hasNext();)
    {
      if (!first)
	shead+=" & ";
      info = ioit.next();
      if (info->isInverted())
	nottmp=notstr;
      else
	nottmp="";
      shead += nottmp + " " + info->convertToString(machine, options);
      first=FALSE;
    }
  }
  else
  {
    for(; sit.hasNext();)
    {
      s = sit.next();
      if (!s->isDeleted())
      {
	if (!first)
	  shead+=" & ";
	shead += s->getStateName();
	first=FALSE;
      }
    }
  }

  shead.replace(QRegExp("\\\\"), "$\\backslash$");
  shead.replace(QRegExp("_"), "\\_");

  shead = sheadhead + shead;
  shead += " \\\\\n";
  /*
  shead += tr("States") + " & ";
  for(int j=0; j<(int)eventlist.count(); j++)
    shead += " &";
  shead += " \\\\\n";
  */
  shead += "\\hline \n";
  shead += "\\hline \n";
  return shead;
}

QString TableBuilderLatex::getFoot()
{
  QString sfoot;
//  sfoot = "\\hline \n";
  sfoot += "\\end{tabular}\n";

  return sfoot;
}


QString TableBuilderLatex::getRow(GState* s)
{
  QListIterator<IOInfo*> ioit(eventlist);
  IOInfo* io;
  IOInfo* io_out;
  GState* next;
  bool first=FALSE;
  QString srow, srow_out;

  srow = s->getStateName(); // + " & ";
  for(;ioit.hasNext();)
  {
    io = ioit.next();
    if (!first)
      srow+=" & ";
    if ((next = s->next(io, io_out))!=NULL)
    {
      srow += next->getStateName();
    }
    else
      srow += "-";
    first=FALSE;
  }


  if (options->getStateTableIncludeOut())
  {
    srow += " \\\\\n";
    srow_out="";
    // asynchronous outputs
    ioit.toFront();
    for(;ioit.hasNext();)
    {
      io = ioit.next();
      srow_out+=" & ";
      if ((next = s->next(io, io_out))!=NULL)
      {
	srow_out += io_out->convertToString(machine, options);
      }
      else
	srow_out += " ";
    }
    srow_out.replace(QRegExp("\\\\"), "$\\backslash$");
    //srow_out.replace(QRegExp("_"), "\_");
  }

  srow += srow_out + " \\\\\n";
  srow += "\\hline \n";
  srow.replace(QRegExp("_"), "\\_");
  return srow;
}



QString TableBuilderLatex::getRow(IOInfo* io)
{
  //QListIterator<IOInfo> ioit(eventlist);
  QListIterator<GState*> sit(machine->getSList());
  //IOInfo* io;
  IOInfo* io_out;
  GState *s, *next;
  bool first=FALSE;
  QString srow, srow_out;
  QString notstr = options->getInversionDescriptor();
  QString nottmp;

  //srow = s->getStateName(); // + " & ";
  if (io->isInverted())
    nottmp=notstr;
  else
    nottmp="";
  srow = nottmp + " " + io->convertToString(machine, options);

  for(;sit.hasNext();)
  {
//    io = ioit.current();
    s = sit.next();
    if (!s->isDeleted())
    {
      if (!first)
	srow+=" & ";
      if ((next = s->next(io, io_out))!=NULL)
      {
	srow += next->getStateName();
      }
      else
	srow += "-";
      first=FALSE;
    }
  }
  srow.replace(QRegExp("\\\\"), "$\\backslash$");

  if (options->getStateTableIncludeOut())
  {
    srow += " \\\\\n";
    srow_out="";
    // asynchronous outputs
    sit.toFront();
    for(;sit.hasNext();)
    {
      s = sit.next();
      if (!s->isDeleted())
      {
	srow_out+=" & ";
	if ((next = s->next(io, io_out))!=NULL)
	{
	  srow_out += io_out->convertToString(machine, options);
	}
	else
	  srow_out += " ";
      }
    }
    srow_out.replace(QRegExp("\\\\"), "$\\backslash$");
    //srow_out.replace(QRegExp("_"), "\_");
  }

  srow += srow_out + " \\\\\n";
  srow += "\\hline \n";
  srow.replace(QRegExp("_"), "\\_");
  return srow;
}
