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

#ifndef TRANSITIONINFOBIN_H
#define TRANSITIONINFOBIN_H

#include "TransitionInfo.h"
#include "IOInfoBin.h"


/**
 * @class TransitionInfoBin
 * @brief Stores information about a binary transition condition.
 */
class TransitionInfoBin : public TransitionInfo
{
  public:
    TransitionInfoBin();
    TransitionInfoBin(const TransitionInfoBin&);
    TransitionInfoBin(IOInfoBin bin, IOInfoBin bout);
    ~TransitionInfoBin();

    TransitionInfoBin& operator=(const TransitionInfoBin&);

    TransitionInfo* clone() { return new TransitionInfoBin(*this); };

    /// Returns array with input bits
    /*char**/ IOInfoBin getInputs() const { return *(IOInfoBin*)inputs; };
    /// Returns array with output bits
    /*char**/ IOInfoBin getOutputs() const { return *(IOInfoBin*)outputs; };
    void setInputs(QString, int numin=-1 );
    void setOutputs(QString, int numout=-1 );
    void setInputsSize(int bits);
    void setOutputsSize(int bits);

    QString getCompleteInputsStr(Machine* m=NULL, Options* opt=NULL);
    QString getInputsStr(Machine* m=NULL, Options* opt=NULL);
    QString getOutputsStr(Machine* m=NULL, Options* opt=NULL);
    QString getInputsStrBin(Machine* m=NULL, Options* opt=NULL);
    QString getOutputsStrBin(Machine* m=NULL, Options* opt=NULL);
    QString getInputsStrHex(/*int*/);
    QString getOutputsStrHex(/*int*/);
    QString getInputsStrASCII();
    QString getOutputsStrASCII();
    QString getSeparator(Options* opt);

    bool matches(IOInfo* );

  private:
};



#endif
