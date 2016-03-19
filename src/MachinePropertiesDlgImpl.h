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


#ifndef MACHINEPROPERTIESDLHIMPL_H
#define MACHINEPROPERTIESDLHIMPL_H

#include <qlineedit.h>
#include <qspinbox.h>
#include <q3listbox.h>
#include <qlabel.h>
#include <q3buttongroup.h>
#include <qcheckbox.h>
#include "ui_MachinePropertiesDlg.h"


class LBArrowLine;
class LBArrowFilled;
class LBArrowWhite;
class LBArrowFilledPointed;
class LBArrowWhitePointed;

/**
 * @class MachinePropertiesDlgImpl
 * @brief Dialog to set the properties of the current machine.
 */
class MachinePropertiesDlgImpl : public QDialog
{ 
    Q_OBJECT
    Ui::MachinePropertiesDlg machinePropertiesDlg;

public:
    MachinePropertiesDlgImpl( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WindowFlags fl = 0 );
    ~MachinePropertiesDlgImpl();

    /// Returns the name of the machine.
    QString getName() { return machinePropertiesDlg.le_name->text(); };
    /// Sets the name of the machine.
    void setName(QString n) { machinePropertiesDlg.le_name->setText(n); };
    /// Returns the version of the machine.
    QString getVersion() { return machinePropertiesDlg.le_version->text(); };
    /// Sets the version of the machine.
    void setVersion(QString v) { machinePropertiesDlg.le_version->setText(v); };
    int getType();
    void setType(int t);
    void enableType(bool et);

    /// Returns the number of bits the states are coded with, i.e. the number of moore outputs
    int getNumMooreOutputs() { return machinePropertiesDlg.sb_mooreout->value(); };
    /// Sets the number of bits the states are coded with, i.e. the number of moore outputs.
    void setNumMooreOutputs(int num) { machinePropertiesDlg.sb_mooreout->setValue(num); saved_numbits=num; };
    /// Returns the names of the moore output bits.
    QString getMooreOutputNames() { return machinePropertiesDlg.le_mooreout->text(); };
    /// Sets the names of the moore output bits.
    void setMooreOutputNames(QString s) { machinePropertiesDlg.le_mooreout->setText(s); };

    /// Returns the number of mealy input bits
    int getNumInputs() { return machinePropertiesDlg.sb_mealyin->value(); };
    /// Sets the number of mealy input bits
    void setNumInputs(int num) { machinePropertiesDlg.sb_mealyin->setValue(num); saved_numin=num; };
    /// Returns the names of mealy input bits.
    QString getMealyInputNames() { return machinePropertiesDlg.le_mealyin->text(); };
    /// Sets the names of mealy input bits.
    void setMealyInputNames(QString s) { machinePropertiesDlg.le_mealyin->setText(s); };

    /// Returns the number of mealy output bits
    int getNumOutputs() { return machinePropertiesDlg.sb_mealyout->value(); };
    /// Sets the number of mealy output bits
    void setNumOutputs(int num) { machinePropertiesDlg.sb_mealyout->setValue(num); saved_numout=num; };
    /// Returns the names of mealy output bits.
    QString getMealyOutputNames() { return machinePropertiesDlg.le_mealyout->text(); };
    /// Sets the names of mealy output bits.
    void setMealyOutputNames(QString s) { machinePropertiesDlg.le_mealyout->setText(s); };
    
    /// Returns the font used for the state names
    QFont getSFont() { return sfont; };
    /// Sets the font used for the state names
    void setSFont(QFont f) { sfont = f; machinePropertiesDlg.lb_statefont->setText(f.family()); 
      machinePropertiesDlg.lb_statefont->setFont(f); };
    /// Returns the font used for the transition names
    QFont getTFont() { return tfont; };
    /// Sets the font used for the transition names
    void setTFont(QFont f) { tfont = f; machinePropertiesDlg.lb_transfont->setText(f.family());
      machinePropertiesDlg.lb_transfont->setFont(f); };
    /// Returns the arrow type used for the transitions
      int getArrowType() { return machinePropertiesDlg.lbox_arrowtype->currentItem(); };
    /// Sets the arrow type used for the transitions
      void setArrowType(int at) { machinePropertiesDlg.lbox_arrowtype->setCurrentItem(at); };
          /// Returns the string of the desription field
      QString getDescription() { return machinePropertiesDlg.te_description->text(); };
    /// Sets the string of the description field
      void setAuthor(QString s) { machinePropertiesDlg.le_author->setText(s); };
          /// Returns the string of the desription field
      QString getAuthor() { return machinePropertiesDlg.le_author->text(); };
    /// Sets the string of the description field
      void setDescription(QString s) { machinePropertiesDlg.te_description->setText(s); };

      bool getDrawITrans() { return machinePropertiesDlg.cb_inittrans->isChecked(); };
      void setDrawITrans(bool di) { machinePropertiesDlg.cb_inittrans->setChecked(di); };

    /// Selects first field in dialog and sets the focus.
      void selectFirst() { machinePropertiesDlg.le_name->selectAll(); machinePropertiesDlg.le_name->setFocus(); };

  private:
    /// Line arrow list box item 
    LBArrowLine* lb1;
    /// Filled arrow list box item 
    LBArrowFilled* lb2;
    /// White arrow list box item 
    LBArrowWhite* lb3;
    /// Filled pointed arrow list box item 
    LBArrowFilledPointed* lb4;
    /// White pointed arrow list box item 
    LBArrowWhitePointed* lb5;

    /// State font
    QFont sfont;
    /// Transition font
    QFont tfont;

    /// Previous number of moore output bits
    int saved_numbits;
    /// Previous number of input bits
    int saved_numin;
    /// Previous number of output bits
    int saved_numout;

  public slots:
    void chooseSFont();
    void chooseTFont();
    void binaryClicked();
    void asciiClicked();
    void freeTextClicked();
    void drawITransClicked();
};

#endif // MACHINEPROPERTIESDLHIMPL_H
