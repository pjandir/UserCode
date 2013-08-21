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

void HistogramIt( TString file="" ) { 

  ifstream ifs;
  ifs.open( file );

  double array[4][4][3]; //MET/HT/NBJETS
  double dum;

//  double x[4] = {1,2,3,4};
//  double y[17] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
//  TH2D * hist = new TH2D("title","name",3,x,16,y);
  char *bbins[3] = {"=1 btag","=2 btag",">=3 btag"};
  char *ebins[16] = {"MET1, HT1","MET1, HT2","MET1,HT3","MET1, HT4","MET2, HT1","MET2, HT2","MET2, HT3","MET2, HT4","MET3, HT1","MET3, HT2","MET3, HT3","MET3, HT4","MET4, HT1","MET4, HT2","MET4, HT3","MET4, HT4"};
  TH2F *h = new TH2F("h","ttbar: btag efficiency closure",3,0,3,2,0,2);
  h->SetBit(TH1::kCanRebin);
  h->SetStats(0);

  TCanvas * can;
  can = new TCanvas("canvas","hope",750,550); 

  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);
//  gStyle->SetPadTickX(2);
//  gStyle->SetPadTickY(5);

  int l = 0;
  for(int i = 0 ; i < 4; i++) {
    for(int j = 0 ; j < 4; j++) {
      for(int k = 0 ; k < 3; k++) {
        ifs >> dum;
        array[i][j][k] = dum;
        cout << dum << " " ;
        h->Fill(bbins[k], ebins[l], dum); 
      }   
      l++;
      cout << endl;
    }   
  }
  h->SetTickLength(0.0,"X");
  h->SetTickLength(0.0,"Y");
  h->Draw("colz");
  can->SaveAs("visual_btageff_ttbar_closure.png");

}

