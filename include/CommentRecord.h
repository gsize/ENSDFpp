/**\file CommentRecord.h
   \brief Header file for the CommentRecord class.
   \author Rikard Lundmark
   \ingroup Records
   \ingroup Database
*/
/**\file CommentRecord.cpp
   \brief Source file for the CommentRecord class.
   \author Rikard Lundmark
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

#ifndef COMMENT_RECORD
#define COMMENT_RECORD //!<Inclusion guard.

/**Corresponds to a single CommentRecord in the ENSDF database (including continuation records). 

   \author Rikard Lundmark
   \ingroup Records
   \ingroup Database
 */
class CommentRecord : public Record
{
 public:
  CommentRecord(list<string> cardArg //!<The card string(s) corresponding to this record. 
		); //!<Constructor.
  
};

#endif
