
#include "TChain.h"

//Count Events from AOD/cfA/whatever trees
void EvGen(TString str = "/full/path/to/root/files") {

  //Ignore warnings
  gErrorIgnoreLevel = 3000;

  //TString tree = "configurableAnalysis/eventA";
  TString tree = "Events";
  TChain ch( tree );
  ch.Add( str );  
 
  //Check to make sure nothing goes wrong
  if ( ch.LoadTree(0) < 0 ) { cout << "Tree not found within file. Please check: Exiting." << endl; return; } 
  if ( ch.IsZombie() )      { cout << "Input root file is corrupt. Please check: Exiting." << endl; return; } 

  //Get count
  double ev = ch.GetEntries();

  //Output
  //cout << " -- " << str << "    " << ev << endl;
  printf(" -- %s   %11.0f\n",(char *)str,ev); 
 
}
