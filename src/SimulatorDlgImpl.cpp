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

#include <qtimer.h>
//Added by qt3to4:
#include <QCloseEvent>
#include <QPixmap>
#include "SimulatorDlgImpl.h"
#include "MainWindow.h"
#include "Project.h"
#include "Convert.h"
#include "Machine.h"
#include "Const.h"
#include "TransitionInfo.h"
#include "../pics/redlight.xpm"
#include "../pics/greenlight.xpm"
#include "../pics/greylight.xpm"

/** 
 *  Constructs a SimulatorDlgImpl which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
SimulatorDlgImpl::SimulatorDlgImpl( QWidget* parent,  const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl )
{
  simulatorDlg.setupUi(this);

    main = (MainWindow*)parent;
    timer = new QTimer(this);

    redlight = new QPixmap((const char**)redlight_xpm);
    greenlight = new QPixmap((const char**)greenlight_xpm);
    greylight = new QPixmap((const char**)greylight_xpm);

    connect(timer, SIGNAL(timeout()), this, SIGNAL(inputSent()));
}

/**  
 *  Destroys the object and frees any allocated resources
 */
SimulatorDlgImpl::~SimulatorDlgImpl()
{
  delete timer;
  delete redlight;
  delete greenlight;
  delete greylight;
}


/// Initialises the dialog
void SimulatorDlgImpl::init()
{
  resetButtons();

  if (isIBinChecked())
    simulatorDlg.le_inputs->setMaxLength(main->project->machine->getNumInputs());
  else if (isIHexChecked())
    simulatorDlg.le_inputs->setMaxLength(int((double)main->project->machine->getNumInputs()/4+0.9));
  else 
    simulatorDlg.le_inputs->setMaxLength(int((double)main->project->machine->getNumInputs()/8 +0.9)*4);

  setInputs("");
  simulatorDlg.le_inputs->setFocus();
  setState(Off);
}

/**
 * Close the simulator.
 * Emits the closing signal and hides the dialog. Is invoked when the users
 * clicks the Close button.
 */
void SimulatorDlgImpl::closeSim()
{
  emit closing();
  hide();
}

/**
 * Is invoked when the user closes the window.
 * Emits the closing signal and hides the dialog.
 */
void SimulatorDlgImpl::closeEvent(QCloseEvent* e)
{
  emit closing();
  e->accept();
}

/**
 * User has clicked the Send button.
 */
void SimulatorDlgImpl::send()
{
  emit inputSent();
}

/**
 * User has clicked the Reset button.
 */
void SimulatorDlgImpl::reset()
{
  emit resetPressed();
}

/// Stops the timer for the clock.
void SimulatorDlgImpl::stopTimer()
{
  timer->stop();
}

/// Selects the contents of the 'inputs' field and sets the focus
void SimulatorDlgImpl::selectFirst()
{
  simulatorDlg.le_inputs->selectAll();
  simulatorDlg.le_inputs->setFocus();
}

void SimulatorDlgImpl::clearInput()
{
  simulatorDlg.le_inputs->setText("");
  simulatorDlg.le_inputs->setFocus();
}


/**
 * Is invoked when the text in the inputs field changes.
 * The buttons for the bits 0-15 are changed according to the string @a in.
 */
