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

#include "IOInfoText.h"
#include "Const.h"
#include "Convert.h"
#include "IOInfoASCII.h"
#include "IOInfoList.h"

/// Standard constructor
IOInfoText::IOInfoText(IOType t) : IOInfo(t) {}

/// Constructor
IOInfoText::IOInfoText(IOType t, unsigned char i) : IOInfo(t) {
  //  info = QString(QChar(i));
  Convert conv;
  info = conv.asciiToReadableStr(&i, 1);
}

/// Constructor
IOInfoText::IOInfoText(IOType t, QString i) : IOInfo(t) { info = i; }

void IOInfoText::setRangeInfo(IOInfo *rstart, IOInfo *rend) {
  unsigned char as[MAX_CHARARRAY_LENGTH];
  unsigned char ae[MAX_CHARARRAY_LENGTH];
  int lena, lene;
  Convert conv;
  QString ss, se;

  rstart->convertToASCII(as, MAX_CHARARRAY_LENGTH, lena, true);
  rend->convertToASCII(ae, MAX_CHARARRAY_LENGTH, lene, true);

  ss = conv.asciiToReadableStr(as, lena);
  se = conv.asciiToReadableStr(ae, lene);
  if (ss == se) {
    info = ss;
    range = false;
  } else {
    info = ss + "-" + se;
    range = true;
    range_start = int((unsigned char)as[0]);
    range_end = int((unsigned char)ae[0]);
  }
  type = rstart->getType();
  role = false;
}

/// Destructor
IOInfoText::~IOInfoText() {}

QString IOInfoText::convertToString(Machine * /*m=NULL*/,
                                    Options * /*opt=NULL*/) const {
  return info;
}

QString IOInfoText::convertToComparableString(Machine * /*m=NULL*/,
                                              Options * /*opt=NULL*/) const {
  /*
  IOInfoList list;
  list.setAutoDelete(true);
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

QString IOInfoText::convertToBinStr(Machine * /*m=true*/,
                                    Options * /*opt=NULL*/) const {
  unsigned char ascii[MAX_CHARARRAY_LENGTH];
  int alen;

  if (!convertToASCII(ascii, MAX_CHARARRAY_LENGTH, alen))
    return "";

  Convert conv;
  return conv.asciiToBinStr(alen * 8, ascii, MAX_CHARARRAY_LENGTH);
}

QString IOInfoText::convertToHexStr() const {
  Convert conv;
  unsigned char ascii[MAX_CHARARRAY_LENGTH];
  int length;

  conv.resolveEscapes(info, ascii, MAX_CHARARRAY_LENGTH, length);
  return conv.asciiToHexStr(ascii, length);
}

IOInfoBin IOInfoText::convertToBin(int numbits) const {
  Convert conv;
  unsigned char ascii[MAX_CHARARRAY_LENGTH];
  int length;

  conv.resolveEscapes(info, ascii, MAX_CHARARRAY_LENGTH, length);
  return conv.asciiToX10(numbits, ascii, length, type);
}

int IOInfoText::convertToInt() const {
  Convert conv;
  QString binstr;

  if (!isSingle())
    return -1;

  binstr = convertToBinStr();
  return conv.binStrToInt(binstr);
}

void IOInfoText::convertToBinList(IOInfoList &list,
                                  bool resolve_invert /*=true*/) const {
  unsigned char ascii[MAX_CHARARRAY_LENGTH];
  int calen;

  convertToASCII(ascii, MAX_CHARARRAY_LENGTH, calen);

  if (!invert || !resolve_invert) {
    for (int i = 0; i < calen; i++) {
      unsigned char a;
      IOInfoBin *bin = new IOInfoBin(type);
      a = ascii[i];
      bin->setASCII(&a, 1, 8);
      list.append(bin);
    }
  } else {
    for (int i = 0; i <= 255; i++) {
      unsigned char a = (unsigned char)i;
      if (IOInfoASCII::findChar(ascii, calen, a) == -1) {
        IOInfoBin *bin = new IOInfoBin(type);
        bin->setASCII(&a, 1, 8);
        list.append(bin);
      }
    }
  }
}

