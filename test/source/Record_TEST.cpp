#include "Record_TEST.h"

bool Record_TEST::testNukleid() const
{
  ////////////////// Nukleid test ///////////////////
  Nukleid n1("  4HE");
  assert(n1.getElement()=="HE");
  assert(n1.getA()==4);
  
  n1 = Nukleid(" 44HE");
  assert(n1.getElement()=="HE");
  assert(n1.getA()==44);
  
  n1 = Nukleid("444HE");
  assert(n1.getElement()=="HE");
  assert(n1.getA()==444);
  
  n1 = Nukleid("  4H ");
  assert(n1.getElement()=="H");
  assert(n1.getA()==4);
  
  n1 = Nukleid(" 44H ");
  assert(n1.getElement()=="H");
  assert(n1.getA()==44);
  
  n1 = Nukleid("444H ");
  assert(n1.getElement()=="H");
  assert(n1.getA()==444);
  
  Nukleid n2(" 47CA");
  assert(!(n1 == n2));
  
  n2 = Nukleid("444H ");
  assert(n1==n2);
  ///////////////////////////////////////////////////
  return true;
}

bool Record_TEST::testLevelRecord() const
{
  list<string> myList;
  myList.push_back(" 47CA  L 2013.51   103/2-                                                       ");
  LevelRecord level(myList, NULL);
  assert(level.getNukleid().getElement()=="CA");
  assert(level.getNukleid().getA()==47);
  assert(level.getEnergy()==2013.51);
  assert(level.getHalfLife()==-3);
  return true;
}

bool Record_TEST::testGammaRecord() const
{
  list<string> myList;
  myList.push_back(" 47CA  L 2013.51   103/2-                                                       ");
  LevelRecord level(myList,NULL);
  myList.clear();
  myList.push_back(" 47CA  G 2578.26   12 42.2   17 (M2)                                            ");
  GammaRecord gamma(myList, &level, NULL, NULL);
  assert(gamma.getNukleid().getElement()=="CA");
  assert(gamma.getNukleid().getA()==47);
  assert(gamma.getDecayEnergy()==2578.26);
  assert(gamma.getLevelRecord()->getEnergy()==2013.51);
  return true;
}

bool Record_TEST::testNormalizationRecord() const
{
  list<string> myList;
  myList.push_back(" 47CA  N 0.9335    11           1.       0.985   15                             ");
  NormalizationRecord norm(myList, NULL);
  assert(norm.getNukleid().getElement()=="CA");
  assert(norm.getNukleid().getA()==47);
  assert(norm.getBetaMultiplier()==0.985);
  return true;
}

bool Record_TEST::testParentRecord() const
{
  list<string> myList;
  myList.push_back(" 47K   P 0.0         1/2+              17.50 S   24             6644      8     ");
  ParentRecord parent(myList);
  assert(parent.getNukleid().getElement()=="K");
  assert(parent.getNukleid().getA()==47);
  assert(parent.getHalfLife()==17.5);

  list<string> myOtherList;
  myOtherList.push_back("  8B   P 0.0         2+                770 MS    3              17979.8   10    ");
  ParentRecord par(myOtherList);
  assert(par.getNukleid().getElement()=="B");
  assert(par.getNukleid().getA()==8);
  assert(par.getHalfLife()==0.77);

  return true;
}

bool Record_TEST::testBetaMinusRecord() const
{
  
  list<string> myList1, myList2, myList3, myList4;
  myList1.push_back(" 47K   P 0.0         1/2+              17.50 S   24             6644      8     ");
  ParentRecord parent(myList1);
  myList2.push_back(" 47CA  L 2013.51   103/2-                                                       ");
  LevelRecord level(myList2, NULL);
  myList3.push_back(" 47CA  N 0.9335    11           1.       0.985   15                             ");
  NormalizationRecord norm(myList3, &parent);
  myList4.push_back(" 47CA  B             19.0    3           5.46    1                              ");
  BetaMinusRecord beta(myList4, &norm, &level, &parent, NULL);
  assert(beta.getNukleid().getElement()=="CA");
  assert(beta.getNukleid().getA()==47);
  assert(beta.getIntensityOfBetaDecayBranch()==18.715);
  assert(beta.getNormalizationRecord()!=NULL);
  return true;
}

bool Record_TEST::testBetaPlusRecord() const
{  
  list<string> myList1, myList2, myList3, myList4;
  myList1.push_back(" 47K   P 0.0         1/2+              17.50 S   24             6644      8     ");
  ParentRecord parent(myList1);
  myList2.push_back(" 47CA  L 2013.51   103/2-                                                       ");
  LevelRecord level(myList2, NULL);
  myList3.push_back(" 47CA  N 0.9335    11           1.       0.985   15                             ");
  NormalizationRecord norm(myList3, &parent);
  myList4.push_back(" 47CA  E             19.0    3           5.46    1                              ");
  BetaPlusRecord beta(myList4, &norm, &level, &parent,NULL);
  
  assert(beta.getNukleid().getElement()=="CA");
  assert(beta.getNukleid().getA()==47);
  assert(beta.getIntensityOfBetaDecayBranch()==18.715);
  assert(beta.getNormalizationRecord()!=NULL);
  return true;
}



bool Record_TEST::testRecord() const
{
  class TrimExtender: public Record
  {
  public:
    TrimExtender(list<string> toConstructFrom)
      :Record(toConstructFrom)
    {
      
    }
    string trimMYString(string toTrim)
    {
      return trimString(toTrim);
    }
  };
  
  list<string> tt;
  tt.push_back(" 92TC");
  TrimExtender myExtender(tt);
  assert(myExtender.trimMYString(" DIN MAMMA ").compare("DIN MAMMA")==0);
  return true;
}

