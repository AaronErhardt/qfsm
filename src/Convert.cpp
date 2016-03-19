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

#include <math.h>
#include <qstring.h>
#include <qregexp.h>
//Added by qt3to4:
#include <Q3ValueList>
#include "IOInfoList.h"
#include "Convert.h"
#include "IOInfoASCII.h"


/**
 * Standard constructor.
 */
Convert::Convert()
{
}


/**
 * Converts a string representing a binary number into an integer.
 * @param s string to convert
 * @return converted value
 */
int Convert::binStrToInt(QString s)
{
  QChar c;
  int count;
  int power=0;
  int result=0;

  count = s.length();


  if (s.isEmpty())
    return 0;

  count--;
  do
  {
    c = s[count--];

    if (c=='1')
      result += int(pow(2.0, power));
    power++;
  } while (count>=0);
  
  return result;
}


/**
 * Converts a string representing a hexadecimal number into an integer.
 *
 * @param hex String with the hexidecimal number
 * @param ires Resulting integer value
 * @returns TRUE if successful
 */
bool Convert::hexStrToInt(QString hex, int& ires)
{
  int len;
  QString hexdig = "0123456789ABCDEF";
  QString tmp=hex;
  int dezdig;
  int sum=0;
  int count=0;

  len = hex.length();
  
  for(int i=len-1; i>=0; i--)
  {
    dezdig = hexdig.find(tmp[i].upper());
    if (dezdig<0)
    {
      ires=0;
      return FALSE;
    }

    sum += dezdig * int(pow(16.0, count));

    count++;
  }
  ires = sum;
  return TRUE;
}


/**
 * Converts an integer into a string representing the binary value of that
 * integer.
 * @param c integer to convert
 * @param len length of resulting string
 * @return binary string
 */
QString Convert::intToBinStr(int c, int len)
{
  if (c > pow(2.0, len) -1 || len==0)
    return QString::null;

  QString result;
  int ctmp, cm;

  ctmp = c;
  for (int i=len-1; i>=0; i--)
  {
    cm = ctmp - (1<<(i)); //int(pow(2, i));
    if (cm>=0)
    {
      result += "1";
      ctmp = cm;
    }
    else
      result += "0";
  }
  return result;
}


/**
 * Converts a string representing a binary value into a binary array.
 * A binary array is an array of chars where each char represents one bit. The
 * bit with the @a lowest index is the MSB. 
 * Value of 0 means 0, 1 means 1 and 2 means 'don't care'
 * The end of the binary array is marked with a decimal '10'.
 * @param num number of bits to convert (lenth of buffer-1)
 * @param cs string to convert
 * @param buffer binary array
 */
IOInfoBin Convert::binStrToX10(int num, const QString cs, IOType t)
{
  /*
  char* buffer = new char[num+1];

  QString s;
  int len;
  int count=0;
  IOInfoBin result(t);

  s = cs.right(num);
  len = s.length();
  
  memset(buffer, 0, num);

  for (int i=num-1; i>=0; i--)
  {
    if (count<len)
    {
      switch (s[len-count-1].latin1())
      {
	case '0': buffer[i]=0; break;
	case '1': buffer[i]=1; break;
	case 'x': buffer[i]=2; break;
      }
    }
    else
      buffer[i]=0;
    count++;
  }
//  if (num>0)
    buffer[num]=10;

  result.setInfo(buffer);
  delete [] buffer;
  
  return result;
  */
  IOInfoBin result(t,cs);
  
  return result;
}

/**
 * Converts a binary array into an string.
 * @param io Object containing binary information
 * @return converted string
 */
QString Convert::X10ToBinStr(IOInfoBin io)
{
/*  QString s;
  int num;
  char* buffer;

  buffer = io.getInfo();
  num = io.getLength();

  if (!buffer)
    return "";

  for (int i=0; i<num; i++)
  {
    switch (buffer[i])
    {
      case 2:
        s = s + "x";
	break;
      case 1:
        s = s + "1";
	break;
      default:
        s = s + "0";
    }
  }

  return s;
  */
  return io.getInfo();
}

