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

#include <qregexp.h>
//Added by qt3to4:
#include <Q3PtrList>
#include "IOInfoASCII.h"
#include "Convert.h"
#include "Const.h"
#include "IOInfoList.h"

/// Standard constructor
IOInfoASCII::IOInfoASCII(IOType t)
  	   : IOInfo(t)
{
}

/// Constructor
IOInfoASCII::IOInfoASCII(IOType t, unsigned char i)
  	   : IOInfo(t)
{
//  info = QString(QChar(i));
  Convert conv;
  info = conv.asciiToReadableStr(&i, 1);
}

/// Constructor
IOInfoASCII::IOInfoASCII(IOType t, QString i)
  	   : IOInfo(t)
{
  info = i;
}

int IOInfoASCII::getLength() const
{
  return 8;
  /*
  Convert conv;
  unsigned char ascii[MAX_CHARARRAY_LENGTH];
  int length;

  conv.resolveEscapes(info, ascii, MAX_CHARARRAY_LENGTH, length);
  return length*8;
  */
}


void IOInfoASCII::setRangeInfo(IOInfo* rstart, IOInfo* rend)
{
  unsigned char as[MAX_CHARARRAY_LENGTH];
  unsigned char ae[MAX_CHARARRAY_LENGTH];
  int lena, lene;
  Convert conv;
  QString ss, se;

  rstart->convertToASCII(as, MAX_CHARARRAY_LENGTH, lena, TRUE);
  rend->convertToASCII(ae, MAX_CHARARRAY_LENGTH, lene, TRUE);

  if (lena!=1 || lene!=1)
    return;

  ss = conv.asciiToReadableStr(as, lena);
  se = conv.asciiToReadableStr(ae, lene);
  if (ss==se)
  {
    info = ss;
    range=FALSE;
  }
  else
  {
    info = ss + "-" + se;
    range = TRUE;
    range_start=int((unsigned char)as[0]);
    range_end=int((unsigned char)ae[0]);
  }
  type = rstart->getType();
  role = FALSE;
}

/// Destructor
IOInfoASCII::~IOInfoASCII()
{
}

QString IOInfoASCII::convertToString(Machine* /*m=NULL*/, Options* /*opt=NULL*/) const
{
  return info;
}


QString IOInfoASCII::convertToComparableString(Machine* /*m=NULL*/, Options* /*opt=NULL*/) const
{
  /*
  IOInfoList list;
  list.setAutoDelete(TRUE);
  split(list);
  IOInfo* io;

  QPtrListIterator<IOInfo> it(list);

  for(;it.current(); ++it)
  {
    io = it.current();


  }
  */
  return convertToHexStr(); // + QString::number(!role);
}


QString IOInfoASCII::convertToBinStr(Machine* /*m=NULL*/, Options* /*opt=NULL*/) const
{
  unsigned char ascii[MAX_CHARARRAY_LENGTH];
  int alen;
  QString binstr, result;

  if (!convertToASCII(ascii, MAX_CHARARRAY_LENGTH, alen))
    return "";

  Convert conv;
  binstr = conv.asciiToBinStr(alen*8, ascii, MAX_CHARARRAY_LENGTH);

  if (alen<=1)
    return binstr;
  else
  {
    result.append(binstr.mid(0, 8));
    for(int i=1; i<alen; i++)
    {
      result.append('|');
      result.append(binstr.mid(i*8, 8));
    }
  }
  return result;
}

QString IOInfoASCII::convertToHexStr() const
{
  Convert conv;
  unsigned char ascii[MAX_CHARARRAY_LENGTH];
  int length;

  conv.resolveEscapes(info, ascii, MAX_CHARARRAY_LENGTH, length);
  return conv.asciiToHexStr(ascii, length);
}


IOInfoBin IOInfoASCII::convertToBin(int numbits) const
{
  Convert conv;
  unsigned char ascii[MAX_CHARARRAY_LENGTH];
  int length;
  IOInfoBin result(type);
  QString binstr;

  /*
  if (length<=1)
  {
    conv.resolveEscapes(info, ascii, MAX_CHARARRAY_LENGTH, length);
    result = conv.asciiToX10(numbits, ascii, length, type);
  }
  else
  */  // SD changed 2011-06-23
  {
    //binstr = conv.asciiToBinStr(MAX_CHARARRAY_LENGTH, ascii, length);
    binstr = convertToBinStr();
    result = IOInfoBin(type, binstr, invert);
    result.setSize(numbits);
  }
  return result;
}

int IOInfoASCII::convertToInt() const
{
  Convert conv;
  QString binstr;

  if (!isSingle())
    return -1;

  binstr = convertToBinStr();
  return conv.binStrToInt(binstr);
}
  
