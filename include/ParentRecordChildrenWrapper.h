/**\file ParentRecordChildrenWrapper.h
   \author Rikard Lundmark
   \brief Header file for the ParentRecordChildrenWrapper class.
   \ingroup RecordWrappers
   \ingroup Database
 */
/**\file ParentRecordChildrenWrapper.cpp
   \author Rikard Lundmark
   \brief Source file for the ParentRecordChildrenWrapper class.
   \ingroup RecordWrappers
   \ingroup Database
*/

using namespace std;
#ifndef NULL
#define NULL 0 //!<Inclusion guard.
#endif

#include "Child.h"
#include "ParentRecord.h"

#ifndef PARENTRECORDCHILDRENWRAPPER_H
#define PARENTRECORDCHILDRENWRAPPER_H //!<Inclusion guard.


/**Extended by all classes that contains pointers to a ParentRecord.
   \author Rikard Lundmark
   \ingroup RecordWrappers
   \ingroup Database
*/
class ParentRecordChildrenWrapper: public Child<ParentRecord>
{
 public:
  virtual const ParentRecord * getParentRecord() const;//!<Get the ParentRecord \return The associated ParentRecord.

  ParentRecordChildrenWrapper(ParentRecord * toSet //!<The ParentRecord to set.
			      ); //!<Constructor, associates the object with the ParentRecord by telling the ParentRecord in question that it has a child.
};
#endif
