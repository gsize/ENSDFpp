#include "Main.h"

using namespace std;
int main(int argc, char *argv[])
{
  list<CommandLineArgument> myArguments;
  myArguments.push_back(CommandLineArgument("file",1));
  myArguments.push_back(CommandLineArgument("bLimits",2));
  myArguments.push_back(CommandLineArgument("bBranch",1));
  myArguments.push_back(CommandLineArgument("gBranch",1));
  myArguments.push_back(CommandLineArgument("v",1)); //verbose.
  myArguments.push_back(CommandLineArgument("i",0));
  myArguments.push_back(CommandLineArgument("gList",0));
  myArguments.push_back(CommandLineArgument("iList",0));
  myArguments.push_back(CommandLineArgument("cList",0));
  myArguments.push_back(CommandLineArgument("texList",0));
  myArguments.push_back(CommandLineArgument("t",1));
  myArguments.push_back(CommandLineArgument("tLimits",2));
  myArguments.push_back(CommandLineArgument("help",0));
  CommandLineInterpreter * myInterpreter = new CommandLineInterpreter(argc, argv, myArguments);
  if(!myInterpreter->readFlaggedCommand("help").empty())
    {
      printf("The following arguments are valid:\n");
      printf("  -file <filename> Specifies output file.\n");
      printf("  -bLimits <lower limit> <upper limit> Specifies limiting Beta decay times.\n");
      printf("  -bBranch <branch strength> Specifies minimum branch strength for a beta decay branch.\n");
      printf("  -gBranch <branch strength> Specifies minimum branch strength for a gamma decay.\n");
      printf("  -v <verbose level> Specifies how verbose the output should be.\n     The larger verbose level, the more information will be dumped to the terminal during execution.\n");
      printf("  -i Interactive session.\n");
      printf("  -gList Create a list of gamma energies instead of normal output.\n");
      printf("  -iList Create a list of isomers instead of normal output.\n");
      printf("  -cList Create a list of nuclides suitable for chart view.\n");
      printf("  -texList Create a list of nuclides suitable for the report.\n");

      printf("  -tLimits Time limits for the isomers in case of the iList parameter.\n");
      printf("  -t <number of threads> specifies number of threads to use for loading data, default is 5.");
      printf("  -help Displays this help message.\n");
      return 0;
    }
  
  if(argc<2 || !(myInterpreter->readFlaggedCommand("i").empty()))
    {
      int verbosityLevel = 0;
      if(myInterpreter->readFlaggedCommand("v").size()==1)
	verbosityLevel = atoi((myInterpreter->readFlaggedCommand("v").front()).c_str());
      unsigned int nbrOfThreads = 5;
      if(myInterpreter->readFlaggedCommand("t").size()==1)
        nbrOfThreads = atoi((myInterpreter->readFlaggedCommand("t").front()).c_str());
      int retval = proceed_interact(verbosityLevel, nbrOfThreads);
      delete myInterpreter;
      myInterpreter = NULL;
      return retval;
    }
  int retval = proceed_nointeract(myInterpreter);
  delete myInterpreter;
  myInterpreter = NULL;
  return retval;
}


int proceed_interact(int verbosityLevel, unsigned int nbrOfThreads)
{
  VerbosePrinter * myVerbosePrinter = new VerbosePrinter(verbosityLevel);
  myVerbosePrinter->print(1,"Creating ENSDF object.\n");
  ENSDFProcessor * myProcessor = new ENSDFProcessor(ENSDF_DIR, MASSTABLE_DIR, myVerbosePrinter, nbrOfThreads);

  int thisVariableIsOnlyUsedToAvoidCompilerWarnings = 0;
  char proceed = 'Y';
  do
    {
      double min=1E-3, max=1, betabranch=0.1, gammabranch=0.1;
      printf("\nPlease enter query parameters.\n");
      printf("Minimum time for beta decay (s): ");
      thisVariableIsOnlyUsedToAvoidCompilerWarnings=scanf("%lg",&min);
      printf("Maximum time for beta decay (s): ");
      thisVariableIsOnlyUsedToAvoidCompilerWarnings=scanf("%lg",&max);
      printf("Minimum beta branch strength (%%): ");
      thisVariableIsOnlyUsedToAvoidCompilerWarnings=scanf("%lg", &betabranch);
      printf("Minimum gamma branch strength (%%): ");
      thisVariableIsOnlyUsedToAvoidCompilerWarnings=scanf("%lg",&gammabranch);
      char * myD = new char[200];
      printf("Enter output file name: "); fflush(stdin);
      thisVariableIsOnlyUsedToAvoidCompilerWarnings=scanf("%s",myD);
      
      string fileString(myD);
      
      myVerbosePrinter->print(1,"Running query\n");
      myProcessor->runBetaGammaQuery(min, max, betabranch, gammabranch, fileString);
      
      fflush(stdin);
      printf("Do you want to run another query? [Y/N] ");
      thisVariableIsOnlyUsedToAvoidCompilerWarnings=scanf(" %c", &proceed);
      fflush(stdin);
    }while(proceed=='Y' || proceed=='y');
  delete myProcessor;
  myProcessor = NULL;
  delete myVerbosePrinter;
  myVerbosePrinter = NULL;
  return 0;
}


