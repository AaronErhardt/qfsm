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

replaced Qt 3 interator through Qt 4 iterators
*/

#ifndef EXPORTAHDL_H
#define EXPORTAHDL_H

#include "Export.h"
#include <Q3PtrList>
#include <Q3PtrListIterator>

/**
 * @class ExportAHDL
 * @brief Class that manages export to AHDL.
 *
 * The AHDL file can be used as a Altera Max2Plus text design file (tdf).
 * A tdf file can be compiled by the Max2Plus software and afterwards programmed into an
 * Altera chip.
 */

class ExportAHDL : public Export
{
  public:
    ExportAHDL(Options* opt);
    void doExport();
    QString fileFilter();
	QString defaultExtension();

  private:
    void writeName();
    void writeIO();
    void writeVariables();
    void writeMain();
    void writeTransitions();

    bool sync_reset;
    bool use_moore;
};

#endif
