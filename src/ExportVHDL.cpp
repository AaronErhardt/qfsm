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

#include "QApplication"
#include "AppInfo.h"
#include "ExportVHDL.h"
#include "Machine.h"
#include "TransitionInfo.h"
#include "IOInfo.h"
#include "IOInfoList.h"
#include "Convert.h"
#include "Utils.h"
#include "Options.h"



static const char* const std_ulogicOrBit[]={"bit","std_ulogic"};

ExportVHDL::ExportVHDL(Options* opt)
    : Export(opt)
{
  state_encoding = false;
  io_names = false;
  synchronous_reset = false;
  synchronous_enable = false;
  neg_reset = false;
  use_std_logic = true;
  io_header = true;
  alliance = false;
  cond_notation = 1;
  state_code = false;
  debug_state = false;
}

/**
 * Initializes the export object.
 * @a oe is a pointer to the output stream opened with the standard fstream methods for writing the entity file.
 * @a oa is a pointer to the output stream opened with the standard fstream methods for writing the architecture file.
 */
void ExportVHDL::init(std::ofstream* oe,std::ofstream*oa, Machine* m, QString fn/*=QString::null*/, ScrollView* sv/*=NULL*/)
{
  oute = oe;
  outa = oa;
  machine = m;
  fileName = fn;
  scrollview = sv;
}

/// Writes all the relevant data into the tdf file.
void ExportVHDL::doExport()
{
  state_encoding=!options->getVHDLSymbolicStates();
  io_names=options->getVHDLInOutNames();
  synchronous_reset=options->getVHDLSyncReset();
  synchronous_enable=options->getVHDLSyncEnable();
  neg_reset=options->getVHDLNegReset();
  use_std_logic=options->getVHDLStdLogic();
  io_header=options->getVHDLIOheader();
  alliance=options->getVHDLAlliance();
  cond_notation=options->getVHDLCondNotation();
  state_code = options->getVHDLStateCode();
  sep_files = options->getVHDLSepFiles();
  sync_look_ahead = options->getVHDLSyncLookAhead();
  architecture_name = options->getVHDLArchitectureName();
  debug_state = options->getVHDLDebugState();


  writeHeader(oute,"--", "");
  if (io_header)
    writeDescription(oute);
  writeEnvironment(oute);
  writeEntity(oute);
  if(sep_files)
  {
    writeHeader(outa,"--", "");
    if (io_header)
      writeDescription(outa);
    writeEnvironment(outa);
  }
  writeArchitecture(outa);
}


QString ExportVHDL::fileFilter()
{
  return "VHDL (*.vhd *.vhdl)";
}

QString ExportVHDL::defaultExtension()
{
  return "vhd";
}

/// Writes the 'library' and 'use' lines to the output stream
void ExportVHDL::writeEnvironment(std::ofstream *out)
{
  using namespace std;

  if (use_std_logic)
  {
    *out << "LIBRARY IEEE;" << endl << endl;
    *out << "USE IEEE.std_logic_1164.ALL;" << endl << endl;
  }
}


static QString appendableVectorDefinition(QString& input)
{
  QString vector;
  int pos1=0,pos2=0;
  if ((pos1=input.indexOf('[')) !=-1 && input.indexOf("..") !=-1 && (pos2=input.indexOf(']')) !=-1)
  {
    vector="_vector"+input.mid(pos1,pos2-pos1+1);
    vector.replace(".."," DOWNTO ");
    vector.replace('[','(');
    vector.replace(']',')');
    input.remove(pos1,pos2-pos1+1);
  }

  return vector;
}

int numbits (int n)
{
  int i;
  for (i=0;(1 << i) < n;i++)
    ;
  return i;
}