/**
 * Converts a binary string into decimal representation.
 *
 * @param io Object containing binary information
 * @param dec Resulting decimal representation
 * @returns TRUE if successful
 */
bool Convert::X10ToDec(IOInfoBin io, int& dec)
{
/*
  int len = io.getLength();
  int count=0;
  int sum=0;
  int btmp;
  char* info = io.getInfo();

  while (count<len)
  {
    btmp = info[count];
    if (btmp==1)
      sum += (int)pow(2.0, len-count-1);
    else if (btmp==2)
      return FALSE;
    count++;
  }

  dec = sum;

  return TRUE;
  */
  QString info =io.getInfo();
  dec=0;
  if(!io.isSingle())
    return FALSE;

  for(int c=info.length()-1; c>=0; c--)
    if(info[c]=='1')
      dec+=1<<c;
  return TRUE;
}

/**
 * Converts a binary string into ASCII representation.
 *
 * @param io Object containing binary information
 * @param ascii Resulting array of ascii characters
 * @param asciiarraylen Length of @a ascii
 * @param length Number of characters that have been converted
 * @param singlechar If TRUE only a single character is converted
 * @returns TRUE if successful
 */
bool Convert::X10ToASCII(IOInfoBin io, unsigned char* ascii, int asciiarraylen, int& length,
    bool singlechar/*=TRUE*/)
{
  /*
  int itmp;
  bool ok;
  IOInfoBin iotmp = io;
  iotmp.setInputsSize(8);

  ok =  X10ToDec(iotmp, itmp);
  cres = (char)itmp;
  return ok;
  */
  QString binstr;
  binstr = X10ToBinStr(io);
  if (!binStrToASCII(binstr, ascii, asciiarraylen, length, singlechar))
  {
    length=0;
    return FALSE;
  }
  return TRUE;
}


/*
 * Inverts a binary array.
 * @param len number of bits to invert
 * @param buffer buffer containing bits to be converted
 * @param inverted inverted bits
 */
/*
void Convert::invertX10(int len, char* buffer, char* inverted)
{
  for(int i=0; i<len; i++)
    inverted[i]=buffer[len-1-i];
  inverted[len]=10;
}
*/

/**
 * Converts a string representing a hexadecimal number into a binary array.
 * @param len number of bits to convert (length of binary array)
 * @param hex string containing hexadecimal number
 * @param bin buffer for resulting binary data
 */
IOInfoBin Convert::hexStrToX10(int len, const QString hex, IOType t)
{
  /*
  int dezdig;
  QString hexdig = "0123456789ABCDEF";
  int count=0;
  QString actdig;
  int slen = hex.length();
  int numconv=0;		// number of converted bits
  char* bintmp = new char[slen*4+1];
  int diff1=0, diff2=0;
  char* bin = new char[len+1];
  IOInfoBin result(t);

  memset(bintmp, 0, 4*slen);
  memset(bin, 0, len);

  count = (slen*4-len)/4; 	// ignore leading digits
  if (count<0)
    count=0;

  while (count<slen)
  {
    actdig = hex[count].upper();
    dezdig = hexdig.find(actdig);
    if (dezdig==-1)
      dezdig=0;
    
    for(int i=3; i>=0; i--)
    {
//      if (numconv+3-i<len)
      {
	if (dezdig-int(pow(2.0,i)+0.5)>=0)
        {
          bintmp[numconv+3-i]=1;
	  dezdig-=int(pow(2.0,i)+0.5);
        }
	else 
	  bintmp[numconv+3-i]=0;
      }
    }
    count++;
    numconv+=4;
  }

  if (len%4)
    diff2=4-len%4;
  if (4*slen<len)
    diff1=len-4*slen;

  if (numconv>len)
    numconv=len;
  memcpy(bin+diff1, bintmp+diff2, numconv);

  bin[len]=10;

//  invertX10(len, bininv, bin);


  result.setInfo(bin);

  delete [] bintmp;
  delete [] bin;

  return result;
  */
  QString binString("");
  for(int c=0; c<hex.length(); c++)
  {
    switch (hex[c].latin1())
    {
      case '0': binString += "0000"; break;
      case '1': binString += "0001"; break;
      case '2': binString += "0010"; break;
      case '3': binString += "0011"; break;
      case '4': binString += "0100"; break;
      case '5': binString += "0101"; break;
      case '6': binString += "0110"; break;
      case '7': binString += "0111"; break;
      case '8': binString += "1000"; break;
      case '9': binString += "1001"; break;
      case 'A': binString += "1010"; break;
      case 'B': binString += "1011"; break;
      case 'C': binString += "1100"; break;
      case 'D': binString += "1101"; break;
      case 'E': binString += "1110"; break;
      case 'F': binString += "1111"; break;
    }
  }
  binString.resize(len);
  IOInfoBin result(t,binString);
  return result;
}


