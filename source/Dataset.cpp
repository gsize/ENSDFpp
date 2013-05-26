#include "Dataset.h"

Dataset::~Dataset()
{
  for(list<IdentificationRecord* >::iterator it = myIdentificationRecords.begin(); it!=myIdentificationRecords.end(); it++)
    {
      delete *it;
      *it=NULL;
    }
  myIdentificationRecords.clear();
  for(list<HistoryRecord* >::iterator it = myHistoryRecords.begin(); it!=myHistoryRecords.end(); it++)
    {
      delete *it;
      *it=NULL;
   }
  myHistoryRecords.clear();
  for(list<CrossReferenceRecord* >::iterator it = myCrossReferenceRecords.begin(); it!=myCrossReferenceRecords.end(); it++)
    {
      delete *it;
      *it=NULL;
    }
  myCrossReferenceRecords.clear();
  for(list<CommentRecord* >::iterator it = myCommentRecords.begin(); it!=myCommentRecords.end(); it++)
    {
      delete *it;
      *it=NULL;
    }
  myCommentRecords.clear();
  for(list<ParentRecord* >::iterator it = myParentRecords.begin(); it!=myParentRecords.end(); it++)
    {
      delete *it;
      *it=NULL;
    }
  myParentRecords.clear();
  for(list<NormalizationRecord* >::iterator it = myNormalizationRecords.begin(); it!=myNormalizationRecords.end(); it++)
    {
      delete *it;
      *it=NULL;
    }
  myNormalizationRecords.clear();
  for(list<ProductionNormalizationRecord* >::iterator it = myProductionNormalizationRecords.begin(); it!=myProductionNormalizationRecords.end(); it++)
    {
      delete *it;
      *it=NULL;
    }
  myProductionNormalizationRecords.clear();
  for(list<LevelRecord* >::iterator it = myLevelRecords.begin(); it!=myLevelRecords.end(); it++)
    {
      delete *it;
      *it = NULL;
    }
  myLevelRecords.clear();
  for(list<BetaMinusRecord* >::iterator it = myBetaMinusRecords.begin(); it!=myBetaMinusRecords.end(); it++)
    {
      delete *it;
      *it = NULL;
    }
  myBetaMinusRecords.clear();
  for(list<BetaPlusRecord* >::iterator it = myBetaPlusRecords.begin(); it!=myBetaPlusRecords.end(); it++)
    {
      delete *it;
      *it = NULL;
    }
  myBetaPlusRecords.clear();
  for(list<AlphaRecord* >::iterator it = myAlphaRecords.begin(); it!=myAlphaRecords.end(); it++)
    {
      delete *it;
      *it = NULL;
    }
  myAlphaRecords.clear();
  for(list<DelayedParticleRecord* >::iterator it = myDelayedParticleRecords.begin(); it!=myDelayedParticleRecords.end(); it++)
    {
      delete *it;
      *it = NULL;
    }
  myDelayedParticleRecords.clear();
  
  myBetaRecords.clear();
  myRecords.clear();
}

void Dataset::flushAllStacksExcept(int nbrOfRecords, ...)
{
  set<RecordType> toNotFlush;
  va_list v1;
  va_start(v1,nbrOfRecords);
  for( int i = 0; i<nbrOfRecords; ++i )
    {
      RecordType R1 = intToEnum(va_arg(v1,int));
      toNotFlush.insert(R1);
    }
  va_end(v1);
  
  for(map<RecordType, list<string> >::iterator it = myRecordStack.begin(); it!=myRecordStack.end(); it++)
    {
      if(toNotFlush.find(it->first)==toNotFlush.end())
	flushSpecific(it->first);
    }
}

