/**\file NormalizationRecordChildrenWrapper.h
   \author Rikard Lundmark
   \brief Header file for the NormalizationRecordChildrenWrapper class.
   \ingroup RecordWrappers
   \ingroup Database
*/
/**\file NormalizationRecordChildrenWrapper.cpp
   \author Rikard Lundmark
   \brief Source file for the NormalizationRecordChildrenWrapper class.
   \ingroup RecordWrappers
   \ingroup Database
*/


using namespace std;

#ifndef NULL
#define NULL 0 //!<Inclusion guard.
#endif

#include "Child.h"
#include "NormalizationRecord.h"

#ifndef NORMALIZATIONRECORDCHILDRENWRAPPER_H
#define NORMALIZATIONRECORDCHILDRENWRAPPER_H //!<Inclusion guard.
/**Extended by all classes that contains pointers to a NormalizationRecord.
   \author Rikard Lundmark
   \ingroup RecordWrappers
   \ingroup Database
 */
class NormalizationRecordChildrenWrapper: public Child<NormalizationRecord>
{
 public:
  virtual const NormalizationRecord * getNormalizationRecord() const; //!<Get the NormalizationRecord \return The associated NormalizationRecord
  NormalizationRecordChildrenWrapper(NormalizationRecord * toSet //!<The NormalizationRecord to set.
				     ); //!<Constructor, associates the object with the NormalizationRecord by telling the NormalizationRecord in question that it has a child.
};

#endif
