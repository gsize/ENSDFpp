/**\file LevelRecordChildrenWrapper.h
   \author Rikard Lundmark
   \brief Header file for the LevelRecordChildrenWrapper class.
   \ingroup Database
   \ingroup RecordWrappers
*/
/**\file LevelRecordChildrenWrapper.cpp
   \author Rikard Lundmark
   \brief Source file for the LevelRecordChildrenWrapper class.
   \ingroup Database
   \ingroup RecordWrappers
*/


using namespace std;

#ifndef NULL //!<Inclusion guard.
#define NULL 0
#endif

#include "Child.h"
#include "LevelRecord.h"

#ifndef LEVELRECORDCHILDRENWRAPPER_H
#define LEVELRECORDCHILDRENWRAPPER_H //!<Inclusion guard.

/**Extended by all classes that contains pointers to a LevelRecord.
   \author Rikard Lundmark
   \ingroup Database
   \ingroup RecordWrappers
 */
class LevelRecordChildrenWrapper: public Child<LevelRecord>
{
 public:
  virtual const LevelRecord * getLevelRecord() const; //!<Get the LevelRecord \return The associated LevelRecord.
  LevelRecordChildrenWrapper(LevelRecord * toSet //!<The LevelRecord to set.
			     ); //!<Constructor, associates the object with the LevelRecord by telling the LevelRecord in question that it has a child.
};
#endif
