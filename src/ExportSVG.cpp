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
#include <qpainter.h>
#include <qfile.h>
#include <q3picture.h>
#include <QSvgGenerator>

#include "ExportSVG.h"
#include "Machine.h"
#include "TransitionInfo.h"
//#include "AppInfo.h"
#include "IOInfo.h"
#include "Draw.h"
#include "ScrollView.h"
#include "DrawArea.h"

//using namespace std;


ExportSVG::ExportSVG(Options* opt)
  	  : Export(opt)
{
}

/// Writes all the relevant data into the tdf file.
void ExportSVG::doExport()
{
  using namespace std;

  // code adapted from Umbrello
  bool exportSuccessful;
  QRect textrect;

  //out->close();


//  Q3Picture pic;
  
  //only to get image size
  QSvgGenerator *pic=new QSvgGenerator();
  pic->setFileName(fileName);

  QPainter *painter = new QPainter(pic);
  Draw* draw = new Draw(scrollview, options);
  QRect rect = draw->getBoundingBox(machine, painter);
  rect.setWidth(rect.width()+10);
  rect.setHeight(rect.height()+10);
  delete painter;
  delete draw;
  delete pic;
  
  //draw image
  pic=new QSvgGenerator();
  pic->setFileName(fileName);
  pic->setSize(rect.size());
  painter = new QPainter(pic);
  draw = new Draw(scrollview, options);


  if (!scrollview)
  {
    delete painter;
    exportSuccessful = FALSE;
  }


  painter->translate(-rect.x(),-rect.y());

  //int resolution = printer->resolution();


  if (scrollview)
    scrollview->getDrawArea()->getSelection()->deselectAll(machine);
  draw->drawStates(machine, painter, 0, 0, 1.0);
  draw->drawTransitions(machine, painter, 0, 0, 1.0);
  if (machine->getDrawITrans())
    draw->drawInitialTransition(machine, machine->getInitialTransition(), painter, 0, 0, 1.0, textrect, FALSE);

  // delete painter and printer before we try to open and fix the file
  delete painter;
  delete draw;
  delete pic;
  
  // modify bounding box from screen to eps resolution.
  //rect.setWidth( int(ceil(rect.width() * 72.0/resolution)) );
  //rect.setHeight( int(ceil(rect.height() * 72.0/resolution)) );
//  pic.setBoundingRect(rect);
  //exportSuccessful = fixSVG(fileName,rect);

// pic.save(fileName,"svg");
	
  if (scrollview)
    scrollview->getDrawArea()->reset();
  //return exportSuccessful;
}


QString ExportSVG::fileFilter()
{
  return "Scalable Vector Graphics (*.svg)";
}

QString ExportSVG::defaultExtension()
{
	return "svg";
}



