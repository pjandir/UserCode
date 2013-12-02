
string GetSampleName( TString inputFile="") {
  //8TeV
  //Drell Yan
  if (inputFile.Contains("DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph")) return "ZJets";
  if (inputFile.Contains("DYJetsToLL_HT-200To400_TuneZ2Star_8TeV-madgraph")) return "ZJets_HT200To400";
  if (inputFile.Contains("DYJetsToLL_HT-400ToInf_TuneZ2Star_8TeV-madgraph")) return "ZJets_HT400ToInf";
  //Pythia QCD - all LO PREP
  if (inputFile.Contains("QCD1000")) return "QCD1000";
  if (inputFile.Contains("QCD120")) return "QCD120";
  if (inputFile.Contains("QCD1400")) return "QCD1400";
  if (inputFile.Contains("QCD170")) return "QCD170";
  if (inputFile.Contains("QCD1800")) return "QCD1800";
  if (inputFile.Contains("QCD300")) return "QCD300";
  if (inputFile.Contains("QCD30")) return "QCD30";
  if (inputFile.Contains("QCD470")) return "QCD470";
  if (inputFile.Contains("QCD600")) return "QCD600";
  if (inputFile.Contains("QCD800")) return "QCD800";
  if (inputFile.Contains("QCD80")) return  "QCD80";
  //single top (don't bother)
  //W+Jets
  if (inputFile.Contains("WJetsToLNu_HT-400ToInf_8TeV-madgraph")) return "WJets_HT400ToInf";
  if (inputFile.Contains("WJetsToLNu_HT-250To300_8TeV-madgraph")) return "WJets_HT250To300";
  if (inputFile.Contains("WJetsToLNu_HT-300To400_8TeV-madgraph")) return "WJets_HT300To400";
  if (inputFile.Contains("WJets_HT400ToInf")) return "WJets_HT400ToInf";
  if (inputFile.Contains("WJets_HT250To300")) return "WJets_HT250To300";
  if (inputFile.Contains("WJets_HT300To400")) return "WJets_HT300To400";
  if (inputFile.Contains("WJetsToLNu_TuneZ2Star_8TeV-madgraph")) return "WJets";
  //diboson
  if (inputFile.Contains("WZ_TuneZ2star_8TeV_pythia6_tauola")) return "WZ";
  if (inputFile.Contains("WW_TuneZ2star_8TeV_pythia6_tauola")) return "WW";
  if (inputFile.Contains("ZZ_TuneZ2star_8TeV_pythia6_tauola")) return "ZZ";
  //Z -> nu nu  
  if (inputFile.Contains("ZJetsToNuNu_100_HT_200_TuneZ2Star_8TeV_madgraph")) return "Zinvisible_HT100To200";
  if (inputFile.Contains("ZJetsToNuNu_200_HT_400_TuneZ2Star_8TeV_madgraph")) return "Zinvisible_HT200To400";
  if (inputFile.Contains("ZJetsToNuNu_400_HT_inf_TuneZ2Star_8TeV_madgraph")) return "Zinvisible_HT400ToInf";
  if (inputFile.Contains("ZJetsToNuNu_50_HT_100_TuneZ2Star_8TeV_madgraph")) return "Zinvisible_HT50To100";
  //LM
  if (inputFile.Contains("SUSY_LM9_sftsht_8TeV"))          return "LM9";
  //ttbar
  //don't do this -- there are already 2 ttbar samples with very similar names
  //I'm gonna do it...
  if( inputFile.Contains("TTJets")) return "TTJets_madgraph"; 
  if( inputFile.Contains("TT_8TeV")) return "TTbar_MC_NLO"; 
  if( inputFile.Contains("TT_CT10")) return "TTbar_powheg"; 
  //SMS
  if (inputFile.Contains("MadGraph_T1bbbb"))          return "T1bbbb_madgraph";
  if (inputFile.Contains("MadGraph_T1tttt"))          return "T1tttt_madgraph";
  if (inputFile.Contains("T1bbbb"))          return "T1bbbb";
  if (inputFile.Contains("T1tttt"))          return "T1tttt";
  if (inputFile.Contains("T2tt"))          return "T2tt";
  if (inputFile.Contains("T2bb"))          return "T2bb";
  if (inputFile.Contains("T5tttt"))          return "T5tttt";
  if (inputFile.Contains("T1t1t"))          return "T1t1t";
  if (inputFile.Contains("T1ttcc"))          return "T1ttcc";
  if (inputFile.Contains("T7btw"))          return "T7btw";
  if (inputFile.Contains("T6bbHH"))          return "T6bbHH";
  if (inputFile.Contains("TChihh"))          return "TChihh";
  if (inputFile.Contains("TChiHH"))          return "TChiHH";
  if (inputFile.Contains("TChiZH"))          return "TChiZH";
  //pMSSM
  if (inputFile.Contains("pMSSM")) {
    if ( inputFile.Contains("batch1") )     return "pMSSM_b1";
    if ( inputFile.Contains("batch2") )     return "pMSSM_b2";
    if ( inputFile.Contains("batch3") )     return "pMSSM_b3";
    if ( inputFile.Contains("batch4") )     return "pMSSM_b4"; 
  }
  if (inputFile.Contains("MET_Run2012A"))  return "META";
  if (inputFile.Contains("MET_Run2012B"))  return "METB";
  if (inputFile.Contains("MET_Run2012C"))  return "METC";
  if (inputFile.Contains("MET_Run2012D"))  return "METD";

  //Otherwise not found
  return inputFile;
}