/**
 * Converts a binary array into a string containing the corresponding
 * hexadecimal value.
 * @param len length of binary array
 * @param bininv binary data
 * @return string with hexadecimal data
 */
QString Convert::X10ToHexStr(/*int len, char* bininv*/IOInfoBin invio)
{
  if(!invio.isSingle())
    return QString("");
  int count=0;
  int dsum=0;
  QString hexdig = "0123456789ABCDEF";
  QString bin; //= new char[len+1];
  IOInfoBin io(invio.getType());
//  Convert conv;
  QString hex;
  int len;

//  conv.invertX10(len, bininv, bin);
  io = invio;
  io.invertBits();
  bin = io.getInfo();
  len = bin.length();

  while (count<len)
  {
    dsum=0;
    for(int i=0; i<4; i++)
    {
      if (count<len)
        dsum+=int(pow(2.0,i)+0.5)*(bin[count].toLatin1()-48);
      count++;
    }
    hex = hexdig[dsum] + hex;
  }

//  delete [] bin;

  return hex;
}


/**
 * Converts a binary string into a hexadecimal string.
 * @param bin string containing the binary value
 * @return string containing the hexadecimal value
 */
QString Convert::binStrToHexStr(const QString bin)
{
  int len;
  int count;
  QString hex;
  int dsum=0;
  QChar c;
  int dig;

  len = bin.length();
  count = len-1;

  while (count>=0)
  {
    dsum = 0;
    for (int i=3; i>=0; i--)
    {
      if (count-i>=0)
      {
	c = bin[count-i];
	dig = c.digitValue();
	if (dig<0)
	  dig=0;
        dsum += int(pow(2.0,i)+0.5)*dig;
      }
    }
    switch (dsum)
    {
      case 0: hex = "0" + hex; break;
      case 1: hex = "1" + hex; break;
      case 2: hex = "2" + hex; break;
      case 3: hex = "3" + hex; break;
      case 4: hex = "4" + hex; break;
      case 5: hex = "5" + hex; break;
      case 6: hex = "6" + hex; break;
      case 7: hex = "7" + hex; break;
      case 8: hex = "8" + hex; break;
      case 9: hex = "9" + hex; break;
      case 10: hex = "A" + hex; break;
      case 11: hex = "B" + hex; break;
      case 12: hex = "C" + hex; break;
      case 13: hex = "D" + hex; break;
      case 14: hex = "E" + hex; break;
      case 15: hex = "F" + hex; break;
    }
    count-=4;
  }
  return hex;
}


/**
 * Converts a string representing a binary number into ASCII representation
 * 
 * @param bin String with the binary number
 * @param ascii Array holding the resulting string of ASCII characters
 * @param arraymaxlen Length of the array @a ascii
 * @param length Number of converted characters
 * @param singlechar If TRUE only the first character is converted.
 * @returns TRUE if successful
 */
