#include "Dataset_TEST.h"

bool Dataset_TEST::Dataset_ConstructsCorrectly_AssertTrue() const
{
  Dataset * myDataset = new Dataset(list<string>());
  delete myDataset;
  return true;
}

bool Dataset_TEST::Dataset_LoadsDatasetCorrectly_AssertTrue() const
{
  list<string> myList;
  myList.push_back(" 27NA    ADOPTED LEVELS                1990EN08                  98NP     200103");
  myList.push_back(" 27NA  H TYP=FUL$AUT=P. M. ENDT, J.BLACHOT, R.B. FIRESTONE, J.ZIPKIN$           ");
  myList.push_back(" 27NA2 H CIT=NP A633, 1 (1998)$CUT=1-Jan-1999$                                  ");
  myList.push_back(" 27NA  H TYP=FUL$AUT=P. M. ENDT$CIT=NP A521,1 (1990)$CUT=1-Jun-1990$            ");
  myList.push_back(" 27NA c  See abstract for special evaluation policies used in the               ");
  myList.push_back(" 27NA2c  A=27 or comments dataset in ENSDF                                      ");
  myList.push_back(" 27NA  Q 9010      406750    4013300   70-11340  90    1995AU04                 ");
  myList.push_back(" 27NA c  From {+26}Mg({+18}O,{+17}F) 1985Fi08                                   ");
  myList.push_back(" 27NA  XA26MG(18O,17F)                                                          ");
  myList.push_back(" 27NA  L 0.0         5/2+               301 MS   6                              ");
  myList.push_back(" 27NA2 L %B-=100 $%B-N=0.13 4$XREF=A                                            ");
  myList.push_back(" 27NA cL T$weighted av from: 280 ms {I20} (1973Al13), 304 ms {I7} (1974Ro31)    ");
  myList.push_back(" 27NA2cL 295 ms {I20} (1986Du07)                                                ");
  myList.push_back(" 27NAB L MOMM1=+3.895 5$MOME2=-0.06 5                                           ");
  myList.push_back(" 27NA  L 1720      40                                                           ");
  myList.push_back(" 27NAX L XREF=A                                                                 ");
  myList.push_back(" 27NA  L 2210      30                                                           ");
  myList.push_back(" 27NAX L XREF=A                                                                 ");
  myList.push_back(" 27NA  L 3820      40                                                           ");
  myList.push_back(" 27NAX L XREF=A                                                                 ");
  myList.push_back(" 27NA  L 4980      50                                                           ");
  myList.push_back(" 27NAX L XREF=A                                                                 ");
  myList.push_back(" 27NA  L 5590      50                                                           ");
  myList.push_back(" 27NAX L XREF=A                                                                 ");
  Dataset myDataset(myList);
  return true;
}

bool Dataset_TEST::Dataset_LoadsMoreRecordTypesCorrectly_AssertTrue() const
{
  list<string> myList;
  myList.push_back(" 27NA    ADOPTED LEVELS, GAMMAS                                  98NP     200906");
  myList.push_back(" 27NA  H TYP=FUL$AUT=M.S. BASUNIA$CUT=1-APR-2009$CIT=ENSDF$                     ");
  myList.push_back(" 27NA  Q 9069      4  6728   5 13286   19-11272  80    2009AUZZ                 ");
  myList.push_back(" 27NA CQ $Q-=9069 4, SN=6726 7, SP=13240 30, QA=-11270 80 2003Au03              ");
  myList.push_back(" 27NA  P 0.0         5/2+              301 MS    6                              ");
  myList.push_back(" 27NA  XF26MG(18O,17F)                                                          ");
  myList.push_back(" 27AL  N                       0.0000134               1.3E-5 4                 ");
  myList.push_back(" 27NA PN                                                                     6  ");
  myList.push_back(" 27NA  L 0.0         5/2+               301 MS   6                          Z   ");
  myList.push_back(" 27NA  G 1728        14      7                                                  ");
  myList.push_back(" 27NA  B             4.2     13            5.54  14                             ");
  myList.push_back(" 27AL  E               99.70520  0.0650 7  3.617425             99.77     2     ");
  Dataset myDataset(myList);
  return true;
}

