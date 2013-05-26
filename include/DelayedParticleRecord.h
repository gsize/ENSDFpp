/**\file DelayedParticleRecord.h
   \author Rikard Lundmark
   \brief Header file for the DelayedParticleRecord class.
   \ingroup Database
   \ingroup Records
*/
/**\file DelayedParticleRecord.cpp
   \author Rikard Lundmark
   \brief Source file for the DelayedParticleRecord class.
   \ingroup Database
   \ingroup Records
*/

#include "Record.h"
#include "LevelRecord.h"
#include "NormalizationRecord.h"
#include "ParentRecord.h"
#include "QValueRecord.h"
#include "LevelRecordChildrenWrapper.h"
#include "ParentRecordChildrenWrapper.h"
#include "QValueRecordChildrenWrapper.h"

#ifndef STRING
#define STRING //!<Inclusion guard
#include <string>
#endif

#ifndef LIST
#define LIST //!<Inclusion guard
#include <list>
#endif

using namespace std;

#ifndef DELAYED_PARTICLE_RECORD
#define DELAYED_PARTICLE_RECORD //!<Inclusion guard.

/**Corresponds to a single Delayed particle record in the ENSDF database (including continuation records). 
   \note Currently only a dummy class.
   \author Rikard Lundmark
   \ingroup Database
   \ingroup Records
 */

class DelayedParticleRecord : public Record, public LevelRecordChildrenWrapper, public ParentRecordChildrenWrapper, public QValueRecordChildrenWrapper
{
public:
  DelayedParticleRecord(list<string> cardArg, //!<The card string(s) corresponding to this record. 
			NormalizationRecord * myNormalizationRecord, //!<A pointer to the Normalization record corresponding to this record. 
			LevelRecord* level, //!<A lpointer to the Level record corresponding to this record.
			ParentRecord * myParentRecord, //!< A pointer to the Parent record corresponding to this record. 
			QValueRecord* qValRecord //!<A pointer to the Q value record corresponding to this record. 
			); //!< Constructor, called when the object is constructed by the Dataset class.
};

#endif