/// Writes the 'entity' block to the output stream
void ExportVHDL::writeEntity(std::ofstream*out)
{
  using namespace std;

  const char* const bit_string=std_ulogicOrBit[use_std_logic];

  //take values into account depending on alliance value
  bool io_names_t=!alliance && io_names;            //true only when !alliance
  bool state_encoding_t=!alliance && state_encoding;//true only when !alliance
  bool synchronous_reset_t=alliance || synchronous_reset;//false only when !alliance


  mname = machine->getName();
  mname.replace(' ', '_');
  if (mname.isEmpty()) mname="StateMachine";

  *out << "ENTITY " << mname.toLatin1().constData() << " IS" << endl;
  //*out << "--  generic (prop_delay : Time := 10 ns);" << endl;
  *out << "  PORT (clk: IN " << bit_string << ";" << endl;
  if (synchronous_reset_t)
  {
    *out << "        " << (neg_reset?"srst_n":"srst_p")
         <<": IN " << bit_string << ";" << endl;
  }
    if (synchronous_enable)
  {
    *out << "        sen_p" <<": IN " << bit_string << ";" << endl;
  }
  if (!alliance)
  {
    *out << "        " << (neg_reset?"rst_n":"rst_p")
         << ": IN " << bit_string << ";" << endl;
  }

  if (io_names_t)
  {
    if(machine->getNumInputs() >0)
    {
      foreach(QString input, machine->retranslateNames(machine->getInputNameList()).split(","))
      {
        QString vector=appendableVectorDefinition(input);
        *out << "        " << input.toLatin1().constData() << ": IN "<< bit_string << vector.toLatin1().constData() << ";\n";
      }
    }

    if (machine->getNumMooreOutputs()>0)
    {
      QStringList mooreOutputs=(machine->retranslateNames(machine->getMooreOutputList())).split(',');
      int size=mooreOutputs.size();
      int counter=0;
      foreach(QString output, mooreOutputs)
      {
        QString vector=appendableVectorDefinition(output);
        *out << "        " << output.toLatin1().constData() << ": OUT "<< bit_string << vector.toLatin1().constData();
        if ((++counter)!=size || machine->getNumOutputs()>0 || debug_state)
          *out<< ";" << endl;
      }
    }
    if (machine->getNumOutputs()>0)
    {

      QStringList mealyOutputs=(machine->retranslateNames(machine->getOutputNameList())).split(',');
      int size=mealyOutputs.size();
      int counter=0;
      foreach(QString output, mealyOutputs)
      {
        QString vector=appendableVectorDefinition(output);
        *out << "        " << output.toLatin1().constData() << ": OUT "<< bit_string << vector.toLatin1().constData();
        if ((++counter)!=size || debug_state)
          *out<< ";" << endl;
      }
    }
    if (debug_state) 
    {
      int numStateBits = numbits (machine->getNumStates());

      *out << "        " << "debug_state" << ": OUT "<< bit_string << "_vector (" << numStateBits -1 << " DOWNTO 0)";
    }
    *out << ");\n";
  }
  else // ! io_names
  {
    if(machine->getNumInputs()>0)
      *out << "        a: IN " << bit_string << "_vector(" << machine->getNumInputs()-1 << " DOWNTO 0)";
    if (machine->getNumMooreOutputs()>0)
    {
      if(machine->getNumInputs()>0)
        *out << ";\n";
      *out << "        q: OUT " << bit_string << "_vector(" << machine->getNumMooreOutputs()-1 << " DOWNTO 0)";
    }
    if (machine->getNumOutputs()>0)
    {
      if(machine->getNumInputs()>0 || machine->getNumMooreOutputs()>0)
        *out << ";\n";
      *out << "        o: OUT " << bit_string << "_vector(" << machine->getNumOutputs()-1 << " DOWNTO 0)";
    }
    *out << ");" << endl;
  }  // end if

  *out << "END " << mname.toLatin1().constData() << ";" << endl << endl;
}




/// Writes the 'architecture' block to the output stream
void ExportVHDL::writeArchitecture(std::ofstream*out)
{
  using namespace std;

  const char* const bit_string=std_ulogicOrBit[use_std_logic];

  //take values into account depending on alliance value
  bool io_names_t=!alliance && io_names;
  bool state_encoding_t=!alliance && state_encoding;
  bool synchronous_reset_t=alliance || synchronous_reset;



  *out << "ARCHITECTURE " << architecture_name.toLatin1().constData() << " OF " << mname.toLatin1().constData() << " IS" << endl << endl;
  if (!state_encoding_t)
  {
    QList<GState*> slist = machine->getSList();
    QString stmp;
    QMutableListIterator<GState*> it(slist);
    bool first=TRUE;
    for (; it.hasNext();)
    {
      GState* st = it.next();
      if (st->isDeleted())
        continue;
      if (!first)
        stmp += ", ";
      stmp += Utils::noWS(st->getStateName());
      first=FALSE;
    }

    if (state_code)
    {
      *out << "SIGNAL current_state, next_state : "
           << bit_string << "_vector(" << machine->getNumEncodingBits()-1 << " DOWNTO 0);" << endl << endl;

      it.toFront();
      for (; it.hasNext();)
      {
        GState* st = it.next();
        if (st->isDeleted())
          continue;
        *out << "CONSTANT " << Utils::noWS(st->getStateName()).toLatin1().constData() << " : "
             << bit_string << "_vector(" << machine->getNumEncodingBits()-1 << " DOWNTO 0)"
             <<" := \"" << st->getCodeStr().toLatin1().constData() << "\";\n";
      }
    }
    else
    {
      *out << "TYPE state_type IS (" << stmp.toLatin1().constData() << ");" << endl;
      *out << "SIGNAL next_state, current_state : state_type;" << endl;
    }
  }
  else
  {
    *out << "SIGNAL current_state, next_state : " << bit_string << "_vector(" <<
    machine->getNumEncodingBits()-1
    << " DOWNTO 0);" << endl;
  }

  if(sync_look_ahead && machine->getNumMooreOutputs()>0)
  {
    *out << "SIGNAL next_output : " << bit_string << "_vector(" << machine->getNumMooreOutputs()-1 << " DOWNTO 0);" << endl;

  }
  *out << endl;


  if (alliance)
  {
    *out << "-- comments for syf which comes with alliance : http://www-asim.lip6.fr/alliance"<<endl;
    *out << "-- interpreted as comments by other tools"<<endl;
    *out << "  --pragma CURRENT_STATE current_state" << endl;
    *out << "  --pragma NEXT_STATE next_state" << endl;
    *out << "  --pragma CLOCK clk" << endl << endl;
  }


  *out << "BEGIN" << endl;
  writeClockProcess(out);
  writeStateProcess(out);

  if(sync_look_ahead && machine->getNumMooreOutputs()>0)
  {
    writeOutputProcess(out);
    writeOutputBufferProcess(out);
  }

  *out << "END " << architecture_name.toLatin1().constData() << ";" << endl;
}




