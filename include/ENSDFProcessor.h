/**\file ENSDFProcessor.h
   \author Rikard Lundmark
   \brief Header file for the ENSDFProcessor class.
*/
/**\file ENSDFProcessor.cpp
   \author Rikard Lundmark
   \brief Source file for the ENSDFProcessor class.
*/


using namespace std;
#ifndef LIST
#define LIST //!<Inclusion guard
#include <list>
#endif

#ifndef VECTOR
#define VECTOR //!<Inclusion guard
#include <vector>
#endif

#ifndef STRING
#define STRING //!<Inclusion guard
#include <string>
#endif

#ifndef STDIO_H
#define STDIO_H //!<Inclusion guard
#include <stdio.h>
#endif

#ifndef SYS_TYPES_H
#define SYS_TYPES_H //!<Inclusion guard
#include <sys/types.h>
#endif

#ifndef DIRENT_H
#define DIRENT_H //!<Inclusion guard
#include <dirent.h>
#endif

#ifndef MAP
#define MAP //!<Inclusion guard
#include <map>
#endif

#ifndef EXCEPTION
#define EXCEPTION //!<Inclusion guard
#include <exception>
#endif

#ifndef SSTREAM
#define SSTREAM //!<Inclusion guard
#include <sstream>
#endif

#include "Dataset.h"
#include "Isotop.h"
#include "ENSDF.h"
#include "Nukleid.h"
#include "Record.h"
#include "DataQuery.h"
#include "DataQueryBetaGamma.h"
#include "DataQueryIsomer.h"
#include "InterestingDecay.h"
#include "InterestingDecayBetaGamma.h"
#include "InterestingDecayIsomer.h"
#include "Enums.h"
#include "MassTable.h"
#include "VerbosePrinter.h"
#include "VerbosePrinterEventEnabled.h"



#ifndef ENSDF_PROCESSOR_H
#define ENSDF_PROCESSOR_H //!<Inclusion guard


/** This class acts as an intermediate step between the Main function and the ENSDF object and the different DataQuery objects. 
    It controlls the construction of the ENSDF and MassTable objects.
    \author Rikard Lundmark
 */
class ENSDFProcessor : public VerbosePrinterEventEnabled
{
 public:
  ENSDFProcessor(string ENSDFDirectory, //!<The directory containing the ENSDF files.
		 string MassTableDirectory, //!<The directory containing the MassTable files (mass.mas03).
		 VerbosePrinter * toRegister = NULL, //!< Used to display information to the user.
		 unsigned int nbrOfThreads = 5 //!< The number of working threads the ENSDF object should use when constructing the Isotope objects.
		 );
  //!<Constructor, constructs the processor, which will also construct the underlying ENSDF and MassTable objects.

  ~ENSDFProcessor(); //!<Prevents memory leaks by destroying for example the ENSDF and MassTable objects.

  list<InterestingDecayBetaGamma* > runBetaGammaQuery(double minBetaDecayTime, //!<The minimum beta decay time to search for.
						      double maxBetaDecayTime //!<The maximum beta decay time to search for.
						      ); //!< Runs a DataQueryBetaGamma. \returns a list with the InterestingDecayBetaGamma found. \see DataQueryBetaGamma.
  
  void runBetaGammaQuery(double minBetaDecayTime, //!<The minimum beta decay time to search for.
			 double maxBetaDecayTime, //!<The maximum beta decay time to search for.
			 double minBetaBranchStrength, //!<The minimum beta branch strength to print.
			 double minGammaBranchStrength, //!<The minimum gamma branch strength to print.
			 string outputFileName //!<The file to write the result to. Must be a valid filename.
			 ); /**< Runs a DataQueryBetaGamma with the arguments minBetaDecayTime and maxBetaDecayTime, and saves the results to outputFileName.
			      \see DataQueryBetaGamma, InterestingDecayBetaGamma::toString(double, double)
			    */
  
  void runBetaGammaQuery_GenerateGammaList(double minBetaDecayTime,  //!<The minimum beta decay time to search for.
					   double maxBetaDecayTime, //!<The maximum beta decay time to search for.
					   double minGammaBranchStrength, //!<The minimum gamma branch strength to print.
					   string outputFileName //!<The file to write the result to. Must be a valid filename.
					   ); /**<Just like runBetaGammaQuery(double, double, double, double, string), but generates a list of nucleids and gamma energies only.*/

void runBetaGammaQuery_GenerateChartList(double minBetaDecayTime,  //!<The minimum beta decay time to search for.
					   double maxBetaDecayTime, //!<The maximum beta decay time to search for.
					   double minGammaBranchStrength, //!<The minimum gamma branch strength to print.
					   string outputFileName //!<The file to write the result to. Must be a valid filename.
					   ); /**<Just like runBetaGammaQuery(double, double, double, double, string), but generates a list of nucleids and gamma energies only.*/

void runBetaGammaQuery_GenerateTexList(double minBetaDecayTime,  //!<The minimum beta decay time to search for.
					   double maxBetaDecayTime, //!<The maximum beta decay time to search for.
					   double minGammaBranchStrength, //!<The minimum gamma branch strength to print.
					   string outputFileName //!<The file to write the result to. Must be a valid filename.
					   ); /**<Just like runBetaGammaQuery(double, double, double, double, string), but generates a list of nucleids and gamma energies only.*/



  
  list<InterestingDecayIsomer* > runIsomerQuery(double tLower, //!<The lower level decay time to search for.
						double tUpper //!<The upper level decay time to search for.
						);//!<Runs a DataQueryIsomer. \returns the InterestingDecaysIsomer objects found. \see DataQueryIsomer.

  void runIsomerQuery(double tLower, //!< The lower level decay time to search for.
		      double tUpper, //!< The upper level decay time to search for.
		      string outputFileName //!< The file to write the result to.
		      );//!< Calls runIsomerQuery(double, double), and writes the data to the file specified by outputFileName. \see InterestingDecayIsomer::toString()
  
 protected:
  ENSDF * myENSDF; //!< The ENSDF object used in this ENSDFprocessor.
  MassTable * myTable; //!< The MassTable object used in this ENSDFProcessor.


  vector<string> getDirectoryContent(
				     string DirectoryName //!<The directory to find the files in.
				     ); //!<Returns a list of the files in a given directory. \return A list of the files in the directory.

  static int one(const struct dirent *unused  //!<Unused.
		 ){ return 1; } //!<Used to when retrieving directory content.

};
#endif
