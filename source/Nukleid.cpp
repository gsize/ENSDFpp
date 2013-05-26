#include "Nukleid.h"
using namespace std;

Nukleid::Nukleid() 
{
  name="UNKNOWN";
  element="UNKNOWN";
  A=0;
  Z=0;
}

Nukleid::Nukleid(string nucleid)
{
  name=trimString(nucleid);
  parseNukleidName(nucleid, A, element);
  Z=parseAtomicNumber(element);
}

string Nukleid::trimString(string toTrim)
{
  string results = "";
  for(unsigned int i = 0; i<toTrim.size(); i++)
    if(!(toTrim[i]==' ' || toTrim[i]=='\n' || toTrim[i]=='\t'))
      results+=toTrim[i];
  return results;
}

unsigned short int Nukleid::parseAtomicNumber(string elementToParse)
{
  ElementLookupTable myTable;
  return myTable.lookupElement(elementToParse);
}

string Nukleid::toString() const
{
  if(element.size()>10)
    return "STRINGERROR";
  stringstream ss;
  ss << A << element;
  return ss.str();
}

string Nukleid::getElement() const
{
  return element;
}

int Nukleid::getZ() const
{
	return Z;
}

int Nukleid::getA() const
{
	return A;
}

// returns 0 as mass and "" as element if the input is invalid
void Nukleid::parseNukleidName(string nucleid, short unsigned int &mass, string &element)
{
  
  ////////////////// Check if the input is valid ///////////////////
  if (nucleid.length() != 5 && nucleid.length()!=6)
    {
      throw DataFileException("Nucleid string was of wrong length.");
      return;
    }
  
  for (int i = 0; i < 3; i++)
    {
      if (!((nucleid.at(i) >= '0' && nucleid.at(i) <= '9') || nucleid.at(i) == ' '))
	{
	  throw DataFileException("Nucleid number was invalid: '''" + nucleid + "'''");
	  return;
	}
    }
  
  for (unsigned int i = 3; i < nucleid.length(); i++)
    {
      if(nucleid.at(i)>='a' && nucleid.at(i)<='z')
	{
	  nucleid[i]+='A'-'a';
	}
      if (!((nucleid.at(i) >= 'A' && nucleid.at(i) <= 'Z') || (nucleid.at(i) == ' ') || (nucleid.at(i) >= '0' && nucleid.at(i) <= '9')))
	{
	  throw DataFileException("Nucleid name was invalid: '''" + nucleid + "'''");
	  return;
	    }
    }
  //////////////////////////////////////////////////////////////////
  
  string number = nucleid.substr(0, 3);
  const char* numberCString = number.c_str();
  mass = atoi(numberCString);
  
  if (nucleid.at(4) == ' ')
    element = nucleid.at(3);
  else
    if(nucleid.length()==5)
      element = nucleid.substr(3,2);
    else
      if(nucleid[5]!=' ')
	element = nucleid.substr(3,3);
      else
	element = nucleid.substr(3,2);
}

bool Nukleid::operator == (const Nukleid & rhs) const
{
  if (Z == rhs.Z && A == rhs.A && element.compare(rhs.element)==0)
    return true;
  return false;
}

bool Nukleid::operator > (const Nukleid & rhs) const
{
  if (Z > rhs.Z)
    return true;
  else if (Z == rhs.Z)
    {
      if(name.compare(rhs.name)==0)
	return false;
      return name.compare(rhs.name)>0;
    }
  return false;
}

bool Nukleid::operator < (const Nukleid & rhs) const
{
  if (Z > rhs.Z)
    {
      return false;
    }
  else if (Z == rhs.Z)
    {
      if(name.compare(rhs.name)==0)
	{
	  return false;
	}
      return !(name.compare(rhs.name)>0);
    }
  return true;
}
