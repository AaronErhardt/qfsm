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

#include <stdlib.h>
#include <typeinfo>
#include "IOInfoBin.h"
#include "IOInfoASCII.h"
#include "Convert.h"
#include "Const.h"
#include "Options.h"
#include "Machine.h"
#include "TransitionInfoBin.h"

/// Standard constructor.
TransitionInfoBin::TransitionInfoBin()
{
  type = Binary;
//  inputs = NULL;
//  outputs = NULL;
  inputs = new IOInfoBin(IO_MealyIn);
  outputs = new IOInfoBin(IO_MealyOut);
}

/**
 * Constructor.
 * @param numin number of input bits
 * @param in array of input bits
 * @param numout number of output bits
 * @param out array of output bits
 */
TransitionInfoBin::TransitionInfoBin(IOInfoBin bin, IOInfoBin bout/*int numin, char* in, int numout, char* out*/)
{
  type = Binary;
//  inputs=new char[numin+1];
//  outputs=new char[numout+1];
  inputs = new IOInfoBin(bin);
  outputs = new IOInfoBin(bout);

/*  memcpy(inputs, in, numin);
  inputs[numin]=10;
  memcpy(outputs, out, numout);
  outputs[numout]=10;
  */
}


/// Destructor.
TransitionInfoBin::~TransitionInfoBin()
{
  /*
  if (inputs)
    delete [] inputs;
  if (outputs)
    delete [] outputs;
    */
  if (inputs)
    delete inputs;
  if (outputs)
    delete outputs;
}

/// Copy constructor
TransitionInfoBin::TransitionInfoBin(const TransitionInfoBin& t) 
		  : TransitionInfo()
{
  /*
    IOInfoBin iobin;

    if (typeid(*t.inputs).name()==typeid(iobin).name())
    {
      IOInfoBin *bin, *bout;
      bin = t.inputs->getIOInfoBin();
      bout = t.outputs->getIOInfoBin();
      inputs = new IOInfoBin(*bin);
      outputs = new IOInfoBin(*bout);
//      inputs = new IOInfoBin(*(IOInfoBin*)t.inputs);
//      outputs = new IOInfoBin(*(IOInfoBin*)t.outputs);
      delete bin;
      delete bout;
    }
    else
    {
      IOInfoASCII *ain, *aout;
      ain = t.inputs->getIOInfoASCII();
      aout = t.outputs->getIOInfoASCII();
      inputs = new IOInfoASCII(*ain);
      outputs = new IOInfoASCII(*aout);
//      inputs = new IOInfoASCII(*(IOInfoASCII*)t.inputs);
//      outputs = new IOInfoASCII(*(IOInfoASCII*)t.outputs);
      delete ain;
      delete aout;
    }
    */
  inputs = t.inputs->clone();
  outputs = t.outputs->clone();

  type = t.type;
}


/// Assignment operator
TransitionInfoBin& TransitionInfoBin::operator=(const TransitionInfoBin& t)
{
  if (this!=&t)
  {
    if (inputs)
    {
      delete inputs;
      inputs=NULL;
    }
    if (outputs)
    {
      delete outputs;
      outputs=NULL;
    }

    /*
    IOInfoBin iobin;

    if (typeid(*t.inputs).name()==typeid(iobin).name())
    {
      IOInfoBin *bin, *bout;
      bin = t.inputs->getIOInfoBin();
      bout = t.outputs->getIOInfoBin();
      inputs = new IOInfoBin(*bin);
      outputs = new IOInfoBin(*bout);
//      inputs = new IOInfoBin(*(IOInfoBin*)t.inputs);
//      outputs = new IOInfoBin(*(IOInfoBin*)t.outputs);
      delete bin;
      delete bout;
    }
    else
    {
      IOInfoASCII *ain, *aout;
      ain = t.inputs->getIOInfoASCII();
      aout = t.outputs->getIOInfoASCII();
      inputs = new IOInfoASCII(*ain);
      outputs = new IOInfoASCII(*aout);
//      inputs = new IOInfoASCII(*(IOInfoASCII*)t.inputs);
//      outputs = new IOInfoASCII(*(IOInfoASCII*)t.outputs);
      delete ain;
      delete aout;
    }
    */
    inputs = t.inputs->clone();
    outputs = t.outputs->clone();

    type = t.type;
  }
  return *this;
}


