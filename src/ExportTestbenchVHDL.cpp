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

#include "ExportTestbenchVHDL.h"

#include <qapplication.h>
#include <iostream>
#include <qregexp.h>

#include "Machine.h"
#include "TransitionInfo.h"
#include "IOInfo.h"
#include "IOInfoList.h"
#include "Convert.h"
#include "Utils.h"
#include "Options.h"
#include "AppInfo.h"


ExportTestbenchVHDL::ExportTestbenchVHDL(Options* opt)
      : Export(opt)
{
  outb = NULL;
  outp = NULL;
  io_names = false;
  synchronous_reset = false;
  synchronous_enable = false;
  neg_reset = false;
  use_std_logic = true;
  io_header = true;
  alliance = false;
}

/**
 * Initializes the export object.
 * @a ob is a pointer to the output stream opened with the standard fstream methods for writing the testvector file.
 * @a op is a pointer to the output stream opened with the standard fstream methods for writing the package file.
 */
void ExportTestbenchVHDL::init(std::ofstream* ob,std::ofstream*op, Machine* m, QString fn/*=QString::null*/, ScrollView* sv/*=NULL*/)
{
  outb = ob;
  outp = op;
  machine = m;
  fileName = fn;
  scrollview = sv;
}


/// Writes all the relevant data into the vhdl file.
void ExportTestbenchVHDL::doExport()
{

  mname=machine->getName();
  mname.replace(QRegExp(" "), "_");
  io_names=options->getTestbenchIONames();
  synchronous_reset=options->getTestbenchSynchronousReset();
  synchronous_enable=options->getTestbenchSynchronousEnable();
  neg_reset=options->getTestbenchNegatedReset();
  use_std_logic=options->getTestbenchStdLogic();
  io_header=options->getTestbenchIOHeader();
  alliance=options->getVHDLAlliance();
  testvector_name=options->getTestvectorASCIIPath();
  testpackage_name=options->getTestpackageVHDLPath();
  logfile_name=options->getTestbenchLogfilePath();


  //writes the package file
  writeHeader(outp,"--", "");
  writeEnvironment(outp);
  writePackage(outp);

  
  //writes the testbench file
  writeHeader(outb,"--", "");
  if(io_header)
    writeDescription(outb);
  writeEnvironment(outb);
  writeEntity(outb);
  writeArchitecture(outb);

}

/// Returns the file filter for the file dialog
QString ExportTestbenchVHDL::fileFilter()
{
  return "VHDL (*.vhd *.vhdl)";
}

/// Returns the default extension for the save file name
QString ExportTestbenchVHDL::defaultExtension()
{
  return "vhd";
}

/// Writes the testbench subprogram package
void ExportTestbenchVHDL::writePackage(std::ofstream*out)
{
  using namespace std;
    QString bit_string;

  if (use_std_logic)
    bit_string="std_ulogic";
  else bit_string="bit";


  *out << endl << "PACKAGE p_" << mname.toLatin1().toStdString() << "_tbench IS" << endl << endl;

  *out << "  SHARED VARIABLE errflag     : boolean := false;" << endl;
  *out << "  SHARED VARIABLE show_errors : boolean := true;" << endl << endl;

  *out << "--------------------------------------" << endl;
  *out << "-- convert std_ulogic_vector to string" << endl;
  *out << "--------------------------------------" << endl << endl;
  *out << "  FUNCTION TO_string(arg      : " << bit_string.toLatin1().toStdString() << "_vector) RETURN string;" << endl << endl;

  *out << "------------------------------------------------" << endl;
  *out << "-- read a delimiter character from stimulus file" << endl;
  *out << "------------------------------------------------" << endl << endl;
  *out << "  PROCEDURE read_delimiter (" << endl;
  *out << "    VARIABLE L         : INOUT line;" << endl;
  *out << "    CONSTANT delimiter :       character);" << endl << endl;

  *out << "------------------------------------------" << endl;
  *out << "-- read an input vector from stimulus file" << endl;
  *out << "------------------------------------------" << endl << endl;
  *out << "  PROCEDURE read_assign (" << endl;
  *out << "    VARIABLE L          : INOUT line;" << endl;
  *out << "    SIGNAL input_vector : OUT   " << bit_string.toLatin1().toStdString() << "_vector);" << endl << endl;

  *out << "------------------------------------------" << endl;
  *out << "-- read an input signal from stimulus file" << endl;
  *out << "------------------------------------------" << endl;
  *out << "  PROCEDURE read_assign (" << endl;
  *out << "    VARIABLE L          : INOUT line;" << endl;
  *out << "    SIGNAL input_signal : OUT   " << bit_string.toLatin1().toStdString() << ");" << endl << endl;

  *out << "------------------------------" << endl;
  *out << "-- write errors to output file" << endl;
  *out << "------------------------------" << endl;
  *out << "  PROCEDURE write_errors(FILE f     : text;" << endl;
  *out << "                         field_name : string;" << endl;
  *out << "                         vec_num    : natural;" << endl;
  *out << "                         exp, res   : " << bit_string.toLatin1().toStdString() << ");" << endl << endl;

  *out << "  PROCEDURE write_errors(FILE f     : text;" << endl;
  *out << "                         field_name : string;" << endl;
  *out << "                         vec_num    : natural;" << endl;
  *out << "                         exp, res   : " << bit_string.toLatin1().toStdString() << "_vector);" << endl << endl;

  *out << "------------------------------------------------------------" << endl;
  *out << "-- compare expected versus result vector and log differences" << endl;
  *out << "------------------------------------------------------------" << endl;
  *out << "  PROCEDURE check_results(" << endl;
  *out << "    VARIABLE L   : INOUT line;" << endl;
  *out << "    res          :       " << bit_string.toLatin1().toStdString() << ";" << endl;
  *out << "    field_name   :       string;" << endl;
  *out << "    vec_num      :       natural;" << endl;
  *out << "    FILE logfile :       text);" << endl << endl;

  *out << "  PROCEDURE check_results(" << endl;
  *out << "    VARIABLE L   : INOUT line;" << endl;
  *out << "    SIGNAL res   : IN    " << bit_string.toLatin1().toStdString() << "_vector;" << endl;
  *out << "    field_name   :       string;" << endl;
  *out << "    vec_num      :       natural;" << endl;
  *out << "    FILE logfile :       text);" << endl << endl;

  *out << "END p_" << mname.toLatin1().toStdString() << "_tbench;" << endl << endl;

  *out << "PACKAGE BODY p_" << mname.toLatin1().toStdString() << "_tbench IS" << endl;

  writeConverterFunction(out);
  writeReadDelimiterProcess(out);
  writeReadVectorProcess(out);
  writeReadSignalProcess(out);
  writeErrorLogProcess(out);
  writeCheckResultProcess(out);

  *out << endl << "END p_" << mname.toLatin1().toStdString() << "_tbench;" << endl;
}

