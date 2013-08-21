
#include <fstream>
#include <TFile.h>
#include <TString.h>
#include <TCanvas.h>


void cross() {

//  TFile joshFile("./../../BasicLoopCU/btagEffMaps/histos_btageff_csvm_TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12-PU_S6_START52_V9-v1_AODSIM_UCSB1355ra2b_v63.root");
  TFile joshFile("./../../BasicLoopCU/btagEffMaps/histos_btageff_csvm_TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12-PU_S7_START52_V9-v2_AODSIM_UCSB1338ra2b_v63.root");

  TFile myFile("./../histos_btageff_csvm_TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12-PU_S7_START52_V9-v2_AODSIM_UCSB1338_v63.root");

  if ( myFile.IsZombie() || joshFile.IsZombie() ) cout << "ZOMBIE" << endl;

  TCanvas * c = 0;
  TH1F * hist1; 
  TH1F * hist2; 
  string names[9] = {"h_bjet","h_cjet","h_ljet","h_btag","h_ctag","h_ltag","h_btageff","h_ctageff","h_ltageff"}
  
  for(int i = 0; i < 9; i++) {
    //This 'hack' absolutely needed. Don't ask...
    char  hist_name[200]; 
    sprintf(hist_name,"%s",names[i].c_str());
    
    c = new TCanvas("c","",1000,600);
    if(i < 6)    c->SetLogy(1);    
 
    joshFile.cd("");
    hist1 = (TH1F*) gDirectory->Get(hist_name); 
    myFile.cd("");
    hist2 = (TH1F*) gDirectory->Get(hist_name); 

///// *******************
    double bins[15] = {30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500, 670};
    TH1F * dumhist1 = new TH1F(hist_name,hist_name,14,bins);
    TH1F * dumhist2 = new TH1F(hist_name,hist_name,14,bins);
    for(int k = 0; k < hist1->GetNbinsX()-1; k++) {
      dumhist1->SetBinContent(k,hist1->GetBinContent(k) );
      dumhist2->SetBinContent(k,hist2->GetBinContent(k) );
    }
    TCanvas * dumc = new TCanvas("dumc","",1000,600);
    if(i<6) dumc->SetLogy(1);
    dumhist1->SetTitle(hist_name);
    dumhist2->SetLineColor(1);
    dumhist1->SetLineColor(2);
    TLegend *duml = new TLegend(0.50, 0.71, 0.74, 0.79, "", "brNDC");
    duml->SetBorderSize(2);
    duml->SetFillStyle(2);
    char dumdum1[200];
    sprintf(dumdum1,"Skim, Entries: %i",hist1->GetEntries());
    char dumdum2[200];
    sprintf(dumdum2,"Unskim, Entries: %i",hist2->GetEntries());
    duml->AddEntry(dumhist2, dumdum2, "l");
    duml->AddEntry(dumhist1, dumdum1, "l");
    dumhist2->SetAxisRange(0,670);
    dumhist1->SetAxisRange(0,670);
    dumhist1->GetXaxis()->SetRange(0,670);
//    dumhist1->SetMinimum(0);
    dumhist2->Draw("dumhist");
    dumhist1->Draw("dumhist same");
    duml->Draw(); 
    char dumlabel[200];
    sprintf(dumlabel,"%s_alt.png",hist_name);
    dumc->SaveAs(dumlabel);
///// *******************   
    
    hist2->SetTitle(hist_name);
    hist2->SetLineColor(1);
    hist1->SetLineColor(2);
    //Legend
    TLegend *leg = new TLegend(0.50, 0.71, 0.74, 0.79, "", "brNDC");
    leg->SetBorderSize(2);
    leg->SetFillStyle(1001);
    char dum1[200];
    sprintf(dum1,"Skim, Entries: %i",hist1->GetEntries());
    char dum2[200];
    sprintf(dum2,"Unskim, Entries: %i",hist2->GetEntries());
    leg->AddEntry(hist2, dum2, "l");
    leg->AddEntry(hist1, dum1, "l");

//    hist2->GetXaxis()->SetRange(0,1000);
//    hist1->SetAxisRange(0,1000);

    hist2->Draw("hist");
    hist1->Draw("hist same");
    leg->Draw();

    char label[200];
    sprintf(label,"%s.png",hist_name);
    c->SaveAs(label);

  }//end for  

}
