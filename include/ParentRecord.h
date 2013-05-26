/**\file ParentRecord.h
   \author Rikard Lundmark
   \brief Header file for the ParentRecord class.
   \ingroup Records
   \ingroup Database
*/
/**\file ParentRecord.cpp
   \author Rikard Lundmark
   \brief Source file for the ParentRecord class.
   \ingroup Records
   \ingroup Database
*/


#include "Record.h"
#include "LevelRecord.h"
#include "Nukleid.h"
#include "ChildAddable.h"
#include "Child.h"


#ifndef STRING
#define STRING //!<Inclusion guard
#include <string>
#endif

#ifndef LIST
#define LIST //!<Inclusion guard
#include <list>
#endif

using namespace std;

#ifndef PARENT_RECORD
#define PARENT_RECORD //!<Inclusion guard.

/**Corresponds to a single ParentRecord in the ENSDF database (including continuation records). 
   \author Rikard Lundmark
   \note Not fully implemented.
   \ingroup Records
   \ingroup Database
 */
class ParentRecord : public Record, public ChildAddable<Child<ParentRecord> >
{
 public:
  ParentRecord(list<string> card //!<The card string(s) corresponding to this record. 
	       );
  //!<Constructor, constructs the object.
  
  double getHalfLife() const;//!< Get the half-life of this parent. \returns The half-life of the parent (in seconds). 
  
 protected:
  double halfLife; //!<The half-life of this ParentRecord.
 private:
  void processCard(); //!<Called by the constructor in order to initialize the private members.
};

#endif
