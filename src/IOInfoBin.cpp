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

#include "IOInfoBin.h"
#include "IOInfoASCII.h"
#include "Convert.h"
#include "Const.h"
#include "IOInfoList.h"
#include "Options.h"
#include "Machine.h"
#include "TransitionInfo.h"

/**
 * Constructor.
 * Initialises the IOInfo object with the bits contained in the array @a io
 * with the length @a len.
 */
IOInfoBin::IOInfoBin(IOType t, QString io, bool inv/*=FALSE*/)
  : IOInfo(t, inv)
{
/*  int len=0;
  while (io[len]!=10)
  len++;

  info = new char[len+1];
  for(int i=0; i<len; i++)
  info[i]=io[i];
  info[len]=10;
  */

  info=setBinFormat(io);
}

/**
 * Standard constructor.
 * Sets no information.
 */
IOInfoBin::IOInfoBin(IOType t, bool inv/*=FALSE*/)
  : IOInfo(t, inv)
{
  info = QString("");
//  length=0;
}


/**
 * Constructor.
 * 
 * @param code I/O info in decimal form
 * @param len Length of the I/O info (in bits)
 */
IOInfoBin::IOInfoBin(IOType t, int code, int len, bool inv/*=FALSE*/)
  : IOInfo(t, inv)
{
  Convert conv;
  QString stmp;
  IOInfoBin iotmp(t);

  stmp = conv.intToBinStr(code, len);
//  iotmp = conv.binStrToX10(len, stmp, t);

//  info=NULL;
//  *this = iotmp;
  info=stmp;
  
}


void IOInfoBin::setRangeInfo(IOInfo* range_start, IOInfo* /*range_end*/)
{
  if (range_start!=NULL)
  {
    *this = range_start->convertToBin(getLength());
    role=FALSE;
  }
}

/// Destructor
IOInfoBin::~IOInfoBin()
{
//  if (info)
//    delete [] info;
}

int IOInfoBin::getLength() const
{
/*  int count=0;
  if (!info)
  return count;

  while (info[count]!=10)
  count++;

  return count;
  */
  int len=info.find('|');
  if(len==-1)
    len=info.length();
  if(len<0)
    len=0;
  return len;
}



/// Copy constructor.
IOInfoBin::IOInfoBin(const IOInfoBin& io)
  : IOInfo(io.getType())
{
    role=io.role;
    invert=io.invert;
    range=io.range;
    range_start=io.range_start;
    range_end=io.range_end;
    any=io.any;
    def=io.def;

/*
  int len = io.getLength();
  info = new char[len+1];


  for(int i=0; i<len; i++)
  info[i]=io.info[i];
  info[len]=10;
  */
  info=io.info;
}

/// Overloaded assignment operator.
IOInfoBin& IOInfoBin::operator=(const IOInfoBin& io)
{
  if (this != &io)
  {
    type = io.getType();
    role = io.getRole();
    invert = io.isInverted();
/*    if (info)
    delete [] info;
    int len = io.getLength();
    info = new char[len+1];
//    length = io.length;

    for(int i=0; i<len; i++)
    info[i]=io.info[i];
    info[len]=10;
*/
    info=io.info;
  }
  return *this;
}

/*
/// Converts to binary (does nothing)
IOInfoBin IOInfoBin::convertToBin()
{
  IOInfoBin tmp;
  tmp = *this;
  return tmp;
//  return *this;
}
*/


///corrects the format of the string @a io and returns the corrected string
QString IOInfoBin::setBinFormat(QString io)
{
  QStringList ioParts;
  int maxLen=0;
  QStringList::iterator i;
  QString result;
  
  for(int c=0; c<io.length(); c++)
  {
    if(io[c]!='1' && io[c]!='0' && io[c]!='x' && io[c]!='|')
    {
      io.remove(c,1);
      c--;
    }
  }

  ioParts=io.split('|');

  for(i=ioParts.begin(); i!=ioParts.end(); ++i)
    if(maxLen<i->length())
      maxLen=i->length();


  for(i=ioParts.begin(); i!=ioParts.end(); ++i)
  {
    if(i->length()<maxLen)
    {
      i->prepend(QString(maxLen-i->length(),'0'));
    }
  }
  
  for(i=ioParts.begin(); i!=ioParts.end(); ++i)
  {

    result+=(*i);
    if(i+1!=ioParts.end())
      result+="|";
  }
  
  return result;
}