void IOInfoASCII::convertToBinList(IOInfoList& list, bool resolve_invert/*=TRUE*/) const
{
  unsigned char ascii[MAX_CHARARRAY_LENGTH];
  int calen;

  convertToASCII(ascii, MAX_CHARARRAY_LENGTH, calen);

  list.clear();

  if (!invert || !resolve_invert)
  {
    for(int i=0; i<calen; i++)
    {
      unsigned char a;
      IOInfoBin* bin = new IOInfoBin(type);
      a = ascii[i];
      bin->setASCII(&a, 1, 8);
      list.append(bin);
    }
  }
  else
  {
    for(int i=0; i<=255; i++)
    {
      unsigned char a = (unsigned char)i;
      if (findChar(ascii, calen, a)==-1)
      {
	IOInfoBin* bin = new IOInfoBin(type);
	bin->setASCII(&a, 1, 8);
	list.append(bin);
      }
    }
  }
}

void IOInfoASCII::setBin(QString bin, int )
{
  Convert conv;
  unsigned char ascii[MAX_CHARARRAY_LENGTH];
  int length;

  if (conv.binStrToASCII(bin, ascii, MAX_CHARARRAY_LENGTH, length, FALSE))
    info = conv.asciiToReadableStr(ascii, length);
}

void IOInfoASCII::setASCII(const unsigned char* ascii, int asciilen, int )
{
  Convert conv;
  info = conv.asciiToReadableStr(ascii, asciilen);
  //qDebug("%s", info.latin1());
  //qDebug("%d", asciilen);
}


void IOInfoASCII::setString(QString string, int )
{
  info = string;
}



bool IOInfoASCII::convertToASCII(unsigned char* ascii, int maxlen, int& length, bool
    singlechar/*=FALSE*/) const
{
  Convert conv;
  if (singlechar)
  {
    unsigned char asctmp[MAX_CHARARRAY_LENGTH];
    int alen;

    conv.resolveEscapes(info, asctmp, MAX_CHARARRAY_LENGTH, alen);
    if (maxlen>0)
      ascii[0]=asctmp[alen-1];
    length=1;
  }
  else
    conv.resolveEscapes(info, ascii, maxlen, length);

  return TRUE;
}


/// Converts an escape character into the ASCII character
char IOInfoASCII::escapeToChar(char c)
{
  switch(c)
  {
    case 't': return 0x09;
    case 'n': return 0x0a;
    case 'r': return 0x0d;
    case 's': return 0x20;
    default:  return c;
  }
}

/// Converts an ASCII character into an escape sequence
QString IOInfoASCII::charToEscape(char c)
{
  switch(c)
  {
    case 0x09: return "\\t";
    case 0x0a: return "\\n";
    case 0x0d: return "\\r";
    case 0x20: return "\\s";
    case '-':  return "\\-";
    case '\\': return "\\\\";
    default: return "";
  }
}


