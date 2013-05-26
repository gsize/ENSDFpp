/**\file DataFileException.h
   \author Rikard Lundmark
   \brief Header file for the DataFileException class.
 */
/**\file DataFileException.cpp
   \author Rikard Lundmark
   \brief Source file for the DataFileException class.
*/
using namespace std;

#ifndef EXCEPTION
#define EXCEPTION //!<Inclusion guard.
#include <exception>
#endif

#ifndef STRING
#define STRING //!<Inclusion guard
#include <string>
#endif

#ifndef DATAFILEEXCEPTION_H
#define DATAFILEEXCEPTION_H //!<Inclusion guard.
/**An exception thrown when an error relating to a data file is detected.
   When this error is thrown, there probably is something wrong with one of the data files supplied to the program.

\author Rikard Lundmark

 */
class DataFileException : public exception
{
  
private:
  string msg; //!< The reason of the exception to be thrown.

public:
  DataFileException(string m="exception!" //!<The description of the reason for the exception to be thrown.
		    ); //!<Constructor.

  ~DataFileException() throw(); //!<Destructor.
  const char* what() const throw(); //!<Retrieves the reason of the exception.
};
#endif