string GetSignalType( TString name = "" ) { 

  string str = GetSampleName(name);
  
  if ( str == "T1bbbb" ||  
       str == "T1bbbb_madgraph" ||
       str == "T1tttt" ||
       str == "T1tttt_madgraph" ||
       str == "T2tt" ||
       str == "T2bb" ||
       str == "T5tttt" ||
       str == "T1t1t" ||
       str == "T1ttcc" ||
       str == "T1tbbb" ||
       str == "T1ttbb" ||
       str == "T1tttb" ||
       str == "T2tb" ||
       str == "T6bbHH" || 
       str == "TChihh" ||
       str == "TChiHH" ||
       str == "TChiZH" || 
     str == "T7btw" 
     )   
  {
     return "SMS";
  }
  else if ( name.Contains("pMSSM") ) {   
     return "pMSSM";
  }

  //Otherwise we have no idea..
  return "UNKNOWN";
}


string GetPrintout( string sampleName="", int mgl=800, int mlsp=700, TString inFile="") {

  string str;
  string name = GetSignalType(inFile); 
  char dum[300];
  if(name == "SMS") {
    sprintf(dum," %s  mGl=%d, mLsp=%d,", sampleName.c_str(), mgl, mlsp);
    str = dum;
  }
  else if(name == "pMSSM") {
    sprintf(dum," %s  runNumber=%d,", sampleName.c_str(), mgl);
    str = dum;
  }
  else {
    sprintf(dum,"   %s,",sampleName.c_str());
    str = sampleName;
  }
  return str;
}


