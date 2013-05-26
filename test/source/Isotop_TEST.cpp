#include "Isotop_TEST.h"


bool Isotop_TEST::Isotop_ConstructsCorrectly_AssertTrue() const
{
  Isotop myIsotop(list< list<string> >());
  return true;
}

int Isotop_TEST::runUnitTests() const
{
  cout << "Running unit tests on Isotop...";
  Isotop_ConstructsCorrectly_AssertTrue();
  cout << "done" << endl;
  return 0;
}
