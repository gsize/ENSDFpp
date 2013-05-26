/**\file BetaStablePrinter.h
   \author Rikard Lundmark
   \brief Header file for the small program BetaStablePrinter, see BetaStablePrinter.cpp for more information.
*/

/**\file BetaStablePrinter.cpp
   \author Rikard Lundmark
   \brief Source file for the small program BetaStablePrinter.
   \section purpose Purpose
   The purpose of the BetaStablePrinter is to print Beta stable isotopes to a file in order to display these in a nucleid chart. Since 2012-05-02 this is not entirely correct, since also alpha stability is taken into account.

*/

using namespace std;
#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef LIST
#define LIST //!<Inclusion guard
#include <list>
#endif

#include "MassTable.h"
#include "MassObject.h"
#include "Nukleid.h"
#include "HalfLifeEstimator.h"

int main(); //!<Main function in this short program.
