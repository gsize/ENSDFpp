#include "ElementLookupTable.h"

ElementLookupTable::ElementLookupTable()
{
  myTable["H"]=1;
  myTable["HE"]=2;
  myTable["LI"]=3;
  myTable["BE"]=4;
  myTable["B"]=5;
  myTable["C"]=6;
  myTable["N"]=7;
  myTable["O"]=8;
  myTable["F"]=9;
  myTable["NE"]=10;
  myTable["NA"]=11;
  myTable["MG"]=12;
  myTable["AL"]=13;
  myTable["SI"]=14;
  myTable["P"]=15;
  myTable["S"]=16;
  myTable["CL"]=17;
  myTable["AR"]=18;
  myTable["K"]=19;
  myTable["CA"]=20;
  myTable["SC"]=21;
  myTable["TI"]=22;
  myTable["V"]=23;
  myTable["CR"]=24;
  myTable["MN"]=25;
  myTable["FE"]=26;
  myTable["CO"]=27;
  myTable["NI"]=28;
  myTable["CU"]=29;
  myTable["ZN"]=30;
  myTable["GA"]=31;
  myTable["GE"]=32;
  myTable["AS"]=33;
  myTable["SE"]=34;
  myTable["BR"]=35;
  myTable["KR"]=36;
  myTable["RB"]=37;
  myTable["SR"]=38;
  myTable["Y"]=39;
  myTable["ZR"]=40;
  myTable["NB"]=41;
  myTable["MO"]=42;
  myTable["TC"]=43;
  myTable["RU"]=44;
  myTable["RH"]=45;
  myTable["PD"]=46;
  myTable["AG"]=47;
  myTable["CD"]=48;
  myTable["IN"]=49;
  myTable["SN"]=50;
  myTable["SB"]=51;
  myTable["TE"]=52;
  myTable["I"]=53;
  myTable["XE"]=54;
  myTable["CS"]=55;
  myTable["BA"]=56;
  myTable["LA"]=57;
  myTable["CE"]=58;
  myTable["PR"]=59;
  myTable["ND"]=60;
  myTable["PM"]=61;
  myTable["SM"]=62;
  myTable["EU"]=63;
  myTable["GD"]=64;
  myTable["TB"]=65;
  myTable["DY"]=66;
  myTable["HO"]=67;
  myTable["ER"]=68;
  myTable["TM"]=69;
  myTable["YB"]=70;
  myTable["LU"]=71;
  myTable["HF"]=72;
  myTable["TA"]=73;
  myTable["W"]=74;
  myTable["RE"]=75;
  myTable["OS"]=76;
  myTable["IR"]=77;
  myTable["PT"]=78;
  myTable["AU"]=79;
  myTable["HG"]=80;
  myTable["TL"]=81;
  myTable["PB"]=82;
  myTable["BI"]=83;
  myTable["PO"]=84;
  myTable["AT"]=85;
  myTable["RN"]=86;
  myTable["FR"]=87;
  myTable["RA"]=88;
  myTable["AC"]=89;
  myTable["TH"]=90;
  myTable["PA"]=91;
  myTable["U"]=92;
  myTable["NP"]=93;
  myTable["PU"]=94;
  myTable["AM"]=95;
  myTable["CM"]=96;
  myTable["BK"]=97;
  myTable["CF"]=98;
  myTable["ES"]=99;
  myTable["FM"]=100;
  myTable["MD"]=101;
  myTable["NO"]=102;
  myTable["LR"]=103;
  myTable["RF"]=104;
  myTable["DB"]=105;
  myTable["SG"]=106;
  myTable["BH"]=107;
  myTable["HS"]=108;
  myTable["MT"]=109;
  myTable["DS"]=110;
  myTable["RG"]=111;
  myTable["CN"]=112;
  myTable["UUT"]=113;
  myTable["UUQ"]=114;
  myTable["UUP"]=115;
  myTable["UUH"]=116;
  myTable["UUS"]=117;
  myTable["UUO"]=118;
}

//returns 0 if element is non-existent.
unsigned short int ElementLookupTable::lookupElement(string elementToLookup)
{
  stringToUpper(elementToLookup);
  if(myTable.find(elementToLookup)!=myTable.end())
    return myTable[elementToLookup];
  else
    return 0;
}


void ElementLookupTable::stringToUpper(string& s)
{
  std::string::iterator i = s.begin();
  std::string::iterator end = s.end();
  
  while (i != end) {
    *i = std::toupper((unsigned char)*i);
    ++i;
  }
}