/// Writes the clock process to the output stream
void ExportVHDL::writeClockProcess(std::ofstream*out)
{
  using namespace std;

  //take values into account depending on alliance value
  bool io_names_t=!alliance && io_names;
  bool state_encoding_t=!alliance && state_encoding;
  bool synchronous_reset_t=alliance || synchronous_reset;


  if (alliance)
  {
    *out << "  state_register: PROCESS (clk)" << endl;
    *out << "  BEGIN" << endl;
  }
  else
  {
    if (synchronous_reset_t)
    {
      if (neg_reset)  *out << "  state_register: PROCESS (srst_n, rst_n, ";
      else            *out << "  state_register: PROCESS (srst_p, rst_p, ";
    }
    else
    {
      if (neg_reset)  *out << "  state_register: PROCESS (rst_n, ";
      else            *out << "  state_register: PROCESS (rst_p, ";
    }

    if(synchronous_enable)
      *out << "sen_p, clk)" << endl;
    else *out << "clk)" << endl;

    *out << "  BEGIN" << endl;

    if (neg_reset)  *out << "    IF rst_n='0' THEN" << endl;
    else            *out << "    IF rst_p='1' THEN" << endl;

    GState* stmp = machine->getInitialState();

    if (state_encoding_t)
    {
      *out << "      current_state <= \"";
      *out << Convert::intToBinStr(stmp->getEncoding(), machine->getNumEncodingBits()).toLatin1().constData()
      << "\";" << endl;
    }
    else
    {
      *out << "      current_state <= " <<
      Utils::noWS(stmp->getStateName()).toLatin1().constData()
      << ";" << endl;
    }

    if (use_std_logic)
      *out << "    ELSIF rising_edge(clk) THEN" << endl;
    else *out << "    ELSIF clk'event and clk='1' THEN" << endl;


  }

  if (synchronous_reset_t && !alliance)
  {
    GState* istate;
    istate = machine->getInitialState();

    if (neg_reset)  *out << "      IF srst_n='0' THEN " << endl;
    else            *out << "      IF srst_p='1' THEN " << endl;


    if (state_encoding_t)
    {
      *out << "      current_state <= \"";
      *out << Convert::intToBinStr(istate->getEncoding(), machine->getNumEncodingBits()).toLatin1().constData()
      << "\";" << endl;
    }
    else
    {
      *out << "        current_state <= " <<
      Utils::noWS(istate->getStateName()).toLatin1().constData()
      << ";" << endl;
    }

    if(synchronous_enable)
    {
      *out << "      ELSIF sen_p='1' THEN" << endl;
    }
    else {
      *out << "      ELSE" << endl;
    }
    *out << "        current_state <= next_state;" << endl;
    *out << "      END IF;" << endl;
  }
  else
  {
    if (alliance)
      *out << "    IF ( clk = '1' AND NOT clk'STABLE ) THEN" << endl;
    if(synchronous_enable)
    {
      *out << "      IF sen_p='1' THEN" << endl;
      *out << "        current_state <= next_state;" << endl;
      *out << "      END IF;" << endl;
    }
    else {
      *out << "      current_state <= next_state;" << endl;
    }
  }

  *out << "    END IF;" << endl;
  *out << "  END PROCESS;" << endl << endl;
}



