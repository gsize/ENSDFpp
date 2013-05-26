/**\file IdentificationRecord.h
   \author Rikard Lundmark
   \brief Header file for the IdentificationRecord class.
   \ingroup Records
   \ingroup Database
*/
/**\file IdentificationRecord.cpp
   \author Rikard Lundmark
   \brief Source file for the IdentificationRecord class.
   \ingroup Records
   \ingroup Database
*/


using namespace std;
#include "Record.h"
#include "Nukleid.h"

#ifndef STRING
#define STRING //!<Inclusion guard
#include <string>
#endif

#ifndef LIST
#define LIST //!<Inclusion guard
#include <list>
#endif


#ifndef IDENTIFICATION_RECORD
#define IDENTIFICATION_RECORD //!<Inclusion guard

/**Corresponds to a single IdentificationRecord in the ENSDF database (including continuation records).
   \author Rikard Lundmark
   \note Not fully implemented.
   \ingroup Records
   \ingroup Database
 */

class IdentificationRecord : public Record
{
public:
	// cardArg is the ENSDF card for the record in the form of a 80-character string
  IdentificationRecord(list<string> cardArg //!<The card string(s) corresponding to this record. 
		       ); //!<Constructor, constructs the object.
  string getDSID() const; //!< Get dataset information \returns the DSID information.
  string getReferences() const; //!< Get reference information. \returns the References information.
  string getDate() const; //!<Get date. \returns The date corresponding to this IdentificationRecord.
  string getPublicationInformation() const; //!<Get publication information. \returns The Publication information.
  
 protected:
  string DSID, //!<The DSID information.
    references, //!<The reference information.
    publicationInformation,  //!<The publication information.
    date; //!<The date information.
 private:
  void processCard(); //!<Called by the constructor to process the card information and initalize DSID, references, publicationInformation and date.
};

#endif
