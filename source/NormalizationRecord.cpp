#include "NormalizationRecord.h"

NormalizationRecord::NormalizationRecord(list<string> cardArg, ParentRecord* parentArg)
  :Record(cardArg), ParentRecordChildrenWrapper(parentArg)
{
  processCard();
}

double NormalizationRecord::getBetaMultiplier() const
{
  return betaMultiplier;
}

void NormalizationRecord::processCard()
{
  betaMultiplier = cardToDouble(42, 49);
  NT = cardToDouble(22, 29);
  NR = cardToDouble(10,19);
}

double NormalizationRecord::getNT() const
{
  return NT;
}

double NormalizationRecord::getNR() const
{
  return NR;
}