void SimulatorDlgImpl::inputsChanged(const QString& in)
{
  Convert conv;
  int len;
  QString bin;
//  char* bininv;
  IOInfoBin io(IO_MealyIn), ioinv(IO_MealyIn);

  len = main->project->machine->getNumInputs();
//  bin = new char[len+1];
//  bininv = new char[len+1];
  if (isIBinChecked())
    ioinv = conv.binStrToX10(len, in, IO_MealyIn);
  else if (isIHexChecked())
    ioinv = conv.hexStrToX10(len, in, IO_MealyIn);
  else 
  {
    unsigned char ascii[MAX_CHARARRAY_LENGTH];
    int alen;

    conv.resolveEscapes(in, ascii, MAX_CHARARRAY_LENGTH, alen);
    ioinv = conv.asciiToX10(len, ascii, alen, IO_MealyIn);
  }

//  conv.invertX10(len, bininv, bin);
  io = ioinv;
  io.invertBits();
  bin = io.getInfo();

  if (simulatorDlg.pb_bin0->isEnabled())
    simulatorDlg.pb_bin0->setOn(bin[0]=='1');
  if (simulatorDlg.pb_bin1->isEnabled())
    simulatorDlg.pb_bin1->setOn(bin[1]=='1');
  if (simulatorDlg.pb_bin2->isEnabled())
    simulatorDlg.pb_bin2->setOn(bin[2]=='1');
  if (simulatorDlg.pb_bin3->isEnabled())
    simulatorDlg.pb_bin3->setOn(bin[3]=='1');
  if (simulatorDlg.pb_bin4->isEnabled())
    simulatorDlg.pb_bin4->setOn(bin[4]=='1');
  if (simulatorDlg.pb_bin5->isEnabled())
    simulatorDlg.pb_bin5->setOn(bin[5]=='1');
  if (simulatorDlg.pb_bin6->isEnabled())
    simulatorDlg.pb_bin6->setOn(bin[6]=='1');
  if (simulatorDlg.pb_bin7->isEnabled())
    simulatorDlg.pb_bin7->setOn(bin[7]=='1');
  if (simulatorDlg.pb_bin8->isEnabled())
    simulatorDlg.pb_bin8->setOn(bin[8]=='1');
  if (simulatorDlg.pb_bin9->isEnabled())
    simulatorDlg.pb_bin9->setOn(bin[9]=='1');
  if (simulatorDlg.pb_bin10->isEnabled())
    simulatorDlg.pb_bin10->setOn(bin[10]=='1');
  if (simulatorDlg.pb_bin11->isEnabled())
    simulatorDlg.pb_bin11->setOn(bin[11]=='1');
  if (simulatorDlg.pb_bin12->isEnabled())
    simulatorDlg.pb_bin12->setOn(bin[12]=='1');
  if (simulatorDlg.pb_bin13->isEnabled())
    simulatorDlg.pb_bin13->setOn(bin[13]=='1');
  if (simulatorDlg.pb_bin14->isEnabled())
    simulatorDlg.pb_bin14->setOn(bin[14]=='1');
  if (simulatorDlg.pb_bin15->isEnabled())
    simulatorDlg.pb_bin15->setOn(bin[15]=='1');

//  delete [] bin;
//  delete [] bininv;
}

/// Called when return is pressed in the 'inputs' field
void SimulatorDlgImpl::returnPressedInputs()
{
  /*
  if (pb_send->isEnabled())
    send();
    */
}


/// Button 0 was pressed
void SimulatorDlgImpl::button0Pressed()
{
  updateInputsStr();
}

/// Button 1 was pressed
void SimulatorDlgImpl::button1Pressed()
{
  updateInputsStr();
}

/// Button 2 was pressed
void SimulatorDlgImpl::button2Pressed()
{
  updateInputsStr();
}

/// Button 3 was pressed
void SimulatorDlgImpl::button3Pressed()
{
  updateInputsStr();
}

/// Button 4 was pressed
void SimulatorDlgImpl::button4Pressed()
{
  updateInputsStr();
}

/// Button 5 was pressed
void SimulatorDlgImpl::button5Pressed()
{
  updateInputsStr();
}

/// Button 6 was pressed
void SimulatorDlgImpl::button6Pressed()
{
  updateInputsStr();
}

/// Button 7 was pressed
void SimulatorDlgImpl::button7Pressed()
{
  updateInputsStr();
}

/// Button 8 was pressed
void SimulatorDlgImpl::button8Pressed()
{
  updateInputsStr();
}

/// Button 9 was pressed
void SimulatorDlgImpl::button9Pressed()
{
  updateInputsStr();
}

/// Button 10 was pressed
void SimulatorDlgImpl::button10Pressed()
{
  updateInputsStr();
}

/// Button 11 was pressed
void SimulatorDlgImpl::button11Pressed()
{
  updateInputsStr();
}

/// Button 12 was pressed
void SimulatorDlgImpl::button12Pressed()
{
  updateInputsStr();
}

/// Button 13 was pressed
void SimulatorDlgImpl::button13Pressed()
{
  updateInputsStr();
}

/// Button 14 was pressed
void SimulatorDlgImpl::button14Pressed()
{
  updateInputsStr();
}

/// Button 15 was pressed
void SimulatorDlgImpl::button15Pressed()
{
  updateInputsStr();
}


