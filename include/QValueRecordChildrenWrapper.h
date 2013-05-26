/**\file QValueRecordChildrenWrapper.h
   \author Rikard Lundmark
   \brief Header file for the QValueRecordChildrenWrapper class.
   \ingroup Database
   \ingroup RecordWrappers
*/
/**\file QValueRecordChildrenWrapper.cpp
   \author Rikard Lundmark
   \brief Source file for the QValueRecordChildrenWrapper class.
   \ingroup Database
   \ingroup RecordWrappers
*/

using namespace std;

#ifndef NULL
#define NULL 0 //!<Inclusion guard.
#endif

#include "Child.h"
#include "QValueRecord.h"

#ifndef QVALUERECORDCHILDRENWRAPPER_H
#define QVALUERECORDCHILDRENWRAPPER_H //!<Inclusion guard.

class QValueRecord;

/**Extended by all classes that contain pointers to a QValueRecord.
   \author Rikard Lundmark
   \ingroup Database
 */
class QValueRecordChildrenWrapper: public Child<QValueRecord>
{
 public:
  virtual const QValueRecord * getQValueRecord() const; //!<Get the QValueRecord \return The associated QValueRecord.
  QValueRecordChildrenWrapper(QValueRecord * toSet); //!<Constructor, associates the object with the QValueRecord by telling the QValueRecord in question that it has a child.
};
#endif
