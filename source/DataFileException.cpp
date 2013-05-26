using namespace std;
#include "DataFileException.h"

DataFileException::DataFileException(string m)
  :msg(m)
{

}

DataFileException::~DataFileException() throw()
{

}

const char* DataFileException::what() const throw()
{
  return msg.c_str();
}
