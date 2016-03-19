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

#include "ExportVHDLFHA.h"
#include "Machine.h"
#include "TransitionInfo.h"
#include "IOInfo.h"
#include "IOInfoList.h"
#include "Convert.h"
#include "Utils.h"
#include "Options.h"

using namespace std;


ExportVHDLFHA::ExportVHDLFHA(Options* opt)
  : Export(opt)
{
  synchronous_reset = false;
}


/// Writes all the relevant data into the tdf file.
void ExportVHDLFHA::doExport()
{
//  state_encoding=!options->getVHDLSymbolicStates();
//  synchronous_reset=options->getVHDLSyncReset();
//  use_std_logic=options->getVHDLStdLogic();
//default values
  synchronous_reset=options->getVHDLSyncReset();

  writeHeader("--", "");
  writeDescription();
  writeEnvironment();
  writeEntity();
  writeArchitecture();
}


QString ExportVHDLFHA::fileFilter()
{
  return "VHDL (*.vhdl *.vhd)";
}

/// Writes the 'library' and 'use' lines to the output stream
void ExportVHDLFHA::writeEnvironment()
{

  *out << "LIBRARY IEEE;" << endl << endl;
  *out << "USE IEEE.std_logic_1164.ALL;" << endl << endl;

}

/// Writes the 'entity' block to the output stream
void ExportVHDLFHA::writeEntity()
{
  QString bit_string;


  bit_string = "std_ulogic";


  mname = machine->getName();
  mname.replace(QRegExp(" "), "_");

  *out << "ENTITY " << mname.latin1() << " IS" << endl;
//  *out << "--  generic (prop_delay : Time := 10 ns);" << endl;
  *out << "  PORT (clk: IN " << bit_string.latin1() << ";" << endl;
  *out << "        rst_n: IN " << bit_string.latin1() << ";" << endl;
  if(synchronous_reset)
    *out << "        srst_n: IN " << bit_string.latin1() << ";" << endl;
  QStringList inputs=machine->getInputNameList();
  QStringList::const_iterator i;
  for (i = inputs.constBegin(); i != inputs.constEnd(); ++i)
    *out << "        " << i->latin1() << ": IN "<< bit_string.latin1() << ";\n";

  if (machine->getNumMooreOutputs()>0)
  {
    QStringList mooreOutputs=machine->getMooreOutputList();
    for (i = mooreOutputs.constBegin(); i != mooreOutputs.constEnd(); ++i)
    {
      *out << "        " << i->latin1() << ": OUT "<< bit_string.latin1();
      if((i+1)!=mooreOutputs.constEnd() || machine->getNumOutputs()>0)
        *out<< ";\n";
    }
  }
  if (machine->getNumOutputs()>0)
  {
    QStringList mealyOutputs=machine->getOutputNameList();
    for (i = mealyOutputs.constBegin(); i != mealyOutputs.constEnd(); ++i)
    {
      *out << "        " << i->latin1() << ": OUT "<< bit_string.latin1();
      if((i+1)!=mealyOutputs.constEnd())
        *out<< ";\n";
    }
  }
  *out << ");\n";

  *out << "END " << mname.latin1() << ";" << endl << endl;
}




/// Writes the 'architecture' block to the output stream
void ExportVHDLFHA::writeArchitecture()
{
  QString bit_string;


  bit_string = "std_ulogic";


  *out << "ARCHITECTURE behave OF " << mname.latin1() << " IS" << endl << endl;

  QList<GState*> slist = machine->getSList();
  QString stmp;
  QMutableListIterator<GState*> it(slist);
  bool first=TRUE;
  for(; it.hasNext();)
  {
    GState* st = it.next();
    if (!first)
      stmp += ", ";
    stmp += Utils::noWS(st->getStateName());
    first=FALSE;
  }
  *out << "TYPE state_type IS (" << stmp.latin1() << ");" << endl;
  *out << "SIGNAL next_state, current_state : state_type;" << endl << endl;

/*
  *out << "-- comments for syf which comes with alliance : http://www-asim.lip6.fr/alliance"<<endl;
  *out << "-- interpreted as comments by other tools"<<endl;
  *out << "  --pragma CURRENT_STATE current_state" << endl;
  *out << "  --pragma NEXT_STATE next_state" << endl;

  *out << "  --pragma CLOCK clock" << endl << endl;
*/


  *out << "BEGIN" << endl;
// state output ******************
//  *out << "  current_state_out <= current_state;" << endl << endl;
  writeClockProcess();
  writeStateProcess();
  *out << "END behave;" << endl;
}




