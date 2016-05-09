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

void EffVariationMod( TString inputFile = "" , int verbosity = 0, int mgl = 800, int mlsp = 500 , string mod) { 

// Taken from GenerateSUSYFile.C 
// Adapted for single point use

  string sampleName = GetSampleName( inputFile );
  string printout = GetPrintout( sampleName, mgl, mlsp );

//gluino cross sections in pb.
  TFile prospino("referenceXSecs.root");
  TH1F *gluinoxsec = (TH1F*) prospino.Get("gluino_NLONLL") ;
  if ( gluinoxsec == 0 ) {
     printf("\n\n *** Can't find histogram with name gluino in referenceXSecs.root.\n\n") ;
     return ;
  } else {
//     gluinoxsec->Print("all") ;
  }

  TChain myChain("reducedTree");
  myChain.Add( inputFile );

  if ( myChain.IsZombie() ) {
    cout << "File(s) in Chain failed!!" << endl;
    return;
  }

  gROOT->Reset();

  double minLeadJetPt  = 70. ;
  double min3rdJetPt   = 50. ;
  const int nBinsBjets = 3 ;   // this must always be 3
  const int nJetsCut = 3 ;     // #jets >= nJetsCut
  TString bEffbins[nBinsBjets] = {")*prob1",")*prob2",")*probge3"};
  TString bEffPlusbins[nBinsBjets]  = {")*prob1_HFplus" ,")*prob2_HFplus" ,")*probge3_HFplus" };
  TString bEffMinusbins[nBinsBjets] = {")*prob1_HFminus",")*prob2_HFminus",")*probge3_HFminus"};

  //-- met4-ht4-v15
  const int nBinsMET   = 4 ;
  const int nBinsHT    = 4 ;
  const int version    = 15;
  float Mbins[nBinsMET+1] = {125.,150.,250.,350.,99999.}  ;
  float Hbins[nBinsHT+1]  = {400.,500.,800.,1000.,99999.} ;
/*
  //-- met3-ht3-v1
  const int nBinsMET   = 3 ;
  const int nBinsHT    = 3 ;
  const int version    = 1 ;
  float Mbins[nBinsMET+1] = {150.,250.,350.,99999.}  ;
  float Hbins[nBinsHT+1]  = {400.,600.,1000.,99999.} ;
*/
  //For the btag sigma variation
  float delta_sig[nBinsMET][nBinsHT][nBinsBjets] ;
  float  delta_sl[nBinsMET][nBinsHT][nBinsBjets] ;
  float delta_ldp[nBinsMET][nBinsHT][nBinsBjets] ;
    
  long dummyEvts = 10000 ;

  if( sampleName == "T1bbbb" ) {
    //Only go over one Mass Pair. Select yourself here!!
    int mGl  = mgl;
    int mLsp = mlsp;
  }

  ofstream ofs_sig, ofs_ldp, ofs_sl, inFile, inFileErr;
  char outfile[200];
  sprintf( outfile, "btagEff_Sig_%s_%s_%i_%i.txt", sampleName.c_str() , mod.c_str(), mgl, mlsp) ;  
  ofs_sig.open( outfile );
  sprintf( outfile, "btagEff_Ldp_%s_%s_%i_%i.txt", sampleName.c_str() , mod.c_str(), mgl, mlsp) ;  
  ofs_ldp.open( outfile );
  sprintf( outfile, "btagEff_Sl_%s_%s_%i_%i.txt", sampleName.c_str() , mod.c_str(), mgl, mlsp) ;  
  ofs_sl.open( outfile );
  sprintf( outfile, "datfiles/%s-met%d-ht%d-v%d-EffCounts-SIG.dat", sampleName.c_str(), nBinsMET, nBinsHT, version ) ;  
  inFile.open( outfile );
  sprintf( outfile, "datfiles/%s-met%d-ht%d-v%d-EffCountsErr-SIG.dat", sampleName.c_str(), nBinsMET, nBinsHT, version ) ;  
  inFileErr.open( outfile );
  

  TString cutsSig = "minDeltaPhiN>4&&nMuons==0&&nElectrons==0";
  TString cutsSL =  "minDeltaPhiN>4&&( (nMuons==1&&nElectrons==0) || (nElectrons==1&&nMuons==0) )";
  TString cutsLDP = "minDeltaPhiN<4&&nMuons==0&&nElectrons==0";
  TString jetpt = "&&jetpt1>";
  jetpt+= minLeadJetPt;
  jetpt+= "&&jetpt2>";
  jetpt+= minLeadJetPt;
  jetpt+= "&&jetpt3>";
  jetpt+= min3rdJetPt;
  cutsSig += jetpt;
  cutsSL  += jetpt;
  cutsLDP += jetpt;   
 
  stringstream njcut ; njcut << nJetsCut;
  TString cutsNjets = "&&njets>=";
  cutsNjets += njcut.str();

  TH2F* h_susy_sig[10] ;
  TH2F* h_susy_sl[10] ;
  TH2F* h_susy_ldp[10] ;
  TH2F* h_susy_sig_p1sig[10] ;
  TH2F* h_susy_sl_p1sig[10] ;
  TH2F* h_susy_ldp_p1sig[10] ;
  TH2F* h_susy_sig_m1sig[10] ;
  TH2F* h_susy_sl_m1sig[10] ;
  TH2F* h_susy_ldp_m1sig[10] ;
  for ( int bi=0; bi<nBinsBjets; bi++ ) {
     char hname[1000] ;
     sprintf( hname, "h_susy_sig_%db", bi+1 ) ;
     h_susy_sig[bi] = new TH2F( hname, hname, nBinsMET, Mbins, nBinsHT, Hbins ) ;
     h_susy_sig[bi] -> Sumw2() ;
     sprintf( hname, "h_susy_sl_%db", bi+1 ) ;
     h_susy_sl[bi] = new TH2F( hname, hname, nBinsMET, Mbins, nBinsHT, Hbins ) ;
     h_susy_sl[bi] -> Sumw2() ;
     sprintf( hname, "h_susy_ldp_%db", bi+1 ) ;
     h_susy_ldp[bi] = new TH2F( hname, hname, nBinsMET, Mbins, nBinsHT, Hbins ) ;
     h_susy_ldp[bi] -> Sumw2() ;

     sprintf( hname, "h_susy_sig_%db_p1sig", bi+1 ) ;
     h_susy_sig_p1sig[bi] = new TH2F( hname, hname, nBinsMET, Mbins, nBinsHT, Hbins ) ;
     h_susy_sig_p1sig[bi] -> Sumw2() ;
     sprintf( hname, "h_susy_sl_%db_p1sig", bi+1 ) ;
     h_susy_sl_p1sig[bi] = new TH2F( hname, hname, nBinsMET, Mbins, nBinsHT, Hbins ) ;
     h_susy_sl_p1sig[bi] -> Sumw2() ;
     sprintf( hname, "h_susy_ldp_%db_p1sig", bi+1 ) ;
     h_susy_ldp_p1sig[bi] = new TH2F( hname, hname, nBinsMET, Mbins, nBinsHT, Hbins ) ;
     h_susy_ldp_p1sig[bi] -> Sumw2() ;

     sprintf( hname, "h_susy_sig_%db_m1sig", bi+1 ) ;
     h_susy_sig_m1sig[bi] = new TH2F( hname, hname, nBinsMET, Mbins, nBinsHT, Hbins ) ;
     h_susy_sig_m1sig[bi] -> Sumw2() ;
     sprintf( hname, "h_susy_sl_%db_m1sig", bi+1 ) ;
     h_susy_sl_m1sig[bi] = new TH2F( hname, hname, nBinsMET, Mbins, nBinsHT, Hbins ) ;
     h_susy_sl_m1sig[bi] -> Sumw2() ;
     sprintf( hname, "h_susy_ldp_%db_m1sig", bi+1 ) ;
     h_susy_ldp_m1sig[bi] = new TH2F( hname, hname, nBinsMET, Mbins, nBinsHT, Hbins ) ;
     h_susy_ldp_m1sig[bi] -> Sumw2() ;

  }

//  float xsec = -1.;
  if ( sampleName == "T1bbbb" ) {
//    int theBin = gluinoxsec->FindBin( mGl ) ;					      
//    if ( theBin <=0 || theBin > gluinoxsec->GetNbinsX() ) {			      
//      printf("\n\n *** can't find bin for mgl=%d.  Returned %d\n\n", mGl, theBin ) ; 
//      return ; 								      
//    }										      
//    xsec = gluinoxsec->GetBinContent( theBin ) ;				      

    printf("\n  mGl=%4d, mLsp=%4d\n", mGl, mLsp ) ; cout << flush ;
  }

  printf("\n\n") ;
  for (int k = 0 ; k < nBinsBjets ; k++) {

    TString cutSMS = "(";
    if( sampleName == "T1bbbb" ) {
      cutSMS += "m0>";
      cutSMS += mGl-1;
      cutSMS += "&&m0<";
      cutSMS += mGl+1;
      cutSMS += "&&m12>";
      cutSMS += mLsp-1;
      cutSMS += "&&m12<";
      cutSMS += mLsp+1;
      cutSMS += "&&";
    }

    TString cutbEff      = bEffbins[k]     ;
    TString cutbEffPlus  = bEffPlusbins[k] ;
    TString cutbEffMinus = bEffMinusbins[k];

    TString allSigCuts = cutSMS+cutsSig+cutsNjets+cutbEff ;
    TString allSLCuts  = cutSMS+cutsSL +cutsNjets+cutbEff ;
    TString allLDPCuts = cutSMS+cutsLDP+cutsNjets+cutbEff ;
    
    TString p1SigCuts = cutSMS+cutsSig+cutsNjets+cutbEffPlus ;
    TString p1SLCuts  = cutSMS+cutsSL +cutsNjets+cutbEffPlus ;
    TString p1LDPCuts = cutSMS+cutsLDP+cutsNjets+cutbEffPlus ;
    
    TString m1SigCuts = cutSMS+cutsSig+cutsNjets+cutbEffMinus ;
    TString m1SLCuts  = cutSMS+cutsSL +cutsNjets+cutbEffMinus ;
    TString m1LDPCuts = cutSMS+cutsLDP+cutsNjets+cutbEffMinus ;
  
    //cout << p1SigCuts << " " << m1SigCuts << endl;
    
    char hname[1000] ;

    sprintf( hname, "h_susy_sig_%db", k+1 ) ;
    myChain.Project( hname,"HT:MET",allSigCuts);
    printf("   %s nBjets = %d,  SIG selection %9.1f events.\n", printout.c_str(), k+1, h_susy_sig[k]->Integral() ) ; cout << flush ;

    sprintf( hname, "h_susy_sl_%db", k+1 ) ;
    myChain.Project( hname,"HT:MET",allSLCuts);
    printf("   %s nBjets = %d,  SL  selection %9.1f events.\n", printout.c_str(), k+1, h_susy_sl[k]->Integral() ) ; cout << flush ;

    sprintf( hname, "h_susy_ldp_%db", k+1 ) ;
    myChain.Project( hname,"HT:MET",allLDPCuts);
    printf("   %s nBjets = %d,  LDP selection %9.1f events.\n", printout.c_str(), k+1, h_susy_ldp[k]->Integral() ) ; cout << flush ;

    sprintf( hname, "h_susy_sig_%db_p1sig", k+1 ) ;
    myChain.Project( hname,"HT:MET",p1SigCuts);
    printf("   %s nBjets = %d,  SIG selection %9.1f events with +1 sigma btag eff.\n", printout.c_str(), k+1, h_susy_sig_p1sig[k]->Integral() ) ; cout << flush ;

    sprintf( hname, "h_susy_sl_%db_p1sig", k+1 ) ;
    myChain.Project( hname,"HT:MET",p1SLCuts);
    printf("   %s nBjets = %d,  SL  selection %9.1f events with +1 sigma btag eff.\n", printout.c_str(), k+1, h_susy_sl_p1sig[k]->Integral() ) ; cout << flush ;

    sprintf( hname, "h_susy_ldp_%db_p1sig", k+1 ) ;
    myChain.Project( hname,"HT:MET",p1LDPCuts);
    printf("   %s nBjets = %d,  LDP selection %9.1f events with +1 sigma btag eff.\n", printout.c_str(), k+1, h_susy_ldp_p1sig[k]->Integral() ) ; cout << flush ;

    sprintf( hname, "h_susy_sig_%db_m1sig", k+1 ) ;
    myChain.Project( hname,"HT:MET",m1SigCuts);
    printf("   %s nBjets = %d,  SIG selection %9.1f events with -1 sigma btag eff.\n", printout.c_str(), k+1, h_susy_sig_m1sig[k]->Integral() ) ; cout << flush ;

    sprintf( hname, "h_susy_sl_%db_m1sig", k+1 ) ;
    myChain.Project( hname,"HT:MET",m1SLCuts);
    printf("   %s nBjets = %d,  SL  selection %9.1f events with -1 sigma btag eff.\n", printout.c_str(), k+1, h_susy_sl_m1sig[k]->Integral() ) ; cout << flush ;

    sprintf( hname, "h_susy_ldp_%db_m1sig", k+1 ) ;
    myChain.Project( hname,"HT:MET",m1LDPCuts);
    printf("   %s nBjets = %d,  LDP selection %9.1f events with -1 sigma btag eff.\n", printout.c_str(), k+1, h_susy_ldp_m1sig[k]->Integral() ) ; cout << flush ;

  } // k (nBjets)
  printf("\n\n") ;

  char dummy[200];
  if ( sampleName == "T1bbbb" ) { 
    ofs_sig << mGl << "     " << mLsp << "    ";
    ofs_ldp << mGl << "     " << mLsp << "    ";
    ofs_sl << mGl << "     " << mLsp << "    ";
  }

  for (int i = 0 ; i < nBinsMET ; i++) {
    for (int j = 0 ; j < nBinsHT ; j++) {
      for (int k = 0 ; k < nBinsBjets ; k++) {
        if( h_susy_sig[k]->GetBinContent(i+1,j+1) != 0.0 )
           delta_sig[i][j][k] = 0.5 * ( h_susy_sig_p1sig[k]->GetBinContent(i+1,j+1) - h_susy_sig_m1sig[k]->GetBinContent(i+1,j+1) ) / h_susy_sig[k]->GetBinContent(i+1,j+1) ;
         else if ( h_susy_sig_p1sig[k]->GetBinContent(i+1,j+1) == 0.0 && h_susy_sig_m1sig[k]->GetBinContent(i+1,j+1) == 0.0 )
           delta_sig[i][j][k] = 0.0;
         else
           delta_sig[i][j][k] = 0.50;     

        if( h_susy_ldp[k]->GetBinContent(i+1,j+1) != 0.0 )
           delta_ldp[i][j][k] = 0.5 * ( h_susy_ldp_p1sig[k]->GetBinContent(i+1,j+1) - h_susy_ldp_m1sig[k]->GetBinContent(i+1,j+1) ) / h_susy_ldp[k]->GetBinContent(i+1,j+1) ;
         else if ( h_susy_ldp_p1sig[k]->GetBinContent(i+1,j+1) == 0.0 && h_susy_ldp_m1sig[k]->GetBinContent(i+1,j+1) == 0.0 )
           delta_ldp[i][j][k] = 0.0;
         else
           delta_ldp[i][j][k] = 0.50;     

        if( h_susy_sl[k]->GetBinContent(i+1,j+1) != 0.0 )
           delta_sl[i][j][k] = 0.5 * ( h_susy_sl_p1sig[k]->GetBinContent(i+1,j+1) - h_susy_sl_m1sig[k]->GetBinContent(i+1,j+1) ) / h_susy_sl[k]->GetBinContent(i+1,j+1) ;
         else if ( h_susy_sl_p1sig[k]->GetBinContent(i+1,j+1) == 0.0 && h_susy_sl_m1sig[k]->GetBinContent(i+1,j+1) == 0.0 )
           delta_sl[i][j][k] = 0.0;
         else
           delta_sl[i][j][k] = 0.50;     
        
        inFile << h_susy_sig[k]->GetBinContent(i+1, j+1) << " " ;
        inFileErr << h_susy_sig[k]->GetBinError(i+1, j+1) << " " ;

        sprintf(dummy, "  %6.3f ", delta_sig[i][j][k]);
        ofs_sig << dummy ; 
        sprintf(dummy, "  %6.3f ", delta_ldp[i][j][k]);
        ofs_ldp << dummy ; 
        sprintf(dummy, "  %6.3f ", delta_sl[i][j][k]);
        ofs_sl << dummy ; 
      } // k
      inFile << endl;
      inFileErr << endl;
    } // j
  } // i

  if( verbosity >= 1 ) {
  
  printf("----------------\n") ;
  for (int i = 0 ; i < nBinsMET ; i++) {
    for (int j = 0 ; j < nBinsHT ; j++) {
      for (int k = 0 ; k < nBinsBjets ; k++) {

        printf ( " Btag eff weighted counts: %s: MET,HT (%d,%d) nb=%d   SIG = %9.0f, SL=%9.0f, LDP=%9.0f\n",
                 printout.c_str(), i+1, j+1, k+1,
                 h_susy_sig[k] -> GetBinContent( i+1, j+1 ),
                 h_susy_sl[k]  -> GetBinContent( i+1, j+1 ),
                 h_susy_ldp[k] -> GetBinContent( i+1, j+1 )  ) ;

      } // k
      printf("----------------\n") ;
    } // j
  } // i
  printf("\n\n") ;

  printf("----------------\n") ;
  for (int i = 0 ; i < nBinsMET ; i++) {
    for (int j = 0 ; j < nBinsHT ; j++) {
      for (int k = 0 ; k < nBinsBjets ; k++) {

        printf ( " Btag eff +1 sigma counts: %s: MET,HT (%d,%d) nb=%d   SIG = %9.0f, SL=%9.0f, LDP=%9.0f\n",
                 printout.c_str(), i+1, j+1, k+1,
                 h_susy_sig_p1sig[k] -> GetBinContent( i+1, j+1 ),
                 h_susy_sl_p1sig[k]  -> GetBinContent( i+1, j+1 ),
                 h_susy_ldp_p1sig[k] -> GetBinContent( i+1, j+1 )  ) ;

      } // k
      printf("----------------\n") ;
    } // j
  } // i
  printf("\n\n") ;
  
  printf("----------------\n") ;
  for (int i = 0 ; i < nBinsMET ; i++) {
    for (int j = 0 ; j < nBinsHT ; j++) {
      for (int k = 0 ; k < nBinsBjets ; k++) {

        printf ( " Btag eff -1 sigma counts: %s: MET,HT (%d,%d) nb=%d   SIG = %9.0f, SL=%9.0f, LDP=%9.0f\n",
                 printout.c_str(), i+1, j+1, k+1,
                 h_susy_sig_m1sig[k] -> GetBinContent( i+1, j+1 ),
                 h_susy_sl_m1sig[k]  -> GetBinContent( i+1, j+1 ),
                 h_susy_ldp_m1sig[k] -> GetBinContent( i+1, j+1 )  ) ;

      } // k
      printf("----------------\n") ;
    } // j
  } // i

  } // end verbosity if
  printf("\n\n") ;
  
  printf("----------------\n") ;

  ofs_sig.close();
  ofs_ldp.close();
  ofs_sl.close();
  inFile.close();
  inFileErr.close();
  
  return;

}
