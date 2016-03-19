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

#include <qradiobutton.h>
#include <q3buttongroup.h>

#include "TransitionPropertiesDlgImpl.h"

#include "Transition.h"
#include "Error.h"
#include "TransitionInfo.h"
#include "Const.h"


/** 
 *  Constructs a TransitionPropertiesDlgImpl which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
TransitionPropertiesDlgImpl::TransitionPropertiesDlgImpl( QWidget* parent,  const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl )
{
  transitionPropertiesDlg.setupUi(this);

  connect(transitionPropertiesDlg.rb_ascii,SIGNAL(clicked()),this,SLOT(asciiClicked()));
  connect(transitionPropertiesDlg.rb_bin,SIGNAL(clicked()),this,SLOT(binaryClicked()));
  connect(transitionPropertiesDlg.rb_text,SIGNAL(clicked()),this,SLOT(freeTextClicked()));

}

/**  
 *  Destroys the object and frees any allocated resources
 */
TransitionPropertiesDlgImpl::~TransitionPropertiesDlgImpl()
{
}


/// Validates the strings entered as the transition inputs and outputs
void TransitionPropertiesDlgImpl::validate()
{
  Error err;
  QString in, out;
  int type;
  int cres;

//  in = transitionPropertiesDlg.le_input->text();
  in = getInputs();
  out = transitionPropertiesDlg.le_output->text();
  type = getType();

  cres = Transition::conditionValid(type, in);
  if (cres)
  {
    switch (cres)
    {
      case 1:
	err.info(tr("Input condition is not in binary format."));
	break;
      case 2:
	err.info(tr("Incomplete escape sequence."));
	break;
      case 3:
	err.info(tr("'-' has to define a range."));
	break;
      case 4:
	err.info(tr("Output must be only one character."));
	break;
      case 5:
	err.info(tr("Invalid escape sequence.\nThe format is \\0xx, where xx is a\nhexadecimal value"));
        break;
      default:
	err.info(tr("Input condition is not in the correct format."));
	break;
    }
    return;
  }
  else
  {
    cres = Transition::conditionValid(type, out, FALSE);
    if (cres)
    {
      switch (cres)
      {
	case 1:
	  err.info(tr("Output condition is not in binary format."));
	  break;
	case 2:
	  err.info(tr("Incomplete escape sequence."));
	  break;
	case 3:
	  err.info(tr("'-' has to define a range."));
	  break;
	case 4:
	  err.info(tr("Output must be only one character."));
	  break;
	case 5:
	  err.info(tr("Invalid escape sequence.\nThe format is \\0xx, where xx is a\nhexadecimal value"));
	  break;
	default:
	  err.info(tr("Output condition is not in the correct format."));
	  break;
      }
      return;
    }
    else
      accept();
  }
}

/// Returns the type of the transition
int TransitionPropertiesDlgImpl::getType()
{
  if (transitionPropertiesDlg.rb_ascii->isChecked()) 
	return 1;
  if (transitionPropertiesDlg.rb_text->isChecked()) 
	return 2;
  else return 0;

//  return bg_type->selectedId();

  /*
  if (rb_ascii->isChecked())
    return Ascii;
  else
    return Binary;
    */
}

void TransitionPropertiesDlgImpl::resetFields()
{
  transitionPropertiesDlg.cb_default->setEnabled(FALSE);
  transitionPropertiesDlg.cb_invert->setEnabled(FALSE);
  transitionPropertiesDlg.cb_any->setEnabled(FALSE);
  transitionPropertiesDlg.le_input->setEnabled(TRUE);
  transitionPropertiesDlg.le_input->clear();
  transitionPropertiesDlg.le_output->clear();
}