bool Convert::binStrToASCII(const QString bin, unsigned char* ascii, int arraymaxlen, int& length,
    bool singlechar/*=TRUE*/, int arrayoffset/*=0*/)
{
  if (arraymaxlen==0)
    return FALSE;

  int itmp;
  int binlen;
  length=0;
  int newlen, scanend;
  QString rbin, sdiff;
  QString bin8;
  int count;
  int firstxpos;
  int tmplength1=0, tmplength2=0;
  
  rbin=bin;
  rbin.replace(QRegExp("\\s"), "");
  if (singlechar)
  {
    if (rbin.find(QRegExp("[^01]"))!=-1)
      return FALSE;
  }
  else
  {
    if (rbin.find(QRegExp("[^01xX]"))!=-1)
      return FALSE;
  }

//  cx = rbin.contains("x", FALSE);
  firstxpos = rbin.find("x", 0, FALSE);
  if (firstxpos!=-1)
  {
    rbin.replace(firstxpos, 1, "0");
    binStrToASCII(rbin, ascii, arraymaxlen, tmplength1, singlechar, arrayoffset);
    rbin.replace(firstxpos, 1, "1");
//    rbin.replace(QRegExp("[xX]"), "0");
    binStrToASCII(rbin, ascii, arraymaxlen-tmplength1, tmplength2, singlechar,
	arrayoffset+tmplength1);
    length=tmplength1+tmplength2;
  }
  else
  {
    binlen = rbin.length();
    newlen = int((double)binlen/8 + 0.9) * 8;
    if (singlechar)
      newlen = 8;
    if (newlen>=binlen)
    {
      sdiff.fill('0', newlen-binlen);
      rbin.prepend(sdiff);
      newlen = rbin.length();
    }
    else
      rbin = rbin.right(newlen);

    length = newlen/8;
    count = length-1;
    scanend = newlen-1;

    while (scanend>0 && count>=0 && count<arraymaxlen)
    {
      bin8=rbin.mid(scanend-7, 8);
      if (bin8.isEmpty())
	bin8=rbin.mid(0, scanend+1);
      if (bin8.isEmpty())
	return FALSE;

      if (!bin8.isEmpty())
      {
	itmp = binStrToInt(bin8);

	unsigned char ctmp = (unsigned char)itmp;
	ascii[arrayoffset+count]=ctmp;
	count--;
      }
      scanend-=8;
    }
  }
  return TRUE;
}




/**
 * Converts a hexadecimal string into a binary string.
 * @param maxlen length the binary string will have
 * @param hex string containing a hexadecimal number
 * @return string containing the binary number
 */
QString Convert::hexStrToBinStr(int maxlen, const QString hex)
{
  int len;
  QString tmp=hex;
  QString hexdig = "0123456789ABCDEF";
  int dezdig;
  QString bin;

  len = hex.length();
  
  for(int i=len-1; i>=0; i--)
  {
    dezdig = hexdig.find(tmp[i].upper());
    if (dezdig<0)
      dezdig=0;
    switch (dezdig)
    {
      case 0: bin = "0000" + bin; break;
      case 1: bin = "0001" + bin; break;
      case 2: bin = "0010" + bin; break;
      case 3: bin = "0011" + bin; break;
      case 4: bin = "0100" + bin; break;
      case 5: bin = "0101" + bin; break;
      case 6: bin = "0110" + bin; break;
      case 7: bin = "0111" + bin; break;
      case 8: bin = "1000" + bin; break;
      case 9: bin = "1001" + bin; break;
      case 10: bin = "1010" + bin; break;
      case 11: bin = "1011" + bin; break;
      case 12: bin = "1100" + bin; break;
      case 13: bin = "1101" + bin; break;
      case 14: bin = "1110" + bin; break;
      case 15: bin = "1111" + bin; break;
    }
  }
  bin = bin.right(maxlen);

  return bin;
}


/**
 * Converts a string representing a hexadecimal number into ASCII representation
 * 
 * @param bin String with the hexadecimal number
 * @param ascii Array holding the resulting string of ASCII characters
 * @param maxarraylen Length of the array @a ascii
 * @param length Number of converted characters
 * @param singlechar If TRUE only the first character is converted.
 * @returns TRUE if successful
 */