/*
/// Copy constructor.
TransitionInfoBin::TransitionInfoBin(const TransitionInfoBin& t) 
		  : TransitionInfo()
{
  type = Binary;
  int count=0;

  while (t.inputs[count]!=10)
    count++;

  inputs = new char[count+1];

  for(int i=0; i<count; i++)
    inputs[i] = t.inputs[i];
  inputs[count]=10;

  count=0;
  while (t.outputs[count]!=10)
    count++;

  outputs = new char[count+1];

  for(int j=0; j<count; j++)
    outputs[j] = t.outputs[j];
  outputs[count]=10;
}

/// Overloaded assignment operator
TransitionInfoBin& TransitionInfoBin::operator=(const TransitionInfoBin& t)
{
  if (this!=&t)
  {
    type = Binary;
    int count=0;

    while (t.inputs[count]!=10)
      count++;

    inputs = new char[count+1];

    for(int i=0; i<count; i++)
      inputs[i] = t.inputs[i];
    inputs[count]=10;

    count=0;
    while (t.outputs[count]!=10)
      count++;

    outputs = new char[count+1];

    for(int j=0; j<count; j++)
      outputs[j] = t.outputs[j];
    outputs[count]=10;
  }
  return *this;
}
*/


QString TransitionInfoBin::getCompleteInputsStr(Machine* m/*=NULL*/, Options* opt/*=NULL*/)
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


QString TransitionInfoBin::getInputsStr(Machine* m/*=NULL*/, Options* opt/*=NULL*/)
{
  return getInputsStrBin(m, opt);
  /*
  QString sin = getInputsStrBin();

  if (opt!=NULL && opt->getDisplayIONames())
  {
    if (m==NULL)
      return sin;

    bool first;
    int count, in_len;
    QString sin2;
    QStringList::iterator it;
    QStringList in_names=m->getInputNameList();
    in_len = in_names.count();

    count=0;
    first=TRUE;
    for(it = in_names.begin(); it!=in_names.end(); ++it)
    {
      if (count<in_len)
      {
	if (sin[count]=='x')
	  count++;
	else
	{
	  if (!first)
	    sin2 += ", ";
	  sin2 += *it + "=" + sin[count++];
	  first=FALSE;
	}
      }
    }
    sin = sin2;
  }
  if (opt && opt->getIOMark() && !opt->getDisplayIONames())
  {
    if (sin.length()>0)
      sin = "?" + sin;
  }
  return sin;
  */
}

QString TransitionInfoBin::getOutputsStr(Machine* m/*=NULL*/, Options* opt/*=NULL*/)
{
  return getOutputsStrBin(m, opt);
  /*
  QString sout = getOutputsStrBin();

  if (opt!=NULL && opt->getDisplayIONames())
  {
    if (m==NULL)
      return sout;

    bool first;
    int count, out_len;
    QString sout2;
    QStringList::iterator it;
    QStringList out_names=m->getOutputNameList();
    out_len = out_names.count();

    count=0;
    first=TRUE;
    for(it = out_names.begin(); it!=out_names.end(); ++it)
    {
      if (count<out_len)
      {
	if (!first)
	  sout2 += ", ";
	sout2 += *it + "=" + sout[count++];
	first=FALSE;
      }
    }
    sout = sout2;
  }
  if (opt && opt->getIOMark() && !opt->getDisplayIONames())
  {
    if (sout.length()>0)
      sout = "!" + sout;
  }
  return sout;
  */
}

QString TransitionInfoBin::getSeparator(Options* opt)
{  
  QString sep;
//  if (opt->getViewMealyIn() && opt->getViewMealyOut())
  {
    if (opt->getDisplayIONames())
      sep = "\n";
    else
    {
      if (opt->getIOMark())
	sep = ",";
      else
	sep = "/";
    }
  }
  /*
  else 
    sep = "";
    */

  return sep;
}

QString TransitionInfoBin::getInputsStrASCII()
{
  unsigned char ascii[MAX_CHARARRAY_LENGTH];
  int len;
  Convert conv;

  inputs->convertToASCII(ascii, MAX_CHARARRAY_LENGTH, len, FALSE);
  return conv.asciiToReadableStr(ascii, len);
}

QString TransitionInfoBin::getOutputsStrASCII()
{
  unsigned char ascii[MAX_CHARARRAY_LENGTH];
  int len;
  Convert conv;

  outputs->convertToASCII(ascii, MAX_CHARARRAY_LENGTH, len, FALSE);
  return conv.asciiToReadableStr(ascii, len);
}

/**
 * Returns string containing the input bits in bin format.
 * @param numin number of input bits
 * @return String representing the input information in binary format.
 */