/// Writes the 'library' and 'use' lines to the output stream
void ExportTestbenchVHDL::writeEnvironment(std::ofstream*out)
{
  using namespace std;

//  if (use_std_logic)
//  {
    *out << "LIBRARY IEEE;" << endl;
    *out << "USE IEEE.std_logic_1164.ALL;" << endl;
//  }
  *out << "USE ieee.std_logic_textio.ALL;" << endl;
  *out << "USE std.textio.ALL;" << endl ;
}

void ExportTestbenchVHDL::writeEntity(std::ofstream*out)
{
  using namespace std;


  *out << "USE work.p_" << mname.toLatin1().toStdString() << "_tbench.ALL;" << endl << endl;

  *out << "ENTITY t_" << mname.toLatin1().toStdString() << " IS" << endl;
  *out << "  GENERIC(show_errors :boolean := true);  -- show errors on standard output" << endl;
  *out << "END t_" << mname.toLatin1().toStdString() << ";" << endl << endl;

}

/// Writes the testbench architecture
void ExportTestbenchVHDL::writeArchitecture(std::ofstream*out)
{
  using namespace std;

  *out << "ARCHITECTURE tbench OF t_" << mname.toLatin1().toStdString() << " IS" << endl;

  writeComponent(outb);
//  *out << endl << "  SHARED VARIABLE errflag : boolean := false;" << endl << endl;

  writeDefinitions(outb);
  *out << "BEGIN -- tbench" << endl;
  writeInstantiation(outb);
  writeClockProcess(outb);
//  writeObserverProcess();
  writeNewObserverProcess(outb);
  *out << "END tbench;" << endl;
}


/// Writes the component definition
void ExportTestbenchVHDL::writeComponent(std::ofstream*out)
{
  using namespace std;

  QString bit_string;
  bool io_names_t, synchronous_reset_t;


  synchronous_reset_t=synchronous_reset;
  io_names_t=io_names;

  if (use_std_logic)
    bit_string = "std_ulogic";
  else
    bit_string = "bit";

  *out << "  COMPONENT " << mname.toLatin1().toStdString() << endl;
  *out << "    PORT (clk: IN " << bit_string.toLatin1().toStdString() << ";" << endl;
  if(synchronous_reset_t)
  {
    if (neg_reset)
      *out << "          srst_n: IN " << bit_string.toLatin1().toStdString() << ";" << endl;
    else
      *out << "          srst_p: IN " << bit_string.toLatin1().toStdString() << ";" << endl;
  }
  if(synchronous_enable)
  {
      *out << "          sen_p: IN " << bit_string.toLatin1().toStdString() << ";" << endl;
  }
  if (!alliance)
  {
    if (neg_reset)
      *out << "          rst_n: IN " << bit_string.toLatin1().toStdString() << ";" << endl;
    else
      *out << "          rst_p: IN " << bit_string.toLatin1().toStdString() << ";" << endl;
  }

  if (io_names_t)
  {
    QStringList inputs=(machine->retranslateNames(machine->getInputNameList())).split(",");
    QStringList::iterator i;
    QString vector="";
    int pos1=0,pos2=0;
    if(machine->getNumInputs()>0)
    {
      for (i = inputs.begin(); i != inputs.end(); ++i)
      {
      vector="";
        if((pos1=i->find("[")) !=-1 && i->find("..") !=-1 && (pos2=i->find("]")) !=-1)
        {
          vector="_vector"+i->mid(pos1,pos2-pos1+1);
          vector.replace(".."," DOWNTO ");
          vector.replace("[","(");
          vector.replace("]",")");
          i->remove(pos1,pos2-pos1+1);
        }
        *out << "          " << i->toLatin1().toStdString() << ": IN "<< bit_string.toLatin1().toStdString() << vector.toLatin1().toStdString() << ";\n";
      }
    }

    if (machine->getNumMooreOutputs()>0)
    {
      QStringList mooreOutputs=(machine->retranslateNames(machine->getMooreOutputList())).split(",");
      for (i = mooreOutputs.begin(); i != mooreOutputs.end(); ++i)
      {
      vector="";
        if((pos1=i->find("[")) !=-1 && i->find("..") !=-1 && (pos2=i->find("]")) !=-1)
        {
          vector="_vector"+i->mid(pos1,pos2-pos1+1);
          vector.replace(".."," DOWNTO ");
          vector.replace("[","(");
          vector.replace("]",")");
          i->remove(pos1,pos2-pos1+1);
        }
  *out << "          " << i->toLatin1().toStdString() << ": OUT "<< bit_string.toLatin1().toStdString() << vector.toLatin1().toStdString();
  if((i+1)!=mooreOutputs.end() || machine->getNumOutputs()>0)
    *out<< ";\n";
      }
    }
    if (machine->getNumOutputs()>0)
    {

      QStringList mealyOutputs=(machine->retranslateNames(machine->getOutputNameList())).split(",");
      for (i = mealyOutputs.begin(); i != mealyOutputs.end(); ++i)
      {
      vector="";
        if((pos1=i->find("[")) !=-1 && i->find("..") !=-1 && (pos2=i->find("]")) !=-1)
        {
          vector="_vector"+i->mid(pos1,pos2-pos1+1);
          vector.replace(".."," DOWNTO ");
          vector.replace("[","(");
          vector.replace("]",")");
          i->remove(pos1,pos2-pos1+1);
        }
  *out << "          " << i->toLatin1().toStdString() << ": OUT "<< bit_string.toLatin1().toStdString() << vector.toLatin1();
  if((i+1)!=mealyOutputs.end())
    *out<< ";\n";
      }
    }
    *out << ");\n";
  }
  else // ! io_names
  {
    if(machine->getNumInputs() >0)
    {
      *out << "          a: IN " << bit_string.toLatin1().toStdString() << "_vector(" << machine->getNumInputs()-1
        << " DOWNTO 0)";
    }
    if (machine->getNumMooreOutputs()>0)
    {
      *out << ";\n          q: OUT " << bit_string.toLatin1().toStdString() << "_vector(" << machine->getNumMooreOutputs()-1
  << " DOWNTO 0)";
    }
    if (machine->getNumOutputs()>0)
    {
      *out << ";\n          o: OUT " << bit_string.toLatin1().toStdString() << "_vector(" << machine->getNumOutputs()-1
  << " DOWNTO 0)";
    }
    *out << ");" << endl;
  }  // end if
  *out << "  END COMPONENT;" << endl;
}