/// Writes the input/current_state process to the output stream
void ExportVHDL::writeStateProcess(std::ofstream*out)
{
  using namespace std;

  GState* s;
  GTransition* t;
  GTransition* default_trans;
  QString tinfoi, tinfoo, sn;
  State* stmp;
  TransitionInfo* tinfo;
  IOInfo* iosingle,*iosingle2;
  IOInfo* tioinfo;
  bool first, first_trans,any_tr,default_tr;
  Convert conv;
  const char* const bit_string=std_ulogicOrBit[use_std_logic];
  QString out_bit_string;

  QStringList inputs=machine->getInputNameList();
  QStringList outputs=machine->getOutputNameList();
  QStringList inputs_array=(machine->retranslateNames(machine->getInputNameList())).split(",");

  QStringList::iterator i;
  bool io_names_t, state_encoding_t, synchronous_reset_t;
  int cond_notation_t;
  int numStateBits = numbits(machine->getNumStates());
  //qDebug("numStateBits: %d", numStateBits);

  if (machine->getType()==1) // Binary machine
    io_names_t=false;

  if (alliance && machine->getType()==0)
  {
    io_names_t=false;
    state_encoding_t=false;
    synchronous_reset_t=false;
    cond_notation_t=0; // IF-THEN notation
  }
  else
  {
    io_names_t=io_names;
    state_encoding_t=state_encoding;
    synchronous_reset_t=synchronous_reset;
    cond_notation_t=cond_notation;
  }

  if(sync_look_ahead)
    *out << "  next_state_logic: PROCESS (current_state";
  else *out << "  next_state_and_output_logic: PROCESS (current_state";

 if(machine->getNumInputs()>0)
  {
    if (io_names_t)
    {
      for (i=inputs_array.begin(); i != inputs_array.end(); ++i)
      {
        i->replace(".."," DOWNTO ");
        i->replace('[','(');
        i->replace(']',')');
        *out << ", " << i->latin1();
      }
    }
    else
      *out << ", a";
  }
  *out << ")\n";

  if (io_names_t)
  {
    int debugStateBits;
    if (debug_state) debugStateBits = numbits (machine->getNumStates());
    else             debugStateBits = 0;

    // temporary variables
    if (machine->getNumInputs()>0)
      *out << "    VARIABLE temp_input : "<< bit_string << "_vector("<< machine->getNumInputs()-1 << " DOWNTO 0);" << endl;
    if (machine->getNumMooreOutputs()>0 && !sync_look_ahead || debugStateBits)
      *out << "    VARIABLE temp_output : "<< bit_string << "_vector("<<  debugStateBits + machine->getNumMooreOutputs()-1 << " DOWNTO 0);" << endl;
    if (machine->getNumOutputs()>0)
      *out << "    VARIABLE temp_mealy_output : "<< bit_string << "_vector("<< machine->getNumOutputs()-1 << " DOWNTO 0);" << endl;
    // end temporary
  }

  *out << "  BEGIN" << endl;

  if (io_names_t && machine->getNumInputs()>0)
  {
    i=inputs.begin();
    i->replace('[','(');
    i->replace(']',')');
    if (machine->getNumInputs() == 1)
      *out << "    temp_input(0) := " << i->latin1();
    else if (machine->getNumInputs() >1)
    {
      *out << "    temp_input := " << i->latin1();
      i++;

      for (; i != inputs.end(); ++i)
      {
        i->replace('[','(');
        i->replace(']',')');
        *out << " & " << i->latin1();
      }
    }
    *out << ";\n";
  }

  if (alliance)
  {
    GState* istate;
    istate = machine->getInitialState();

    if (neg_reset)  *out << "    IF srst_n='0' THEN " << endl;
    else            *out << "    IF srst_p='1' THEN " << endl;


    if (state_encoding_t)
    {
      *out << "      next_state <= \"";
      *out << Convert::intToBinStr(istate->getEncoding(), machine->getNumEncodingBits()).toLatin1().constData()
          << "\";" << endl;
    }
    else
    {
      *out << "        next_state <= " <<
          Utils::noWS(istate->getStateName()).toLatin1().constData()
          << ";" << endl;
    }

    *out << "    ELSE" << endl;
  }



  *out << "    CASE current_state IS" << endl;

  QMutableListIterator<GState*> is(machine->getSList());

  for (; is.hasNext();)
  {
    s = is.next();
    sn = s->getStateName();
    sn.replace(' ', '_');
    any_tr=false;

    if (s->countTransitions()>0)
    {
      if (state_encoding_t)
      {
        *out << "      WHEN \"" <<
            Convert::intToBinStr(s->getEncoding(),
                                 machine->getNumEncodingBits()).toLatin1().constData()
            << "\" =>";
      }
      else
      {
        *out << "      WHEN " << Utils::noWS(s->getStateName()).toLatin1().constData() << " =>";
      }
      if (machine->getNumMooreOutputs() > 0 && !sync_look_ahead)
      {
        IOInfo* mout = s->getMooreOutputs();
        QString smout = mout->convertToBinStr();

        if (!smout.isEmpty())
        {   
          *out << (io_names_t?" temp_output := \"":" q <= \"");
	  if (debug_state) 
	    //*out << Convert::intToBinStr(s->getEncoding(), machine->getNumEncodingBits()).toLatin1().constData();
	  {
	    QString sbincode = Convert::intToBinStr(s->getEncoding(), numStateBits);
	    if (sbincode==QString::null)
	      sbincode = Convert::intToBinStr(0, numStateBits);
	    *out << sbincode.toLatin1().constData();
	  }

          *out << smout.left(machine->getMooreOutputList().size()).toLatin1().constData();
          *out << "\";\n";
        }
        else
          *out << endl;
      }
      else *out << "\n";
    }

    QMutableListIterator<GTransition*> it(s->tlist);

    if(s->countTransitions()>0)
    {

      t = it.next();
      tinfo = t->getInfo();
      tioinfo = tinfo->getInputInfo();


      if(machine->getNumInputs()>0)
      {


        any_tr=false;
        default_tr=false;
        it.toFront();
        while(it.hasNext())
        {
          t=it.next();
          tinfo=t->getInfo();
          tioinfo=tinfo->getInputInfo();
          if(tioinfo->getAnyInput())
          {
            any_tr=true;
          }
          if(tioinfo->isDefault())
          {
            default_tr=true;
            default_trans=t;
          }
        }

        if(default_tr && s->countTransitions()==1)
        {
          default_tr=false;
          any_tr=true;
        }

        it.toFront();

        if(!any_tr)
        {
          if (cond_notation_t==1 && s->countTransitions()>0)
            *out << (io_names_t?"        CASE temp_input IS"
                               :"        CASE a IS")
            << endl;
        }

        first_trans=TRUE;


        while(it.hasNext() || default_tr)
        {

          if(!it.hasNext() && default_tr) //process default transition at the end
          {
            t=default_trans;
            default_tr=false;
          }
          else
          {
            t = it.next();
          }


          tinfo = t->getInfo();
          tioinfo = tinfo->getInputInfo();


          if (!t->isDeleted() && t->getEnd() &&
              !(any_tr && !(tioinfo->getAnyInput() || (tioinfo->isDefault() && s->countTransitions()==1))) &&
              !(default_tr && tioinfo->isDefault()))
          {
            if (!any_tr)
            {
              IOInfoList iolist;
              bool inv = tioinfo->isInverted();
              if (cond_notation_t==0) // IF-THEN notation
              {
                if (alliance)
                {
                  // treat info as non inverted (nasty workaround)
                  tioinfo->setInvert(false);
                }
                tioinfo->convertToBinList(iolist, false);

                if (alliance)
                  tioinfo->setInvert(inv);
              }
              else // CASE-WHEN notation
                tioinfo->convertToBinList(iolist, true);

              //  iolist.setAutoDelete(TRUE);

              QMutableListIterator<IOInfo*> ioit(iolist);


              for(int c1=0; c1<iolist.size(); c1++)
              {
                iosingle=iolist[c1];
                for(int c2=c1+1; c2<iolist.size(); c2++)
                {
                  iosingle2=iolist[c2];
                  if(iosingle->convertToBinStr() == iosingle2->convertToBinStr())
                  {
                    iolist.removeAt(c2);
                    qDebug(QString("removed "+iosingle->convertToBinStr()).latin1());
                    c2--;
                  }
                }

              }



              if (cond_notation_t==0)
              {
                if(tioinfo->isDefault())
                  *out << "        " << "ELSE ";
                else
                {
                  *out << "        " << (first_trans?"IF ":"ELSIF ");
                  *out << (io_names_t?"temp_input":"a");
                  *out << (tioinfo->isInverted()?"/=":"=");
                }
              }
              else
              {
                if(tioinfo->isDefault())
                  *out << "          WHEN OTHERS ";
                else *out << "          WHEN ";
              }

              if(!tioinfo->isDefault())
              {
                *out << "\"";

                first = TRUE;
                while ( ioit.hasNext())
                {

                  iosingle = ioit.next();
                  tinfoi = iosingle->convertToBinStr();
                  tinfoi.replace('x', '-');

                  if (!tinfoi.isEmpty())
                  {
                    if (cond_notation_t==0) // IF-THEN notation
                    {
                      if (!first)
                      {
                        *out << (tioinfo->isInverted()?"and ":"or ");
                        *out << (io_names_t?"temp_input":"a");
                        *out << (tioinfo->isInverted()?"/=":"=");
                        *out << '\"';
                      }
                    }
                    else // CASE-WHEN notation
                    {
                      if (!first)
                        *out << "| \"";
                    }

                    int slen = tinfoi.length();
                    int numin = machine->getNumInputs();
                    for (int k=slen; k<numin; k++)
                      *out << '0';

                    *out << tinfoi.toLatin1().constData() << "\" ";
                    first=FALSE;
                  }
                }
              }

              if (cond_notation_t==0) // IF-THEN notation
              {
                if(!tioinfo->isDefault())
                  *out << "THEN" << endl;
              }
              else // CASE-WHEN notation
                *out << "=>" << endl;
            }

            tinfoo = tinfo->getOutputsStrBin();
            if (!tinfoo.isEmpty())
            {
              if (cond_notation_t==1)
                *out << "  ";  // correct indent

              *out << "          " << (io_names_t?"temp_mealy_output := \"":"o <= \"");

              int numout = machine->getNumOutputs();
              for (int l=tinfoo.length(); l<numout; l++)
                *out << '0';

              *out << tinfoo.toLatin1().constData() << "\";" << endl;
            }
            stmp = t->getEnd();
            if (stmp)
            {
              sn = stmp->getStateName();
              sn.replace(' ', '_');
            }


            if (cond_notation_t==1)
              *out << "  ";  // correct indent

            if (state_encoding_t)
            {
              *out << "          next_state <= \""
                  << Convert::intToBinStr(stmp->getEncoding(),
                                          machine->getNumEncodingBits()).toLatin1().constData() << "\";" << endl;
            }
            else
            {
              *out << "          next_state <= " <<
                  Utils::noWS(stmp->getStateName()).toLatin1().constData() << ";" << endl;
            }



            first_trans=FALSE;
          }
        }
        if (!any_tr)
        {
          if (cond_notation_t==0) // IF-THEN notation
          {
            if (!alliance)
            {
              if(!tioinfo->isDefault())
              {
                *out << "        ELSE" << endl;
                *out << "          next_state <= current_state;" << endl;


              }
            }
            *out << "        END IF;" << endl;
          }
          else {
            if(!tioinfo->isDefault())
              *out << "          WHEN OTHERS => next_state <= current_state;" << endl;
            *out << "        END CASE;" << endl;   // temp_input
          }
        }


        //  *out << "      WHEN OTHERS => null;" << endl;
        // WHEN OTHERS => temp_output := (OTHERS => 'X');
        // next_state <= idle0;

      }
      else
      {
        GTransition*t;
        TransitionInfo*tinfo;
        QString tinfoo;
        State*stmp;
        QMutableListIterator<GTransition*> it(s->tlist);
        t=it.next();
        tinfo=t->getInfo();
        stmp=t->getEnd();

        tinfoo = tinfo->getOutputsStrBin();
        if (!tinfoo.isEmpty())
        {

          *out << "        " << (io_names_t?"temp_mealy_output := \"":"o <= \"");

          int numout = machine->getNumOutputs();
          for (int l=tinfoo.length(); l<numout; l++)
            *out << '0';

          *out << tinfoo.toLatin1().constData() << "\";" << endl;
        }

        if (state_encoding_t)
        {
          *out << "        next_state <= \""
              << Convert::intToBinStr(stmp->getEncoding(),
                                      machine->getNumEncodingBits()).toLatin1().constData() << "\";" << endl;
        }
        else
        {
          *out << "      next_state <= " <<
              Utils::noWS(stmp->getStateName()).toLatin1().constData() << ";" << endl;
        }
      }
    }
  }


  if(use_std_logic)
        out_bit_string="X\');";
  else out_bit_string="0\');";


  if(io_names_t)
  {
    if(machine->getNumMooreOutputs()>0 && machine->getNumOutputs()==0 && ! sync_look_ahead)
      *out << "      WHEN OTHERS => temp_output := (OTHERS =>\'" << out_bit_string.toLatin1().constData() << endl;
    else if(machine->getNumMooreOutputs()>0 && machine->getNumOutputs()>0)
    {
      *out << "      WHEN OTHERS => temp_output := (OTHERS =>\'" << out_bit_string.toLatin1().constData() << endl;
      *out << "        temp_mealy_output := (OTHERS =>\'" << out_bit_string.toLatin1().constData() << endl;
    }
    else if(machine->getNumOutputs()>0)
            *out << "      WHEN OTHERS => temp_mealy_output := (OTHERS =>\'" << out_bit_string.toLatin1().constData() << endl;
     else *out << "      WHEN OTHERS => NULL;" << endl;

  }
  else {
     if(machine->getNumMooreOutputs()>0 && machine->getNumOutputs()==0 && ! sync_look_ahead)
      *out << "      WHEN OTHERS => q <= (OTHERS =>\'" << out_bit_string.toLatin1().constData() << endl;
    else if(machine->getNumMooreOutputs()>0 && machine->getNumOutputs()>0 && !sync_look_ahead)
    {
      *out << "      WHEN OTHERS => q <= (OTHERS =>\'" << out_bit_string.toLatin1().constData() << endl;
      *out << "        o <= (OTHERS =>\'" << out_bit_string.toLatin1().constData() << endl;
    }
    else if(machine->getNumOutputs()>0)
            *out << "      WHEN OTHERS => o <= (OTHERS =>\'" << out_bit_string.toLatin1().constData() << endl;
     else *out << "      WHEN OTHERS => NULL;" << endl;

  }


      *out << "      next_state <= ";
      if (state_encoding_t)
        *out << "\"" << Convert::intToBinStr(machine->getInitialTransition()->getEnd()->getEncoding(),
                                             machine->getNumEncodingBits()).toLatin1().constData() << "\";" << endl;
      else *out << Utils::noWS(machine->getInitialTransition()->getEnd()->getStateName()).toLatin1().constData() << ";" << endl;

      *out << "    END CASE;" << endl;
      if (alliance)
        *out << "    END IF;" << endl;


    if (io_names_t)
    {
      if (machine->getNumMooreOutputs()>0 && ! sync_look_ahead)
      {
        int c=machine->getNumMooreOutputs();
        foreach(QString output, machine->getMooreOutputList())
        {
          output.replace('[','(');
          output.replace(']',')');

          *out << "    " << output.toLatin1().constData() << " <= temp_output(" << --c << ");\n";
        }
      }
      if (debug_state) 
      {
	int numStateBits = numbits (machine->getNumStates());

	*out << "    " << "debug_state <= temp_output (" << machine->getNumMooreOutputs() + numStateBits - 1
	     << " DOWNTO " << machine->getNumMooreOutputs() << ");" << endl;
      }
      if (machine->getNumOutputs()>0)
      {
        int c=machine->getNumOutputs();
        foreach(QString output, machine->getOutputNameList())
        {
          output.replace('[','(');
          output.replace(']',')');

          *out << "    " << output.toLatin1().constData() << " <= temp_mealy_output(" << --c << ");\n";
        }
      }
    }


    *out << "  END PROCESS;" << endl << endl;

}


