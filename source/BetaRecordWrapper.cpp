#include "BetaRecordWrapper.h"

BetaRecordWrapper::BetaRecordWrapper(list<string> cardArg, LevelRecord * myLevel, ParentRecord * myParent, QValueRecord * myQValue, NormalizationRecord * norm) 
  :LevelRecordChildrenWrapper(myLevel), 
   ParentRecordChildrenWrapper(myParent), 
   QValueRecordChildrenWrapper(myQValue), 
   NormalizationRecordChildrenWrapper(norm), 
   Record(cardArg)
{
  //nothing to do here yet...
}