void Dataset::flushSpecific(RecordType toFlush)
{
  if(myRecordStack.find(toFlush)==myRecordStack.end())
    throw DataFileException("Cannot flush the attempted list.");
  
  for(map<RecordType, list<string> >::iterator it = myRecordStack.begin(); it!=myRecordStack.end(); it++)
    {
      if(it->first==toFlush)
	{
	  if(!it->second.empty())
	    {
	      ParentRecord * ParentReference = NULL;
	      if(!myParentRecords.empty())
		  ParentReference = myParentRecords.back();
	      NormalizationRecord * NormalizationReference = NULL;
	      if(!myNormalizationRecords.empty())
		NormalizationReference = myNormalizationRecords.back();
	      QValueRecord * QValueReference = NULL;
	      if(!myQValueRecords.empty())
		QValueReference = myQValueRecords.back();
	      LevelRecord * LevelReference = NULL;
	      if(!myLevelRecords.empty())
		LevelReference = myLevelRecords.back();
	      if(toFlush==IdentificationRecord_)
		{
		  myIdentificationRecords.push_back(new IdentificationRecord(it->second));
		}
	      else if(toFlush==HistoryRecord_)
		{
		  myHistoryRecords.push_back(new HistoryRecord(it->second));
		}
	      else if(toFlush==CrossReferenceRecord_)
		{
		  myCrossReferenceRecords.push_back(new CrossReferenceRecord(it->second));
		}
	      else if(toFlush==CommentRecord_)
		{
		  myCommentRecords.push_back(new CommentRecord(it->second));
		}
	      else if(toFlush==ParentRecord_)
		{
		  myParentRecords.push_back(new ParentRecord(it->second));
		}
	      else if(toFlush==NormalizationRecord_)
		{
		  myNormalizationRecords.push_back(new NormalizationRecord(it->second, ParentReference));
		}
	      else if(toFlush==ProductionNormalizationRecord_)
		{
		  myProductionNormalizationRecords.push_back(new ProductionNormalizationRecord(it->second, NormalizationReference));
		}
	      else if(toFlush==LevelRecord_)
		{
		  myLevelRecords.push_back(new LevelRecord(it->second, QValueReference));
		}
	      else if(toFlush==BetaMinusRecord_)
		{
		  myBetaMinusRecords.push_back(new BetaMinusRecord(it->second, NormalizationReference, LevelReference, ParentReference, QValueReference));
		}
	      else if(toFlush==BetaPlusRecord_)
		{
		  myBetaPlusRecords.push_back(new BetaPlusRecord(it->second, NormalizationReference, LevelReference, ParentReference, QValueReference));
		}
	      else if(toFlush==AlphaRecord_)
		{
		  myAlphaRecords.push_back(new AlphaRecord(it->second, NormalizationReference, LevelReference, ParentReference, QValueReference));
		}
	      else if(toFlush==DelayedParticleRecord_)
		{
		  myDelayedParticleRecords.push_back(new DelayedParticleRecord(it->second, NormalizationReference, LevelReference, ParentReference, QValueReference));
		}
	      else if(toFlush==GammaRecord_)
		{
		  myGammaRecords.push_back(new GammaRecord(it->second, LevelReference, NormalizationReference, QValueReference));
		}
	      it->second.clear();
	    }
	}
    }
}

void Dataset::initRecordStack()
{
  myRecordStack[IdentificationRecord_];
  myRecordStack[HistoryRecord_];
  myRecordStack[CrossReferenceRecord_];
  myRecordStack[CommentRecord_];
  myRecordStack[ParentRecord_];
  myRecordStack[NormalizationRecord_];
  myRecordStack[ProductionNormalizationRecord_];
  myRecordStack[LevelRecord_];
  myRecordStack[BetaMinusRecord_];
  myRecordStack[BetaPlusRecord_];
  myRecordStack[AlphaRecord_];
  myRecordStack[DelayedParticleRecord_];
  myRecordStack[GammaRecord_];
}

