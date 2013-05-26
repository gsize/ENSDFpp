/**\file HistoryRecord.h
   \author Rikard Lundmark
   \brief Header file for the HistoryRecord class.
   \ingroup Records
   \ingroup Database
*/
/**\file HistoryRecord.cpp
   \author Rikard Lundmark
   \brief Source file for the HistoryRecord class.
   \ingroup Records
   \ingroup Database
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

#ifndef HISTORY_RECORD
#define HISTORY_RECORD //!<Inclusion guard

/**Representing a single History record in the ENSDF database (including continuation records). 
   \author Rikard Lundmark
   \note Not fully implemented.
   \ingroup Records
   \ingroup Database
 */
class HistoryRecord : public Record
{
 public:
  HistoryRecord(list<string> cardArg //!<	The card string(s) corresponding to this record. 
		); //!<Creates the object.
};

#endif
