/**\file QValueRecord.h
   \author Rikard Lundmark
   \brief Header file for the QValueRecord class.
   \ingroup Records
   \ingroup Database
*/
/**\file QValueRecord.cpp
   \author Rikard Lundmark
   \brief Source file for the QValueRecord class.
   \ingroup Records
   \ingroup Database
*/
#include "Record.h"
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

#ifndef QVALUE_RECORD
#define QVALUE_RECORD //!<Inclusion guard.
/** Corresponds to a single QValueRecord in the ENSDF database (including continuation records).
    \author Rikard Lundmark
    \note Not fully implemented.
    \ingroup Records
    \ingroup Database
 */
class QValueRecord : public Record, public ChildAddable<Child<QValueRecord> >
{
public:
  QValueRecord(list<string> cardArg //!<The card string(s) corresponding to this record. 
	       );//!<Constructor.

  bool operator== (const QValueRecord &other //!<The object to compare.
		   ) const; //!< Comparision operator.

  double getQValue() const; //!<Get the Q value. \returns The Q value.

 protected:
  double QValue; //!<Contains the energy in keV alvailible for beta decay of the ground state.
 private:
  void processCard();//!<Called by the constructor to initialize the protected members.
};

#endif