Dataset::Dataset(list<string> textToInput)
{
  initRecordStack();
  for(list<string>::iterator it = textToInput.begin(); it!=textToInput.end();it++)
    {
      string local = *it;
      if(local[6]==' ' && local[7]==' ' && local[8]==' ') //IdentificationRecord
	{
	  if(local[5]==' ')
	    {
	      flushAllStacksExcept(0);
	    }
	  else
	    {
	      if(myRecordStack[IdentificationRecord_].empty())
		throw DataFileException("No IdentificationRecord to continue: \n" + local);
	      flushAllStacksExcept(1,IdentificationRecord_);
	    }
	  myRecordStack[IdentificationRecord_].push_back(local);
	}     
      else if(local[6]==' ' && local[7]=='H' && local[8]==' ') //HistoryRecord
	{
	  if(local[5]==' ')
	    {
	      flushAllStacksExcept(0);
	    }
	  else
	    {
	      if(myRecordStack[HistoryRecord_].empty())
		throw DataFileException("No HistoryRecord to continue: \n" + local);
	    }
	  myRecordStack[HistoryRecord_].push_back(local);
	}
      else if(local[6]== ' ' && local[7]=='Q' && local[8]==' ') //QValueRecord
	{
	  if(local[5]==' ')
	    {
	      flushAllStacksExcept(0);
	    }
	  else
	    {
	      if(myRecordStack[QValueRecord_].empty())
		throw DataFileException("No QValueRecord to continue: \n" + local);
	      flushAllStacksExcept(1,QValueRecord_);
	    }
	  myRecordStack[QValueRecord_].push_back(local);
	}
      else if(local[6]==' ' && local[7]=='X') //CrossReferenceRecord
	{
	  if(local[5]==' ')
	    {
	      flushAllStacksExcept(0);
	    }
	  else
	    {
	      if(myRecordStack[CrossReferenceRecord_].empty())
		throw DataFileException("No CrossReferenceRecord to continue: \n" + local);
	    }
	  myRecordStack[CrossReferenceRecord_].push_back(local);
	}
      else if((local[6]=='C' || local[6]=='D' || local[6]=='T' || local[6]=='c' || local[6]=='d' || local[6]=='t')) //Comment record
	{
	  if(local[5]==' ')
	    {
	      flushSpecific(CommentRecord_);
	    }
	  else
	    {
	      if(myRecordStack[CommentRecord_].empty())
		throw DataFileException("No CommentRecord to continue: \n" + local);
	    }
	  myRecordStack[CommentRecord_].push_back(local);
	}
      else if(local[6]==' ' && local[7]=='P') //Parent record
	{
	  if(local[5]==' ')
	    {
	      flushAllStacksExcept(0);
	    }
	  else
	    {
	      if(myRecordStack[ParentRecord_].empty())
		throw DataFileException("No ParentRecord to continue: \n" + local);
	      flushAllStacksExcept(1,ParentRecord_);
	    }
	  myRecordStack[ParentRecord_].push_back(local);
	}
      else if(local[6]==' ' && local[7]=='N') //NormalizationRecord
	{
	  if(local[5]==' ')
	    {
	      flushAllStacksExcept(0);
	    }
	  else
	    {
	      if(myRecordStack[NormalizationRecord_].empty())
		throw DataFileException("No NormalizationRecord to continue: \n" + local);
	      flushAllStacksExcept(1,NormalizationRecord_);
	    }
	  myRecordStack[NormalizationRecord_].push_back(local);
	}
      else if(local[6]=='P' && local[7]=='N' && local[8]== ' ') //ProductionNormalizationRecord
	{
	  if(local[5]==' ')
	    {
	      flushAllStacksExcept(0);
	    }
	  else
	    {
	      if(myRecordStack[ProductionNormalizationRecord_].empty())
		throw DataFileException("No ProductionNormalizationRecord to continue: \n" + local);
	      flushAllStacksExcept(1,ProductionNormalizationRecord_);
	    }
	  myRecordStack[ProductionNormalizationRecord_].push_back(local);
	}
      else if(local[6]==' ' && local[7]=='L' && local[8]== ' ') //LevelRecord
	{
	  if(local[5]==' ')
	    {
	      flushAllStacksExcept(0);
	    }
	  else
	    {
	      if(myRecordStack[LevelRecord_].empty())
		throw DataFileException("No LevelRecord to continue: \n" + local);
	      flushAllStacksExcept(1,LevelRecord_);
	    }
	  myRecordStack[LevelRecord_].push_back(local);
	}
      else if(local[6]==' ' && local[7]=='B' && local[8]==' ') //BetaMinusRecord
	{
	  if(local[5]==' ')
	    {
	      flushAllStacksExcept(0);
	    }
	  else
	    {
	      if(myRecordStack[BetaMinusRecord_].empty())
		throw DataFileException("No BetaMinusRecord to continue: \n" + local);
	      flushAllStacksExcept(1,BetaMinusRecord_);
	    }
	  myRecordStack[BetaMinusRecord_].push_back(local);
	}
      else if(local[6]==' ' && local[7]=='E' && local[8]==' ') //BetaPlusRecord
	{
	  if(local[5]==' ')
	    {
	      flushAllStacksExcept(0);
	    }
	  else
	    {
	      if(myRecordStack[BetaPlusRecord_].empty())
		throw DataFileException("No BetaPlusRecord to continue: \n" + local);
	      flushAllStacksExcept(1,BetaPlusRecord_);
	    }
	  myRecordStack[BetaPlusRecord_].push_back(local);
	}
      else if(local[6]==' ' && local[7]=='A' && local[8]==' ') //AlphaRecord
	{
	  if(local[5]==' ')
	    {
	      flushAllStacksExcept(0);
	    }
	  else
	    {
	      if(myRecordStack[AlphaRecord_].empty())
		throw DataFileException("No AlphaRecord to continue: \n" + local);
	      flushAllStacksExcept(1,AlphaRecord_);
	    }
	  myRecordStack[AlphaRecord_].push_back(local);
	}
      else if(local[6]==' ' && (local[7]=='D' || local[7]==' ') && (local[8]=='N' || local[8]=='P' || local[8]=='A')) //DelayedParticleRecord
	{
	  if(local[5]==' ')
	    {
	      flushAllStacksExcept(0);
	    }
	  else
	    {
	      if(myRecordStack[DelayedParticleRecord_].empty())
		throw DataFileException("No DelayedParticleRecord to continue: \n" + local);
	      flushAllStacksExcept(1,DelayedParticleRecord_);
	    }
	  myRecordStack[DelayedParticleRecord_].push_back(local);
	}
      else if(local[6]==' ' && local[7]=='G' && local[8]==' ') //GammaRecord
	{
	  if(local[5]==' ')
	    {
	      flushAllStacksExcept(0);
	    }
	  else
	    {
	      if(myRecordStack[GammaRecord_].empty())
		throw DataFileException("No GammaRecord to continue: \n" + local);
	      flushAllStacksExcept(1,GammaRecord_);
	    }
	  myRecordStack[GammaRecord_].push_back(local);
	}
      else if(local[3]==' ' && local[4]==' ' && local[5]==' ' && local[6]==' ' && local[7]=='R' && local[8]==' ') //ReferenceRecord
	{
	  myRecordStack[CrossReferenceRecord_].push_back(local);
	  flushAllStacksExcept(0);
	}
      else //if this occurs, we either have a) a file error or b) an error in this software. Either way, throw an exception.
	{
	  throw DataFileException("Invalid entry detected in data files: \n" + local);
	}
    }
  flushAllStacksExcept(0);
  initRecords();
  initBetaRecords();
}