/// Writes the machine description to the output stream
void ExportVHDL::writeDescription(std::ofstream*out)
{
  using namespace std;

  *out << endl;
  if (machine->getNumInputs()>0)
  {
    *out << "-- Inputs:";
    foreach(const QString& input, machine->getInputNameList())
      *out << "   " << input.toLatin1().constData();
    *out << endl;
  }
  if (machine->getNumOutputs()>0)
  {
    *out << "-- Mealy Outputs:";
    foreach(const QString& output, machine->getOutputNameList())
      *out << "   " << output.toLatin1().constData();
    *out << endl;
  }


  int *textLen=new int[machine->getNumMooreOutputs()+1];
  textLen[0]=12;

  foreach(GState* state, machine->getSList())
    if (!state->isDeleted() && state->getStateName().length()>textLen[0])
      textLen[0]=state->getStateName().length();
  textLen[0]++;

  *out << "-- State/Output" << QString(textLen[0]-13,' ').toLatin1().constData();


  if (machine->getNumMooreOutputs()>0)
  {
    int spc=1;
    QStringList outputs=machine->getMooreOutputList();
    QStringList::iterator i;
    for (i=outputs.begin(); i!=outputs.end(); ++i)
    {
      textLen[spc]=i->length()+1;
      spc++;
      *out << ' '<< i->latin1();
    }
  }
  *out << endl;

  IOInfo*mooreOutput;
  QString sMooreOutput;

  foreach(GState* state, machine->getSList())
  {
    if (state->isDeleted())
      continue;
    int spc=0;
    *out << "-- " << state->getStateName().toLatin1().constData() << QString(textLen[spc]-state->getStateName().length(),' ').toLatin1().constData();
    spc++;
    if (machine->getNumMooreOutputs()>0)
    {
      mooreOutput=state->getMooreOutputs();
      sMooreOutput=mooreOutput->convertToBinStr();
      int c=0;
      while (c<sMooreOutput.length())
      {
        *out << sMooreOutput[c].toLatin1() << QString(textLen[spc]-1,' ').toLatin1().constData();
        c++;
        spc++;
      }
    }
    *out << endl;
  }
  *out << endl;
  delete[] textLen;
}

