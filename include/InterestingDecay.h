/**\file InterestingDecay.h
   \author Rikard Lundmark
   \brief Header file for the InterestingDecay class.
*/
/**\file InterestingDecay.cpp
   \author Rikard Lundmark
   \brief Source file for the InterestingDecay class.
*/

using namespace std;

#ifndef STRING
#define STRING //!<Inclusion guard
#include <string>
#endif

#ifndef UTILITY
#define UTILITY //!<Inclusion guard
#include <utility>
#endif

#include "Nukleid.h"


#ifndef INTERESTINGDECAY_H
#define INTERESTINGDECAY_H //!<Inclusion guard
/**A class extending the DataQuery class normally needs to return the query result in some way, the results are normally contained in an object extending this class.
   \author Rikard Lundmark
 */
class InterestingDecay
{
 public:
  Nukleid getNukleid() const; //!<Return the Nukleid which the InterestingDecay is regarding.
  virtual string toString() const; //!<Returns a string corresponding to this InterestingDecay. By default this is equal to getNukleid().toString() if not overridden. \return A string describing the InterestingDecay.

  virtual bool operator==(const InterestingDecay &other //!<To compare with.
			  ) const; //!<Comparision operator. If not overridden, it only compares the Nukleid objects in the InterestingDecays.
  
  virtual bool operator<(const InterestingDecay &other //!<To compare with.
			 ) const;//!<If not overridden, it only compares the Nukleid objects in the InterestingDecays
  
 protected:
  InterestingDecay(
		   Nukleid toSet //!<The Nukleid object this InterestingDecay is regarding.
		   );//!<Constructor.
 private:
  Nukleid myNukleid; //!<The Nukleid object this InterestingDecay is regarding.
};


#endif
