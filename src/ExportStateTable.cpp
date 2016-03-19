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

#include <qapplication.h>
#include "ExportStateTable.h"
#include "Machine.h"
#include "TransitionInfo.h"
#include "IOInfo.h"
#include "TableBuilder.h"


/// Constructor
ExportStateTable::ExportStateTable(Options* opt, TableBuilder* tb)
                : Export(opt)
{
  tablebuilder = tb;
}

/// Writes all the relevant data into the tdf file.
void ExportStateTable::doExport()
{
  if(tablebuilder->fileFilter().find(".txt")==-1)  //no header for text files
    writeHeader(tablebuilder->getCommentStart(), tablebuilder->getCommentEnd());
  writeMain();
}


QString ExportStateTable::fileFilter()
{
  return tablebuilder->fileFilter();
}

QString ExportStateTable::defaultExtension()
{
	return tablebuilder->defaultExtension();
}


/// Writes the main part to the output stream
void ExportStateTable::writeMain()
{
  QString header, body, footer;
  header = tablebuilder->getHead();
  body = tablebuilder->getBody();
  footer = tablebuilder->getFoot();

  *out << header.latin1() << body.latin1() << footer.latin1();
}