QString TransitionInfoBin::getInputsStrBin(Machine* m/*=NULL*/, Options* opt/*=NULL*/)
{
//  Convert conv;
//  return conv.X10ToBinStr(*(IOInfoBin*)inputs);
  return inputs->convertToBinStr(m, opt);
}

/**
 * Returns string containing the output bits in bin format.
 * @param numout number of output bits
 * @return String representing the output information in binary format.
 */
QString TransitionInfoBin::getOutputsStrBin(Machine* m/*=NULL*/, Options* opt/*=NULL*/)
{
//  Convert conv;
//  return conv.X10ToBinStr(*(IOInfoBin*)outputs);
  return outputs->convertToBinStr(m, opt);
}

/**
 * Returns string containing the input bits in hex format.
 * @param numout number of intput bits
 * @return String representing the input information in hexadecimal format.
 */
QString TransitionInfoBin::getInputsStrHex(/*int numin*/)
{
//  Convert conv;
//  return conv.X10ToHexStr(*(IOInfoBin*)inputs);
  return inputs->convertToHexStr();
}

/**
 * Returns string containing the output bits in hex format.
 * @param numout number of output bits
 * @return String representing the output information in hexadecimal format.
 */
QString TransitionInfoBin::getOutputsStrHex(/*int numout*/)
{
//  Convert conv;
//  return conv.X10ToHexStr(*(IOInfoBin*)outputs);
  return outputs->convertToHexStr();
}


/** 
 * Sets the inputs to the binary value contained in @a s.
 * @param numin number of inputs
 * @param s string containing the binary information
 */
void TransitionInfoBin::setInputs(QString s, int numin/*=-1*/)
{
  if (numin==-1)
    numin = inputs->getLength();
  /*
  Convert conv;
  *inputs = conv.binStrToX10(numin, s);
  */
  inputs->setBin(s, numin);
}


/** 
 * Sets the outputs to the binary value contained in @a s.
 * @param numout number of inputs
 * @param s string containing the binary information
 */
void TransitionInfoBin::setOutputs(QString s, int numout/*=-1*/)
{
  if (numout==-1)
    numout = outputs->getLength();
  /*
  Convert conv;
  *outputs = conv.binStrToX10(numout, s);
  */
  outputs->setBin(s, numout);
}



/**
 * Sets the number of inputs to @a newin.
 * @param oldin old number of inputs
 * @param newin new number of inputs
 */
void TransitionInfoBin::setInputsSize(int newin)
{
  inputs->setSize(newin);
/*
  int oldin = inputs->getLength();
  char old[oldin+1];
  int oldcount;
  char *pin;

  pin = inputs->getInfo();
  for (int i=0; i<=oldin; i++)
  {
    old[i] = pin[i];
  }

//  delete [] inputs;

  pin = new char[newin+1];

  oldcount = oldin;
  for(int j=newin-1; j>=0; j--)
  {
    if (oldcount>0)
      pin[j] = old[oldcount-1];
    else
      pin[j]=0;

    oldcount--;
  }
  pin[newin]=10;

  inputs->setInfo(pin);

  delete [] pin;
  */
}


/**
 * Sets the number of outputs to @a newin.
 * @param oldin old number of outputs
 * @param newin new number of outputs
 */
void TransitionInfoBin::setOutputsSize(int newout)
{
  outputs->setSize(newout);

  /*
  int oldout = outputs->getLength();
  char old[oldout+1];
  int oldcount;
  char* pout;

  pout = outputs->getInfo();
  for (int i=0; i<=oldout; i++)
  {
    old[i] = pout[i];
  }

//  delete [] outputs;

  pout= new char[newout+1];

  oldcount = oldout;
  for(int j=newout-1; j>=0; j--)
  {
    if (oldcount>0)
      pout[j] = old[oldcount-1];
    else
      pout[j]=0;

    oldcount--;
  }
  pout[newout]=10;

  outputs->setInfo(pout);

  delete [] pout;
  */
}


/**
 * Checks if transition matches i/o-info @a io.
 * @param io I/O-info which shall be checked
 * @return TRUE if the information matches otherwise FALSE.
 */
bool TransitionInfoBin::matches(IOInfo* io)
{
//  IOInfoBin iobin = io->convertToBin();
//  bool result = TRUE;
//  char* ioinf;
//  ioinf = iobin.getInfo();

  /*
  for (int i=0; i<iobin.getLength(); i++)
  {
    if (ioinf[i]==inputs[i] || inputs[i]==2)
      result = TRUE;
    else
      return FALSE;
  }
  */
  return inputs->matches(io);
//  return inputs->equals(io);

//  return TRUE;
}



