#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TChain.h"
#include "TString.h"
#include "TROOT.h"
#include "MyUtils.C"

string getBin( int n ) ;

//If file lines are mismatched, put the one with MORE lines first
void CompareSystematicNumbers( TString in1 = "btagEff_T1bbbb_SIG.txt", TString in2 = "btagEff_T1bbbb_SIG.txt" , TString outfile = "out", double cutoff = 10.0 ) { 

  //Choose the percent to cut at points above it for potential inspection
  //cutoff = 10.0;
  
  ifstream f1, f2;
  f1.open( in1 );
  f2.open( in2 );

  if ( !( f1.good() && f2.good()) ) { cout << " Files are corrupt!" << endl; return;  } 

  cout << endl << "Comparing " << GetNameFromPath(in1) << endl;

  //Overall difference and special for looking at particular threshold of difference.
  ofstream out, outs;
  TString outname = outfile + "_"; 
  outname += cutoff;
  outname += "_PercentDiff.txt";
  out.open( outfile + ".txt" );
  outs.open( outname );

  int mgl1, mlsp1;
  int mgl2, mlsp2;
  double b1, b2;
  char dump[200]; 
  char dum1[2000], dum2[2000];
  int loc;
  int massMatch = 0;

  while( f1.getline(dum1,2000,'\n')  ) {
    
    istringstream iss_f1(dum1); 
    iss_f1 >> mgl1 >> mlsp1;

    loc = f2.tellg();
    f2.getline(dum2,2000,'\n');
    istringstream iss_f2(dum2);
    iss_f2 >> mgl2 >> mlsp2;
    if ( mgl1 !=mgl2 && mlsp1 != mlsp2 ) {
      f2.seekg(loc);
      printf("%4i %4i AND %4i %4i don't match!!\n",mgl1,mlsp1,mgl2,mlsp2);
      //cout << mgl1 << " " <<  mlsp1 << " AND " << mgl2 << "  " << mlsp2 << "  don't match!!" << endl; 
      continue;
    } 
    int binCount = 0;  
    bool massFlag = true;

    out << mgl1 << "    " << mlsp1;
    while ( iss_f1 >> b1 ) {
      iss_f2 >> b2;
      binCount++;
      double diff = b1-b2;
      double per;
      if ( b1 == 0.0 ) 
        if ( diff == 0.0 )
          per = 0.0;
        else   
          per = 3.14159; // Somethings wrong, so put in this very unique number that is unlikely to appear naturally. 
      else per = diff/b1*100.;
      sprintf(dump, "  %8.5f ", per);
      out << dump;
      if ( fabs(per) > cutoff ) { 
        sprintf(dump, "%4i %4i at Bin: %s [%2i] with diff of %9.3f% \n", mgl1, mlsp2, getBin(binCount).c_str(), binCount, per);
        outs << dump;
        if ( massFlag ) {
          massMatch++;
          massFlag = false;
        }
      }
    }
    out << endl;
  }
  cout << "There were " << massMatch << " mass pairs that had a difference of (>=)" << cutoff << "% (as specified)." << endl << endl;

  f1.close();
  f2.close();
  out.close();
  outs.close();
  return;
}

string getBin( int n ) {
  
  string bins[48] = {
  "nb1,M1,H1","nb1,M1,H2","nb1,M1,H3","nb1,M1,H4","nb1,M2,H1","nb1,M2,H2","nb1,M2,H3","nb1,M2,H4","nb1,M3,H1","nb1,M3,H2","nb1,M3,H3","nb1,M3,H4","nb1,M4,H1","nb1,M4,H2","nb1,M4,H3","nb1,M4,H4",
  "nb2,M1,H1","nb2,M1,H2","nb2,M1,H3","nb2,M1,H4","nb2,M2,H1","nb2,M2,H2","nb2,M2,H3","nb2,M2,H4","nb2,M3,H1","nb2,M3,H2","nb2,M3,H3","nb2,M3,H4","nb2,M4,H1","nb2,M4,H2","nb2,M4,H3","nb2,M4,H4",
  "nb3,M1,H1","nb3,M1,H2","nb3,M1,H3","nb3,M1,H4","nb3,M2,H1","nb3,M2,H2","nb3,M2,H3","nb3,M2,H4","nb3,M3,H1","nb3,M3,H2","nb3,M3,H3","nb3,M3,H4","nb3,M4,H1","nb3,M4,H2","nb3,M4,H3","nb3,M4,H4"
  };

  return bins[n-1];

}

 
