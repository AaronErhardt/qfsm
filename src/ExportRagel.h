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
/*
Qt 4 Port by Rainer Strobel

replaced Qt 3 iterators through Qt 4 iterators
in method writeTransitions:
added .latin1() to out << iosingle
*/

#ifndef EXPORTRAGEL_H
#define EXPORTRAGEL_H

#include "Export.h"

/**
 * @class ExportRAGEL
 * @brief Class that manages export to ragel FSM files.
 *
 * The ragel file can be used to generate code with the programs from the (separate) ragel project. 
 * This is useful for parser generation or to automatically create (complicated) program logic.
 */

class ExportRagel : public Export
{
  Q_OBJECT

  public:
    ExportRagel(Options* opt);

    bool validateMachine(Machine* );
    void doExport();
    QString fileFilter();
	QString defaultExtension();

    int writeActionFile(const char* filename, const char* ragelfile);

  private:
    void writeName();
    void writeMain();
    void writeTransitions();


    bool create_action;
    int lang_action;
};

#endif