/// Writes the clock process to the output stream
void ExportVHDLFHA::writeClockProcess()
{

  if(synchronous_reset)
    *out << "  state_register: PROCESS (srst_n, rst_n, clk)" << endl;
  else *out << "  state_register: PROCESS (rst_n, clk)" << endl;


  *out << "  BEGIN" << endl;

//  if (!synchronous_reset)
//  {
  *out << "    IF rst_n='0' THEN" << endl;

  GState* stmp = machine->getInitialState();


  *out << "      current_state <= " <<
      Utils::noWS(stmp->getStateName()).latin1() 
      << ";" << endl;
    
  *out << "    ELSIF rising_edge(clk) THEN" << endl;
  if (synchronous_reset)
  {
    GState* istate;
    istate = machine->getInitialState();
    
    *out << "      IF srst_n='0' THEN " << endl; 
    *out << "        current_state <= " <<
        Utils::noWS(istate->getStateName()).latin1() 
        << ";" << endl;
        
    *out << "      ELSE" << endl;
    *out << "        current_state <= next_state;" << endl;
    *out << "      END IF;" << endl;
  }
  else *out << "      current_state <= next_state;" << endl;
  *out << "    END IF;" << endl;
  *out << "  END PROCESS;" << endl << endl;
}



/// Writes the input/current_state process to the output stream
void ExportVHDLFHA::writeStateProcess()
{
  GState* s;
  GTransition* t;
  QString tinfoi, tinfoo, sn;
  State* stmp;
  TransitionInfo* tinfo;
  IOInfo* iosingle;
  IOInfo* tioinfo;
  bool first;
  Convert conv;
  QStringList inputs=machine->getInputNameList();
  QStringList::const_iterator i;


  *out << "  next_state_and_output_logic: PROCESS (current_state";


  for (i=inputs.constBegin(); i != inputs.constEnd(); ++i)
    *out << " , " << i->latin1();
  *out << ")\n";
  if(machine->getNumInputs()>0)
    *out << "    VARIABLE temp_input : std_ulogic_vector("<< machine->getNumInputs()-1 << " DOWNTO 0);" << endl;
  if(machine->getNumMooreOutputs()>0)
    *out << "    VARIABLE temp_output : std_ulogic_vector("<< machine->getNumMooreOutputs()-1 << " DOWNTO 0);" << endl;
  if(machine->getNumOutputs()>0)
    *out << "    VARIABLE temp_mealy_output : std_ulogic_vector("<< machine->getNumOutputs()-1 << " DOWNTO 0);" << endl;
  *out << "  BEGIN" << endl;




  i=inputs.constBegin();
  if(machine->getNumInputs() == 1)
    *out << "    temp_input(0) := " << i->latin1();
  else if(machine->getNumInputs() >1)
  {
    *out << "    temp_input := " << i->latin1();
    ++i;
    for (; i != inputs.constEnd(); ++i)
      *out << " & " << i->latin1();
  }
  *out << ";\n";



  *out << "    CASE current_state IS";

  QMutableListIterator<GState*> is(machine->getSList());

  for(; is.hasNext();)
  {
    s = is.next();
    sn = s->getStateName();
    sn.replace(QRegExp(" "), "_");
    if (s->countTransitions()>0)
    {
      *out << endl << "      WHEN " << Utils::noWS(s->getStateName()).latin1() << " =>";

      if (machine->getNumMooreOutputs() > 0) 
      {
        IOInfo* mout;
        QString smout;
        mout = s->getMooreOutputs();
        smout = mout->convertToBinStr();

    //mealy outputs
        if (!smout.isEmpty())
        {
          *out << " temp_output := \"";
          QStringList outputs=machine->getMooreOutputList();
          QStringList::const_iterator i=outputs.constBegin();
          int c=0;
          while (i != outputs.constEnd())
          {
            *out << smout[c].toLatin1();
            c++;
            ++i;
          }
          *out << "\";\n";
        }
      }
      else *out << "\n";
    
    
      QListIterator<GTransition*> it(s->tlist);
      *out << "        CASE temp_input IS";
      for(; it.hasNext();)
      {
        t = it.next();
        tinfo = t->getInfo();
        tioinfo = tinfo->getInputInfo();
    
        if (!t->isDeleted() && t->getEnd())
        {
          IOInfoList iolist;
          tioinfo->convertToBinList(iolist, FALSE);
    
          QMutableListIterator<IOInfo*> ioit(iolist);
          *out << endl << "          WHEN ";
    
          first = TRUE;
          for(; ioit.hasNext();)
          {
    
            iosingle = ioit.next();
            tinfoi = iosingle->convertToBinStr();  
            tinfoi.replace(QRegExp("x"), "-");
    
            if (!tinfoi.isEmpty())
            {
              if (!first)
              {
                *out << " |";
              }
              *out << " \"";
              int slen = tinfoi.length();
              int numin = machine->getNumInputs();
              for(int k=slen; k<numin; k++)
                *out << "0";
    
              *out << tinfoi.latin1() << "\"";
              first=FALSE;
            }
          }
    
          tinfoo = tinfo->getOutputsStrBin();
          *out << " => ";
        //mealy output
          if (!tinfoo.isEmpty())
          {
            *out << " temp_mealy_output := \"";
    
            int slen = tinfoo.length();
            int numout = machine->getNumOutputs();
            for(int l=slen; l<numout; l++)
              *out << "0";

            *out << tinfoo.latin1() << "\";" << endl << "            ";
          }
          stmp = t->getEnd();
          if (stmp)
          {
            sn = stmp->getStateName();
            sn.replace(QRegExp(" "), "_");
          }
    

          *out << " next_state <= " <<
              Utils::noWS(stmp->getStateName()).latin1() << ";";
            
        }
      }
      *out << endl << "          WHEN OTHERS => next_state <= current_state;" << endl;
      *out << "        END CASE;" << endl;
    }
  }

//  *out << "      when others => null;" << endl;
  *out << "    END CASE;" << endl;
    //moore outputs
  if(machine->getNumMooreOutputs()>0)
  {;
  QStringList outputs=machine->getMooreOutputList();
  QStringList::const_iterator i=outputs.constBegin();
  int c=machine->getNumMooreOutputs()-1;
  while (i != outputs.constEnd())
  {
    *out << "    " << i->latin1() << " <= temp_output(" << c << ");\n";
    c--;
    ++i;
  }
  }
  if(machine->getNumOutputs()>0)
  {;
  QStringList outputs=machine->getOutputNameList();
  QStringList::const_iterator i=outputs.constBegin();
  int c=machine->getNumOutputs()-1;
  while (i != outputs.constEnd())
  {
    *out << "    " << i->latin1() << " <= temp_mealy_output(" << c << ");\n";
    c--;
    ++i;
  }
  }

  *out << "  END PROCESS;" << endl << endl;
}

