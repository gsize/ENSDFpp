#include "Record.h"
#include <iostream>

Record::Record(list<string> cardArg) 
{
  if(!cardArg.empty())
    {
      myCard = cardArg;
      myNukleid = Nukleid(myCard.front().substr(0,5));
    }
}

Record::~Record() 
{
  //nothing to do here...
}

Nukleid Record::getNukleid() const
{
  return myNukleid;
}

list<string> Record::getCardStrings() const
{
  return myCard;
}

double Record::cardToDouble(int startPos, int endPos)
{
  if(!myCard.empty())
    {
      string data = myCard.front().substr(startPos-1, endPos-startPos+1);
      const char* dataCString = data.c_str();
      double number = atof(dataCString);
      return number;
    }
  else
    {
      throw DataFileException("Empty card string.\n");
    }
}

string Record::trimString(string toTrim)
{
  int ptrStart = -1;
  int ptrStop = toTrim.size();
  while(toTrim[++ptrStart]==' ');
  while(toTrim[--ptrStop]==' ');
  return toTrim.substr(ptrStart,ptrStop-ptrStart+1);
}

// returns -1 if the nucleid is stable and 0 if no half life is given
double Record::parseHalfLife(int startPos, int endPos)
{
  string tempStr = myCard.front().substr(startPos-1, endPos-startPos+1);
  string halfLifeStr = trimString(tempStr);


  if (halfLifeStr.substr(0,5).compare("STABLE") == 0)			// the strings are equal
    return -1;
  unsigned int i = 0;
  for (i = 0; i < halfLifeStr.length(); i++)
    {
      if (!((halfLifeStr.at(i) <= '9' && halfLifeStr.at(i) >= '0') || halfLifeStr.at(i) == '.'))
	break;
    }
  if(halfLifeStr.size()<i+2)
    return -3;
  string numberStr = halfLifeStr.substr(0, i);
  const char* numberCString = numberStr.c_str();
  double number = atof(numberCString);
  if(halfLifeStr.size()>i+2)
    {
      string unit = halfLifeStr.substr(i+1, 2);
      if (unit.compare("Y ") == 0)
	number *= 365*24*60*60;
      else if (unit.compare("D ") == 0)
	number *= 60*60*24;
      else if (unit.compare("H ") == 0)
	number *= 60*60;
      else if (unit.compare("M ") == 0)
	number *= 60;
      else if (unit.compare("S ") == 0)
	number *= 1;
      else if (unit.compare("MS") == 0)
	number *= 1E-3;
      else if (unit.compare("US") == 0)
	number *= 1E-6;
      else if (unit.compare("NS") == 0)
	number *= 1E-9;
      else if (unit.compare("PS") == 0)
	number *= 1E-12;
      else if (unit.compare("FS") == 0)
	number *= 1E-15;
      else if (unit.compare("AS") == 0)
	number *= 1E-18;
      else
	return -2;
    }
  else if(halfLifeStr.size()>i+1)
    {
      string unit = halfLifeStr.substr(i+1, 1);
      if (unit.compare("Y") == 0)
	number *= 365*24*60*60;
      else if (unit.compare("D") == 0)
	number *= 60*60*24;
      else if (unit.compare("H") == 0)
	number *= 60*60;
      else if (unit.compare("M") == 0)
	number *= 60;
      else if (unit.compare("S") == 0)
	number *= 1;
      else
	return -5;
    }
  else
    {
      number = - 1339;
    }
  /**\todo Fix the times given in units of time.*/
  return number;
}