void IOInfoText::setBin(QString bin, int) {
  Convert conv;
  unsigned char ascii[MAX_CHARARRAY_LENGTH];
  int length;

  if (conv.binStrToASCII(bin, ascii, MAX_CHARARRAY_LENGTH, length, false))
    info = conv.asciiToReadableStr(ascii, length);
}

void IOInfoText::setASCII(const unsigned char *ascii, int asciilen, int) {
  Convert conv;
  info = conv.asciiToReadableStr(ascii, asciilen);
}

void IOInfoText::setString(QString string, int) { info = string; }

bool IOInfoText::convertToASCII(unsigned char *ascii, int maxlen, int &length,
                                bool singlechar /*=false*/) const {
  Convert conv;
  if (singlechar) {
    unsigned char asctmp[MAX_CHARARRAY_LENGTH];
    int alen;

    conv.resolveEscapes(info, asctmp, MAX_CHARARRAY_LENGTH, alen);
    if (maxlen > 0)
      ascii[0] = asctmp[alen - 1];
    length = 1;
  } else
    conv.resolveEscapes(info, ascii, maxlen, length);

  return true;
}

bool IOInfoText::isSingle() const {
  return true;

  /*
  QString stmp;
  int ccount=0;
  int i=0, len;
  char ctmp;
  bool escprev=false;

  if (info.isEmpty())
    return false;

  stmp = info.stripWhiteSpace();
  len = stmp.length();

  while(i<len)
  {
    ctmp=info[i].latin1();
    if (ctmp=='\\' && escprev==false)
    {
      escprev=true;

      if (i<len-1)
      {
        if (info[(i+1)]=='0')
        {
          if (i>=len-3)
            return false;
          i+=2;
        }
      }
    }
//    else if (ctmp=='-')
//      return false;
    else
      ccount++;

    i++;
    escprev=false;
  }

  if (ccount==1)
    return true;
  else
    return false;
    */
}

