/**\file ElementLookupTable.h
   \author Rikard Lundmark
   \brief Header file for the ElementLookupTable class.
*/
/**\file ElementLookupTable.cpp
   \author Rikard Lundmark
   \brief Source file for the ElementLookupTable class.
*/

using namespace std;
#ifndef STRING
#define STRING //!<Inclusion guard
#include <string>
#endif

#ifndef MAP
#define MAP //!<Inclusion guard.
#include <map>
#endif

#ifndef ELEMENTLOOKUPTABLE_H
#define ELEMENTLOOKUPTABLE_H
/** Converts element designations (for example NA, Na, na) to atomic numbers (for example 11).
   \author Rikard Lundmark
   \note The elements are hard-coded.
 */
class ElementLookupTable
{
 public:
  ElementLookupTable(); //!<Constructor, constructs the LookupTable.
  unsigned short int lookupElement(string elementToLookup); //!<Look up a specific element. \return the atomic number of the element, or 0 if the element was not found.
 protected:
  void stringToUpper(string& s //!< String to convert to uppercase.
		     ); //!<Converts a string to upper case.
  map<string, unsigned short int> myTable; //!<Maps the element strings to their atomic numbers.
};
#endif
