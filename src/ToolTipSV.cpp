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

#include "ToolTipSV.h"
#include "ScrollView.h"
#include "DrawArea.h"

/// Constructor
ToolTipSV::ToolTipSV(QWidget* parent)
       : QObject(parent)
{
  par=parent;
  QFont f("Courier");
  f.setStyleHint(QFont::TypeWriter);
  f.setFixedPitch(TRUE);
//  setFont(f);
  QToolTip::setFont(f);
}


/// Checks if there is a tooltip for point @a p
void ToolTipSV::maybeTip(const QPoint& p)
{
//  ScrollView* sv = (ScrollView*)parentWidget();
  ScrollView* sv = (ScrollView*)par;
  QPoint offset = sv->mapTo(sv->widget(),QPoint(0,0));
  QRect r;
  QString tiptext;
//  QPoint offset(sv->contentsX(), sv->contentsY());

  r = sv->getDrawArea()->tooltipRect(p+offset, tiptext);

  if (!r.isValid())
    return;

//  tip(r, tiptext);
  QToolTip::showText (p, tiptext, par, r );
}


