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

#include "ExportVerilog.h"
#include "Machine.h"
#include "TransitionInfo.h"
#include "IOInfo.h"
#include "IOInfoList.h"
#include "Convert.h"
#include "Utils.h"
#include "Options.h"

//using namespace std;


ExportVerilog::ExportVerilog(Options* opt)
  	     : Export(opt)
{
}

/// Writes all the relevant data into the tdf file.
void ExportVerilog::doExport()
{
  writeHeader("//", "");
  writeModule();
}


QString ExportVerilog::fileFilter()
{
  return "Verilog HDL (*.v)";
}

QString ExportVerilog::defaultExtension()
{
	return "v";
}


/// Writes the 'module' block to the output stream
void ExportVerilog::writeModule()
{
  using namespace std;

  QString mname = machine->getName();
  mname.replace(QRegExp("\\s"), "_");

  *out << "module " << mname.latin1() << " (clock, reset, in, ";
  if (machine->getNumOutputs()>0)
    *out << "out, ";
  *out << "state";
  if (machine->getNumMooreOutputs()>0)
    *out << ", moore";
  *out << ");" << endl;

  *out << "  input     clock, reset;" << endl;
  *out << "  input  [" << machine->getNumInputs()-1 << ":0]  in;" << endl;
  if (machine->getNumOutputs()>0)
    *out << "  output [" << machine->getNumOutputs()-1 << ":0]  out;" << endl;
  if (machine->getNumMooreOutputs()>0)
    *out << "  output [" << machine->getNumMooreOutputs()-1 << ":0]  moore;" << endl;
  *out << "  output [" << machine->getNumEncodingBits()-1 << ":0]  state;" << endl << endl;

  if (machine->getNumOutputs()>0)
    *out << "  reg[" << machine->getNumOutputs()-1 << ":0]      out;" << endl;
  if (machine->getNumMooreOutputs()>0)
    *out << "  reg[" << machine->getNumMooreOutputs()-1 << ":0]      moore;" << endl;
  *out << "  reg[" << machine->getNumEncodingBits()-1 << ":0]      state, nextstate;" << endl;
  *out << endl;
  *out << "  parameter ";

  QList<GState*> slist = machine->getSList();
  QString stmp;
  QMutableListIterator<GState*> it(slist);
  bool first=TRUE;
  for(; it.hasNext();)
  {
    GState* st = it.next();
    if (st->isDeleted())
      continue;
    if (!first)
      stmp += ", ";
    stmp += Utils::noWS(st->getStateName());
    stmp += " = " + QString::number(machine->getNumEncodingBits()) + "\'b" + Convert::intToBinStr(st->getEncoding(), machine->getNumEncodingBits());
    first=FALSE;
  }
  *out << stmp.latin1() << ";" << endl << endl;

  writeClockProcess();
  writeStateProcess();
  *out << "endmodule" << endl;
}




/// Writes the reset/clock process to the output stream
void ExportVerilog::writeClockProcess()
{
  using namespace std;

  GState* stmp = machine->getInitialState();
  GState* s;
  QString sn;
  IOInfo* mout;
  QString smout;

  if (options->getVerilogSyncReset())
  {
    *out << "  always @ (posedge clock) begin" << endl;
  }
  else
  {
    *out << "  always @ (posedge reset or posedge clock) begin" << endl;
  }

  *out << "    if (reset)" << endl;
  *out << "      begin" << endl;
  *out << "        state <= " << Utils::noWS(stmp->getStateName()).latin1() << ";" << endl;
  if (machine->getNumMooreOutputs()>0)
  {
    mout = stmp->getMooreOutputs();
    smout = mout->convertToBinStr();

    if (!smout.isEmpty())
    {
      *out << "        moore <= " << machine->getNumMooreOutputs() <<  "\'b";
      *out << smout.latin1() << ";" << endl;
    }
  }
  *out << "      end;" << endl;

  *out << "    else" << endl;

  *out << "      begin" << endl;
  *out << "        state <= nextstate;" << endl;

  if (machine->getNumMooreOutputs()>0)
  {
    *out << "        case (nextstate)" << endl;

    QMutableListIterator<GState*> is(machine->getSList());

    for(; is.hasNext();)
    {
      s = is.next();
      if (s->isDeleted())
	continue;
      sn = s->getStateName();
      sn.replace(QRegExp(" "), "_");
      //if (s->countTransitions()>0)
      {
	*out << "          " << Utils::noWS(s->getStateName()).latin1() << ":" << endl;
      }
      //*out << "          begin" << endl;
      if (machine->getNumMooreOutputs()>0)
      {
	mout = s->getMooreOutputs();
	smout = mout->convertToBinStr();

	if (!smout.isEmpty())
	{
	  *out << "            moore <= " << machine->getNumMooreOutputs() << "\'b";
	  *out << smout.latin1() << ";" << endl;
	}
      }

      //*out << "          end" << endl;
    }

    *out << "        endcase" << endl;
  }
    
  *out << "      end" << endl;
  *out << "  end" << endl << endl;
}






