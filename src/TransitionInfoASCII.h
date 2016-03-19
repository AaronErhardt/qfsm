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

in method matches:
replaced matches() by equals() for comparism of
two IOInfo objects to keep simulator working
  */

#ifndef TRANSITIONINFOASCII_H
#define TRANSITIONINFOASCII_H

#include "TransitionInfo.h"
#include "IOInfoASCII.h"


/**
 * @class TransitionInfoASCII
 * @brief Stores information about an ASCII transition condition.
 */
class TransitionInfoASCII : public TransitionInfo
{
  public:
    TransitionInfoASCII();
    TransitionInfoASCII(IOInfoASCII ain, IOInfoASCII aout);
    TransitionInfoASCII(QString sin, QString sout);
    TransitionInfoASCII(const TransitionInfoASCII& t) ;
    ~TransitionInfoASCII();

    TransitionInfoASCII& operator=(const TransitionInfoASCII& t);

    TransitionInfo* clone() { return new TransitionInfoASCII(*this); };

    QString getCompleteInputsStr(Machine* m=NULL, Options* opt=NULL);
    QString getInputsStr(Machine* m=NULL, Options* opt=NULL);
    QString getInputsStrBin(Machine* m=NULL, Options* opt=NULL);
    QString getOutputsStr(Machine* m=NULL, Options* opt=NULL);
    QString getOutputsStrBin(Machine* m=NULL, Options* opt=NULL);
    QString getOutputsStrHex();
    QString getInputsStrASCII();
    QString getOutputsStrASCII();
    QString getSeparator(Options* ) { return "/"; };
    void setInputs(QString, int numin=-1);
    void setOutputs(QString, int numout=-1);
    void setInputsSize(int bits);
    void setOutputsSize(int bits);

    bool matches(IOInfo* );

  private:
//    IOInfoASCII inputs;
//    IOInfoASCII outputs;

};


#endif
