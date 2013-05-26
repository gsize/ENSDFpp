#include "ENSDF_TEST.h"

bool ENSDF_TEST::ENSDF_CheckIfConstructsCorrectly_AssertTrue() const
{
  ENSDF myENSDF(vector<string>());
  return true;
}

bool ENSDF_TEST::ENSDF_ReadsCorrectNumberOfIsotopes_AssertTrue() const
{
  vector<string> myVector;
  myVector.push_back("ensdf.027");
  ENSDF myENSDF(myVector);

  Nukleid myNukleid(" 27AL");

  assert(myENSDF.getAllIsotopes().find(myNukleid)->second->getDatasets().size()==13);
  assert (myENSDF.getNumberOfIsotops()==9);
  return true;
}

bool ENSDF_TEST::ENSDF_PassesDataCorrectlyToSubRoutines_AssertTrue() const
{
  //27SI -> 12 datasets
  vector<string> myVector;
  myVector.push_back("ensdf.027");
  ENSDF myENSDF(myVector);
  return true;
}

int ENSDF_TEST::runUnitTests() const
{
  cout << "Running unit tests on ENSDF...";
  if(!ENSDF_CheckIfConstructsCorrectly_AssertTrue())
    return 1;
  if(!ENSDF_ReadsCorrectNumberOfIsotopes_AssertTrue())
    return 2;
  if(!ENSDF_PassesDataCorrectlyToSubRoutines_AssertTrue())
    return 3;
  cout << "done" << endl;
  return 0;
}
