 #include "DataFileException_TEST.h"

bool DataFileException_TEST::DataFileException_ThrowsCorrectString_AssertTrue() const
{
  try
    {
      throw DataFileException("qwerty");
    }
  catch(exception& e)
    {
      string s(e.what());
      assert(s.compare("qwerty")==0);
    }
  return true;
}

int DataFileException_TEST::runUnitTests() const
{
  cout << "Running unit tests on DataFileException...";
  if(!DataFileException_ThrowsCorrectString_AssertTrue())
    return 1;
  cout << "done" << endl;
  return 0;
}
