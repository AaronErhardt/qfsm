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

in method clockPressed:
removed the line hz/=10;
*/

#ifndef SIMULATORDLGIMPL_H
#define SIMULATORDLGIMPL_H

#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qradiobutton.h>
//Added by qt3to4:
#include <QCloseEvent>
#include <QPixmap>
#include "ui_SimulatorDlg.h"
#include "WSpinBox.h"

class MainWindow;


/**
 * @class SimulatorDlgImpl
 * @brief Simulator dialog
 */
class SimulatorDlgImpl : public QDialog
{ 
    Q_OBJECT
        
        Ui::SimulatorDlg simulatorDlg;

public:
    /// State of the machine
    enum simstate {Off, Busy, Finished};

    SimulatorDlgImpl( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~SimulatorDlgImpl();

    /// Enables button for bit 0 if @a e is TRUE otherwise disables it
    void enable0(bool e) { simulatorDlg.pb_bin0->setEnabled(e); };
    /// Enables button for bit 1 if @a e is TRUE otherwise disables it
    void enable1(bool e) { simulatorDlg.pb_bin1->setEnabled(e); };
    /// Enables button for bit 2 if @a e is TRUE otherwise disables it
    void enable2(bool e) { simulatorDlg.pb_bin2->setEnabled(e); };
    /// Enables button for bit 3 if @a e is TRUE otherwise disables it
    void enable3(bool e) { simulatorDlg.pb_bin3->setEnabled(e); };
    /// Enables button for bit 4 if @a e is TRUE otherwise disables it
    void enable4(bool e) { simulatorDlg.pb_bin4->setEnabled(e); };
    /// Enables button for bit 5 if @a e is TRUE otherwise disables it
    void enable5(bool e) { simulatorDlg.pb_bin5->setEnabled(e); };
    /// Enables button for bit 6 if @a e is TRUE otherwise disables it
    void enable6(bool e) { simulatorDlg.pb_bin6->setEnabled(e); };
    /// Enables button for bit 7 if @a e is TRUE otherwise disables it
    void enable7(bool e) { simulatorDlg.pb_bin7->setEnabled(e); };
    /// Enables button for bit 8 if @a e is TRUE otherwise disables it
    void enable8(bool e) { simulatorDlg.pb_bin8->setEnabled(e); };
    /// Enables button for bit 9 if @a e is TRUE otherwise disables it
    void enable9(bool e) { simulatorDlg.pb_bin9->setEnabled(e); };
    /// Enables button for bit 10 if @a e is TRUE otherwise disables it
    void enable10(bool e) { simulatorDlg.pb_bin10->setEnabled(e); };
    /// Enables button for bit 11 if @a e is TRUE otherwise disables it
    void enable11(bool e) { simulatorDlg.pb_bin11->setEnabled(e); };
    /// Enables button for bit 12 if @a e is TRUE otherwise disables it
    void enable12(bool e) { simulatorDlg.pb_bin12->setEnabled(e); };
    /// Enables button for bit 13 if @a e is TRUE otherwise disables it
    void enable13(bool e) { simulatorDlg.pb_bin13->setEnabled(e); };
    /// Enables button for bit 14 if @a e is TRUE otherwise disables it
    void enable14(bool e) { simulatorDlg.pb_bin14->setEnabled(e); };
    /// Enables button for bit 15 if @a e is TRUE otherwise disables it
    void enable15(bool e) { simulatorDlg.pb_bin15->setEnabled(e); };
    /// Enables buttons for Frequency if @a e is TRUE otherwise disables them 
    void enableFrequency(bool e) { simulatorDlg.frequency->setEnabled(e);
      simulatorDlg.lb_frequency->setEnabled(e);};
    /// Enables 'Send' button if @a e is TRUE otherwise disables it 
      void enableSend(bool e) { simulatorDlg.pb_send->setEnabled(e); };
    /// Returns the string of the inputs field
      QString getInputs() { return simulatorDlg.le_inputs->text(); };
    /// Sets the input string
      void setInputs(QString s) { simulatorDlg.le_inputs->setText(s); };
    /// Sets the state name
      void setStateName(QString n) { simulatorDlg.lb_sname->setText(n); };
    /// Sets the state code
      void setStateCode(QString c) { simulatorDlg.lb_scode->setText(c); };
    /// Sets the output string 
      void setOutputs(QString o) { simulatorDlg.lb_outputs->setText(o); };

    /// Returns TRUE if @a Binary is checked for the inputs otherwise FALSE
      bool isIBinChecked() { return simulatorDlg.rb_ibin->isChecked(); };
    /// Returns TRUE if @a Hexadecimal is checked for the inputs otherwise FALSE
      bool isIHexChecked() { return simulatorDlg.rb_ihex->isChecked(); };
    /// Returns TRUE if @a ASCII is checked for the inputs otherwise FALSE
      bool isIASCIIChecked() { return simulatorDlg.rb_iascii->isChecked(); };
    /// Returns TRUE if @a Binary is checked for the outputs otherwise FALSE
      bool isOBinChecked() { return simulatorDlg.rb_obin->isChecked(); };
    /// Returns TRUE if @a Hexadecimal is checked for the outputs otherwise FALSE
      bool isOHexChecked() { return simulatorDlg.rb_ohex->isChecked(); };
    /// Returns TRUE if @a ASCII is checked for the outputs otherwise FALSE
      bool isOASCIIChecked() { return simulatorDlg.rb_oascii->isChecked(); };
    /// Returns TRUE if 'clock' is pressed, otherwise FALSE
      bool isClockOn() { return simulatorDlg.pb_clock->isOn(); };
    void setState(int);

    void resetButtons();
    void resetBits();
    void stopTimer();
    void init();

signals:
    /// Emited when the input needs to be sent to the machine
    void inputSent();
    /// Emited when the dialog is about to close
    void closing();
    /// Emited when reset is pressed
    void resetPressed();

public slots:
    void closeSim();
    void send();
    void reset();
    void inputsChanged(const QString& );
    void button0Pressed();
    void button1Pressed();
    void button2Pressed();
    void button3Pressed();
    void button4Pressed();
    void button5Pressed();
    void button6Pressed();
    void button7Pressed();
    void button8Pressed();
    void button9Pressed();
    void button10Pressed();
    void button11Pressed();
    void button12Pressed();
    void button13Pressed();
    void button14Pressed();
    void button15Pressed();
    void iBinPressed();
    void iHexPressed();
    void iASCIIPressed();
    void oBinPressed();
    void oHexPressed();
    void oASCIIPressed();

    void clockPressed();
    void selectFirst();
    void clearInput();

    void returnPressedInputs();

private:
    /// Pointer to the main window
    MainWindow* main;
    /// Timer
    QTimer* timer;
    /// Red light pixmap
    QPixmap* redlight;
    /// Green light pixmap
    QPixmap* greenlight;
    /// greylight pixmap
    QPixmap* greylight;

    void closeEvent(QCloseEvent* );
    void updateInputsStr();

};

#endif // SIMULATORDLGIMPL_H
