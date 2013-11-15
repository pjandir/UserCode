#include <iostream>
#include <fstream>
#include <sstream>

#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TChain.h"
#include "TString.h"
#include "TROOT.h"

//input paths to the two reducedTrees
void checkMET(TString first = "", TString second = ""  ) {
  TDatime time1;

  TChain tree1("reducedTree");
  tree1.Add( first ) ;
  TChain tree2("reducedTree");
  tree2.Add( second ) ;

  if( tree1.IsZombie() || tree2.IsZombie() ) { cout << "File(s) is zombie." << endl; return; }
  if( tree1.GetEntries() != tree2.GetEntries() ) { cout << " Entries do not match!" << endl << "Now exiting." << endl; return; }

  int entries = tree1.GetEntries(); 

  cout << endl << "There are " << entries << " to be analyzed." << endl << endl;

  // Data type must be the same as the leaf. 
  float MET1, MET2;
  // Must initialize!
  MET1 = 0;
  MET2 = 0;

  // Set those variables to the variable name in the tree
  tree1.SetBranchAddress("MET", &MET1);
  tree2.SetBranchAddress("MET", &MET2);

  int tenp = TMath::Nint( entries/10. ) ; 
  int onep = TMath::Nint( entries/100. ) ; 
  int tenthp = TMath::Nint( entries/1000. ) ; 

  for (int e = 0; e < entries; e++) { 

    int val = e/tenp;
    if ( e%tenthp==0 && (e!=0 ) ) { printf(".") ; cout << flush ; }
    if ( e%tenp==0 && (e!=0) ) { TDatime ti; int dif = ti.Convert() - time1.Convert(); printf(" %i0%% Time elapsed: %02.f:%02.0f \n",val,dif/60,dif%60); cout << flush; } 

    tree1.GetEntry(e);
    tree2.GetEntry(e);  
 
    float diff = ( MET1 - MET2 );

    if ( diff > 0.0001 ) //There are better ways to do this 
      cout << "Uh-oh "  << e << "  " << MET1 << " " << MET2 << endl; 
  }//end loop

  TDatime time2;
  int t = time2.Convert() - time1.Convert();

  printf("\nTime it took to run this program: %02.0f:%02.0f:%02.0f\n", t/3600, (t/60)%60, t%60);


}

