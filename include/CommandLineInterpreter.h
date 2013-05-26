/**\file CommandLineInterpreter.h
   \brief Header file for the CommandLineInterpreter class.
   \author Rikard Lundmark
*/
/**\file CommandLineInterpreter.cpp
   \brief Source file for the CommandLineInterpreter class.
   \author Rikard Lundmark
*/

using namespace std;

#ifndef STRING
#define STRING //!<Inclusion guard
#include <string>
#endif

#ifndef VECTOR
#define VECTOR //!<Inclusion guard
#include <vector>
#endif

#ifndef MAP
#define MAP //!<Inclusion guard.
#include <map>
#endif

#ifndef LIST
#define LIST //!<Inclusion guard
#include <list>
#endif

#include "CommandLineArgument.h"
#include "CommandLineException.h"

#ifndef COMMANDLINEINTERPRETER_H
#define COMMANDLINEINTERPRETER_H //!<Inclusion guard.

/**Interprets command line arguments according to a list of CommandLineArguments (acceptable flags), and throws an exception if unknown flags are encountered.

   \author Rikard Lundmark
 */
class CommandLineInterpreter
{
 public:
  CommandLineInterpreter(int argc, //!<The number of command line arguments.
			 char *argv[], //!<The actual arguments.
			 list<CommandLineArgument> myAcceptableFlags //!<The flags which should be accepted by this interpreter.
			 );
  //!< Constructor. \exception CommandLineException if the CommandLineArguments does not match argv and argc (if there are unknown flags).

  vector<string> readFlaggedCommand(string flag //!<The flag to read
				    );//!<Returns a vector<string> containing all arguments for a specific flag. Returns an empty vector if there are no arguments for this flag.
  
  vector<string> readFlaglessCommands(); //!<Returns all arguments without flags.
 private:
  map<string, vector<string> > myFlaggedCommands; //!<The current flagged commands.
  vector<string> myFlaglessCommands; //!<The current flagless commands.
};
#endif
