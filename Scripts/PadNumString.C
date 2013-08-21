
#include <iostream>
#include <sstream>
#include <string>
#include "TMath.h"

void PadNumString( int num , int maxVal = 1000) {

  stringstream sstr;
  int digits = TMath::Log10(num);
  int padVal = TMath::Log10(maxVal) + 1;
  
  for( int i = 0; i < (padVal-digits); i++ ) 
    sstr << '0';
 
  sstr << num;
  cout << sstr.str() << endl;
  
  return;
}

