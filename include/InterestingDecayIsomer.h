/**\file InterestingDecayIsomer.h
   \author Rikard Lundmark
   \brief Header file for the InterestingDecayIsomer class.
*/
/**\file InterestingDecayIsomer.cpp
   \author Rikard Lundmark
   \brief Source file for the InterestingDecayIsomer class.
*/

#include "Nukleid.h"
#include "InterestingDecay.h"
#include "DoubleMath.h"

#ifndef SSTREAM
#define SSTREAM //!<Inclusion guard
#include <sstream>
#endif

#ifndef INTERESTINGDECAYISOMER
#define INTERESTINGDECAYISOMER //!<Inclusion guard
/**Extends InterestingDecay for using with the DataQueryIsomer class.
   \author Rikard Lundmark
 */
class InterestingDecayIsomer: public InterestingDecay
{
 public:
  InterestingDecayIsomer(Nukleid nukleidToSet, //!<The nucleid corresponding to this InterestingDecayIsomer.
			 double halfLifeToSet, //!<The half-life.
			 double energyToSet //!<The energy.
			 );//!<Constructs the object. \see DataQueryIsomer for more information about this.
  double getHalfLife() const; //!<Get the half life. \returns The half life.
  double getEnergy() const; //!<Get the energy. \returns The energy.
  string toString() const; //!<Get a string consisting of atomic number, mass number and nucleid name, used for plotting the isomers in a nucleid chart.

  bool operator==(const InterestingDecayIsomer &other //!<To compare with.
		  ) const; //!<Comparision operator.

  bool operator<(const InterestingDecayIsomer &other //!<To compare with.
		 ) const; //!<Comparition operator.

 protected:
  double myHalfLife; //!< The half-life.
  double myEnergy; //!< The energy.
};
#endif
