#include "ParentRecord.h"

ParentRecord::ParentRecord(list<string> cardArg)
  :Record(cardArg)
{
  processCard();
}

void ParentRecord::processCard()
{
  halfLife = parseHalfLife(40, 49);
}

double ParentRecord::getHalfLife() const
{
  return halfLife;
}
