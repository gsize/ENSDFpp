/**\file InterestingDecayBetaGamma.h
   \author Rikard Lundmark
   \brief Header file for the InterestingDecayBetaGamma class.
*/
/**\file InterestingDecayBetaGamma.cpp
   \author Rikard Lundmark
   \brief Source file for the InterestingDecayBetaGamma class.
*/


using namespace std;
#include "Nukleid.h"
#include "Enums.h"
#include "DataFileException.h"
#include "MassObject.h"
#include "InterestingDecay.h"
#include "DoubleMath.h"
#include "LevelRecord.h"
#include "BetaRecordWrapper.h"
#include "BetaMinusRecord.h"
#include "BetaPlusRecord.h"

#define ELECTRONMASS (510.9989) //!<Mass of an electron (in keV)


#ifndef SSTREAM
#define SSTREAM //!<Inclusion guard
#include <sstream>
#endif

#ifndef VECTOR
#define VECTOR //!<Inclusion guard
#include <vector>
#endif

#ifndef LIST
#define LIST //!<Inclusion guard
#include <list>
#endif

#ifndef INTERESTINGDECAYBETAGAMMA_H
#define INTERESTINGDECAYBETAGAMMA_H //!<Inclusion guard
/**InterestingDecay for the DataQueryBetaGamma class. 
   \author Rikard Lundmark
 */
class InterestingDecayBetaGamma: public InterestingDecay
{
 public:
  InterestingDecayBetaGamma(vector< vector<double> > finalAdjacencyMatrix, //!<The adjacency matrix for the gamma levels.
			    vector<LevelRecord *> Levels, //!<The level records corresponding to this adjacency matrix.
			    list<BetaRecordWrapper *> Betas, //!<The beta records for this interesting decay.
			    Nukleid nukleid, //!<The Nukleid object for this interesting decay.
			    MassObject parent, //!<The parent mass object (used for beta Q value computations).
			    MassObject child //!<The child object (used for beta Q value computations).
			    ); //!<Constructor. \see DataQueryBetaGamma::RunQuery(double, double) for details about how the parameters are constructed.

  ~InterestingDecayBetaGamma(); //!<Destructor.

  string toString(double betaFilter = 0 //!<Sets the filter level for the beta decays.
		  , double gammaFilter = 0 //!<Sets the filter level for the gamma decays.
		  ) const; //!<Get a string containing information about all beta decays stronger than betaFilter and all gamma decays stronger than gammaFilter that were found in one iteration in the DataQueryBetaGamma. \return a string containing the mentioned information.

  string toGammaString(double gammaFilter = 0 //!<Sets the filter level for the gamma decays.
		       ) const; //!< Get a string containing only the parent nucleid and the gamma energy emitted for all gamma decays stronger than gammaFilter in one iteration of the DataQueryBetaGamma.


  string toChartString(double gammaFilter = 0 //!<Sets the filter level for the gamma decays.
		       ) const; //!< Get a string containing only the parent nucleid and the gamma energy emitted for all gamma decays stronger than gammaFilter in one iteration of the DataQueryBetaGamma.


  string toTexString(double gammaFilter = 0 //!<Sets the filter level for the gamma decays.
		       ) const; //!< Get a string containing only the parent nucleid and the gamma energy emitted for all gamma decays stronger than gammaFilter in one iteration of the DataQueryBetaGamma.

  
  list<BetaRecordWrapper *> getBetaDecays(); //!<Get the Beta decays associated with the InterestingDecayBetaGamma object. \return a list with the associated beta decays.
 protected:
  vector<vector<double> > myFinalAdjacencyMatrix; //!<The adjacency matrix for gamma levels. \see DataQueryBetaGamma::RunQuery(double, double) for information about computing this.
  vector<LevelRecord *> myLevels; //!<The LevelRecords.
  list<BetaRecordWrapper *> myBetas; //!<The Beta records.
  MassObject myParent; //!<The parent mass object (used for beta Q value computations).
  MassObject myChild; //!<The child mass object (used for beta Q value computations).
};

#endif
