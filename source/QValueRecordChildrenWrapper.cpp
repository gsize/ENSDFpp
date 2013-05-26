#include "QValueRecordChildrenWrapper.h"

const QValueRecord * QValueRecordChildrenWrapper::getQValueRecord() const
{
  return getChildAddable();
}

QValueRecordChildrenWrapper::QValueRecordChildrenWrapper(QValueRecord * toSet)
  :Child<QValueRecord>(toSet)
{

}
