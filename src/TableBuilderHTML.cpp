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
#include "TableBuilderHTML.h"

/// Constructor
TableBuilderHTML::TableBuilderHTML(QObject* par, Machine* m, Options* opt)
  		 : TableBuilder(par, m, opt)
{
}

/// Destructor
TableBuilderHTML::~TableBuilderHTML()
{
}

QString TableBuilderHTML::fileFilter()
{
  return "HTML State Table (*.html)";
}

QString TableBuilderHTML::defaultExtension()
{
	return "html";
}


QString TableBuilderHTML::getHead()
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

  sheadhead = "<TABLE border=\"1\">\n";
  sheadhead += "<TR>\n";
  //sheadhead += "\t<TH valign=\"bottom\" width=\"50\" height=\"40\">" 
  sheadhead += "\t<TH valign=\"bottom\" rowspan=\"2\">" 
    + row_label + "</TH>\n";

  sheadhead += "\t<TH colspan=\"" + QString::number(rowcount) + "\" halign=\"center\">"
    + col_label + "</TH>\n";
  sheadhead += "</TR>\n";
  sheadhead += "<TR>\n";

  if (options->getStateTableOrientation()==0)
  {
    for(; ioit.hasNext();)
    {
      info = ioit.next();
      if (info->isInverted())
	nottmp=notstr;
      else
	nottmp="";
      shead += "\t<TH>"+nottmp + " " + info->convertToString(machine, options)+"</TH>\n";
    }
  }
  else
  {
    for(; sit.hasNext();)
    {
      s = sit.next();
      if (!s->isDeleted())
	shead += "\t<TH>"+ s->getStateName() +"</TH>\n";
    }
  }

  shead = sheadhead + shead + "</TR>\n";

  return shead;
}

QString TableBuilderHTML::getFoot()
{
  QString sfoot;
  sfoot = "</TABLE>\n";

  return sfoot;
}


QString TableBuilderHTML::getRow(GState* s)
{
  QListIterator<IOInfo*> ioit(eventlist);
  IOInfo* io;
  GState* next;
  QString srow;
  IOInfo* io_out;

  srow =  "<TR>\n";
  srow += "\t<TD>" + s->getStateName() + "</TD>\n";

  for(;ioit.hasNext();)
  {
    io = ioit.next();
    if ((next = s->next(io, io_out))!=NULL)
    {
      srow += "\t<TD>" + next->getStateName();

      if (options->getStateTableIncludeOut())
	srow += "<BR>" + io_out->convertToString(machine, options);
	
      srow += "</TD>\n";
    }
    else
      srow += "\t<TD align=\"Center\">-</TD>\n";
  }
//  srow.replace(QRegExp("_"), "\\_");
  srow += "</TR>\n";
  return srow;
}



QString TableBuilderHTML::getRow(IOInfo* io)
{
  //QListIterator<IOInfo> ioit(eventlist);
  QListIterator<GState*> sit(machine->getSList());
  //IOInfo* io;
  GState *s, *next;
  QString srow;
  IOInfo* io_out;
  QString notstr = options->getInversionDescriptor();
  QString nottmp;

  srow =  "<TR>\n";
  //srow += "\t<TD>" + s->getStateName() + "</TD>\n";
  if (io->isInverted())
    nottmp=notstr;
  else
    nottmp="";
  srow += "\t<TD>" + nottmp + " " + io->convertToString(machine, options) + "</TD>\n";

  for(;sit.hasNext();)
  {
    s = sit.next();
    if (!s->isDeleted())
    {
      if ((next = s->next(io, io_out))!=NULL)
      {
	srow += "\t<TD>" + next->getStateName();

	if (options->getStateTableIncludeOut())
	  srow += "<BR>" + io_out->convertToString(machine, options);
	  
	srow += "</TD>\n";
      }
      else
	srow += "\t<TD align=\"Center\">-</TD>\n";
    }
  }
//  srow.replace(QRegExp("_"), "\\_");
  srow += "</TR>\n";
  return srow;
}

