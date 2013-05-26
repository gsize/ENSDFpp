#include "ParentRecordChildrenWrapper.h"

const ParentRecord * ParentRecordChildrenWrapper::getParentRecord() const
{
  return getChildAddable();
}

ParentRecordChildrenWrapper::ParentRecordChildrenWrapper(ParentRecord * toSet)
  :Child<ParentRecord>(toSet)
{
  
}