/**
 * Updates the string in the inputs field according to the state of the buttons.
 */
void SimulatorDlgImpl::updateInputsStr()
{
  int len;
  QString s;
  Convert conv;
  QString bin;
  IOInfoBin io(IO_MealyIn), ioinv(IO_MealyIn);

  len = main->project->machine->getNumInputs();
  s = simulatorDlg.le_inputs->text();

  if (isIBinChecked())
    ioinv = conv.binStrToX10(len, s, IO_MealyIn);
  else if (isIHexChecked())
    ioinv = conv.hexStrToX10(len, s, IO_MealyIn);
  else 
  {
    unsigned char ascii[MAX_CHARARRAY_LENGTH];
    int alen;

    conv.resolveEscapes(s, ascii, MAX_CHARARRAY_LENGTH, alen);
    ioinv = conv.asciiToX10(len, ascii, alen, IO_MealyIn);
  }

  io = ioinv;
  io.invertBits();
  bin = io.getInfo();
  bin.resize(len);

  if (len>0)
    bin[0]=simulatorDlg.pb_bin0->isOn()+'0';
  if (len>1)
    bin[1]=simulatorDlg.pb_bin1->isOn()+'0';
  if (len>2)
    bin[2]=simulatorDlg.pb_bin2->isOn()+'0';
  if (len>3)
    bin[3]=simulatorDlg.pb_bin3->isOn()+'0';
  if (len>4)
    bin[4]=simulatorDlg.pb_bin4->isOn()+'0';
  if (len>5)
    bin[5]=simulatorDlg.pb_bin5->isOn()+'0';
  if (len>6)
    bin[6]=simulatorDlg.pb_bin6->isOn()+'0';
  if (len>7)
    bin[7]=simulatorDlg.pb_bin7->isOn()+'0';
  if (len>8)
    bin[8]=simulatorDlg.pb_bin8->isOn()+'0';
  if (len>9)
    bin[9]=simulatorDlg.pb_bin9->isOn()+'0';
  if (len>10)
    bin[10]=simulatorDlg.pb_bin10->isOn()+'0';
  if (len>11)
    bin[11]=simulatorDlg.pb_bin11->isOn()+'0';
  if (len>12)
    bin[12]=simulatorDlg.pb_bin12->isOn()+'0';
  if (len>13)
    bin[13]=simulatorDlg.pb_bin13->isOn()+'0';
  if (len>14)
    bin[14]=simulatorDlg.pb_bin14->isOn()+'0';
  if (len>15)
    bin[15]=simulatorDlg.pb_bin15->isOn()+'0';
  
  io.setInfo(bin);

//  io.setInfo(bin);
  ioinv = io;
  ioinv.invertBits();

  if (isIBinChecked())
    s = conv.X10ToBinStr(ioinv);
  else if (isIHexChecked())
    s = conv.X10ToHexStr(ioinv);
  else
  {
    unsigned char ascii[MAX_CHARARRAY_LENGTH];
    int alen;

    if (!conv.X10ToASCII(ioinv, ascii, MAX_CHARARRAY_LENGTH, alen))
      s="";
    else
      s=conv.asciiToReadableStr(ascii, alen);
  }

  simulatorDlg.le_inputs->setText(s);

}


/// Called when the 'Binary' button for the inputs is pressed.
void SimulatorDlgImpl::iBinPressed()
{
  QString tmp;
  Convert conv;

  if (isIHexChecked())
  {
    tmp = conv.hexStrToBinStr(main->project->machine->getNumInputs(), simulatorDlg.le_inputs->text());
//    le_inputs->setText(tmp);
//    rb_ibin->setChecked(TRUE);
//    inputsChanged(tmp);
  }
  else if (isIASCIIChecked())
  {
    unsigned char ascii[MAX_CHARARRAY_LENGTH];
    int alen;

    conv.resolveEscapes(simulatorDlg.le_inputs->text(), ascii, MAX_CHARARRAY_LENGTH, alen);
    tmp = conv.asciiToBinStr(main->project->machine->getNumInputs(), ascii, alen);
//    le_inputs->setText(tmp);
//    rb_ibin->setChecked(TRUE);
//    inputsChanged(tmp);
  }
  simulatorDlg.le_inputs->setMaxLength(main->project->machine->getNumInputs());
  simulatorDlg.le_inputs->setText(tmp);
  simulatorDlg.rb_ibin->setChecked(TRUE);
  inputsChanged(tmp);
}