bool Convert::hexStrToASCII(const QString hex, unsigned char* ascii, int maxarraylen, int& length,
    bool singlechar/*=TRUE*/)
{
  int itmp;
  QString rhex;
  int count=0, aindex;
  int hexlen;
  unsigned char ctmp;

  length=0;
  rhex = hex;
  rhex.replace(QRegExp("\\s"), "");
  if (rhex.find(QRegExp("[^\\da-fA-F]"))!=-1)
    return FALSE;
  hexlen = rhex.length();
  if (hexlen%2)
    rhex = "0"+rhex;
  if (singlechar)
    rhex=rhex.right(2);
  hexlen = rhex.length();
  aindex=0;

  while (count<hexlen && aindex<maxarraylen)
  {
    if (count+1<hexlen)
    {
      if (!hexStrToInt(rhex.mid(count, 2), itmp))
        return FALSE;
    }
    else
    {
      if (!hexStrToInt(rhex.mid(count, 1), itmp))
        return FALSE;
    }
    ctmp = (unsigned char)itmp;
    
    ascii[aindex++]=ctmp;

    count+=2;
  }
  length=aindex;
  return TRUE;
}


/**
 * Converts an ASCII string into a string representing the binary number
 *
 * @param maxlen Maximum length of the binary string
 * @param ascii Array holding the ASCII characters
 * @param asciilen Length of the string of ASCII characters 
 *    (can be smaller than the array size)
 * @returns The string representing the binary number
 */
QString Convert::asciiToBinStr(int maxlen, const unsigned char* ascii, int asciilen)
{
  QString hex, bin;
  int newlen;

  newlen = (maxlen+7)/8;
  if (newlen>asciilen)
    newlen=asciilen;
  hex = asciiToHexStr(ascii, newlen);
  //qDebug("hex: %s", hex.latin1());
  bin = hexStrToBinStr(maxlen, hex);
  //qDebug("bin: %s", bin.latin1());

  return bin;
}

/**
 * Converts a single ASCII character into a string representing the binary number
 *
 * @param maxlen Maximum length of the binary string
 * @param ascii The ASCII character to convert
 * @returns The string representing the binary number
 */
QString Convert::asciiToBinStr(int maxlen, const unsigned char ascii)
{
  return asciiToBinStr(maxlen, &ascii, 1);
}

/**
 * Converts an ASCII string into a string representing the hexadecimal number
 *
 * @param ascii Array holding the ASCII characters
 * @param asciilen Length of the string of ASCII characters 
 *    (can be smaller than the array size)
 * @returns The string representing the hexadecimal number
 */
QString Convert::asciiToHexStr(const unsigned char* ascii, int asciilen)
{
  QString hex="";
  int itmp, k;
//  char cnext;

  for(int i=0; i<asciilen; i++)
  {
    itmp = (int)(unsigned char)ascii[i];

    k = itmp/16;

    // first digit
    switch (k)
    {
      case 0: hex += "0" ; break;
      case 1: hex += "1" ; break;
      case 2: hex += "2" ; break;
      case 3: hex += "3" ; break;
      case 4: hex += "4" ; break;
      case 5: hex += "5" ; break;
      case 6: hex += "6" ; break;
      case 7: hex += "7" ; break;
      case 8: hex += "8" ; break;
      case 9: hex += "9" ; break;
      case 10: hex += "A" ; break;
      case 11: hex += "B" ; break;
      case 12: hex += "C" ; break;
      case 13: hex += "D" ; break;
      case 14: hex += "E" ; break;
      case 15: hex += "F" ; break;
    }

    itmp -= int(16*k);

    // second digit
    switch (itmp)
    {
      case 0: hex += "0" ; break;
      case 1: hex += "1" ; break;
      case 2: hex += "2" ; break;
      case 3: hex += "3" ; break;
      case 4: hex += "4" ; break;
      case 5: hex += "5" ; break;
      case 6: hex += "6" ; break;
      case 7: hex += "7" ; break;
      case 8: hex += "8" ; break;
      case 9: hex += "9" ; break;
      case 10: hex += "A" ; break;
      case 11: hex += "B" ; break;
      case 12: hex += "C" ; break;
      case 13: hex += "D" ; break;
      case 14: hex += "E" ; break;
      case 15: hex += "F" ; break;
    }

  }
  return hex;
}