/// Writes the input/current_state process to the output stream
void ExportVerilog::writeStateProcess()
{
  using namespace std;

  GState* s;
  GTransition* t;
  QString tinfoi, tinfoo, sn;
  State* stmp;
  TransitionInfo* tinfo;
  IOInfo* iosingle;
  IOInfo* tioinfo;
  bool first, first_trans;

  if (options->getVerilogSyncReset())
  {
    GState* sinit;

    sinit = machine->getInitialState();

    *out << "  always @ (reset or in or state) begin" << endl;
    *out << "    if (reset)" << endl;
    *out << "      nextstate = " <<
      Utils::noWS(sinit->getStateName()).latin1() << ";" << endl;
    *out << "    else begin" << endl;
  }
  else
    *out << "  always @ (in or state) begin" << endl;

  if (machine->getNumOutputs()>0)
  {
    *out << "      out = " << machine->getNumOutputs() << "\'b";
    for(int i=0; i<machine->getNumOutputs(); i++)
      *out << "0";
    *out << ";" << endl;
  }

  *out << "      nextstate = state;" << endl;

  *out << "      case (state)" << endl;

  QMutableListIterator<GState*> is(machine->getSList());

  for(; is.hasNext();)
  {
    s = is.next();
    if (s->isDeleted())
      continue;
    sn = s->getStateName();
    sn.replace(QRegExp(" "), "_");
    //if (s->countTransitions()>0)
    {
      *out << "        " << Utils::noWS(s->getStateName()).latin1() << ":" << endl;
    }
    *out << "        begin" << endl;
    /*
    if (machine->getNumMooreOutputs()>0)
    {
      IOInfo* mout;
      QString smout;
      mout = s->getMooreOutputs();
      smout = mout->convertToBinStr();

      *out << "        moore = " << machine->getNumMooreOutputs() << "\'b";
      *out << smout << ";" << endl;
    }
    */

    QMutableListIterator<GTransition*> it(s->tlist);

    first_trans=TRUE;

    for(; it.hasNext();)
    {
      t = it.next();
      tinfo = t->getInfo();
      tioinfo = tinfo->getInputInfo();

      if (!t->isDeleted() && t->getEnd())
      {
	IOInfoList iolist;
	tioinfo->convertToBinList(iolist, FALSE);
//	iolist.setAutoDelete(TRUE);
	
	QMutableListIterator<IOInfo*> ioit(iolist);

	*out << "          ";
	if (!first_trans)
	  *out << "else ";
	*out << "if (in";
	if (tioinfo->isInverted())
	  *out << "!=";
	else
	  *out << "==";
	*out << machine->getNumInputs() << "\'b";
	first_trans=FALSE;

	first = TRUE;
	for(; ioit.hasNext();)
	{

	  iosingle = ioit.next();
	  tinfoi = iosingle->convertToBinStr();  

	  if (!tinfoi.isEmpty())
	  {
	    if (!first)
	    {
	      if (tioinfo->isInverted())
		*out << " && ";
	      else
		*out << " || " ;
	      *out << endl << "              in";
	      if (tioinfo->isInverted())
		*out << "!="; 
	      else
		*out << "==";
	      *out << machine->getNumInputs() << "\'b";
	    }

	    int slen = tinfoi.length();
	    int numin = machine->getNumInputs();
	    for(int k=slen; k<numin; k++)
	      *out << "0";

	    *out << tinfoi.latin1();
	    first=FALSE;
	  }
	}
	*out << ")" << endl;

	tinfoo = tinfo->getOutputsStrBin();
	*out << "          begin" << endl;
	if (!tinfoo.isEmpty())
	{
	  *out << "            out = " << machine->getNumOutputs() << "\'b";

	  int slen = tinfoo.length();
	  int numout = machine->getNumOutputs();
	  for(int l=slen; l<numout; l++)
	    *out << "0";

	  *out << tinfoo.latin1() << ";" << endl;
	}
	stmp = t->getEnd();
	if (stmp)
        {
	  sn = stmp->getStateName();
          sn.replace(QRegExp(" "), "_");
        }
	if (stmp!=s)
	{
	  *out << "            nextstate = " <<
	    Utils::noWS(stmp->getStateName()).latin1() << ";" << endl;
	}
	*out << "          end" << endl;
      }
    }
    *out << "        end" << endl;
  }

  *out << "      endcase" << endl;
  if (options->getVerilogSyncReset())
    *out << "    end" << endl;
  *out << "  end" << endl << endl;
}

