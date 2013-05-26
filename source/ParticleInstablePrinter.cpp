#include "ParticleInstablePrinter.h"


int main()
{
  int thisVariableIsOnlyUsedToAvoidCompilerWarnings = 0;
  printf("Loading nucleid mass table..."); fflush(stdout);
  MassTable myMassTable("../ENSDF_MASSTABLE/mass.mas03");
  printf("done\n");
  printf("Enter output file name: "); fflush(stdout); fflush(stdin);
  char * myD = new char[255];
  thisVariableIsOnlyUsedToAvoidCompilerWarnings=scanf("%s", myD);
  FILE * myFile = fopen(myD, "w");
  if(myFile==NULL)
    {
      perror("File could not be opened.");
      return 1;
    }
  list<MassObject> myList = myMassTable.getMassObjects();
  for(list<MassObject>::iterator it = myList.begin(); it!=myList.end(); it++)
    {
      double VL = it->getAtomicMass().value;
      double HL1 = 1E99,  HL2 = 1E99, HL3 = 1E99, HL4 = 1E99, HL5=1E99;
      bool alphaInstable = false;
      try
	{
	  HL1 = myMassTable.getMassObject(it->getNukleid().getZ()-1, it->getNukleid().getA()-1).getAtomicMass().value + PROTONMASS;
	}
      catch(DataFileException) {}
      try
	{
	  HL2 = myMassTable.getMassObject(it->getNukleid().getZ(), it->getNukleid().getA()-1).getAtomicMass().value + NEUTRONMASS;
	}
      catch(DataFileException) {}
      try
	{
	  HL3 = myMassTable.getMassObject(it->getNukleid().getZ(), it->getNukleid().getA()-2).getAtomicMass().value + 2*NEUTRONMASS;
	}
      catch(DataFileException) {}
      try
	{
	  HL4 = myMassTable.getMassObject(it->getNukleid().getZ()-1, it->getNukleid().getA()-2).getAtomicMass().value + NEUTRONMASS + PROTONMASS;
	}
      catch(DataFileException) {}
      try
	{
	  HL5 = myMassTable.getMassObject(it->getNukleid().getZ()-2, it->getNukleid().getA()-2).getAtomicMass().value + 2*PROTONMASS;
	}
      catch(DataFileException) {}
      try
	{
	  double aAlpha = -1E99;
	  double aMyself = it->getMassExcess().value;
	  aAlpha = myMassTable.getMassObject(it->getNukleid().getZ() - 2,it->getNukleid().getA()-4).getMassExcess().value + myMassTable.getMassObject(2,4).getMassExcess().value;
	  HalfLifeEstimator myEstimator;
	  alphaInstable = (myEstimator.estimateHalfLife((aMyself-aAlpha)/1E3, it->getNukleid().getA(), it->getNukleid().getZ()) < 1E-9);
	}
      catch(DataFileException)
	{
	  //do nothing...
	}

      if(VL>HL1 || VL>HL2 || VL>HL3 || VL>HL4 || VL>HL5 || alphaInstable)
	fprintf(myFile, "%d %d %s\n", it->getNukleid().getZ(), it->getNukleid().getA(), it->getNukleid().getElement().c_str());
    }
  fclose(myFile);
  printf("File successfully created, finishing.\n");
  return 0;
}
