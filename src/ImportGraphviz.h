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

#ifndef IMPORTGRAPHVIZ_H
#define IMPORTGRAPHVIZ_H

#include <qstring.h>
#include "Import.h"

class Options;
class Project;


/**
 * @class ImportGraphviz
 * @brief Class that manages importing from Graphviz dot files
 *
 */
class ImportGraphviz : public Import
{
  public:
    ImportGraphviz(Options* opt);
    //~ImportGraphviz();

    /// Does the actual exporting
    Project* doImport();
    /// Returns the appropriate filter string for the file dialog.
    QString fileFilter() { return "Graphviz dot file (*.gv)"; };
    /// Returns the default file extension
    QString defaultExtension() { return "gv"; };

  private:
    /// Fits a simple cubic spline (with 4 control points @a cpx, @a cpy) to a set of data points @a x, @a y using gradient descent.
    /// The two end points of the spline are fixed.
    void cubicSplineApprox(int numin, double x[], double y[], double cpx[], double cpy[]);
};

#endif

