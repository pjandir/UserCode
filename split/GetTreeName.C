
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

  //Find the .root and cut it out
  size_t und = str.find(".root");
  string ret = str.substr(0,und);

  cout << ret << endl;
  return;
}

