#include "CommandLineInterpreter.h"

CommandLineInterpreter::CommandLineInterpreter(int argc, char *argv[], list<CommandLineArgument> myAcceptableFlags)
{
  for(int i = 0; i<argc; i++)
    {
      string temp(argv[i]);
      if(temp[0]=='-') //we have a flag...
	{
	  temp = temp.substr(1,temp.size());
	  bool found = false;
	  for(list<CommandLineArgument>::iterator it = myAcceptableFlags.begin(); it!=myAcceptableFlags.end(); it++)
	    {
	      if(temp.compare(it->flag)==0)
		{
		  if(i+it->numberOfArguments>argc)
		    throw CommandLineException("Insufficient arguments for flag.\n");
		  vector<string> myList;
		  for(int k = i+1; k<=i+it->numberOfArguments; k++)
		    {
		      string tmp(argv[k]);
		      myList.push_back(tmp);
		    }
		  myFlaggedCommands[temp] = myList;
		  i+=it->numberOfArguments;
		  found=true;
		}
	    }
	  if(!found)
	    throw CommandLineException("Command flag not recognized");	  
	}
      else
	{
	  myFlaglessCommands.push_back(argv[i]);
	}
    }
}

vector<string> CommandLineInterpreter::readFlaggedCommand(string flag)
{
  if(myFlaggedCommands.find(flag)!=myFlaggedCommands.end())
    {
      if(myFlaggedCommands[flag].empty())
	myFlaggedCommands[flag].push_back("");
      return myFlaggedCommands[flag];
    }
  else
    {
      return vector<string>();
    }
}

vector<string> CommandLineInterpreter::readFlaglessCommands()
{
  return myFlaglessCommands;
}
