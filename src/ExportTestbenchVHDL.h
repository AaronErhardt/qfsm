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


#ifndef EXPORTTESTBENCHVHDL_H
#define EXPORTTESTBENCHVHDL_H

#include "Export.h"


class Options;

/**
 * @class ExportTestbenchVHDL
 * @brief Class that manages export of a VHDL testbench.
 *
 */

class ExportTestbenchVHDL : public Export
{
  public:
    ExportTestbenchVHDL(Options* opt);

    void doExport();
    QString fileFilter();
  QString defaultExtension();
  void init(std::ofstream* ,std::ofstream* ,Machine*, QString fn=QString::null, ScrollView* sv=NULL);

  private:
    /// Output stream for vhdl testbench file
    std::ofstream* outb;
    /// Output stream for vhdl package file
    std::ofstream* outp;
    /// Name of the machine to export
    QString mname;
    /// Name of the testvector file
    QString testvector_name;
    /// Name of the testvector file
    QString testpackage_name;
    /// Name of the log file
    QString logfile_name;
    /// If TRUE, the names of the inputs/outputs are used, otherwise the vectors a,o,q
    bool io_names;
    /// If TRUE, the reset signal will be handled synchronously, otherwise asynchronously.
    bool synchronous_reset;
    /// If TRUE, a synchronous enable signal will be added
    bool synchronous_enable;
    /// If TRUE, the negated reset signal will be used
    bool neg_reset;
    /// If TRUE, 'std_logic' is used instead of 'bit'
    bool use_std_logic;
    /// If TRUE, an I/O description is written in the header
    bool io_header;
    /// If TRUE, produce Alliance compliant code
    bool alliance;


    void writeEnvironment(std::ofstream*);
    void writeEntity(std::ofstream*);
    void writeArchitecture(std::ofstream*);
    void writeComponent(std::ofstream*);
    void writeConverterFunction(std::ofstream*);
    void writeDefinitions(std::ofstream*);
    void writeInstantiation(std::ofstream*);
    void writeClockProcess(std::ofstream*);
    void writeObserverProcess(std::ofstream*);
    void writeDescription(std::ofstream*);

    // functions for improved testbench
    void writeReadDelimiterProcess(std::ofstream*);
    void writeReadVectorProcess(std::ofstream*);
    void writeReadSignalProcess(std::ofstream*);
    void writeErrorLogProcess(std::ofstream*);
    void writeCheckResultProcess(std::ofstream*);
    void writeNewObserverProcess(std::ofstream*);
    void writePackage(std::ofstream*);

    void writeHeader(std::ofstream*out,QString,QString);

};


#endif // EXPORTTESTBENCHVHDL_H
