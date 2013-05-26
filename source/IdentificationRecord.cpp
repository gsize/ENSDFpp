#include "IdentificationRecord.h"

IdentificationRecord::IdentificationRecord(list<string> cardArg)
  :Record(cardArg)
{
  processCard();
}

void IdentificationRecord::processCard()
{
  string card = getCardStrings().front();
  DSID = card.substr(9, 30);
  references = card.substr(39, 26);
  publicationInformation = card.substr(65, 9);
  date = card.substr(74, 6);
}

string IdentificationRecord::getDate() const
{
  return date;
}

string IdentificationRecord::getDSID() const
{
  return DSID;
}

string IdentificationRecord::getPublicationInformation() const
{
  return publicationInformation;
}

string IdentificationRecord::getReferences() const
{
  return references;
}