QList<IOInfo *> IOInfoText::getSingles() {
  QList<IOInfo *> list;
  list.append(new IOInfoText(type, info));
  return list;

  /*
  int i=0; //, fpos=0;
  int len;
//  char lc, rc;
  char ctmp=0, cprev=0, cnext;
  bool nextisescape=false;
  bool previsdigit=false, nextisdigit=false;
  QString sinf;
  Convert conv;
  bool firstadded=false;

  len = info.length();

  while (i<len)
  {

    ctmp = info[i].latin1();
    if (ctmp=='\\')		// escape sequence
    {
      if(i==len-1)
        break;

      bool append=true;
//      ctmp = escapeToChar(info[i+1].latin1());
      QString sesc;
      //QString cnext;
      cnext = info[(i+1)].latin1();
      if (cnext=='0')
      {
        if (i>=len-3)
        {
          append=false;
          i=len;
        }
        else
        {
          sesc.sprintf("\\0%c%c", info[(i+2)].latin1(), info[(i+3)].latin1());
          i+=2;

          int asciilen;
          conv.resolveEscapes(sesc, &ctmp, 1, asciilen);
        }
        previsdigit=false;
      }
      else if (cnext=='d')
      {
        previsdigit=true;
        if (i>=len-2 || (info[(i+2)].latin1()!='-'))	// append just 10 digits
        {
          for(char r='0'; r<='9'; r++)
          {
            list.append(new IOInfoText(type, r));
          }
        }
        append=false;
      }
      else
      {
        previsdigit=false;
        //sesc = "\\" + cnext;
        sesc.sprintf("\\%c",cnext);
      }

      if (append)
      {
        list.append(new IOInfoText(type, sesc));
        firstadded=true;
      }
      else
        firstadded=false;

      i++;
    }
    else if (ctmp=='-')
    {
      char cnext;
      bool includefirst=false;

      if (len==1)
      {
        list.append(new IOInfoText(type, '-'));
        return list;
      }
      if (i==0 || i==len-1)
        break;

      cnext = info[(i+1)].latin1();
      if (cnext=='\\')
      {
        nextisescape=true;

        if (i==len-2)
          break;


        if (info[(i+2)].latin1()=='d')
        {
          nextisdigit=true;
          if (previsdigit)
          {
            cprev='0';
            cnext='9';
            includefirst=true;
          }
          else if (cprev<'0')
          {
            cnext='9';
          }
          else if (cprev>'9')
          {
            cnext='0';
            //includefirst=true;
          }
          else
          {
            cprev='0';
            cnext='9';
            includefirst=true;
          }
        }
        else if (info[(i+2)].latin1()=='0')
        {
          if (i>=len-4)
          {
//	    append=false;
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
          cnext = IOInfoASCII::escapeToChar(info[(i+2)].latin1());
      }
      else
      {
        nextisescape=false;
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
          includefirst=true;
        }
      }

      if (cprev>cnext)
      {
        char chartmp;
        chartmp=cnext;
        cnext=cprev;
        cprev=chartmp;
        if (firstadded)
          includefirst=true;
      }
      if (!firstadded || includefirst)
        cprev--;
      for(char r=cprev+1; r<=cnext; r++)
      {
        list.append(new IOInfoText(type, r));

      }
      firstadded=true;

      i++;
      if (nextisescape)
        i++;
    }
    else
    {
      list.append(new IOInfoText(type, ctmp));

      if (ctmp>='0' && ctmp<='9')
        previsdigit=true;
      else if (ctmp!='\\')
        previsdigit=false;
      firstadded=true;
    }

    i++;
    cprev=ctmp;
  }

  return list;
  */
}

QList<IOInfo *> IOInfoText::getSinglesInversion() { return getSingles(); }

IOInfo *IOInfoText::clone() const { return new IOInfoText(*this); }

void IOInfoText::split(IOInfoList &list, bool /*resolve_invert*/) const {
  /*
  Convert conv;

  char asctmp[MAX_CHARARRAY_LENGTH];
  int length;
  convertToASCII(asctmp, MAX_CHARARRAY_LENGTH, length);

  conv.asciiToIOList(asctmp, length, list);
  */
  list.append(this->clone());
}

void IOInfoText::split(IOInfoList &list, GState *) const { split(list, true); }

/* *
 * Creates a list of IOInfo objects out of this IOInfo and @a ioinfo
 * splitting the IOInfos if they overlap
 *
 * @param ioinfo IOInfoText object to merge with
 * @param list Resulting list
 * @returns 1 if this IOInfo completely contains @a ioinfo,
 * 	    2 if @a ioinfo completely contains this IOInfo,
 *          3 if the two overlap,
 *          0 if no split occured
 */
/*
int IOInfoText::split(const IOInfo* ioinfo, IOInfoList& list)
{
  list.clear();
  list.append(ioinfo);
  list.append(this->clone());

  return 0;
}
*/

IOInfo *IOInfoText::getPlus1() {
  return NULL;
  /*
  char c;
  int len;
  if (!isSingle())
    return NULL;

  if (!convertToASCII(&c, 1, len, true))
    return NULL;

  if (c=='\255')
    return NULL;
  c++;

  IOInfo *newio;
  QString s;
  s = c;
  newio = new IOInfoText(type, s);
  return newio;
  */
}

IOInfo *IOInfoText::getMinus1() {
  return NULL;

  /*
  char c;
  int len;
  if (!isSingle())
    return NULL;

  if (!convertToASCII(&c, 1, len, true))
    return NULL;

  if (c==0)
    return NULL;
  c--;

  IOInfo *newio;
  QString s;
  s = c;
  newio = new IOInfoText(type, s);
  return newio;
  */
}
