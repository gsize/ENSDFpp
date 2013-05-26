#include "CommandLineArgument.h"

CommandLineArgument::CommandLineArgument()
{
  
}

CommandLineArgument::CommandLineArgument(string mFlag, int mNumberOfArguments)
{
  flag=mFlag;
  numberOfArguments = mNumberOfArguments;
}
