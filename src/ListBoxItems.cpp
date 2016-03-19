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

#include <math.h>
#include <q3listbox.h>
#include <qpen.h>
#include <qpainter.h>
#include <qstyle.h>
//Added by qt3to4:
#include <Q3PointArray>
#include <QStyle>
#include <QStyleOptionFocusRect>

#include "ListBoxItems.h"
#include "Const.h"


/** 
 * Constructor.
 * Intialises the list box item for the listbox @a lb.
 */
LBArrowLine::LBArrowLine(Q3ListBox* lb)
	   : Q3ListBoxItem(lb)
{
  h = 30;
  w = 30;
  setCustomHighlighting(TRUE);
}


/// Returns the height of the listbox item
int LBArrowLine::height(const Q3ListBox* ) const
{
  return 30;
}

/// Returns the width of the listbox item
int LBArrowLine::width(const Q3ListBox* ) const
{
  return 30;
}

/// Draws the listbox item
void LBArrowLine::paint(QPainter* p)
{
  QPen pen(QColor(0,0,0), 1);
  QPen white(QColor(255,255,255), 1);
  int wi, le;
  int ofx, ofy;
  QRect r(0, 0, listBox()->viewport()->width(), 30);
//  r = listBox()->itemRect(this);


  wi = int(15 * sin(ARROW_ANGLE/180 * PI));
  le = int(15 * cos(ARROW_ANGLE/180 * PI));

  p->setPen(pen);

  if (selected())
  {
    p->eraseRect(r);
//    listBox()->style().drawPrimitive(QStyle::PE_FocusRect, p, r, listBox()->colorGroup()); //,

      QStyleOptionFocusRect option;
      option.initFrom(listBox());
      option.backgroundColor = listBox()->palette().color(QPalette::Background);

      listBox()->style()->drawPrimitive(QStyle::PE_FrameFocusRect, &option, p, listBox());
  }

  h = 2*wi;
  w = le+20;
  ofx = (r.width()-w)/2;
  ofy = (r.height()-h)/2;

//  p->moveTo(ofx, ofy+wi);
//  p->lineTo(ofx+le+20, ofy+wi);
  p->drawLine(ofx, ofy+wi,ofx+le+20, ofy+wi);

//  p->moveTo(ofx+20, ofy);
//  p->lineTo(ofx+le+20, ofy+wi);
//  p->lineTo(ofx+20, ofy + 2*wi);
  p->drawLine(ofx+20, ofy,ofx+le+20, ofy+wi);
  p->drawLine(ofx+le+20, ofy+wi,ofx+20, ofy + 2*wi);

}







/**
 * Constructor.
 * Initialises the listbox item for the listbox @a lb.
 */
LBArrowFilled::LBArrowFilled(Q3ListBox* lb)
	   : Q3ListBoxItem(lb)
{
  h = 30;
  w = 30;
  setCustomHighlighting(TRUE);
}


/// Returns the height of the listbox
int LBArrowFilled::height(const Q3ListBox* ) const
{
  return 30;
}

/// Returns the width of the listbox
int LBArrowFilled::width(const Q3ListBox* ) const
{
  return 30;
}

/// Draws the listbox item.
void LBArrowFilled::paint(QPainter* p)
{
  QPen pen(QColor(0,0,0), 1);
  QPen white(QColor(255,255,255), 1);
  QBrush br(QColor(0,0,0));
  QBrush brwhite(QColor(255,255,255));
  int wi, le;
  int ofx, ofy;
  QRect r(0, 0, listBox()->viewport()->width(), 30);
  Q3PointArray pa(3);
//  r = listBox()->itemRect(this);


  wi = int(15 * sin(ARROW_ANGLE/180 * PI));
  le = int(15 * cos(ARROW_ANGLE/180 * PI));


  p->setPen(pen);
  p->setBrush(br);

  if (selected())
 //   p->eraseRect(r);

//  if (current())
  {
    p->eraseRect(r);
    //p->setPen(white);
 //   listBox()->style()->drawPrimitive(QStyle::PE_FrameFocusRect, p, r, listBox()->colorGroup());
    
    QStyleOptionFocusRect option;
    option.initFrom(listBox());
    option.backgroundColor = listBox()->palette().color(QPalette::Background);

    listBox()->style()->drawPrimitive(QStyle::PE_FrameFocusRect, &option, p, listBox());

//    listBox()->style().drawFocusRect(p, r, listBox()->colorGroup(),
//      &p->backgroundColor(), TRUE);
  }

  h = 2*wi;
  w = le+20;
  ofx = (r.width()-w)/2;
  ofy = (r.height()-h)/2;

//  p->moveTo(ofx, ofy+wi);
//  p->lineTo(ofx+le+20, ofy+wi);
  p->drawLine(ofx, ofy+wi,ofx+le+20, ofy+wi);

  pa.setPoints(3, ofx+20, ofy, ofx+le+20, ofy+wi, ofx+20, ofy+2*wi);

  /*
  if (selected())
    p->setBrush(brwhite);
    */
  p->drawPolygon(pa);
}