/// Writes a comment to the top of the output stream 
void ExportVHDLFHA::writeHeader(QString commentstart, QString commentend)
{
  *out << commentstart.latin1() << "----------------------------------------------------------------" << commentend.latin1() << endl;
  *out << commentstart.latin1() << " Module     : " << machine->getName().latin1() << commentend.latin1() << endl;
  *out << commentstart.latin1() << "----------------------------------------------------------------" << commentend.latin1() << endl;
  *out << commentstart.latin1() << " Author     : " << commentend.latin1() << endl;
  *out << commentstart.latin1() << " Company    : University of Applied Sciences Augsburg" << commentend.latin1() << endl;
  *out << commentstart.latin1() << "----------------------------------------------------------------" << commentend.latin1() << endl;
  *out << commentstart.latin1() << " Description: " << commentend.latin1() << endl;
  *out << commentstart.latin1() << "----------------------------------------------------------------" << commentend.latin1() << endl;
  *out << commentstart.latin1() << " Revisions : " << machine->getVersion().latin1() << " - " << commentend.latin1() << endl;
  *out << commentstart.latin1() << "----------------------------------------------------------------" << commentend.latin1() << endl;
}

/// Writes the machine description to the output stream
void ExportVHDLFHA::writeDescription()
{

  *out << endl;
  if(machine->getNumInputs()>0)
  {
    *out << "-- Inputs:";
    QStringList inputs=machine->getInputNameList();
    QStringList::const_iterator i;
    for(i=inputs.constBegin(); i!=inputs.constEnd(); ++i)
    {
      *out << "   "<< i->latin1();
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
      *out << "   "<< i->latin1();
    }
    *out << endl;
  }


  QList<GState*>states= machine->getSList();
  QList<GState*>::const_iterator is;
  int *textLen=new int[machine->getNumMooreOutputs()+1];
  textLen[0]=12;

  for(is=states.constBegin(); is!=states.constEnd(); ++is)
  {
    if((*is)->getStateName().length()>textLen[0])
      textLen[0]=(*is)->getStateName().length();
  }
  textLen[0]++;

  *out << "-- State/Output" << QString(textLen[0]-13,' ').latin1();


  if(machine->getNumMooreOutputs()>0)
  {
    int spc=1;
    QStringList outputs=machine->getMooreOutputList();
    QStringList::const_iterator i;
    for(i=outputs.constBegin(); i!=outputs.constEnd(); ++i)
    {
      textLen[spc]=i->length()+1;
      spc++;
      *out << " "<< i->latin1();
    }
  }
  *out << endl;

  IOInfo*mooreOutput;
  QString sMooreOutput;

  for(is=states.constBegin(); is!=states.constEnd(); ++is)
  {
    int spc=0;
    *out << "-- " << (*is)->getStateName().latin1() << QString(textLen[spc]-(*is)->getStateName().length(),' ').latin1();
    spc++;
    if(machine->getNumMooreOutputs()>0)
    {
      mooreOutput=(*is)->getMooreOutputs();
      sMooreOutput=mooreOutput->convertToBinStr();
      int c=0;
      while(c<sMooreOutput.length())
      {
        *out << sMooreOutput[c].toLatin1() << QString(textLen[spc]-1,' ').latin1();
        c++;
        spc++;
      }
    }
    *out << endl;
  }
  *out << endl;
  delete[] textLen;
}