void Dataset::initBetaRecords()
{
  for(list<BetaMinusRecord* >::iterator it = myBetaMinusRecords.begin(); it!=myBetaMinusRecords.end(); it++)
    {
      myBetaRecords.push_back(*it);
    }
  
  for(list<BetaPlusRecord* >::iterator it = myBetaPlusRecords.begin(); it!=myBetaPlusRecords.end(); it++)
    {
      myBetaRecords.push_back(*it);
    }
}

list<Record *> Dataset::getRecords() const
{
  return myRecords;
}

list<BetaRecordWrapper *> Dataset::getBetaRecords() const
{
  return myBetaRecords;
}

void Dataset::initRecords()
{

  for(list<IdentificationRecord* >::iterator it = myIdentificationRecords.begin(); it!=myIdentificationRecords.end(); it++)
    {
      myRecords.push_back(*it);
    }
  for(list<HistoryRecord* >::iterator it = myHistoryRecords.begin(); it!=myHistoryRecords.end(); it++)
    {
      myRecords.push_back(*it);
   } 
  for(list<CrossReferenceRecord* >::iterator it = myCrossReferenceRecords.begin(); it!=myCrossReferenceRecords.end(); it++)
    {
      myRecords.push_back(*it);
    }
  for(list<CommentRecord* >::iterator it = myCommentRecords.begin(); it!=myCommentRecords.end(); it++)
    {
      myRecords.push_back(*it);
    }
  for(list<ParentRecord* >::iterator it = myParentRecords.begin(); it!=myParentRecords.end(); it++)
    {
      myRecords.push_back(*it);
    }
  for(list<NormalizationRecord* >::iterator it = myNormalizationRecords.begin(); it!=myNormalizationRecords.end(); it++)
    {
      myRecords.push_back(*it);
    }
  for(list<ProductionNormalizationRecord* >::iterator it = myProductionNormalizationRecords.begin(); it!=myProductionNormalizationRecords.end(); it++)
    {
      myRecords.push_back(*it);
    }
  for(list<LevelRecord* >::iterator it = myLevelRecords.begin(); it!=myLevelRecords.end(); it++)
    {
      myRecords.push_back(*it);
    }
  for(list<BetaMinusRecord* >::iterator it = myBetaMinusRecords.begin(); it!=myBetaMinusRecords.end(); it++)
    {
      myRecords.push_back(*it);
    }
  for(list<BetaPlusRecord* >::iterator it = myBetaPlusRecords.begin(); it!=myBetaPlusRecords.end(); it++)
    {
      myRecords.push_back(*it);
    }
  for(list<AlphaRecord* >::iterator it = myAlphaRecords.begin(); it!=myAlphaRecords.end(); it++)
    {
      myRecords.push_back(*it);
    }
  for(list<DelayedParticleRecord* >::iterator it = myDelayedParticleRecords.begin(); it!=myDelayedParticleRecords.end(); it++)
    {
      myRecords.push_back(*it);
    }
}

