#include "InterestingDecayBetaGamma.h"

InterestingDecayBetaGamma::InterestingDecayBetaGamma(vector< vector<double> > finalAdjacencyMatrix, vector<LevelRecord *> Levels, list<BetaRecordWrapper *> Betas, Nukleid nukleid, MassObject parent, MassObject child)
  :InterestingDecay(nukleid)
{
  myBetas = Betas;
  myLevels = Levels;
  myFinalAdjacencyMatrix = finalAdjacencyMatrix;
  myParent = parent;
  myChild = child;
}

InterestingDecayBetaGamma::~InterestingDecayBetaGamma()
{
  
}

list<BetaRecordWrapper *> InterestingDecayBetaGamma::getBetaDecays()
{
  return myBetas;
}

string InterestingDecayBetaGamma::toChartString(double gammaFilter) const
{
  stringstream ss;
  for(unsigned int i = 1; i<myFinalAdjacencyMatrix.size(); i++)
    {
      if(myLevels[i-1]==NULL)
	throw DataFileException("NULL level detected in string creator function.");
      for(unsigned int j = i; j<myFinalAdjacencyMatrix.size(); j++)
	{
	  if(myFinalAdjacencyMatrix[i][j]*100>=gammaFilter)
	    {
	      if(myLevels[i-1]->getEnergy()-myLevels[j-1]->getEnergy()>1E-3)
		ss << getNukleid().getZ() << " " << getNukleid().getA() << " " << getNukleid().getElement() << endl;
	    }
 	}
    }
  return ss.str();
}


string InterestingDecayBetaGamma::toTexString(double gammaFilter) const
{
  stringstream ss;
  for(unsigned int i = 1; i<myFinalAdjacencyMatrix.size(); i++)
    {
      if(myLevels[i-1]==NULL)
	throw DataFileException("NULL level detected in string creator function.");
      for(unsigned int j = i; j<myFinalAdjacencyMatrix.size(); j++)
	{
	  if(myFinalAdjacencyMatrix[i][j]*100>=gammaFilter)
	    {
	      if(myLevels[i-1]->getEnergy()-myLevels[j-1]->getEnergy()>1E-3)
		ss << getNukleid().getA() << " " << getNukleid().getZ() << " " << getNukleid().getElement() << " " << myLevels[i-1]->getEnergy()-myLevels[j-1]->getEnergy() << " " << myFinalAdjacencyMatrix[i][j]*100 << " " << myBetas.front()->getParentRecord()->getHalfLife()*1000 << endl;
	    }
	}
    }
  return ss.str();
}


string InterestingDecayBetaGamma::toGammaString(double gammaFilter) const
{
  stringstream ss;
  for(unsigned int i = 1; i<myFinalAdjacencyMatrix.size(); i++)
    {
      if(myLevels[i-1]==NULL)
	throw DataFileException("NULL level detected in string creator function.");
      for(unsigned int j = i; j<myFinalAdjacencyMatrix.size(); j++)
	{
	  if(myFinalAdjacencyMatrix[i][j]*100>=gammaFilter)
	    {
	      if(myLevels[i-1]->getEnergy()-myLevels[j-1]->getEnergy()>1E-3)
		ss << getNukleid().getA() << " " << getNukleid().getZ() << " " << myLevels[i-1]->getEnergy()-myLevels[j-1]->getEnergy() << " " << myFinalAdjacencyMatrix[i][j]*100 << endl;
	    }
	}
    }
  return ss.str();
}

string InterestingDecayBetaGamma::toString(double betaFilter, double gammaFilter) const
{
  stringstream ss;
  double QValue = 0;
  for(list<BetaRecordWrapper *>::const_iterator it = myBetas.begin(); it!=myBetas.end(); it++)
    {
      if((*it)->getIntensityOfBetaDecayBranch()>=betaFilter)
	{
	  if(dynamic_cast<BetaMinusRecord *>(*it))
	    {
	      QValue = myParent.getMassExcess().value-myChild.getMassExcess().value;
	      ss << "B-: ";
	    }
	  else
	    {
	      QValue = myParent.getMassExcess().value-myChild.getMassExcess().value-2*ELECTRONMASS;
	      ss << "B+: ";
	    }
	  ss << getNukleid().toString();
	  ss << " with Q-value: " << QValue << " keV, Half-life: " << (*it)->getParentRecord()->getHalfLife() << " s, Branch-strength: " << (*it)->getIntensityOfBetaDecayBranch() << " %, Ground-state energy : " << (*it)->getLevelRecord()->getEnergy() << " keV" << endl;
	}
    }
  if(myLevels.size()!=myFinalAdjacencyMatrix.size()-1)
    throw DataFileException("Wrong number of levels.");

  for(unsigned int i = 1; i<myFinalAdjacencyMatrix.size(); i++)
    {
      
      for(unsigned int j = i; j<myFinalAdjacencyMatrix.size(); j++)
	{
	  if(myFinalAdjacencyMatrix[i][j]*100>=gammaFilter)
	    {
	      ss << "G: Probability: " << myFinalAdjacencyMatrix[i][j]*100 << "%, Energy: " << myLevels[i-1]->getEnergy()-myLevels[j-1]->getEnergy() << " keV, Energy of start level: " << myLevels[i-1]->getEnergy() << "keV." << endl;
	    }
	}
    }
  return ss.str();
}
