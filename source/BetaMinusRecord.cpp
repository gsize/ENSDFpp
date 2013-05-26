#include "BetaMinusRecord.h"

BetaMinusRecord::BetaMinusRecord(list<string> cardArg, NormalizationRecord* norm, LevelRecord* lev, ParentRecord* par, QValueRecord* qValArg)
  :BetaRecordWrapper(cardArg, lev, par, qValArg, norm)
{
  processCard();
}

double BetaMinusRecord::getEndPointEnergy() const
{
  return endPointEnergy;
}

double BetaMinusRecord::getIntensityOfBetaDecayBranch() const
{
  return intensityOfBetaMinusDecayBranch;
}

void BetaMinusRecord::processCard()
{
  endPointEnergy = cardToDouble(10, 19);
  intensityOfBetaMinusDecayBranch = cardToDouble(22, 29);
  if (getNormalizationRecord() != NULL)
    {
      intensityOfBetaMinusDecayBranch *= getNormalizationRecord()->getBetaMultiplier();
    }
}