int proceed_nointeract(CommandLineInterpreter * myInterpreter)
{
  int verbosityLevel = 0;
  if(myInterpreter->readFlaggedCommand("v").size()==1)
    verbosityLevel = atoi((myInterpreter->readFlaggedCommand("v").front()).c_str());

  
  VerbosePrinter * myVerbosePrinter = new VerbosePrinter(verbosityLevel);

  unsigned int nbrOfThreads = 5;
  if(myInterpreter->readFlaggedCommand("t").size()==1)
    {
      nbrOfThreads = atoi((myInterpreter->readFlaggedCommand("t").front()).c_str());
      myVerbosePrinter->print(8,"Number of threads: %d.\n",nbrOfThreads);
    }
  else
    {
      myVerbosePrinter->print(8,"Number of threads not specified, the default number %d was set.\n", nbrOfThreads);
    }

  
  
  if(myInterpreter->readFlaggedCommand("file").size()!=1)
    throw CommandLineException("File not properly specified.\n");
  string myFile = myInterpreter->readFlaggedCommand("file").front();
  if(myFile.size()<2)
    throw CommandLineException("Invalid file name specified.\n");
  
  myVerbosePrinter->print(1,"Creating ENSDF object.\n");
  ENSDFProcessor * myProcessor = new ENSDFProcessor(ENSDF_DIR, MASSTABLE_DIR, myVerbosePrinter, nbrOfThreads);

  myVerbosePrinter->print(1,"Running query\n");
  if(!myInterpreter->readFlaggedCommand("iList").empty())
    {
      if(myInterpreter->readFlaggedCommand("tLimits").size()!=2)
	throw CommandLineException("Decay time limits not properly specified.\n");
      double tLower = atof(((myInterpreter->readFlaggedCommand("tLimits"))[0]).c_str());
      double tUpper = atof(((myInterpreter->readFlaggedCommand("tLimits"))[1]).c_str());

      myProcessor->runIsomerQuery(tLower, tUpper, myFile);
    }
  else
    {
      if(myInterpreter->readFlaggedCommand("bLimits").size()!=2)
	throw CommandLineException("Beta limits not properly specified.\n");
      double bLowerLimit = atof(((myInterpreter->readFlaggedCommand("bLimits"))[0]).c_str());
      double bUpperLimit = atof(((myInterpreter->readFlaggedCommand("bLimits"))[1]).c_str());
      
      if(myInterpreter->readFlaggedCommand("gBranch").size()!=1)
	throw CommandLineException("Gamma branch not properly specified.\n");
      double gBranch = atof(myInterpreter->readFlaggedCommand("gBranch").front().c_str());
      
      if(!myInterpreter->readFlaggedCommand("gList").empty())
	{
	  myProcessor->runBetaGammaQuery_GenerateGammaList(bLowerLimit, bUpperLimit, gBranch, myFile);
	}
      else if(!myInterpreter->readFlaggedCommand("cList").empty())
	{
	  myProcessor->runBetaGammaQuery_GenerateChartList(bLowerLimit, bUpperLimit, gBranch, myFile);
	}
      else if(!myInterpreter->readFlaggedCommand("texList").empty())
	{
	   myProcessor->runBetaGammaQuery_GenerateTexList(bLowerLimit, bUpperLimit, gBranch, myFile);
	}
      else
	{
	  if(myInterpreter->readFlaggedCommand("bBranch").size()!=1)
	    throw CommandLineException("Beta branch not properly specified.\n");
	  double bBranch = atof(myInterpreter->readFlaggedCommand("bBranch").front().c_str());
	  myProcessor->runBetaGammaQuery(bLowerLimit, bUpperLimit, bBranch, gBranch, myFile);
	}
    }
  delete myProcessor;
  myProcessor = NULL;
  delete myVerbosePrinter;
  myVerbosePrinter = NULL;
  return 0;
}
