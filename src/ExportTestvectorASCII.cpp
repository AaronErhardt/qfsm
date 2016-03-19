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

#include "ExportTestvectorASCII.h"



#include <iostream>
#include <qregexp.h>
#include <QList>
#include <QString>

#include "Machine.h"
#include "TransitionInfo.h"
#include "IOInfo.h"
#include "IOInfoList.h"
#include "Convert.h"
#include "Utils.h"
#include "Options.h"
#include "TestvectorGenerator.h"


ExportTestvectorASCII::ExportTestvectorASCII(Options* opt)
      : Export(opt)
{
  generator=new TestvectorGenerator();
  synchronous_reset = false;
  synchronous_enable = false;
  negated_reset = false;
  use_std_logic = true;
  io_names = false;
}

ExportTestvectorASCII::~ExportTestvectorASCII()
{
  delete generator;
}


/// Writes all the relevant data into the tdf file.
void ExportTestvectorASCII::doExport()
{

  synchronous_reset=options->getTestbenchSynchronousReset();
  synchronous_enable=options->getTestbenchSynchronousEnable();
  use_std_logic=options->getVHDLStdLogic();
  negated_reset=options->getTestbenchNegatedReset();
  io_names=options->getTestbenchIONames();


  generator->init(machine,synchronous_reset,synchronous_enable,negated_reset);
  generator->generateTestvector();


  writeHeader("","");
  generateVector();

}

void ExportTestvectorASCII::generateVector()
{
  using namespace std;
  unsigned int c=0;


  QList <IOInfo*> input_vector=generator->getInputVector();
  QList <IOInfo*> control_signal_vector=generator->getControlSignalVector();
  QList <IOInfo*> mealy_output_vector=generator->getMealyOutputVector();
  QList <IOInfo*> moore_output_vector=generator->getMooreOutputVector();

  IOInfo*i,*ics,*omealy,*omoore;

  QMutableListIterator <IOInfo*> i_i(input_vector);
  QMutableListIterator <IOInfo*> i_cs(control_signal_vector);
  QMutableListIterator <IOInfo*> i_omealy(mealy_output_vector);
  QMutableListIterator <IOInfo*> i_omoore(moore_output_vector);

  QStringList names=machine->getInputNameList();
  QList<int> input_separators;
  QList<int> moore_output_separators;
  QList<int> mealy_output_separators;
  QListIterator <int> i_sep(input_separators);

  QStringListIterator i_s(names);
  QString s;
  QString vector_name("");
  c=0;

  while(i_s.hasNext())
  {
      s=i_s.next();

      if(s.indexOf("[") !=-1 && s.indexOf("]")!=-1)
      {
          if(vector_name!=s.left(s.indexOf("[")))
          {
              if(c>0)
              {
              input_separators.append(c);
              qDebug(QString::number(c).latin1());
              c++;
              }
              vector_name=s.left(s.indexOf("["));
          }
      }
      else {
        if(c>0)
        {
        input_separators.append(c);
        qDebug(QString::number(c).latin1());
        c++;
        }
      }
      c++;
  }

  names=machine->getMooreOutputList();
  i_s=names;
  vector_name="";
  c=0;

  while(i_s.hasNext())
  {
      s=i_s.next();

      if(s.indexOf("[") !=-1 && s.indexOf("]")!=-1)
      {
          if(vector_name!=s.left(s.indexOf("[")))
          {
              if(c>0)
              {
              moore_output_separators.append(c);
              qDebug(QString::number(c).latin1());
              c++;
              }
              vector_name=s.left(s.indexOf("["));
          }
      }
      else {
        if(c>0)
        {
        moore_output_separators.append(c);
        qDebug(QString::number(c).latin1());
        c++;
        }
      }
      c++;
  }


  names=machine->getOutputNameList();
  i_s=names;
  vector_name="";
  c=0;

  while(i_s.hasNext())
  {
      s=i_s.next();

      if(s.indexOf("[") !=-1 && s.indexOf("]")!=-1)
      {
          if(vector_name!=s.left(s.indexOf("[")))
          {
              if(c>0)
              {
              mealy_output_separators.append(c);
              qDebug(QString::number(c).latin1());
              c++;
              }
              vector_name=s.left(s.indexOf("["));
          }
      }
      else {
        if(c>0)
        {
        mealy_output_separators.append(c);
        qDebug(QString::number(c).latin1());
        c++;
        }
      }
      c++;
  }

  c=0;

  while(i_i.hasNext() && i_omealy.hasNext() && i_omoore.hasNext())
  {
    c++;
    i=i_i.next();
    omealy=i_omealy.next();
    omoore=i_omoore.next();
    ics=i_cs.next();

    *out << " " << QString::number(c-1).latin1() << " ";

    if(synchronous_reset || synchronous_enable)
    {
      s=ics->convertToBinStr(machine,options).replace("x","0");
      s.insert(1," ");
      *out << s.latin1() << " ";
    }


    s=i->convertToBinStr(machine,options).replace("x","0");

    if(io_names)
      {
      i_sep=input_separators;
      while(i_sep.hasNext())
      {
          s.insert(i_sep.next()," ");
      }
    }
    *out << s.latin1();

    *out << " | ";

    s=omoore->convertToBinStr(machine,options).replace("x","0");

    if(io_names)
    {
      i_sep=moore_output_separators;
      while(i_sep.hasNext())
      {
          s.insert(i_sep.next()," ");
      }
    }
    *out << s.latin1();

    if(machine->getNumOutputs()>0 && machine->getNumMooreOutputs()>0)
        *out << " ";

    s=omealy->convertToBinStr(machine,options).replace("x","0");

    if(io_names)
    {
      i_sep=mealy_output_separators;
      while(i_sep.hasNext())
      {
          s.insert(i_sep.next()," ");
      }
    }
    *out << s.latin1();
    *out << endl;
  }
}



