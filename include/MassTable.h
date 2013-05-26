/**\file MassTable.h
   \author Rikard Lundmark
   \brief Header file for the MassTable class.
*/
/**\file MassTable.cpp
   \author Rikard Lundmark
   \brief Source file for the MassTable class.
*/


using namespace std;

#ifndef STDIO_H
#define STDIO_H //!<Inclusion guard.
#include <stdio.h>
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

#include "MassObject.h"
#include "DataFileException.h"
#include "Nukleid.h"
#include "VerbosePrinterEventEnabled.h"
#include "VerbosePrinter.h"

#define PROTONMASS (1.00782503207) //!<The mass of a proton.
#define NEUTRONMASS (1.00866491574) //!<The mass of a neutron.

#ifndef MASSTABLE
#define MASSTABLE
/** Contains the MassTable from the mass.mas03 file.
    \author Rikard Lundmark
 */
class MassTable: public VerbosePrinterEventEnabled
{
 public:
  MassTable(string filename, //!<The filename to load the masstable from.
	    VerbosePrinter * toRegister = NULL //!<Used to display information to the user.
	    ); //!<C
  list<MassObject> getMassObjects() const; //!<Get the mass objects in the table. \returns A list of MassObjects. 

  const MassObject getMassObject(Nukleid toGet //!<The Nukleid object to get a MassObject for. 
				 ) const; //!<Returns a MassObject corresponding to toGet. \returns a MassObject. \throws DataFileException if there is no such MassObject.

  const MassObject getMassObject(unsigned short int Z, //!<The atomic number.
				 unsigned short int A //!<The mass number
				 ) const; //!<Returns a MassObject corresponding to a specific atomic- and massnumber. \returns a MassObject. \throws DataFileException if no such MassObject exists.
 private:
  list<MassObject> myMasses; //!<A list of MassObject loaded in the constructor.
};
#endif
