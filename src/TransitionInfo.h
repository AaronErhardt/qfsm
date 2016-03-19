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
/*
Qt 4 Port by Rainer Strobel

replaced Qt 3 iterators by Qt 4 iterators
*/

#ifndef TRANSITIONINFO_H
#define TRANSITIONINFO_H

#include <qstring.h>

class IOInfo;
class Options;
class Machine;

enum TransitionType {Binary, Ascii, Text};


/**
 * @class TransitionInfo
 * @brief Base class for all kind of transition conditions.
 */
class TransitionInfo
{
  public:
    TransitionInfo();
    virtual ~TransitionInfo();

    /// Produces an exact copy of this transition info and returns a pointer to it
    virtual TransitionInfo* clone()=0;

    /// Returns the inputs
    IOInfo* getInputInfo() { return inputs; };
    /// Returns the outputs
    IOInfo* getOutputInfo() { return outputs; };
    /// Returns a string representing the inputs (including NOT, any, default etc.)
    virtual QString getCompleteInputsStr(Machine* m=NULL, Options* opt=NULL) { return getInputsStr(); };
    /// Returns a string representing the inputs
    virtual QString getInputsStr(Machine* m=NULL, Options* opt=NULL)=0;
    /// Returns a string representing the outputs
    virtual QString getOutputsStr(Machine* m=NULL, Options* opt=NULL)=0;
    /// Returns a binary string representing the inputs
    virtual QString getInputsStrBin(Machine* =NULL, Options* =NULL) { return ""; };
    /// Returns a binary string representing the outputs
    virtual QString getOutputsStrBin(Machine* =NULL, Options* =NULL) { return ""; };
    /// Returns a hexadecimal string representing the inputs
    virtual QString getInputsStrHex(/*int*/) { return ""; };
    /// Returns a hexadecimal string representing the outputs
    virtual QString getOutputsStrHex(/*int*/) { return ""; };
    /// Returns an ASCII string representing the inputs
    virtual QString getInputsStrASCII() { return ""; };
    /// Returns an ASCII string representing the outputs
    virtual QString getOutputsStrASCII() { return ""; };
    /// Returns the separator string used between inputs and outputs string
    virtual QString getSeparator(Options*) { return ""; };
    /// Sets the inputs
    virtual void setInputs(QString, int numin=-1)=0;
    /// Sets the outputs
    virtual void setOutputs(QString, int numout=-1)=0;
    /// Returns the type of the transition (Binary, ASCII).
    int getType() { return type; };
    /// Sets the type of the transition (Binary, ASCII).
    void setType(int t) { type = t; };
    /// Sets the input size (in bits)
    virtual void setInputsSize(int bits)=0;
    /// Sets the output size (in bits)
    virtual void setOutputsSize(int bits)=0;

    /// Returns TRUE if @a io matches this transition info, otherwise FALSE
    virtual bool matches(IOInfo* io)=0;
    bool intersection(TransitionInfo* );

  protected:
    /// Inputs
    IOInfo* inputs;
    /// Outputs
    IOInfo* outputs;
    /// Type of the transition. 0: Binary / 1: ASCII
    int type;
   
};


#endif