/**
 * Constructor.
 * Initialises the listbox item for the listbox @a lb.
 */
LBArrowWhite::LBArrowWhite(Q3ListBox* lb)
	   : Q3ListBoxItem(lb)
{
  h = 30;
  w = 30;
  setCustomHighlighting(TRUE);
}


/// Returns the height of the listbox
int LBArrowWhite::height(const Q3ListBox* ) const
{
  return 30;
}

/// Returns the width of the listbox
int LBArrowWhite::width(const Q3ListBox* ) const
{
  return 30;
}

/// Draws the listbox item.
void LBArrowWhite::paint(QPainter* p)
{
  QPen pen(QColor(0,0,0), 1);
  QPen white(QColor(255,255,255), 1);
  QBrush br(QColor(0,0,0));
  QBrush brwhite(QColor(255,255,255));
  int wi, le;
  int ofx, ofy;
  QRect r(0, 0, listBox()->viewport()->width(), 30);
  Q3PointArray pa(3);
//  r = listBox()->itemRect(this);


  wi = int(15 * sin(ARROW_ANGLE/180 * PI));
  le = int(15 * cos(ARROW_ANGLE/180 * PI));


  p->setPen(pen);
  p->setBrush(brwhite);

  if (selected())
 //   p->eraseRect(r);

//  if (current())
  {
    p->eraseRect(r);
    //p->setPen(white);
//    listBox()->style()->drawPrimitive(QStyle::PE_FrameFocusRect, p, r, listBox()->colorGroup());
    
    QStyleOptionFocusRect option;
    option.initFrom(listBox());
    option.backgroundColor = listBox()->palette().color(QPalette::Background);

    listBox()->style()->drawPrimitive(QStyle::PE_FrameFocusRect, &option, p, listBox());

//    listBox()->style().drawFocusRect(p, r, listBox()->colorGroup(),
//      &p->backgroundColor(), TRUE);
  }

  h = 2*wi;
  w = le+20;
  ofx = (r.width()-w)/2;
  ofy = (r.height()-h)/2;

//  p->moveTo(ofx, ofy+wi);
//  p->lineTo(ofx+le+20, ofy+wi);
  p->drawLine(ofx, ofy+wi,ofx+le+20, ofy+wi);

  pa.setPoints(3, ofx+20, ofy, ofx+le+20, ofy+wi, ofx+20, ofy+2*wi);

  /*
  if (selected())
    p->setBrush(br);
    */
  p->drawPolygon(pa);
}






/**
 * Constructor.
 * Initialises the listbox item for the listbox @a lb.
 */
LBArrowFilledPointed::LBArrowFilledPointed(Q3ListBox* lb)
	   : Q3ListBoxItem(lb)
{
  h = 30;
  w = 30;
  setCustomHighlighting(TRUE);
}


/// Returns the height of the listbox
int LBArrowFilledPointed::height(const Q3ListBox* ) const
{
  return 30;
}

/// Returns the width of the listbox
int LBArrowFilledPointed::width(const Q3ListBox* ) const
{
  return 30;
}

