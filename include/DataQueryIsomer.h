/**\file DataQueryIsomer.h
   \author Rikard Lundmark
   \brief Header file for the DataQueryIsomer class.
*/
/**\file DataQueryIsomer.cpp
   \author Rikard Lundmark
   \brief Source file for the DataQueryIsomer class.
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
#include "InterestingDecayIsomer.h"

#include "DataQuery.h"

#ifndef DATAQUERYISOMER_H
#define DATAQUERYISOMER_H //!<Inclusion guard.

/** The purpose of this class is to run a specific query on the ENSDF object.
 * This query searches the ENSDF for isomers, that is, isotopes that has excited levels that have a lifetime within a certain timespan.

\author <a href="mailto:riklund@student.chalmers.se">Rikard Lundmark</a>
 */
class DataQueryIsomer: public DataQuery
{
 public:
  DataQueryIsomer(ENSDF * ENSDFDatabase, //!<The ENSDF object to run queries on.
		  VerbosePrinter * toRegister = NULL //!<Used to display information to the user.
		  ); //!<Creates the object and prepares it for running queries on it.
  list<InterestingDecayIsomer* > RunQuery(
					  double minT/**<The minimum time for the excited level.*/, 
					  double maxT/**<The maximum time for the excited level.*/
					  );//!<Runs a query on the ENSDF object. \return a list containing the InterestingDecayIsomer objects detected when running the query.
 protected:
  list<InterestingDecayIsomer* > 
    DetectInterestingStuffWithThisIsotope( 
					  Isotop * isotopToCheck, //!<The isotope to search.
					  double minT, //!<The minimum level lifetime.
					  double maxT //!<The maximum level lifetime.
					   ); //!<Searches a specific isotope for isomers. \returns a list containing the InterestingDecayIsomer objects for this specific query.
  static bool CompareElementsForUnique(const InterestingDecayIsomer * G1, //!<Pointer to compare.
				       const InterestingDecayIsomer * G2 //!<Pointer to compare.
				       ); //!<Predicate used for comparing InterestingDecayIsomer pointers when sorting. Just compares the nucleid objects.
  
  static bool CompareElementsForSort(const InterestingDecayIsomer * G1, //!<Pointer to compare.
				     const InterestingDecayIsomer * G2 //!<Pointer to compare.
				     ); //!<Predicate used for comparing InterestingDecayIsomer pointers when removing doubles. Just compares the nucleid objects.
};

#endif
