#include "MassPrinter.h"

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
  fprintf(myFile, "0 1 n\n");
  for(list<MassObject>::iterator it = myList.begin(); it!=myList.end(); it++)
    {
      fprintf(myFile, "%d %d %s\n", it->getNukleid().getZ(), it->getNukleid().getA(), it->getNukleid().getElement().c_str());
    }
  fclose(myFile);
  printf("File successfully created, finishing.\n");
  return 0;
}