bool Record_TEST::testLevelHalfLife() const
{
  list<string> myList;
  myList.push_back(" 92TC    ADOPTED LEVELS, GAMMAS                                  NDS00    200101");
  myList.push_back(" 92TC  H TYP=FUL$AUT=CORAL M. BAGLIN$CIT=NDS 91, 423 (2000)$CUT=7-Nov-2000$     ");
  myList.push_back(" 92TC  Q -4.53E+3  SY11.02E3 20 4020   28              1995AU04                 ");
  myList.push_back(" 92TC CQ Q-        Uncertainty=300 KEV (1995AU04).                              ");
  myList.push_back(" 92TC C  {UOther Reactions}:                                                    ");
  myList.push_back(" 92TC C  46TI(54FE,5p3n|g), E(54FE)=225 MEV (1990ISZY): measured EG,            ");
  myList.push_back(" 92TC2C  GG coin; searched for ns isomers; attributed a 257G-500G-1347G         ");
  myList.push_back(" 92TC3C  cascade to 92TC, implying levels at 1347, 1847 and 2104. None of       ");
  myList.push_back(" 92TC4C  these transitions has been confirmed in subsequent (40CA,5PNG) or      ");
  myList.push_back(" 92TC5C  (35CL,4P3NG) studies, and the evaluator does not adopt them as         ");
  myList.push_back(" 92TC6C  transitions in 92TC. Furthermore, 1995GH02 have reassigned all         ");
  myList.push_back(" 92TC7C  three transitions to 94RU.                                             ");
  myList.push_back(" 92TC C                                                                         ");
  myList.push_back(" 92TC C  For shell-model calculations see, e.g., 1974GR36, 1976SE01, 1976GR07,  ");
  myList.push_back(" 92TC2C  1992SI15, 1995GH02, 1996TU03.                                          ");
  myList.push_back(" 92TC CL           The adopted level scheme is based on that of 1994AR33 in     ");
  myList.push_back(" 92TC2CL (40CA,5PNG). However, the evaluator has adopted several of the         ");
  myList.push_back(" 92TC3CL modifications suggested by 1995GH02 in (35CL,4P3NG): (i) the order     ");
  myList.push_back(" 92TC4CL of the 663 and 636 cascade gammas has been reversed, so the weaker G   ");
  myList.push_back(" 92TC5CL lies higher in the cascade; (ii) the 1786G is placed so it directly    ");
  myList.push_back(" 92TC6CL feeds the (15+) 3588 level (an alternative placement given by 1994AR33)");
  myList.push_back(" 92TC7CL because 1995GH02 suggest that a 627G (not the 1786G) lies immediately  ");
  myList.push_back(" 92TC8CL above the 2058G, and the placement is shown as tentative because       ");
  myList.push_back(" 92TC9CL the 1786G was not observed by 1995GH02; (iii) an 1108G-1938G           ");
  myList.push_back(" 92TCACL cascade is added feeding the (17-) 4787 level (as in 1995GH02) but,    ");
  myList.push_back(" 92TCBCL owing to the strength of the 1108G in 1995GH02, the evaluator allows   ");
  myList.push_back(" 92TCCCL that it may be a doublet there and retains 1994AR33's placement of an  ");
  myList.push_back(" 92TCDCL 1108G from the (15-) 4048 level; (iv) the 1986G is placed feeding      ");
  myList.push_back(" 92TCECL the (15-) 4048 level (as in 1995GH02), instead of the (16-) 4716 level ");
  myList.push_back(" 92TCFCL (1994AR33); (v) addition of 1015.2G, 1051.6G. Additional               ");
  myList.push_back(" 92TCGCL inconsistencies between the level schemes of 1994AR33 and 1995GH02     ");
  myList.push_back(" 92TCHCL center on whether there are two levels near 2002 KEV and whether the   ");
  myList.push_back(" 92TCICL 647G is a doublet (see comment on E(2002 levels)).                     ");
  myList.push_back(" 92TC CL           See 1994AR33, 1995GH02, 1996TU03 for further discussion of   ");
  myList.push_back(" 92TC7CL possible configuration assignments for 92TC levels.                    ");
  myList.push_back(" 92TC CL E         From least-squares adjustment of EG, allowing 1 KEV          ");
  myList.push_back(" 92TC2CL uncertainty in E|g data for which authors did not quote uncertainty,   ");
  myList.push_back(" 92TC3CL except for levels excited only in (3HE,T).                             ");
  myList.push_back(" 92TC CG M         From G anisotropy ratio and reaction systematics in          ");
  myList.push_back(" 92TC2CG (40CA,5PNG), except when noted otherwise.                              ");
  myList.push_back(" 92TC CG MR        From G(|q) in (3HE,2NPG).                                    ");
  myList.push_back(" 92TC CG E,RI      From EC decay, except as noted.                              ");
  myList.push_back(" 92TC CL BAND(A)   SENIORITY |>4, YRAST PI=+ STATES.                            ");
  myList.push_back(" 92TC2CL Probable configuration=((|p p{-1/2}){+2}(|p g{-9/2}){+3}(|n            ");
  myList.push_back(" 92TC3CL g{-9/2}){+-1}) for J=10 to J|<15 levels (1994AR33).                    ");
  myList.push_back(" 92TC CL BAND(B)   YRAST PI=- STATES.                                           ");
  myList.push_back(" 92TC2CL Probable configuration=((|p p{-1/2})(|p g{-9/2}){+4}(|n g{-9/2}){+-1}) ");
  myList.push_back(" 92TC3CL for J|<17 levels (1994AR33).                                           ");
  myList.push_back(" 92TC CL BAND(C)   CONF=((P,1G9/2)(N,1G9/2,-1)) (1972Ha02).                     ");
  myList.push_back(" 92TC2CL Dominance of this seniority=2 configuration based on population        ");
  myList.push_back(" 92TC3CL in (3HE,T).                                                            ");
  myList.push_back(" 92TC CL J(T)      From (40CA,5PNG), based on G anisotropy and the              ");
  myList.push_back(" 92TC2CL assumptions that all observed |g's have J{-i}|>J{-f}, most have        ");
  myList.push_back(" 92TC3CL J{-i}>J{-f} and that crossover transitions are E2, unless noted        ");
  myList.push_back(" 92TC4CL otherwise.                                                             ");
  myList.push_back(" 92TC CG E(W)      Weighted average from |e decay and (3HE,2NPG).               ");
  myList.push_back(" 92TC CG E(U,V),RI(V)$From (3HE,2NPG).                                          ");
  myList.push_back(" 92TC CG E(X,Y),RI(Y)$From (40CA,5PNG); evaluator assigns                       ");
  myList.push_back(" 92TC2CG authors' upper limit of |DE=1 KEV to EG.                               ");
  myList.push_back(" 92TC CL E(Z)      Two levels at or near 2002 KEV, each deexcited by an         ");
  myList.push_back(" 92TC2CL EG AP 647 KEV transition, are proposed in (40CA,5pn|g) to account      ");
  myList.push_back(" 92TC3CL for observed Doppler splitting of 1355G in coin spectra gated by       ");
  myList.push_back(" 92TC4CL 394G, 485G, 495G, 545G, 622G and 1067G. Alternatively, an              ");
  myList.push_back(" 92TC5CL isomeric                                                               ");
  myList.push_back(" 92TC6CL level slightly above the 2001 level may deexcite to the latter via an  ");
  myList.push_back(" 92TC7CL unobserved, highly converted low-energy transition. However, the       ");
  myList.push_back(" 92TC8CL inconsistency between 647G(|q) in (3HE,2PNG), 647G anisotropy in       ");
  myList.push_back(" 92TC9CL (40CA,5pn|g) and ^DCO ratio in (35CL,4p3n|g) suggests that the         ");
  myList.push_back(" 92TCACL 647G is indeed a doublet whose components deexcite states which have   ");
  myList.push_back(" 92TCBCL been populated to differing extents in the different reactions. The    ");
  myList.push_back(" 92TCCCL evaluator adopts this scenario, even though 1995GH02                   ");
  myList.push_back(" 92TCDCL conclude from their (35CL,4p3n|g) data that the 646G is not a          ");
  myList.push_back(" 92TCECL doublet.                                                               ");
  myList.push_back(" 92TC PN                                                                     6  ");
  myList.push_back(" 92TC  XA92RU EC DECAY                                                          ");
  myList.push_back(" 92TC  XB92MO(3HE,2NPG)                                                         ");
  myList.push_back(" 92TC  XC92MO(3HE,T)                                                            ");
  myList.push_back(" 92TC  XD92MO(P,NG)                                                             ");
  myList.push_back(" 92TC  XE58NI(40CA,5PNG),                                                       ");
  myList.push_back(" 92TC  XF64ZN(35CL,4P3NG)                                                       ");
  myList.push_back(" 92TC  L      0.0    (8)+              4.25 M    15                         C   ");
  myList.push_back(" 92TCX L XREF=ABCDEF                                                            ");
  myList.push_back(" 92TC2 L %EC+%B+=100                                                            ");
  myList.push_back(" 92TC CL J         LOGFT=5.4 for 92TC EC decay to 8+ (89% branch);              ");
  myList.push_back(" 92TC2CL LOGFT=5.7 to 7+; EC decay to 6+ 2612 level is weak or nonexistent;     ");
  myList.push_back(" 92TC3CL |s(|q) systematics in (3HE,T).                                         ");
  myList.push_back(" 92TC CL T         weighted average of 4.5 M 5 (1948MO18), 4.0 M 1 and          ");
  myList.push_back(" 92TC2CL 4.4 M 4 (1964VA05), 4.52 M 12 (1985BE12), using method of              ");
  myList.push_back(" 92TC3CL limitation of relative statistical weights.                            ");
  myList.push_back(" 92TC  L   213.81  10(6+)              1 NS      LT                         C   ");
  myList.push_back(" 92TCX L XREF=ABCD                                                              ");
  myList.push_back(" 92TC CL T         from (P,NG).                                                 ");
  myList.push_back(" 92TC CL J         5,6+ from (3HE,T); J=6 based on Hauser-Feshbach analysis in  ");
  myList.push_back(" 92TC2CL (P,NG).                                                                ");
  myList.push_back(" 92TC  G 213.81    10 100      (E2)                    0.0823               W   ");
  myList.push_back(" 92TCB G BE2W>47                                                                ");
  myList.push_back(" 92TC CG M         ^D,E2 from RUL; adopted |DJ=(2).                             ");
  myList.push_back(" 92TC  L   270.15  11(4+)              1.03 US   7                          C   ");
  myList.push_back(" 92TCX L XREF=ABCD                                                              ");
  myList.push_back(" 92TC CL J         3+,4+ from (3HE,T); J=4 based on Hauser-Feshbach analysis in ");
  myList.push_back(" 92TC2CL (P,NG); E2 G to J=(6) level.                                           ");
  myList.push_back(" 92TC CL T         from (P,NG).                                                 ");
  myList.push_back(" 92TC  G 56.34      2 100      E2                      9.9                      ");
  myList.push_back(" 92TCB G BE2W=3.6 3                                                             ");
  myList.push_back(" 92TC CG M         from ECC, 92RU EC decay.                                     ");
  myList.push_back(" 92TC  L 389.25    23(5+)                                                   C   ");
  myList.push_back(" 92TCX L XREF=BCD                                                               ");
  myList.push_back(" 92TC CL J         5,6+ from (3HE,T); J=5 based on Hauser-Feshbach analysis in  ");
  myList.push_back(" 92TC2CL (P,NG); PI=+ probable, by analogy to 88Y and 90NB.                     ");
  myList.push_back(" 92TC  G 119.1      2 100       [M1]                   0.172                U   ");
  myList.push_back(" 92TC  L   529.47  15(3+)              0.1 US    LE                         C   ");
  myList.push_back(" 92TCX L XREF=ABCD                                                              ");
  myList.push_back(" 92TC CL J         259G is ^D to (4+); 2241G from 1+ 2771; 3+,4+ from (3HE,T);  ");
  myList.push_back(" 92TC2CL JPI=1,2-,3+ based on Hauser-Feshbach analysis in (P,NG).               ");
  myList.push_back(" 92TC CL T         from 92RU EC decay.                                          ");
  myList.push_back(" 92TC  G 259.32    12 100      (M1)                    0.0216               W   ");
  myList.push_back(" 92TCB G BM1W>1.2E-5                                                            ");
  myList.push_back(" 92TC CG M         259G is ^D from (3HE,2NPG); adopted DPI=(no).                ");
  myList.push_back(" 92TC  L   576.93  15(2+)              2 NS      LT                         C   ");
  myList.push_back(" 92TCX L XREF=ABCD                                                              ");
  myList.push_back(" 92TC CL J         134G is ^D from 1+ 711; M1 47G to (3+).                      ");
  myList.push_back(" 92TC CL T         from (P,NG).                                                 ");
  myList.push_back(" 92TC  G 47.46      3100     10 M1                     2.37                     ");
  myList.push_back(" 92TCB G BM1W>0.030                                                             ");
  myList.push_back(" 92TC CG M         from ECC, 92RU EC decay.  ^D from RUL.                       ");
  myList.push_back(" 92TC  G 306.8      2 1.14   11 (E2)                   0.0237                   ");
  myList.push_back(" 92TC CG M         ^D,E2 from RUL; level scheme requires DJ=2 and DPI=no.       ");
  myList.push_back(" 92TC  L 626.4      3(4,6+)                                                     ");
  myList.push_back(" 92TCX L XREF=B                                                                 ");
  myList.push_back(" 92TC CL J         J=(4,6) from DJ=1 237G to (5+) 389; 6+ favored by shell-model");
  myList.push_back(" 92TC2CL calculations (1976SE01) which predict a                                ");
  myList.push_back(" 92TC3CL configuration=((|p g{-9/2}){+3}7/2 ~# (|n g{-9/2}){+-1})6+ level       ");
  myList.push_back(" 92TC4CL near this energy (1983FI08).                                           ");
  myList.push_back(" 92TC  G 237.1      2 100      D                                            U   ");
  myList.push_back(" 92TC CG M         DJ=1 from G(|q) in (3HE,2NPG).                               ");
  myList.push_back(" 92TC  L 686.14    17(9+)                                                   C   ");
  myList.push_back(" 92TCX L XREF=BCEF                                                              ");
  myList.push_back(" 92TC CL J         from (3HE,T); 686G is ^D to (8)+.                            ");
  myList.push_back(" 92TC  G 686.2      2 100      (M1)                                         U   ");
  myList.push_back(" 92TC CG M         ^D from (40CA,5PNG) and (3HE,2NPG); level scheme.            ");
  myList.push_back(" 92TC  L   711.39  16 1+               0.1 US    LE                             ");
  myList.push_back(" 92TCX L XREF=ABD                                                               ");
  myList.push_back(" 92TC CL J         from LOGFT=4.9 from 0+ 92RU parent.                          ");
  myList.push_back(" 92TC CL T         from 92RU EC decay.                                          ");
  myList.push_back(" 92TC  G 134.57     8 100      (M1)                    0.123                W   ");
  myList.push_back(" 92TCB G BM1W>8.0E-5                                                            ");
  myList.push_back(" 92TC CG M         ^D from (3HE,2NPG); adopted DPI=(no).                        ");
  myList.push_back(" 92TC  L 965.7      3(6+)                                                       ");
  myList.push_back(" 92TCX L XREF=BC                                                                ");
  myList.push_back(" 92TC CL J         ^D 576G to (5+), but J probably not 5, from G(|q) in         ");
  myList.push_back(" 92TC2CL (3HE,2NPG); 5,6+ favored in (3HE,T).                                   ");
  myList.push_back(" 92TC  G 576.4      2 100       D                                           U   ");
  myList.push_back(" 92TC CG M         DJ=1 from G(|q) in (3HE,2NPG).                               ");
  myList.push_back(" 92TC  L 1119.4     4                                                           ");
  myList.push_back(" 92TCX L XREF=B                                                                 ");
  myList.push_back(" 92TC CL J         G to J=(4,6+) 626 level. See comment on J(1129 level).       ");
  myList.push_back(" 92TC  G 493.0      2 100                                                   U   ");
  myList.push_back(" 92TC  L 1129      20 LE 3                                                      ");
  myList.push_back(" 92TCX L XREF=C                                                                 ");
  myList.push_back(" 92TC CL J         from (3HE,T). If J(626 level) were 4, this level would       ");
  myList.push_back(" 92TC2CL presumably correspond to 1119 level in (3HE,2NPG) whose J would        ");
  myList.push_back(" 92TC3CL then be limited to (2,3).                                              ");
  myList.push_back(" 92TC  L  1161.97  17 (0+,1)                                                    ");
  myList.push_back(" 92TCX L XREF=AB                                                                ");
  myList.push_back(" 92TC CL J         G from 1+; LOGFT=6.3 3 (LOGF1UT=7.6 2) FOR WEAK EC BRANCH    ");
  myList.push_back(" 92TC2CL FROM 0+; 585G to (2+) 577. POSSIBLE CANDIDATE FOR 0+ ANTI-ANALOG STATE ");
  myList.push_back(" 92TC3CL (1976SE01).                                                            ");
  myList.push_back(" 92TC  G 450.7      1100      3                                                 ");
  myList.push_back(" 92TC  G 585.0      2 8.6    10                                                 ");
  myList.push_back(" 92TC  L 1163.7    11                                                           ");
  myList.push_back(" 92TCX L XREF=B                                                                 ");
  myList.push_back(" 92TC CL J         G ray to (6+).                                               ");
  myList.push_back(" 92TC  G 198         100                                                    U   ");
  myList.push_back(" 92TC  L 1222      20LE3                                                        ");
  myList.push_back(" 92TCX L XREF=C                                                                 ");
  myList.push_back(" 92TC CL J         from (3HE,T).                                                ");
  myList.push_back(" 92TC  L 1324      25LE3                                                        ");
  myList.push_back(" 92TCX L XREF=C                                                                 ");
  myList.push_back(" 92TC CL J         from (3HE,T).                                                ");
  myList.push_back(" 92TC  L 1355.48   17(10+)                                                  A   ");
  myList.push_back(" 92TCX L XREF=BEF                                                               ");
  myList.push_back(" 92TC CL J         ^D G to (9+); (E2) G to (8)+; PI=(+) based on branching in   ");
  myList.push_back(" 92TC2CL (3HE,2NPG); yrast selectivity in (3HE,2NPG) favors J=10.               ");
  myList.push_back(" 92TC  G 669.4      2 29      3 D                                           V   ");
  myList.push_back(" 92TC CG M         from G(|q) in (3HE,2NPG).                                    ");
  myList.push_back(" 92TC  G 1355.4     2 100    11(E2)                                         V   ");
  myList.push_back(" 92TC CG M         Q from (40CA,5pn|g) and (3HE,2NPG); level scheme.            ");
  myList.push_back(" 92TC  L  1443.92  181+                                                         ");
  myList.push_back(" 92TCX L XREF=AC(1453)                                                          ");
  myList.push_back(" 92TC CL J         from LOGFT=5.2 from 0+ parent; (1+,2+,4-) from               ");
  myList.push_back(" 92TC2CL (3HE,T).                                                               ");
  myList.push_back(" 92TC  G 867.0      1 100                                                       ");
  myList.push_back(" 92TC  L  1487.25  17 LE 3                                                      ");
  myList.push_back(" 92TCX L XREF=A                                                                 ");
  myList.push_back(" 92TC CL J         G to (2+); G from 1+.                                        ");
  myList.push_back(" 92TC  G 910.2      1 100                                                       ");
  myList.push_back(" 92TC  L 1502.92   23(6,8+)                                                     ");
  myList.push_back(" 92TCX L XREF=B                                                                 ");
  myList.push_back(" 92TC CL J         |DJ=0 or 2 to (6+) in (3HE,2NPG); branching and IG favor     ");
  myList.push_back(" 92TC2CL PI=+ if J=8 (1983FI08).                                                ");
  myList.push_back(" 92TC  G 1289.1     2 100                                                   U   ");
  myList.push_back(" 92TC  L 1589.2     4(7,8)                                                      ");
  myList.push_back(" 92TCX L XREF=B                                                                 ");
  myList.push_back(" 92TC CL J         G to J LE 6; G(|q) in (3HE,2NPG) allows J=4 to 8 if          ");
  myList.push_back(" 92TC2CL J(626 level)=6, but strong population in (3HE,2NPG) favors high        ");
  myList.push_back(" 92TC3CL spin (1983FI08).                                                       ");
  myList.push_back(" 92TC  G 962.8      2 100                                                   U   ");
  myList.push_back(" 92TC  L 1613      25LE 3                                                       ");
  myList.push_back(" 92TCX L XREF=C                                                                 ");
  myList.push_back(" 92TC CL J         from (3HE,T).                                                ");
  myList.push_back(" 92TC  L  1796.60  171+                                                         ");
  myList.push_back(" 92TCX L XREF=A                                                                 ");
  myList.push_back(" 92TC CL J         from LOGFT=5.1 from 0+ 92RU parent.                          ");
  myList.push_back(" 92TC  G 634.8      5 4.6     6                                                 ");
  myList.push_back(" 92TC  G 1219.6     1 100     5                                                 ");
  myList.push_back(" 92TC  L  1980.54  18 LE 3                                                      ");
  myList.push_back(" 92TCX L XREF=A                                                                 ");
  myList.push_back(" 92TC CL J         G rays to 1+ and (2+).                                       ");
  myList.push_back(" 92TC  G 1268.9     3 21      3                                                 ");
  myList.push_back(" 92TC  G 1403.6     2 100     6                                                 ");
  myList.push_back(" 92TC  L 2001.8    11 (12+)                                                 A   ");
  myList.push_back(" 92TCX L XREF=EF                                                                ");
  myList.push_back(" 92TCF L FLAG=TZ                                                                ");
  myList.push_back(" 92TC  G  646.3    10 100                                                   X   ");
  myList.push_back(" 92TC CG E,M       G unresolved from ^D 647.2G in (40CA,5pn|g) where            ");
  myList.push_back(" 92TC2CG anisotropy of doublet is consistent with stretched Q; thus, mult=Q is  ");
  myList.push_back(" 92TC3CG favored for this component.                                            ");
  myList.push_back(" 92TC  L 2002.7     3(11-)             3.15 NS   20                         B   ");
  myList.push_back(" 92TCX L XREF=BE                                                                ");
  myList.push_back(" 92TC2 L MOMM1=8.87 22 (1996TU03)                                               ");
  myList.push_back(" 92TCF L FLAG=Z                                                                 ");
  myList.push_back(" 92TC CL MOMM1     from g-factor=0.806 20 measured using TDPAD, assuming        ");
  myList.push_back(" 92TC2CL J=11.                                                                  ");
  myList.push_back(" 92TC CL J         measured g-factor is close to that calculated for a          ");
  myList.push_back(" 92TC2CL configuration=((|p p{-1/2})(|p g{-9/2}){+4}(|n g{-9/2}){+-1}) state,   ");
  myList.push_back(" 92TC3CL and to that known for analogous 11- state in 90NB (1996TU03).          ");
  myList.push_back(" 92TC CL T         from time differential perturbed angular distribution        ");
  myList.push_back(" 92TC2CL in (28SI,p3n|g) (1996TU03). Other ^T{-1/2}: 1.9 NS 4 (DSAM, after      ");
  myList.push_back(" 92TC3CL corrections for prompt component and deorientation effects; 1994AR33). ");
  myList.push_back(" 92TC  G 647.2      2 100       (E1+M2)  +0.10   3                              ");
  myList.push_back(" 92TCB G BE1W=3.85E-7 25$BM2W=0.04 3                                            ");
  myList.push_back(" 92TC CG E         from (3HE,2NPG); EG given as 646.8 10 in                     ");
  myList.push_back(" 92TC2CG (40CA,5PNG) for unresolved component of doublet.                       ");
  myList.push_back(" 92TC CG M,MR      from G(|q) in (3HE,2NPG); however, 647G is a doublet in      ");
  myList.push_back(" 92TC2CG (40CA,5PNG), so MR may not be reliable. E1 is favored                  ");
  myList.push_back(" 92TC3CG over M1 because BM1W=2.55|*10{+-5} 17 would be atypically              ");
  myList.push_back(" 92TC4CG small.                                                                 ");
  myList.push_back(" 92TC  L   2107.0   4 1+                                                        ");
  myList.push_back(" 92TCX L XREF=A                                                                 ");
  myList.push_back(" 92TC CL J         from LOGFT=5.1 from 0+ parent.                               ");
  myList.push_back(" 92TC  G 945.0      3 100                                                       ");
  myList.push_back(" 92TCL G FL=1161.97                                                             ");
  myList.push_back(" 92TC  L  2316.08  19 1+                                                        ");
  myList.push_back(" 92TCX L XREF=A                                                                 ");
  myList.push_back(" 92TC CL J         from LOGFT=4.8 from 0+ parent.                               ");
  myList.push_back(" 92TC  G 1604.7     1 100     4                                                 ");
  myList.push_back(" 92TC  G 1738.5     5  8.9   18                                                 ");
  myList.push_back(" 92TC  L  2390.98  17 1+                                                        ");
  myList.push_back(" 92TCX L XREF=A                                                                 ");
  myList.push_back(" 92TC CL J         from LOGFT=4.1 from 0+ parent.                               ");
  myList.push_back(" 92TC  G 410.4      1 19.5    4                                                 ");
  myList.push_back(" 92TC  G 594.3      2 6.4     7                                                 ");
  myList.push_back(" 92TC  G 903.6      1 8.5     5                                                 ");
  myList.push_back(" 92TC  G 947.2      3 29      3                                                 ");
  myList.push_back(" 92TC  G 1229.1     1 36.5   21                                                 ");
  myList.push_back(" 92TC  G 1679.6     1 100     4                                                 ");
  myList.push_back(" 92TC  G 1814.0     6 2.1     5                                                 ");
  myList.push_back(" 92TC  L 2548.9     4(12-)                                                  B   ");
  myList.push_back(" 92TCX L XREF=BEF                                                               ");
  myList.push_back(" 92TC CL J         ^D+Q G to (11-) with MR favoring M1+E2; J{-i}>J{-f} likely   ");
  myList.push_back(" 92TC2CL in (40CA,5PNG).                                                        ");
  myList.push_back(" 92TC  G 546.2      2 100      (M1+E2)   -0.18   10                             ");
  myList.push_back(" 92TCL G FL=2002.7                                                              ");
  myList.push_back(" 92TC CG E         from (3HE,2NPG). EG=545.0 10 in (40CA,5PNG).                 ");
  myList.push_back(" 92TC CG M         ^D+Q from G(|q) in (3HE,2NPG); level scheme.                 ");
  myList.push_back(" 92TC  L 2664.7    15 (13+)                                                 A   ");
  myList.push_back(" 92TCX L XREF=E(2638)F                                                          ");
  myList.push_back(" 92TCF L FLAG=T                                                                 ");
  myList.push_back(" 92TC CL E         the adopted order of the 636G-663G cascade is based on IG    ");
  myList.push_back(" 92TC2CL in (35CL,4P3NG); E(level)=2637.6 in (40CA,5PNG) because,               ");
  myList.push_back(" 92TC3CL there, the order of the cascade |g's is reversed.                      ");
  myList.push_back(" 92TC  G  662.9    10 100       D                                           X   ");
  myList.push_back(" 92TCL G FL=2001.8                                                              ");
  myList.push_back(" 92TC  L  2771.02  21 1+                                                        ");
  myList.push_back(" 92TCX L XREF=A                                                                 ");
  myList.push_back(" 92TC CL J         from LOGFT=4.4 from 0+ parent.                               ");
  myList.push_back(" 92TC  G 974.3     2 9.2     14                                                 ");
  myList.push_back(" 92TC  G 2059.7    2 100      6                                                 ");
  myList.push_back(" 92TC  G 2194.3    5 23.3    22                                                 ");
  myList.push_back(" 92TC  G 2241.3    5 7.5     25                                                 ");
  myList.push_back(" 92TC  L 2940.0     4(13-)                                                  B   ");
  myList.push_back(" 92TCX L XREF=BEF                                                               ");
  myList.push_back(" 92TCF L FLAG=T                                                                 ");
  myList.push_back(" 92TC CL J         (12+) suggested in (35CL,4p3n|g).                            ");
  myList.push_back(" 92TC  G 391.1      2 100       D                                               ");
  myList.push_back(" 92TC CG E         from (3HE,2NPG). EG=393.6 10 in (40CA,5PNG), 393             ");
  myList.push_back(" 92TC2CG in (35CL,4p3n|g).                                                      ");
  myList.push_back(" 92TC  L   3004.8   3 1+                                                        ");
  myList.push_back(" 92TCX L XREF=A                                                                 ");
  myList.push_back(" 92TC CL J         from LOGFT=4.5 from 0+ parent.                               ");
  myList.push_back(" 92TC  G 1517.6     3 100     5                                                 ");
  myList.push_back(" 92TC  G 2427.5     5 36      4                                                 ");
  myList.push_back(" 92TC  L   3048.1   3 1+                                                        ");
  myList.push_back(" 92TCX L XREF=A                                                                 ");
  myList.push_back(" 92TC CL J         from LOGFT=4.8 from 0+ parent; G rays to 1+ and (2+) and     ");
  myList.push_back(" 92TC2CL (3+).                                                                  ");
  myList.push_back(" 92TC  G 656.3     10 26     13                                                 ");
  myList.push_back(" 92TC  G 1560.7     5 100    10                                                 ");
  myList.push_back(" 92TC  G 2471.2     3 27      5                                                 ");
  myList.push_back(" 92TC  G 2519.3    10 12      5                                                 ");
  myList.push_back(" 92TC  L 3069.4     7 (13-)                                                 T   ");
  myList.push_back(" 92TCX L XREF=EF                                                                ");
  myList.push_back(" 92TC  G  521.0    10  85    15 D                                           Y   ");
  myList.push_back(" 92TC CG           Other IG: 28 5 in (35CL,4p3n|g), but see comment on          ");
  myList.push_back(" 92TC2CG 1066.7G.                                                               ");
  myList.push_back(" 92TC CG M         from (35CL,4p3n|g).                                          ");
  myList.push_back(" 92TC  G  1066.7   10  100   15 Q                                           Y   ");
  myList.push_back(" 92TCL G FL=2002.7                                                              ");
  myList.push_back(" 92TC CG M         Q from (40CA,5pn|g). ^D from unenumerated ^DCO ratio         ");
  myList.push_back(" 92TC2CG in (35CL,4p3n|g), where I(1067G)/I(521G) is much larger than in        ");
  myList.push_back(" 92TC3CG (40CA,5pn|g); this may indicate that 1067G is a doublet in             ");
  myList.push_back(" 92TC4CG (35CL,4p3n|g).                                                         ");
  myList.push_back(" 92TC  L 3301.0    18 (14+)                                                 A   ");
  myList.push_back(" 92TCX L XREF=EF                                                                ");
  myList.push_back(" 92TCF L FLAG=T                                                                 ");
  myList.push_back(" 92TC  G  636.3    10 100       D                                           X   ");
  myList.push_back(" 92TC CG M         from (35CL,4p3n|g).                                          ");
  myList.push_back(" 92TC  L 3563.4     7 (14-)                                                 B   ");
  myList.push_back(" 92TCX L XREF=EF                                                                ");
  myList.push_back(" 92TCF L FLAG=T                                                                 ");
  myList.push_back(" 92TC  G  494.6        100    8 D                                               ");
  myList.push_back(" 92TC CG E,RI,M    from (35CL,4p3n|g); doublet in (40CA,5PNG).                  ");
  myList.push_back(" 92TC  G  622.2    10  49    LT                                             X   ");
  myList.push_back(" 92TC CG RI        from (35CL,4p3n|g); however, IG>52 10 from                   ");
  myList.push_back(" 92TC2CG (40CA,5PNG).                                                           ");
  myList.push_back(" 92TC CG M         Q (interpreted as M2) in (35CL,4p3n|g), but ^D from          ");
  myList.push_back(" 92TC2CG (40CA,5pn|g). However, if M2 and IG AP 50, ^T{-1/2}(3563 level)        ");
  myList.push_back(" 92TC3CG exceeds |?5 NS (based on RUL).                                         ");
  myList.push_back(" 92TC  G  1015.2      10                                                        ");
  myList.push_back(" 92TC CG E,RI      from (35CL,4p3n|g); not reported in (40CA,5PNG).             ");
  myList.push_back(" 92TC  L 3587.9    20 (15+)                                                 A   ");
  myList.push_back(" 92TCX L XREF=EF                                                                ");
  myList.push_back(" 92TCF L FLAG=T                                                                 ");
  myList.push_back(" 92TC  G  286.9    10 100       D                                           X   ");
  myList.push_back(" 92TC CG M         from (35CL,4p3n|g).                                          ");
  myList.push_back(" 92TC  L   3709.2   4 1+                                                       ?");
  myList.push_back(" 92TCX L XREF=A                                                                 ");
  myList.push_back(" 92TC CL J         LOGFT=4.7 from 0+ parent; G decay to 1+, (2+) levels.        ");
  myList.push_back(" 92TC  G 938.1      4 100    40                                                ?");
  myList.push_back(" 92TC  G 2997.4    10 36     16                                                ?");
  myList.push_back(" 92TC  G 3133.0    10 40     20                                                ?");
  myList.push_back(" 92TC  L 3813      30 0+                                                        ");
  myList.push_back(" 92TCX L XREF=C                                                                 ");
  myList.push_back(" 92TC CL J         from (3HE,T); isobaric analog of 92MO GS.                    ");
  myList.push_back(" 92TC  L 4048.0     9 (15-)                                                 B   ");
  myList.push_back(" 92TCX L XREF=EF                                                                ");
  myList.push_back(" 92TCF L FLAG=T                                                                 ");
  myList.push_back(" 92TC  G  484.6    10  100   11 D                                           Y   ");
  myList.push_back(" 92TC  G  1108.0   10  22     5                                             Y   ");
  myList.push_back(" 92TC CG           Placement from (40CA,5PNG) only.                             ");
  myList.push_back(" 92TC  L 4615.0    12                                                           ");
  myList.push_back(" 92TCX L XREF=F                                                                 ");
  myList.push_back(" 92TC CL J         G to (14-) level.                                            ");
  myList.push_back(" 92TC  G  1051.6      100                                                       ");
  myList.push_back(" 92TC CG E         from (35CL,4p3n|g).                                          ");
  myList.push_back(" 92TC  L 4716.4    12 (16-)                                                 T   ");
  myList.push_back(" 92TCX L XREF=EF                                                                ");
  myList.push_back(" 92TC  G  668.5    10 100                                                   X   ");
  myList.push_back(" 92TC  L 4786.8    23 (17-)                                                 B   ");
  myList.push_back(" 92TCX L XREF=EF                                                                ");
  myList.push_back(" 92TCF L FLAG=T                                                                 ");
  myList.push_back(" 92TC  G   70.6    10  41     7 (M1)                   0.753                Y   ");
  myList.push_back(" 92TC CG M         ^D from (40CA,5PNG); Q crossover G from same level.          ");
  myList.push_back(" 92TC  G  738.6    10  100   15 Q                                           Y   ");
  myList.push_back(" 92TC  L 5373.5    23 (16+,17+)                                             A  ?");
  myList.push_back(" 92TCX L XREF=E                                                                 ");
  myList.push_back(" 92TCF L FLAG=T                                                                 ");
  myList.push_back(" 92TC CL E         an alternative placement of the 1786G (between a 7431-KEV    ");
  myList.push_back(" 92TC2CL (18+,19+) level and the 5646 level) was suggested in (40CA,5PNG);      ");
  myList.push_back(" 92TC3CL however, a 627G? feeds the 5646 level and the 1786G is absent in       ");
  myList.push_back(" 92TC4CL (35CL,4p3n|g).                                                         ");
  myList.push_back(" 92TC  G  1785.6   10 100                                                   X  ?");
  myList.push_back(" 92TC  L 5646.2    23 (17+)                                                     ");
  myList.push_back(" 92TCX L XREF=EF                                                                ");
  myList.push_back(" 92TC CL J         Q G to (15+); possible configuration is                      ");
  myList.push_back(" 92TC2CL ((|p g{-9/2}){+5}25/2+)~#(|n g{-9/2}){+-1} (1994AR33).                 ");
  myList.push_back(" 92TC  G  2058.3   10 100       Q                                           X   ");
  myList.push_back(" 92TC CG M         from (35CL,4p3n|g).                                          ");
  myList.push_back(" 92TC  L 6033.7    13                                                           ");
  myList.push_back(" 92TCX L XREF=EF                                                                ");
  myList.push_back(" 92TC CL E,J       6701.7 25, (17-,18-) in (40CA,5PNG) because, there,          ");
  myList.push_back(" 92TC2CL the 1986G was placed feeding the (16-) 4716 level.                     ");
  myList.push_back(" 92TC  G  1985.6   10 100                                                   X   ");
  myList.push_back(" 92TC  L 6272.9    25                                                          ?");
  myList.push_back(" 92TCX L XREF=F                                                                 ");
  myList.push_back(" 92TC  G  626.7       100                                                      ?");
  myList.push_back(" 92TC CG E         from (35CL,4p3n|g).                                          ");
  myList.push_back(" 92TC  L 6725.2    16 (19-)                                                     ");
  myList.push_back(" 92TCX L XREF=F                                                                 ");
  myList.push_back(" 92TC CL J         from (35CL,4p3n|g); Q G to (17-).                            ");
  myList.push_back(" 92TC  G  1938.4      100       Q                                               ");
  myList.push_back(" 92TC CG E,M       from (35CL,4p3n|g).                                          ");
  myList.push_back(" 92TC  L 7833.1    19 (21-)                                                     ");
  myList.push_back(" 92TCX L XREF=F                                                                 ");
  myList.push_back(" 92TC CL J         Q G to (19-) in (35CL,4p3n|g).                               ");
  myList.push_back(" 92TC  G  1107.9      100       Q                                               ");
  myList.push_back(" 92TC CG           EG from (35CL,4p3n|g). Based on strength of this G, the      ");
  myList.push_back(" 92TC2CG evaluator suggests that it might be a doublet in this reaction.        ");
  
  Dataset myDataset(myList);
  list<LevelRecord *> myLevels = myDataset.getLevelRecords();
  assert(myLevels.size()==51);
  list<LevelRecord*>::iterator it = myLevels.begin();
  assert((*it)->getHalfLife()==255); it++;
  assert((*it)->getHalfLife()==1E-9); it++;
  assert(doubleEquality((*it)->getHalfLife(),1.03E-6)); it++;
  assert((*it)->getHalfLife()<0); it++;
  assert((*it)->getHalfLife()==0.1E-6); it++;
  assert((*it)->getHalfLife()==2E-9); it++;
  assert((*it)->getHalfLife()<0); it++;
  assert((*it)->getHalfLife()<0); it++;
  assert((*it)->getHalfLife()==0.1E-6); it++;
  return true;
}


int Record_TEST::runUnitTests() const
{
  cout << "Testing records...";
  if(!testNukleid())
    return 1;
  if(!testLevelRecord())
    return 2;
  if(!testGammaRecord())
    return 3;
  if(!testNormalizationRecord())
    return 4;
  if(!testParentRecord())
    return 5;
  if(!testBetaMinusRecord())
    return 6;
  if(!testBetaPlusRecord())
    return 7;
  if(!testRecord())
    return 8;
  if(!testLevelHalfLife())
    return 9;
  cout << "done" << endl;
  return 0;
}