/// Writes the string std_ulogic_vector to string converter function
void ExportTestbenchVHDL::writeConverterFunction(std::ofstream*out)
{
  using namespace std;

  QString bit_string;

  if (use_std_logic)
    bit_string = "std_ulogic";
  else
    bit_string = "bit";


  *out << "  FUNCTION TO_string(arg : " << bit_string.toLatin1().toStdString() << "_vector) RETURN string IS" << endl;
  *out << "    ALIAS u : " << bit_string.toLatin1().toStdString() << "_vector(arg'length DOWNTO 1) IS arg;" << endl;
  *out << "    VARIABLE result : string(arg'length DOWNTO 1);" << endl;
  *out << "  BEGIN" << endl;
  *out << "    FOR i IN u'RANGE LOOP" << endl;
  *out << "      CASE u(i) IS" << endl;
  *out << "        WHEN '0' => result(i):='0';" << endl;
  *out << "        WHEN '1' => result(i):='1';" << endl;
  if(use_std_logic)
  {
    *out << "        WHEN 'U' => result(i):='U';" << endl;
    *out << "        WHEN 'X' => result(i):='X';" << endl;
    *out << "        WHEN 'Z' => result(i):='Z';" << endl;
    *out << "        WHEN 'W' => result(i):='W';" << endl;
    *out << "        WHEN 'L' => result(i):='L';" << endl;
    *out << "        WHEN 'H' => result(i):='H';" << endl;
    *out << "        WHEN '-' => result(i):='-';" << endl;
  }
  *out << "      END CASE;" << endl;
  *out << "    END LOOP;" << endl;
  *out << "    RETURN result;" << endl;
  *out << "  END TO_string;" << endl;

}

/// Writes signal and constant definitions
void ExportTestbenchVHDL::writeDefinitions(std::ofstream*out)
{
  using namespace std;

  QString bit_string;
  bool io_names_t, synchronous_reset_t;


  synchronous_reset_t=synchronous_reset;
  io_names_t=io_names;


  if (use_std_logic)
    bit_string = "std_ulogic";
  else
    bit_string = "bit";

  *out << "  -- component ports " << endl;
  *out << "  SIGNAL clk: " << bit_string.toLatin1().toStdString() << ";" << endl;
  if(synchronous_reset_t)
  {
    if (neg_reset)
      *out << "  SIGNAL srst_n: " << bit_string.toLatin1().toStdString() << ";" << endl;
    else
      *out << "  SIGNAL srst_p: " << bit_string.toLatin1().toStdString() << ";" << endl;
  }
  if(synchronous_enable)
  {
      *out << "  SIGNAL sen_p: " << bit_string.toLatin1().toStdString() << ";" << endl;
  }
  if (!alliance)
  {
    if (neg_reset)
      *out << "  SIGNAL rst_n: " << bit_string.toLatin1().toStdString() << ";" << endl;
    else
      *out << " SIGNAL rst_p: " << bit_string.toLatin1().toStdString() << ";" << endl;
  }

  if (io_names_t)
  {
    QStringList inputs=(machine->retranslateNames(machine->getInputNameList())).split(",");
    QStringList::iterator i;
    QString vector="";
    int pos1=0,pos2=0;
    if(machine->getNumInputs()>0)
    {
      for (i = inputs.begin(); i != inputs.end(); ++i)
      {
      vector="";
        if((pos1=i->find("[")) !=-1 && i->find("..") !=-1 && (pos2=i->find("]")) !=-1)
        {
          vector="_vector"+i->mid(pos1,pos2-pos1+1);
          vector.replace(".."," DOWNTO ");
          vector.replace("[","(");
          vector.replace("]",")");
          i->remove(pos1,pos2-pos1+1);
        }
        *out << "  SIGNAL " << i->toLatin1().toStdString() << ": "<< bit_string.toLatin1().toStdString() << vector.toLatin1().toStdString() << ";\n";
      }
    }

    if (machine->getNumMooreOutputs()>0)
    {
      QStringList mooreOutputs=(machine->retranslateNames(machine->getMooreOutputList())).split(",");
      for (i = mooreOutputs.begin(); i != mooreOutputs.end(); ++i)
      {
      vector="";
        if((pos1=i->find("[")) !=-1 && i->find("..") !=-1 && (pos2=i->find("]")) !=-1)
        {
          vector="_vector"+i->mid(pos1,pos2-pos1+1);
          vector.replace(".."," DOWNTO ");
          vector.replace("[","(");
          vector.replace("]",")");
          i->remove(pos1,pos2-pos1+1);
        }
  *out << "  SIGNAL " << i->toLatin1().toStdString() << ": "<< bit_string.toLatin1().toStdString() << vector.toLatin1();
  if((i+1)!=mooreOutputs.end() || machine->getNumOutputs()>0)
    *out<< ";\n";
      }
    }
    if (machine->getNumOutputs()>0)
    {

      QStringList mealyOutputs=(machine->retranslateNames(machine->getOutputNameList())).split(",");
      for (i = mealyOutputs.begin(); i != mealyOutputs.end(); ++i)
      {
      vector="";
        if((pos1=i->find("[")) !=-1 && i->find("..") !=-1 && (pos2=i->find("]")) !=-1)
        {
          vector="_vector"+i->mid(pos1,pos2-pos1+1);
          vector.replace(".."," DOWNTO ");
          vector.replace("[","(");
          vector.replace("]",")");
          i->remove(pos1,pos2-pos1+1);
        }
  *out << "  SIGNAL " << i->toLatin1().toStdString() << ": "<< bit_string.toLatin1().toStdString() << vector.toLatin1();
  if((i+1)!=mealyOutputs.end())
    *out<< ";\n";
      }
    }
    *out << ";\n";
  }
  else // ! io_names
  {
    *out << "  SIGNAL a: " << bit_string.toLatin1().toStdString() << "_vector(" << machine->getNumInputs()-1
      << " DOWNTO 0);";
    if (machine->getNumMooreOutputs()>0)
    {
      *out << "\n  SIGNAL q: " << bit_string.toLatin1().toStdString() << "_vector(" << machine->getNumMooreOutputs()-1
  << " DOWNTO 0);";
    }
    if (machine->getNumOutputs()>0)
    {
      *out << "\n  SIGNAL o: " << bit_string.toLatin1().toStdString() << "_vector(" << machine->getNumOutputs()-1
  << " DOWNTO 0);";
    }
  }  // end if
  *out << endl << "  -- definition of a clock period" << endl;

  *out << "  CONSTANT period : time := 10 ns;" << endl;
  *out << "  CONSTANT strobe : time := period*0.99; -- sampling at 99%" << endl;
  *out << "                                       -- of period" << endl;
  *out << "  -- switch for clock generator" << endl;
  *out << "  SIGNAL clken_p : boolean := true;" << endl << endl;
}

