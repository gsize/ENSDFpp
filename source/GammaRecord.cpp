#include "GammaRecord.h"

GammaRecord::GammaRecord(list<string> cardArg, LevelRecord *level, NormalizationRecord* norm, QValueRecord* qValArg)
  :Record(cardArg), LevelRecordChildrenWrapper(level), QValueRecordChildrenWrapper(qValArg), NormalizationRecordChildrenWrapper(norm)
{
  processCard();
}

void GammaRecord::processCard()
{
  decayEnergy = cardToDouble(10, 19);
  transitionIntensity = cardToDouble(22, 29);  
}

double GammaRecord::getDecayEnergy() const
{
  return decayEnergy;
}

double GammaRecord::getTransitionIntensity() const
{
  return transitionIntensity;
}
