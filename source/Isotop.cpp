#include "Isotop.h"

Isotop::Isotop(list < list<string> > indata)
{
  for(list< list<string> >::iterator it = indata.begin(); it!=indata.end(); ++it)
    {
      try
	{
	  myDatasets.push_back(new Dataset(*it));
	}
      catch(exception &ex)
	{
	  throw DataFileException(ex.what());
	}
    }
  for(list<Dataset*>::iterator it = myDatasets.begin(); it!=myDatasets.end(); it++)
    {
      list<IdentificationRecord* > myIdentificationRecords = (*it)->getIdentificationRecords();
      if(!myIdentificationRecords.empty())
	{
	  myNukleid = myIdentificationRecords.front()->getNukleid();
	}
    }
}

Isotop::~Isotop()
{
  for(list<Dataset* >::iterator it = myDatasets.begin(); it!=myDatasets.end(); it++)
    {
      delete *it;
      *it=NULL;
    }
  myDatasets.clear();
}

list<Dataset* > Isotop::getDatasets() const
{
  return myDatasets;
}

Nukleid Isotop::getNukleid() const
{
  return myNukleid;
}
