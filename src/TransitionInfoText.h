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

#ifndef TRANSITIONINFOTEXT_H
#define TRANSITIONINFOTEXT_H

#include "TransitionInfo.h"
#include "IOInfoText.h"


/**
 * @class TransitionInfoText
 * @brief Stores information about an ASCII transition condition.
 */
class TransitionInfoText : public TransitionInfo
{
  public:
    TransitionInfoText();
    TransitionInfoText(IOInfoText ain, IOInfoText aout);
    TransitionInfoText(QString sin, QString sout);
    TransitionInfoText(const TransitionInfoText& t) ;
    ~TransitionInfoText();

    TransitionInfoText& operator=(const TransitionInfoText& t);

    TransitionInfo* clone() { return new TransitionInfoText(*this); };

    QString getInputsStr(Machine* m=NULL, Options* opt=NULL);
    QString getOutputsStr(Machine* m=NULL, Options* opt=NULL);
    QString getOutputsStrBin(Machine* m=NULL, Options* opt=NULL);
    QString getOutputsStrHex();
    QString getInputsStrASCII();
    QString getOutputsStrASCII();
    QString getSeparator(Options* ) { return " / "; };
    void setInputs(QString, int numin=-1);
    void setOutputs(QString, int numout=-1);
    void setInputsSize(int bits);
    void setOutputsSize(int bits);

    bool matches(IOInfo* );

  private:

};


#endif
