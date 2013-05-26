/**\file MassPrinter.h
   \author Rikard Lundmark
   \brief Header file for the MassPrinter class, see MassPrinter.cpp for more information.
*/
/**\file MassPrinter.cpp
   \author Rikard Lundmark
   \brief Source file for the MassPrinter class.
   \section purpose Purpose
   The purpose of the MassPrinter is to print the masses of all isotopes in the mass.mas03 file, in order to prepare a nucleid chart.
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

int main(); //!<Main function in this short program.
