#include "ENSDF.h"

/* Creates the ENSDF object. 
 * Arguments: vector<string> filenames, the filenames that contains the ENSDF database.
 */
ENSDF::ENSDF(vector<string> filenames, VerbosePrinter * toRegister, unsigned int numberOfThreads)
{
  registerListener(toRegister);
  vPrint(3, "Loading ENSDF files.\n");
  list<string> myIsotopes;
  for(vector<string>::iterator it = filenames.begin(); it < filenames.end(); it++)
    {
      vPrint(6,"Now loading file: \"%s\" into memory\n",it->c_str());
      FILE * myFile;
      myFile = fopen ((*it).c_str() , "r");
      char line[100];
      
      if(myFile==NULL)
	perror("The opened file is null");
      
      while (fgets(line, 100, myFile) != NULL) 
	{
	  string myString(line);
	  myIsotopes.push_back(myString);
	}
      if(myFile!=NULL)
	fclose(myFile);
    }
  list< list<string> > allDatasets = splitInDataSets(myIsotopes); //contains all datasets, one entry for each dataset.
  
  map< Nukleid, list< list<string> > > datasetsSortedByIsotope; //the outer list contains one entry for each isotope. Now fill this...

  vPrint(3,"Identifying isotopes for each dataset.\n");
  for(list< list<string> >::iterator myIterator = allDatasets.begin(); myIterator!=allDatasets.end(); myIterator++)
    {
      Nukleid * myNucleid = NULL;
      list<string>::iterator subIterator = myIterator->begin();
      while(myNucleid == NULL && subIterator != myIterator->end())
	{
	  myNucleid = getNucleidFromString(*subIterator);
	  subIterator++;
	}
      if(myNucleid==NULL) //if this occurs, we cannot obtain any more information...
	{
	  throw DataFileException("Error parsing data file: SubIterator went out of bounds");
	}
      datasetsSortedByIsotope[Nukleid(*myNucleid)].push_back(*myIterator);
      delete myNucleid;
    }
  allDatasets = list< list<string> >();
  vPrint(3, "Creating isotope objects\n");
  int iter = 0;
  vector<list<pair<Nukleid, list<list<string> > * > > > toFlush;
  for(unsigned int i = 0; i<numberOfThreads; i++)
    {
      toFlush.push_back(list< pair < Nukleid, list< list< string > > * > >());
    }
  int flushAdress = 0;
  for(map<Nukleid, list< list<string> > >::iterator myIterator = datasetsSortedByIsotope.begin(); myIterator!=datasetsSortedByIsotope.end(); myIterator++)
    {
      Nukleid myNukleid = myIterator->first;
      vPrint(12,"Preparing to create isotope object for nucleid %s (%d of %d).\n",myNukleid.toString().c_str(), ++iter, datasetsSortedByIsotope.size());
      toFlush[(flushAdress++)%numberOfThreads].push_back(make_pair(myNukleid, &(myIterator->second)));
    }
  threadFlush(toFlush);
  //to free memory.
  datasetsSortedByIsotope=map<Nukleid,list< list<string> > >();
  vPrint(3,"Done creating ENSDF object\n");
  return;
}

ENSDF::~ENSDF()
{
  for(map<Nukleid, Isotop* >::iterator it = myNucleidIsotopeMap.begin(); it!=myNucleidIsotopeMap.end(); it++)
    {
      delete it->second;
      it->second = NULL;
    }
}

