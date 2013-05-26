/**\file Isotop_TEST.h
   \author Rikard Lundmark
   \brief Header file for the Isotop test class.
   \ingroup UnitTests
*/
/**\file Isotop_TEST.cpp
   \author Rikard Lundmark
   \brief Source file for the Isotop test class.
   \ingroup UnitTests
*/


using namespace std;
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

#include "Isotop.h"
#include "GenericUnitTest.h"


#ifndef ISOTOP_TEST
#define ISOTOP_TEST//!<Inclusion guard.

/** Test class for the Isotop class. 
    \author Rikard Lundmark
    \todo Add more test cases.
    \ingroup UnitTests
 */
class Isotop_TEST: public GenericUnitTest
{
 public:
  int runUnitTests() const;
 protected:
  bool Isotop_ConstructsCorrectly_AssertTrue() const; //!<Test
};

#endif
