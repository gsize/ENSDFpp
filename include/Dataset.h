/**\file Dataset.h
   \brief Header file for the Dataset class.
   \author Rikard Lundmark
   \ingroup Database
*/
/**\file Dataset.cpp
   \brief Source file for the Dataset class.
   \author Rikard Lundmark
   \ingroup Database
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

#ifndef VECTOR
#define VECTOR //!<Inclusion guard
#include <vector>
#endif

#ifndef SET
#define SET
#include <set> //!<Inclusion guard
#endif

#ifndef STDARG_H
#define STDARG_H
#include <stdarg.h> //!<Inclusion guard
#endif

#include "Record.h"
#include "DataFileException.h"
#include "IdentificationRecord.h"
#include "HistoryRecord.h"
#include "QValueRecord.h"
#include "CrossReferenceRecord.h"
#include "CommentRecord.h"
#include "ParentRecord.h"
#include "NormalizationRecord.h"
#include "ProductionNormalizationRecord.h"
#include "LevelRecord.h"
#include "BetaMinusRecord.h"
#include "BetaPlusRecord.h"
#include "AlphaRecord.h"
#include "DelayedParticleRecord.h"
#include "GammaRecord.h"
#include "ReferenceRecord.h"
#include "Enums.h"

#ifndef DATASET_H
#define DATASET_H //!<Inclusion guard.

/**This class corresponds to a specific dataset in the ENSDF database. It contains all the records in the dataset.
   \author Rikard Lundmark
   \ingroup Database
*/
class Dataset
{
 public:
  Dataset(list<string> textToInput //!<All the records in the dataset, one line per record.
	  ); //!<Constructor, constructs the dataset from a list of strings consisting of the dataset information in the ENSDF file.

  ~Dataset(); //!<Destructor, deletes all records in the database.

  list<Record * > getRecords() const; //!< \returns All the Records in this dataset.
  list<BetaRecordWrapper *> getBetaRecords() const; //!< \returns All the BetaPlusRecord and BetaMinusRecords in this Dataset, casted to BetaRecordWrapper's.

  list<IdentificationRecord* > getIdentificationRecords() const; //!< \returns The IdentificationRecords in this Dataset.
  list<HistoryRecord* > getHistoryRecords() const; //!< \returns The HistoryRecords in this Dataset.
  list<CrossReferenceRecord* > getCrossReferenceRecords() const; //!< \returns The CrossReferenceRecords in this Dataset.
  list<CommentRecord* > getCommentRecords() const; //!< \returns The CommentRecords in this Dataset.
  list<ParentRecord* > getParentRecords() const; //!< \returns the ParentRecords in this Dataset.
  list<NormalizationRecord* > getNormalizationRecords() const; //!< \returns the NormalizationRecords in this Dataset.
  list<ProductionNormalizationRecord* > getProductionNormalizationRecords() const; //!< \returns the ProductionNormalizationRecords in this Dataset.
  list<LevelRecord* > getLevelRecords() const; //!< \returns the LevelRecords in this Dataset.
  list<BetaMinusRecord* > getBetaMinusRecords() const; //!< \returns the BetaMinusRecords in this Dataset.
  list<BetaPlusRecord* > getBetaPlusRecords() const; //!< \returns the BetaPlusRecords in this Dataset.
  list<AlphaRecord* > getAlphaRecords() const; //!< \returns the AlphaRecords in this Dataset.
  list<DelayedParticleRecord* > getDelayedParticleRecords() const; //!< \returns the DelayedParticleRecords in this Dataset.
  list<GammaRecord* > getGammaRecords() const; //!< \returns the GammaRecords in this Dataset.
  list<ReferenceRecord* > getReferenceRecords() const; //!< \returns the ReferenceRecords in this Dataset.

 protected:
  void generateRecordLists(); //!<Generates the list myRecords from all records.
  void initRecordStack(); //!<Initializes the private member myRecordStack.
  void initRecords(); //!<Generates the list myRecords from all Record's.
  void initBetaRecords(); //!<Generates the list myBetaRecords from all BetaPlusRecord's and BetaMinusRecord's.  

  list<Record* > myRecords; //!<All Record's in the dataset.
  list<BetaRecordWrapper *> myBetaRecords; //!<All BetaPlusRecord's and BetaMinusRecord's in the Dataset.
  
  list<IdentificationRecord* > myIdentificationRecords; //!<The IdentificationRecord's in this Dataset.
  list<HistoryRecord* > myHistoryRecords; //!<The HistoryRecord's in this Dataset.
  list<CrossReferenceRecord* > myCrossReferenceRecords; //!< The CrossReferenceRecord's in this Dataset.
  list<CommentRecord* > myCommentRecords; //!< The CommentRecord's in this Dataset.
  list<ParentRecord* > myParentRecords; //!<The ParentRecord's in this Dataset.
  list<NormalizationRecord* > myNormalizationRecords; //!<The NormalizationRecord's in this Dataset.
  list<ProductionNormalizationRecord*> myProductionNormalizationRecords; //!<The ProductionNormalizationRecord's in this Dataset.
  list<LevelRecord* > myLevelRecords; //!< The LevelRecord's in this Dataset.
  list<BetaMinusRecord* > myBetaMinusRecords; //!<The BetaMinusRecord's in this Dataset.
  list<BetaPlusRecord* > myBetaPlusRecords; //!<The BetaPlusRecord's in this Dataset.
  list<AlphaRecord* > myAlphaRecords; //!<The AlphaRecord's in this Dataset.
  list<DelayedParticleRecord* > myDelayedParticleRecords; //!<The DelayedParticleRecord's in this Dataset.
  list<GammaRecord* > myGammaRecords; //!<the GammaRecord's in this Dataset.
  list<QValueRecord* > myQValueRecords; //!<The QValueRecord's in this Dataset.
  list<ReferenceRecord* > myReferenceRecords; //!<The ReferenceRecord's in this Dataset.

 private:
  void flushSpecific(RecordType toFlush //!< the RecordType to flush.
		     ); //!<Flushes a list of accumulated records from myRecordStack. Used upon initializing only.

  void flushAllStacksExcept(int nbrOfRecords, 
			    ...);//!<Flushes all accumulated lists of records except a number nbrOfRecords of records, which are specified by nbrOfRecords arguments, each consisting of the specific RecordType. Call with argument 0 to flush all.


  map<RecordType, list<string> > myRecordStack; //!<A map mapping RecordTypes together with accumulated records. This is used in order to accumulate continuation records and create one single record for them. Flushing this means taking the list and creating a record from it, and then emptying the list.
};
#endif
