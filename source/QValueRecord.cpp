#include "QValueRecord.h"

using namespace std;

QValueRecord::QValueRecord(list<string> cardArg)
  :Record(cardArg)
{
  processCard();
}

void QValueRecord::processCard()
{
  QValue = cardToDouble(10, 19);
}

bool QValueRecord::operator== (const QValueRecord &other) const
{
  return ((getNukleid()==other.getNukleid())&&(QValue==other.QValue));
}

double QValueRecord::getQValue() const
{
  return QValue;
}
