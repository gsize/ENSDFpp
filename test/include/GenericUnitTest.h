/** \file GenericUnitTest.h
    \author Rikard Lundmark
    \brief Generic test class
    \ingroup Unit tests
*/
/**
   \file GenericUnitTest.cpp
   \author Rikard Lundmark
   \brief Generic test class
 */

using namespace std;

#ifndef GENERIC_UNIT_TEST_H
#define GENERIC_UNIT_TEST_H
class GenericUnitTest
{
 public:
  virtual int runUnitTests() const = 0; //!<Run the tests.
  GenericUnitTest(); //!<Constructor, constructs the class.
};
#endif
