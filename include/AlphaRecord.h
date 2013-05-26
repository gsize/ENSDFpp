/** \file AlphaRecord.h
    \author Rikard Lundmark
    \brief Header file for the AlphaRecord class.
    \ingroup Database
    \ingroup Records
*/
/** \file AlphaRecord.cpp
    \author Rikard Lundmark
    \brief Source file for the AlphaRecord class.
    \ingroup Database
    \ingroup Records
*/

using namespace std;

#include "Record.h"
#include "LevelRecord.h"
#include "Nukleid.h"
#include "NormalizationRecord.h"
#include "ParentRecord.h"
#include "QValueRecord.h"
#include "ParentRecordChildrenWrapper.h"
#include "QValueRecordChildrenWrapper.h"
#include "LevelRecordChildrenWrapper.h"
#include "NormalizationRecordChildrenWrapper.h"

#ifndef STRING
#define STRING //!<Inclusion guard
#include <string>
#endif

#ifndef LIST
#define LIST //!<Inclusion guard
#include <list>
#endif

#ifndef ALPHA_RECORD
#define ALPHA_RECORD //!<Inclusion guard.

/** Representing a single Alpha record in the ENSDF database (including continuation records).
    \note Currently only a dummy class.
    \author Rikard Lundmark
    \ingroup Database
    \ingroup Records
 */
class AlphaRecord : public Record, public ParentRecordChildrenWrapper, public QValueRecordChildrenWrapper, public LevelRecordChildrenWrapper, public NormalizationRecordChildrenWrapper
{
 public:
  AlphaRecord(
	      list<string> cardArg, //!< The card string(s) corresponding to this record. 
	      NormalizationRecord * myNormalizationRecord, //!< A pointer to the Normalization record corresponding to this record.
	      LevelRecord* level, //!<A pointer to the Level record corresponding to this record.
	      ParentRecord* myParent, //!< A pointer to the Parent record corresponding to this record.
	      QValueRecord* qValRecord//!< A pointer to the Q value record corresponding to this record.
	      );  //!< Constructor, called when the object is constructed by the Dataset.
};

#endif
