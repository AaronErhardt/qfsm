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



#ifndef EXPORTTESTVECTORASCII_H
#define EXPORTTESTVECTORASCII_H

#include "Export.h"

class Options;
class TestvectorGenerator;

/**
 * @class ExportTestvectorASCII
 * @brief Class that manages export of an ASCII testvector.
 *
 */

class ExportTestvectorASCII : public Export
{
  public:
    ExportTestvectorASCII(Options* opt);

    ~ExportTestvectorASCII();

    void doExport();
    QString fileFilter();
    QString defaultExtension();

    void generateVector();

    void writeHeader(QString,QString);

  private:

    /// TestvectorGenerator object for current machine
    TestvectorGenerator* generator;

    /// If TRUE, the reset signal will be handled synchronously, otherwise asynchronously.
    bool synchronous_reset;

     /// If TRUE an enable signal will be added
    bool synchronous_enable;

    /// If TRUE the reset signal is negated
    bool negated_reset;

    /// If TRUE, 'std_logic' is used instead of 'bit'
    bool use_std_logic;

    /// If TRUE, the names of the inputs/outputs are used, otherwise the vectors a,o,q
    bool io_names;
};

#endif // EXPORTTESTVECTORASCII_H
