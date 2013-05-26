/**\file BetaRecordWrapper.h
   \author Rikard Lundmark
   \brief Header file for the BetaRecordWrapper class.
   \ingroup Database
   \ingroup RecordWrappers
*/
/** \file BetaRecordWrapper.cpp
    \author Rikard Lundmark
    \brief Source file for the BetaRecordWrapper class.
    \ingroup Database
    \ingroup RecordWrappers
*/

using namespace std;
#ifndef LIST
#define LIST //!<Inclusion guard
#include <list>
#endif

#ifndef STRING
#define STRING //!<Inclusion guard
#include <string>
#endif

#include "LevelRecord.h"
#include "Nukleid.h"
#include "ParentRecord.h"
#include "QValueRecord.h"
#include "LevelRecordChildrenWrapper.h"
#include "ParentRecordChildrenWrapper.h"
#include "QValueRecordChildrenWrapper.h"
#include "NormalizationRecordChildrenWrapper.h"
#include "Record.h"


#ifndef BETARECORDWRAPPER_H
#define BETARECORDWRAPPER_H //!<Inclusion guard.
/**Used to provide the rest of the ENSDF software with a simple way to deal with beta records without specializing to either beta+ or beta-.
   \note Electron capture is not supported, a typecast to BetaPlusRecord has to be done for that.
   \author Rikard Lundmark
   \ingroup Database
   \ingroup RecordWrappers
 */
class BetaRecordWrapper: public LevelRecordChildrenWrapper, public ParentRecordChildrenWrapper, public QValueRecordChildrenWrapper, public NormalizationRecordChildrenWrapper, public Record
{
 private:
  //nothing here.
 public:
  BetaRecordWrapper(list<string> cardArg, //!<The The card string(s) corresponding to this record. 
		    LevelRecord * myLevel, //!<A pointer to the Level record corresponding to this record. 
		    ParentRecord * myParent, //!< A pointer to the Parent record corresponding to this record. 
		    QValueRecord * myQValue, //!< A pointer to the Q value record corresponding to this record. 
		    NormalizationRecord * norm //!< A pointer to the Normalization record corresponding to this record. 
		    ); //!<Constructor, construct the object.

  virtual double getEndPointEnergy() const = 0; //!< The endpoint energy of this beta decay.
  virtual double getIntensityOfBetaDecayBranch() const = 0; //!< The intensity of the beta decay branch. 

};
#endif