/// Draws the listbox item.
void LBArrowFilledPointed::paint(QPainter* p)
{
  QPen pen(QColor(0,0,0), 1);
  QPen white(QColor(255,255,255), 1);
  QBrush br(QColor(0,0,0));
  QBrush brwhite(QColor(255,255,255));
  int wi, le;
  int ofx, ofy;
  QRect r(0, 0, listBox()->viewport()->width(), 30);
  Q3PointArray pa(4);
//  r = listBox()->itemRect(this);


  wi = int(15 * sin(ARROW_ANGLE/180 * PI));
  le = int(15 * cos(ARROW_ANGLE/180 * PI));


  p->setPen(pen);
  p->setBrush(br);

  if (selected())
 //   p->eraseRect(r);

//  if (current())
  {
    p->eraseRect(r);
    //p->setPen(white);
 //   listBox()->style()->drawPrimitive(QStyle::PE_FrameFocusRect, p, r, listBox()->colorGroup()); 
    
    QStyleOptionFocusRect option;
    option.initFrom(listBox());
    option.backgroundColor = listBox()->palette().color(QPalette::Background);

    listBox()->style()->drawPrimitive(QStyle::PE_FrameFocusRect, &option, p, listBox());

//    listBox()->style().drawFocusRect(p, r, listBox()->colorGroup(),
//      &p->backgroundColor(), TRUE);
  }

  h = 2*wi;
  w = le+20;
  ofx = (r.width()-w)/2;
  ofy = (r.height()-h)/2;

//  p->moveTo(ofx, ofy+wi);
//  p->lineTo(ofx+le+20, ofy+wi);
  p->drawLine(ofx, ofy+wi,ofx+le+20, ofy+wi);

  pa.setPoints(4, ofx+20, ofy, ofx+le+20, ofy+wi, ofx+20, ofy+2*wi, ofx+20+int(0.33*le), ofy+wi); 

  /*
  if (selected())
    p->setBrush(br);
    */
  p->drawPolygon(pa);
}






/**
 * Constructor.
 * Initialises the listbox item for the listbox @a lb.
 */
LBArrowWhitePointed::LBArrowWhitePointed(Q3ListBox* lb)
	   : Q3ListBoxItem(lb)
{
  h = 30;
  w = 30;
  setCustomHighlighting(TRUE);
}


/// Returns the height of the listbox
int LBArrowWhitePointed::height(const Q3ListBox* ) const
{
  return 30;
}

/// Returns the width of the listbox
int LBArrowWhitePointed::width(const Q3ListBox* ) const
{
  return 30;
}

/// Draws the listbox item.
void LBArrowWhitePointed::paint(QPainter* p)
{
  QPen pen(QColor(0,0,0), 1);
  QPen white(QColor(255,255,255), 1);
  QBrush br(QColor(0,0,0));
  QBrush brwhite(QColor(255,255,255));
  int wi, le;
  int ofx, ofy;
  QRect r(0, 0, listBox()->viewport()->width(), 30);
  Q3PointArray pa(4);
//  r = listBox()->itemRect(this);


  wi = int(15 * sin(ARROW_ANGLE/180 * PI));
  le = int(15 * cos(ARROW_ANGLE/180 * PI));


  p->setPen(pen);
  p->setBrush(brwhite);

  if (selected())
 //   p->eraseRect(r);

//  if (current())
  {
    p->eraseRect(r);
    //p->setPen(white);
//    listBox()->style()->drawPrimitive(QStyle::PE_FrameFocusRect, p, r, listBox()->colorGroup()); 
    
    QStyleOptionFocusRect option;
    option.initFrom(listBox());
    option.backgroundColor = listBox()->palette().color(QPalette::Background);

    listBox()->style()->drawPrimitive(QStyle::PE_FrameFocusRect, &option, p, listBox());

//    listBox()->style().drawFocusRect(p, r, listBox()->colorGroup(),
//      &p->backgroundColor(), TRUE);
  }

  h = 2*wi;
  w = le+20;
  ofx = (r.width()-w)/2;
  ofy = (r.height()-h)/2;

//  p->moveTo(ofx, ofy+wi);
//  p->lineTo(ofx+le+20, ofy+wi);
  p->drawLine(ofx, ofy+wi,ofx+le+20, ofy+wi);

  pa.setPoints(4, ofx+20, ofy, ofx+le+20, ofy+wi, ofx+20, ofy+2*wi, ofx+20+int(0.33*le), ofy+wi); 

  /*
  if (selected())
    p->setBrush(br);
    */
  p->drawPolygon(pa);
}




