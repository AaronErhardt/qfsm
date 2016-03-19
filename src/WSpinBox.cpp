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

#include "WSpinBox.h"


/// Constructor
WSpinBox::WSpinBox(QWidget* parent, const char* name)
	: QDoubleSpinBox(parent)
{
  setRange(0.1, 10);
//  setLineStep(1);
  setSingleStep(1);
//  dval = new QDoubleValidator(0.1, 10.0, 1, this);
//  setValidator(dval);
  setValue(10);
}

/// Destructor
WSpinBox::~WSpinBox()
{
//  delete dval;
}


/// Converts the value @a value to a text string
QString WSpinBox::mapValueToText( int value )
{
  return QString("%1.%2").arg(value/10).arg(value%10);
}

/// Converts the text of this widget into an integer
int WSpinBox::mapTextToValue( bool* ok )
{
  *ok = TRUE;
  return int(text().toFloat()*10);
}


