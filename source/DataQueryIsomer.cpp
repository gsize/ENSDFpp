#include "DataQueryIsomer.h"

DataQueryIsomer::DataQueryIsomer(ENSDF * ENSDFDatabase, VerbosePrinter * toRegister)
{
  registerListener(toRegister);
  myENSDF = ENSDFDatabase;
}


list<InterestingDecayIsomer* > DataQueryIsomer::RunQuery(double minT, double maxT)
{
  vPrint(4,"Query parameters: Min time: %e s, max time: %e s.\n", minT, maxT);

  list<InterestingDecayIsomer* > toReturn;
  map< Nukleid, Isotop*> myIsotopeMap = myENSDF->getAllIsotopes();
  
  vPrint(4,"Searching through isotopes.\n");
  for(map< Nukleid, Isotop*>::iterator it = myIsotopeMap.begin(); 
      it!=myIsotopeMap.end(); it++)
    {
      list<InterestingDecayIsomer* > tempList = DetectInterestingStuffWithThisIsotope(it->second, minT, maxT);
      toReturn.insert(toReturn.end(), tempList.begin(), tempList.end());
    }
  toReturn.sort();
  toReturn.unique();
  return toReturn;
}

list<InterestingDecayIsomer* > DataQueryIsomer::DetectInterestingStuffWithThisIsotope(Isotop * isotopToCheck, double minT, double maxT)
{
  list<InterestingDecayIsomer* > toReturn;

  vPrint(7, "Searching through isotope %s.\n", isotopToCheck->getNukleid().toString().c_str());
  list<Dataset* > myDatasets = isotopToCheck->getDatasets();
  vPrint(9, "%d datasets to search.\n",myDatasets.size());
  for(list<Dataset* >::iterator ir = myDatasets.begin(); ir!=myDatasets.end(); ir++)
    {
      list<LevelRecord *> myLevelRecords = (*ir)->getLevelRecords();
      vPrint(12, "Found %d levels.\n", myLevelRecords.size());
      for(list<LevelRecord *>::iterator it = myLevelRecords.begin(); it!=myLevelRecords.end(); it++)
	{
	  if(*it!=NULL)
	    {
	      int pushback = 0;
	      if((*it)->getEnergy()>0 && (*it)->getHalfLife()>=minT && (*it)->getHalfLife()<=maxT)
		{
		  pushback = 1;
		  toReturn.push_back(new InterestingDecayIsomer((*it)->getNukleid(), (*it)->getHalfLife(), (*it)->getEnergy()));
		}
	      vPrint(15,"%s with energy %f, half-life %f, pushback %d.\n", isotopToCheck->getNukleid().toString().c_str(),(*it)->getEnergy(), (*it)->getHalfLife(), pushback);
	    }
	}
    }
  toReturn.sort(&CompareElementsForSort);
  vPrint(8,"Size before truncation: %d.\n",toReturn.size());
  toReturn.unique(&CompareElementsForUnique);
  vPrint(8,"Size after truncation: %d.\n", toReturn.size());
  return toReturn;
}

bool DataQueryIsomer::CompareElementsForSort(const InterestingDecayIsomer * G1, const InterestingDecayIsomer * G2)
{
  if(G1!=NULL && G2!=NULL)
    return G1->getNukleid()<G2->getNukleid();
  return G1!=NULL;
}

bool DataQueryIsomer::CompareElementsForUnique(const InterestingDecayIsomer * G1, const InterestingDecayIsomer * G2)
{
  if(G1!=NULL && G2!=NULL)
    return G1->getNukleid()==G2->getNukleid();
  return G1==G2;
}
