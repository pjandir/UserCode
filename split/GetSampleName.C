
void GetSampleName( TString inputFile="") {

  string ret;
  ret = inputFile;
  //8TeV
  //Drell Yan
  if (inputFile.Contains("DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph"))        ret = "ZJets";
  if (inputFile.Contains("DYJetsToLL_HT-200To400_TuneZ2Star_8TeV-madgraph")) ret = "ZJets200";
  if (inputFile.Contains("DYJetsToLL_HT-400ToInf_TuneZ2Star_8TeV-madgraph")) ret = "ZJets400";
  //Pythia QCD - all LO PREP
  if (inputFile.Contains("QCD_Pt-1000to1400"))  ret = "QCD1000";
  if (inputFile.Contains("QCD_Pt-120to170"))    ret = "QCD120" ;
  if (inputFile.Contains("QCD_Pt-1400to1800"))  ret = "QCD1400";
  if (inputFile.Contains("QCD_Pt-170to300"))    ret = "QCD170" ;
  if (inputFile.Contains("QCD_Pt-1800"))        ret = "QCD1800";
  if (inputFile.Contains("QCD_Pt-300to470"))    ret = "QCD300" ;
  if (inputFile.Contains("QCD30"))              ret = "QCD30"  ;
  if (inputFile.Contains("QCD_Pt-470to600"))    ret = "QCD470" ;
  if (inputFile.Contains("QCD_Pt-600to800"))    ret = "QCD600" ;
  if (inputFile.Contains("QCD_Pt-800to1000"))   ret = "QCD800" ;
  if (inputFile.Contains("QCD80"))              ret = "QCD80"  ;
  //single top 
  //W+Jets
  if (inputFile.Contains("WJetsToLNu_HT-400ToInf_8TeV-madgraph")) ret = "WJets400";
  if (inputFile.Contains("WJetsToLNu_HT-250To300_8TeV-madgraph")) ret = "WJets250";
  if (inputFile.Contains("WJetsToLNu_HT-300To400_8TeV-madgraph")) ret = "WJets300";
  if (inputFile.Contains("WJetsToLNu_TuneZ2Star_8TeV-madgraph"))  ret = "WJets"   ;
  //diboson
  if (inputFile.Contains("WZ_TuneZ2star_8TeV_pythia6_tauola")) ret = "WZ";
  if (inputFile.Contains("WW_TuneZ2star_8TeV_pythia6_tauola")) ret = "WW";
  if (inputFile.Contains("ZZ_TuneZ2star_8TeV_pythia6_tauola")) ret = "ZZ";
  //Z -> nu nu  
  if (inputFile.Contains("ZJetsToNuNu_100_HT_200_TuneZ2Star_8TeV_madgraph")) ret = "Zinv100";
  if (inputFile.Contains("ZJetsToNuNu_200_HT_400_TuneZ2Star_8TeV_madgraph")) ret = "Zinv200";
  if (inputFile.Contains("ZJetsToNuNu_400_HT_inf_TuneZ2Star_8TeV_madgraph")) ret = "Zinv400";
  if (inputFile.Contains("ZJetsToNuNu_50_HT_100_TuneZ2Star_8TeV_madgraph"))  ret = "Zinv50" ;
  //LM
  if (inputFile.Contains("SUSY_LM9_sftsht_8TeV"))          ret = "LM9";
  //ttbar
  if (inputFile.Contains("TTJets") && inputFile.Contains("madgraph")) ret = "TTJetsMG"; 
  if (inputFile.Contains("TTJets") ) 				      ret = "TTJets"  ; 
  if (inputFile.Contains("TT") && inputFile.Contains("mcatnlo"))      ret = "TTJets"  ;
  if (inputFile.Contains("TT") && inputFile.Contains("powheg"))       ret = "TTJets"  ;

  //SMS
  if (inputFile.Contains("MadGraph_T1bbbb"))  ret= "T1bbbbMG";
  if (inputFile.Contains("MadGraph_T1tttt"))  ret= "T1ttttMG";
  if (inputFile.Contains("T1bbbb"))           ret= "T1bbbb"  ;
  if (inputFile.Contains("T1tttt"))           ret= "T1tttt"  ;
  if (inputFile.Contains("T2tt"))             ret= "T2tt"    ;
  if (inputFile.Contains("T2bb"))             ret= "T2bb"    ;
  if (inputFile.Contains("T5tttt"))           ret= "T5tttt"  ;
  if (inputFile.Contains("T1t1t"))            ret= "T1t1t"   ;
  if (inputFile.Contains("T1ttcc"))           ret= "T1ttcc"  ;
  if (inputFile.Contains("T7btw"))            ret= "T7btw"   ;
  //pMSSM
  if (inputFile.Contains("pMSSM")) {
    if ( inputFile.Contains("batch1") )     ret= "pMSSM_b1";
    if ( inputFile.Contains("batch2") )     ret= "pMSSM_b2";
    if ( inputFile.Contains("batch3") )     ret= "pMSSM_b3";
    if ( inputFile.Contains("batch4") )     ret= "pMSSM_b4";
  }
  if (inputFile.Contains("HbbHbb") ) ret = "hbbhbb"; 
  if (inputFile.Contains("TChihh") ) ret = "TChihh"; 
  //Otherwise not found--be careful..

  cout << ret << endl;
  return;
}

