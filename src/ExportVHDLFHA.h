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

modified VHDL export class which is compatible with the standards of 
the university of applied sciences augsburg
*/

#ifndef EXPORTVHDLFHA_H
#define EXPORTVHDLFHA_H

#include "Export.h"

class Options;

/**
 * @class ExportVHDLFHA
 * @brief Class that manages export to VHDL with FH Augsburg standard.
 *
 */

class ExportVHDLFHA : public Export
{
  public:
    ExportVHDLFHA(Options* opt);

    void doExport();
    QString fileFilter();

  private:
    /// Name of the machine to export
    QString mname;
    /// If TRUE, the reset signal will be handled synchronously, otherwise asynchronously.
    bool synchronous_reset;

    void writeEnvironment();
    void writeEntity();
    void writeArchitecture();
    void writeClockProcess();
    void writeStateProcess();
    void writeDescription();
    
    /// Writes a comment to the top of the output stream 
    virtual void writeHeader(QString commentstart, QString commentend="");
};

#endif
