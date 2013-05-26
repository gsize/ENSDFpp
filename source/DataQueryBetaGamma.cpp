#include "DataQueryBetaGamma.h"


DataQueryBetaGamma::DataQueryBetaGamma(const ENSDF * ENSDFDatabase, const MassTable * MassTabell, VerbosePrinter * toRegister)
{
  registerListener(toRegister);
  myENSDF = ENSDFDatabase;
  myMassTable = MassTabell;
}

DataQueryBetaGamma::~DataQueryBetaGamma()
{
  //no need to destroy anything here.
}

list<InterestingDecayBetaGamma* > DataQueryBetaGamma::RunQuery(double minBeta, double maxBeta) const
{
  vPrint(4,"Query parameters: Min beta time: %f s, max beta time: %f s.\n", minBeta, maxBeta);
  list<InterestingDecayBetaGamma* > toReturn;
  map< Nukleid, Isotop*> myIsotopeMap = myENSDF->getAllIsotopes();
  
  vPrint(4,"Searching through isotopes.\n");
  for(map< Nukleid, Isotop*>::iterator it = myIsotopeMap.begin(); 
      it!=myIsotopeMap.end(); it++)
    {
      list<InterestingDecayBetaGamma* > tempList = DetectInterestingStuffWithThisIsotope(it->second, minBeta, maxBeta);
      toReturn.insert(toReturn.end(), tempList.begin(), tempList.end());
    }
  vPrint(5, "Number of interesting decays: %d", toReturn.size());
  for(list<InterestingDecayBetaGamma*>::iterator it = toReturn.begin(); it!=toReturn.end(); it++)
    {
      vPrint(3,"%s\n",(*it)->toString(0,0).c_str());
    }
  return toReturn;
}

bool DataQueryBetaGamma::CompareElementsForSort(const LevelRecord * L1, const LevelRecord * L2)
{
  if(L1==NULL || L2==NULL)
    return false;
  if(L1->getEnergy()>L2->getEnergy())
    return true;
  return false;
}


