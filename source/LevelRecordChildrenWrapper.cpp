#include "LevelRecordChildrenWrapper.h"

const LevelRecord * LevelRecordChildrenWrapper::getLevelRecord() const
{
  return getChildAddable();
}

LevelRecordChildrenWrapper::LevelRecordChildrenWrapper(LevelRecord * toSet)
  :Child<LevelRecord>(toSet)
{

}
