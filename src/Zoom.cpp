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

#include "Zoom.h"
#include "Const.h"
#include "DrawArea.h"

/// Constructor
Zoom::Zoom()
{
  scale=1.0;
}

/**
 * Zooms in/out the scrollview.
 * @param sview pointer to scrollview
 * @param p point which will be used as new center
 * @param zoomin if TRUE zooms in otherwise zooms out
 */
void Zoom::zoom(DrawArea* sview, QPoint p, bool zoomin)
{
  double factor = ZOOM_FACTOR;
  int vp_width = sview->parentWidget()->width();
  int vp_height = sview->parentWidget()->height();
  int neww, newh;

  if (!zoomin)
    factor = 1/ZOOM_FACTOR;

  if (scale*factor<MAX_ZOOM && scale*factor>MIN_ZOOM)
  {
    scale*=factor;

    //sview->setUpdatesEnabled(FALSE);
    
    neww = int(sview->width()*factor);
    if (neww<vp_width)
      neww=vp_width;
    newh = int(sview->height()*factor);
    if (newh<vp_height)
      newh=vp_height;
    sview->resize(neww, newh);
//    sview->setContentsPos(int(p.x()*factor-vp_width/2), int(p.y()*factor-vp_height/2));
//    sview->horizontalScrollBar()->setValue(int(p.x()*factor-vp_width/2));
//    sview->verticalScrollBar()->setValue(int(p.y()*factor-vp_height/2));
    /*
    sview->setUpdatesEnabled(TRUE);
    sview->repaint();
    */
  }
}



/**
 * Resets the zoom. 
 * Sets all the zooming parameters to the standard value (100%).
 */
void Zoom::resetZoom(DrawArea* sview)
{

//  sview->resizeContents(CONT_WIDTH, CONT_HEIGHT);
  sview->resize(int(sview->width()/scale),
    int(sview->height()/scale));
  scale = 1.0;
//  sview->setContentsPos(0,0);
//  sview->horizontalScrollBar()->setValue(0);
//  sview->verticalScrollBar()->setValue(0);
  sview->repaint();
}