list<IdentificationRecord* > Dataset::getIdentificationRecords() const
{
  return myIdentificationRecords;
}

list<HistoryRecord* > Dataset::getHistoryRecords() const
{
  return myHistoryRecords;
}

list<CrossReferenceRecord* > Dataset::getCrossReferenceRecords() const
{
  return myCrossReferenceRecords;
}

list<CommentRecord* > Dataset::getCommentRecords() const
{
  return myCommentRecords;
}

list<ParentRecord* > Dataset::getParentRecords() const
{
  return myParentRecords;
}

list<NormalizationRecord* > Dataset::getNormalizationRecords() const
{
  return myNormalizationRecords;
}

list<ProductionNormalizationRecord* > Dataset::getProductionNormalizationRecords() const
{
  return myProductionNormalizationRecords;
}

list<LevelRecord* > Dataset::getLevelRecords() const
{
  return myLevelRecords;
}

list<BetaMinusRecord* > Dataset::getBetaMinusRecords() const
{
  return myBetaMinusRecords;
}

list<BetaPlusRecord* > Dataset::getBetaPlusRecords() const
{
  return myBetaPlusRecords;
}

list<AlphaRecord* > Dataset::getAlphaRecords() const
{
  return myAlphaRecords;
}

list<DelayedParticleRecord* > Dataset::getDelayedParticleRecords() const
{
  return myDelayedParticleRecords;
}

list<GammaRecord* > Dataset::getGammaRecords() const
{
  return myGammaRecords;
}

list<ReferenceRecord* > Dataset::getReferenceRecords() const
{
  return myReferenceRecords;
}