/// Writes the input/current_state process to the output stream
void ExportVHDL::writeOutputProcess(std::ofstream*out)
{
  using namespace std;

  GState* s;
  QString sn;

  QString out_bit_string;



  bool io_names_t;

  if (machine->getType()==1) // Binary machine
    io_names_t=false;

  if (alliance && machine->getType()==0)
    io_names_t=false;
  else io_names_t=io_names;


  *out << "  lookahead_output_logic: PROCESS (next_state)\n" ;
  *out << "  BEGIN" << endl;
  *out << "    CASE next_state IS" << endl;

  QMutableListIterator<GState*> is(machine->getSList());

  for (; is.hasNext();)
  {
    s = is.next();
    sn = s->getStateName();
    sn.replace(' ', '_');

    if (state_encoding)
    {
      *out << "      WHEN \"" <<
          Convert::intToBinStr(s->getEncoding(),
                               machine->getNumEncodingBits()).toLatin1().constData()
          << "\" =>";
    }
    else
    {
      *out << "      WHEN " << Utils::noWS(s->getStateName()).toLatin1().constData() << " =>";
    }

    *out << " next_output <= \"" << s->getMooreOutputsStr(machine,options).latin1() << "\";" << endl;

  }


  if(use_std_logic)
        out_bit_string="X\');";
  else out_bit_string="0\');";



  if(machine->getNumMooreOutputs()>0)
          *out << "      WHEN OTHERS => next_output <= (OTHERS =>\'" << out_bit_string.toLatin1().constData() << endl;
   else *out << "      WHEN OTHERS => NULL;" << endl;



   *out << "    END CASE;" << endl;


    *out << "  END PROCESS;" << endl << endl;

}


