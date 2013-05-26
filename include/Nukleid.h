/**\file Nukleid.h
   \author Rikard Lundmark
   \brief Header file for the Nukleid class.
   \ingroup Database
*/
/**\file Nukleid.cpp
   \author Rikard Lundmark
   \brief Source file for the Nukleid class.
   \ingroup Database
*/


#ifndef STRING
#define STRING //!<Inclusion guard
#include <string>
#endif

#ifndef SSTREAM
#define SSTREAM //!<Inclusion guard.
#include <sstream>
#endif

#ifndef STDLIB_H
#define STDLIB_H //!<Inclusion guard
#include <stdlib.h>
#endif

#ifndef UTILITY
#define UTILITY //!<Inclusion guard.
#include <utility>
#endif

#include "DataFileException.h"
#include "ElementLookupTable.h"

using namespace std;
using namespace rel_ops;

#ifndef NUKLEID_H
#define NUKLEID_H //!<Inclusion guard.

/**Identifies a specific nucleid. Contains mass number, number of protons and chemical element in a string. Example: 8BE, 2H, etc. 
   \author Rikard Lundmark
   \ingroup Database
 */
class Nukleid
{
public:
  Nukleid(); //!<Constructor, constructs a blank nucleid (empty).
  Nukleid(string nucleid //!<The nucleid string to construct the Nukleid object from. 5 or 6 characters long, the first 3 characters are the mass number, the last 2 (or 3) are the name. Example: nucleid="  3H ", nucleid="235U ".
	  ); //!<Constructor, constructs a nucleid from a nucleid string.
  string getElement() const; //!<Returns the element string.
  int getZ() const; //!<Returns number of protons. 
  int getA() const; //!<Returns number of nucleons.
  string toString() const; //!<Returns a string formatted like "3HE".

  bool operator== (const Nukleid &other //!<To compare with.
		   ) const; //!<Comparision operator.
  bool operator> (const Nukleid &other //!<To compare with.
		  ) const; //!<Comparision operator.
  bool operator< (const Nukleid &other //!<To compare with.
		  ) const; //!<Comparision operator.

  static void parseNukleidName(string nucleid, //!<The nucleid name to parse
			       short unsigned int &mass, //!<A reference to an integer in which the mass number will be inserted.
			       string &element //!<A reference to a string in which the element will be inserted.
			       ); //!<Parses a nucleid name to mass and element.
  
 protected:
  short unsigned int parseAtomicNumber(string elementToParse //!<The element to parse.
				       ); //!<Parses the atomic number from elementToParse.

  unsigned short int Z; //!<The number of protons in the nucleid.
  unsigned short int A; //!<The number of nucleons in the nucleid.
  string element; //!<The element name.
  string name; //!<The name of the element. (e.g. "8HE").

 private:
  string trimString(string toTrim //!<The string to trim.
		    );//!<Trims a string.
};

#endif