/// Called when the 'Hexadecimal' button for the inputs is pressed.
void SimulatorDlgImpl::iHexPressed()
{
  QString tmp;
  Convert conv;
  int maxlen;

  if (isIBinChecked())
  {
    tmp = conv.binStrToHexStr(simulatorDlg.le_inputs->text());
//    le_inputs->setText(tmp);
//    rb_ihex->setChecked(TRUE);
//    inputsChanged(tmp);
  }
  else if (isIASCIIChecked())
  {
    unsigned char ascii[MAX_CHARARRAY_LENGTH];
    int alen;

    conv.resolveEscapes(simulatorDlg.le_inputs->text(), ascii, MAX_CHARARRAY_LENGTH, alen);
    tmp = conv.asciiToHexStr(ascii, alen);
//    le_inputs->setText(tmp);
//    rb_ihex->setChecked(TRUE);
//    inputsChanged(tmp);
  }
  maxlen = int((double)main->project->machine->getNumInputs()/4+0.9);
  tmp = tmp.right(maxlen);
  simulatorDlg.le_inputs->setMaxLength(maxlen);
  simulatorDlg.le_inputs->setText(tmp);
  simulatorDlg.rb_ihex->setChecked(TRUE);
  inputsChanged(tmp);
}


/// Called when the 'ASCII' button for the inputs is pressed
void SimulatorDlgImpl::iASCIIPressed()
{
  QString tmp;
  Convert conv;

  if (isIBinChecked())
  {
    unsigned char ascii[MAX_CHARARRAY_LENGTH];
    int alen;

    conv.binStrToASCII(simulatorDlg.le_inputs->text(), ascii, MAX_CHARARRAY_LENGTH, alen);
    tmp = conv.asciiToReadableStr(ascii, alen);
//    le_inputs->setText(tmp);
//    rb_iascii->setChecked(TRUE);
//    inputsChanged(tmp);
  }
  else if (isIHexChecked())
  {
    unsigned char ascii[MAX_CHARARRAY_LENGTH];
    unsigned char single;
    int alen;

    conv.hexStrToASCII(simulatorDlg.le_inputs->text(), ascii, MAX_CHARARRAY_LENGTH, alen);
    if (alen>0)
    {
      single = ascii[alen-1];
      tmp = conv.asciiToReadableStr(&single, 1);
    }
//    le_inputs->setText(tmp);
//    rb_iascii->setChecked(TRUE);
//    inputsChanged(tmp);
  }
  simulatorDlg.le_inputs->setMaxLength(int((double)main->project->machine->getNumInputs()/8 +0.9)*4);
  simulatorDlg.le_inputs->setText(tmp);
  simulatorDlg.rb_iascii->setChecked(TRUE);
  inputsChanged(tmp);
}

/// Called when the 'Binary' button for the outputs is pressed.
void SimulatorDlgImpl::oBinPressed()
{
  QString tmp;
  Convert conv;

  if (isOHexChecked())
  {
    tmp = conv.hexStrToBinStr(main->project->machine->getNumOutputs(), simulatorDlg.lb_outputs->text());
    simulatorDlg.lb_outputs->setText(tmp);
  }
  else if (isOASCIIChecked())
  {
    unsigned char ascii[MAX_CHARARRAY_LENGTH];
    int alen;
    conv.resolveEscapes(simulatorDlg.lb_outputs->text(), ascii, MAX_CHARARRAY_LENGTH, alen);
    tmp = conv.asciiToBinStr(main->project->machine->getNumOutputs(), ascii, alen);
    simulatorDlg.lb_outputs->setText(tmp);
  }
}


/// Called when the 'Hexadecimal' button for the outputs is pressed.
void SimulatorDlgImpl::oHexPressed()
{
  QString tmp;
  Convert conv;

  if (isOBinChecked())
  {
    tmp = conv.binStrToHexStr(simulatorDlg.lb_outputs->text());
    simulatorDlg.lb_outputs->setText(tmp);
  }
  else if (isOASCIIChecked())
  {
    unsigned char ascii[MAX_CHARARRAY_LENGTH];
    int alen;
    conv.resolveEscapes(simulatorDlg.lb_outputs->text(), ascii, MAX_CHARARRAY_LENGTH, alen);
    tmp = conv.asciiToHexStr(ascii, alen);
    simulatorDlg.lb_outputs->setText(tmp);
  }
}

