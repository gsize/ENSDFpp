/**\file DataFileException_TEST.h
   \author Rikard Lundmark
   \brief Header file for the DataFileException test class.
   \ingroup UnitTests
*/
/**\file DataFileException_TEST.cpp
   \author Rikard Lundmark
   \brief Source file for the DataFileException test class.
   \ingroup UnitTests
*/


#ifndef ASSERT_H
#define ASSERT_H//!<Inclusion guard.
#include <assert.h>
#endif

#ifndef IOSTREAM
#define IOSTREAM//!<Inclusion guard.
#include <iostream>
#endif

#ifndef LIST
#define LIST//!<Inclusion guard.
#include <list>
#endif

#ifndef STRING
#define STRING//!<Inclusion guard.
#include <string>
#endif

#include "DataFileException.h"
#include "GenericUnitTest.h"

using namespace std;

#ifndef DATAFILEEXCEPTION_TEST
#define DATAFILEEXCEPTION_TEST //!<Inclusion guard.
/** Runs the test on the DataFileException class.
    \author Rikard Lundmark
    \ingroup UnitTests
 */
class DataFileException_TEST : public GenericUnitTest
{
 public:
  int runUnitTests() const; 
 protected:
  bool DataFileException_ThrowsCorrectString_AssertTrue() const; //!<Test
};
#endif