/*
/// Old 'matches' function
bool IOInfoASCII::matchesOld(IOInfo* io)
{
  if (!io->isSingle())
    return FALSE;

  unsigned char c;
  int i=0; //, fpos=0;
  int len;
//  char lc, rc;
  unsigned char ctmp, cprev=0;
  bool nextisescape=FALSE;
  bool nextisdigit, previsdigit=FALSE;
  QString sinf;
  Convert conv;
  int tmplen;
  unsigned char carray[30];

  len = info.length();
  if (!io->convertToASCII(carray, sizeof(carray), tmplen))
    return FALSE;

  for (int ti=0; ti<tmplen-1; ti++)
    if (carray[ti]!=0)		// not a single char
      return FALSE;

  if (tmplen==0)
    return FALSE;

  c = carray[tmplen-1];

  while (i<len)
  {
    nextisdigit=FALSE;

    ctmp = info[i].latin1();
    if (ctmp=='\\')		// escape sequence
    {
      if(i==len-1)
        break;

      unsigned char cnext;
      
      cnext = info[(i+1)].latin1();
      if (cnext=='d')		// digit
      {
	if (c>='0' && c<='9')
	  return TRUE;
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
	  hexStr.sprintf("%c%c", info[(i+2)].latin1(), info[(i+3)].latin1());

	  i+=2;

	  if (!conv.hexStrToInt(hexStr, ires) || ires>255)
	    break;

	  ctmp = (unsigned char)ires;
	}
        else			// excape character
          ctmp = escapeToChar(info[(i+1)].latin1());

        if (ctmp==c)
	  return TRUE;
      }

      i++;
    }
    else if (ctmp=='-')		// range
    {
      unsigned char cnext;

      if (i==0 || i==len-1)
	break;

      cnext = info[(i+1)].latin1();
      if (cnext=='\\')		// last char. of range is escape character
      {
	nextisescape=TRUE;

	if (i==len-2)
	  break;

	cnext=info[(i+2)].latin1();
      
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
	    hexStr.sprintf("%c%c", info[(i+3)].latin1(), info[(i+4)].latin1());

	    i+=2;

	    if (!conv.hexStrToInt(hexStr, ires) || ires>255)
	      break;

	    cnext = (unsigned char)ires;
	  }
	  else			// excape character
	    cnext = escapeToChar(info[(i+2)].latin1());

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
	    if (c>=cnext && c<='9')
	      return TRUE;
	  }
	  else if (cnext<='9')	// 0-9
	  {
	    if (c>='0' && c<='9')
	      return TRUE;
	  }
	  else			// 0-x
	    //if (c>=0 && c<=cnext)
	    if (c<=cnext)
	      return TRUE;
        }
	else
	{
	  if (cprev<cnext)	// range normal
	  {
	    if (c>=cprev && c<=cnext)
	      return TRUE;
	  }
	  else			// range reversed
	  {
	    if (c>=cnext && c<=cprev)
	      return TRUE;
	  }
	}
      }
      else			// end of range is a digit
      {
	if (previsdigit)	// 0-9
	{
	  if (c>='0' && c<='9')
	    return TRUE;
	}
	else
	{
	  // normal or reversed?
	  if (cprev<'0')	// x-9
	  {
	    if (c>=cprev && c<='9')
	      return TRUE;
	  }
	  else if (cprev<='9')	// 0-9	(\d-\d should be rare)
	  {
	    if (c>='0' && c<='9')
	      return TRUE;
	  }
	  else			// 0-x
	    //if (c>=0 && c<=cprev)
	    if (c<=cprev)
	      return TRUE;
	}
      }

      previsdigit = nextisdigit;

      i++;	// for the '-'
      if (nextisescape)
	i++;	// for the '\'
    }
    else			// trivial case (normal character)
      if (c==ctmp)
	return TRUE;

    i++;
    cprev=ctmp;
  }  
  return FALSE;
}
*/


//bool IOInfoASCII::matches(IOInfo* io)
//{
  /*
  Convert conv;
  int calen1, calen2;
  char carray1[MAX_CHARARRAY_LENGTH];
  char carray2[MAX_CHARARRAY_LENGTH];

  if (!convertToASCII(carray1, sizeof(carray1), calen1))
    return FALSE;
  if (!io->convertToASCII(carray2, sizeof(carray2), calen2))
    return FALSE;

  for(int i=0; i<calen2; i++)
  {
    if (findChar(carray1, calen1, carray2[i])==-1)
      return FALSE;
  }

  return TRUE;
  */
  /*
  IOInfoList list1;
  IOInfoList list2;
  list1.setAutoDelete(TRUE);
  list2.setAutoDelete(TRUE);

  convertToBinList(list1);
  io->convertToBinList(list2);

  QListIterator<IOInfo> it(list2);
  for(;it.current(); ++it)
  {
    if (!list1.contains(it.current()))
      return FALSE;
  }
  return TRUE;
  */
//}


/**
 * Finds a character in an ASCII string.
 * 
 * @param ascii Array of ASCII characters
 * @param len Length of the array
 * @param c Character to look for
 * @returns If found, the position of the character in the array, otherwise -1
 */
int IOInfoASCII::findChar(const unsigned char* ascii, int len, unsigned char c)
{
  for(int i=0; i<len; i++)
  {
    if (ascii[i]==c)
      return i;
  }
  return -1;
}


bool IOInfoASCII::isSingle() const
{
  Convert conv;
  unsigned char ascii[MAX_CHARARRAY_LENGTH];
  int length;

  conv.resolveEscapes(info, ascii, MAX_CHARARRAY_LENGTH, length);
  return (length==1);

  /*
  // this code section is not working 
  QString stmp;
  int ccount=0;
  int i=0, len;
  unsigned char ctmp;
  bool escprev=FALSE;

  if (info.isEmpty())
    return FALSE;

  stmp = info.stripWhiteSpace();
  len = stmp.length();

  while(i<len)
  {
    ctmp=info[i].latin1();
    if (ctmp=='\\' && escprev==FALSE)
    {
      escprev=TRUE;

      if (i<len-1)
      {
	if (info[(i+1)]=='0')
	{
          if (i>=len-3)
	    return FALSE;
	  i+=2;
	}
	else if (info[(i+1)]=='d')
          return FALSE;
      }
    }
//    else if (ctmp=='-')
//      return FALSE;
    else
    {
      ccount++;
      escprev=FALSE;
    }

    i++;
  }

  if (ccount==1)
    return TRUE;
  else
    return FALSE;
    */
}