bool IOInfoBin::isSingle() const
{
/*  int i=0;
  while (info[i]!=10) //end of info is marked with 10?
  {
  if (info[i]==2)
  return FALSE;
  i++;
}
  return TRUE;*/
  if(info.contains('X') || info.contains('|'))
    return FALSE;
  else return TRUE;
}



QString IOInfoBin::convertToString(Machine* m/*=NULL*/, Options* opt/*=NULL*/) const
{
  /*
  int len;
  len = getLength();
  QString stmp;

  for(int i=0; i<len; i++)
  {
  if (info[i]==0)
  stmp += "0";
  else if (info[i]==1)
  stmp += "1";
  else if (info[i]==2)
  stmp += "x";
}
  return stmp;
  */

  return convertToBinStr(m, opt);
}

QString IOInfoBin::convertToComparableString(Machine* m/*=NULL*/, Options* opt/*=NULL*/) const
{
  return convertToString(m, opt); // + QString::number(!role);
}

QString IOInfoBin::convertToBinStr(Machine* m/*=NULL*/, Options* opt/*=NULL*/) const
{
  QString result("");
  if (opt!=NULL && opt->getDisplayIONames())
  {
    QStringList ioList;
    ioList=info.split("|");
    QStringList::iterator ioit;
    bool first;
    int count, len;
    QString stmp2,stmp;
    QStringList::iterator it;
    QStringList names;
    
    
    
    for(ioit = ioList.begin(); ioit!=ioList.end(); ++ioit)
    {
      stmp=*ioit;
      stmp2="";
    
      if (type==IO_MealyIn)
        names=m->getInputNameList();
      else if (type==IO_MealyOut)
        names=m->getOutputNameList();
      else if (type==IO_MooreOut)
        names=m->getMooreOutputList();
      len = stmp.length();
    
      count=0;
      first=TRUE;
      for(it = names.begin(); it!=names.end(); ++it)
      {
        if (count<len)
        {
          if (stmp[count]=='x')
            count++;
          else
          {
            if (!first)
              stmp2 += ", ";
            stmp2 += *it + "=" + stmp[count++];
            first=FALSE;
          }
        }
      }
      result+=stmp2;
      if((ioit+1)!=ioList.end())
        result+=" | ";
    }
  }
  else result=info;
  if (opt && opt->getIOMark() && !opt->getDisplayIONames())
  {
    if (result.length()>0)
    {
      if (type==IO_MealyIn)
        result = "?" + result;
      else if (type==IO_MealyOut)
        result = "!" + result;
    }
  }
  return result;
/*  Convert conv;
  QString stmp;
  stmp = conv.X10ToBinStr(*this);
  if (opt!=NULL && opt->getDisplayIONames())
  {
  bool first;
  int count, len;
  QString stmp2;
  QStringList::iterator it;
  QStringList names;

  if (type==IO_MealyIn)
  names=m->getInputNameList();
  else if (type==IO_MealyOut)
  names=m->getOutputNameList();
  else if (type==IO_MooreOut)
  names=m->getMooreOutputList();
  len = stmp.length();

  count=0;
  first=TRUE;
  for(it = names.begin(); it!=names.end(); ++it)
  {
  if (count<len)
  {
  if (stmp[count]=='x')
  count++;
  else
  {
  if (!first)
  stmp2 += ", ";
  stmp2 += *it + "=" + stmp[count++];
  first=FALSE;
}
}
}
  stmp = stmp2;
}
  if (opt && opt->getIOMark() && !opt->getDisplayIONames())
  {
  if (stmp.length()>0)
  {
  if (type==IO_MealyIn)
  stmp = "?" + stmp;
  else if (type==IO_MealyOut)
  stmp = "!" + stmp;
}
}
  return stmp;
  */
}


