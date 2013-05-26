#include "NormalizationRecordChildrenWrapper.h"

const NormalizationRecord * NormalizationRecordChildrenWrapper::getNormalizationRecord() const
{
  return getChildAddable();
}

NormalizationRecordChildrenWrapper::NormalizationRecordChildrenWrapper(NormalizationRecord * toSet)
  :Child<NormalizationRecord>(toSet)
{

}