list<InterestingDecayBetaGamma* > DataQueryBetaGamma::DetectInterestingStuffWithThisIsotope(const Isotop * isotopToCheck, double minBeta, double maxBeta) const
{
  list<InterestingDecayBetaGamma* > toReturn;

  vPrint(7, "Searching through isotope %s.\n", isotopToCheck->getNukleid().toString().c_str());
  list<Dataset* > myDatasets = isotopToCheck->getDatasets();
  vPrint(9, "%d datasets to search.\n",myDatasets.size());


  for(list<Dataset* >::iterator ir = myDatasets.begin(); ir!=myDatasets.end(); ir++)
    {
      vPrint(15, "Searching through a dataset within isotope %s.\n", isotopToCheck->getNukleid().toString().c_str());
      list<LevelRecord *> myLevelsList = (*ir)->getLevelRecords();
      myLevelsList.sort(&CompareElementsForSort);
      vector<LevelRecord *> myLevels;
      vPrint(22, "We have the following levels:\n");
      for(list<LevelRecord *>::iterator it = myLevelsList.begin(); it!=myLevelsList.end(); it++)
	{
	  if(*it!=NULL)
	    {
	      myLevels.push_back(*it);
	      vPrint(22,"Energy: %f, HalfLife: %f\n", (*it)->getEnergy(), (*it)->getHalfLife());
	    }
	}

      //now create decay matrix.
      vector<vector<double> > adjacencyMatrix;
      adjacencyMatrix.push_back(vector<double>()); //first row and column contains BETA information (in practice only first row...)
      
      for(vector<LevelRecord *>::const_iterator it = myLevels.begin(); it!=myLevels.end(); it++)
	{
	  adjacencyMatrix.push_back(vector<double>());
	}
      for(vector<vector<double> >::iterator it = adjacencyMatrix.begin(); it!=adjacencyMatrix.end(); it++)
	{
	  for(unsigned int i = 0; i<adjacencyMatrix.size(); i++)
	    it->push_back(0);
	}
      vPrint(16,"Decay matrix created.\n");
      vector<vector<double> > finalAdjacencyMatrix = adjacencyMatrix;
      list<GammaRecord *> myGammas = (*ir)->getGammaRecords();
      for(list<GammaRecord *>::iterator it = myGammas.begin(); it!=myGammas.end(); it++)
	{
	  const LevelRecord * Lstart = (*it)->getLevelRecord();
	  const LevelRecord * Lend = findNextLevel(*ir, *it);
	  if(Lstart==NULL || Lend==NULL)
	    {
	      vPrint(7, "NULL level detected.\n");
	      if(Lstart!=NULL)
		vPrint(8,"SLevel: %f\n", Lstart->getEnergy());
	      if(Lend!=NULL)
		vPrint(8,"ELevel: %f\n", Lend->getEnergy());
	      vPrint(8,"Gamma: %f\n", (*it)->getDecayEnergy());
	      list<GammaRecord *>::iterator ir = it;
	      it++;
	      myGammas.erase(ir);
	      it--;
	    }
	  else
	    {
	      unsigned int startP = -1, stopP = -1;
	      unsigned int count = 1;
	      for(vector<LevelRecord *>::const_iterator ia = myLevels.begin(); ia!=myLevels.end(); ia++)
		{
		  if((*ia)==Lstart)
		    startP = count;
		  if((*ia)==Lend)
		    stopP = count;
		  ++count;
		}
	      if(startP<0 || stopP<0) //if this happens, something is terribly wrong with the program.
		throw DataFileException("Pointer went out of bounds."); 
	      else if(startP==stopP) //if this happens, it means the level the gamma left from is the same as the level it fell to. Cannot be allowed.
		{
		  vPrint(8, "Warning: Gamma level without energy detected.");
		  list<GammaRecord *>::iterator ir = it;
		  it++;
		  myGammas.erase(ir);
		  it--;
		}
	      else
		{
		  vPrint(22, "startP: %d, stopP: %d\n", startP, stopP);
		  adjacencyMatrix[startP][stopP]=(*it)->getTransitionIntensity(); //+1 corrected for.
		  //from startP level to stopP level.
		}
	    }
	}
      

#ifdef SLOWDEBUG
      //now the adjacency matrix is filled with the intensities...
      vPrint(16,"Adjacency matrix filled with intensities:\n");
      for(unsigned int i = 0; i<adjacencyMatrix.size(); i++){
	for(unsigned int j = 0; j<adjacencyMatrix.size(); j++)
	  vPrint(20, "%f ", adjacencyMatrix[i][j]);
	vPrint(20,"\n");
	}
#endif
      
      list<BetaRecordWrapper*> foundBetas;

      list<BetaRecordWrapper*> myBetaRecords = (*ir)->getBetaRecords();
      for(list<BetaRecordWrapper*>::const_iterator it = myBetaRecords.begin(); it!=myBetaRecords.end(); it++)
	{
	  const ParentRecord * P = (*it)->getParentRecord();
	  if(P!=NULL && minBeta<=P->getHalfLife() && maxBeta>=P->getHalfLife())
	    {
	      foundBetas.push_back(*it);
	    }
#ifdef SLOWDEBUG
	  else
	    {
	      if(P==NULL)
		vPrint(18,"Not adding beta, parent null.\n");
	      else
		vPrint(18,"Not adding beta, half-life %f, parent %s.\n", P->getHalfLife(), P->getNukleid().toString().c_str());
	    }
#endif
	}
      for(list<BetaRecordWrapper*>::const_iterator it = foundBetas.begin(); it!=foundBetas.end(); it++)
	{
	  list<BetaRecordWrapper*>::const_iterator ip = it;
	  for(ip++; ip!=foundBetas.end(); ip++)
	    {
	      if((*it)->getLevelRecord()==(*ip)->getLevelRecord())
		{
		  vPrint(22,"Energy: %f, HalfLife: %f\n", (*it)->getLevelRecord()->getEnergy(), (*it)->getLevelRecord()->getHalfLife());
		  vPrint(22, "B1: %s.\n", (*it)->getCardStrings().front().c_str());
		  vPrint(22, "B2: %s.\n", (*ip)->getCardStrings().front().c_str());
		  throw DataFileException("Two different betas goes to the same level.");
		}
	    }
	}
      if(foundBetas.size()>0 && myGammas.size()>0)
	{
	  //Now add beta intensity to each level...
	  double levelSum = 0;
	  for(list<BetaRecordWrapper*>::const_iterator it = foundBetas.begin(); it!=foundBetas.end(); it++)
	    {
	      unsigned int toLevel = -1;
	      int count = 0;
	      for(vector<LevelRecord *>::const_iterator ip = myLevels.begin(); ip!=myLevels.end(); ip++)
		{
		  ++count;
		  if((*it)->getLevelRecord()==(*ip))
		    {
		      toLevel = count;
		      break;
		    }
		}
	      if(toLevel<0)
		throw DataFileException("LevelRecord not found!");
	      adjacencyMatrix[0][toLevel] = (*it)->getIntensityOfBetaDecayBranch()/100;

#ifdef SLOWDEBUG
	      vPrint(20, "Beta intensity: %f, to level %d.\n",adjacencyMatrix[0][toLevel], toLevel); //+1 corrected for.
#endif

	      levelSum +=adjacencyMatrix[0][toLevel];
	    }
	  finalAdjacencyMatrix[0][0] = levelSum;

	  //now normalize outgoing intensity from a level to 1.
	  vPrint(15, "Now normalizing...\n");
	  for(unsigned int i = 1; i<adjacencyMatrix.size(); i++)
	    {
	      double rowSum = 1E-90;
	      for(unsigned int j = 1; j<adjacencyMatrix.size(); j++)
		{
		  rowSum+=adjacencyMatrix[i][j];
		}
	      for(unsigned int j = 1; j<adjacencyMatrix.size(); j++)
		{
		  adjacencyMatrix[i][j]/=rowSum;
		}
	    }
#ifdef SLOWDEBUG
	  vPrint(20,"New normalized matrix:\n");
	  for(unsigned int i = 0; i<adjacencyMatrix.size(); i++){
	    for(unsigned int j = 0; j<adjacencyMatrix.size(); j++)
	      vPrint(20, "%f ", adjacencyMatrix[i][j]);
	    vPrint(20,"\n");
	  } 
#endif
	  
	  //now compute final Gamma intensities.
	  vPrint(16,"Final Gamma intensities computed.\n");
	  for(unsigned int i = 0; i<adjacencyMatrix.size(); i++)
	    {
#ifdef SLOWDEBUG
	      vPrint(20,"%f ", finalAdjacencyMatrix[i][0]);
#endif
	      for(unsigned int j = 1; j<adjacencyMatrix.size(); j++)
		{
		  finalAdjacencyMatrix[i][j] = adjacencyMatrix[i][j]*finalAdjacencyMatrix[i][0];
#ifdef SLOWDEBUG
		  vPrint(20,"%f ", finalAdjacencyMatrix[i][j]);
#endif
		  finalAdjacencyMatrix[j][0]+= finalAdjacencyMatrix[i][j];
		}
#ifdef SLOWDEBUG
	      vPrint(20,"\n");
#endif
	    }
	  
	  //adjacency matrix computation completed!
	  toReturn.push_back(
			     new InterestingDecayBetaGamma(
							   finalAdjacencyMatrix, 
							   myLevels, 
							   foundBetas, 
							   foundBetas.front()->getParentRecord()->getNukleid(), 
							   myMassTable->getMassObject(foundBetas.front()->getParentRecord()->getNukleid()), 
							   myMassTable->getMassObject(foundBetas.front()->getNukleid())));
	  vPrint(12,"New InterestingDecay object created.\n");
	}
      else
	{
	  vPrint(16, "No suitable Beta records found for isotope %s.\n",isotopToCheck->getNukleid().toString().c_str());
	  vPrint(16, "Stats: Number of found betas: %d, total: %d, number of gammas: %d.\n", foundBetas.size(),myBetaRecords.size(), myGammas.size());
	  
	}
    }      
  vPrint(15,"All interesting decays for this isotope detected.\n");
  return toReturn;
}


