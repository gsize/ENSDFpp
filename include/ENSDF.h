/**\file ENSDF.h
   \author Rikard Lundmark
   \brief Header file for the ENSDF class.
*/
/**\file ENSDF.cpp
   \author Rikard Lundmark
   \brief Source file for the ENSDF class.
*/
/** @defgroup Database Database classes
 *  These classes are containing information from the ENSDF database.
 */


using namespace std;

#ifndef PTHREAD_H
#define PTHREAD_H //!<Inclusion guard.
#include <pthread.h>
#endif

#ifndef STDLIB_H
#define STDLIB_H //!<Inclusion guard
#include <stdlib.h>
#endif


#ifndef STDIO_H
#define STDIO_H //!<Inclusion guard.
#include <stdio.h> 
#endif

#ifndef UTILITY
#define UTILITY //!<Inclusion guard.
#include <utility> 
#endif

#ifndef MAP
#define MAP //!<Inclusion guard.
#include <map>
#endif

#ifndef STRING
#define STRING //!<Inclusion guard
#include <string>
#endif

#ifndef VECTOR
#define VECTOR //!<Inclusion guard
#include <vector>
#endif

#ifndef LIST
#define LIST //!<Inclusion guard
#include <list>
#endif

#ifndef EXCEPTION
#define EXCEPTION //!<Inclusion guard.
#include <exception>
#endif

#ifndef ALGORITHM
#define ALGORITHM//!<Inclusion guard.
#include <algorithm>
#endif

#include "DataFileException.h"
#include "Isotop.h"
#include "Nukleid.h"
#include "VerbosePrinterEventEnabled.h"
#include "VerbosePrinter.h"

#ifndef ENSDF_H
#define ENSDF_H //!<Inclusion guard.

void * loadIsotope(void * ptr //!<A pointer to an object of type list< pair<Isotop**, list<list<string> >* > > *, from which isotopes are created.
		   );//!<Function used to create isotopes asynchronously. Is used by pThread in thread maintaining.


/** Loads all information in the ENSDF data files, and creates Isotop object from them asynchronously.
    \author Rikard Lundmark
    \note The more CPU power you have, the faster initialization. 
    \note Loading the entire ENSDF database requires lots memory, we recommend at least 2 GB free when starting the program.
 */
class ENSDF : public VerbosePrinterEventEnabled
{
 public:
  ENSDF(vector<string> filenames, //!<A list of all the files which contains the ENSDF data. These files will be loaded in whole upon construction. \note If any non-ENSDF files are entered here, an exception will be thrown and the object will not initialize correctly.
	VerbosePrinter * toRegister = NULL, //!<Used to communicate with the user.
	unsigned int numberOfThreads = 5 //!<Number of working threads. You usually need
	); //!<Constructor, creates the ENSDF object and loads all Isotop objects asynchronously into memory. \note May take several minutes.
  ~ENSDF(); //!<Destructor, deletes Isotop objects to prevent memory leaks.
  const Isotop * getIsotop(const Nukleid isotopeToGet //!<The Nukleid object to find a matching Isotop object for.
			   ) const; //!<\returns the Isotop object corresponding to the Nukleid object specified, or NULL if there was no such isotop object.
  const map< Nukleid, Isotop*> getAllIsotopes() const; //!<\returns a map containing all Isotop objects in this ENSDF object.
  int getNumberOfIsotops() const; //!< \returns The number of Isotop object in this ENSDF object.
 protected:
  map< Nukleid, Isotop*> myNucleidIsotopeMap; //!< A register of all Isotop objects.
  Nukleid * getNucleidFromString(string stringToGetIsotopeFrom  //!< The 80 character ENSDF record string to find the Nukleid object from (usually the Nukleid identified by the first 5 characters).
				 );//!<Tries to identify a Nukleid object in an ENSDF record string (80 characters). Returns NULL if no Nukleid object could be created.
  list< list<string> > splitInDataSets(list<string> allDatasets //!<The ENSDF information to split in datasets. Each string in the list should be an 80 character ENSDF record. 
				       );//!<Takes all ENSDF information as input, and splits it Dataset's based on the End of dataset records. \returns A list of lists of strings, where each inner list corresponds to a dataset.

  bool isEmptyString(string toCheck //!<The string to check for empty-ness
		     ); //!<Checks if a string is empty or not.
  void threadFlush(vector< list<pair<Nukleid, list< list< string > >* > > > toFlush //!<The information needed to create all Isotop objects.
		   ); //!<Creates the working threads which creates all isotope objects, and waits for them to return. \note This is usually the most slow part of the creation process (therefore the multi-threading).
};
#endif
