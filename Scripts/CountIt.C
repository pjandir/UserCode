
#include <iostream>
#include <fstream>
#include <sstream>
#include <string> 
#include <TString.h>

using namespace std;

//Input a rawCounts_SMS_MODEL_SEARCH_REGION.txt file to sum up all search region numbers.
//In other words, one should get back the total number of events from generator level.
void CountIt(TString inFile  = "in.txt") {

  ifstream in; 
  in.open(inFile);

  if ( !in.good() ) { cout << "File is corrupt." << endl; return; } 

  // Oh the gymnastics... *sigh* 
  // There has to be a better way but string and TString just don't play that well together.
  string inFileCopy(inFile);
  TString outFile;
  TString inFileCopy2(inFile);
  int pos = inFileCopy.find("_");
  outFile = inFileCopy2(0,pos);
  outFile += ".csv";

  ofstream out;
  out.open(outFile);

  TString dum;
  char instuff[10000];
  int mgl, mlsp;
  double d = 0;

  while ( in.getline(instuff,10000,'\n')  ) { 
    double c=0;
    istringstream iss(instuff);
    iss >> mgl >> mlsp;
    while (iss >> dum) {
      out << dum << " , ";  
      c += dum.Atof();
    }   
    out << dum << " , " << endl;
    cout << "total for " <<mgl << " " <<mlsp << " is " << c << endl;
    d+=c; //running total;
  }

  printf("\nTotal number of events in this file (inc all bins, search regions, mass pairs, etc.) is %12.2f.\n",d);

  in.close();
  out.close();
 
} //end main
