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

#include "TransitionInfoText.h"
#include "Convert.h"
#include "IOInfoText.h"
#include "Const.h"
#include "Machine.h"
#include "Options.h"


/// Constructor
TransitionInfoText::TransitionInfoText()
{
  type = Text;
  inputs = new IOInfoText(IO_MealyIn);
  outputs = new IOInfoText(IO_MealyOut);
}

/// Constructor
TransitionInfoText::TransitionInfoText(IOInfoText ain, IOInfoText aout)
{
  type = Text;

  inputs = new IOInfoText(ain);
  outputs = new IOInfoText(aout);
}

/// Constructor
TransitionInfoText::TransitionInfoText(QString sin, QString sout)
{
  type = Text;

  inputs = new IOInfoText(IO_MealyIn, sin);
  outputs = new IOInfoText(IO_MealyOut, sout);
}

/// Destructor
TransitionInfoText::~TransitionInfoText()
{
  if (inputs)
    delete inputs;
  if (outputs)
    delete outputs;
}

/// Copy constructor
TransitionInfoText::TransitionInfoText(const TransitionInfoText& t) 
		  : TransitionInfo()
{
//  IOInfoText ioascii;

  inputs = t.inputs->clone();
  outputs = t.outputs->clone();

  type = t.type;
}


/// Assignment operator
TransitionInfoText& TransitionInfoText::operator=(const TransitionInfoText& t)
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

    //IOInfoText ioascii;

    inputs = t.inputs->clone();
    outputs = t.outputs->clone();
    type = t.type;
  }
  return *this;
}


QString TransitionInfoText::getInputsStr(Machine* m/*=NULL*/, Options* opt/*=NULL*/)
{
  return inputs->convertToString(m, opt); //getInfo();
}

QString TransitionInfoText::getOutputsStr(Machine* m/*=NULL*/, Options* opt/*=NULL*/)
{
  return outputs->convertToString(m, opt); //getInfo();
}

QString TransitionInfoText::getOutputsStrBin(Machine* /*m=NULL*/, Options* /*opt=NULL*/)
{
  Convert conv;
  unsigned char ascii[MAX_CHARARRAY_LENGTH];
  int length;

  conv.resolveEscapes(outputs->convertToString(), ascii, MAX_CHARARRAY_LENGTH, length);
  return conv.asciiToBinStr(8, ascii, length); //getInfo());
}

QString TransitionInfoText::getOutputsStrHex()
{
  Convert conv;
  unsigned char ascii[MAX_CHARARRAY_LENGTH];
  int length;

  conv.resolveEscapes(outputs->convertToString(), ascii, MAX_CHARARRAY_LENGTH, length);
  return conv.asciiToHexStr(ascii, length);
}

QString TransitionInfoText::getInputsStrASCII()
{
  return getInputsStr();
}


QString TransitionInfoText::getOutputsStrASCII()
{
  return getOutputsStr();
}


void TransitionInfoText::setInputs(QString sin, int numbits)
{
  inputs->setString(sin, numbits);
}

void TransitionInfoText::setOutputs(QString sout, int numbits)
{
  outputs->setString(sout, numbits);
}


void TransitionInfoText::setInputsSize(int )
{
}

void TransitionInfoText::setOutputsSize(int )
{
}



bool TransitionInfoText::matches(IOInfo* io)
{
//  return inputs->matches(io);
  return inputs->equals(io);
}

