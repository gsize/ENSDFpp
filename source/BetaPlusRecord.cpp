#include "BetaPlusRecord.h"

BetaPlusRecord::BetaPlusRecord(list<string> cardArg, NormalizationRecord* norm, LevelRecord* lev, ParentRecord* par, QValueRecord* qValArg)
  :BetaRecordWrapper(cardArg, lev, par, qValArg, norm)
{
  processCard();
}

void BetaPlusRecord::processCard()
{
  endPointEnergy = cardToDouble(10,19);
  intensityOfBetaPlusDecayBranch = cardToDouble(22, 29);
  intensityOfElectronCaptureBranch = cardToDouble(32,39);
  
  if (getNormalizationRecord() != NULL)
    {
      intensityOfBetaPlusDecayBranch *= getNormalizationRecord()->getBetaMultiplier();
    }
}

double BetaPlusRecord::getIntensityOfElectronCaptureBranch() const
{
  return intensityOfElectronCaptureBranch;
}

double BetaPlusRecord::getIntensityOfBetaDecayBranch() const
{
	return intensityOfBetaPlusDecayBranch;
}

double BetaPlusRecord::getEndPointEnergy() const
{
  return endPointEnergy;
}

