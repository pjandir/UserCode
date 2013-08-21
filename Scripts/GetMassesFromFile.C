
#include <iostream>
#include <string>
#include <TString>

//Finds the MGl mass in the T1tttt file name
//Works by reading in file names from a text file and grouping them by MGl mass
//Everything is hardcoded..

void GetMassesFromFile( TString name ="SMS-T1tttt_Mgluino-350to2000_mLSP-0to1650_8TeV-Pythia6Z_Summer12-START52_V9_FSIM-v3_AODSIM_UCSB1601reshuf_v66.txt" ) {

  //Output txt file name.. mostly.
  string title = "SMS-T1tttt_Mgluino-350to2000_mLSP-0to1650_8TeV-Pythia6Z_Summer12-START52_V9_FSIM-v3_AODSIM_UCSB1601reshuf_v66";
  ifstream ifs;
  ifs.open( name );
  if (!ifs.good() ) { cout << "File provided is a zombie." << endl; return; }

  //Select ranges
  int mglmin = 350;
  int mglmax = 2000; 
  int mlspmin = 0;
  int mglbin = 25;
  int mlspbin = 25;
  // 
  int countfiles = 0; 
 
  for ( int i = mglmin; i < mglmax+1; i+=mglbin ) {
 
    ofstream ofs;
    char txt[2000];
    sprintf(txt,"%s_MGl_%i.txt",title.c_str(),i);
    ofs.open(txt);
    
    string str;
    int a = 0, b = 0, c = 0;
    int lim = 100000;
   
    while ( ifs >> str ){
      if (a++ > lim) break; //diagnostic..
    
      size_t mass = str.find("v66_f"); 
      size_t dot = str.find("root");
      string r1 = str.substr(mass+5,dot-mass-6);
      size_t one = r1.find("_");
      string r2 = r1.substr(one+1,r1.length()-one+1);
      size_t two = r2.find("_");
      string res1 = r1.substr(0,one);
      string res2 = r2.substr(0,two);
      int mgl = atoi(res1.c_str());
      int mlsp = atoi(res2.c_str());
      //diagnostics..
      //cout << str << endl;
      //cout << r1 << " " << r2 << endl;
      //cout << one << " " << two << endl;
      //cout << endl << mgl << endl << mlsp << endl;
      b++;
      if (mgl == i) {
        ofs << str << endl;
        c++;
      } 
    }//while
    
    ifs.clear();
    ifs.seekg(0, ios::beg);
    ofs.close(); 
    countfiles+=c;
    cout << "There were " << b << " files read in. MGl = " << i << " and " << c << " files found for that MGl "  << endl;
  }//end mgl

  cout << "A total of " << countfiles << " files were matched in output." << endl;
  ifs.close();
  return;
}
//  /mnt/hadoop/cms/store/users/cfA/2012/SMS-T1tttt_Mgluino-350to2000_mLSP-0to1650_8TeV-Pythia6Z_Summer12-START52_V9_FSIM-v3_AODSIM_UCSB1601reshuf_v66/cfA_SMS-T1tttt_Mgluino-350to2000_mLSP-0to1650_8TeV-Pythia6Z_Summer12-START52_V9_FSIM-v3_AODSIM_UCSB1601reshuf_v66_f1000_0_0_1795.root