QList<IOInfo*> IOInfoASCII::getSingles()
{
  Convert conv;
  unsigned char ascii[MAX_CHARARRAY_LENGTH];
  int length;
  QList<IOInfo*> list;

  conv.resolveEscapes(info, ascii, MAX_CHARARRAY_LENGTH, length);
  for(int i=0; i<length; i++)
    list.append(new IOInfoASCII(type, ascii[i]));

  return list;

  /*
  int i=0; //, fpos=0;
  int len;
//  char lc, rc;
  unsigned char ctmp=0, cprev=0, cnext;
  bool nextisescape=FALSE;
  bool previsdigit=FALSE, nextisdigit=FALSE;
  QString sinf;
  QList<IOInfo*> list;
  Convert conv;
  bool firstadded=FALSE;

  len = info.length();

  while (i<len)
  {

    ctmp = info[i].latin1();
    if (ctmp=='\\')		// escape sequence
    {
      if(i==len-1)
        break;
      
      bool append=TRUE;
//      ctmp = escapeToChar(info[i+1].latin1());
      QString sesc;
      //QString cnext;
      cnext = info[(i+1)].latin1();
      if (cnext=='0')
      {
	if (i>=len-3)
	{
	  append=FALSE;
	  i=len;
	}
	else
	{
	  sesc.sprintf("\\0%c%c", info[(i+2)].latin1(), info[(i+3)].latin1());
          i+=2;

	  int asciilen;
	  conv.resolveEscapes(sesc, &ctmp, 1, asciilen);
	}
	previsdigit=FALSE;
      }
      else if (cnext=='d')
      {
	previsdigit=TRUE;
	if (i>=len-2 || (info[(i+2)].latin1()!='-'))	// append just 10 digits
	{
	  for(unsigned char r='0'; r<='9'; r++)
	  {
	    list.append(new IOInfoASCII(type, r));
	  }
	}
	append=FALSE;
      }
      else
      {
	previsdigit=FALSE;
        //sesc = "\\" + cnext;
        sesc.sprintf("\\%c",cnext);
      }
      
      if (append)
      {
        list.append(new IOInfoASCII(type, sesc));
	firstadded=TRUE;
      }
      else
	firstadded=FALSE;

      i++;
    }
    else if (ctmp=='-')
    {
      unsigned char cnext;
      bool includefirst=FALSE;

      if (len==1)
      {
	list.append(new IOInfoASCII(type, '-'));
	return list;
      }
      if (i==0 || i==len-1)
	break;

      cnext = info[(i+1)].latin1();
      if (cnext=='\\')
      {
	nextisescape=TRUE;

	if (i==len-2)
	  break;


	if (info[(i+2)].latin1()=='d')
	{
	  nextisdigit=TRUE;
	  if (previsdigit)
	  {
	    cprev='0';
	    cnext='9';
	    includefirst=TRUE;
	  }
	  else if (cprev<'0')
	  {
	    cnext='9';
	  }
	  else if (cprev>'9')
	  {
	    cnext='0';
	    //includefirst=TRUE;
	  }
	  else
	  {
	    cprev='0';
	    cnext='9';
	    includefirst=TRUE;
	  }
	}
	else if (info[(i+2)].latin1()=='0')
	{
	  if (i>=len-4)
	  {
//	    append=FALSE;
	    cnext=cprev;
	    i=len;
	  }
	  else
	  {
	    QString sesc;
	    sesc.sprintf("\\0%c%c", info[(i+3)].latin1(), info[(i+4)].latin1());
	    i+=2;

	    int asciilen;
	    conv.resolveEscapes(sesc, &cnext, 1, asciilen);
	  }
	}
	else
	  cnext = escapeToChar(info[(i+2)].latin1());
      }
      else
      {
	nextisescape=FALSE;
      }

      if (previsdigit)
      {
	if (cnext<'0')
	  cprev='9';
	else if (cnext>'9')
	{
	  cprev='0';
	}
	else
	{
	  cprev='0';
	  cnext='9';
	  includefirst=TRUE;
	}
      }

      if (cprev>cnext)
      {
	unsigned char chartmp;
	chartmp=cnext;
	cnext=cprev;
	cprev=chartmp;
	if (firstadded)
	  includefirst=TRUE;
      }
      if (!firstadded || includefirst)
	cprev--;
      for(int r=cprev+1; r<=cnext; r++)
      {
	list.append(new IOInfoASCII(type, (unsigned char)r));

      }
      firstadded=TRUE;

      i++;
      if (nextisescape)
	i++;
    }
    else
    {
      list.append(new IOInfoASCII(type, ctmp));

      if (ctmp>='0' && ctmp<='9')
	previsdigit=TRUE;
      else if (ctmp!='\\')
	previsdigit=FALSE;
      firstadded=TRUE;
    }

    i++;
    cprev=ctmp;
  }  
  */

  return list;
}


