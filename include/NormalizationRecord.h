/**\file NormalizationRecord.h
   \author Rikard Lundmark
   \brief Header file for the NormalizationRecord class.
   \ingroup Records
   \ingroup Database
*/
/**\file NormalizationRecord.cpp
   \author Rikard Lundmark
   \brief Source file for the NormalizationRecord class.
   \ingroup Records
   \ingroup Database
*/

#include "Record.h"
#include "ParentRecord.h"
#include "Nukleid.h"
#include "ParentRecordChildrenWrapper.h"

#ifndef STRING
#define STRING //!<Inclusion guard
#include <string>
#endif

#ifndef LIST
#define LIST //!<Inclusion guard
#include <list>
#endif

using namespace std;

#ifndef NORMALIZATION_RECORD
#define NORMALIZATION_RECORD //!<Inclusion guard.
/**Represents a single Normalization record (includeing continuation records) in the ENSDF database.
   \author Rikard Lundmark
   \note Not fully implemented.
   \ingroup Records
   \ingroup Database
 */
class NormalizationRecord : public Record, public ChildAddable<Child<NormalizationRecord> >, public ParentRecordChildrenWrapper
{
public:

  NormalizationRecord(list<string> cardArg, //!<The card string(s) corresponding to this record. 
		      ParentRecord *parent //!<	A pointer to the Parent record corresponding to this record. 
		      );//!<Constructor, constructs the object. 

	double getNT() const; //!<Get the NT information. \return The NT information in the normalization record.
	double getNR() const; //!< Get the NR information. \return the NR information in the normalization record.
	double getBetaMultiplier() const; //!< Get the beta multiplier. \return the beta multiplier information in the normalization record.

protected:
	double NT; //!<The NT information in the NormalizationRecord.
	double NR; //!<The NR information in the NormalizationRecord.
	double betaMultiplier; //!<The Beta multiplier in the Normalization record.
 private:
	void processCard(); //!<Called by the constructor to initialize the protected members.
};

#endif