/**
 * Converts a single ASCII character into hexadecimal representation
 * 
 * @param ascii ASCII character to convert.
 * @returns String representing the hexadecimal number
 */
QString Convert::asciiToHexStr(const unsigned char ascii)
{
  return asciiToHexStr(&ascii, 1);
}

/**
 * Converts a string of ASCII characters into binary representation
 * 
 * @param maxlen Maximum length of the binary string
 * @param ascii Array of ASCII characters
 * @param asciilen Number of ASCII characters stores in the array
 * @returns Object with the binary number
 */
IOInfoBin Convert::asciiToX10(int maxlen, const unsigned char* ascii, int asciilen, IOType t)
{
  QString binstr;

  binstr = asciiToBinStr(maxlen, ascii, asciilen);
  return binStrToX10(maxlen, binstr, t);
}


/**
 * Converts a single ASCII character into binary representation
 * 
 * @param maxlen Maximum length of the binary string
 * @param ascii ASCII character to convert
 * @returns Object with the binary number
 */
IOInfoBin Convert::asciiToX10(int maxlen, const unsigned char ascii, IOType t)
{
  return asciiToX10(maxlen, &ascii, 1, t);
}



/**
 * Resolves the escape symbols in a string of ASCII characters.
 *
 * Example: \d is resolved into 0123456789 (digit)
 *
 * @param estr String of characters possibly with escape symbols
 * @param cres Resulting array of ascii characters
 * @param arraymaxlen Length of the array
 * @param length Number characters stores in the array after resolution
 */
