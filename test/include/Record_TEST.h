/**\file Record_TEST.h
   \author Rikard Lundmark
   \brief Header file for the Record test class.
   \ingroup UnitTests
*/
/**\file Record_TEST.cpp
   \author Rikard Lundmark
   \brief Source file for the Record test class.
   \ingroup UnitTests
*/


#ifndef IOSTREAM
#define IOSTREAM //!<Inclusion guard
#include <iostream>
#endif

#ifndef ASSERT_H
#define ASSERT_H //!<Inclusion guard
#include <assert.h>
#endif

#ifndef LIST
#define LIST //!<Inclusion guard
#include <list>
#endif

#ifndef STRING
#define STRING //!<Inclusion guard
#include <string>
#endif

#ifndef IOSTREAM
#define IOSTREAM //!<Inclusion guard
#include <iostream>
#endif

#include "Nukleid.h"
#include "LevelRecord.h"
#include "GammaRecord.h"
#include "ParentRecord.h"
#include "BetaMinusRecord.h"
#include "BetaPlusRecord.h"
#include "Dataset.h"
#include "DoubleMath.h"
#include "GenericUnitTest.h"

using namespace std;


#ifndef RECORD_TEST
#define RECORD_TEST //!<Inclusion guard
/** Runs tests on different record classes, including the Nukleid class.
    \author Rikard Lundmark
    \ingroup UnitTests
    \todo Split into separate classes for separate records, and the tests of Nukleid should logically not be in this class which should be taken care of.
 */
class Record_TEST : public GenericUnitTest
{
 public:
  int runUnitTests() const;
 protected:
  bool testNukleid() const; //!<Test
  bool testLevelRecord() const; //!<Test
  bool testGammaRecord() const; //!<Test
  bool testNormalizationRecord() const; //!<Test
  bool testParentRecord() const; //!<Test
  bool testBetaMinusRecord() const; //!<Test
  bool testBetaPlusRecord() const; //!<Test
  bool testRecord() const; //!<Test
  bool testLevelHalfLife() const; //!<Test
};

#endif
