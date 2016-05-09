#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TChain.h"
#include "TString.h"
#include "TROOT.h"

bool massCompare(int gl1, int lsp1, int gl2, int lsp2);

//Sort the sytematics files in case of incorrect Mgl Mlsp sorting.
//Sort the sytematics files in case of incorrect scan point sorting (single value).
void SortSystematicFile( TString in1 = "btagEff_T1bbbb_SIG.txt", int signal = 1) { 

  ifstream f1;
  f1.open( in1 );

  if ( !( f1.good() ) ) { cout << " File is corrupt!" << endl; return;  } 

  cout << endl << "Sorting " << in1 << endl;

  ofstream out, outs;
  out.open( in1 + ".sorted" ); 
  outs.open( in1 + ".original" );

  char dum1[2000];
  vector<string> vals;

  while( f1.getline(dum1,2000,'\n')  ) {
    //Print out to file to make another copy of original file.
    outs << dum1 << endl;
    string str1(dum1);
    vals.push_back(str1);
  }

  if ( signal == 1 ) {
    //The actual sort
    int a, b = 0;
    bool swapped = true;
    string temp;
    while (swapped) {
      swapped = false;
      b++;
      for (a = 0; a < vals.size()-b; a++) {
        istringstream iss1(vals[a]);
        istringstream iss2(vals[a+1]);     
        int gl1, lsp1;
        int gl2, lsp2;
        iss1 >> gl1 >> lsp1;  
        iss2 >> gl2 >> lsp2; 
        if ( massCompare(gl1,lsp1,gl2,lsp2)  ) {
          temp = vals[a];
          vals[a] = vals[a+1];
          vals[a+1] = temp;
          swapped = true;
        }
      }   
    }//end swap
  }// SMS
  if ( signal == 2 ) {
    //The actual sort
    int a, b = 0;
    bool swapped = true;
    string temp;
    while (swapped) {
      swapped = false;
      b++;
      for (a = 0; a < vals.size()-b; a++) {
        istringstream iss1(vals[a]);
        istringstream iss2(vals[a+1]);     
        int s1, s2;
        iss1 >> s1 ;  
        iss2 >> s2 ; 
        if ( s1 > s2 ) {
          temp = vals[a];
          vals[a] = vals[a+1];
          vals[a+1] = temp;
          swapped = true;
        }
      }   
    }//end swap
  }// pMSSM

  //Print out sorted values to sorted file.
  for ( vector<string>::iterator itr=vals.begin(); itr!=vals.end(); itr++) out << *itr << endl;

  f1.close();
  out.close();
  outs.close();
  return;
}

//Returns whether the second pair is 'smaller' than the first.
//So:
// 750 200 700 200 is true
// 750 200 750 250 is false
bool massCompare(int gl1, int lsp1, int gl2, int lsp2) {

  bool res;
  if ( gl1 > gl2 ) res = false;
  if ( gl1 < gl2 ) res = true;
  if ( gl1 == gl2 ) {
    if ( lsp1 > lsp2 ) res = false;
    else if ( lsp1 < lsp2 ) res = true;
  }  

  return !res;
}