void Convert::resolveEscapes(QString estr, unsigned char* cres, int arraymaxlen, int& length)
{
  int i=0; 
  int len;
  unsigned char ctmp, cprev=0;
  bool nextisescape=FALSE;
  bool nextisdigit, previsdigit=FALSE;
  QString sinf;
  Convert conv;
  int fc;

  length=0;

  len = estr.length();

  while (i<len)
  {
    nextisdigit=FALSE;

    ctmp = estr[i].latin1();
    if (ctmp=='\\')		// escape sequence
    {
      if(i==len-1)
        break;

      unsigned char cnext;
      
      cnext = estr[i+1].latin1();
      if (cnext=='d')		// digit
      {
	for(fc='0'; fc<='9'; fc++)
	{
	  if (length>=arraymaxlen)
	    return;
	  cres[length++]=fc;
	}

	previsdigit=TRUE;
      }
      else 
      {
	if (cnext=='0')		// hex code (\0xx where xx is the hex code of the character)
	{
	  if (i>=len-3)
	  {
	    i=len;
	    break;
	  }  
	  int ires;
	  QString hexStr;
	  hexStr.sprintf("%c%c", estr[i+2].latin1(), estr[i+3].latin1());

	  i+=2;

	  if (!conv.hexStrToInt(hexStr, ires) || ires>255)
	    break;

	  ctmp = (unsigned char)ires;
	}
        else			// excape character
	{
          ctmp = IOInfoASCII::escapeToChar(estr[i+1].latin1());
	  //qDebug("escape: %c", ctmp);
	}

	if (length>=arraymaxlen)
	  return;

	cres[length++]=ctmp;
      }

      i++;
    }
    else if (ctmp=='-' && len>1)		// range
    {
      unsigned char cnext;

      // undo last added character because we are adding the whole range
      if (!previsdigit)
	length--;

      if (i==0 || i==len-1)
	break;

      cnext = estr[i+1].latin1();
      if (cnext=='\\')		// last char of range is escape character
      {
	nextisescape=TRUE;

	if (i==len-2)
	  break;

	cnext=estr[i+2].latin1();
      
	if (cnext=='d')		// digit
	{
	  nextisdigit=TRUE;
	}
	else 
	{
	  if (cnext=='0')	// hex code (\0xx where xx is the hex code of the character)
	  {
	    if (i>=len-4)
	    {
	      i=len;
	      break;
	    }  
	    int ires;
	    QString hexStr;
	    hexStr.sprintf("%c%c", estr[i+3].latin1(), estr[i+4].latin1());

	    i+=2;

	    if (!conv.hexStrToInt(hexStr, ires) || ires>255)
	      break;

	    cnext = (unsigned char)ires;
	  }
	  else			// excape character
	    cnext = IOInfoASCII::escapeToChar(estr[i+2].latin1());

	}
      }
      else
	nextisescape=FALSE;


      if (!nextisdigit)
      {
	if (previsdigit)
        {
	  if (cnext<'0')	// x-9
	  {
//	    if (c>=cnext && c<='9')
//	      return TRUE;
	    for(fc=cnext; fc<'0'; fc++)
	    {
	      if (length>=arraymaxlen)
		return;
	      cres[length++]=fc;
	    }
	  }
	  else if (cnext<='9')	// \d-5 (all digits)
	  {
	    // should already be added
//	    for(fc='0'; fc<'9'; fc++)
//	      cres[length++]=fc;
	  }
	  else			// 0-x
	    for(fc='9'+1; fc<=cnext; fc++)
	    {
	      if (length>=arraymaxlen)
		return;
	      cres[length++]=fc;
	    }
//	    if (c>=0 && c<=cnext)
//	      return TRUE;
        }
	else
	{
	  if (cprev<cnext)	// range normal
	  {
	    for(fc=cprev; fc<=cnext; fc++)
	    {
	      if (length>=arraymaxlen)
		return;
	      cres[length++]=fc;
	    }
//	    if (c>=cprev && c<=cnext)
//	      return TRUE;
	  }
	  else			// range reversed
	  {
	    for(fc=cnext; fc<=cprev; fc++)
	    {
	      if (length>=arraymaxlen)
		return;
	      cres[length++]=fc;
	    }
//	    if (c>=cnext && c<=cprev)
//	      return TRUE;
	  }
	}
      }
      else			// end of range is a digit
      {
	if (previsdigit)	// 0-9 (\d-\d should be rare)
	{
	  // should already been added
//	  if (c>='0' && c<='9')
//	    return TRUE;
	}
	else
	{
	  // normal or reversed?
	  if (cprev<'0')	// x-9
	  {
//	    if (c>=cprev && c<='9')
//	      return TRUE;
	    for(fc=cprev; fc<'0'; fc++)
	    {
	      if (length>=arraymaxlen)
		return;
	      cres[length++]=fc;
	    }
	  }
	  else if (cprev<='9')	// 5-\d (all digits)
	  {
//	    if (c>='0' && c<='9')
//	      return TRUE;
	    for(fc='0'; fc<='9'; fc++)
	    {
	      if (fc!=cprev)	// add all numbers except the one already added
	      {
		if (length>=arraymaxlen)
		  return;
		cres[length++]=fc;
	      }
	    }
	  }
	  else			// 0-x
	    for(fc='0'; fc<=cprev; fc++)
	    {
	      if (length>=arraymaxlen)
		return;
	      cres[length++]=fc;
	    }

//	    if (c>=0 && c<=cprev)
//	      return TRUE;
	}
      }

      previsdigit = nextisdigit;

      i++;	// for the '-'
      if (nextisescape)
	i++;	// for the '\'
    }
    else			// trivial case (normal character)
    {
      if (length>=arraymaxlen)
	return;
      cres[length++]=ctmp;
    }

    i++;
    cprev=ctmp;
  }  
}


/**
 * Converts a string of ASCII characters into a readable string.
 *
 * This means, escape characters are introduces where necessary.
 *
 * @param asciiarray Array of ASCII characters
 * @param asciilength Number of characters in the array
 * @returns Resulting string
 */