/// Called when the 'ASCII' button for the outputs is pressed.
void SimulatorDlgImpl::oASCIIPressed()
{
  QString tmp;
  Convert conv;

  if (isOBinChecked())
  {
    unsigned char ascii[MAX_CHARARRAY_LENGTH];
    int alen;

    conv.binStrToASCII(simulatorDlg.lb_outputs->text(), ascii, MAX_CHARARRAY_LENGTH, alen, FALSE);
    tmp = conv.asciiToReadableStr(ascii, alen);
    simulatorDlg.lb_outputs->setText(tmp);
  }
  else if (isOHexChecked())
  {
    unsigned char ascii[MAX_CHARARRAY_LENGTH];
    int alen;

    conv.hexStrToASCII(simulatorDlg.lb_outputs->text(), ascii, MAX_CHARARRAY_LENGTH, alen, FALSE);
    tmp = conv.asciiToReadableStr(ascii, alen);
    simulatorDlg.lb_outputs->setText(tmp);
  }
}



/// Sets all button states to Off
void SimulatorDlgImpl::resetButtons()
{
  if (main->project->machine)
  {
    if (main->project->machine->getType()==Binary)
    {
      simulatorDlg.rb_ibin->setChecked(TRUE);
      simulatorDlg.rb_obin->setChecked(TRUE);
    }
    else
    {
      simulatorDlg.rb_iascii->setChecked(TRUE);
      simulatorDlg.rb_oascii->setChecked(TRUE);
    }
      
  }

  resetBits();
  simulatorDlg.pb_clock->setOn(FALSE);
}


void SimulatorDlgImpl::resetBits()
{
  simulatorDlg.pb_bin0->setOn(FALSE);
  simulatorDlg.pb_bin1->setOn(FALSE);
  simulatorDlg.pb_bin2->setOn(FALSE);
  simulatorDlg.pb_bin3->setOn(FALSE);
  simulatorDlg.pb_bin4->setOn(FALSE);
  simulatorDlg.pb_bin5->setOn(FALSE);
  simulatorDlg.pb_bin6->setOn(FALSE);
  simulatorDlg.pb_bin7->setOn(FALSE);
  simulatorDlg.pb_bin8->setOn(FALSE);
  simulatorDlg.pb_bin9->setOn(FALSE);
  simulatorDlg.pb_bin10->setOn(FALSE);
  simulatorDlg.pb_bin11->setOn(FALSE);
  simulatorDlg.pb_bin12->setOn(FALSE);
  simulatorDlg.pb_bin13->setOn(FALSE);
  simulatorDlg.pb_bin14->setOn(FALSE);
  simulatorDlg.pb_bin15->setOn(FALSE);
}


/// Called when the 'clock' button is pressed
void SimulatorDlgImpl::clockPressed()
{
  double hz;
  double msec;
  hz = simulatorDlg.frequency->value();
//  hz /= 10;
  msec = 1000/hz;

  if (!simulatorDlg.pb_clock->isOn())
  {
    timer->start((int)msec);
    simulatorDlg.lb_frequency->setEnabled(FALSE);
    simulatorDlg.frequency->setEnabled(FALSE);
    simulatorDlg.pb_send->setEnabled(FALSE);
    resetBits();
  }
  else //if (timer->isActive())
  {
    timer->stop();
    simulatorDlg.lb_frequency->setEnabled(TRUE);
    simulatorDlg.frequency->setEnabled(TRUE);
    simulatorDlg.pb_send->setEnabled(TRUE);
  }
}


/**
 * Sets the state of the machine to @a s
 * @param s State of the machine
 *    - Busy: Machine hasn't reached an end state (red light)
 *    - Finished: Machine has reached an end state (green light)
 *    - Otherwise undefined (grey light)
 */
void SimulatorDlgImpl::setState(int s)
{
  switch (s)
  {
    case Busy:     simulatorDlg.pm_end->setPixmap(*redlight); break;
    case Finished: simulatorDlg.pm_end->setPixmap(*greenlight); break;
    default: simulatorDlg.pm_end->setPixmap(*greylight); break;
  }
}

