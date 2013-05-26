/**\file DataQueryBetaGamma.h
   \author Rikard Lundmark
   \brief Header file for the DataQueryBetaGamma class.
*/
/** \file DataQueryBetaGamma.cpp
    \author Rikard Lundmark
    \brief Source file for the DataQueryBetaGamma class.
*/


#ifndef LIST
#define LIST //!<Inclusion guard
#include <list>
#endif

#ifndef MATH_H
#define MATH_H //!<Inclusion guard.
#include <math.h>
#endif

#include "ENSDF.h"
#include "Nukleid.h"
#include "Isotop.h"
#include "InterestingDecayBetaGamma.h"
#include "BetaMinusRecord.h"
#include "BetaPlusRecord.h"
#include "BetaRecordWrapper.h"
#include "Enums.h"
#include "MassTable.h"
#include "MassObject.h"
#include "DataQuery.h"

#ifndef DATAQUERYBETAGAMMA_H
#define DATAQUERYBETAGAMMA_H //!<Inclusion guard.

/** The purpose of this class is to run a specific query type on the ENSDF database.
   This query searches for isotopes with a beta decay time between a minimum and a maximum decay time, 
   and which thereafter emits a gamma photon. 
   \remark This query was engineered to get data for coincidence measurements in a detector.
 * 
 \author <a href="mailto:riklund@student.chalmers.se">Rikard Lundmark</a>
 */
class DataQueryBetaGamma: public DataQuery
{
 public:
  DataQueryBetaGamma(const ENSDF * ENSDFDatabase, //!<The ENSDF database to run querys towards.
		     const MassTable * MassTabell, //!<A MassTable object used to extract some decay information.
		     VerbosePrinter * toRegister = NULL //!<Used to communicate information to the user.
		     ); //!<Constructor, constructs the query object and prepares it for running querys on.
  ~DataQueryBetaGamma(); //!<Destructor
  list<InterestingDecayBetaGamma* > RunQuery(double minBeta, //!<The minimum beta decay time.
					     double maxBeta //!<The maximum beta decay time.
					     ) const; //!<Runs a query on the ENSDF object \return A list with the interesting decays found.
 protected:
  list<InterestingDecayBetaGamma* > DetectInterestingStuffWithThisIsotope(const Isotop * isotopToCheck, //!<The isotope to search in.
									  double minBeta, //!< The minimum beta decay time.
									  double maxBeta //!<The maximum beta decay time.
									  ) const; //!< Detects all interesting decays for a specific isotope.
  
  const LevelRecord * findNextLevel(const Dataset * datasetToCheck, //!<The dataset to search for the level in.
				    const GammaRecord * gammaToMatch //!<The gamma record to find a next level for.
				    ) const; //!<Tries to find the LevelRecord in datasetToCheck to which gammaToMatch decays. \return A level record, if any is found, otherwise NULL. \note The ENSDF database does unfortunately not contain any way to find the LevelRecord for sure.
  const MassTable * myMassTable; //!<The MassTable used in this query object.
  static bool CompareElementsForSort(const LevelRecord * L1, const LevelRecord * L2); //!<Used for sorting a list containing LevelRecords.
};

#endif
