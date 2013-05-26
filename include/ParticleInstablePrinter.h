/**\file ParticleInstablePrinter.h
   \author Rikard Lundmark
   \brief Header file for the small program ParticleInstablePrinter, see ParticleInstablePrinter.cpp for more information.
*/

/**\file ParticleInstablePrinter.cpp
   \author Rikard Lundmark
   \brief Source file for the small program ParticleInstablePrinter.
   \section purpose Purpose
   The purpose of the ParticleInstablePrinter is to print particle instable isotopes to a file in order to display these in a nucleid chart.
*/


using namespace std;
#ifndef STDIO_H
#define STDIO_H //!<Inclusion guard.
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

int main(); //!<Main function.