QList<IOInfo*> IOInfoASCII::getSinglesInversion()
{
  QList<IOInfo*> list;
//  list.setAutoDelete(FALSE);
  if (!invert)
    return getSingles();

  for(int c=0; c<=255; c++)
  {
    IOInfoASCII* newio = new IOInfoASCII(type, (unsigned char)c);
    if (matches(newio))
    {
      //qDebug("%s", newio->convertToString().latin1());
      list.append(newio);
      //list.append(new IOInfoASCII(type, (char)c));
    }
    else
      delete newio;
  }

  return list;
}

int IOInfoASCII::getNumSingles()
{
  QList<IOInfo*> ltmp;
  ltmp = getSinglesInversion();
  return ltmp.count();
}


/// Returns TRUE if the character @a cp is readable
bool IOInfoASCII::isReadable(unsigned char cp)
{
  unsigned char c=(unsigned char) cp;

  if (c==0x0f || c==0x12 || c==0x13 || c==0x15 || c==0x16 || (c>=0x21 && c<=0x7e))// ||
//      (c>=0x80 && c<=0xa8))
    return TRUE;

  return FALSE;
}


/*
IOInfoBin* IOInfoASCII::getIOInfoBin() const
{
  IOInfoBin* tmp = new IOInfoBin();
  char ascii[MAX_CHARARRAY_LENGTH];
  int len;
  convertToASCII(ascii, MAX_CHARARRAY_LENGTH, len);
  tmp->setASCII(ascii, MAX_CHARARRAY_LENGTH, len);
  return tmp;
}

IOInfoASCII* IOInfoASCII::getIOInfoASCII() const
{
  IOInfoASCII* tmp = new IOInfoASCII();
  *tmp = *this;
  return tmp;
}
*/

IOInfo* IOInfoASCII::clone() const
{
  return new IOInfoASCII(*this);
}


/*
void IOInfoASCII::splitOld(IOInfoList& list)
{
  int count=0;
  int len=info.length();
  QString rangestart;
  QString letter;
  bool range=FALSE;
//  bool escape=FALSE;
  IOInfoASCII* ioa;

  list.clear();

  while (count<len)
  {
    if (info[count]=='\\')
    {
      if (count<len+1)
      {
	if (info[(count+1)]=='0')
	{
	  if (count<len+3)
	  {
            letter = info.mid(count, 4);
	    count+=3;
	  }
	  else
	    return;
	}
	else
	{
          letter = info.mid(count, 2);
	  count++;
	}
      }
      else
	return;
    }
    else
      letter = info[count];

    if (range)			// end of range
    {
      QString srange;

      srange = rangestart;
      srange += "-" + letter;
      ioa = new IOInfoASCII(type, srange);
      list.append(ioa);
      range=FALSE;
      count++;
      continue;
    }

    if (count<len+1)
    {
      if (info[(count+1)]=='-')	// start of range
      {
        rangestart=letter;
	count+=2;
	range=TRUE;
	continue;
      }
    }
    
    ioa = new IOInfoASCII(type, letter);
    list.append(ioa);
    range=FALSE;
    count++;
  }
}
*/


void IOInfoASCII::split(IOInfoList& list, bool resolve_invert) const
{
  if (!resolve_invert && invert)
  {
    // This case has not been tested and is currently not used. 
    // I'm not sure why we do not split here. 
    list.append(this->clone());
    return;
  }

  Convert conv;

  unsigned char asctmp[MAX_CHARARRAY_LENGTH];
  int length;
  convertToASCII(asctmp, MAX_CHARARRAY_LENGTH, length);

  conv.asciiToIOList(asctmp, length, list, invert && resolve_invert);
}


void IOInfoASCII::split(IOInfoList&list, GState*) const
{
  split(list,true);

}

/* *
 * Creates a list of IOInfo objects out of this IOInfo and @a ioinfo 
 * splitting the IOInfos if they overlap
 *
 * @param ioinfo IOInfoASCII object to merge with
 * @param list Resulting list
 * @returns 1 if this IOInfo completely contains @a ioinfo, 
 * 	    2 if @a ioinfo completely contains this IOInfo, 
 *          3 if the two overlap, 
 *          0 if no split occured
 */
