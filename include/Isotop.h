/**\file Isotop.h
   \author Rikard Lundmark
   \brief Header file for the Isotop class.
   \ingroup Database
*/
/**\file Isotop.cpp
   \author Rikard Lundmark
   \brief Source file for the Isotop class.
   \ingroup Database
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

#include "Dataset.h"
#include "Nukleid.h"
#include "LevelRecord.h"
#include "DataFileException.h"

//dummy classes for testing purposes
#ifndef ISOTOP_H
#define ISOTOP_H //!<Inclusion guard
/**The Isotop class wrapps all the datasets concerning a specific nukleid.
   \author Rikard Lundmark
   \ingroup Database
 */
class Isotop
{
 public:
  Isotop(list< list<string> > indata //!<Each list in this list of lists of strings contains the ENSDF records for a dataset.
	 ); //!<Constructor, constructs all Datasets from indata.
  ~Isotop(); //!<Destructor.

  Nukleid getNukleid() const; //!<Gets the Nukleid associated with this Isotop. \returns The Nukleid associated with this Isotop.
  list<Dataset* > getDatasets() const; //!<Gets all datasets for this Isotop. \returns a list containing pointers to each Dataset.
 protected:
  list<Dataset* > myDatasets; //!<Pointers to all datasets in this Nukleid.
  Nukleid myNukleid; //!<The specifik Nukleid.
};
#endif
