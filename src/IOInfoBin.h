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

changed return value of getSingles and getSinglesInversion from
QList <IOInfo> to QList <IOInfo*> because it had to be chaned in 
the base class.
*/

#ifndef IOINFOBIN_H
#define IOINFOBIN_H

#include "IOInfo.h"

class IOInfoASCII;

/**
 * @class IOInfoBin
 * @brief Stores binary Input/Ouput information.
 *
 */
class IOInfoBin : public IOInfo
{
  public:
    IOInfoBin(IOType t, QString, bool inv=FALSE);
    IOInfoBin(IOType t, bool inv=FALSE);
    IOInfoBin(IOType t, int code, int len, bool inv=FALSE);
    ~IOInfoBin();
    IOInfoBin(const IOInfoBin& );
    IOInfoBin& operator=(const IOInfoBin& );
    bool isSingle() const;

    QList<IOInfo*> getSingles();
    QList<IOInfo*> getSinglesInversion();
    int getNumSingles();

    void setRangeInfo(IOInfo* range_start, IOInfo* range_end);
    /// Returns lenght of the information
    int getLength() const; //{ return length; };
    /// Returns a pointer to the binary array
    QString getInfo() { return info; };
    void setInfo(QString);
    void invertBits();
    void setBin(QString bin, int numbits);
    void setASCII(const unsigned char* ascii, int asciilen, int numbits);
    void setString(QString string, int numbits);
    void setSize(int );
    IOInfo* getMinus1();
    IOInfo* getPlus1();
    void setAnyInput(bool ai);
    

    QString convertToString(Machine* m=NULL, Options* opt=NULL) const;
    QString convertToComparableString(Machine* m=NULL, Options* opt=NULL) const;
    QString convertToBinStr(Machine* m=NULL, Options* opt=NULL) const;
    QString convertToHexStr() const;
    bool convertToASCII(unsigned char* ascii, int maxlen, int& length, bool singlechar=FALSE) const;
    IOInfoBin convertToBin(int numbits) const;
    int convertToInt() const;
    void convertToBinList(IOInfoList& list, bool resolve_invert=TRUE) const;
    QString setBinFormat(QString);

    IOInfo* clone() const;
    void split(IOInfoList& , bool resolve_invert) const;
    /// Split default transition with respect to the start state
    virtual void split(IOInfoList& , GState*s) const;
    //int split(const IOInfo* ioinfo, IOInfoList& list);
    //bool expandList(IOInfoList&, IOInfoList& );
    bool matches(IOInfo* );
    QStringList getRagelConditions();

  private:
   /**
    * The QString that contains the bits.
    *
    * Every character represents a bit.
    * 0: '0' / 1: '1' / 2: 'x' (don't care) / '|': seperator between io's (logical OR)
    */
    QString info;

    static void resolveX(IOInfoBin bin, IOInfoList& list);
};

#endif
