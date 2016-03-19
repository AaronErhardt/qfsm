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

#include <typeinfo>

#include "TransitionInfoASCII.h"
#include "Convert.h"
#include "IOInfoASCII.h"
#include "Const.h"
#include "Machine.h"
#include "Options.h"


/// Constructor
TransitionInfoASCII::TransitionInfoASCII()
{
  type = Ascii;
  inputs = new IOInfoASCII(IO_MealyIn);
  outputs = new IOInfoASCII(IO_MealyOut);
}

/// Constructor
TransitionInfoASCII::TransitionInfoASCII(IOInfoASCII ain, IOInfoASCII aout)
{
  type = Ascii;

  inputs = new IOInfoASCII(ain);
  outputs = new IOInfoASCII(aout);
}

/// Constructor
TransitionInfoASCII::TransitionInfoASCII(QString sin, QString sout)
{
  type = Ascii;

  inputs = new IOInfoASCII(IO_MealyIn, sin);
  outputs = new IOInfoASCII(IO_MealyOut, sout);
}

/// Destructor
TransitionInfoASCII::~TransitionInfoASCII()
{
  if (inputs)
    delete inputs;
  if (outputs)
    delete outputs;
}

/// Copy constructor
TransitionInfoASCII::TransitionInfoASCII(const TransitionInfoASCII& t) 
		  : TransitionInfo()
{
//  IOInfoASCII ioascii;

  inputs = t.inputs->clone();
  outputs = t.outputs->clone();

  type = t.type;
}


/// Assignment operator
TransitionInfoASCII& TransitionInfoASCII::operator=(const TransitionInfoASCII& t)
{
  if (this!=&t)
  {
    if (inputs)
    {
      delete inputs;
      inputs = NULL;
    }
    if (outputs)
    {
      delete outputs;
      outputs = NULL;
    }

    //IOInfoASCII ioascii;

    inputs = t.inputs->clone();
    outputs = t.outputs->clone();
    type = t.type;
  }
  return *this;
}

QString TransitionInfoASCII::getCompleteInputsStr(Machine* m/*=NULL*/, Options* opt/*=NULL*/)
{
  QString res;
  res = getInputsStr(m, opt);
  if (opt)
  {
    if (getInputInfo()->isInverted())
      res = opt->getInversionDescriptor() + " " + res;
    else if (getInputInfo()->getAnyInput())
      res = opt->getAnyInputDescriptor();
    else if (getInputInfo()->isDefault())
      res = opt->getDefaultTransitionDescriptor();
  }
  return res;
}

QString TransitionInfoASCII::getInputsStr(Machine* m/*=NULL*/, Options* opt/*=NULL*/)
{
  return inputs->convertToString(m, opt); //getInfo();
}

/**
 * Returns string containing the input condition in bin format.
 * @return String representing the input information in binary format.
 */
QString TransitionInfoASCII::getInputsStrBin(Machine* m/*=NULL*/, Options* opt/*=NULL*/)
{
  return inputs->convertToBinStr(m, opt);
}


QString TransitionInfoASCII::getOutputsStr(Machine* m/*=NULL*/, Options* opt/*=NULL*/)
{
  return outputs->convertToString(m, opt); //getInfo();
}

QString TransitionInfoASCII::getOutputsStrBin(Machine* /*m=NULL*/, Options* /*opt=NULL*/)
{
  Convert conv;
  unsigned char ascii[MAX_CHARARRAY_LENGTH];
  int length;

  conv.resolveEscapes(outputs->convertToString(), ascii, MAX_CHARARRAY_LENGTH, length);
  return conv.asciiToBinStr(8, ascii, length); //getInfo());
}

QString TransitionInfoASCII::getOutputsStrHex()
{
  Convert conv;
  unsigned char ascii[MAX_CHARARRAY_LENGTH];
  int length;

  conv.resolveEscapes(outputs->convertToString(), ascii, MAX_CHARARRAY_LENGTH, length);
  return conv.asciiToHexStr(ascii, length);
}

QString TransitionInfoASCII::getInputsStrASCII()
{
  return getInputsStr();
}


QString TransitionInfoASCII::getOutputsStrASCII()
{
  return getOutputsStr();
}


void TransitionInfoASCII::setInputs(QString sin, int numbits)
{
  inputs->setString(sin, numbits);
}

void TransitionInfoASCII::setOutputs(QString sout, int numbits)
{
  outputs->setString(sout, numbits);
}


void TransitionInfoASCII::setInputsSize(int )
{
}

void TransitionInfoASCII::setOutputsSize(int )
{
}



bool TransitionInfoASCII::matches(IOInfo* io)
{
  return inputs->matches(io);
//  return inputs->equals(io);
}

