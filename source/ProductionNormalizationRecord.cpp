#include "ProductionNormalizationRecord.h"

ProductionNormalizationRecord::ProductionNormalizationRecord(list<string> cardArg, NormalizationRecord* myNormalization)
  :NormalizationRecordChildrenWrapper(myNormalization), Record(cardArg)
{

}

