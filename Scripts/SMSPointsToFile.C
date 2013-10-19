#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TChain.h"
#include "TString.h"
#include "TROOT.h"
#include "MyUtils.C"

//Input reducedTree signal samples to extract all scan points to txt file
//Many things are hardcoded..
void SMSPointsToFile(TString in = "", TString mod = "" ) {

  TDatime time1;
  string name = GetSampleName( in ); 
  string signal = GetSignalType( in ) ; 
  TString outname = "allScanPoints_" + name;
  if ( mod != "" ) { outname += "_" ; outname += mod; }
  outname += ".txt";

  TChain ch("reducedTree");
  ch.Add(in);
  if ( ch.IsZombie() ) { cout << "File is zombie" << endl; return; }

  ofstream ofs;
  ofs.open( outname );

  cout << "Sample is " << name << " which is of type " << signal << endl << endl;
  cout << "Points will be written out to " << outname << " .. " << endl ;

  //Histogram dimensions are hardcoded.. careful for the future. 
  TH2D * h = new TH2D("h","h",2000,0,2000,2000,0,2000);
  char dim = 'z';  

  // Depending on signal model, we want different m0,m12,mIntermediate 
  if ( name == "T1t1t"  || name == "T1ttcc" ) { 
    dim = 'x';
    ch.Project("h","mIntermediate:m12",""); 
  }
  else if ( name == "T5tttt" || name == "T7btw" ) { 
    dim = 'y'; 
    ch.Project("h","mIntermediate:m0",""); 
  }
  else {
    //Default. Most SMS scans follow this..
    ch.Project("h","m12:m0",""); 
  }

  cout << endl <<  "Scanning " << endl;

  double dum = 1;
  int found = 0;
  for ( int ix = 1; ix<=h->GetXaxis()->GetNbins(); ix++) {
    for ( int iy = 1; iy<=h->GetYaxis()->GetNbins() ; iy++) {
      double val=0;
      if       (dim=='z') val=h->GetBinContent(ix,iy,dum);
      else  if (dim=='y') val=h->GetBinContent(ix,dum,iy);
      else  if (dim=='x') val=h->GetBinContent(dum,iy,ix);
 
      if ( val != 0 ) {
        found++;
        ofs << ix-1 << "   " << iy-1 << endl;
        //ofs << ix-1 << "\t" << iy-1 << endl;
      }
    }
  }
  cout << endl << endl << "Found " << found << " points.. done. " << endl << endl;
  h->Clear();

  TDatime time2;
  int t = time2.Convert() - time1.Convert();

  printf("Time it took to run this program: %02.0f:%02.0f:%02.0f\n", t/3600, (t/60)%60, t%60);

}//end of function