/*
int IOInfoASCII::split(const IOInfo* ioinfo, IOInfoList& list)
{
  unsigned char ascii1[MAX_CHARARRAY_LENGTH];
  unsigned char ascii2[MAX_CHARARRAY_LENGTH];
  int length1, length2;
  unsigned char first1, last1, first2, last2;
  unsigned char res1[MAX_CHARARRAY_LENGTH];
  unsigned char res2[MAX_CHARARRAY_LENGTH];
  unsigned char res3[MAX_CHARARRAY_LENGTH];
  int res1len, res2len, res3len;
  int i;
  Convert conv;
  IOInfoList result;
  result.setAutoDelete(TRUE);

  convertToASCII(ascii1, MAX_CHARARRAY_LENGTH, length1);
  ioinfo->convertToASCII(ascii2, MAX_CHARARRAY_LENGTH, length2);
  first1 = ascii1[0];
  first2 = ascii2[0];
  last1 = ascii1[length1-1];
  last2 = ascii2[length2-1];
  int overlap_pos1, overlap_pos2;

  list.clear();

  if (first1==first2 && last1==last2)
  {
    list.append(this->clone());
//    qDebug("identical IOInfo (no split)");
    return 0;
  }
  else if (last1<first2 || last2<first1)
  {
    list.append(this->clone());
    list.append(ioinfo->clone());
    return 0;
  }
  else if (first1<first2 && last1>=first2 && last1<last2)
  {
    overlap_pos1 = length1-(last1-first2)-1;
    overlap_pos2 = (last1-first2);
    res1len=res2len=res3len=0;
    for(i=0; i<overlap_pos1; i++)
      res1[res1len++]=ascii1[i];
    for(i=overlap_pos1; i<length1; i++)
      res2[res2len++]=ascii1[i];
    for(i=overlap_pos2+1; i<length2; i++)
      res3[res3len++]=ascii2[i];

    if (res1len>0)
    {
      conv.asciiToIOList(res1, res1len, result, invert);
      list.append(result.getFirst()->clone());
    }
    if (res2len>0)
    {
      conv.asciiToIOList(res2, res2len, result, invert);
      list.append(result.getFirst()->clone());
    }
    if (res3len>0)
    {
      conv.asciiToIOList(res3, res3len, result, invert);
      list.append(result.getFirst()->clone());
    }
    return 3;
  }
  else if (first2<first1 && last2>=first1 && last2<last1)
  {
    overlap_pos2 = length2-(last2-first1)-1;
    overlap_pos1 = (last2-first1);
    res1len=res2len=res3len=0;
    for(i=0; i<overlap_pos2; i++)
      res1[res1len++]=ascii2[i];
    for(i=overlap_pos2; i<length2; i++)
      res2[res2len++]=ascii2[i];
    for(i=overlap_pos1+1; i<length1; i++)
      res3[res3len++]=ascii1[i];

    if (res1len>0)
    {
      conv.asciiToIOList(res1, res1len, result, invert);
      list.append(result.getFirst()->clone());
    }
    if (res2len>0)
    {
      conv.asciiToIOList(res2, res2len, result, invert);
      list.append(result.getFirst()->clone());
    }
    if (res3len>0)
    {
      conv.asciiToIOList(res3, res3len, result, invert);
      list.append(result.getFirst()->clone());
    }
    return 3;
  }
  else if (first1<=first2 && last1>=last2)
  {
    overlap_pos1 = first2-first1;
    overlap_pos2 = length1 - (last1-last2) - 1;
    res1len=res2len=res3len=0;
    for(i=0; i<overlap_pos1; i++)
      res1[res1len++]=ascii1[i];
    for(i=overlap_pos1; i<=overlap_pos2; i++)
      res2[res2len++]=ascii1[i];
    for(i=overlap_pos2+1; i<length1; i++)
      res3[res3len++]=ascii1[i];

    if (res1len>0)
    {
      conv.asciiToIOList(res1, res1len, result, invert);
      list.append(result.getFirst()->clone());
    }
    if (res2len>0)
    {
      conv.asciiToIOList(res2, res2len, result, invert);
      list.append(result.getFirst()->clone());
    }
    if (res3len>0)
    {
      conv.asciiToIOList(res3, res3len, result, invert);
      list.append(result.getFirst()->clone());
    }
    return 1;
  }
  else if (first2<=first1 && last2>=last1)
  {
    overlap_pos1 = first1-first2;
    overlap_pos2 = length2 - (last2-last1) - 1;
    res1len=res2len=res3len=0;
    for(i=0; i<overlap_pos1; i++)
      res1[res1len++]=ascii2[i];
    for(i=overlap_pos1; i<=overlap_pos2; i++)
      res2[res2len++]=ascii2[i];
    for(i=overlap_pos2+1; i<length2; i++)
      res3[res3len++]=ascii2[i];

    if (res1len>0)
    {
      conv.asciiToIOList(res1, res1len, result, invert);
      list.append(result.getFirst()->clone());
    }
    if (res2len>0)
    {
      conv.asciiToIOList(res2, res2len, result, invert);
      list.append(result.getFirst()->clone());
    }
    if (res3len>0)
    {
      conv.asciiToIOList(res3, res3len, result, invert);
      list.append(result.getFirst()->clone());
    }
    return 2;
  }
  return 0;
}
*/


