#include "RunTests.h"


int main()
{
  addTests();
  cout << "Running unit tests..." << endl;
  for(list<GenericUnitTest*>::iterator it = myTests.begin(); it!=myTests.end(); it++)
    {
      int response = (*it)->runUnitTests();
      if(response!=0)
	{
	  cout << "Test failed. Further testing terminated." << endl;
	  return response;
	}
    }
  cout << "All tests were successful." << endl;
  return 0;
}


void addTests()
{
  myTests.push_back((GenericUnitTest*)(new DataFileException_TEST()));
  myTests.push_back((GenericUnitTest*)(new Dataset_TEST()));
  myTests.push_back((GenericUnitTest*)(new ENSDF_TEST()));
  myTests.push_back((GenericUnitTest*)(new Isotop_TEST()));
  myTests.push_back((GenericUnitTest*)(new Record_TEST()));
}
