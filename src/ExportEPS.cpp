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

#include <iostream>
#include <qregexp.h>
#include <qprinter.h>
#include <qpainter.h>
#include <qfile.h>
#include <QTextStream>

#include "ExportEPS.h"
#include "Machine.h"
#include "TransitionInfo.h"
//#include "AppInfo.h"
#include "IOInfo.h"
#include "Draw.h"
#include "ScrollView.h"
#include "DrawArea.h"

//using namespace std;


ExportEPS::ExportEPS(Options* opt)
  	  : Export(opt)
{
}

/// Writes all the relevant data into the tdf file.
void ExportEPS::doExport()
{
  using namespace std;

  // code adapted from Umbrello
  bool exportSuccessful;
  QRect textrect;

  //out->close();

    // print the image to a normal postscript file,
    // do not clip so that everything ends up in the file
    // regardless of "paper size"

    // because we want to work with postscript
    // user-coordinates, set to the resolution
    // of the printer (which should be 72dpi here)
    QPrinter *printer;

    printer = new QPrinter(QPrinter::ScreenResolution);

    printer->setOutputToFile(true);
    printer->setOutputFormat(QPrinter::PostScriptFormat);
    printer->setOutputFileName(fileName);
    printer->setColorMode(QPrinter::Color);
	printer->setFontEmbeddingEnabled(true);

    // do not call printer.setup(); because we want no user
    // interaction here
    QPainter *painter = new QPainter(printer);

    // make sure the widget sizes will be according to the
    // actually used printer font, important for getDiagramRect()
    // and the actual painting
    //view->forceUpdateWidgetFontMetrics(painter);

    if (!scrollview)
    {
      delete painter;
      delete printer;
      exportSuccessful = FALSE;
    }
    Draw* draw = new Draw(scrollview, options);
    QRect rect = draw->getBoundingBox(machine, painter);
	rect.setWidth(rect.width()+10);
	rect.setHeight(rect.height()+10);
    painter->translate(-rect.x(),-rect.y());
    //view->getDiagram(rect,*painter);

    int resolution = printer->resolution();


    if (scrollview)
      scrollview->getDrawArea()->getSelection()->deselectAll(machine);
    draw->drawStates(machine, painter, 0, 0, 1.0);
    draw->drawTransitions(machine, painter, 0, 0, 1.0);
    if (machine->getDrawITrans())
      draw->drawInitialTransition(machine, machine->getInitialTransition(), painter, 0, 0, 1.0, textrect, FALSE);

    // delete painter and printer before we try to open and fix the file
    delete painter;
    delete printer;
    delete draw;
    
    // modify bounding box from screen to eps resolution.
    rect.setWidth( int(ceil(rect.width() * 72.0/resolution)) );
    rect.setHeight( int(ceil(rect.height() * 72.0/resolution)) );
    exportSuccessful = fixEPS(fileName,rect);
	
    // next painting will most probably be to a different device (i.e. the screen)
    //view->forceUpdateWidgetFontMetrics(0);

    if (scrollview)
      scrollview->getDrawArea()->reset();
    //return exportSuccessful;
}


// code adapted from umbrello
bool ExportEPS::fixEPS(const QString &fileName, QRect rect) const 
{
  using namespace std;

    // now open the file and make a correct eps out of it
    QFile epsfile(fileName);
    if (! epsfile.open(IO_ReadOnly)) {
        return false;
    }
    // read
    QTextStream ts(&epsfile);
    QString fileContent = ts.read();
    epsfile.close();

    // read information
    QRegExp rx("%%BoundingBox:\\s*(-?[\\d\\.:]+)\\s*(-?[\\d\\.:]+)\\s*(-?[\\d\\.:]+)\\s*(-?[\\d\\.:]+)");
    const int pos = rx.search(fileContent);
    if (pos < 0) {
        cerr << "ExportEPS::fixEPS(" << fileName.latin1()
                  << "): cannot find %%BoundingBox" << endl;
        return false;
    }

    // write new content to file
    if (! epsfile.open(IO_WriteOnly | IO_Truncate)) {
        cerr << "ExportEPS::fixEPS(" << fileName.latin1()
                  << "): cannot open file for writing" << endl;
        return false;
    }

    // be careful when rounding (ceil/floor) the BB, these roundings
    // were mainly obtained experimentally...
    const double epsleft = rx.cap(1).toFloat();
    const double epstop = rx.cap(4).toFloat();
    const int left = int(floor(epsleft));
    const int right = int(ceil(epsleft)) + rect.width();
    const int top = int(ceil(epstop)) + 1;
    const int bottom = int(floor(epstop)) - rect.height() + 1;

    // modify content
    fileContent.replace(pos,rx.cap(0).length(),
                        QString("%%BoundingBox: %1 %2 %3 %4").arg(left).arg(bottom).arg(right).arg(top));

    ts << fileContent;
    epsfile.close();

    return true;
}

QString ExportEPS::fileFilter()
{
  return "Encapsulated Postscript (*.eps)";
}

QString ExportEPS::defaultExtension()
{
	return "eps";
}


