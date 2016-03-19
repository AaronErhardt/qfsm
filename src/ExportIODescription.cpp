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

#include <iostream>
#include <qregexp.h>

#include "ExportIODescription.h"
#include "Machine.h"
#include "TransitionInfo.h"
#include "IOInfo.h"
#include "IOInfoList.h"
#include "Convert.h"
#include "Utils.h"
#include "Options.h"

//using namespace std;


ExportIODescription::ExportIODescription(Options* opt)
  	  : Export(opt)
{
}


/// Writes all the relevant data into the tdf file.
void ExportIODescription::doExport()
{
  writeTable();
}


QString ExportIODescription::fileFilter()
{
	return "Comma-Separated Values (*.csv)";
}

QString ExportIODescription::defaultExtension()
{
	return "csv";
}

/*
  "Inputs";"write_p";"tx_rdy_p";"txbaud_en_p";"";""

"State/Output";"mux_sel";"updownctr_en_p";"updownctr_sclr_p";"downctr_load_p";"downctr_en_p";"alarm_p"
    "init";"0";"1";"0";"1";"1";"0"
        "timer_active";;;;;;
        "timer_finished";;;;;;
        "synchronous_clear";;;;;;
*/
/// Writes the table with states and outputs
void ExportIODescription::writeTable()
{
  using namespace std;

  if(machine->getNumInputs()>0)
  {
    *out << "\"Inputs\"";
    QStringList inputs=machine->getInputNameList();
    QStringList::const_iterator i;
    for(i=inputs.constBegin(); i!=inputs.constEnd(); ++i)
    {
      *out << ";\""<< i->latin1() << "\"";
    }
    *out << endl;
  }
  if(machine->getNumOutputs()>0)
  {
    *out << "\"Mealy Outputs\"";
    QStringList outputs=machine->getOutputNameList();
    QStringList::const_iterator i;
    for(i=outputs.constBegin(); i!=outputs.constEnd(); ++i)
    {
      *out << ";\""<< i->latin1() << "\"";
    }
    *out << endl;
  }
      
  *out << "\"State/Output\"";

  if(machine->getNumMooreOutputs()>0)
  {
    QStringList outputs=machine->getMooreOutputList();
    QStringList::const_iterator i;
    for(i=outputs.constBegin(); i!=outputs.constEnd(); ++i)
    {
      *out << ";\""<< i->latin1() << "\"";
    }
  }
  *out << endl;
  QList<GState*>states= machine->getSList();
  QList<GState*>::const_iterator is;
  IOInfo*mooreOutput;
  QString sMooreOutput;

  for(is=states.constBegin(); is!=states.constEnd(); ++is)
  {
    *out << "\"" << (*is)->getStateName().latin1() << "\"";
    if(machine->getNumMooreOutputs()>0)
    {
      mooreOutput=(*is)->getMooreOutputs();
      sMooreOutput=mooreOutput->convertToBinStr();
      int c=0;
      while(c<sMooreOutput.length())
      {
        *out << ";\"" << sMooreOutput[c].toLatin1() << "\"";
        c++;
      }
    }
    *out << endl;
  }
}


/// Writes a comment to the top of the output stream 
void ExportIODescription::writeHeader(QString, QString)
{
  ;
}