/*
bool IOInfoASCII::expandList(IOInfoList& input, IOInfoList& list)
{
  IOInfo *thisio, *io;
  bool split_occured;

  IOInfoList thislist, res;
  thislist.setAutoDelete(TRUE);
  res.setAutoDelete(TRUE);
  split(thislist);
  IOInfoList newlist;
  newlist.setAutoDelete(FALSE);

  QListIterator<IOInfo> thisit(thislist);

  qDebug("\n\n\nmergeWithList %s", convertToString().latin1());
  for(;thisit.current(); ++thisit)
  {
    thisio = thisit.current();

    qDebug("\n\ntreating %s", thisio->convertToString().latin1());
    newlist.clear();
    if (!list.isEmpty())
    {
      QListIterator<IOInfo> it(list);
      for(;it.current();++it)
      {
	io = it.current();
	qDebug("\nsplitting %s and %s", thisio->convertToString().latin1(), io->convertToString().latin1());

	split_occured = thisio->split(io, res);
	//list.remove(it.current());

	QListIterator<IOInfo> resit(res);

	for(; resit.current(); ++resit)
	{
	  qDebug("res: %s", resit.current()->convertToString().latin1());
	  if (!newlist.contains(resit.current()))
	  {
	    newlist.append(resit.current()->clone());
	    qDebug("element %s appended", resit.current()->convertToString().latin1());
	  }
	  else
	    qDebug("element %s already in list", resit.current()->convertToString().latin1());
	}
      }
    }
    else
    {
      newlist.append(thisio->clone());
      qDebug("first element %s appended", thisio->convertToString().latin1());
    }

    list = newlist;

    qDebug("list:");
    QListIterator<IOInfo> it(list);
    for(;it.current();++it)
    {
      io = it.current();
      qDebug("%s", io->convertToString().latin1());
    }
  }
}


*/

IOInfo* IOInfoASCII::getPlus1()
{
  unsigned char c;
  int len;
  if (!isSingle())
    return NULL;

  if (!convertToASCII(&c, 1, len, TRUE))
    return NULL;

  if (c==255) //'\255')
    return NULL;
  c++;

  IOInfo *newio;
  QString s;
  s = c;
  newio = new IOInfoASCII(type, s);
  return newio;
}

IOInfo* IOInfoASCII::getMinus1()
{
  unsigned char c;
  int len;
  if (!isSingle())
    return NULL;

  if (!convertToASCII(&c, 1, len, TRUE))
    return NULL;

  if (c==0)
    return NULL;
  c--;

  IOInfo *newio;
  QString s;
  s = c;
  newio = new IOInfoASCII(type, s);
  return newio;
}


