/** \file BetaPlusRecord.h
    \author Rikard Lundmark
    \brief Header file for the BetaPlusRecord class.
    \ingroup Database
    \ingroup Records
*/
/** \file BetaPlusRecord.cpp
    \author Rikard Lundmark
    \brief Source file for the BetaPlusRecord class.
    \ingroup Database
    \ingroup Records
*/

#include "Record.h"
#include "NormalizationRecord.h"
#include "ParentRecord.h"
#include "LevelRecord.h"
#include "Nukleid.h"
#include "QValueRecord.h"
#include "BetaRecordWrapper.h"
#include "LevelRecordChildrenWrapper.h"
#include "QValueRecordChildrenWrapper.h"
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

#ifndef BETAPLUS_RECORD_H
#define BETAPLUS_RECORD_H //!<Inclusion guard.

/** Corresponds to a Beta plus record in the ENSDF database, this may include electron capture.
    \author Rikard Lundmark
    \ingroup Database
    \ingroup Records
*/
class BetaPlusRecord : public BetaRecordWrapper
{
 public:
  BetaPlusRecord(
		 list<string> cardArg, //!< The card string(s) corresponding to this record. 
		 NormalizationRecord* norm, //!< A pointer to the Normalization record corresponding to this record. 
		 LevelRecord* lev, //!< A pointer to the Level record corresponding to this record. 
		 ParentRecord* parent, //!< A pointer to the Parent record corresponding to this record. 
		 QValueRecord* qValRecord //!< A pointer to the Q value record corresponding to this record. 
		 );
  //!<Constructor.
  
  double getEndPointEnergy() const; //!< Returns the endpoint energy of this beta plus decay.
  double getIntensityOfBetaDecayBranch() const;	//!< Returns the intensity of the beta decay branch.		
  double getIntensityOfElectronCaptureBranch() const; //!<Returns the intensity of the electron capture branch.
  
 protected:
  double intensityOfBetaPlusDecayBranch; //!<The intensity of the beta plus decay branch.
  double intensityOfElectronCaptureBranch; //!<The intensity of the electron capture branch.

  double endPointEnergy; //!< The endpoint energy.
  
 private:
  void processCard(); //!<Called by the constructor to process the record.
};

#endif
