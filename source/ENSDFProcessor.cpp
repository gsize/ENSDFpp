#include "ENSDFProcessor.h"

ENSDFProcessor::ENSDFProcessor(string ENSDFDirectory, string MassTableDirectory, VerbosePrinter * toRegister, unsigned int nbrOfThreads)
{
  registerListener(toRegister);
  vector<string> myDirectory = getDirectoryContent(ENSDFDirectory);
  for(unsigned int i = 0; i<myDirectory.size(); i++)
    {
      myDirectory[i]=ENSDFDirectory + "/" + myDirectory[i];
    }
  myENSDF = new ENSDF(myDirectory, toRegister, nbrOfThreads);
  vector<string> myMassDirectory = getDirectoryContent(MassTableDirectory);
  myTable = new MassTable(MassTableDirectory + "/" + myMassDirectory.front(), toRegister);


  registerChild(myTable);
  registerChild(myENSDF);
}

ENSDFProcessor::~ENSDFProcessor()
{
  delete myTable;
  myTable = NULL;
  delete myENSDF;
  myENSDF = NULL;
}

void ENSDFProcessor::runBetaGammaQuery(double minBetaDecayTime, double maxBetaDecayTime, double minBetaBranchStrength, double minGammaBranchStrength, string outputFileName)
{
  vPrint(2,"Running query to file.\n");
  FILE * myFile = fopen (outputFileName.c_str(), "w");
  if(myFile!=NULL)
    {    
      vPrint(3,"File was successfully created.\n");
      list<InterestingDecayBetaGamma* > myDecays = runBetaGammaQuery(minBetaDecayTime, maxBetaDecayTime);
      for(list<InterestingDecayBetaGamma* >::iterator it = myDecays.begin(); it!=myDecays.end(); it++)
	{
	  fprintf(myFile, "%s\n", (*it)->toString(minBetaBranchStrength, minGammaBranchStrength).c_str());
	}
      vPrint(3,"Wrote %d posts to the file.\n", myDecays.size());
      vPrint(3,"Closing file.\n");
      fclose(myFile); 
      for(list<InterestingDecayBetaGamma*>::iterator it = myDecays.begin(); it!=myDecays.end(); it++)
	{
	  delete *it;
	  *it = NULL;
	}
    }
}

void ENSDFProcessor::runBetaGammaQuery_GenerateGammaList(double minBetaDecayTime, double maxBetaDecayTime, double minGammaBranchStrength, string outputFileName)
{
  vPrint(2, "Running GammaList query to file.\n");
  FILE * myFile = fopen(outputFileName.c_str(), "w");
  if(myFile!=NULL)
    {
      vPrint(3,"File was successfully created.\n");
      list<InterestingDecayBetaGamma* > myDecays = runBetaGammaQuery(minBetaDecayTime, maxBetaDecayTime);
      for(list<InterestingDecayBetaGamma*>::iterator it = myDecays.begin(); it!=myDecays.end(); it++)
	{
	  fprintf(myFile, "%s", (*it)->toGammaString(minGammaBranchStrength).c_str());
	}
      vPrint(3,"Wrote %d posts to the file.\n", myDecays.size());
      vPrint(3,"Closing file.\n");
      fclose(myFile);
      for(list<InterestingDecayBetaGamma*>::iterator it = myDecays.begin(); it!=myDecays.end(); it++)
	{
	  delete *it;
	  *it = NULL;
	}
    }
  else
    vPrint(1,"Could not create file!");
}

void ENSDFProcessor::runBetaGammaQuery_GenerateChartList(double minBetaDecayTime, double maxBetaDecayTime, double minGammaBranchStrength, string outputFileName)
{
  vPrint(2, "Running ChartList query to file.\n");
  FILE * myFile = fopen(outputFileName.c_str(), "w");
  if(myFile!=NULL)
    {
      vPrint(3,"File was successfully created.\n");
      list<InterestingDecayBetaGamma* > myDecays = runBetaGammaQuery(minBetaDecayTime, maxBetaDecayTime);
      for(list<InterestingDecayBetaGamma*>::iterator it = myDecays.begin(); it!=myDecays.end(); it++)
	{
	  fprintf(myFile, "%s", (*it)->toChartString(minGammaBranchStrength).c_str());
	}
      vPrint(3,"Wrote %d posts to the file.\n", myDecays.size());
      vPrint(3,"Closing file.\n");
      fclose(myFile);
      for(list<InterestingDecayBetaGamma*>::iterator it = myDecays.begin(); it!=myDecays.end(); it++)
	{
	  delete *it;
	  *it = NULL;
	}
    }
  else
    vPrint(1,"Could not create file!");
}


