

#include "TMath.h"

void GetString( int num ) { 

  string str;
  char ret[100];
  int flag = TMath::Log10(num);
  if ( flag == 0 ) { 
    sprintf(ret,"0000%i",num);
  }
  else if ( flag == 1 ) { 
    sprintf(ret,"000%i",num);
  }
  else if ( flag == 2 ) { 
    sprintf(ret,"00%i",num);
  }
  else if ( flag == 3 ) { 
    sprintf(ret,"0%i",num);
  }

  //cout << num << "'s log10 is " << flag << " and the return val is " << ret << endl;
  //cout the answer
  cout << ret << endl;
  return;
}

