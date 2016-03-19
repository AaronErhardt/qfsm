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
QList <IOInfo> to QList <IOInfo*> because IOInfo is a virtual class
and instances of this class can't be created.

in method expandList:
removed AutoDelete for QList<IOInfo*> list
replaced eventlist.qsort through qSort(eventList)

in method matches:
modified the code which compares the transition input with
the simulator input
*/

#ifndef IOINFO_H
#define IOINFO_H

#include <qstring.h>
#include <q3ptrlist.h>
#include <qstringlist.h>
//#include "IOInfo.h"
//#include "IOInfoList.h"

class IOInfoBin;
class IOInfoASCII;
class IOInfoList;
class Machine;
class Options;
class GState;
//class QStringList;

enum IOType { IO_None, IO_MealyIn, IO_MealyOut, IO_MooreOut };

/**
 * @class IOInfo
 * @brief Base class for all input/output information.
 */
class IOInfo
{
  public:
    IOInfo(IOType t, bool inv=FALSE);
    virtual ~IOInfo();

    IOType getType() const { return type; };
    bool getRole() const { return role; };
    void setRole(bool r) { role = r; };
    bool isInverted() const { return invert; };
    void setInvert( bool inv ) { invert=inv; };

    virtual void setRangeInfo(IOInfo* range_start, IOInfo* range_end)=0;

    bool equals(IOInfo* );   // instead of ==-operator
    virtual bool matches(IOInfo* );
    /// Returns a string representing the input/output information
    virtual QString convertToString(Machine* m=NULL, Options* opt=NULL) const =0;
    /// Returns a comparable string representing the input/output information
    virtual QString convertToComparableString(Machine* m=NULL, Options* opt=NULL)const =0;
    /// Returns a string representing the binary input/output information
    virtual QString convertToBinStr(Machine* m=NULL, Options* opt=NULL) const =0;
    /// Returns a string representing the hexadecimal input/output information
    virtual QString convertToHexStr() const =0;
    /**
     * Converts the I/O information into a string of ASCII characters.
     * @param ascii Resulting array of ASCII characters
     * @param maxlen Length of the array
     * @param number of relevant ASCII characters in the array
     * @param singlechar If TRUE only a single char is converted
     * @returns TRUE if successful
     */
    virtual bool convertToASCII(unsigned char* ascii, int maxlen, int& length, 
	bool singlechar=FALSE) const =0;
    /// Converts this object into an IOInfoBin object
    virtual IOInfoBin convertToBin(int numbits) const =0;
    /// Converts the I/O info into an integer value
    virtual int convertToInt() const =0;
    /// Converts the I/O info into a list of IOInfoBin objects
    virtual void convertToBinList(IOInfoList& list, bool resolve_invert=TRUE) const =0;

    /// Produces a copy of this object and returns a pointer to it
    virtual IOInfo* clone()const=0;

    /// Sets this I/O info to the binary string @a bin
    virtual void setBin(QString bin, int numbits)=0;
    /**
     * Sets this I/O info to a string of ASCII characters.
     * @param ascii Array holding the ASCII characters
     * @param asciilen Number of characters in the array to use
     * @param numbits Number of bits of the resulting I/O info
     */
    virtual void setASCII(const unsigned char* ascii, int asciilen, int numbits)=0;
    /// Sets this I/O info to the string @a string
    virtual void setString(QString string, int numbits)=0;

    /// Returns the length of this I/O info (in bits)
    virtual int getLength() const=0;
    /// Returns TRUE if this I/O info is a single character
    virtual bool isSingle() const=0;
    /// Returns a list of IOInfo objects with single characters representing this I/O info (does not take into account inversion)
//    virtual QList<IOInfo> getSingles()=0;
    virtual QList<IOInfo*> getSingles()=0;
    /// Returns a list of IOInfo objects with single characters representing this I/O info (does take into account inversion)
//    virtual QList<IOInfo> getSinglesInversion()=0;
    virtual QList<IOInfo*> getSinglesInversion()=0;
    /// Sets the size of the I/O info (in bits)
    virtual int getNumSingles() { return 1; };
    virtual void setSize(int) {};
//    virtual void setOutputsSize(int) {};
    virtual IOInfo* getMinus1()=0;
    virtual IOInfo* getPlus1()=0;

    /// Splits the I/O info into its constituents
    virtual void split(IOInfoList& , bool resolve_invert) const =0;
    /// Split default transition with respect to the start state
    virtual void split(IOInfoList& , GState*s) const =0;
    // / Splits this IOInfo and @a ioinfo into non-overlapping IOInfo objects
    //virtual int split(const IOInfo* ioinfo, IOInfoList& list)=0;
    /// Merges this IOInfo with a list of IOInfos
    static void expandList(IOInfoList&, IOInfoList& , bool resolve_invert);
    virtual void updateDefaultInfo(const IOInfoList& /*other*/) {};
    
    virtual bool isRange(int& start, int& end) const { start=range_start; end=range_end; return range; };
    virtual void setRange(int start, int end) { range_start = start; range_end = end; range=TRUE; };
    virtual bool getAnyInput() const { return any; };
    virtual void setAnyInput(bool ai) { any = ai; if (ai) {def=FALSE; invert=FALSE;} };
    virtual bool isDefault() const { return def; };
    virtual void setDefault(bool de) { def = de; if (de) {any=FALSE; invert=FALSE;} };


    virtual QStringList getRagelConditions()=0;


    /// Returns 0 is a binary ioinfo, 1 for ASCII, 2 for free text and -1 if ambiguous
    static int guessType(QString iostring)
    {
      if (isBinaryType(iostring)==1)
	return 0;
      else if (isASCIIType(iostring)==1)
	return 1;
      else if (isFreeTextType(iostring)==1)
	return 2;
      else
	return -1;
    };

    static int isBinaryType(QString iostring)
    {
      QRegExp regexp("^(DEF|ANY)$|^((NOT)?[ ]*[01]+([|][01]+)*)$");
      if (iostring.contains(regexp))
	return 1;
      return 0;
    };
    static int isASCIIType(QString iostring)
    {
      if (iostring.contains("\\0"))
	return 1;
      for(char c='a'; c<'z'; c++)
	if (iostring.count(c)>1)
	  return 0;
      for(char c='A'; c<'Z'; c++)
	if (iostring.count(c)>1)
	  return 0;
      if (iostring.count(' ')>1)
	return 0;
      if (iostring.contains("\\"))
	return 1;

      return -1;
    };

    static int isFreeTextType(QString iostring) 
    { 
      if (iostring=="ANY" || iostring=="DEF" || iostring.contains("\\"))
	return 0;
      else 
      {
	for(char c='a'; c<'w'; c++)
	  if (iostring.count(c)>1)
	    return 1;
	// don't consider double 'x' because it could be binary (don't care bits)
	for(char c='y'; c<'z'; c++) 
	  if (iostring.count(c)>1)
	    return 1;
	for(char c='A'; c<'W'; c++)
	  if (iostring.count(c)>1)
	    return 1;
	for(char c='Y'; c<'Z'; c++)
	  if (iostring.count(c)>1)
	    return 1;
	if (iostring.count(' ')>1)
	  return 1;
      }

      return -1;
    };

  protected:
    IOType type;
    bool role;
    bool invert;
    bool range;
    int range_start;
    int range_end;
    bool any;
    bool def;
};


#endif