/// Sets the type of the transition
void TransitionPropertiesDlgImpl::setType(int t)
{
  //qDebug("setType %d", t);
  if (t==Binary)
  {
    transitionPropertiesDlg.rb_bin->setEnabled(TRUE);
    transitionPropertiesDlg.rb_ascii->setEnabled(TRUE);
    transitionPropertiesDlg.rb_text->setEnabled(FALSE);
    transitionPropertiesDlg.rb_bin->setChecked(TRUE);
    binaryClicked();
  }
  if (t==Ascii)
  {
    transitionPropertiesDlg.rb_bin->setEnabled(TRUE);
    transitionPropertiesDlg.rb_ascii->setEnabled(TRUE);
    transitionPropertiesDlg.rb_text->setEnabled(FALSE);

    transitionPropertiesDlg.rb_ascii->setChecked(TRUE);
    //transitionPropertiesDlg.cb_default->setEnabled(TRUE); // not needed - this is done in asciiClicked() below
    asciiClicked();
  }
  else if (t==Text)
  {
    transitionPropertiesDlg.rb_bin->setEnabled(FALSE);
    transitionPropertiesDlg.rb_ascii->setEnabled(FALSE);
    transitionPropertiesDlg.rb_text->setEnabled(TRUE);

    transitionPropertiesDlg.rb_text->setChecked(TRUE);
    /*
     // not needed - this is done in freeTextClicked() below
    transitionPropertiesDlg.cb_default->setEnabled(false);
    transitionPropertiesDlg.cb_default->setChecked(false);
    transitionPropertiesDlg.cb_any->setEnabled(false);
    transitionPropertiesDlg.cb_any->setChecked(false);
    transitionPropertiesDlg.cb_invert->setEnabled(false);
    transitionPropertiesDlg.cb_invert->setChecked(false);
    */
    freeTextClicked();
  }
  if (transitionPropertiesDlg.cb_default->isEnabled())
    defaultClicked();
  if (transitionPropertiesDlg.cb_any->isEnabled())
    anyClicked();
  if (transitionPropertiesDlg.cb_invert->isEnabled())
    invertClicked();
}


/// Called when the 'Binary' button is clicked
void TransitionPropertiesDlgImpl::binaryClicked()
{
  //qDebug("binaryClicked()");
  transitionPropertiesDlg.le_input->setMaxLength(binmax_in);
  transitionPropertiesDlg.le_output->setMaxLength(binmax_out);

  transitionPropertiesDlg.cb_default->setEnabled(true);
  transitionPropertiesDlg.cb_any->setEnabled(true);
  transitionPropertiesDlg.cb_invert->setEnabled(true);

  if(transitionPropertiesDlg.cb_default->isChecked())
  {
    transitionPropertiesDlg.le_input->setEnabled(false);
    transitionPropertiesDlg.cb_any->setEnabled(false);
    transitionPropertiesDlg.cb_invert->setEnabled(false);

  }
  else if(transitionPropertiesDlg.cb_any->isChecked())
  {
    transitionPropertiesDlg.cb_default->setEnabled(false);
    transitionPropertiesDlg.le_input->setEnabled(false);
    transitionPropertiesDlg.cb_invert->setEnabled(false);
  }
  else if(transitionPropertiesDlg.cb_invert->isChecked())
  {
    transitionPropertiesDlg.cb_default->setEnabled(false);
    transitionPropertiesDlg.cb_any->setEnabled(false);
  }

}

/// Called when the 'ASCII' button is clicked
void TransitionPropertiesDlgImpl::asciiClicked()
{
  //qDebug("ASCIIClicked()");
  transitionPropertiesDlg.le_input->setMaxLength(MAX_ASCII_INPUTLENGTH);
  transitionPropertiesDlg.le_output->setMaxLength(MAX_ASCII_OUTPUTLENGTH);

  transitionPropertiesDlg.cb_default->setEnabled(true);
  transitionPropertiesDlg.cb_any->setEnabled(true);
  transitionPropertiesDlg.cb_invert->setEnabled(true);

  if(transitionPropertiesDlg.cb_default->isChecked())
  {
    transitionPropertiesDlg.le_input->setEnabled(false);
    transitionPropertiesDlg.cb_any->setEnabled(false);
    transitionPropertiesDlg.cb_invert->setEnabled(false);

  }
  else if(transitionPropertiesDlg.cb_any->isChecked())
  {
    transitionPropertiesDlg.cb_default->setEnabled(false);
    transitionPropertiesDlg.le_input->setEnabled(false);
    transitionPropertiesDlg.cb_invert->setEnabled(false);
  }
  else if(transitionPropertiesDlg.cb_invert->isChecked())
  {
    transitionPropertiesDlg.cb_default->setEnabled(false);
    transitionPropertiesDlg.cb_any->setEnabled(false);
  }


}

