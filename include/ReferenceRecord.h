/**\file ReferenceRecord.h
   \author Rikard Lundmark
   \brief Header file for the ReferenceRecord class.
   \ingroup Records
   \ingroup Database
*/
/**\file ReferenceRecord.cpp
   \author Rikard Lundmark
   \brief Source file for the ReferenceRecord class.
   \ingroup Records
   \ingroup Database
*/
#include "Record.h"

#ifndef STRING
#define STRING //!<Inclusion guard
#include <string>
#endif

#ifndef LIST
#define LIST //!<Inclusion guard
#include <list>
#endif

using namespace std;

#ifndef REFERENCE_RECORD
#define REFERENCE_RECORD
/**Corresponds to a single ReferenceRecord in the ENSDF database (including continuation records). 
   \author Rikard Lundmark
   \note Currently only a dummy class.
   \ingroup Database
   \ingroup Records
 */
class ReferenceRecord : public Record
{
public:

  ReferenceRecord(list<string> cardArg //!<The card string(s) corresponding to this record. 
		  );//!<Constructor.
};

#endif
