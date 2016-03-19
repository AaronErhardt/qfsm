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

in method getType:
changed the code which checks the current type so that it works
under windows
*/

#ifndef TRANSITIONPROPERTIESDLGIMPL_H
#define TRANSITIONPROPERTIESDLGIMPL_H

#include <qlineedit.h>
#include <q3textedit.h>
#include <qcheckbox.h>
#include "ui_TransitionPropertiesDlg.h"

/**
 * @class TransitionPropertiesDlgImpl
 * @brief Dialog for the properties of a transition.
 */
class TransitionPropertiesDlgImpl : public QDialog
{ 
    Q_OBJECT
        
        Ui::TransitionPropertiesDlg transitionPropertiesDlg;

public:
    TransitionPropertiesDlgImpl( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~TransitionPropertiesDlgImpl();

    QString getInputs();// { return transitionPropertiesDlg.le_input->text(); };
    void setInputs(QString s); // { transitionPropertiesDlg.le_input->setText(s); };
    /// Returns the output condition string
    QString getOutputs() { return transitionPropertiesDlg.le_output->text(); };
    /// Sets the outputs condition string
    void setOutputs(QString s) { transitionPropertiesDlg.le_output->setText(s); };
    /// Returns the string of the desription field
    QString getDescription() { return transitionPropertiesDlg.te_description->text(); };
    /// Sets the string of the description field
    void setDescription(QString s) { transitionPropertiesDlg.te_description->setText(s); };
    /// Returns the state of the 'invert' checkbox
    bool getInvert() { return transitionPropertiesDlg.cb_invert->isChecked(); };
    /// Sets the state of the 'invert' checkbox
    void setInvert(bool i) { transitionPropertiesDlg.cb_invert->setChecked(i); };
    /// Returns the state of the 'any input' checkbox
    bool getAnyInput() { return transitionPropertiesDlg.cb_any->isChecked(); };
    /// Sets the state of the 'any input' checkbox
    void setAnyInput(bool i) { transitionPropertiesDlg.cb_any->setChecked(i); };
    /// Returns the state of the 'default transition' checkbox
    bool getDefaultTransition() { return transitionPropertiesDlg.cb_default->isChecked(); };
    /// Sets the state of the 'default transition' checkbox
    void setDefaultTransition(bool i) { transitionPropertiesDlg.cb_default->setChecked(i); };


    int getType();
    void setType(int t);
    /// Sets the maximum number of bits allowed for the inputs and outputs
    void setBinMaxLength(int in, int out) { binmax_in=in; binmax_out=out; };

    /// Selects first field in dialog and sets the focus
    void selectFirst() { transitionPropertiesDlg.le_input->selectAll(); transitionPropertiesDlg.le_input->setFocus(); };

    /// Sets the maximum length for the inputs field
    void setInputMaxLength(int l) { transitionPropertiesDlg.le_input->setMaxLength(l); };
    /// Sets the maximum length for the outputs field
    void setOutputMaxLength(int l) { transitionPropertiesDlg.le_output->setMaxLength(l); };

    void resetFields();

  public slots:
    void validate();
    void binaryClicked();
    void asciiClicked();
    void freeTextClicked();
    void anyClicked();
    void defaultClicked();
    void invertClicked();

  private:
    /// Maximum length of the inputs (in bits)
    int binmax_in;
    /// Maximum length of the outputs (in bits)
    int binmax_out;
};

#endif // TRANSITIONPROPERTIESDLGIMPL_H
