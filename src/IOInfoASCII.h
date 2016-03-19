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
replaced Qt 3 iterators through Qt 4 iterators
*/

#ifndef IOINFOASCII_H
#define IOINFOASCII_H

#include "IOInfo.h"

class IOInfoBin;

/**
 * @class IOInfoASCII
 * @brief Stores ASCII Input/Ouput information.
 *
 */
class IOInfoASCII : public IOInfo
{
  public:
    IOInfoASCII(IOType t);
    IOInfoASCII(IOType t, unsigned char );
    IOInfoASCII(IOType t, QString );
    ~IOInfoASCII();

    void setRangeInfo(IOInfo* range_start, IOInfo* range_end);

    QString convertToString(Machine* m=NULL, Options* opt=NULL) const;
    QString convertToComparableString(Machine* m=NULL, Options* opt=NULL) const;
    QString convertToBinStr(Machine* m=NULL, Options* opt=NULL) const;
    QString convertToHexStr() const;
    bool convertToASCII(unsigned char* ascii, int maxlen, int& length, bool singlechar=FALSE) const;
    IOInfoBin convertToBin(int numbits) const;
    int convertToInt() const;
    void convertToBinList(IOInfoList& list, bool resolve_invert=TRUE) const;

    int getLength() const; // { return info.length()*8; } ;
//    bool matches(IOInfo* );
    bool matchesOld(IOInfo* );
    bool isSingle() const;

    /// Returns the I/O info
    QString getInfo() { return info; };
    /// Sets the I/O info
    void setInfo(QString i) { info = i.stripWhiteSpace(); };
    void setBin(QString bin, int numbits);
    void setASCII(const unsigned char* ascii, int asciilen, int numbits); 
    void setString(QString string, int numbits);
    IOInfo* getMinus1();
    IOInfo* getPlus1();
    void setAnyInput(bool ai); 

    static QString charToEscape(char c);
    static char escapeToChar(char );
    static bool isReadable(unsigned char );
    static int findChar(const unsigned char* ascii, int len, unsigned char c);

    QList<IOInfo*> getSingles();
    QList<IOInfo*> getSinglesInversion();
    int getNumSingles();

    IOInfo* clone() const;
    void split(IOInfoList& , bool resolve_invert) const;
    void split(IOInfoList&, GState*s) const;
    //void splitOld(IOInfoList& );
    //bool expandList(IOInfoList& input, IOInfoList& list);
    //int split(const IOInfo* ioinfo, IOInfoList& list);
    QStringList getRagelConditions();
    void updateDefaultInfo(const IOInfoList& other);

  private:
    /// I/O information
    QString info;
};

#endif