QStringList IOInfoASCII::getRagelConditions()
{
  unsigned char asctmp[MAX_CHARARRAY_LENGTH];
  int length;
  Convert conv;
  IOInfoList list;
  int rstart, rend;
  bool isrange;
  QStringList result;
  QString stmp;
  QString single_chars;

  convertToASCII(asctmp, MAX_CHARARRAY_LENGTH, length);
  if (length==0)
    return result;

  conv.asciiToIOList(asctmp, length, list, FALSE);

  QListIterator<IOInfo*> it(list);

  for(;it.hasNext();)
  {
    IOInfo* io = it.next();

    isrange = io->isRange(rstart, rend);
    
    //qDebug("%s", io->convertToString().latin1());
    //qDebug("%d %d %d", isrange, rstart, rend);
    if (isrange)
    {
      if (rstart==int('0') && rend==int('9'))
	stmp = "digit";
      else if (rstart==int('a') && rend==int('z'))
	stmp = "lower";
      else if (rstart==int('A') && rend==int('Z'))
	stmp = "upper";
      else if (rstart==0 && rend==255)
	stmp = "any";
      else if (rstart==0 && rend==127)
	stmp = "ascii";
      else
      {
	unsigned char c1, c2;
	c1 = (unsigned char)rstart;
	c2 = (unsigned char)rend;
	

	if (IOInfoASCII::isReadable(c1) && IOInfoASCII::isReadable(c2))
	{
	  QString s1=QChar(c1), s2=QChar(c2);
	  s1.replace(QRegExp("[\"]"),"\\\""); 
	  s1.replace(QRegExp("[\']"),"\\\'"); 
	  s1.replace(QRegExp("[/]"),"\\/"); 
	  s1.replace(QRegExp("[\\[]"),"\\["); 
	  s1.replace(QRegExp("[\\]]"),"\\]"); 
	  s1.replace(QRegExp("[\\-]"),"\\-"); 
	  s2.replace(QRegExp("[\"]"),"\\\""); 
	  s2.replace(QRegExp("[\']"),"\\\'"); 
	  s2.replace(QRegExp("[/]"),"\\/"); 
	  s2.replace(QRegExp("[\\[]"),"\\["); 
	  s2.replace(QRegExp("[\\]]"),"\\]"); 
	  s2.replace(QRegExp("[\\-]"),"\\-"); 
	  stmp.sprintf("%s-%s", s1.latin1(), s2.latin1()); 
	  single_chars += stmp;
	  stmp="";
	}
	else
	{
	  QString stmp1, stmp2;
	  /*
	  signed char sc1=(signed char)c1, sc2=(signed char)c2;
	  unsigned char sctmp;
	  if (sc1>sc2)
	  {
	    sctmp=c1;
	    c1 = c2;
	    c2 = sctmp;
	  }
	  */
	  if (c2>127)
	  {
	    stmp1.sprintf("0x%s", conv.asciiToHexStr(c1).latin1());
	    stmp2.sprintf("0x%s", conv.asciiToHexStr(127).latin1());
	    stmp = stmp1 + ".." + stmp2;

	    if (invert)
	      stmp = "^(" + stmp + ")";
	    result.append(stmp);

	    //c2 = c1;
	    c1 = (unsigned char)-128;
	  }

	  stmp1.sprintf("0x%s", conv.asciiToHexStr(c1).latin1());
	  stmp2.sprintf("0x%s", conv.asciiToHexStr(c2).latin1());

	  stmp = stmp1 + ".." + stmp2;
	}
      }
    }
    else
    {
      unsigned char c[1];
      int len;
      
      io->convertToASCII(c, 1, len);
      if (IOInfoASCII::isReadable(c[0]))
      {
	//stmp.sprintf("%c", c[0]);
	QString s1=QChar(c[0]);
	s1.replace(QRegExp("[\"]"),"\\\""); 
	s1.replace(QRegExp("[\']"),"\\\'"); 
	s1.replace(QRegExp("[/]"),"\\/"); 
	s1.replace(QRegExp("[\\[]"),"\\["); 
	s1.replace(QRegExp("[\\]]"),"\\]"); 
	s1.replace(QRegExp("[\\-]"),"\\-"); 
	single_chars += s1;
	stmp="";
      }
      else
	stmp.sprintf("0x%s", conv.asciiToHexStr(c[0]).latin1());

    }
    if (!stmp.isEmpty())
    {
      if (invert)
	stmp = "^(" + stmp + ")";
      result.append(stmp);
    }
  } // end for it

  if (!single_chars.isEmpty())
  {
    if (invert)
      single_chars = "^" + single_chars;
    single_chars = "[" + single_chars + "]";
    result.append(single_chars);
  }

  QStringList::iterator it1, it2;
  // replace 'upper' and 'lower' by 'alpha'
  it1 = result.find("upper");
  it2 = result.find("lower");
  if (it1!=result.end() && it2!=result.end())
  {
    result.erase(it1);
    result.erase(it2);
    result.append("alpha");
  }

  // replace 'alpha' and 'digit' by 'alnum'
  it1 = result.find("alpha");
  it2 = result.find("digit");
  if (it1!=result.end() && it2!=result.end())
  {
    result.erase(it1);
    result.erase(it2);
    result.append("alnum");
  }

  return result;
}


void IOInfoASCII::setAnyInput(bool ai) 
{
  IOInfo::setAnyInput(ai);

  if (ai)
  {
    info = "\\000-\\0FF";
    setRange(0, 255);
  }
}


void IOInfoASCII::updateDefaultInfo(const IOInfoList& other)
{
  if (!def)
    return;

  unsigned char ascii[MAX_CHARARRAY_LENGTH];
  Convert conv;
  int alen=0;
  bool others_contain;

  for(int i=0; i<=255; i++)
  {
    unsigned char a = (unsigned char)i;
    IOInfoASCII ioa(IO_MealyIn, a);
    
    others_contain=FALSE;
    QListIterator<IOInfo*> it(other);
    for(;it.hasNext();)
    {
      if (it.next()->matches(&ioa))
	others_contain=TRUE;
    }
    if (!others_contain)  // put ascii char it into default condition
      ascii[alen++]=a;
  }
  info = conv.asciiToReadableStr(ascii, alen);
}