void ENSDFProcessor::runBetaGammaQuery_GenerateTexList(double minBetaDecayTime, double maxBetaDecayTime, double minGammaBranchStrength, string outputFileName)
{
  vPrint(2, "Running ChartList query to file.\n");
  FILE * myFile = fopen(outputFileName.c_str(), "w");
  if(myFile!=NULL)
    {
      vPrint(3,"File was successfully created.\n");
      list<InterestingDecayBetaGamma* > myDecays = runBetaGammaQuery(minBetaDecayTime, maxBetaDecayTime);
      for(list<InterestingDecayBetaGamma*>::iterator it = myDecays.begin(); it!=myDecays.end(); it++)
	{
	  fprintf(myFile, "%s", (*it)->toTexString(minGammaBranchStrength).c_str());
	  vPrint(3,"%s",(*it)->toTexString(minGammaBranchStrength).c_str());
	}
      vPrint(3,"Wrote %d posts to the file.\n", myDecays.size());
      vPrint(3,"Closing file.\n");
      fclose(myFile);
      for(list<InterestingDecayBetaGamma*>::iterator it = myDecays.begin(); it!=myDecays.end(); it++)
	{
	  delete *it;
	  *it = NULL;
	}
    }
  else
    vPrint(1,"Could not create file!");
}



void ENSDFProcessor::runIsomerQuery(double tLower, double tUpper, string outputFileName)
{
  vPrint(2,"Running Isomer query to file.\n");
  FILE * myFile = fopen (outputFileName.c_str(), "w");
  if(myFile!=NULL)
    {    
      vPrint(3,"File was successfully created.\n");
      list<InterestingDecayIsomer*> myDecays = runIsomerQuery(tLower, tUpper);
      for(list<InterestingDecayIsomer*>::iterator it = myDecays.begin(); it!=myDecays.end(); it++)
	{
	  fprintf(myFile, "%s\n", (*it)->toString().c_str());
	}
      vPrint(3,"Closing file.\n");
      fclose(myFile);
      for(list<InterestingDecayIsomer*>::iterator it = myDecays.begin(); it!=myDecays.end(); it++)
	{
	  delete *it;
	  *it = NULL;
	}
    }
  vPrint(2,"Done with query.\n");
}

list<InterestingDecayIsomer*> ENSDFProcessor::runIsomerQuery(double tLower, double tUpper)
{
  vPrint(2, "Creating Isomer query.\n");
  DataQueryIsomer * myQuery = new DataQueryIsomer(myENSDF, myPrinter);
  registerChild(myQuery);
  list<InterestingDecayIsomer*> myDecayList = myQuery->RunQuery(tLower, tUpper);

  delete myQuery;
  myQuery = NULL;
  
  return myDecayList;
}

list<InterestingDecayBetaGamma*> ENSDFProcessor::runBetaGammaQuery(double minBetaDecayTime, double maxBetaDecayTime)
{
  vPrint(2,"Creating BetaGamma data query.\n");
  DataQueryBetaGamma * myQuery = new DataQueryBetaGamma(myENSDF, myTable, myPrinter);
  registerChild(myQuery);

  list<InterestingDecayBetaGamma*> myDecayList = myQuery->RunQuery(minBetaDecayTime, maxBetaDecayTime);

  delete myQuery;
  myQuery = NULL;

  return myDecayList;
}


//lists the content of a directory
vector<string> ENSDFProcessor::getDirectoryContent(string directoryName)
{
  vPrint(3,"Loading directory content of %s\n",directoryName.c_str());
  vector<string> toReturn;

  struct dirent **eps;
  int n;

  n = scandir (directoryName.c_str(), &eps, one, alphasort);
  if (n >= 0)
    {
      int cnt;
      for (cnt = 0; cnt < n; ++cnt)
	{
	  string tmp(eps[cnt]->d_name);
	  if(!(tmp.compare(".")==0 || tmp.compare("..")==0 || tmp.compare(".svn")==0))
	    toReturn.push_back(eps[cnt]->d_name);
	}
    }
  else
    perror ("Couldn't open the directory");
  vPrint(3,"Found %d entries in folder %s\n", (int)toReturn.size(), directoryName.c_str());
  return toReturn;
}
