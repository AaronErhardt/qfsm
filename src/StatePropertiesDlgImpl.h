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

#ifndef STATEPROPERTIESDLGIMPL_H
#define STATEPROPERTIESDLGIMPL_H

#include <qvalidator.h>
#include <qlineedit.h>
#include <q3textedit.h>
#include <qlabel.h>
#include <qcolor.h>

#include "ui_StatePropertiesDlg.h"
#include "GState.h"

class MainWindow;


/**
 * @class StatePropertiesDlgImpl
 * @brief Dialog to change the properties of a state
 */
class StatePropertiesDlgImpl : public QDialog
{ 
    Q_OBJECT
        
        Ui::StatePropertiesDlg statePropertiesDlg;

public:
    StatePropertiesDlgImpl( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~StatePropertiesDlgImpl();

    /// Dialog mode
    enum DialogMode { StateAdd, StateEdit };

    /// Returns the string of the name field 
    QString getName() {return statePropertiesDlg.le_name->text(); };
    /// Sets the string of the name field
    void setName(const QString& s) {statePropertiesDlg.le_name->setText(s); };
    /// Returns the string of the description field 
    QString getDescription() {return statePropertiesDlg.te_description->text(); };
    /// Sets the string of the description field
    void setDescription(QString s) {statePropertiesDlg.te_description->setText(s); };
    /// Returns the code
    QString getCode() {return statePropertiesDlg.le_code->text(); };
    /// Sets the code
    void setCode(const QString& s) {statePropertiesDlg.le_code->setText(s); };
    /// Returns the moore outputs
    QString getMooreOutputs() {return statePropertiesDlg.le_mooreoutputs->text(); };
    /// Sets the moore outputs
    void setMooreOutputs(const QString& s) {statePropertiesDlg.le_mooreoutputs->setText(s); };
    /// Gets the entry actions
    QString getEntryActions() { return statePropertiesDlg.le_entry->text(); };
    /// Sets the entry actions field
    void setEntryActions(const QString& s) {statePropertiesDlg.le_entry->setText(s); };
    /// Gets the exit actions
    QString getExitActions() { return statePropertiesDlg.le_exit->text(); };
    /// Sets the exit actions field
    void setExitActions(const QString& s) {statePropertiesDlg.le_exit->setText(s); };
    /// Returns the radius
    QString getRadius() {return statePropertiesDlg.le_radius->text(); };
    /// Sets the radius
    void setRadius(const QString& r) {statePropertiesDlg.le_radius->setText(r); };
    /// Returns the line width
    QString getLineWidth() {return statePropertiesDlg.le_linewidth->text(); };
    /// Sets the line width
    void setLineWidth(const QString& l) {statePropertiesDlg.le_linewidth->setText(l); };
    /// Sets the pointer to the main window
    void setMainWindow(MainWindow* m) { main = m; };
    /// Sets the current mode (StateAdd, StateEdit)
    void setMode(int m) { mode = m; };
    /// Sets the state to edit
    void setState(GState* s) { state=s; };
    /// Sets the color of the the state
    void setColor(QColor c) { color=c; statePropertiesDlg.lb_colorpreview->setBackgroundColor(c); };
    /// Returns the color
    QColor getColor() { return color; };

    /// Sets the maximum length of the code
    void setCodeMaxLength(int l) { statePropertiesDlg.le_code->setMaxLength(l); };
    /// Sets the maximum length of the moore outputs
    void setMooreOutputsMaxLength(int l) { statePropertiesDlg.le_mooreoutputs->setMaxLength(l); };
    /// Sets the maximum length of the entry actions
    void setEntryMaxLength(int l) { statePropertiesDlg.le_entry->setMaxLength(l); };
    /// Sets the maximum length of the exit actions
    void setExitMaxLength(int l) { statePropertiesDlg.le_exit->setMaxLength(l); };

    /// Selects the first field of the dialog and sets the focus
    void selectFirst() { statePropertiesDlg.le_name->selectAll(); statePropertiesDlg.le_name->setFocus(); };
  
  private:
    /// Mode of the dialog (see DialogMode)
    int mode;
    /// Pointer of the state to add/edit
    GState* state;
    /// Validator for the radius
    QIntValidator* valRadius;
    /// Validator for the line width
    QIntValidator* valLineWidth;
    /// Pointer to the main window
    MainWindow* main;
    /// Color
    QColor color;

  public slots:
    void chooseFGColor();
    void validate();
};

#endif // STATEPROPERTIESDLGIMPL_H