QString IOInfoBin::convertToHexStr() const
{
  Convert conv;
  return conv.X10ToHexStr(*this);
}

bool IOInfoBin::convertToASCII(unsigned char* ascii, int maxlen, int& length, bool
    singlechar/*=FALSE*/) const
{
  Convert conv;

  return conv.X10ToASCII(*this, ascii, maxlen, length, singlechar);
}


IOInfoBin IOInfoBin::convertToBin(int numbits) const
{
  IOInfoBin tmp(type);
  tmp = *this;
  tmp.setSize(numbits);
//  tmp.setInputsSize(numbits);
//  tmp.setOutputsSize(numbits);

  return tmp;
}


int IOInfoBin::convertToInt() const
{
  QString binstr;
  Convert conv;
  if (!isSingle())
    return -1;
  binstr = convertToBinStr();
  return conv.binStrToInt(binstr);
}



void IOInfoBin::setBin(QString bin, int numbits)
{
  info=setBinFormat(bin);
  setSize(numbits);
  //  Convert conv;
//  IOInfoBin iobin = conv.binStrToX10(numbits, bin, type); 
//  *this = iobin;
}

void IOInfoBin::setASCII(const unsigned char* ascii, int asciilen, int numbits)
{
  Convert conv;
  IOInfoBin iobin = conv.asciiToX10(numbits, ascii, asciilen, type);
  *this = iobin;
}

void IOInfoBin::setString(QString string, int numbits)
{
  Convert conv;
  unsigned char ascii[MAX_CHARARRAY_LENGTH];
  int length;

  conv.resolveEscapes(string, ascii, MAX_CHARARRAY_LENGTH, length);
  setASCII(ascii, length, numbits);
}


void IOInfoBin::setSize(int newin)
{
  if(newin<=0)
    info="";
  else if(newin>getLength())
  {
    int diff=newin-getLength();
    QString ins(diff,'0');
    info.prepend(ins);
    info.replace("|","|"+ins);
  }
  else if(newin<getLength())
  {
    int diff=getLength()-newin;
    info.remove(0,diff);
    int pos=-1;
    while((pos=info.find("|",pos+1))!=-1)
      info.remove(pos+1,diff);

  }
/*  int oldin = getLength();
//  char old[oldin+1];
  int oldcount;
  char *old, *pin;

  old = new char[oldin+1];
  pin = getInfo();

  for (int i=0; i<oldin; i++)   //don't copy anything when oldin == 0
  {
  old[i] = pin[i];
}
  old[oldin]=10;        //set end character

  if(newin>0)
  {
  pin = new char[newin+1];
    
  oldcount = oldin;
  for(int j=newin-1; j>=0; j--)
  {
  if (oldcount>0)
  pin[j] = old[oldcount-1];
  else
  pin[j]=0;
    
  oldcount--;
}
  pin[newin]=10;

}
  else pin=NULL;

  setInfo(pin);
  if(pin!=NULL)
  delete [] pin;
  delete [] old;

*/
}

/*
void IOInfoBin::setOutputsSize(int newout)
{
  int oldout = getLength();
  char old[oldout+1];
  int oldcount;
  char* pout;

  pout = getInfo();
  for (int i=0; i<=oldout; i++)
{
    old[i] = pout[i];
}

  pout= new char[newout+1];

  oldcount = oldout;
  for(int j=newout-1; j>=0; j--)
{
    if (oldcount>0)
      pout[j] = old[oldcount-1];
    else
      pout[j]=0;

    oldcount--;
}
  pout[newout]=10;

  setInfo(pout);

  delete [] pout;
}
*/



  
/// Sets the I/O info to the character string @a io (binary format, see IOInfoBin::info)
void IOInfoBin::setInfo(QString io)
{
  info=setBinFormat(io);
/*  int len=0;
  if(io!=NULL)
  {
  while (io[len]!=10)
  len++;
}

  if (info)
  delete info;

  info = new char[len+1];
  for(int i=0; i<len; i++)
  info[i]=io[i];
  info[len]=10;
*/
}


