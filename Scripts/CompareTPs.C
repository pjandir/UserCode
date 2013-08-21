#include <iostream>
#include <fstream>
#include <string>
#include <TFile.h>
#include <TString.h>
#include "TH1.h"

#define BOOL_STR(b) ((b)?"true":"false")

// Compare Upgrade and Current TPs 
void CompareTPs( TString in1 = "./upgradeTP.root" , TString in2 = "./currentTP.root" ) {

  // User may change these variables to modify the behavior of the script
  // Not everything is printed out to screen.. 
  //---------------------------------------------------------------------------//
  const bool drawGraph  = true ; // Draw the graphs (must be on to save the graphs).
  const bool saveGraph1 = true ; // Save the graphs in a subdir with file extension defined below.
  const bool saveGraph2 = true ; // Save the graphs in a subdir with file extension defined below.
  const bool remZero    = true ; // Remove the xlow bin from graphs (i.e. the first bin) by setting it to zero.
  const bool logy       = true ; // Set y axis to log. 
  const bool logx       = false; // Set x axis to log--not really used.
  const bool dobatch    = true ; // Set dummy TCanvas to batch mode. 

  const int ngraph  =  3       ; // Number of plots to compare.
  const int nrebin  =  5       ; // Number of bins to merge--TH1::Rebin is used in the script. Set to 1 if not desired.  
  const int verbose =  0       ; // Verbosity level for print statements: [0,1,2,3] 0->All,1->Info,2->Warning,3->Error

  string mod     = "_test"     ; // A string to modify file names of produced plots. This string must start with a '_' character if it is not null.
  string folder  = "./plots"   ; // Set which directory graphs are saved to. Note this dir must exist prior to running this script.
  string ifile   = ".png"      ; // Set file type (extension) of graphs for individual files. 
  string gfile   = ".pdf"      ; // Set file type (extension) of graphs for a single continuous file.
  string gname   = "allPlots"  ; // Name of single continuous file 

  string dumdum1 = "Upgrade"   ; // Legend entry
  string dumdum2 = "Current"   ; // Legend entry
  
  // Enter names of the plots within the root files. Also used as part of final string of file names.  
  string names_1[ngraph] = {"tp_pt_emul","tp_pt_emul_hbhe","tp_pt_emul_hf"}; 
  string names_2[ngraph] = {"tp_pt_emul","tp_pt_emul_hbhe","tp_pt_emul_hf"};
  
  // In principle one can use arrays to help customize the plots to define titles, ranges, axis labels, etc.
  string names_titles[ngraph] = {"Upgrade vs Current TP - ALL HCAL","Upgrade vs Current TP - HBHE","Upgrade vs Current TP - HF"}; //titles
  
  //---------------------------------------------------------------------------//
 
 

  // Open the ROOT files containing the histograms. 
  TFile myFile1(in1);
  TFile myFile2(in2);
  if ( myFile1.IsZombie() || myFile2.IsZombie() ) { if ( verbose <= 10 ) cout << "Files are zombies!" << endl; return; }
 
  // Get full name 
  string outGname = gname + mod + gfile; 

  // Set ROOT global error message level -- see TError.h
  if ( verbose == 0 ) gErrorIgnoreLevel =    0;  
  if ( verbose == 1 ) gErrorIgnoreLevel = 1000;  
  if ( verbose == 2 ) gErrorIgnoreLevel = 2000;  
  if ( verbose == 3 ) gErrorIgnoreLevel = 3000;  
 
  // Style options etc. 
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);


  if ( verbose <= 1 ) { 
    cout << endl << "=============================================================" << endl;
    cout << endl << "Comparing TP histograms--Upgrade vs Current " << endl;
    cout << endl << "=============================================================" << endl;
    cout << endl << "User Settings: " << endl; 
    cout << "-------------------------------------------------------------" << endl;
    printf( "Draw the plots                 : %s\n" , BOOL_STR(drawGraph)  );
    printf( "Save the plots (individual)    : %s\n" , BOOL_STR(saveGraph1) );
    printf( "Save the plots (continuous)    : %s\n" , BOOL_STR(saveGraph2) );
    printf( "Remove the zeroth bin          : %s\n" , BOOL_STR(remZero)    );
    printf( "Set x-axis to log scale        : %s\n" , BOOL_STR(logx)       );
    printf( "Set y-axis to log scale        : %s\n" , BOOL_STR(logy)       );
    printf( "Run script in batch mode       : %s\n" , BOOL_STR(dobatch)    );
    printf( "Number of plots to compare     : %i\n" , ngraph               );
    printf( "Number of bins to remerge      : %i\n" , nrebin               );
    printf( "Output print level             : %i\n" , verbose              );
    printf( "Save plots to folder           : %s\n" , folder.c_str()       );
    printf( "Save individual plots as       : %s\n" , ifile.c_str()        );
    printf( "Save continuous plots in       : %s\n" , outGname.c_str()     );
    cout << "-------------------------------------------------------------" << endl;
  }
  if ( verbose <= 2 ) cout << "Warning: Upgrade and Current TPs are assumed to be in " << in1 << " and " << in2 << " respectively. Switch order if needed." << endl;
  
  // Dummy variables
  TH1F * hist1;
  TH1F * hist2;
  TCanvas * dumc = 0;
  dumc = new TCanvas("dumc","",600,400);
  dumc->SetBatch(dobatch);
 
 
  // Compare everything 
  for( int i = 0; i < ngraph; i++ ) {
    char  hist_name1[200], hist_name2[200]; 
    sprintf(hist_name1,"%s",names_1[i].c_str());
    sprintf(hist_name2,"%s",names_2[i].c_str());

    if ( verbose <= 1) cout << endl << "Now processing " << names_1[i] << " and " << names_2[i] << " ... "  << endl ;
    myFile1.cd("datacomp/");
    hist1 = (TH1F*) gDirectory->Get(hist_name1); 
    myFile2.cd("datacomp/");
    hist2 = (TH1F*) gDirectory->Get(hist_name2); 
    if ( hist1->IsZombie() && verbose <= 2 ) { cout << "There is something wrong with " << names_1[i] << "[1]. Please fix: skipping." << endl; continue; } 
    if ( hist2->IsZombie() && verbose <= 2 ) { cout << "There is something wrong with " << names_2[i] << "[2]. Please fix: skipping." << endl; continue; }

    double xup1 = hist1->GetXaxis()->GetBinUpEdge(hist1->GetNbinsX()) ;
    double xup2 = hist2->GetXaxis()->GetBinUpEdge(hist2->GetNbinsX()) ;

    if ( xup1 != xup2 && verbose <= 2 ) { cout << "Warning: Graphs do not have the same bin structure!" << endl; } 

    if ( drawGraph ) {
      if ( logy ) dumc->SetLogy(1);
      if ( logx ) dumc->SetLogx(1);
      if ( remZero ) { hist1->SetBinContent(1,0); hist2->SetBinContent(1,0); }
      hist1->SetLineColor(1);
      hist1->SetMarkerColor(1);
      hist1->SetMarkerStyle(1);
      hist2->SetLineColor(2);
      hist2->SetMarkerColor(2);
      hist2->SetMarkerStyle(1);
      if (nrebin!=1 && verbose<=1) cout << " FYI: Rebinning from " << xup1 / hist1->GetNbinsX() << " GeV steps to " << xup1 / hist1->GetNbinsX() * nrebin << " GeV." << endl; 
      hist1->Rebin(nrebin);
      hist2->Rebin(nrebin);
      TLegend *duml = new TLegend(0.75, 0.81, 0.89, 0.89, "", "brNDC");
      duml->SetBorderSize(2);
      duml->SetFillStyle(2);
      duml->AddEntry(hist1, dumdum1.c_str(), "l");
      duml->AddEntry(hist2, dumdum2.c_str(), "l");
      char title[200];
      sprintf(title,"%s;Energy",names_titles[i].c_str());
      hist1->SetTitle(title);
      //hist1->SetMinimum(1e-3);
      //hist1->SetMaximum(1);
      hist1->Draw("hist1 ");
      hist2->Draw("hist1 same");
      duml->Draw(); 
      char dumlabel[200];
      if ( logy ) sprintf(dumlabel,"%s/%s_logY%s%s",folder.c_str(),hist_name1,mod.c_str(),ifile.c_str());
      else        sprintf(dumlabel,"%s/%s_linY%s%s",folder.c_str(),hist_name1,mod.c_str(),ifile.c_str());
      if ( saveGraph1 ) {
        dumc->SaveAs(dumlabel);
        if ( verbose <= 1 ) cout << "Saving this comparison in: " << dumlabel << endl;
      }
      if ( saveGraph2 ) {
        if ( i == 0 )               dumc->Print( (folder+"/"+outGname+"(").c_str() );
        else if ( (i+1) == ngraph ) dumc->Print( (folder+"/"+outGname+")").c_str() );
        else                        dumc->Print( (folder+"/"+outGname).c_str() ); 
        if ( verbose <= 1 ) cout << "Saving current plot to " << folder << "/" << outGname << endl;
      }
      dumc->Clear();
    }//drawGraph

  }//end for  
  if ( verbose <= 1 ) cout << "=============================================================" << endl;

  myFile1.Close();
  myFile2.Close();
  dumc->Close();
 
  if ( verbose <= 1 ) cout << endl << " .. Done " << endl;
} // end of function