/// Writes component instantiation
void ExportTestbenchVHDL::writeInstantiation(std::ofstream*out)
{
  using namespace std;

  bool io_names_t, synchronous_reset_t;


  synchronous_reset_t=synchronous_reset;
  io_names_t=io_names;



  *out << "  -- component instantiation " << endl;
  *out << "  MUT : " << mname.toLatin1().toStdString() << endl;
  *out << "    PORT MAP (" << endl;
  *out << "      clk => clk," << endl;
  if(synchronous_reset_t)
  {
    if (neg_reset)
      *out << "      srst_n => srst_n," << endl;
    else
      *out << "      srst_p => srst_p, " << endl;
  }
  if(synchronous_enable)
  {
    *out << "      sen_p => sen_p, " << endl;
  }
  if (!alliance)
  {
    if (neg_reset)
      *out << "      rst_n => rst_n," << endl;
    else
      *out << "     rst_p => rst_p," << endl;
  }

  if (io_names_t)
  {
    QStringList inputs=(machine->retranslateNames(machine->getInputNameList())).split(",");
    QStringList::iterator i;
    QString vector="";
    int pos1=0,pos2=0;
    if(machine->getNumInputs()>0)
    {
      for (i = inputs.begin(); i != inputs.end(); ++i)
      {
        if((pos1=i->find("[")) !=-1 && i->find("..") !=-1 && (pos2=i->find("]")) !=-1)
        {
          i->remove(pos1,pos2-pos1+1);
        }
        *out << "      " << i->toLatin1().toStdString() << " => " << i->toLatin1().toStdString() << ",\n";
      }
    }

    if (machine->getNumMooreOutputs()>0)
    {
      QStringList mooreOutputs=(machine->retranslateNames(machine->getMooreOutputList())).split(",");
      for (i = mooreOutputs.begin(); i != mooreOutputs.end(); ++i)
      {
        if((pos1=i->find("[")) !=-1 && i->find("..") !=-1 && (pos2=i->find("]")) !=-1)
        {
          i->remove(pos1,pos2-pos1+1);
        }
  *out << "      " << i->toLatin1().toStdString() << " => " << i->toLatin1();
  if((i+1)!=mooreOutputs.end() || machine->getNumOutputs()>0)
    *out<< ",\n";
      }
    }
    if (machine->getNumOutputs()>0)
    {
      QStringList mealyOutputs=(machine->retranslateNames(machine->getOutputNameList())).split(",");
      for (i = mealyOutputs.begin(); i != mealyOutputs.end(); ++i)
      {
        if((pos1=i->find("[")) !=-1 && i->find("..") !=-1 && (pos2=i->find("]")) !=-1)
        {
          i->remove(pos1,pos2-pos1+1);
        }
  *out << "      " << i->toLatin1().toStdString() << " => " << i->toLatin1();
  if((i+1)!=mealyOutputs.end())
    *out<< ",\n";
      }
    }
    *out << ");\n" << endl;
  }
  else // ! io_names
  {
    if(machine->getNumInputs()>0)
    {
      *out << "      a => a" ;
    }
    if (machine->getNumMooreOutputs()>0)
    {
      if(machine->getNumInputs()>0)
        *out << ",\n";
      *out << "      q => q" ;
    }
    if (machine->getNumOutputs()>0)
    {
      if(machine->getNumInputs()>0 || machine->getNumMooreOutputs()>0)
        *out << ",\n";
      *out << "      o => o" ;
    }
    *out << ");\n" << endl;
  }  // end if
}

/// Writes the clock process
void ExportTestbenchVHDL::writeClockProcess(std::ofstream*out)
{
  using namespace std;

  *out << "  -- clock generation" << endl;
  *out << "  clock_proc: PROCESS" << endl;
  *out << "  BEGIN" << endl;
  *out << "    WHILE clken_p LOOP" << endl;
  *out << "      clk <= '0'; WAIT FOR period/2;" << endl;
  *out << "      clk <= '1'; WAIT FOR period/2;" << endl;
  *out << "    END LOOP;" << endl;
  *out << "    WAIT;" << endl;
  *out << "  END PROCESS;" << endl << endl;
  if(neg_reset)
    *out << "  reset: rst_n <= '0' , '1' AFTER period;" << endl << endl;
  else *out << "  reset: rst_p <= '1' , '0' AFTER period;" << endl << endl;
}

