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

void CountEventsMod( TString inputFile = "" , int mgl = 800, int mlsp = 700, double flatDummyErr = 10., string mod ) {  //-- flat error in %.  If negative, use MC stat err.

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
  const int nBinsBjets =  3  ;   // this must always be 3
  const int nJetsCut   =  3  ;   // #jets >= nJetsCut
  TString cBbins[nBinsBjets] = {"nbjets==1","nbjets==2","nbjets>=3"};

  //-- met4-ht4-v15
  const int nBinsMET   = 4  ;
  const int nBinsHT    = 4  ;
  const int version    = 15 ;
  float Mbins[nBinsMET+1] = {125.,150.,250.,350. ,99999.} ;
  float Hbins[nBinsHT+1]  = {400.,500.,800.,1000.,99999.} ;
/*
  //-- met3-ht3-v1
  const int nBinsMET   = 3 ;
  const int nBinsHT    = 3 ;
  const int version    = 1 ;
  float Mbins[nBinsMET+1] = {150.,250.,350.,99999.}  ;
  float Hbins[nBinsHT+1]  = {400.,600.,1000.,99999.} ;
*/
//double dummyYield = 9.9 ;
  double dummyCorr = 1. ;
  long dummyEvts = 10000 ;
  
  if( sampleName == "T1bbbb" ) {   
    //Only go over one Mass Pair. Select yourself here!!
    int mGl  = mgl;
    int mLsp = mlsp;
  }

  ofstream inFile, inFileErr;
  ofstream ofs_sig, ofs_ldp, ofs_sl;
  char outfile[10000] ;
  sprintf( outfile, "eventCount_Sig_%s_%s_%i_%i.txt", sampleName.c_str() , mod.c_str(), mgl, mlsp) ;   
  ofs_sig.open( outfile );
  sprintf( outfile, "eventCount_Ldp_%s_%s_%i_%i.txt", sampleName.c_str() , mod.c_str(), mgl, mlsp) ;   
  ofs_ldp.open( outfile ); 
  sprintf( outfile, "eventCount_Sl_%s_%s_%i_%i.txt", sampleName.c_str() , mod.c_str(), mgl, mlsp) ;   
  ofs_sl.open( outfile ); 
  sprintf( outfile, "datfiles/%s-met%d-ht%d-v%d-RawCounts-SIG.dat", sampleName.c_str(), nBinsMET, nBinsHT, version ) ;
  inFile.open( outfile );
  sprintf( outfile, "datfiles/%s-met%d-ht%d-v%d-RawCountsErr-SIG.dat", sampleName.c_str(), nBinsMET, nBinsHT, version ) ;
  inFileErr.open( outfile );

  TString cutsSig = "minDeltaPhiN>4&&nMuons==0&&nElectrons==0&&";
  TString cutsSL =  "minDeltaPhiN>4&&( (nMuons==1&&nElectrons==0) || (nElectrons==1&&nMuons==0) )&&";
  TString cutsLDP = "minDeltaPhiN<4&&nMuons==0&&nElectrons==0&&";
  TString jetpt = "jetpt1>";
  jetpt+= minLeadJetPt;
  jetpt+= "&&jetpt2>";
  jetpt+= minLeadJetPt;
  jetpt+= "&&jetpt3>";
  jetpt+= min3rdJetPt;
  jetpt+= "&&";
  cutsSig += jetpt;
  cutsSL  += jetpt;
  cutsLDP += jetpt;   
 
  stringstream njcut ; njcut << nJetsCut;
  TString cutsNjets = "&&njets>=";
  cutsNjets += njcut.str();

  TH2F* h_susy_sig[10] ;
  TH2F* h_susy_sl[10] ;
  TH2F* h_susy_ldp[10] ;
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
  }

  float xsec = -1.;
  if( sampleName == "T1bbbb" ) {
  //  int theBin = gluinoxsec->FindBin( mGl ) ;					      
  //  if ( theBin <=0 || theBin > gluinoxsec->GetNbinsX() ) {			      
  //    printf("\n\n *** can't find bin for mgl=%d.  Returned %d\n\n", mGl, theBin ) ; 
  //    return ; 								      
  //  }										      
  //  xsec = gluinoxsec->GetBinContent( theBin ) ;				      

    if( sampleName == "T1bbbb") {
      inFile << mGl << " " << mLsp << " " << dummyEvts << " " ;
      ofs_sig << mGl << " " << mLsp << " " ;
      ofs_ldp << mGl << " " << mLsp << " " ;
      ofs_sl << mGl << " " << mLsp << " " ;
      printf(" mGl=%4d, mLsp=%4d\n", mGl, mLsp ) ; cout << flush ;
    }
  }

  printf("\n\n") ;
  for (int k = 0 ; k < nBinsBjets ; k++) {

    TString cutSMS;
    if( sampleName == "T1bbbb") {
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
    else 
      cutSMS = ""; 
    
    TString cut = cBbins[k] ;

    TString allSigCuts = cutSMS+cutsSig+cut+cutsNjets ;
    TString allSLCuts  = cutSMS+cutsSL+cut+cutsNjets ;
    TString allLDPCuts = cutSMS+cutsLDP+cut+cutsNjets ;

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

  } // k (nBjets)
  printf("\n\n") ;

  

  printf("----------------\n") ;
  for (int i = 0 ; i < nBinsMET ; i++) {
    for (int j = 0 ; j < nBinsHT ; j++) {
      for (int k = 0 ; k < nBinsBjets ; k++) {

        printf ( " Raw MC counts: %s: MET,HT (%d,%d) nb=%d   SIG = %9.0f, SL=%9.0f, LDP=%9.0f\n",
                 printout.c_str(), i+1, j+1, k+1,
                 h_susy_sig[k] -> GetBinContent( i+1, j+1 ),
                 h_susy_sl[k]  -> GetBinContent( i+1, j+1 ),
                 h_susy_ldp[k] -> GetBinContent( i+1, j+1 )  ) ;
         
        inFile << h_susy_sig[k]->GetBinContent( i+1, j+1) << " ";
        inFileErr << h_susy_sig[k]->GetBinError( i+1, j+1) << " ";
        ofs_sig << h_susy_sig[k]->GetBinContent( i+1, j+1) << " ";
        ofs_ldp << h_susy_ldp[k]->GetBinContent( i+1, j+1) << " ";
        ofs_sl << h_susy_ldp[k]->GetBinContent( i+1, j+1) << " ";

      } // k
      inFile << endl;
      inFileErr << endl;
      printf("----------------\n") ;
    } // j
  } // i
  printf("\n\n") ;


  if ( sampleName == "T1bbbb" ) {
  float totalSUSYyield = 0;
  printf("----------------\n") ;
  for (int i = 0 ; i < nBinsMET ; i++) {
    for (int j = 0 ; j < nBinsHT ; j++) {
      for (int k = 0 ; k < nBinsBjets ; k++) {

      // each point has 10k events generated. The sigma is in pb and I want to normalized to 5 fb-1. 
      // so multiple cross section by 0.5 to get events in 5 fb-1
/*
        inFile << 0.5*xsec*(h_susy_sig[k] -> GetBinContent( i+1, j+1 )) << " " ;
        inFile << 0.5*xsec*(h_susy_sl[k]  -> GetBinContent( i+1, j+1 )) << " " ;
        inFile << 0.5*xsec*(h_susy_ldp[k] -> GetBinContent( i+1, j+1 )) << " " ;

        totalSUSYyield += (h_susy_sig[k] -> GetBinContent( i+1, j+1 )*0.5*xsec);

        double nsel_sig = h_susy_sig[k] -> GetBinContent( i+1, j+1 ) ;
        double nsel_sl  = h_susy_sl[k]  -> GetBinContent( i+1, j+1 ) ;
        double nsel_ldp = h_susy_ldp[k] -> GetBinContent( i+1, j+1 ) ;
        double nevt_err_sig = 1 ;
        double nevt_err_sl  = 1 ;
        double nevt_err_ldp = 1 ;
        if ( nsel_sig > 0. ) { nevt_err_sig = 0.5*xsec*sqrt(nsel_sig) ; }
        if ( nsel_sl  > 0. ) { nevt_err_sl  = 0.5*xsec*sqrt(nsel_sl ) ; }
        if ( nsel_ldp > 0. ) { nevt_err_ldp = 0.5*xsec*sqrt(nsel_ldp) ; }

        printf ( " Xsec weighted events: %s: MET,HT (%d,%d) nb=%d   SIG = %6.1f +/- %4.1f,   SL=%6.1f +/- %4.1f,   LDP=%6.1f +/- %4.1f\n",
                 printout.c_str(), i+1, j+1, k+1,
                 0.5*xsec*(h_susy_sig[k] -> GetBinContent( i+1, j+1 )), nevt_err_sig,
                 0.5*xsec*(h_susy_sl[k]  -> GetBinContent( i+1, j+1 )), nevt_err_sl,
                 0.5*xsec*(h_susy_ldp[k] -> GetBinContent( i+1, j+1 )), nevt_err_ldp  ) ;
*/
      } // k
      printf("----------------\n") ;
    } // j
  } // i
  printf("Total SUSY yield within current binning = %9.1f", totalSUSYyield);
  printf("\n\n") ;

  inFile << endl ;
  inFileErr << endl ;
  }

  inFile.close();
  inFileErr.close();
  return;

}
