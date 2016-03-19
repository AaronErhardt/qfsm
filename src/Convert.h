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

if(!QString) replaced by if(QString.isEmpty())
in method asciiToIOList:
qSort did not work with Q3ValueList.
changed it to the new QList
*/

#ifndef CONVERT_H
#define CONVERT_H

#include <qstring.h>
#include "IOInfoBin.h"

/**
 * @class Convert
 * @brief Class for various conversions.
 *
 * This class is responsible for all sorts of conversions between
 * int, QString, binary, hexadecimal, ASCII.
 */

class Convert
{
  public:
    Convert();

    static QString intToBinStr(int c, int len);

    QString X10ToBinStr(IOInfoBin );
    QString X10ToHexStr(IOInfoBin );
    bool X10ToASCII(IOInfoBin io, unsigned char* cres, int asciiarraylen, int& length, 
	bool singlechar=TRUE);
    bool X10ToDec(IOInfoBin io,int& ires);

    int binStrToInt(QString );
    IOInfoBin binStrToX10(int maxlen, const QString, IOType t);
    QString binStrToHexStr(const QString);
    bool binStrToASCII(const QString, unsigned char* ascii, int arraymaxlen, int& len,
	bool singlechar=TRUE, int arrayoffset=0);

    bool hexStrToInt(QString, int&);
    IOInfoBin hexStrToX10(int, const QString, IOType t);
    QString hexStrToBinStr(int maxlen, const QString);
    bool hexStrToASCII(const QString, unsigned char* ascii, int arraymaxlen, int& len,
	bool singlechar=TRUE);

    IOInfoBin asciiToX10(int maxlen, const unsigned char ascii, IOType t);
    IOInfoBin asciiToX10(int maxlen, const unsigned char* ascii, int asciilen, IOType t);
    QString asciiToBinStr(int maxlen, const unsigned char ascii);
    QString asciiToBinStr(int maxlen, const unsigned char* ascii, int asciilen);
    QString asciiToHexStr(const unsigned char ascii);
    QString asciiToHexStr(const unsigned char* ascii, int asciilen);

    void resolveEscapes(QString estr, unsigned char* cres, int arraymaxlen, int& length);
    QString asciiToReadableStr(const unsigned char* ascii, int asciilength);
    void asciiToIOList(const unsigned char* asciiarray, int asciilength, IOInfoList& result, bool invert=FALSE);

};


#endif
