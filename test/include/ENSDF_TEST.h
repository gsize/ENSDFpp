/**\file ENSDF_TEST.h
   \author Rikard Lundmark
   \brief Header file for the ENSDF test class.
   \ingroup UnitTests
*/
/**\file ENSDF_TEST.cpp
   \author Rikard Lundmark
   \brief Source file for the ENSDF test class.
   \ingroup UnitTests
*/


#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef ASSERT_H
#define ASSERT_H
#include <assert.h>
#endif

#ifndef MAP
#define MAP
#include <map>
#endif

#include "ENSDF.h"
#include "GenericUnitTest.h"

using namespace std;

#ifndef ENSDF_TEST_H
#define ENSDF_TEST_H //!<Inclusion guard
/** Runs the test on the ENSDF class.
    \author Rikard Lundmark
    \ingroup UnitTests
 */
class ENSDF_TEST : public GenericUnitTest
{
 public:
  int runUnitTests() const;
 protected:
  bool ENSDF_CheckIfConstructsCorrectly_AssertTrue() const; //!<Test 
  bool ENSDF_ReadsCorrectNumberOfIsotopes_AssertTrue() const; //!<Test
  bool ENSDF_PassesDataCorrectlyToSubRoutines_AssertTrue() const; //!<Test
};
#endif
