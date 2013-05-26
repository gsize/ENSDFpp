#include "MassObject.h"
#include "Nukleid.h"

MassObject::MassObject()
{
  
}

MassObject::MassObject(string massString)
{
  string elementName = massString.substr(20,3);
  elementName = trimString(elementName);
  while(elementName.size()<2)
    elementName = elementName + " ";
  string elementMass = massString.substr(16,3);
  elementMass = trimString(elementMass);
  while(elementMass.size()<3)
    elementMass = elementMass + " ";

  string nukleidString = elementMass + elementName;

  myNukleid = Nukleid(nukleidString);
  massExcess = stringsToExperimentalValue(massString.substr(29,13),massString.substr(42,10));
  bindingEnergy = stringsToExperimentalValue(massString.substr(54,8),massString.substr(65,7));
  betaDecayEnergy = stringsToExperimentalValue(massString.substr(76,10),massString.substr(88,8));
  string massStr = massString.substr(96,16);
  massStr[3]='.';
  atomicMass = stringsToExperimentalValue(massStr,massString.substr(113,10));					 
}

ExperimentalValue MassObject::stringsToExperimentalValue(string value, string deltaValue)
{
  ExperimentalValue toReturn;
  if(find(value.begin(), value.end(), '*')!=value.end())
    {
      toReturn.isTheoretical=true;
    }
  else
    {
      toReturn.isTheoretical=false;
      if(find(value.begin(), value.end(), '#')!=value.end())
	{
	  toReturn.nonCalculable=true;
	}
      else
	{
	  toReturn.nonCalculable=false;
	}
      remove(value.begin(), value.end(), '#');
      remove(deltaValue.begin(), deltaValue.end(), '#');
      toReturn.value=stringToDouble(value);
      toReturn.deltaValue=stringToDouble(deltaValue);
    }
  return toReturn;
}

double MassObject::stringToDouble(string myString)
{
  return atof(myString.c_str());
}

string MassObject::trimString(string toTrim)
{
  string retur = "";
  for(unsigned int i = 0; i<toTrim.size(); i++)
    if(toTrim[i]!=' ')
      retur = retur + toTrim[i];
  return retur;
}

Nukleid MassObject::getNukleid() const
{
  return myNukleid;
}

ExperimentalValue MassObject::getMassExcess() const
{
  return massExcess;
}

ExperimentalValue MassObject::getBindingEnergy() const
{
  return bindingEnergy;
}

ExperimentalValue MassObject::getBetaDecayEnergy() const
{
  return betaDecayEnergy;
}

ExperimentalValue MassObject::getAtomicMass() const
{
  return atomicMass;
}
