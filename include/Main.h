/**\file Main.h
   \brief Header file for the main program flow controlling functions.
   \author Rikard Lundmark
 */
/**\file Main.cpp
   \brief Source file for the main program flow controlling functions.
   \author Rikard Lundmark
*/

using namespace std;

#ifndef STRING
#define STRING //!<Inclusion guard
#include <string>
#endif

#ifndef STDLIB_H
#define STDLIB_H //!<Inclusion guard
#include <stdlib.h>
#endif

#ifndef VECTOR
#define VECTOR //!<Inclusion guard
#include <vector>
#endif

#ifndef LIST
#define LIST //!<Inclusion guard
#include <list>
#endif

#include "ENSDFProcessor.h"
#include "CommandLineInterpreter.h"
#include "VerbosePrinter.h"
#include "CommandLineException.h"

#define ENSDF_DIR "../ENSDF_DATA" //!<The ENSDF directory, should contain all the ENSDF files.
#define MASSTABLE_DIR "../ENSDF_MASSTABLE" //!<The MassTable directory, should contain ONLY the mass.mas03 file.


int main(int argc, //!<argc, standard.
	 char *argv[] //!<argv, standard.
	 );//!<The main method of the program.


/**Called by main if interactive queries are requested. 
   Currently only supports a limited set of queries.
 */
int proceed_interact(int verbosityLevel, //!<The verbosity level of the VerbosePrinter created.
		     unsigned int nbrOfThreads=5 //!<The number of worker threads for the ENSDFProcessor object.
		     );

/** Run the program in non-interactive mode.
 */
int proceed_nointeract(CommandLineInterpreter * myInterpreter //!<The CommandLineInterpreter from which to read what to do.
		       );


/** \mainpage
 \section intro_sec Introduction
 The ENSDF++ program was originally designed in order to extract data fron the ENSDF database for using in scientific calculations.
 It can without much effort be extended to meet the needs of other scienfic calculation requirements.
 
 \section install Installation
 This software is based upon STL librarys only, and therefore no specific installation procedure is required. The ENSDF++ program can be downloaded from <a href="ENSDFpp.tar.gz">here</a>.
 You however need to set it up with the correct ENSDF data files.
 These files can be obtained from the <a href="ftp://ftp.nncd.bnl.gov">National Nuclear Data Center’s FTP server</a>, using the username bnlndc. The files are currently contained in three archives, ensdf_1103_099.zip, ensdf_1103_199.zip and ensdf_1103_299.zip.
 Place the ENSDF files (extracted from these files) in a directory directly called ENSDF_DATA, one step above the program directory in the file hierarchy. 
 Also, you need to place a directory containing the <a href="http://www.nndc.bnl.gov/masses/mass.mas03">mass.mas03 file</a> in a directory named ENSDF_MASSTABLE, also one step up in the hierarchy.

\section makefile Compiling
Compiling should be no problem, just use the makefile provided. This makefile however contains some targets used for deploying it on some of Chalmers's remote servers. Just ignore these targets, type 'make' or 'make optimize' in the terminal in order to compile the software.

\section custom Customization
You will probably want to implement your own data queries to run, since the queries provieded does not cover more than a few specific cases. Just extend the DataQuery class in the same way as DataQueryBetaGamma and DataQueryIsomer does, and extend the InterestingDecay class like the InterestingDecayBetaGamma and InterestingDecayIsomer classes does. A brief look at the source code of these ought to be instructive in how to write your own queries. You also need to customize the ENSDFProcessor class to run your queries, and the Main.cpp file to communicate correctly with the ENSDFProcessor class. In order to compile your customizations you will also need to update the makefile accordingly, but this should be of no problem, just mimic the targets for the queries you are mimicing.

\section misc Miscellaneous
\todo Add unit tests for all classes, and extend existing unit tests.
\todo There are unfinished classes needing implementation.
\todo This documentation needs to be reviewed.

\section notera Notes
The NuclidePlotter part of the program depends on the <a href="http://www.jibble.org/epsgraphics/">Java EPS Graphics2D package</a>, which is licensed under the GNU General Public License (GPL).

 */