/// Writes the observer process
void ExportTestbenchVHDL::writeObserverProcess(std::ofstream*out)
{
  using namespace std;

  int input_count=machine->getNumInputs();
  int output_count=machine->getNumOutputs()+machine->getNumMooreOutputs();
  int stimuli_counter;
  int c;
  QString bit_string;
  bool io_names_t, synchronous_reset_t;


  synchronous_reset_t=synchronous_reset;
  io_names_t=io_names;




  if (use_std_logic)
    bit_string = "std_ulogic";
  else
    bit_string = "bit";

  *out << "  stimuli_observer: PROCESS" << endl;
  *out << "    VARIABLE errflag : boolean := false;" << endl;
  *out << "    VARIABLE L : line;" << endl;
  *out << "    FILE vectorfile : text OPEN read_mode IS \"./" << testvector_name.toLatin1().toStdString() << "\";";

  if(use_std_logic)
  {
    *out << "    VARIABLE vector : bit_vector(";
    *out << QString::number(input_count+output_count-1).toLatin1();
    *out << " DOWNTO 0);" << endl;
  }

  *out << "    VARIABLE test_vector : " << bit_string.toLatin1().toStdString() << "_vector(";
  *out << QString::number(input_count+output_count-1).toLatin1();
  *out << " DOWNTO 0);" << endl;


  *out << "  BEGIN" << endl;
  *out << "    WAIT FOR period;  --wait for reset" << endl;
  *out << "    WHILE NOT endfile(vectorfile) LOOP" << endl;
  *out << "      readline(vectorfile,L);" << endl;

  if(use_std_logic)
  {
    *out << "      read(L,vector);" << endl;
    *out << "      test_vector:=to_stdulogicvector(vector);" << endl;
  }
  else
    *out << "read(L,test_vector);" << endl;

  stimuli_counter=input_count+output_count;

  if (io_names_t)
  {
    QStringList inputs=machine->getInputNameList();
    QStringList::iterator i;
    for (i = inputs.begin(); i != inputs.end(); ++i)
    {
      stimuli_counter--;
      if(i->find("[") !=-1 && i->find("]") !=-1)
      {
        i->replace("[","(");
        i->replace("]",")");
      }
      *out << "      " << i->toLatin1().toStdString() << " <= test_vector("
          << QString::number(stimuli_counter).toLatin1().toStdString() << ");\n";
    }
  }
  else
  {
    for(c=machine->getNumInputs()-1; c>=0; c--)
    {
      stimuli_counter--;

      *out << "      a(" << QString::number(c).toLatin1().toStdString() << ") <= test_vector("
           << QString::number(stimuli_counter).toLatin1().toStdString() << ");\n";
    }
  }
  *out << "      WAIT FOR strobe;" << endl;

  *out << "      IF (";
  if(io_names_t)
  {

    if (machine->getNumMooreOutputs()>0)
    {
      QStringList mooreOutputs=machine->getMooreOutputList();
      QStringList::iterator i;
      for (i = mooreOutputs.begin(); i != mooreOutputs.end(); ++i)
      {
        if(i->find("[") !=-1 && i->find("]") !=-1)
          {
            i->replace("[","(");
            i->replace("]",")");
          }
        if(i==mooreOutputs.begin())
          *out << i->toLatin1();
        else *out << " & " << i->toLatin1();
      }
    }
    if (machine->getNumOutputs()>0)
    {

      QStringList mealyOutputs=machine->getOutputNameList();
      QStringList::iterator i;
      for (i = mealyOutputs.begin(); i != mealyOutputs.end(); ++i)
      {
        if(i->find("[") !=-1 && i->find("]") !=-1)
          {
            i->replace("[","(");
            i->replace("]",")");
          }
        if(i==mealyOutputs.begin() && machine->getNumMooreOutputs()==0)
          *out << i->toLatin1();
        else *out << " & " << i->toLatin1();
      }
    }
    *out << ")";
  }
  else // ! io_names
  {
    if(machine->getNumMooreOutputs()>0)
    {
      int numOutputs=machine->getNumMooreOutputs();
      for(c=numOutputs-1; c>=0; c--)
      {
        if(c==numOutputs-1)
          *out << "q(" << QString::number(c).toLatin1().toStdString() << ")";
        else *out << " & q(" << QString::number(c).toLatin1().toStdString() << ")";
      }

    }

    if(machine->getNumOutputs()>0)
    {
      int numOutputs=machine->getNumOutputs();
      for(c=numOutputs-1; c>=0; c--)
      {
        if(c==numOutputs-1 && machine->getNumMooreOutputs()==0)
          *out << "a(" << QString::number(c).toLatin1().toStdString() << ")";
        else *out << " & a(" << QString::number(c).toLatin1().toStdString() << ")";
      }
    }
    *out << ")";
  }  // end if

  stimuli_counter--;
  *out << " /= test_vector(" << QString::number(stimuli_counter).toLatin1().toStdString() << " DOWNTO 0) THEN" << endl;
  *out << "        REPORT \"Error: Wrong result!\"" << endl;
  *out << "          SEVERITY failure;" << endl;
  *out << "        errflag:=true;" << endl;
  *out << "      END IF;" << endl;
  *out << "      WAIT FOR period-strobe;" << endl;
  *out << "    END LOOP;  -- reading vector" << endl;
  *out << "    ASSERT errflag" << endl;
  *out << "      REPORT \"No Errors!\"" << endl;
  *out << "        SEVERITY note;" << endl;
  *out << "    clken_p <= false;" << endl;
  *out << "    WAIT;" << endl;
  *out << "  END PROCESS;" << endl;

}

/// Write description
void ExportTestbenchVHDL::writeDescription(std::ofstream*out)
{
  using namespace std;


  *out << endl;
  if(machine->getNumInputs()>0)
  {
    *out << "-- Inputs:";
    QStringList inputs=machine->getInputNameList();
    QStringList::const_iterator i;
    for(i=inputs.constBegin(); i!=inputs.constEnd(); ++i)
    {
      *out << "   "<< i->toLatin1();
    }
    *out << endl;
  }
  if(machine->getNumOutputs()>0)
  {
    *out << "-- Mealy Outputs:";
    QStringList outputs=machine->getOutputNameList();
    QStringList::const_iterator i;
    for(i=outputs.constBegin(); i!=outputs.constEnd(); ++i)
    {
      *out << "   "<< i->toLatin1();
    }
    *out << endl;
  }


  QList<GState*>states= machine->getSList();
  QList<GState*>::const_iterator is;
  int *textLen=new int[machine->getNumMooreOutputs()+1];
  textLen[0]=12;

  for(is=states.constBegin(); is!=states.constEnd(); ++is)
  {
    if(!(*is)->isDeleted() && (*is)->getStateName().length()>textLen[0])
      textLen[0]=(*is)->getStateName().length();
  }
  textLen[0]++;

  *out << "-- State/Output" << QString(textLen[0]-13,' ').toLatin1();


  if(machine->getNumMooreOutputs()>0)
  {
    int spc=1;
    QStringList outputs=machine->getMooreOutputList();
    QStringList::iterator i;
    for(i=outputs.begin(); i!=outputs.end(); ++i)
    {
      textLen[spc]=i->length()+1;
      spc++;
      *out << " "<< i->toLatin1();
    }
  }
  *out << endl;

  IOInfo*mooreOutput;
  QString sMooreOutput;

  for(is=states.constBegin(); is!=states.constEnd(); ++is)
  {
    if((*is)->isDeleted())
      continue;
    int spc=0;
    *out << "-- " << (*is)->getStateName().toLatin1().toStdString() << QString(textLen[spc]-(*is)->getStateName().length(),' ').toLatin1().toStdString();
    spc++;
    if(machine->getNumMooreOutputs()>0)
    {
      mooreOutput=(*is)->getMooreOutputs();
      sMooreOutput=mooreOutput->convertToBinStr();
      int c=0;
      while(c<sMooreOutput.length())
      {
        *out << sMooreOutput[c].toLatin1().toStdString() << QString(textLen[spc]-1,' ').toLatin1().toStdString();
        c++;
        spc++;
      }
    }
    *out << endl;
  }
  *out << endl;
  delete[] textLen;
}


