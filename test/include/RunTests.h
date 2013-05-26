/** \file RunTests.h
    \author Rikard Lundmark
    \brief Header for the unit test program, executes unit tests.
    \ingroup UnitTests
*/

/** \file RunTests.cpp
    \author Rikard Lundmark
    \brief The unit test program, executes unit tests.
    \ingroup UnitTests
*/

/** @defgroup UnitTests Unit tests
 *  Unit tests for the ENSDF++ software.
 \author Rikard Lundmark
 \todo Create more unit tests
 */


using namespace std;
#ifndef ASSERT_H
#define ASSERT_H
#include <assert.h>
#endif

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef LIST
#define LIST
#include <list>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

#include "GenericUnitTest.h"
#include "DataFileException_TEST.h"
#include "Dataset_TEST.h"
#include "ENSDF_TEST.h"
#include "GenericUnitTest.h"
#include "Isotop_TEST.h"
#include "Record_TEST.h"

#ifndef RUNTESTS_H
#define RUNTESTS_H
int main();//!<The main test function and program entry point.
void addTests(); //!<Called by main() to prepare the test cases.
list<GenericUnitTest*> myTests; //!<The existing test cases.
#endif
