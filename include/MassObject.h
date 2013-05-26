/**\file MassObject.h
   \author Rikard Lundmark
   \brief Header file for the MassObject class.
*/
/**\file MassObject.cpp
   \author Rikard Lundmark
   \brief Source file for the MassObject class.
*/


using namespace std;
#ifndef STRING
#define STRING //!<Inclusion guard
#include <string>
#endif

#ifndef ALGORITHM
#define ALGORITHM //!<Inclusion guard.
#include <algorithm>
#endif

#include "Nukleid.h"

#ifndef MASSOBJECT_H
#define MASSOBJECT_H //!<Inclusion guard.

/**Corresponds to an Experimental value in the mass.mas03 file.
   \author Rikard Lundmark
 */
struct ExperimentalValue
{
  double value; //!<The actual value.
  double deltaValue; //!<The error of this value.
  bool isTheoretical; //!<If value is theoretical, this is true, otherwise it is false.
  bool nonCalculable; //!<If the value is not calculable, this is true.
};
  
/** A MassObject corresponds to a line in the mass.mas03 file. 
    \author Rikard Lundmark
    \note Only real nucleids (that is, not for example neutrons and protons) can be mass objects).
 */
class MassObject
{
 public:  
  MassObject(); //!<Constructor, constructs an empty MassObject.
  MassObject(string massString //!<The string to construct the MassObject from. This string must be a valid line >40 in the mass.mas03 file (not neutron or proton or such either).
	     ); //!<Creates the MassObject from a line in the mass.mas03 file.
  Nukleid getNukleid() const; //!<Get the Nukleid corresponding to this object.\returns The Nukleid object of this Mass object.
  ExperimentalValue getMassExcess() const;//!<Get the mass excess. \returns The mass excess of this Mass object.
  ExperimentalValue getBindingEnergy() const; //!< Get the Binding energy. \returns The binding energy of this Mass object.
  ExperimentalValue getBetaDecayEnergy() const;//!< Get the Beta decay energy. \returns the Beta decay energy of this mass object.
  ExperimentalValue getAtomicMass() const; //!< Get the atomic mass. \returns the Atomic mass of this mass object.
 protected:
  ExperimentalValue stringsToExperimentalValue(string value, //!< The value to make an ExperimentalValue from. 
					       string deltaValue //!<The error in in value.
					       ); //!< Returns the ExperimentalValue corresponding to a value and a diffrence in this value. \note The value and deltavalue must follow mass.mas03 format.

  double stringToDouble(string myString //!<The string to convert to a double.
			); //!< Convert a string to a double.
  string trimString(string toTrim //!< the string to trim.
		    ); //!<Trims a string.
  
  Nukleid myNukleid; //!<contains N, Z, A and the designation of this MassObject.
  ExperimentalValue massExcess; //!<In keV
  ExperimentalValue bindingEnergy; //!<In keV
  ExperimentalValue betaDecayEnergy; //!<In keV
  ExperimentalValue atomicMass; //!<The atomic mass in µu

};
#endif
