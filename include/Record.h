/**\file Record.h
   \author Rikard Lundmark
   \brief Header file for the Record class.
   \ingroup Records
*/
/**\file Record.cpp
   \author Rikard Lundmark
   \brief Source file for the Record class.
   \ingroup Database
*/

/** @defgroup Records Record classes
 *  These classes are containing the record information in the ENSDF database.
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

#ifndef STDLIB_H
#define STDLIB_H //!<Inclusion guard
#include <stdlib.h>
#endif

#ifndef MATH_H
#define MATH_H//!<Inclusion guard.
#include <math.h>
#endif

#ifndef UTILITY
#define UTILITY //!<Inclusion guard.
#include <utility>
#endif

#include "Nukleid.h"


#ifndef RECORD
#define RECORD //!<Inclusion guard.

/**Extended by all specializing Record classes in the ENSDF database.
   \author Rikard Lundmark   
   \ingroup Records
   \ingroup Database
 */
class Record
{
public:
  Record(list<string> cardArg //!<The card string(s) corresponding to this record. 
	 );//!<Constructor.
  virtual ~Record();
  Nukleid getNukleid() const; //!<Returns the associated Nukleid object. \return The associated Nukleid object.
  list<string> getCardStrings() const; //!<Get the card strings. \return A list of strings, where each string corresponds to a record (all strings except the first is the continuation records.)
	
protected:
  double cardToDouble(int startPos, //!<The start position in the ENSDF record card.
		      int endPos //!<The end position in the ENSDF record card.
		      ); //!<Takes a portion of the record card, and parses it as a double. \todo Implement this for continuation records also.

  double parseHalfLife(int startPos, //!<The start position in the ENSDF card.
		       int endPos //!<The end position in the ENSDF card.
		       ); //!<Takes a portion of the record card, and parses it as a half-life (number and unit).
  
  string trimString(string toTrim //!<The string to trim.
		    ); //!<Trim a string.
 private:
  Nukleid myNukleid; //!<The Nukleid object corresponding to this Record.
  list<string> myCard; //!<Holds the 80 character wide ENSDF record card(s) for this record.
};										

#endif
