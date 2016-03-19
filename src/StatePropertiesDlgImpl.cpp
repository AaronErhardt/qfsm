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

#include <qcolordialog.h>
#include <qcolor.h>

#include "StatePropertiesDlgImpl.h"
#include "Error.h"
#include "State.h"
#include "MainWindow.h"
#include "Project.h"
#include "Machine.h"
#include "Convert.h"
#include "TransitionInfo.h"
#include "Utils.h"


/** 
 *  Constructs a StatePropertiesDlgImpl which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
StatePropertiesDlgImpl::StatePropertiesDlgImpl( QWidget* parent,  const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl )
{
  statePropertiesDlg.setupUi(this);

  valRadius = new QIntValidator(5, 500, this);
  valLineWidth = new QIntValidator(1, 10, this);

  statePropertiesDlg.le_radius->setValidator(valRadius);
  statePropertiesDlg.le_linewidth->setValidator(valLineWidth);
  statePropertiesDlg.lb_colorpreview->setAutoFillBackground(true);
}

/**  
 *  Destroys the object and frees any allocated resources
 */
StatePropertiesDlgImpl::~StatePropertiesDlgImpl()
{
  delete valRadius;
  delete valLineWidth;
}


/**
 * Validates the state properties and displays an error box when invalid.
 * Displays and error box if no name is given, if the code is not in binary
 * format, if the values are out of range or if the code already exists
 */
void StatePropertiesDlgImpl::validate()
{
   Error err;
   QString r,l,c;
   int icode;
   Machine* m = main->project->machine;
   Convert conv;
   int mtype = m->getType();

   r = statePropertiesDlg.le_radius->text();
   l = statePropertiesDlg.le_linewidth->text();
   c = statePropertiesDlg.le_code->text();

   if (mtype==Binary)
     icode = conv.binStrToInt(c);
   else
     icode = c.toInt();

   int pos=0;

   if (statePropertiesDlg.le_name->text().isEmpty())
     err.info(tr("You must specify a name."));
   else if (!State::codeValid(m->getType(), c))
     err.info(tr("Code is not in binary format."));
   else if (!State::mooreOutputValid(m->getType(), statePropertiesDlg.le_mooreoutputs->text()))
     err.info(tr("Moore outputs are not in the correct format."));
   //else if (!Utils::binStringValid(le_mooreoutputs->text()))
     //err.info(tr("Moore outputs are not in binary format."));
   else if (valRadius->validate(r,pos)!=QValidator::Acceptable)
     err.info(tr("Radius out of range.")); 
   else if (valLineWidth->validate(l,pos)!=QValidator::Acceptable)
     err.info(tr("Linewidth out of range."));
   else
     accept();
   
}


/**
 * Lets you choose a foreground color for the state
 */
void StatePropertiesDlgImpl::chooseFGColor()
{
  QColor c;
  c = QColorDialog::getColor(color, this);

  if (c.isValid())
  {
    //statePropertiesDlg.lb_colorpreview->setBackgroundColor(c);
    QPalette palette;
    palette.setColor(statePropertiesDlg.lb_colorpreview->backgroundRole(), c);
    statePropertiesDlg.lb_colorpreview->setPalette(palette);
    color = c;
  }
}
