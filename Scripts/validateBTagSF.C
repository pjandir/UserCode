#include <iostream>
#include <fstream>
#include <sstream>

#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TChain.h"
#include "TString.h"
#include "TROOT.h"
#include "MyUtils.C"

void validateBTagSF( TString input1 = "", TString input2 = "" ) {

  bool saveFile = true;

  TChain myChain("reducedTree");
  string sample = GetSampleName(input1);
  TString names[2] = {input1,input2};
  
  gROOT->Reset();
  
  double minLeadJetPt  = 70. ;
  double min3rdJetPt   = 50. ;
  const int nBinsBjets =  3  ;   // this must always be 3
  const int nJetsCut   =  3  ;   // #jets >= nJetsCut
  TString cBbins[nBinsBjets] = {"nbjets==1","nbjets==2","nbjets>=3"};

  //-- met4-ht4-v15
  const int nBinsMET   = 4  ;
  const int nBinsHT    = 4  ;
  const int version    = 15 ;
  float Mbins[nBinsMET+1] = {125.,150.,250.,350. ,99999.} ;
  float Hbins[nBinsHT+1]  = {400.,500.,800.,1000.,99999.} ;
 
//reducedTree.Project(name,"MET","(cutPV==1&&HT>400&&njets>=3&&jetpt1>70&&jetpt2>70&&nElectrons==0&&nMuons==0&&MET>125&&minDeltaPhiN_asin>4&&passCleaning&&MET/caloMET<2&    &maxTOBTECjetDeltaMult<40&&nIsoTracks15_005_03==0&&nbjets==1)*weight2*12000*PUweight*prob1")
 
  TString nominal = "(cutPV==1&&HT>400&&passCleaning";
  TString jetpt = "&&jetpt1>";
  jetpt+= minLeadJetPt;
  jetpt+= "&&jetpt2>";
  jetpt+= minLeadJetPt;
  jetpt+= "&&jetpt3>";
  jetpt+= min3rdJetPt;
  jetpt+= "&&";
  stringstream njcut ; njcut << nJetsCut;
  TString cutsNjets = "&&njets>=";
  cutsNjets += njcut.str();

  TH1F * h1 = new TH1F ("hist","hist",10000,0,1000);
  double res[2][4];//2 files, 4 prob variables  
  ofstream ofs;
  TString dum = sample + "_validation_btagSF.csv";
  if ( saveFile ) { 
    ofs.open(dum);
    ofs << sample << "," << endl;
    ofs << nominal << cutsNjets << jetpt << endl;
    cout << "Doing " << sample << " .. " << endl << endl;
  }
  else cout << "Doing " << sample << " .. and not writing out to file .. " << endl << endl;

  for ( int j = 0; j < 2; j++ ) {
  
    myChain.Add( names[j] );
  
    if ( myChain.IsZombie() ) {
      cout << "File " << names[j] << " failed!!" << endl;
      return;
    }
     
    cout << "Processing File" << j+1 << " : " << names[j] << endl;
    for ( int i = 0; i < 4; i++ ) {
    
      TString prob = ")*prob";
      if (i == 3) prob += "ge";
      prob+=i;
      TString allCuts = nominal+cutsNjets+jetpt+"1"+prob;
      //cout << allCuts << endl;
      char hname[1000] ;

      sprintf( hname, "hist") ;
      myChain.Project( hname,"MET",allCuts);
      double val = h1->Integral();
      res[j][i] = val;    

      //printf(" Prob%i events: %9.3f \n", i, val ) ; cout << flush ;

    } //i - end of variables
    myChain.Reset();
  } //j - end of files
  
  printf("\n");
  printf("        File1         File2     (F1-F2)/F1[%]\n");

  if ( saveFile ) ofs << ", File1 , File2 , (F1-F2)/F1[%] , " << endl; 
  for ( int i = 0; i < 4 ; i++ ) {
    
    double one = res[0][i];
    double two = res[1][i];
    double percent = (one-two)/two*100;
    printf("Prob%i %11.2f %11.2f       %5.2f\n",i,one,two,percent);
    if ( saveFile ) ofs << "Prob" << i << "," << one << "," << two << "," << percent << "," << endl;    

  }

  printf("----------------\n") ;
  ofs.close();

  return;

}
