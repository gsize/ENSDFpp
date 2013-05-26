#include "LevelRecord.h"
LevelRecord::LevelRecord(list<string> cardArg, QValueRecord* qValArg)
  :Record(cardArg), QValueRecordChildrenWrapper(qValArg)
{
  processCard();
}

void LevelRecord::processCard()
{
  energy = cardToDouble(10, 19);
  halfLife = parseHalfLife(40, 49);
}

double LevelRecord::getEnergy() const
{
  return energy;
}

double LevelRecord::getHalfLife() const
{
  return halfLife;
}


bool LevelRecord::operator == (const LevelRecord & rhs) const
{
  const ChildAddable<Child<LevelRecord> > * temp1 = this;
  const ChildAddable<Child<LevelRecord> > * temp2 = &rhs;
  double other = (*temp1==*temp2);
  return (doubleEquality(energy,rhs.energy,1))&&(doubleEquality(halfLife,rhs.halfLife)&&(getNukleid()==rhs.getNukleid())&& other);
}
