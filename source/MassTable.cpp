#include "MassTable.h"


MassTable::MassTable(string filename, VerbosePrinter * toRegister)
{
  registerListener(toRegister);
  vPrint(4,"Creating mass table from file %s.\n", filename.c_str());
  FILE * myFile;
  myFile = fopen(filename.c_str(),"r");
  if(myFile==NULL)
    perror("The opened file is null");
  char line[200];
  vector<string> fileContent;
  while (fgets(line,200, myFile)!=NULL)
    {
      string myString(line);
      fileContent.push_back(myString);
    }
  vector<string>::iterator it = fileContent.begin();
  for(int i = 0; i<40 && it!=fileContent.end(); i++)
    ++it;
  while(it!=fileContent.end())
    {
      myMasses.push_back(MassObject(*(it++)));
    }
  if(myFile!=NULL)
    fclose(myFile);
  vPrint(4,"Done creating mass table.\n");
  return;
}

list<MassObject> MassTable::getMassObjects() const
{
  return myMasses;
}

const MassObject MassTable::getMassObject(Nukleid toGet) const
{
  vPrint(13, "Now searching through %d masstable entries.\n",myMasses.size());
  for(list<MassObject>::const_iterator it = myMasses.begin(); it!=myMasses.end(); it++)
    {
      if(it->getNukleid()==toGet)
	return (*it);
    }
  throw DataFileException("The requested nucleid was not found in the masstable: " + toGet.toString() + " Probable cause: incorrect or missing masstable.");
}

const MassObject MassTable::getMassObject(unsigned short int Z, unsigned short int A) const
{
  for(list<MassObject>::const_iterator it = myMasses.begin(); it!=myMasses.end(); it++)
    {
      if(it->getNukleid().getA()==A && it->getNukleid().getZ()==Z)
	return (*it);
    }
  throw DataFileException("The requested nucleid was not found. ");
}