bool Dataset_TEST::Dataset_CreatesCorrectBetaRecords_AssertTrue() const
{
  list<string> myList;
  myList.push_back("  8LI    8HE B- DECAY                  1986BA66                  04NP     200505");
  myList.push_back("  8LI  H TYP=FUL$AUT=J.H. KELLEY, J.L. GODWIN, C.G. SHEU, ET AL.$               ");
  myList.push_back("  8LI2 H CIT=NP A745, 155 (2004)$CUT=31-Mar-2004$                               ");
  myList.push_back("  8LI D  ADDED NB TO N RECORD AND THE PN RECORD (TWB. 940525)                   ");
  myList.push_back("  8LI D  ADDED MISSING EAV'S (TWB. 980831)                                      ");
  myList.push_back("  8LI C  1981BJ03: 8HE, MEASURED BETA^-DELAYED E{-N}, I{-N}, BG^-COIN, T.       ");
  myList.push_back("  8LI2C  DEDUCED DELAYED NEUTRON BRANCHING, LOGFT.                              ");
  myList.push_back("  8LI C  1986BO41: 8HE(B-), MEASURED BETA^-DELAYED TRITON BRANCHING             ");
  myList.push_back("  8LI2C  RATIOS, SPECTRA. DEDUCED LOGFT.                                        ");
  myList.push_back("  8LI C  1988BA67: 8BE(B-); CALCULATED T, BRANCHING RATIO, DELAYED N, T SPECTRA,");
  myList.push_back("  8LI2C  DEDUCED ^GAMOW^-TELLER MATRIX ELEMENTS. R-MATRIX, SHELL MODEL METHODS. ");
  myList.push_back("  8LI C  1991BO31: 8HE(B-), MEASURED CONTINUUM PARTICLE SPECTRA FOLLOWING       ");
  myList.push_back("  8LI2C  BETA^-DECAY. DEDUCED LOGFT, GAMOW^-TELLER TRANSITION STRENGTH,         ");
  myList.push_back("  8LI3C  WIDTH^-LEVEL, DI^-NEUTRON HALO ROLES.                                  ");
  myList.push_back("  8LI C  1993BO24: 8HE(B-), MEASURED BETA^-DELAYED TRITON, ALPHA^-SPECTRA.      ");
  myList.push_back("  8LI2C  DEDUCED BRANCHING RATIO. 8LI DEDUCED LEVEL. R^-MATRIX ANALYSIS.        ");
  myList.push_back("  8LI C  1996BA66: 8HE(B-); ANALYZED B-DECAY DELAYED TRITON SPECTRA. 8LI LEVELS ");
  myList.push_back("  8LI2C  DEDUCED PARAMETERS, B(^GT), BRANCHING RATIOS, LOGFT, ^R-MATRIX         ");
  myList.push_back("  8LI3C  APPROACH.                                                              ");
  myList.push_back("  8LI CL J,T       FROM ADOPTED LEVELS                                          ");
  myList.push_back("  8HE  P 0.          0+                119.1 MS  12             10651     7     ");
  myList.push_back("  8LI  N 1.                     1.       1.0                                    ");
  myList.push_back("  8LI PN                                                                     3  ");
  myList.push_back("  8LI  L 0.          2+                839.9 MS   6                             ");
  myList.push_back("  8LI  L 980.      1 1+                8.2 FS    23                             ");
  myList.push_back("  8LI  B              84     1           4.20                                   ");
  myList.push_back("  8LIS B EAV=4607 4                                                             ");
  myList.push_back("  8LI  G 980.         84     1                                                  ");
  myList.push_back("  8LI  L 3080         1+               1 MEV     AP                             ");
  myList.push_back("  8LI  B              16     LT          4.52                                   ");
  myList.push_back("  8LI CB           IB(3210+5400 LEVEL)=16 1                                     ");
  myList.push_back("  8LIS B EAV=3567 4                                                             ");
  myList.push_back("  8LI  L 5150         1 +              650 KEV   AP                             ");
  myList.push_back("  8LI  B             16      LT          4.53                                   ");
  myList.push_back("  8LIS B EAV=2543 4                                                             ");
  myList.push_back("  8LI CB           IB(3210+5400 LEVEL)=16 1                                     ");
  myList.push_back("  8LI  L 9670         1+               1 MEV     AP                             ");
  myList.push_back("  8LI  B              0.9    1           2.91                                   ");
  myList.push_back("  8LIS B EAV=384 3                                                              ");
  Dataset myDataset(myList);
  list<BetaRecordWrapper *> myBetas = myDataset.getBetaRecords();
  assert(myBetas.size()==4);
  return true;
}


int Dataset_TEST::runUnitTests() const
{
  cout << "Running unit tests on Dataset...";
  if(!Dataset_ConstructsCorrectly_AssertTrue())
    return 1;
  if(!Dataset_LoadsDatasetCorrectly_AssertTrue())
    return 2;
  if(!Dataset_LoadsMoreRecordTypesCorrectly_AssertTrue())
    return 3;
  if(!Dataset_CreatesCorrectBetaRecords_AssertTrue())
    return 4;
  cout << "done" << endl;
  return 0;
}