QString Convert::asciiToReadableStr(const unsigned char* asciiarray, int asciilength)
{
  unsigned char c;
  QString stmp;
  QString hex;
  QString sres;

  for(int i=0; i<asciilength; i++)
  {
    c = asciiarray[i];

    stmp = IOInfoASCII::charToEscape(c);

    if (stmp.isEmpty())
    {
      /*
      if (c=='-')
	stmp="\\-";
      else if (c=='\\')
	stmp="\\\\";
	*/
      if (IOInfoASCII::isReadable(c))
	stmp.sprintf("%c", c);
      else
      {
	hex = asciiToHexStr(c);
	stmp.sprintf("\\0%s", hex.latin1());
      }
    }
    sres += stmp;
  }
  return sres;
}

/**
 * Converts a string of ASCII characters into a list of IOInfo objects
 *
 * Escape characters and ranges are introduced where necessary.
 *
 * @param asciiarray Array of ASCII characters
 * @param asciilength Number of characters in the array
 * @param result Resulting IOInfo list
 */
void Convert::asciiToIOList(const unsigned char* asciiarray, int asciilength, IOInfoList& result, bool invert/*=FALSE*/)
{
  unsigned char c, cnext, cfirst;
  QString stmp, stmp2;
  QString hex;
  QString sres;
  bool inrange=FALSE;
  unsigned char* asciiarray2;
  int asciilength2;

  result.clear();

  // remove duplicates and sort asciiarray
  //replaced QValueList through QList, because qSort does not work with Q3ValueList
  //  Q3ValueList<unsigned char> olist;
  //  Q3ValueList<unsigned char> vlist;
  QList<unsigned char> olist;
  QList<unsigned char> vlist;
  for(int v=0; v<asciilength; v++)
  {
    if (!olist.contains(asciiarray[v]))
      olist.append(asciiarray[v]);
  }
  if (invert)
  {
    for(int o=0; o<=255; o++)
    {
      if (!olist.contains((unsigned char)o))
	vlist.append((unsigned char)o);
    }
  }
  else
    vlist = olist;

  qSort(vlist.begin(), vlist.end());
  asciiarray2 = new unsigned char[vlist.count()];
  qCopy(vlist.begin(), vlist.end(), asciiarray2);
  asciilength2 = vlist.count();

  for(int i=0; i<asciilength2; i++)
  {
    c = asciiarray2[i];
    if (i<asciilength2-1)
    {
      cnext=asciiarray2[i+1];
      if (cnext==c+1) // we are in a range
      {
	if (inrange)
	{
	}
	else
	{
	  cfirst = c;
	  inrange=TRUE;
	}
      }
      else // not a range
      {
	if (inrange) // end of range
	{
          stmp = asciiToReadableStr(&cfirst, 1);
          stmp2 = asciiToReadableStr(&c, 1);
	  sres = stmp + "-" + stmp2;
	  IOInfoASCII* info = new IOInfoASCII(IO_MealyIn, sres);
	  info->setRange(int((unsigned char)cfirst), int((unsigned char)c));
	  if (!result.contains(info))
	    result.append(info);

	  inrange=FALSE;
	}
	else  // we are not and we won't be in a range
	{
          sres = asciiToReadableStr(&c, 1);
	  IOInfoASCII* info = new IOInfoASCII(IO_MealyIn, sres);
	  if (!result.contains(info))
	    result.append(info);
	}
      }
    }
    else // last character
    {
      if (inrange) // end of range
      {
	stmp = asciiToReadableStr(&cfirst, 1);
	stmp2 = asciiToReadableStr(&c, 1);
	sres = stmp + "-" + stmp2;
	IOInfoASCII* info = new IOInfoASCII(IO_MealyIn, sres);
	info->setRange(int((unsigned char)cfirst), int((unsigned char)c));
	if (!result.contains(info))
	  result.append(info);
      }
      else  // we are not in a range
      {
	sres = asciiToReadableStr(&c, 1);
	IOInfoASCII* info = new IOInfoASCII(IO_MealyIn, sres);
	if (!result.contains(info))
	  result.append(info);
      }
    }
  }
  delete [] asciiarray2;
}