void ttwj(int choice, ifstream& ttbarSig, ifstream& wj250Sig, ifstream& wj300Sig, ifstream& wj400Sig, ifstream& ttbarSl, ifstream& wj250Sl, ifstream& wj300Sl, ifstream& wj400Sl ) {

  if ( choice == 1 ) {
    // Nominal "RAW"
    ttbarSig.open("TTJets-met4-ht4-v15-RawCounts-SIG.dat");
    wj250Sig.open("WJets_HT250To300-met4-ht4-v15-RawCounts-SIG.dat");
    wj300Sig.open("WJets_HT300To400-met4-ht4-v15-RawCounts-SIG.dat");
    wj400Sig.open("WJets_HT400ToInf-met4-ht4-v15-RawCounts-SIG.dat");
    ttbarSl.open("TTJets-met4-ht4-v15-RawCounts-SL.dat");
    wj250Sl.open("WJets_HT250To300-met4-ht4-v15-RawCounts-SL.dat");
    wj300Sl.open("WJets_HT300To400-met4-ht4-v15-RawCounts-SL.dat");
    wj400Sl.open("WJets_HT400ToInf-met4-ht4-v15-RawCounts-SL.dat");
  }
  else if ( choice == 2 ) {
    // Btag eff 
    ttbarSig.open("TTJets-met4-ht4-v15-EffCounts-SIG.dat");
    wj250Sig.open("WJets_HT250To300-met4-ht4-v15-EffCounts-SIG.dat");
    wj300Sig.open("WJets_HT300To400-met4-ht4-v15-EffCounts-SIG.dat");
    wj400Sig.open("WJets_HT400ToInf-met4-ht4-v15-EffCounts-SIG.dat");
    ttbarSl.open("TTJets-met4-ht4-v15-EffCounts-SL.dat");
    wj250Sl.open("WJets_HT250To300-met4-ht4-v15-EffCounts-SL.dat");
    wj300Sl.open("WJets_HT300To400-met4-ht4-v15-EffCounts-SL.dat");
    wj400Sl.open("WJets_HT400ToInf-met4-ht4-v15-EffCounts-SL.dat");
  }
  else if ( choice == 3 ) {
    // HF Plus
    ttbarSig.open("TTJets-met4-ht4-v15-EffCountsHFPlus-SIG.dat");
    wj250Sig.open("WJets_HT250To300-met4-ht4-v15-EffCountsHFPlus-SIG.dat");
    wj300Sig.open("WJets_HT300To400-met4-ht4-v15-EffCountsHFPlus-SIG.dat");
    wj400Sig.open("WJets_HT400ToInf-met4-ht4-v15-EffCountsHFPlus-SIG.dat");
    ttbarSl.open("TTJets-met4-ht4-v15-EffCountsHFPlus-SL.dat");
    wj250Sl.open("WJets_HT250To300-met4-ht4-v15-EffCountsHFPlus-SL.dat");
    wj300Sl.open("WJets_HT300To400-met4-ht4-v15-EffCountsHFPlus-SL.dat");
    wj400Sl.open("WJets_HT400ToInf-met4-ht4-v15-EffCountsHFPlus-SL.dat");
  }
  else if ( choice == 4 ) {
    // HF Minus
    ttbarSig.open("TTJets-met4-ht4-v15-EffCountsHFMinus-SIG.dat");
    wj250Sig.open("WJets_HT250To300-met4-ht4-v15-EffCountsHFMinus-SIG.dat");
    wj300Sig.open("WJets_HT300To400-met4-ht4-v15-EffCountsHFMinus-SIG.dat");
    wj400Sig.open("WJets_HT400ToInf-met4-ht4-v15-EffCountsHFMinus-SIG.dat");
    ttbarSl.open("TTJets-met4-ht4-v15-EffCountsHFMinus-SL.dat");
    wj250Sl.open("WJets_HT250To300-met4-ht4-v15-EffCountsHFMinus-SL.dat");
    wj300Sl.open("WJets_HT300To400-met4-ht4-v15-EffCountsHFMinus-SL.dat");
    wj400Sl.open("WJets_HT400ToInf-met4-ht4-v15-EffCountsHFMinus-SL.dat");
  }
  else if ( choice == 5 ) {
    // LF Plus
    ttbarSig.open("TTJets-met4-ht4-v15-EffCountsLFPlus-SIG.dat");
    wj250Sig.open("WJets_HT250To300-met4-ht4-v15-EffCountsLFPlus-SIG.dat");
    wj300Sig.open("WJets_HT300To400-met4-ht4-v15-EffCountsLFPlus-SIG.dat");
    wj400Sig.open("WJets_HT400ToInf-met4-ht4-v15-EffCountsLFPlus-SIG.dat");
    ttbarSl.open("TTJets-met4-ht4-v15-EffCountsLFPlus-SL.dat");
    wj250Sl.open("WJets_HT250To300-met4-ht4-v15-EffCountsLFPlus-SL.dat");
    wj300Sl.open("WJets_HT300To400-met4-ht4-v15-EffCountsLFPlus-SL.dat");
    wj400Sl.open("WJets_HT400ToInf-met4-ht4-v15-EffCountsLFPlus-SL.dat");
  }
  else if ( choice == 6 ) {
    // LF Minus
    ttbarSig.open("TTJets-met4-ht4-v15-EffCountsLFMinus-SIG.dat");
    wj250Sig.open("WJets_HT250To300-met4-ht4-v15-EffCountsLFMinus-SIG.dat");
    wj300Sig.open("WJets_HT300To400-met4-ht4-v15-EffCountsLFMinus-SIG.dat");
    wj400Sig.open("WJets_HT400ToInf-met4-ht4-v15-EffCountsLFMinus-SIG.dat");
    ttbarSl.open("TTJets-met4-ht4-v15-EffCountsLFMinus-SL.dat");
    wj250Sl.open("WJets_HT250To300-met4-ht4-v15-EffCountsLFMinus-SL.dat");
    wj300Sl.open("WJets_HT300To400-met4-ht4-v15-EffCountsLFMinus-SL.dat");
    wj400Sl.open("WJets_HT400ToInf-met4-ht4-v15-EffCountsLFMinus-SL.dat");
  }
  return;
}

