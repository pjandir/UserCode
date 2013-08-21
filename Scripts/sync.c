
#include <iostream>
#include "TMath.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "MyUtils.C"

void sync( TString input="" ) {

  TChain* myChain = new TChain("reducedTree") ;
  myChain->Add( input ) ;
  if ( myChain->IsZombie() ) { cout << "File(s) in Chain failed!!" << endl; return; }

  string sampleName = GetSampleName( input );
  cout << endl << "The total events in this dataset [ " <<  sampleName <<  " ]: " << myChain->GetEntries() << endl << endl; 
  //cout << endl << "The total events in this dataset [ " <<  sampleName <<  " ]: " << reducedTree->GetEntries() << endl << endl; 
  
  const int ncuts    = 14;
  const int nweights =  4;
  char *cuts[ncuts] = {   
			"cutPV==1",
			"HT>400",
			"njets>=3",
			"jetpt1>70&&jetpt2>70",
			"nElectrons==0",
			"nMuons==0",
			"MET>125",
			"minDeltaPhiN_asin>4",
			"passCleaning",
			"MET/caloMET<2",
			"maxTOBTECjetDeltaMult<40",
			"nIsoTracks15_005_03==0",
			"nbjets>=1",
			"nbjets==1"
                   };//14
  char *weights[nweights] = {
			"*weight2",
			"*19399",//19.399fb^-1
			"*PUweight",
			"*prob0"
                   };//4

  // Float shouldn't be used.. use doubles
  // The projection varibale does matter.. use a variable that has only integer bins. Remember we want to take the integral of the hist..
  //TH1F * h = new TH1F ("hist","hist",1000,0,1000);
  TH1D * h = new TH1D ("hist","hist",1000,0,1000);
  TString fullcut;
  TString varcut = "njets"; 

  // cuts
  for ( int i = 0; i < ncuts; i++) {
    TString cut = "(";
    for ( int j = 0; j < i + 1; j++) {
      cut+=cuts[j];
      if (j!=i) cut+="&&";
    }
    cut+=")";
    myChain->Project("hist",varcut,cut);
    //reducedTree->Project("hist",varcut,cut);
    double res = h->GetEntries();
    //double res = h->Integral();
    cout << "The cut [ " << varcut <<  " ] being made: " << cut << endl;
    printf("The number of events that passed this cut: %20.3f\n",res);
    fullcut = cut;
  }
  // weights
  for ( int i = 0; i < nweights; i++) {
    TString cut = fullcut;
    for ( int j = 0; j < i + 1; j++) cut+=weights[j]; 
    myChain->Project("hist",varcut,cut);
    double res = h->Integral();
    cout << "The cut [ " << varcut <<  " ] being made: " << cut << endl;
    printf("The number of events that passed this cut: %20.3f\n",res);
  }//
  cout << endl;

//string eight = "csctighthaloFilter&&eenoiseFilter&&greedymuonFilter&&hbhenoiseFilter&&inconsistentmuonFilter&&ra2ecaltpFilter&&scrapingvetoFilter&&trackingfailureFilter&&badjetFilter&&rawPFMET/caloMET<2";
//string eight = "scrapingvetoFilter&&csctighthaloFilter&&hbhenoiseFilter&&ra2ecaltpFilter&&trackingfailureFilter&&eenoiseFilter&&greedymuonFilter&&inconsistentmuonFilter&&badjetFilter&&rawPFMET/caloMET<2";
//reducedTree.Project(name,"MET","(cutPV==1&&HT>400&&njets>=3&&jetpt1>70&&jetpt2>70&&nElectrons==0&&nMuons==0&&MET>125&&minDeltaPhiN_asin>4&&passCleaning&&MET/caloMET<2&&maxTOBTECjetDeltaMult<40&&nIsoTracks15_005_03==0&&nbjets==1)*weight2*12000*PUweight*probge1")

} //end method