/// Inverts the order of the bits of this I/O info
void IOInfoBin::invertBits()
{
/*  IOInfoBin io(type, info);
  int len=getLength();
  char* buf = io.getInfo();

  for(int i=0; i<len; i++)
  info[i] = buf[len-i-1];
  */
  QString io=info;
  info="";
  QStringList ioParts=io.split('|');

  QStringList::const_iterator i;
  for(i=ioParts.constBegin(); i!=ioParts.constEnd(); ++i)
  {
    for(int c=i->length()-1; c>=0; c--)
    {
      info+=(*i)[c];
    }
    if(i+1!=ioParts.constEnd())
      info+="|";
  }

}

  
/*
bool IOInfoBin::equals(IOInfo* io)
{
  IOInfoBin* iotmp = io->convertToBin(); //(IOInfoBin*)io;
  int len1, len2;
  len1 = getLength();
  len2 = iotmp->getLength();
  char *buf1, *buf2;

  if (len1!=len2)
    return FALSE;

  buf1 = info;
  buf2 = iotmp->getInfo();

  for(int i=0; i<len1; i++)
{
    if (buf1[i]!=buf2[i] && buf1[i]!=2 && buf2[i]!=2)
      return FALSE;
}
  return TRUE;

}

*/


/*bool IOInfoBin::matches(IOInfo* io)
{
//  return equals(io);

  int len1, len2;
  len1 = getLength();
  len2 = io->getLength();
  char *buf1, *buf2;
  int maxlen = len1>len2?len1:len2;

//  if (len1!=len2)
//    return FALSE;

  IOInfoBin iotmp1 = convertToBin(maxlen); //(IOInfoBin*)io;
  IOInfoBin iotmp2 = io->convertToBin(maxlen); //(IOInfoBin*)io;

  buf1 = iotmp1.getInfo();
  buf2 = iotmp2.getInfo();

  for(int i=0; i<maxlen; i++)
{
    if (buf1[i]!=buf2[i] && buf1[i]!=2 && buf2[i]!=2)
      return FALSE;
}
  return TRUE;

}*/



QList<IOInfo*> IOInfoBin::getSingles()
{
  QList<IOInfo*> list;
  QStringList ioParts=info.split('|');

  QStringList::const_iterator i;
  for(i=ioParts.constBegin(); i!=ioParts.constEnd(); ++i)
  {
    list.append(new IOInfoBin(type,*i));
  }


  return list;
}

QList<IOInfo*> IOInfoBin::getSinglesInversion()
{
  if (!invert)
    return getSingles();

  QList<IOInfo*> list;
  int len = getLength();
  int max = 1<<len;
  for(int i=0; i<=max; i++)
  {
    IOInfoBin* newio = new IOInfoBin(type, i, len);
    if (matches(newio))
      list.append(newio);
      //list.append(new IOInfoBin(type, i, len));
    else
      delete newio;
  }
  
  return list;
}

int IOInfoBin::getNumSingles()
{
/*  int len = getLength();
  int nmaxinputs = (int)pow(2.0, len);
  int result = 1;

  for(int i=0; i<len; i++)
  {
  if (info[i]==2)  // "don't care" bit
  result*=2;
}
  if (invert)
  result = nmaxinputs - result;
*/
  int result=0,partNum;
  QStringList ioParts=info.split('|');

  QStringList::const_iterator i;
  for(i=ioParts.constBegin(); i!=ioParts.constEnd(); ++i)
  {
    partNum=1;
    for(int c=0; c<i->length(); c++)
      if((*i)[c]=='x')
        partNum*=2;
    result+=partNum;
  }
  return result;
}


/*
IOInfoBin* IOInfoBin::getIOInfoBin() const
{
  IOInfoBin* tmp = new IOInfoBin();
  *tmp = *this;
  return tmp;
}

IOInfoASCII* IOInfoBin::getIOInfoASCII() const
{
  IOInfoASCII* tmp = new IOInfoASCII();
  char ascii[MAX_CHARARRAY_LENGTH];
  int len;
  convertToASCII(ascii, MAX_CHARARRAY_LENGTH, len);
  tmp->setASCII(ascii, MAX_CHARARRAY_LENGTH, len);
  return tmp;
}
*/

