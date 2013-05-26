#include "BetaStablePrinter.h"

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
      double aLess = 1E99;
      double aMore = 1E99;
      double aAlpha = 1E99;
      double aMyself = it->getMassExcess().value;
      try
	{
	  aLess = myMassTable.getMassObject(it->getNukleid().getZ()-1, it->getNukleid().getA()).getMassExcess().value;
	}
      catch(DataFileException){}
      try
	{
	  aMore = myMassTable.getMassObject(it->getNukleid().getZ()+1, it->getNukleid().getA()).getMassExcess().value;
	}
      catch(DataFileException){}
      try
	{
	  aAlpha = myMassTable.getMassObject(it->getNukleid().getZ() - 2,it->getNukleid().getA()-4).getMassExcess().value + myMassTable.getMassObject(2,4).getMassExcess().value;
	}
      catch(DataFileException)
	{
	  //do nothing...
	}
      double HL1 = 1E99,  HL2 = 1E99, HL3 = 1E99, HL4 = 1E99, HL5=1E99;
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
      double VL = it->getAtomicMass().value;
      HalfLifeEstimator myEstimator;
      //aLess is mass of beta-minus nucleus, aMore of beta-plus.
      double QbetaPlus = aMyself-aLess- 2*ELECTRONMASSINMEV;
      double QbetaMinus = aMyself - aMore;
      //cout << QbetaMinus << " " << QbetaPlus << endl;
      bool SF = (pow((float)it->getNukleid().getZ(),(float)2.)/((float)it->getNukleid().getA()) >= 49);
      //cout << pow((float)it->getNukleid().getZ(),(float)2.)/((float)it->getNukleid().getA()) << endl;
      //cout << it->getNukleid().getA() << it->getNukleid().getElement() << " " << myEstimator.estimateHalfLife((aMyself-aAlpha)/1E3, it->getNukleid().getA(), it->getNukleid().getZ()) << " " << aMyself << " " << aLess <<  " " << aMore << " " << aAlpha << " " << SF << endl << endl << endl;
      if(!SF && QbetaMinus < 0 && QbetaPlus < 0 && (aAlpha > aMyself || (myEstimator.estimateHalfLife((aMyself-aAlpha)/1E3, it->getNukleid().getA(), it->getNukleid().getZ()) > 1E12)) && !(VL>HL1 || VL>HL2 || VL>HL3 || VL>HL4 || VL>HL5)) 
	fprintf(myFile, "%d %d %s\n", it->getNukleid().getZ(), it->getNukleid().getA(), it->getNukleid().getElement().c_str());
    }
  fclose(myFile);
  printf("File successfully created, finishing.\n");
  return 0;
}
