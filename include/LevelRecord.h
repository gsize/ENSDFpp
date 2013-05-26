/**\file LevelRecord.h
   \author Rikard Lundmark
   \brief Header file for the LevelRecord class.
   \ingroup Records
   \ingroup Database
*/
/**\file LevelRecord.cpp
   \author Rikard Lundmark
   \brief Source file for the LevelRecord class.
   \ingroup Records
   \ingroup Database
*/


#include "Record.h"
#include "Nukleid.h"
#include "QValueRecord.h"
#include "QValueRecordChildrenWrapper.h"
#include "DoubleMath.h"
#include "Child.h"
#include "ChildAddable.h"


#ifndef STRING
#define STRING //!<Inclusion guard
#include <string>
#endif

#ifndef LIST
#define LIST //!<Inclusion guard
#include <list>
#endif

using namespace std;

#ifndef LEVELRECORD_H
#define LEVELRECORD_H //!<Inclusion guard.

class LevelRecordChildrenWrapper; 

/** Corresponds to a single Level record in the ENSDF database (includeing continuation records).
    \author Rikard Lundmark
    \note Not fully implemented.
    \ingroup Records
    \ingroup Database
 */
class LevelRecord : public Record, public ChildAddable<Child<LevelRecord> >, public QValueRecordChildrenWrapper
{
public:
  LevelRecord(list<string> cardArg, //!<	The card string(s) corresponding to this record. 
	      QValueRecord* qValRecord  //!<	A pointer to the Q value record corresponding to this record. 
	      ); //!<Constructor.
  
  double getEnergy() const;	//!<Gets the energy of the level. \return The energy of the energy level (in keV).
  double getHalfLife() const;	//!<Gets the half life of the level. \returns The half life of the level (in s), -1 if the level is stable and 0 if no information is given in ENSDF.
  
  bool operator== (const LevelRecord &other //!<The LevelRecord to compare with.
		   ) const; //!<Equality comparision operator.
  
 protected:
  double energy; //!<The energy of this level (in keV).
  double halfLife; //!<The halfLife of this level (in s).
 private:
  void processCard(); //!<Called by the constructor in order to initialize the protected members.
};

#endif
