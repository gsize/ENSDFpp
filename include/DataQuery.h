/**\file DataQuery.h
   \brief Header file for the DataQuery class.
   \author Rikard Lundmark
*/
/**\file DataQuery.cpp
   \brief Source file for the DataQuery class.
   \author Rikard Lundmark
*/


using namespace std;

#include "ENSDF.h"

#ifndef DATAQUERY_H
#define DATAQUERY_H //!<Inclusion guard.

/**Extended by any class wanting to implement a dataquery towards the ENSDF database. Doesn't do very much at the moment.

   \author Rikard Lundmark
 */

class DataQuery: public VerbosePrinterEventEnabled
{
 protected:
  const ENSDF * myENSDF; //!<An ENSDF object.
};
#endif