void qcd(int choice, ifstream& sig120, ifstream& sig170, ifstream& sig300, ifstream& sig470, ifstream& sig600, ifstream& sig800, ifstream& sig1000, ifstream& sig1400, ifstream&sig1800, ifstream& ldp120, ifstream& ldp170, ifstream& ldp300, ifstream& ldp470, ifstream& ldp600, ifstream& ldp800, ifstream& ldp1000, ifstream& ldp1400, ifstream& ldp1800) {
  
  if ( choice == 1 ) { // Raw
    sig120.open("QCD120-met4-ht4-v15-RawCounts-SIG.dat");
    sig170.open("QCD170-met4-ht4-v15-RawCounts-SIG.dat");
    sig300.open("QCD300-met4-ht4-v15-RawCounts-SIG.dat");
    sig470.open("QCD470-met4-ht4-v15-RawCounts-SIG.dat");
    sig600.open("QCD600-met4-ht4-v15-RawCounts-SIG.dat");
    sig800.open("QCD800-met4-ht4-v15-RawCounts-SIG.dat");
    sig1000.open("QCD1000-met4-ht4-v15-RawCounts-SIG.dat");
    sig1400.open("QCD1400-met4-ht4-v15-RawCounts-SIG.dat");
    sig1800.open("QCD1800-met4-ht4-v15-RawCounts-SIG.dat");
    ldp120.open("QCD120-met4-ht4-v15-RawCounts-LDP.dat");
    ldp170.open("QCD170-met4-ht4-v15-RawCounts-LDP.dat");
    ldp300.open("QCD300-met4-ht4-v15-RawCounts-LDP.dat");
    ldp470.open("QCD470-met4-ht4-v15-RawCounts-LDP.dat");
    ldp600.open("QCD600-met4-ht4-v15-RawCounts-LDP.dat");
    ldp800.open("QCD800-met4-ht4-v15-RawCounts-LDP.dat");
    ldp1000.open("QCD1000-met4-ht4-v15-RawCounts-LDP.dat");
    ldp1400.open("QCD1400-met4-ht4-v15-RawCounts-LDP.dat");
    ldp1800.open("QCD1800-met4-ht4-v15-RawCounts-LDP.dat");
  }
  else if ( choice == 2 ) { // Eff
    sig120.open("QCD120-met4-ht4-v15-EffCounts-SIG.dat");
    sig170.open("QCD170-met4-ht4-v15-EffCounts-SIG.dat");
    sig300.open("QCD300-met4-ht4-v15-EffCounts-SIG.dat");
    sig470.open("QCD470-met4-ht4-v15-EffCounts-SIG.dat");
    sig600.open("QCD600-met4-ht4-v15-EffCounts-SIG.dat");
    sig800.open("QCD800-met4-ht4-v15-EffCounts-SIG.dat");
    sig1000.open("QCD1000-met4-ht4-v15-EffCounts-SIG.dat");
    sig1400.open("QCD1400-met4-ht4-v15-EffCounts-SIG.dat");
    sig1800.open("QCD1800-met4-ht4-v15-EffCounts-SIG.dat");
    ldp120.open("QCD120-met4-ht4-v15-EffCounts-LDP.dat");
    ldp170.open("QCD170-met4-ht4-v15-EffCounts-LDP.dat");
    ldp300.open("QCD300-met4-ht4-v15-EffCounts-LDP.dat");
    ldp470.open("QCD470-met4-ht4-v15-EffCounts-LDP.dat");
    ldp600.open("QCD600-met4-ht4-v15-EffCounts-LDP.dat");
    ldp800.open("QCD800-met4-ht4-v15-EffCounts-LDP.dat");
    ldp1000.open("QCD1000-met4-ht4-v15-EffCounts-LDP.dat");
    ldp1400.open("QCD1400-met4-ht4-v15-EffCounts-LDP.dat");
    ldp1800.open("QCD1800-met4-ht4-v15-EffCounts-LDP.dat");
  }
  else if ( choice == 3 ) { // HF Plus
    sig120.open("QCD120-met4-ht4-v15-EffCountsHFPlus-SIG.dat");
    sig170.open("QCD170-met4-ht4-v15-EffCountsHFPlus-SIG.dat");
    sig300.open("QCD300-met4-ht4-v15-EffCountsHFPlus-SIG.dat");
    sig470.open("QCD470-met4-ht4-v15-EffCountsHFPlus-SIG.dat");
    sig600.open("QCD600-met4-ht4-v15-EffCountsHFPlus-SIG.dat");
    sig800.open("QCD800-met4-ht4-v15-EffCountsHFPlus-SIG.dat");
    sig1000.open("QCD1000-met4-ht4-v15-EffCountsHFPlus-SIG.dat");
    sig1400.open("QCD1400-met4-ht4-v15-EffCountsHFPlus-SIG.dat");
    sig1800.open("QCD1800-met4-ht4-v15-EffCountsHFPlus-SIG.dat");
    ldp120.open("QCD120-met4-ht4-v15-EffCountsHFPlus-LDP.dat");
    ldp170.open("QCD170-met4-ht4-v15-EffCountsHFPlus-LDP.dat");
    ldp300.open("QCD300-met4-ht4-v15-EffCountsHFPlus-LDP.dat");
    ldp470.open("QCD470-met4-ht4-v15-EffCountsHFPlus-LDP.dat");
    ldp600.open("QCD600-met4-ht4-v15-EffCountsHFPlus-LDP.dat");
    ldp800.open("QCD800-met4-ht4-v15-EffCountsHFPlus-LDP.dat");
    ldp1000.open("QCD1000-met4-ht4-v15-EffCountsHFPlus-LDP.dat");
    ldp1400.open("QCD1400-met4-ht4-v15-EffCountsHFPlus-LDP.dat");
    ldp1800.open("QCD1800-met4-ht4-v15-EffCountsHFPlus-LDP.dat");
  }
  else if ( choice == 4 ) { // HF Minus
    sig120.open("QCD120-met4-ht4-v15-EffCountsHFMinus-SIG.dat");
    sig170.open("QCD170-met4-ht4-v15-EffCountsHFMinus-SIG.dat");
    sig300.open("QCD300-met4-ht4-v15-EffCountsHFMinus-SIG.dat");
    sig470.open("QCD470-met4-ht4-v15-EffCountsHFMinus-SIG.dat");
    sig600.open("QCD600-met4-ht4-v15-EffCountsHFMinus-SIG.dat");
    sig800.open("QCD800-met4-ht4-v15-EffCountsHFMinus-SIG.dat");
    sig1000.open("QCD1000-met4-ht4-v15-EffCountsHFMinus-SIG.dat");
    sig1400.open("QCD1400-met4-ht4-v15-EffCountsHFMinus-SIG.dat");
    sig1800.open("QCD1800-met4-ht4-v15-EffCountsHFMinus-SIG.dat");
    ldp120.open("QCD120-met4-ht4-v15-EffCountsHFMinus-LDP.dat");
    ldp170.open("QCD170-met4-ht4-v15-EffCountsHFMinus-LDP.dat");
    ldp300.open("QCD300-met4-ht4-v15-EffCountsHFMinus-LDP.dat");
    ldp470.open("QCD470-met4-ht4-v15-EffCountsHFMinus-LDP.dat");
    ldp600.open("QCD600-met4-ht4-v15-EffCountsHFMinus-LDP.dat");
    ldp800.open("QCD800-met4-ht4-v15-EffCountsHFMinus-LDP.dat");
    ldp1000.open("QCD1000-met4-ht4-v15-EffCountsHFMinus-LDP.dat");
    ldp1400.open("QCD1400-met4-ht4-v15-EffCountsHFMinus-LDP.dat");
    ldp1800.open("QCD1800-met4-ht4-v15-EffCountsHFMinus-LDP.dat");
  }
  else if ( choice == 5 ) { // LF Plus
    sig120.open("QCD120-met4-ht4-v15-EffCountsLFPlus-SIG.dat");
    sig170.open("QCD170-met4-ht4-v15-EffCountsLFPlus-SIG.dat");
    sig300.open("QCD300-met4-ht4-v15-EffCountsLFPlus-SIG.dat");
    sig470.open("QCD470-met4-ht4-v15-EffCountsLFPlus-SIG.dat");
    sig600.open("QCD600-met4-ht4-v15-EffCountsLFPlus-SIG.dat");
    sig800.open("QCD800-met4-ht4-v15-EffCountsLFPlus-SIG.dat");
    sig1000.open("QCD1000-met4-ht4-v15-EffCountsLFPlus-SIG.dat");
    sig1400.open("QCD1400-met4-ht4-v15-EffCountsLFPlus-SIG.dat");
    sig1800.open("QCD1800-met4-ht4-v15-EffCountsLFPlus-SIG.dat");
    ldp120.open("QCD120-met4-ht4-v15-EffCountsLFPlus-LDP.dat");
    ldp170.open("QCD170-met4-ht4-v15-EffCountsLFPlus-LDP.dat");
    ldp300.open("QCD300-met4-ht4-v15-EffCountsLFPlus-LDP.dat");
    ldp470.open("QCD470-met4-ht4-v15-EffCountsLFPlus-LDP.dat");
    ldp600.open("QCD600-met4-ht4-v15-EffCountsLFPlus-LDP.dat");
    ldp800.open("QCD800-met4-ht4-v15-EffCountsLFPlus-LDP.dat");
    ldp1000.open("QCD1000-met4-ht4-v15-EffCountsLFPlus-LDP.dat");
    ldp1400.open("QCD1400-met4-ht4-v15-EffCountsLFPlus-LDP.dat");
    ldp1800.open("QCD1800-met4-ht4-v15-EffCountsLFPlus-LDP.dat");
  }
  else if ( choice == 6 ) { // LF Minus
    sig120.open("QCD120-met4-ht4-v15-EffCountsLFMinus-SIG.dat");
    sig170.open("QCD170-met4-ht4-v15-EffCountsLFMinus-SIG.dat");
    sig300.open("QCD300-met4-ht4-v15-EffCountsLFMinus-SIG.dat");
    sig470.open("QCD470-met4-ht4-v15-EffCountsLFMinus-SIG.dat");
    sig600.open("QCD600-met4-ht4-v15-EffCountsLFMinus-SIG.dat");
    sig800.open("QCD800-met4-ht4-v15-EffCountsLFMinus-SIG.dat");
    sig1000.open("QCD1000-met4-ht4-v15-EffCountsLFMinus-SIG.dat");
    sig1400.open("QCD1400-met4-ht4-v15-EffCountsLFMinus-SIG.dat");
    sig1800.open("QCD1800-met4-ht4-v15-EffCountsLFMinus-SIG.dat");
    ldp120.open("QCD120-met4-ht4-v15-EffCountsLFMinus-LDP.dat");
    ldp170.open("QCD170-met4-ht4-v15-EffCountsLFMinus-LDP.dat");
    ldp300.open("QCD300-met4-ht4-v15-EffCountsLFMinus-LDP.dat");
    ldp470.open("QCD470-met4-ht4-v15-EffCountsLFMinus-LDP.dat");
    ldp600.open("QCD600-met4-ht4-v15-EffCountsLFMinus-LDP.dat");
    ldp800.open("QCD800-met4-ht4-v15-EffCountsLFMinus-LDP.dat");
    ldp1000.open("QCD1000-met4-ht4-v15-EffCountsLFMinus-LDP.dat");
    ldp1400.open("QCD1400-met4-ht4-v15-EffCountsLFMinus-LDP.dat");
    ldp1800.open("QCD1800-met4-ht4-v15-EffCountsLFMinus-LDP.dat");
  }
  return;
}

