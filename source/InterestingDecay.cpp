#include "InterestingDecay.h"

InterestingDecay::InterestingDecay(Nukleid toSet)
{
  myNukleid = toSet;
}

Nukleid InterestingDecay::getNukleid() const
{
  return myNukleid;
}

bool InterestingDecay::operator==(const InterestingDecay &other) const
{
  return myNukleid==other.myNukleid;
}

bool InterestingDecay::operator<(const InterestingDecay &other) const
{
  return myNukleid<other.myNukleid;
}

string InterestingDecay::toString() const
{
  return myNukleid.toString();
}
