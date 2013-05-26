#include "AlphaRecord.h"

AlphaRecord::AlphaRecord(list<string> cardArg, NormalizationRecord* myNormalization, LevelRecord* levelArg, ParentRecord * myParent, QValueRecord* qValArg)
  :Record(cardArg), ParentRecordChildrenWrapper(myParent), QValueRecordChildrenWrapper(qValArg), LevelRecordChildrenWrapper(levelArg), NormalizationRecordChildrenWrapper(myNormalization)
{
  //No handling of this record implemented, this is a dummy object.

}
