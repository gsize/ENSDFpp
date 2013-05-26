#include "InterestingDecayIsomer.h"

InterestingDecayIsomer::InterestingDecayIsomer(Nukleid nukleidToSet, double halfLifeToSet, double energyToSet)
  :InterestingDecay(nukleidToSet)
{
  myHalfLife = halfLifeToSet;
  myEnergy = energyToSet;
}

double InterestingDecayIsomer::getHalfLife() const
{
  return myHalfLife;
}

double InterestingDecayIsomer::getEnergy() const
{
  return myEnergy;
}

string InterestingDecayIsomer::toString() const
{
  stringstream ss;
  //ss << getNukleid().toString() << " Half-life: " << myHalfLife << "s, Energy: " << myEnergy << " keV." << endl;
  ss << getNukleid().getZ() << " " << getNukleid().getA() << " " << getNukleid().getElement();
  return ss.str();
}

bool InterestingDecayIsomer::operator==(const InterestingDecayIsomer &other) const
{
  return (getNukleid()==other.getNukleid() && doubleEquality(myHalfLife,other.myHalfLife) && doubleEquality(myEnergy,other.myEnergy));
}

bool InterestingDecayIsomer::operator<(const InterestingDecayIsomer &other) const
{
  if(getNukleid()!=other.getNukleid())
    return getNukleid()<other.getNukleid();
  if(!doubleEquality(myHalfLife,other.myHalfLife))
    return myHalfLife<other.myHalfLife;
  if(!doubleEquality(myEnergy, other.myEnergy))
    return myEnergy<other.myEnergy;
  return false;
}