QString ExportTestvectorASCII::fileFilter()
{
  return "Testvector (*.vec)";
}

QString ExportTestvectorASCII::defaultExtension()
{
  return "vec";
}

/// Writes the machine description to the output stream
void ExportTestvectorASCII::writeHeader(QString,QString)
{
  using namespace std;
  QString bit_string;

  if (use_std_logic)
    bit_string="std_ulogic";
  else bit_string="bit";



  *out << "# Testpattern including expected results of " <<  machine->getName().latin1() <<  endl;
  *out << "#" << endl;

  if(synchronous_reset || synchronous_enable)
  {
    *out << "# control input signals:" << endl;
    *out << "# ----------------------" << endl;
    if(synchronous_reset && negated_reset)
      *out << "# srst_n : " << bit_string.toLatin1().constData()  << ";" << endl;
    else if(synchronous_reset && ! negated_reset)
      *out << "# srst_p : " << bit_string.toLatin1().constData()  << ";"  << endl;
    if(synchronous_enable)
      *out << "# sen_p : " << bit_string.toLatin1().constData()  << ";" << endl;
    *out << endl;
  }

  if (machine->getNumInputs()>0)
  {
    *out << "# input signals:" << endl;
    *out << "# --------------" << endl;
    foreach(const QString& input, machine->getInputNameList())
      *out << "# " << input.toLatin1().constData() << " : " << bit_string.toLatin1().constData() << ";" << endl;
    *out << endl;
  }
  if (machine->getNumOutputs()>0)
  {
    *out << "# mealy outputs:" << endl;
    *out << "# --------------" << endl;
    foreach(const QString& input, machine->getOutputNameList())
      *out << "# " << input.toLatin1().constData() << " : " << bit_string.toLatin1().constData() << ";" << endl;
    *out << endl;
  }

  if (machine->getNumMooreOutputs()>0)
  {
    *out << "# mooore outputs:" << endl;
    *out << "# --------------" << endl;
    foreach(const QString& input, machine->getMooreOutputList())
      *out << "# " << input.toLatin1().constData() << " : " << bit_string.toLatin1().constData() << ";" << endl;
    *out << "#" << endl;
  }

}