/// Writes read_delimiter process
void ExportTestbenchVHDL::writeReadDelimiterProcess(std::ofstream*out)
{
  using namespace std;
  *out << "------------------------------------------------" << endl;
  *out << "-- read a delimiter character from stimulus file" << endl;
  *out << "------------------------------------------------" << endl;
  *out << "PROCEDURE read_delimiter (" << endl;
  *out << "  VARIABLE L         : INOUT line;" << endl;
  *out << "  CONSTANT delimiter :       character) IS" << endl;
  *out << "  VARIABLE c : character;" << endl;
  *out << "BEGIN  -- read_delimiter" << endl;
  *out << "  read(L, c);" << endl;
  *out << "  IF c /= delimiter THEN" << endl;
  *out << "    REPORT \"E@read_delimiter: Not a delimiter character !\" SEVERITY failure;" << endl;
  *out << "  END IF;" << endl;
  *out << "END read_delimiter;" << endl << endl;

}

/// Writes read_assign process to read an input vector from a line of the stimulus file
void ExportTestbenchVHDL::writeReadVectorProcess(std::ofstream*out)
{
  using namespace std;
  QString bit_string;

  if (use_std_logic)
    bit_string="std_ulogic";
  else bit_string="bit";


  *out << "------------------------------------------" << endl;
  *out << "-- read an input vector from stimulus file" << endl;
  *out << "------------------------------------------" << endl;
  *out << "PROCEDURE read_assign (" << endl;
  *out << "  VARIABLE L          : INOUT line;" << endl;
  *out << "  SIGNAL input_vector : OUT   " << bit_string.toLatin1().toStdString() << "_vector) IS" << endl;
  *out << "  VARIABLE vec : " << bit_string.toLatin1().toStdString() << "_vector(input_vector'length-1 DOWNTO 0);" << endl;
  *out << "BEGIN  -- read_assign" << endl;
  *out << "  read(L, vec);" << endl;
  *out << "  input_vector <= vec;" << endl;
  *out << "END read_assign;" << endl << endl;
}

/// Writes read_assign process to read an input signal from a line of the stimulus file
void ExportTestbenchVHDL::writeReadSignalProcess(std::ofstream*out)
{
  using namespace std;

  QString bit_string;

  if (use_std_logic)
    bit_string="std_ulogic";
  else bit_string="bit";


  *out << "------------------------------------------" << endl;
  *out << "-- read an input signal from stimulus file" << endl;
  *out << "------------------------------------------" << endl;
  *out << "PROCEDURE read_assign (" << endl;
  *out << "  VARIABLE L          : INOUT line;" << endl;
  *out << "  SIGNAL input_signal : OUT   " << bit_string.toLatin1().toStdString() << ") IS" << endl;
  *out << "  VARIABLE temp : " << bit_string.toLatin1().toStdString() << ";" << endl;
  *out << "BEGIN  -- read_assign" << endl;
  *out << "  read(L, temp);" << endl;
  *out << "  input_signal <= temp;" << endl;
  *out << "END read_assign;" << endl << endl;

}

/// Writes the write_errors procedure which generates the log file
void ExportTestbenchVHDL::writeErrorLogProcess(std::ofstream*out)
{
  using namespace std;

  QString bit_string;

  if (use_std_logic)
    bit_string="std_ulogic";
  else bit_string="bit";


  *out << "------------------------------" << endl;
  *out << "-- write errors to output file" << endl;
  *out << "------------------------------" << endl;
  *out << "PROCEDURE write_errors(FILE f     : text;" << endl;
  *out << "                       field_name : string;" << endl;
  *out << "                       vec_num    : natural;" << endl;
  *out << "                       exp, res   : " << bit_string.toLatin1().toStdString() << ") IS" << endl;
  *out << "  VARIABLE L : line;" << endl;
  *out << "BEGIN" << endl;
  *out << "  write(L, string'(\"ERROR in field \") & field_name & string'(\" on vector \"));" << endl;
  *out << "  write(L, vec_num);" << endl;
  *out << "  write(L, string'(\" at time \"));" << endl;
  *out << "  write(L, now);" << endl;
  *out << "  writeline(f, L);" << endl;
  *out << "  write(L, string'(\"Res: \") & " << bit_string.toLatin1().toStdString() << "'image(res));" << endl;
  *out << "  writeline(f, L);" << endl;
  *out << "  write(L, string'(\"Exp: \") & " << bit_string.toLatin1().toStdString() << "'image(exp));" << endl;
  *out << "  writeline(f, L);" << endl;
  *out << "  writeline(f, L);                    -- outputs a blank line" << endl;
  *out << "END PROCEDURE write_errors;" << endl << endl;

  *out << "PROCEDURE write_errors(FILE f     : text;" << endl;
  *out << "                       field_name : string;" << endl;
  *out << "                       vec_num    : natural;" << endl;
  *out << "                       exp, res   : " << bit_string.toLatin1().toStdString() << "_vector) IS" << endl;
  *out << "  VARIABLE L : line;" << endl;
  *out << "BEGIN" << endl;
  *out << "  write(L, string'(\"ERROR in field \") & field_name & string'(\" on vector \"));" << endl;
  *out << "  write(L, vec_num);" << endl;
  *out << "  write(L, string'(\" at time \"));" << endl;
  *out << "  write(L, now);" << endl;
  *out << "  writeline(f, L);" << endl;
  *out << "  write(L, string'(\"Res: \") & to_string(res));" << endl;
  *out << "  writeline(f, L);" << endl;
  *out << "  write(L, string'(\"Exp: \") & to_string(exp));" << endl;
  *out << "  writeline(f, L);" << endl;
  *out << "  writeline(f, L);                    -- outputs a blank line" << endl;
  *out << "END PROCEDURE write_errors;" << endl << endl;
}