/// Writes output buffer process for machine export with synchronous look-ahead buffer
void ExportVHDL::writeOutputBufferProcess(std::ofstream*out)
{
  using namespace std;
  GState* istate;

  QString init_outputs;

  //take values into account depending on alliance value
  bool synchronous_reset_t=alliance || synchronous_reset;


  if (alliance)
  {
    *out << "  output_buffer: PROCESS (clk)" << endl;
    *out << "  BEGIN" << endl;
  }
  else
  {
    istate = machine->getInitialState();
    if (synchronous_reset_t)
    {
      if (neg_reset)  *out << "  output_buffer: PROCESS (srst_n, rst_n, ";
      else            *out << "  output_buffer: PROCESS (srst_p, rst_p, ";
    }
    else
    {
      if (neg_reset)  *out << "  output_buffer: PROCESS (rst_n, ";
      else            *out << "  output_buffer: PROCESS (rst_p, ";
    }

    if(synchronous_enable)
      *out << "sen_p, clk)" << endl;
    else *out << "clk)" << endl;

    *out << "  BEGIN" << endl;

    if (neg_reset)  *out << "    IF rst_n='0' THEN" << endl;
    else            *out << "    IF rst_p='1' THEN" << endl;

    init_outputs=istate->getMooreOutputsStr(machine,options);

    if (machine->getNumMooreOutputs()>0)
    {
      int c=machine->getNumMooreOutputs();
      foreach(QString output, machine->getMooreOutputList())
      {
        output.replace('[','(');
        output.replace(']',')');

        *out << "    " << output.toLatin1().constData() << " <= '" << init_outputs[--c].toLatin1() << "';\n";
      }
    }


    if (use_std_logic)
      *out << "    ELSIF rising_edge(clk) THEN" << endl;
    else *out << "    ELSIF clk'event and clk='1' THEN" << endl;


  }

  if (synchronous_reset_t && !alliance)
  {


    if (neg_reset)  *out << "      IF srst_n='0' THEN " << endl;
    else            *out << "      IF srst_p='1' THEN " << endl;



      init_outputs=istate->getMooreOutputsStr(machine,options);

      if (machine->getNumMooreOutputs()>0)
      {
        int c=machine->getNumMooreOutputs();
        foreach(QString output, machine->getMooreOutputList())
        {
          output.replace('[','(');
          output.replace(']',')');

          *out << "    " << output.toLatin1().constData() << " <= '" << init_outputs[--c].toLatin1() << "';\n";
        }
      }


          if(synchronous_enable)
          {
            *out << "      ELSIF sen_p='1' THEN" << endl;
          }
          else {
            *out << "      ELSE" << endl;
          }
          if (machine->getNumMooreOutputs()>0)
          {
            int c=machine->getNumMooreOutputs();
            foreach(QString output, machine->getMooreOutputList())
            {
              output.replace('[','(');
              output.replace(']',')');

              *out << "    " << output.toLatin1().constData() << " <= next_output(" << --c << ");\n";
            }
          }
          *out << "      END IF;" << endl;
        }
        else
        {
          if (alliance)
            *out << "    IF ( clk = '1' AND NOT clk'STABLE ) THEN" << endl;
          if(synchronous_enable)
          {
            *out << "      IF sen_p='1' THEN" << endl;
            if (machine->getNumMooreOutputs()>0)
            {
              int c=machine->getNumMooreOutputs();
              foreach(QString output, machine->getMooreOutputList())
              {
                output.replace('[','(');
                output.replace(']',')');

                *out << "    " << output.toLatin1().constData() << " <= next_output(" << --c << ");\n";
              }
            }
            *out << "      END IF;" << endl;
          }
          else {
            if (machine->getNumMooreOutputs()>0)
            {
              int c=machine->getNumMooreOutputs();
              foreach(QString output, machine->getMooreOutputList())
              {
                output.replace('[','(');
                output.replace(']',')');

                *out << "    " << output.toLatin1().constData() << " <= next_output(" << --c << ");\n";
              }
            }
          }
        }

        *out << "    END IF;" << endl;
        *out << "  END PROCESS;" << endl << endl;

}



