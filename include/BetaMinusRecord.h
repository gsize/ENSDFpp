/** \file BetaMinusRecord.h
    \author Rikard Lundmark
    \brief Header file for the BetaMinusRecord class.
    \ingroup Database
    \ingroup Records
*/
/** \file BetaMinusRecord.cpp
    \author Rikard Lundmark
    \brief Source file for the BetaMinusRecord class.
    \ingroup Database
    \ingroup Records
*/

#include "Record.h"
#include "LevelRecord.h"
#include "NormalizationRecord.h"
#include "ParentRecord.h"
#include "Nukleid.h"
#include "QValueRecord.h"
#include "BetaRecordWrapper.h"
#include "QValueRecordChildrenWrapper.h"
#include "ParentRecordChildrenWrapper.h"
#include "LevelRecordChildrenWrapper.h"


#ifndef STRING
#define STRING //!<Inclusion guard
#include <string>
#endif

#ifndef LIST
#define LIST //!<Inclusion guard
#include <list>
#endif

using namespace std;

#ifndef BETAMINUS_RECORD
#define BETAMINUS_RECORD //!<Inclusion guard.

/** Corresponds to a Beta minus record in the ENSDF database.
    \author Rikard Lundmark
    \ingroup Database
    \ingroup Records
 */
class BetaMinusRecord : public BetaRecordWrapper
{
 public:

  BetaMinusRecord(list<string> cardArg, //!<The card string(s) corresponding to this record.
		  NormalizationRecord* norm, //!<A pointer to the Normalization record corresponding to this record.
		  LevelRecord* lev, //!< A pointer to the Level record corresponding to this record.
		  ParentRecord* parent, //!< A pointer to the Parent record corresponding to this record.
		  QValueRecord* qValRecord //!< A pointer to the Q value record corresponding to this record.
		  );
  //!<Constructor, constructs the object.
  
  
  double getEndPointEnergy() const; //!< Returns the endpoint energy.
  double getIntensityOfBetaDecayBranch() const; //!< Returns the intensity of this beta decay branch.
  
 protected:
  double endPointEnergy; //!< The endpoint energy.
  double intensityOfBetaMinusDecayBranch; //!< The intensity of the beta decay branch.

 private:
  void processCard(); //!< Processes the cardArg string and retrieves information from it. Called by the constructor.
};

#endif
