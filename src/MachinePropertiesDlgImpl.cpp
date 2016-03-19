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

#include "MachinePropertiesDlgImpl.h"
#include <qfontdialog.h>
#include <qradiobutton.h>
#include <q3buttongroup.h>

#include "ListBoxItems.h"


/** 
 *  Constructs a MachinePropertiesDlhImpl which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
MachinePropertiesDlgImpl::MachinePropertiesDlgImpl( QWidget* parent,  const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl )
{
  machinePropertiesDlg.setupUi(this);
  
  lb1 = new LBArrowLine(0); //lbox_arrowtype);
  lb2 = new LBArrowFilled(0); //lbox_arrowtype);
  lb3 = new LBArrowWhite(0); //lbox_arrowtype);
  lb4 = new LBArrowFilledPointed(0); //lbox_arrowtype);
  lb5 = new LBArrowWhitePointed(0); //lbox_arrowtype);

  machinePropertiesDlg.lbox_arrowtype->insertItem(lb1);
  machinePropertiesDlg.lbox_arrowtype->insertItem(lb2);
  machinePropertiesDlg.lbox_arrowtype->insertItem(lb3);
  machinePropertiesDlg.lbox_arrowtype->insertItem(lb4);
  machinePropertiesDlg.lbox_arrowtype->insertItem(lb5);

  machinePropertiesDlg.lbox_arrowtype->setVariableHeight(TRUE);
  
  //connects
/*  QObject::connect(pb_ok, SIGNAL(clicked()), MachinePropertiesDlg, SLOT(accept()));
  QObject::connect(pb_cancel, SIGNAL(clicked()), MachinePropertiesDlg, SLOT(reject()));
  QObject::connect(pb_statefont, SIGNAL(clicked()), MachinePropertiesDlg, SLOT(chooseSFont()));
  QObject::connect(pb_transfont, SIGNAL(clicked()), MachinePropertiesDlg, SLOT(chooseTFont()));
  QObject::connect(rb_binary, SIGNAL(clicked()), MachinePropertiesDlg, SLOT(binaryClicked()));
  QObject::connect(rb_ascii, SIGNAL(clicked()), MachinePropertiesDlg, SLOT(asciiClicked()));
  QObject::connect(rb_text, SIGNAL(clicked()), MachinePropertiesDlg, SLOT(freeTextClicked()));
  QObject::connect(cb_inittrans, SIGNAL(clicked()), MachinePropertiesDlg, SLOT(drawITransClicked()));*/
}

/**  
 *  Destroys the object and frees any allocated resources
 */
MachinePropertiesDlgImpl::~MachinePropertiesDlgImpl()
{
  delete lb1;
  delete lb2;
  delete lb3;
  delete lb4;
  delete lb5;
}

/**
 * Lets you choose a font for the state names.
 * Opens a font dialog box and you can choose a font which will be used to draw
 * the state names.
 */
void MachinePropertiesDlgImpl::chooseSFont()
{
  bool ok;
  QFont f;
  f = QFontDialog::getFont(&ok, sfont, this);

  if (ok)
  {
    machinePropertiesDlg.lb_statefont->setText(f.family());
    machinePropertiesDlg.lb_statefont->setFont(f);
    sfont = f;
  }
}


/**
 * Lets you choose a font for the conditions of the transitions.
 * Opens a font dialog box and you can choose a font which will be used to draw
 * the conditions for the transitions.
 */
void MachinePropertiesDlgImpl::chooseTFont()
{
  bool ok;
  QFont f;
  f = QFontDialog::getFont(&ok, tfont, this);

  if (ok)
  {
    machinePropertiesDlg.lb_transfont->setText(f.family());
    machinePropertiesDlg.lb_transfont->setFont(f);
    tfont = f;
  }
}


/// Returns the type of the machine. 0: Binary / 1: ASCII
int MachinePropertiesDlgImpl::getType()
{ 

  if (machinePropertiesDlg.rb_ascii->isChecked()) 
	return 1;
  if (machinePropertiesDlg.rb_text->isChecked()) 
	return 2;
  else return 0;

//  return bg_type->selectedId();

  /*
  if (rb_binary->isChecked()) 
    return 0; 
  else if 
    return 1; 
    */
}

/// Sets the type of the machine to @a t
void MachinePropertiesDlgImpl::setType(int t)
{
  if (t==1) 
  {
    machinePropertiesDlg.rb_ascii->setChecked(TRUE); 
    asciiClicked();
  }
  else if (t==0)
  {
    machinePropertiesDlg.rb_binary->setChecked(TRUE); 
    binaryClicked();
  }
  else 
  {
    machinePropertiesDlg.rb_text->setChecked(TRUE);
    freeTextClicked();
  }
}

void MachinePropertiesDlgImpl::enableType(bool et=TRUE)
{
  machinePropertiesDlg.bg_type->setEnabled(et);
  
}


/// Called when the 'Binary' radio button is clicked
void MachinePropertiesDlgImpl::binaryClicked()
{
  machinePropertiesDlg.bg_moore->setEnabled(TRUE);
  machinePropertiesDlg.bg_mealy->setEnabled(TRUE);

  
  machinePropertiesDlg.sb_mooreout->setEnabled(TRUE);
  machinePropertiesDlg.sb_mealyin->setEnabled(TRUE);
  machinePropertiesDlg.sb_mealyout->setEnabled(TRUE);
  machinePropertiesDlg.le_mealyin->setEnabled(TRUE);
  machinePropertiesDlg.le_mealyout->setEnabled(TRUE);
  machinePropertiesDlg.le_mooreout->setEnabled(TRUE);
  

}

/// Called when the 'ASCII' radio button is clicked
void MachinePropertiesDlgImpl::asciiClicked()
{
  machinePropertiesDlg.bg_moore->setEnabled(FALSE);
  machinePropertiesDlg.bg_mealy->setEnabled(FALSE);

  saved_numbits=machinePropertiesDlg.sb_mooreout->value();
  saved_numin=machinePropertiesDlg.sb_mealyin->value();
  saved_numout=machinePropertiesDlg.sb_mealyout->value();

  
  machinePropertiesDlg.sb_mealyin->setEnabled(FALSE);
  machinePropertiesDlg.sb_mealyout->setEnabled(FALSE);
  machinePropertiesDlg.sb_mooreout->setEnabled(FALSE);
  machinePropertiesDlg.le_mealyin->setEnabled(FALSE);
  machinePropertiesDlg.le_mealyout->setEnabled(FALSE);
  machinePropertiesDlg.le_mooreout->setEnabled(FALSE);
  

  machinePropertiesDlg.sb_mealyin->setValue(8);
  machinePropertiesDlg.sb_mealyout->setValue(8);
  machinePropertiesDlg.sb_mooreout->setValue(8);
}


void MachinePropertiesDlgImpl::freeTextClicked()
{
  machinePropertiesDlg.bg_moore->setEnabled(FALSE);
  machinePropertiesDlg.bg_mealy->setEnabled(FALSE);

  machinePropertiesDlg.sb_mealyin->setValue(0);
  machinePropertiesDlg.sb_mealyout->setValue(0);
  machinePropertiesDlg.sb_mooreout->setValue(0);
}



void MachinePropertiesDlgImpl::drawITransClicked()
{
}

