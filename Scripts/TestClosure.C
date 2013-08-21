#include <fstream>

int round(double a) {
  return int(a + 0.5);
}

void TestClosure() {

  ifstream unweight, weight;
  ifstream unweighterr, weighterr;
  unweight.open("./datfiles/TTJets-met4-ht4-v15-RawCounts-SIG.dat");
    weight.open("./datfiles/TTJets-met4-ht4-v15-EffCounts-SIG.dat");
  unweighterr.open("./datfiles/TTJets-met4-ht4-v15-RawCountsErr-SIG.dat");
    weighterr.open("./datfiles/TTJets-met4-ht4-v15-EffCountsErr-SIG.dat");
  ofstream out;
  ofstream outalt;
  ofstream outSpec;
  out.open("TTComp.csv"); 
  outalt.open("TTComp_alt.csv"); 
  outSpec.open("TTCompSigma.txt");  
  
  float numw1, numw2, numw3, numu1, numu2, numu3;
  float errw1, errw2, errw3, erru1, erru2, erru3;

  out << "TTJets madgraph, v63, Comparison of Raw and weighted counts" << endl;
  out << "nbjets=1, , , , ,nbjets=2, , , , ,nbjets>=3" << endl;
  out << "Weighted,W sigma,Raw,R sigma,(R-W)/Rsigma,Weighted,W sigma,Raw,R sigma,(R-W)/Rsigma,Weighted,W sigma,Raw,R sigma,(R-W)/Rsigma " << endl;
  outalt << "TTJets madgraph, v63, Comparison of Raw and weighted counts" << endl;
  outalt << "nbjets=1, , ,nbjets=2, , ,nbjets>=3" << endl;
  outalt << "Weighted,Raw,(R-W)/Rsigma,Weighted,Raw,(R-W)/Rsigma,Weighted,Raw,(R-W)/Rsigma " << endl;

  while ( unweight >> numu1 >> numu2 >> numu3 ) {
    
  //Maybe changed later!!
  weight >> numw1 >> numw2 >> numw3; 
  weighterr >> errw1 >> errw2 >> errw3;
  unweighterr >> erru1 >> erru2 >> erru3;

  //cout << erru1 << " " << erru2 << " " << erru3 << endl; 
  //cout << errw1 << " " << errw2 << " " << errw3 << endl; 
  float comp1 = ((numu1-round(numw1))/erru1);  
  float comp2 = ((numu2-round(numw2))/erru2);  
  float comp3 = ((numu3-round(numw3))/erru3);  
  char dum[500];

  out << round(numw1) << "," << errw1 << "," << numu1 << "," << erru1 << "," << comp1 << "," ;
  out << round(numw2) << "," << errw2 << "," << numu2 << "," << erru2 << "," << comp2 << "," ;
  out << round(numw3) << "," << errw3 << "," << numu3 << "," << erru3 << "," << comp3 << "," ;
  out << endl; 
  sprintf(dum,"%5.0f+/-%4.2f,%5.0f+/-%4.2f,%f,",round(numw1),errw1,numu1,erru1,comp1);
  outalt << dum; 
  sprintf(dum,"%5.0f+/-%4.2f,%5.0f+/-%4.2f,%f,",round(numw2),errw2,numu2,erru2,comp2);
  outalt << dum;
  sprintf(dum,"%5.0f+/-%4.2f,%5.0f+/-%4.2f,%f,",round(numw3),errw3,numu3,erru3,comp3);
  outalt << dum << endl;
  outSpec << comp1 << " ";
  outSpec << comp2 << " ";
  outSpec << comp3 << " ";
  outSpec << endl;

  }

  unweight.close();
  weight.close();
  out.close();
  outalt.close();
  outSpec.close();

}
