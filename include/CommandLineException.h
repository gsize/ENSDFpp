/**\file CommandLineException.h
   \author Rikard Lundmark
   \brief Header file for the CommandLineException class.
*/
/** \file CommandLineException.cpp
    \author Rikard Lundmark
    \brief Source file for the CommandLineException class.
*/


using namespace std;

#ifndef EXCEPTION
#define EXCEPTION
#include <exception> //!<Inclusion guard.
#endif

#ifndef STRING
#define STRING //!<Inclusion guard
#include <string>
#endif

#ifndef COMMANDLINEEXCEPTION_H
#define COMMANDLINEEXCEPTION_H //!<Inclusion guard.
/**Thrown when command line arguments are invalid.
   \author Rikard Lundmark
*/
class CommandLineException : public exception
{
public:
  CommandLineException(
		       string m="exception!" //!<The exception string.
		       );//!<Constructor.
  ~CommandLineException() throw();//!<Destructor
  const char* what() const throw();
  //!<To implement Exception.
  
private:
  string msg; //!<The message string for this exception.
};
#endif
