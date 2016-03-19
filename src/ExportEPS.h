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

#ifndef EXPORTEPS_H
#define EXPORTEPS_H

#include "Export.h"

class Options;

/**
 * @class ExportEPS
 * @brief Class that manages export to EPS.
 *
 */

class ExportEPS : public Export
{
  public:
    ExportEPS(Options* opt);

    void doExport();
    QString fileFilter();
	QString defaultExtension();

  private:
    void writeHeader(QString , QString ) { return; };
    bool fixEPS(const QString &fileName, QRect rect) const;
};

#endif
