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
#include <QPixmap>

#include "ExportPNG.h"
#include "Machine.h"
#include "TransitionInfo.h"
//#include "AppInfo.h"
#include "IOInfo.h"
#include "Draw.h"
#include "ScrollView.h"
#include "DrawArea.h"

//using namespace std;


ExportPNG::ExportPNG(Options* opt)
  	  : Export(opt)
{
}

/// Writes all the relevant data into the png file.
void ExportPNG::doExport()
{
  using namespace std;

  // code adapted from Umbrello
  bool exportSuccessful;
  QRect textrect;

//  out->close();

  machine->calcCanvasSize();
  QPixmap pic(scrollview->widget()->width()+10,scrollview->widget()->height()+10);
  


  pic.fill(Qt::white);
  //only to get image size



  QPainter *painter = new QPainter(&pic);
  Draw* draw = new Draw(scrollview, options);
  QRect rect = draw->getBoundingBox(machine, painter);


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
  
  
  painter->end();
  QPixmap saveMap=pic.copy(0,0,rect.width()+10,rect.height()+10);
  
  saveMap.save(fileName,"PNG");
  // delete painter and printer before we try to open and fix the file
  delete painter;
  delete draw;



	
  if (scrollview)
    scrollview->getDrawArea()->reset();

}


QString ExportPNG::fileFilter()
{
  return "Portable Network Graphics (*.png)";
}

QString ExportPNG::defaultExtension()
{
	return "png";
}