IOInfo* IOInfoBin::clone() const
{
  return new IOInfoBin(*this);
}

void IOInfoBin::split(IOInfoList& list, bool resolve_invert) const
{
  list.clear();

  if (invert && !resolve_invert)
  {
    // This case has not been tested and is currently not used. 
    // I'm not sure why we do not split here. 
    list.append(this->clone());
  }
  else if (!invert || !resolve_invert)
  {
    resolveX(*this, list); 
  }
  else // invert && resolve_invert
  {
    IOInfoList xlist;
    resolveX(*this, xlist); 

    int len = 1<<getLength();
    for(int i=0; i<len; i++)
    {
      IOInfoBin* iotmp = new IOInfoBin(type, i, getLength());
      xlist.setInvert(FALSE);
      if(!xlist.contains(iotmp))
      {
        list.append(iotmp);
      }
      else
        delete iotmp;
    }
  }
}

void IOInfoBin::split(IOInfoList& list, GState* s) const
{
  bool condition_found=false;
  list.clear();

  if(def)
  {
    GTransition*t;
    IOInfoBin*iotmp;


    int len=1<<getLength();
    for(int i=0; i<len; i++)
    {
      QListIterator<GTransition*> it(s->tlist);
      iotmp=new IOInfoBin(type,i,getLength());
      condition_found=false;
      while(it.hasNext())
      {

        t=it.next();
        if(t->getInfo()->getInputInfo()->matches(iotmp) &&!t->getInfo()->getInputInfo()->isDefault())
        {
          condition_found=true;
          break;
        }
      }
      if(!condition_found)
        list.append(iotmp);
    }
//    qDebug("Split default transition "+s->getStateName()+" length: "+QString::number(list.length())+" of "+QString::number(len));
  }
  else split(list,true);


}

/*
int IOInfoBin::split(const IOInfo* ioinfo, IOInfoList& list)
{
  list.clear();

  list.append(this->clone());
  list.append(ioinfo->clone());

  return 0;
}
*/


/*
bool IOInfoBin::expandList(IOInfoList&, input, IOInfoList& list)
{
  IOInfoList iolist;
  IOInfo *infos, *infoc;
  iolist.setAutoDelete(TRUE);

  split(iolist);
  
  QListIterator<IOInfo> ioit(iolist);
  for(; ioit.current(); ++ioit)
{
    infos = ioit.current();

    if (list.contains(infos)==0)
{
      infoc = infos->clone();
      list.append(infoc);
}
}
}
*/

void IOInfoBin::convertToBinList(IOInfoList& list, bool resolve_invert/*=TRUE*/) const
{
  // resolveX(*this, list); 
  split(list, resolve_invert);
}


/**
 * Resolves the 'don't care' positions.
 * Example: '0X' would result in '00' and '01'
 *
 * @param bin Object to convert
 * @param list Resulting list of IOInfo objects
 */
void IOInfoBin::resolveX(IOInfoBin bin, IOInfoList& list)
{
  int current_index, pos;
  QString* s;
  QList<IOInfo*> singles=bin.getSingles();

  QList<IOInfo*>::const_iterator ii;
  for(ii=singles.constBegin(); ii!=singles.constEnd(); ++ii)
  {
    QVector<QString> infoList;
    infoList.append(((IOInfoBin*)(*ii))->getInfo());
    current_index=0;
    
    while(current_index<infoList.size())
    {
      s=&(infoList[current_index]);
      pos=s->indexOf('x');
      
      if(pos==-1) // no more x
      {
	list.append(new IOInfoBin(bin.getType(),*s));
	current_index++;
      }
      else // 
      {
        s->replace(pos,1,QChar('0'));
        infoList.append(QString(*s).replace(pos,1,QChar('1')));
      }
    }
    /*
    // old version
    while(si!=infoList.end())
    {
      //QString *s=&(*si);
      QString *s=&(*si);
      int pos=s->indexOf('x');
      //qDebug(*s);
      
      if(pos==-1) // no more x
      {
	list.append(new IOInfoBin(bin.getType(),*si));
	current_index++;
        ++si;
      }
      else // 
      {
        s->replace(pos,1,QChar('0'));
        //infoList.append(QString(*s).replace(pos,1,QChar('1')));
        infoList.append(s->replace(pos,1,QChar('1')));
        
        //si=infoList.begin();
	si = infoList.begin()+current_index;
      }
    }
    */
    /*
    for(si=infoList.begin(); si!=infoList.end(); ++si)
    {
      list.append(new IOInfoBin(bin.getType(),*si));
    }
    */
  }

  while (!singles.isEmpty())
     delete singles.takeFirst();
  
}