void TransitionPropertiesDlgImpl::freeTextClicked()
{
  //qDebug("freeTextClicked()");
  transitionPropertiesDlg.le_input->setMaxLength(MAX_TEXT_INPUTLENGTH);
  transitionPropertiesDlg.le_output->setMaxLength(MAX_TEXT_OUTPUTLENGTH);

  transitionPropertiesDlg.cb_default->setEnabled(true);
  transitionPropertiesDlg.cb_any->setEnabled(false);
  transitionPropertiesDlg.cb_any->setChecked(false);
  transitionPropertiesDlg.cb_invert->setEnabled(false);
  transitionPropertiesDlg.cb_invert->setChecked(false);
    /*
  if (!cb_any->isChecked() && !cb_invert->isChecked())
    cb_default->setEnabled(TRUE);
  else
    cb_default->setEnabled(FALSE);
  defaultClicked();
  anyClicked();
  invertClicked();
  */
  if(transitionPropertiesDlg.cb_default->isChecked())
  {
    transitionPropertiesDlg.le_input->setEnabled(false);
  }
  if (transitionPropertiesDlg.cb_default->isEnabled())
    defaultClicked();
  /* 
  // no ANY or INVERT in text conditions
  if (transitionPropertiesDlg.cb_any->isEnabled())
    anyClicked();
  if (transitionPropertiesDlg.cb_invert->isEnabled())
    invertClicked();
    */
}


void TransitionPropertiesDlgImpl::anyClicked()
{
  if (transitionPropertiesDlg.cb_any->isChecked())
  {
    transitionPropertiesDlg.cb_invert->setEnabled(FALSE);
    transitionPropertiesDlg.cb_default->setEnabled(FALSE);
    transitionPropertiesDlg.le_input->setEnabled(FALSE);
  }
  else
  {
    transitionPropertiesDlg.cb_invert->setEnabled(TRUE);
    transitionPropertiesDlg.cb_default->setEnabled(TRUE);
    transitionPropertiesDlg.le_input->setEnabled(TRUE);
  }
}

void TransitionPropertiesDlgImpl::defaultClicked()
{
  if (transitionPropertiesDlg.cb_default->isChecked())
  {
    transitionPropertiesDlg.cb_invert->setEnabled(FALSE);
    transitionPropertiesDlg.cb_any->setEnabled(FALSE);
    transitionPropertiesDlg.le_input->setEnabled(FALSE);
    transitionPropertiesDlg.le_input->setText("");
  }
  else
  {
    if (getType()!=Text)
    {
      transitionPropertiesDlg.cb_invert->setEnabled(TRUE);
      transitionPropertiesDlg.cb_any->setEnabled(TRUE);
    }
    transitionPropertiesDlg.le_input->setEnabled(TRUE);
  }
}

void TransitionPropertiesDlgImpl::invertClicked()
{
  if (transitionPropertiesDlg.cb_invert->isChecked())
  {
    transitionPropertiesDlg.le_input->setEnabled(TRUE);
    transitionPropertiesDlg.cb_default->setEnabled(FALSE);
    transitionPropertiesDlg.cb_any->setEnabled(FALSE);
  }
  else
  {
    transitionPropertiesDlg.cb_default->setEnabled(TRUE);
    transitionPropertiesDlg.cb_any->setEnabled(TRUE);
    transitionPropertiesDlg.cb_default->setEnabled(true);
  }
}


/// Returns the input condition string
QString TransitionPropertiesDlgImpl::getInputs()
{
  QString inputs=transitionPropertiesDlg.le_input->text().simplified();
  inputs.replace(" | ","|");
  inputs.replace(" |","|");
  inputs.replace("| ","|");
  return inputs;
}

/// Sets the input condition string
void TransitionPropertiesDlgImpl::setInputs(QString s)
{
  transitionPropertiesDlg.le_input->setText(s.replace("|"," | "));
}


