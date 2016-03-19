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

#include <qprinter.h>
#include <q3paintdevicemetrics.h>

#include "PrintManager.h"
#include "MainWindow.h"
#include "Draw.h"
#include "Machine.h"
#include "Error.h"

/// Constructor
PrintManager::PrintManager(QWidget* parent)
	    : QObject(parent)
{
  main = (MainWindow*)parent;

  printer = new QPrinter();
  draw = new Draw(main, main->getOptions());
}

/// Destructor
PrintManager::~PrintManager()
{
  delete printer;
  delete draw;
}


/**
 * Prints the current machine adjusting on one page.
 */
void PrintManager::print()
{
  if (printer->setup(main))
  {
    QPainter p;
    Machine* m = main->project->machine;
    int w, h;
    double scale;
    int canvw, canvh;
    int mleft, mtop;
    mleft = 10;
    mtop = 10;
    QString name;
    QRect textrect;

    name = printer->printerName();
//    qDebug(name);
    if (!printer->outputToFile() && name.isEmpty())
    {
      Error::info(tr("The printer could not be initialised."));
      return;
    }
    p.begin(printer);

    Q3PaintDeviceMetrics metrics(printer);
    w = metrics.width();
    h = metrics.height();
 
    m->getCanvasSize(canvw, canvh);
    scale = (double)w/canvw;
    if (canvh*scale>h)
      scale = (double)h/canvh;

    printer->setFullPage(FALSE);

    draw->drawStates(m, &p, int(-mleft/scale), int(-mtop/scale), scale);
    draw->drawTransitions(m, &p, int(-mleft/scale), int(-mtop/scale), scale) 
      /*m->getNumInputs(), m->getNumOutputs()*/;
    if (m->getDrawITrans())
      draw->drawInitialTransition(m, m->getInitialTransition(), &p, int(-mleft/scale),
	int(-mtop/scale), scale, textrect, FALSE);
    if (main->getOptions()->getPrintHeader())
      draw->drawHeadline(m, &p); //, scale);
    
    p.end();
  }
}
