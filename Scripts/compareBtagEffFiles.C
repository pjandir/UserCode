
#include <iostream>
#include <fstream>
#include <string>
#include <TFile.h>
#include <TString.h>
#include "TH1.h"

//Must compile with .L compareBtagEffFiles.C+

//Compare the btag histo files histograms bin-by-bin
void CompareBtagEffFiles( TString ind = "" , TString inf = "" ) {

  const int ngraph = 9;       // # plots to compare
  const int nbins = 19;       // # bins to compare in each plot
  const int taggedgraphs = 6; // # plots which are simple counts only

  TFile myFiled(ind);
  TFile myFilef(inf);
  if ( myFiled.IsZombie() || myFilef.IsZombie() ) { cout << "Files are zombies!" << endl; return; }
 
  string names_d[ngraph] = {"h_bjet","h_cjet","h_ljet","h_btag","h_ctag","h_ltag","h_btageff","h_ctageff","h_ltageff"};
  string names_f[ngraph] = {"h_bjet","h_cjet","h_ljet","h_btag","h_ctag","h_ltag","h_btageff","h_ctageff","h_ltageff"};
  double ptbins[18] = {20, 30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500, 600, 800, 99999}; 
 
  TH1D * histd;
  TH1F * histf;

  cout << endl << "Comparing histograms in the btag eff histo files bin-by-bin (inc under/over-flow). " << endl;
  cout << "-------------------------------------------------------------" << endl;
  for( int i = 0; i < ngraph; i++ ) {
    //This 'hack' absolutely needed. Don't ask...
    char  hist_named[200], hist_namef[200]; 
    sprintf(hist_named,"%s",names_d[i].c_str());
    sprintf(hist_namef,"%s",names_f[i].c_str());

    cout << endl << "Now processing " << names_d[i] << " and " << names_f[i] << " ... "  << endl << endl;
    myFiled.cd("");
    histd = (TH1D*) gDirectory->Get(hist_named); 
    myFilef.cd("");
    histf = (TH1F*) gDirectory->Get(hist_namef); 
    if (histd->IsZombie() ) { cout << "There is something wrong with " << names_d[i] << "d. Please fix: now exiting." << endl; return; } 
    if (histf->IsZombie() ) { cout << "There is something wrong with " << names_f[i] << "f. Please fix: now exiting." << endl; return; }
 
    if ( i < taggedgraphs )
      cout << "  | TH1D       : TH1F       : D/F " << endl;
    else
      cout << "  | TH1D              : TH1F              : D/F " << endl;

    double totd = 0, totf = 0;
    for( int j = 0; j < nbins; j++ ) {
      if ( i < taggedgraphs ) { 
        printf("%2i| %10.0f : %-10.0f : %5.4f\n",j,histd->GetBinContent(j),histf->GetBinContent(j),histd->GetBinContent(j)/histf->GetBinContent(j));
        totd +=  histd->GetBinContent(j); 
        totf +=  histf->GetBinContent(j); 
      }
      else
        printf("%2i| %15.15f : %15.15f : %5.4f\n",j,histd->GetBinContent(j),histf->GetBinContent(j),histd->GetBinContent(j)/histf->GetBinContent(j));
    }//go through the bins..

    if ( i < taggedgraphs ) {
      cout << "  " << endl;
      printf("SUM %10.0f : %-10.0f : %5.4f\n",totd, totf, totd/totf);
    }
    cout << "-------------------------------------------------------------" << endl;

  }//end for  

  myFiled.Close();
  myFilef.Close();
 
  cout << endl << " .. Done " << endl;
} // end of function

