
#include <iostream>
#include <fstream>
#include <sstream>
#include <string> 
#include <TString.h>

using namespace std;

//Simple file converted to csv
void VariablesToExcel(TString inFile  = "in.txt") {

  ifstream in;
  ofstream out;

  // Oh the gymnastics... *sigh* 
  // There has to be a better way but string and TString just don't play that well together.
  string inFileCopy(inFile);
  TString outFile;
  TString inFileCopy2(inFile);
  int pos = inFileCopy.find("_");
  outFile = inFileCopy2(0,pos);
  outFile += ".csv";

  in.open(inFile);
  out.open(outFile);

  TString dum;
  char instuff[500];

  while ( in.getline(instuff,500,'\n')  ) {
    
   istringstream iss(instuff);
   while (iss >> dum) {
     out << dum << " , ";  
   }  
   out << dum << " , " << endl;

  }

  in.close();
  out.close();
 
} //end main