const LevelRecord * DataQueryBetaGamma::findNextLevel(const Dataset * datasetToCheck, const GammaRecord * gammaToMatch) const
{
  if(gammaToMatch->getLevelRecord()==NULL)
    {
      vPrint(3,"WARNING: No level record for this gamma record: %s\n", gammaToMatch->getCardStrings().front().c_str());
      return NULL;
    }
  double guessedLevelEnergy = (gammaToMatch->getLevelRecord()->getEnergy() - gammaToMatch->getDecayEnergy());
  double bestMatch = 1E99;
  LevelRecord * found = NULL;
  list<LevelRecord *> myLevelRecords = datasetToCheck->getLevelRecords();
  for(list<LevelRecord* >::iterator it = myLevelRecords.begin(); it!=myLevelRecords.end(); it++)
    {
      //vPrint(17,"Comparing energy %f with guessed energy %f, the gamma energy was %f.\n", (*it)->getEnergy(), guessedLevelEnergy, gammaToMatch->getDecayEnergy());
      double tmp = fabs((*it)->getEnergy()-guessedLevelEnergy);
      if(tmp<bestMatch && (tmp<guessedLevelEnergy*0.3 || tmp<100 )) //allow 10 % difference or 10 keV difference.
	{
	  bestMatch = tmp;
	  found = *it;
	}
    }
  return found;
}