void ENSDF::threadFlush(vector<list<pair<Nukleid, list<list<string> > *> > > toFlush)
{
  list<pthread_t *> myThreads;
  list<pair<Nukleid, Isotop*> > myIsotopes;
  int iret1;
  for(vector<list< pair < Nukleid, list< list< string > > * > > >::iterator it = toFlush.begin(); it!=toFlush.end(); it++)
    {
      pthread_t * mySingleThread = new pthread_t();
      list< pair< Isotop**, list< list< string > > * > > * myP = 
	new list < pair < Isotop**, list< list< string > > * > >();

      for(list< pair < Nukleid, list< list< string> > * > >::iterator iq = it->begin(); iq!=it->end(); iq++)
	{
	  myP->push_back(pair < Isotop**, list< list< string > > * > (&myNucleidIsotopeMap[iq->first], iq->second));
	}
      vPrint(7,"Creating worker thread...\n");
      iret1 = pthread_create( mySingleThread, NULL, loadIsotope, (void*)myP);
      if(iret1!=0)
	perror("ERROR creating thread.\n");
      
      myThreads.push_back(mySingleThread);
    }
  for(list<pthread_t *>::iterator it = myThreads.begin(); it!=myThreads.end(); it++)
    {
      vPrint(7,"Waiting for thread to finish.\n");
      pthread_join(**it, NULL);
      vPrint(7,"Thread finished.\n");
      delete *it;
      *it = NULL;
    }
  return;
}


void * loadIsotope(void * ptr)
{
  list< pair<Isotop**, list<list<string> >* > > * toCreateFrom
    = (list< pair<Isotop**, list<list<string> >* > > * ) ptr; 
  for(list<pair<Isotop**, list< list< string> >* > >::iterator it = toCreateFrom->begin(); it!=toCreateFrom->end(); it++)
    *(it->first)= new Isotop(*(it->second));
  delete toCreateFrom;
  ptr = NULL;
  toCreateFrom = NULL;
  return (void*)NULL; //quick and dirty
}


/* Returns a specific isotope, if we are asked for it.
 * Arguments: a nucleid object describing the isotope we want to get.
 * Returns: an isotope object with the ENSDF datasets concerning this nucleid.
 */
const Isotop * ENSDF::getIsotop(const Nukleid nucleidToGet) const
{
  if(myNucleidIsotopeMap.find(nucleidToGet)!=myNucleidIsotopeMap.end())
    return myNucleidIsotopeMap.find(nucleidToGet)->second;
  else
    return NULL;
}

/* Returns the total number of isotops stored.
 */
int ENSDF::getNumberOfIsotops() const
{
  return myNucleidIsotopeMap.size();
}

const map< Nukleid, Isotop*> ENSDF::getAllIsotopes() const
{
  return myNucleidIsotopeMap;
}


/* Returns a list containing the data sets found in the input list.
 * Arguments: A list containing all the data sets found in the ENSDF, with a blank line between data sets.
 * Returns: a list containing all the data sets found in the input list.
 */
list< list<string> > ENSDF::splitInDataSets(list<string> allDatasets)
{
  list< list<string> > toReturn;
  list<string> currentDataset;
  for(list<string>::iterator it = allDatasets.begin(); it!=allDatasets.end(); ++it)
    {
      if(isEmptyString(*it))
	{
	  if(!currentDataset.empty())
	    {
	      toReturn.push_back(currentDataset);
	      currentDataset.clear();
	    }
	}
      else
	{
	  currentDataset.push_back(*it);
	}
    }
  if(!currentDataset.empty())
    {
      toReturn.push_back(currentDataset);
      currentDataset.clear();
    }
  return toReturn;
}

/* Checks if a string is empty
 * Arguments: the string to check for emptiness.
 * Returns: true if the string to check only contains ' ' and '\n'
 */
bool ENSDF::isEmptyString(string toCheck)
{
  for(unsigned int i = 0; i<toCheck.size(); i++)
    {
      if(toCheck.at(i)!=' ' && toCheck.at(i)!='\n')
	return false;
    }
  return true;
}

/* Returns an isotope object corresponding to a 80 character long ENSDF entry string.
 * Arguments: the string to create the isotope object from
 * Returns: The isotope object corresponding to the argument, or NULL if the argument string was invalid.
 */
Nukleid * ENSDF::getNucleidFromString(string stringToGetIsotopeFrom)
{
  try
    {
      Nukleid * myNukleid = new Nukleid(stringToGetIsotopeFrom.substr(0,5));
      return myNukleid;
    }
  catch(exception &e)
    {
      return NULL;
    }
}
