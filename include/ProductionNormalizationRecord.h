/**\file ProductionNormalizationRecord.h
   \author Rikard Lundmark
   \brief Header file for the ProductionNormalizationRecord class.
   \ingroup Records
   \ingroup Database
*/
/**\file ProductionNormalizationRecord.cpp
   \author Rikard Lundmark
   \brief Source file for the ProductionNormalizationRecord class.
   \ingroup Records
   \ingroup Database
*/

#include "Record.h"
#include "NormalizationRecord.h"
#include "NormalizationRecordChildrenWrapper.h"

#ifndef STRING
#define STRING //!<Inclusion guard
#include <string>
#endif

#ifndef LIST
#define LIST //!<Inclusion guard
#include <list>
#endif

using namespace std;

#ifndef PRODUCTION_NORMALIZATION_RECORD
#define PRODUCTION_NORMALIZATION_RECORD //!<Inclusion guard.

/**Representing a single Alpha record in the ENSDF database (including continuation records). 
   \author Rikard Lundmark
   \note Currently only a dummy class.
   \ingroup Records
   \ingroup Database
 */
class ProductionNormalizationRecord : public NormalizationRecordChildrenWrapper, public Record
{
public:

  ProductionNormalizationRecord(list<string> cardArg, //!<The card string(s) corresponding to this record. 
				NormalizationRecord* myNormalizationRecord //!<A pointer to the Normalization record corresponding to this record.
				);
  //!<Constructor, constructs the object.

};

#endif
