

//cfA version hardcoded!!
void GetTreeName( TString inputFile="") {
//reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.SMS-MadGraph_T1t1t-1000-800to800-100to550_UCSB1754reshuf_v68_1.root

  string str;
  string name( inputFile );
  unsigned int pos = name.find_last_of("/");

  //Get name of file only not the entire path that may be provided
  if ( pos != std::string::npos ) {
    str = name.substr(pos+1);
  } 
  else {
    str = name;
  }

  //Find the .root and cut it out..
  size_t und = str.find("v68");
  if ( und > 255 ) und = str.find("v66");
  if ( und > 255 ) und = str.find("v67");
  if ( und > 255 ) und = str.find("v69");
  if ( und > 255 ) und = str.find("v70");
  string ret = str.substr(0,und+3);

  cout << ret << endl;
  return;
}

