#include "DelayedParticleRecord.h"

using namespace std;

DelayedParticleRecord::DelayedParticleRecord(list<string> cardArg, NormalizationRecord* myNormalizationRecord, LevelRecord* levelArg, ParentRecord * myParent, QValueRecord* qValArg)
  :Record(cardArg), LevelRecordChildrenWrapper(levelArg), ParentRecordChildrenWrapper(myParent), QValueRecordChildrenWrapper(qValArg)
{

}
