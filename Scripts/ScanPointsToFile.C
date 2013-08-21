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
void ScanPointsToFile(TString in = "", TString mod = "" ) {

  TDatime time1;
  string name = GetSampleName( in ); 
  string signal = GetSignalType( in ) ; 
  TString outname = "allScanPoints_" + name;
  if ( mod != "" ) { outname += "_" ; outname += mod; }
  outname += ".txt";

  TChain tree("reducedTree");
  tree.Add ( in ) ;

  if ( tree.IsZombie() ) { cout << "File is corrupt." << endl; return;  } 

  ofstream ofs;
  ofs.open( outname );


  //---------------------------------------------------------------
  // Leafs from the tree
  // Data type must be the same as the leaf. 
  int m0, m12, m3;
  ULong64_t runNumber;

  m0 = 0;
  m12 = 0;
  m3 = 0;
  runNumber = 0;

  //m0:mGl m12:mLsp m3:mIntermediary
  tree.SetBranchAddress("m0", &m0);
  tree.SetBranchAddress("m12", &m12);
  tree.SetBranchAddress("mIntermediate", &m3);
  tree.SetBranchAddress("runNumber", &runNumber);
  //---------------------------------------------------------------
  
  int entries = tree.GetEntries(); 
  cout << endl << "There are " << entries << " entries in input tree for " << name << endl; 

  int tenp = TMath::Nint( entries/10. ) ; 
  int onep = TMath::Nint( entries/100. ) ; 
  int tenthp = TMath::Nint( entries/1000. ) ; 
  vector<string> lists;

  cout << endl <<  "Scanning " << endl;
  for (int e = 0; e < entries; e++) { 

    tree.GetEntry(e);
    int val = e/tenp;
    if ( e%tenthp==0 && (e!=0 ) ) { printf(".") ; cout << flush ; }
    if ( e%tenp==0 && (e!=0) ) { TDatime ti; int dif = ti.Convert() - time1.Convert(); printf(" %i0%% Time elapsed: %02.f:%02.0f \n",val,dif/60,dif%60); cout << flush; } 

    char dum[1000];
    double rtmp = runNumber;
    double m1tmp = m0;
    double m2tmp = m12;   
    double m3tmp = m3;

    if ( signal == "pMSSM" ) {
      int log = (int) TMath::Log10(rtmp);
   
      // Pad numbers to sort correctly 
      if ( log == 0 ) sprintf(dum,"0000%.0f",rtmp);
      if ( log == 1 ) sprintf(dum,"000%.0f",rtmp);
      if ( log == 2 ) sprintf(dum,"00%.0f",rtmp);
      if ( log == 3 ) sprintf(dum,"0%.0f",rtmp);
      if ( log == 4 ) sprintf(dum,"%.0f",rtmp);
    } 

    if ( signal == "SMS" ) {
      char dum1[1000], dum2[100], dum3[100];
      int log1 = (int) TMath::Log10(m1tmp);
      int log2 = (int) TMath::Log10(m2tmp);
      int log3 = (int) TMath::Log10(m3tmp);

      // Pad numbers to sort correctly
      if ( log1 == 0 ) sprintf(dum1,"0000%.0f",m1tmp); 
      if ( log1 == 1 ) sprintf(dum1,"000%.0f",m1tmp); 
      if ( log1 == 2 ) sprintf(dum1,"00%.0f",m1tmp); 
      if ( log1 == 3 ) sprintf(dum1,"0%.0f",m1tmp); 
      if ( log1 == 4 ) sprintf(dum1,"%.0f",m1tmp); 

      if ( log2 == 0 ) sprintf(dum2,"0000%.0f",m2tmp); 
      if ( log2 == 1 ) sprintf(dum2,"000%.0f",m2tmp); 
      if ( log2 == 2 ) sprintf(dum2,"00%.0f",m2tmp); 
      if ( log2 == 3 ) sprintf(dum2,"0%.0f",m2tmp); 
      if ( log2 == 4 ) sprintf(dum2,"%.0f",m2tmp);

      if ( log3 == 0 ) sprintf(dum3,"0000%.0f",m3tmp); 
      if ( log3 == 1 ) sprintf(dum3,"000%.0f",m3tmp); 
      if ( log3 == 2 ) sprintf(dum3,"00%.0f",m3tmp); 
      if ( log3 == 3 ) sprintf(dum3,"0%.0f",m3tmp); 
      if ( log3 == 4 ) sprintf(dum3,"%.0f",m3tmp); 
      
      // Depending on signal model.. 
      if ( name == "T1t1t"  || name == "T1ttcc" ) { 
        sprintf(dum,"%s  %s",dum3,dum2);
      }
      else if ( name == "T5tttt" || name == "T7btw" ) { 
        sprintf(dum,"%s  %s",dum1,dum3);
      }
      else {
        sprintf(dum,"%s  %s",dum1,dum2);
      }
 
    }

    string temp(dum);
    lists.push_back(temp);

  }// end of entries 
  cout << endl << "Done " << endl << endl;

  cout << "Sorting and outputting.." << endl;
  set<string> sorted;
  unsigned int len = lists.size();
  for ( unsigned int i = 0; i < len ; i++ ) { 
    sorted.insert( lists[i]  ); 
  } 

  
  if ( signal == "pMSSM" ) {
    for ( set<string>::iterator itr = sorted.begin(); itr != sorted.end(); itr++) {
      stringstream sstr(*itr);
      double res;
      sstr >> res;
      ofs << res << endl;
    }
  }
  if ( signal == "SMS" ) {
    for ( set<string>::iterator itr = sorted.begin(); itr != sorted.end(); itr++) {
      stringstream sstr(*itr);
      double mg,ml;
      sstr >> mg >> ml;
      ofs << mg << " " <<  ml  << endl;
    }
  }

  //Diagnostic.. 
  //for ( set<string>::iterator itr = sorted.begin(); itr != sorted.end(); itr++) {
  // cout << *itr << "," ;
  //}
  //cout << endl << endl;
  lists.clear();
  sorted.clear();
  TDatime time2;
  int t = time2.Convert() - time1.Convert();

  printf("Time it took to run this program: %02.0f:%02.0f:%02.0f\n", t/3600, (t/60)%60, t%60);

}//end of function


