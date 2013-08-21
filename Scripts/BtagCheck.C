#include <iostream>
#include <fstream>
#include <sstream>

#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TChain.h"
#include "TString.h"
#include "TROOT.h"

void BtagCheck(TString first = "", TString second = ""  ) {

  TChain tree1("reducedTree");
  tree1.Add ( first ) ;
  TChain tree2("reducedTree");
  tree2.Add (second ) ;

  if( tree1.GetEntries() != tree2.GetEntries() ) {
    cout << " Entries do not match!" << endl << "Now exiting." << endl;
    return;
  }

  int entries = tree1.GetEntries(); 

  // Data type must be the same as the leaf. 
  float p0_1, p1_1, p2_1;
  float p0_2, p1_2, p2_2;
  p0_1 = 0;
  p1_1 = 0;
  p2_1 = 0;
  p0_2 = 0;
  p1_2 = 0;
  p2_2 = 0;

  tree1.SetBranchAddress("prob0", &p0_1);
  tree1.SetBranchAddress("prob1", &p1_1);
  tree1.SetBranchAddress("prob2", &p2_1);
  tree2.SetBranchAddress("prob0", &p0_2);
  tree2.SetBranchAddress("prob1", &p1_2);
  tree2.SetBranchAddress("prob2", &p2_2);

  for (int e = 0; e < entries; e++) { 

    tree1.GetEntry(e);
    tree2.GetEntry(e);  
 
  //  cout << p0_1 << " as compared to " << p0_2 << endl; 
  //  cout << p1_1 << " as compared to " << p1_2 << endl; 
  //  cout << p2_1 << " as compared to " << p2_2 << endl; 
   double diff0 = ( p0_1/p0_2 - 1 )*100;
   double diff1 = ( p1_1/p1_2 - 1 )*100;
   double diff2 = ( p2_1/p2_2 - 1 )*100;

   if ( diff0 >0.1 || diff1 >0.1 || diff2 >0.1 )
     cout << e << " " << diff0 << " " << diff1 << " " << diff2 << endl;

  }


}