double ttwjError(double a = 0, double ae = 0, double b = 0, double be = 0, double c = 0, double ce = 0, double d = 0, double de = 0, double e = 0, double ee = 0) {

  //double res = sqrt( a*ae*ae + b*be*be + c*ce*ce + d*de*de );
  //return res;
  return sqrt( a*ae*ae + b*be*be + c*ce*ce + d*de*de + e*ee*ee );

}

double weightQCD(double z, double x, double y) {

//  if ( x == 0. || y == 0. ) return 100; 
  double sigx = 1/x ;
  double sigy = 1/y ;
  double err = z*sqrt( pow((sqrt(x)/x),2) + pow((sqrt(y)/y),2)  );
  return pow(err,-2);
}

double calcQCD(double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9, double b1, double b2, double b3, double b4, double b5, double b6, double b7, double b8, double b9 ) {

  double sig[9] = {a1,a2,a3,a4,a5,a6,a7,a8,a9}; 
  double ldp[9] = {b1,b2,b3,b4,b5,b6,b7,b8,b9}; 
  double res = 0, weightTot = 0;
  for( int i = 0; i < 9 ; i++ ) {
    if( ldp[i] > 0. ) double ratio = sig[i]/ldp[i];
    else if ( !(ldp[i] > 0. && sig[i] > 0.)  ) double ratio = 0.;
    else double ratio = 0.;
    if (ratio <= 0.) continue;
    double weight = weightQCD(ratio,sig[i],ldp[i]);
    res += weight*ratio; 
    weightTot += weight;

 }
 if ( res == 0. && weightTot == 0. ) return 1;
 return res/weightTot;

}

//Get name of file even if filepath is included in the string
string GetNameFromPath( TString orig = "./My/Dir/my_awesome_fileOK.txt" ) {
 
  string name ( (char*) orig ) ;
  unsigned int pos = name.find_last_of("/");
  string ret;

  if ( pos != std::string::npos ) {
    //cout << "found" << endl; 
    ret = name.substr(pos+1);
  }
  else {
    //cout << "not found" << endl;
    ret = name;
  }
 
  return ret;
}

