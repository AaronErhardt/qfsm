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
/*
Qt 4 Port by Rainer Strobel

changed parent class of WSpinBox from QSpinBox to QDoubleSpinBox
and removed setValidator from constructor

replaced setLineStep by setSingleStep

in destructor:
removed delete call
*/

#ifndef WSPINBOX_H
#define WSPINBOX_H

#include <QDoubleSpinBox>
#include <qstring.h>
//#include <qvalidator.h>

/**
 * @class WSpinBox
 * @brief A spinbox for double values with one decimal with a range from 0.1 to 10.0.
 */
//class WSpinBox : public QSpinBox
class WSpinBox :public QDoubleSpinBox
{
  Q_OBJECT
  public:
    WSpinBox(QWidget* parent=0, const char* name=0);
    ~WSpinBox();

    QString mapValueToText( int value );
    int mapTextToValue( bool* ok );

  private:
    /// Double validator
    //QDoubleValidator* dval;
};



#endif
