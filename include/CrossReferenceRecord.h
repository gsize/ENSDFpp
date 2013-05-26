/**\file CrossReferenceRecord.h
   \author Rikard Lundmark
   \brief Header file for the CrossReferenceRecord class.
   \ingroup Database
   \ingroup Records
*/
/**\file CrossReferenceRecord.cpp
   \author Rikard Lundmark
   \brief Source file for the CrossReferenceRecord class.
   \ingroup Database
   \ingroup Records
*/

using namespace std;
#include "Record.h"

#ifndef STRING
#define STRING //!<Inclusion guard
#include <string>
#endif

#ifndef LIST
#define LIST //!<Inclusion guard
#include <list>
#endif

#ifndef CROSS_REFERENCE_RECORD
#define CROSS_REFERENCE_RECORD //!<Inclusion guard.

/**Represents a single CrossReferenceRecord in the ENSDF database (including continuation records).

Currently only a dummy class.

\author Rikard Lundmark
\ingroup Database
\ingroup Records


 */
class CrossReferenceRecord : public Record
{
 public:
  CrossReferenceRecord(list<string> cardArg //!< The card string(s) corresponding to this record. 
		       );
  //!< Constructor.
};

#endif