/// Writes the check_results procedure to compare simulated results with expected results
void ExportTestbenchVHDL::writeCheckResultProcess(std::ofstream*out)
{


  using namespace std;

  QString bit_string;

  if (use_std_logic)
    bit_string="std_ulogic";
  else bit_string="bit";


  *out << "------------------------------------------------------------" << endl;
  *out << "-- compare expected versus result vector and log differences" << endl;
  *out << "------------------------------------------------------------" << endl;
  *out << "PROCEDURE check_results(" << endl;
  *out << "  VARIABLE L   : INOUT line;" << endl;
  *out << "  res          :       " << bit_string.toLatin1().toStdString() << ";" << endl;
  *out << "  field_name   :       string;" << endl;
  *out << "  vec_num      :       natural;" << endl;
  *out << "  FILE logfile :       text) IS" << endl;
  *out << "  VARIABLE errors_found : boolean := false;" << endl;
  *out << "  VARIABLE exp          : " << bit_string.toLatin1().toStdString() << ";" << endl;
  *out << "BEGIN" << endl;
  *out << "  read(L, exp);" << endl;
  *out << "  -- Use the 1164 don't-care notation" << endl;

  if(use_std_logic)
    *out << "  IF exp /= '-' THEN" << endl;

  *out << "    IF exp /= res THEN" << endl;
  *out << "      errors_found := true;" << endl;
  *out << "      errflag      := true;" << endl;
  *out << "    END IF;" << endl;
  if(use_std_logic)
    *out << "  END IF;" << endl;

  *out << "  IF errors_found THEN" << endl;
  *out << "    -- log to error file" << endl;
  *out << "    write_errors(logfile, field_name, vec_num, exp, res);" << endl << endl;

  *out << "    -- optionally log to transcript window" << endl;
  *out << "    IF show_errors THEN" << endl;
  *out << "      write_errors(output, field_name, vec_num, exp, res);" << endl;
  *out << "    END IF;" << endl;
  *out << "  END IF;" << endl;
  *out << "END PROCEDURE check_results;" << endl << endl;

  *out << "PROCEDURE check_results(" << endl;
  *out << "  VARIABLE L   : INOUT line;" << endl;
  *out << "  SIGNAL res   : IN    " << bit_string.toLatin1().toStdString() << "_vector;" << endl;
  *out << "  field_name   :       string;" << endl;
  *out << "  vec_num      :       natural;" << endl;
  *out << "  FILE logfile :       text) IS" << endl;
  *out << "  VARIABLE errors_found : boolean := false;" << endl;
  *out << "  VARIABLE exp          : " << bit_string.toLatin1().toStdString() << "_vector(res'length-1 DOWNTO 0);" << endl;
  *out << "BEGIN" << endl;
  *out << "  read(L, exp);" << endl;
  *out << "  my_loop:" << endl;
  *out << "  FOR i IN exp'range LOOP" << endl;
  *out << "    -- Use the 1164 don't-care notation" << endl;
  if(use_std_logic)
    *out << "    IF exp(i) /= '-' THEN" << endl;
  *out << "      IF exp(i) /= res(i) THEN" << endl;
  *out << "        errors_found := true;" << endl;
  *out << "        errflag      := true;" << endl;
  *out << "        EXIT my_loop;" << endl;
  *out << "      END IF;" << endl;
  if(use_std_logic)
    *out << "    END IF;" << endl;
  *out << "  END LOOP;" << endl;
  *out << "  IF errors_found THEN" << endl;
  *out << "    -- log to error file" << endl;
  *out << "    write_errors(logfile, field_name, vec_num, exp, res);" << endl << endl;

  *out << "    -- optionally log to transcript window" << endl;
  *out << "    IF show_errors THEN" << endl;
  *out << "      write_errors(output, field_name, vec_num, exp, res);" << endl;
  *out << "    END IF;" << endl;
  *out << "  END IF;" << endl;
  *out << "END PROCEDURE check_results;" << endl;
  *out << "-- end of subprogram section -----------------------------------------" << endl << endl;

}

