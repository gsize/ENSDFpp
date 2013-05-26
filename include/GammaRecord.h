/**\file GammaRecord.h
   \brief Header file for the GammaRecord class.
   \author Rikard Lundmark
   \ingroup Database
   \ingroup Records
*/
/**\file GammaRecord.cpp
   \brief Source file for the GammaRecord class.
   \author Rikard Lundmark
   \ingroup Database
   \ingroup Records
*/



#include "Record.h"
#include "LevelRecord.h"
#include "NormalizationRecord.h"
#include "Nukleid.h"
#include "QValueRecord.h"
#include "LevelRecordChildrenWrapper.h"
#include "QValueRecordChildrenWrapper.h"
#include "NormalizationRecordChildrenWrapper.h"

#ifndef STRING
#define STRING //!<Inclusion guard
#include <string>
#endif

#ifndef LIST
#define LIST //!<Inclusion guard
#include <list>
#endif

using namespace std;

#ifndef GAMMA_RECORD
#define GAMMA_RECORD //!<Inclusion guard

/**Corresponds to a single Gamma record (including continuation records) in the ENSDF database.
   \author Rikard Lundmark
   \note Not fully implemented.
   \ingroup Records
   \ingroup Database
 */

class GammaRecord : public Record, public LevelRecordChildrenWrapper, public QValueRecordChildrenWrapper, public NormalizationRecordChildrenWrapper
{
public:
  GammaRecord(list<string> cardArg, //!< The card string(s) corresponding to this record. 
	      LevelRecord* level, //!<A pointer to the Level record corresponding to this record. 
	      NormalizationRecord* norm, //!<	A pointer to the Normalization record corresponding to this record. 
	      QValueRecord* qValRecord //!< A pointer to the Q value record corresponding to this record. 
	      ); //!<Constructor, constructs this record.

	double getDecayEnergy() const;		//!<Get the decay energy. \returns The energy emitted by the gamma ray.
	double getTransitionIntensity() const; //!<Get the transition intensity. \returns the transition intensity of this Gamma decay branch.

protected:
	double transitionIntensity; //!< The transition intensity.

	double decayEnergy; //!<The decay energy.
 private:
	void processCard(); //!<	Called by the constructor to process the record. 
};

#endif
