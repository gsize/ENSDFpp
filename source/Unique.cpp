#include "Unique.h"
#include <iostream>

bool uniqueCompare(string first, string second)
{
  if(first.length()!=second.length())
    return false;
  for(unsigned int i = 0; i<first.length(); i++)
    {
      if(first[i]!=second[i])
	return false;
    }
  return true;
}

bool uniqueSort(string first, string second)
{
  for(unsigned int i = 0; i<first.length() && i<second.length(); i++)
    {
      if(first[i]<second[i])
	return true;
      if(first[i]>second[i])
	return false;
    }
  return first.length()<second.length();
}

int main(int argc, char* argv[])
{
  if(argc!=3)
    {
      fprintf(stderr,"Usage: %s inputfile outputfile\n",argv[0]);
      return 0;
    }
  FILE * myFile;
  myFile = fopen(argv[1],"r");
  if(myFile==NULL)
    perror("File 1 could not be opened.\n");
  char line[100];
  list<string> myList;
  while (fgets(line,100,myFile)!=NULL)
    {
      string myString(line);
      myList.push_back(myString);
    }
  pclose(myFile);
  myList.sort(uniqueSort);
  myList.unique(uniqueCompare);
  myFile = fopen(argv[2],"w");
  if(myFile==NULL)
    perror("File 2 could not be opened.\n");
  for(list<string>::iterator it = myList.begin(); it!=myList.end(); it++)
    {
      fprintf(myFile, "%s", (*it).c_str());
    }
  pclose(myFile);
  return 0;
}
