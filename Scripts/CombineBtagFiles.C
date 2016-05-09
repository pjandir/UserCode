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

void CombineBtagFiles( TString sig = "btagEff_T1bbbb_SIG.txt", TString sl = "btagEff_T1bbbb_SL.txt", TString ldp = "btagEff_T1bbbb_LDP.txt" , TString slsig = "btagEff_T1tttt_SLSIG.txt", TString outfile = "out.txt" ) { 

  ifstream isig, ildp, isl, islsig;
  isig.open( sig );
  ildp.open( ldp );
  isl.open( sl );
  islsig.open ( slsig ); 
  if ( !islsig.good()  )  cout << "Warning: " << slsig << "(aka SLSIG) not being added." << endl;
  bool flag = islsig.good();

  ofstream out;
  out.open( outfile );

  int mgl, mlsp;
  double bsig, bldp, bsl, bslsig;
  int dum1, dum2;
  char dump[200]; 
  char in[2000];

  while( isig.getline(in,2000,'\n')  ) {
    istringstream iss_sig(in); 
    iss_sig >> mgl >> mlsp;
    out << mgl << "     " << mlsp << "    ";
    while ( iss_sig >> bsig ) {
      sprintf(dump, "  %6.3f ", bsig);
      out << dump;
    }

    if ( flag ) { 
      cout << "*" ;
      islsig.getline(in,2000,'\n');
      istringstream iss_slsig(in);
      iss_slsig >> dum1 >> dum2;
      while ( iss_slsig >> bslsig ) {
        sprintf(dump, "  %6.3f ", bslsig);
        out << dump;
      }
    }

    isl.getline(in,2000,'\n');
    istringstream iss_sl(in);
    iss_sl >> dum1 >> dum2;
    while ( iss_sl >> bsl ) {
      sprintf(dump, "  %6.3f ", bsl);
      out << dump;
    }
    ildp.getline(in,2000,'\n');
    istringstream iss_ldp(in);
    iss_ldp >> dum1 >> dum2;
    while ( iss_ldp >> bldp ) {
      sprintf(dump, "  %6.3f ", bldp);
      out << dump;
    }
    cout << "." ;
    out << endl;
  }
  cout << endl;

  isig.close();
  ildp.close();
  isl.close();
  out.close();
  return;
}

