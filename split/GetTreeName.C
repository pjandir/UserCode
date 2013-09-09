//Careful cfA versions are hardcoded..
void GetTreeName( TString inputFile="") {

  string str;
  string name( inputFile );
  unsigned int pos = name.find_last_of("/");

  //Get name of file only--not the entire path that may be provided
  if ( pos != std::string::npos ) {
    str = name.substr(pos+1);
  } 
  else {
    str = name;
  }

  //Find the .root and cut it out.
  //It must be done this way since the usual names here are: reducedTree.blah.Name_of_Dataset_v69_batch_1234.root
  size_t und = str.find("v65");
  if ( und > 255 ) und = str.find("v66");
  if ( und > 255 ) und = str.find("v67");
  if ( und > 255 ) und = str.find("v68");
  if ( und > 255 ) und = str.find("v69");
  if ( und > 255 ) und = str.find("v70");
  if ( und > 255 ) und = str.find("v71");
  if ( und > 255 ) und = str.find("v71s");
  if ( und > 255 ) und = str.find("v72");
  if ( und > 255 ) und = str.find("v73");
  if ( und > 255 ) und = str.find("v74");
  string ret = str.substr(0,und+3);

  //Special for v71 skim&slim
  if ( str.find("ra2b") < 256 ) {
    und = str.find("v71s");
    ret = str.substr(0,und+4);
  }

  cout << ret << endl;
  return;
}