/// Writes the improved observer process
void ExportTestbenchVHDL::writeNewObserverProcess(std::ofstream*out)
{
  using namespace std;

  bool io_names_t, synchronous_reset_t;


  synchronous_reset_t=synchronous_reset;
  io_names_t=io_names;


  *out << "    stimuli_observer : PROCESS" << endl;

  *out << "    VARIABLE Li     : line;             -- pointer to file input buffer" << endl;
  *out << "    FILE vectorfile : text OPEN read_mode IS \"" << testvector_name.toLatin1().toStdString() << "\";" << endl;
  *out << "    VARIABLE Lo     : line;             -- pointer to file output buffer" << endl;
  *out << "    FILE resultfile : text OPEN write_mode IS \"" << logfile_name.toLatin1().toStdString() << "\";" << endl;


  *out << "    -- following definition of corresponding temp input buffer variables" << endl;
  *out << "    CONSTANT commentchar   : character := '#';  -- comment character" << endl;
  *out << "    VARIABLE vectorfirstc  : character := '#';  -- first character" << endl;
  *out << "    VARIABLE vectornum     : natural   := 0;    -- vector number" << endl;
  *out << "    VARIABLE vectordelimit : character := ' ';  -- delimiter character" << endl;
  *out << "                                                -- between signals/vectors" << endl;
  *out << "    VARIABLE iodelimit     : character := '|';  -- delimiter character" << endl;
  *out << "                                                -- between inputs/outputs" << endl;


  *out << " BEGIN" << endl;
  *out << "   WAIT FOR period;                    -- wait for reset" << endl;

  *out << "   WHILE NOT endfile(vectorfile) LOOP" << endl;
  *out << "     readline(vectorfile, Li);" << endl;
  *out << "      IF (Li /= NULL) AND (Li'length > 0) THEN" << endl;
  *out << "        read(Li, vectorfirstc);" << endl;
  *out << "        IF (vectorfirstc /= commentchar) THEN  -- check for comment character" << endl;
  *out << "          read(Li, vectornum);          -- read vector no." << endl << endl;
  *out << "          -- read and assign input signals" << endl;

    if(synchronous_reset)
    {
        *out << "         read_delimiter(Li, vectordelimit);" << endl;
        if(neg_reset)
          *out << "         read_assign(Li, srst_n);" << endl;
        else *out << "         read_assign(Li, srst_p);" << endl;
    }
    if(synchronous_enable)
    {
        *out << "         read_delimiter(Li, vectordelimit);" << endl;
        *out << "         read_assign(Li, sen_p);" << endl;
    }

  if (io_names_t)
  {
    QStringList inputs=(machine->retranslateNames(machine->getInputNameList())).split(",");
    QStringList::iterator i;
    int pos1=0,pos2=0;


    if(machine->getNumInputs()>0)
    {
      for (i = inputs.begin(); i != inputs.end(); ++i)
      {
        if((pos1=i->find("[")) !=-1 && i->find("..") !=-1 && (pos2=i->find("]")) !=-1)
        {
          i->remove(pos1,pos2-pos1+1);
        }
        *out << "         read_delimiter(Li, vectordelimit);" << endl;
        *out << "         read_assign(Li, " << i->toLatin1().toStdString() << ");" << endl;
      }
    }
  }
  else
  {

    *out << "         read_assign(Li, a);" << endl;
  }

  *out << "          WAIT FOR period;" << endl;
  *out << "          read_delimiter(Li, vectordelimit);" << endl;
  *out << "          read_delimiter(Li, iodelimit);" << endl << endl;

  *out << "          -- read and compare output signals" << endl;

  if (io_names_t)
  {
    QStringList::iterator i;
    int pos1=0,pos2=0;
    if (machine->getNumMooreOutputs()>0)
    {
      QStringList mooreOutputs=(machine->retranslateNames(machine->getMooreOutputList())).split(",");
      for (i = mooreOutputs.begin(); i != mooreOutputs.end(); ++i)
      {
        if((pos1=i->find("[")) !=-1 && i->find("..") !=-1 && (pos2=i->find("]")) !=-1)
        {
          i->remove(pos1,pos2-pos1+1);
        }
        *out << "          read_delimiter(Li, vectordelimit);" << endl;
        *out << "          check_results (Li, " << i->toLatin1().toStdString() << ", string'(\"" << i->toLatin1().toStdString() << "\"), vectornum, resultfile);" << endl;
      }
    }
    if (machine->getNumOutputs()>0)
    {

      QStringList mealyOutputs=(machine->retranslateNames(machine->getOutputNameList())).split(",");
      for (i = mealyOutputs.begin(); i != mealyOutputs.end(); ++i)
      {
        if((pos1=i->find("[")) !=-1 && i->find("..") !=-1 && (pos2=i->find("]")) !=-1)
        {
          i->remove(pos1,pos2-pos1+1);
        }
        *out << "          read_delimiter(Li, vectordelimit);" << endl;
        *out << "          check_results (Li, " << i->toLatin1().toStdString() << ", string'(\"" << i->toLatin1().toStdString() << "\"), vectornum, resultfile);" << endl;
      }
    }
  }
  else
  {
    if(machine->getNumMooreOutputs()>0)
    {
      *out << "          read_delimiter(Li, vectordelimit);" << endl;
      *out << "          check_results (Li, q, string'(\"q\"), vectornum, resultfile);" << endl;

    }

    if(machine->getNumOutputs()>0)
    {
      *out << "          read_delimiter(Li, vectordelimit);" << endl;
      *out << "          check_results (Li, o, string'(\"o\"), vectornum, resultfile);" << endl;

    }
  }



 *out << endl << "       END IF;  -- first character is a comment    " << endl;
 *out << "     END IF;  -- line is not null" << endl;
*out << "    END LOOP;  -- while not end of file" << endl << endl;

*out << "    IF errflag THEN                     -- check global error flag" << endl;
*out << "      REPORT \"Error: Verification NOT successful!\" & lf &" << endl;
*out << "        \"Check log file for details.\"" << endl;
*out << "        SEVERITY note;" << endl;
*out << "    ELSE" << endl;
*out << "      REPORT \"No errors !\"" << endl;
*out << "        SEVERITY note;" << endl;
*out << "      write(Lo, string'(\"No errors !\"));" << endl;
*out << "      writeline(resultfile, Lo);" << endl;
*out << "    END IF;" << endl << endl;

*out << "    clken_p <= false;" << endl;
*out << "    WAIT;" << endl;
*out << "  END PROCESS;" << endl;

*out << "-------------------------------------------------------------------------------" << endl;

}


#ifdef FHA

/// Writes a comment to the top of the output stream
void ExportTestbenchVHDL::writeHeader(std::ofstream*out,QString commentstart, QString commentend)
{
  QString description = machine->getDescription();
  description.replace('\n',"\n"+commentstart+"              ");
  *out << commentstart.toLatin1() << "----------------------------------------------------------------" << commentend.toLatin1() << "\n";
  *out << commentstart.toLatin1() << " Module     : " << machine->getName().toLatin1() << commentend.toLatin1() << "\n";
  *out << commentstart.toLatin1() << "----------------------------------------------------------------" << commentend.toLatin1() << "\n";
  *out << commentstart.toLatin1() << " Author     : " << machine->getAuthor().toLatin1() << commentend.toLatin1() << "\n";
  *out << commentstart.toLatin1() << " Company    : University of Applied Sciences Augsburg" << commentend.toLatin1() << "\n";
  *out << commentstart.toLatin1() << "----------------------------------------------------------------" << commentend.toLatin1() << "\n";
  *out << commentstart.toLatin1() << " Description: "  << description.toLatin1() << commentend.toLatin1() << "\n";
  *out << commentstart.toLatin1() << "----------------------------------------------------------------" << commentend.toLatin1() << "\n";
  *out << commentstart.toLatin1() << " Revisions : " << machine->getVersion().toLatin1() << " - " << commentend.toLatin1() << "\n";
  *out << commentstart.toLatin1() << "----------------------------------------------------------------" << commentend.toLatin1() << "\n";
}
#else
/// Writes the header (some comments) into the file.
void ExportTestbenchVHDL::writeHeader(std::ofstream*out,QString commentstart, QString commentend)
{
  using namespace std;

  // Write some comment
  QWidget* wm = qApp->mainWidget();
  AppInfo ai(wm);

  *out << commentstart.toLatin1().toStdString() << " This file was generated by		" <<
    commentend.toLatin1().toStdString() << endl;
  *out << commentstart.toLatin1().toStdString() << " Qfsm Version " << ai.getVersionMajor() << "."
       << ai.getVersionMinor() << "			" << commentend.toLatin1().toStdString() << endl;
  *out << commentstart.toLatin1().toStdString() << " (C) " << ai.getAuthor().toLatin1().toStdString() << "			"
       << commentend.toLatin1().toStdString() << endl << endl;

}

#endif

