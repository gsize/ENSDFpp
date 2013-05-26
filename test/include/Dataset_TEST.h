/**\file Dataset_TEST.h
   \author Rikard Lundmark
   \brief Header file for the Dataset test class.
   \ingroup UnitTests
*/
/**\file Dataset_TEST.cpp
   \author Rikard Lundmark
   \brief Source file for the Dataset test class.
   \ingroup UnitTests
*/

using namespace std;

#ifndef IOSTREAM
#define IOSTREAM //!<Inclusion guard
#include <iostream>
#endif

#ifndef ASSERT_H
#define ASSERT_H //!<Inclusion guard
#include <assert.h>
#endif

#include "Dataset.h"
#include "GenericUnitTest.h"

#ifndef DATASET_TEST
#define DATASET_TEST //!<Inclusion guard
/** Runs the test on the DataFileException class.
    \author Rikard Lundmark
    \ingroup UnitTests
 */
class Dataset_TEST : public GenericUnitTest
{
 public:
  int runUnitTests() const;
 protected:
  bool Dataset_ConstructsCorrectly_AssertTrue() const; //!<Test
  bool Dataset_LoadsDatasetCorrectly_AssertTrue() const; //!<Test
  bool Dataset_LoadsMoreRecordTypesCorrectly_AssertTrue() const; //!<Test
  bool Dataset_CreatesCorrectBetaRecords_AssertTrue() const; //!<Test
};
#endif