/** 
 * Returns TRUE if @a io matches this object (i.e. this I/O info contains @a io).
 * IOInfo::matches() also works but is less efficient (especially for lots of "don't care" bits).
 */
bool IOInfoBin::matches(IOInfo* io)
{
  bool io_matches;
  IOInfoList l1,l2;
  IOInfoBin b1(type), b2(type);
  int len1, len2, maxlen;
  len1 = getLength();
  len2 = io->getLength();

  maxlen = len1>len2? len1 : len2;

  b1 = convertToBin(maxlen);
  b2 = io->convertToBin(maxlen);

  if (any) // any input is accepted
    return TRUE;

  if(def && io->isDefault())   // can this case occur? 
    return FALSE;

  l1 = b1.getSingles();
  b2.split(l2,true);

  // all b2 must be "contained" in b1
  IOInfoList::const_iterator i1,i2;
  QString b1s, b2s;
  int pos=0;

  for(i2=l2.constBegin(); i2!=l2.constEnd(); ++i2)
  {
    b2s = ((IOInfoBin*)(*i2))->getInfo();
    if (isInverted()) // for inverted transitions, every inverted component needs to match (as !(A | B) is equivalent with !A & !B)
      io_matches=true;
    else
      io_matches=false;
    for(i1=l1.constBegin(); i1!=l1.constEnd(); ++i1)
    {
      b1s = ((IOInfoBin*)(*i1))->getInfo();
      pos=b1s.indexOf('x');
      while(pos>=0)
      {
	b1s.replace(pos,1,b2s[pos]);
	pos=b1s.indexOf('x', pos+1);
      }
      //qDebug("comparing: %s and %s", b1s.latin1(), b2s.latin1());
      if (isInverted())
      {
	if (b1s==b2s)
	{
	  io_matches=false;
	  break;
	}
      }
      else
      {
	if (b1s==b2s)
	{
	  io_matches=true;
	  break;
	}
      }
    }
    if (io_matches==false)
      return false;
  }

   while (!l1.isEmpty())
     delete l1.takeFirst();
   while (!l2.isEmpty())
     delete l2.takeFirst();

  return true;
}

    

IOInfo* IOInfoBin::getPlus1()
{
  int i;
  i = convertToInt();
  if (i==-1)
    return NULL;
  i++;
  IOInfo *newio;
  if (i>=pow(2.0,getLength()))
    return NULL;
  newio = new IOInfoBin(type, i, getLength());
  return newio;
}

IOInfo* IOInfoBin::getMinus1()
{
  int i;
  i = convertToInt();
  if (i==-1)
    return NULL;
  i--;
  IOInfo *newio;
  //if (i<=0)
  if (i<0)
    return NULL;
  newio = new IOInfoBin(type, i, getLength());
  return newio;
}


QStringList IOInfoBin::getRagelConditions()
{
  IOInfoASCII* tmp = new IOInfoASCII(type);
  unsigned char ascii[MAX_CHARARRAY_LENGTH];
  int len;
  QStringList result;
  convertToASCII(ascii, MAX_CHARARRAY_LENGTH, len);
  tmp->setASCII(ascii, len, len*8);
  result = tmp->getRagelConditions();
  delete tmp;
  return result;
}


void IOInfoBin::setAnyInput(bool ai)
{
  IOInfo::setAnyInput(ai);

  if (ai)
  {
    int len = getLength();

    info=QString(len,'x');
  }
}