/// Writes a comment to the top of the output stream
void ExportVHDL::writeHeader(std::ofstream*out,QString commentstart, QString commentend)
{
  using namespace std;
#ifdef FHA
  QString description = machine->getDescription();
  description.replace('\n',"\n"+commentstart+"              ");
  *out << commentstart.toLatin1().constData() << "----------------------------------------------------------------" << commentend.toLatin1().constData() << "\n";
  *out << commentstart.toLatin1().constData() << " Module     : " << machine->getName().toLatin1().constData() << commentend.toLatin1().constData() << "\n";
  *out << commentstart.toLatin1().constData() << "----------------------------------------------------------------" << commentend.toLatin1().constData() << "\n";
  *out << commentstart.toLatin1().constData() << " Author     : " << machine->getAuthor().toLatin1().constData() << commentend.toLatin1().constData() << "\n";
  *out << commentstart.toLatin1().constData() << " Company    : University of Applied Sciences Augsburg" << commentend.toLatin1().constData() << "\n";
  *out << commentstart.toLatin1().constData() << "----------------------------------------------------------------" << commentend.toLatin1().constData() << "\n";
  *out << commentstart.toLatin1().constData() << " Description: "  << description.toLatin1().constData() << commentend.toLatin1().constData() << "\n";
  *out << commentstart.toLatin1().constData() << "----------------------------------------------------------------" << commentend.toLatin1().constData() << "\n";
  *out << commentstart.toLatin1().constData() << " Revisions : " << machine->getVersion().toLatin1().constData() << " - " << commentend.toLatin1().constData() << "\n";
  *out << commentstart.toLatin1().constData() << "----------------------------------------------------------------" << commentend.toLatin1().constData() << "\n";
#else
  // Write some comment
  QWidget* wm = qApp->mainWidget();
  AppInfo ai(wm);

  *out << commentstart.latin1() << " This file was generated by				" <<
    commentend.latin1() << endl;
  *out << commentstart.latin1() << " Qfsm Version " << ai.getVersionMajor() << "."
       << ai.getVersionMinor() << "					" << commentend.latin1() << endl;
  *out << commentstart.latin1() << " (C) " << ai.getAuthor().latin1() << "			"
       << commentend.latin1() << endl << endl;
#endif
}



