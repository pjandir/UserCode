#!/bin/bash

dir=/mnt/hadoop/cms/store/users/cfA/2012

#name=QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3_AODSIM_UCSB1513ra2b_v66
#name=QCD_Pt-170to300_TuneZ2star_8TeV_pythia6_Summer12-PU_S7_START52_V9-v1_AODSIM_UCSB1514ra2b_v66
#name=QCD_Pt-300to470_TuneZ2star_8TeV_pythia6_Summer12-PU_S7_START52_V9-v1_AODSIM_UCSB1519ra2b_v66
#name=QCD_Pt-300to470_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2_AODSIM_UCSB1560ra2b_v66
#name=QCD_Pt-470to600_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2_AODSIM_UCSB1515ra2b_v66
#name=QCD_Pt-600to800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2_AODSIM_UCSB1516ra2b_v66
#name=QCD_Pt-800to1000_TuneZ2star_8TeV_pythia6_Summer12-PU_S7_START52_V9-v1_AODSIM_UCSB1520ra2b_v66
#name=QCD_Pt-1000to1400_TuneZ2star_8TeV_pythia6_Summer12-PU_S7_START52_V9-v1_AODSIM_UCSB1521ra2b_v66
#name=QCD_Pt-1400to1800_TuneZ2star_8TeV_pythia6_Summer12-PU_S7_START52_V9-v1_AODSIM_UCSB1522ra2b_v66
#name=QCD_Pt-1800_TuneZ2star_8TeV_pythia6_Summer12-PU_S7_START52_V9-v1_AODSIM_UCSB1517ra2b_v66
#name=SMS-T1bbbb_Mgluino-100to2000_mLSP-0to2000_8TeV-Pythia6Z_Summer12-START52_V9_FSIM-v1_AODSIM_UCSB1548_v66
name=SMS-T1tttt_Mgluino-350to2000_mLSP-0to1650_8TeV-Pythia6Z_Summer12-START52_V9_FSIM-v3_AODSIM_UCSB1601_v66
#name=TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1489ra2b_v66
#name=WJetsToLNu_HT-250To300_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1488ra2b_v66
#name=WJetsToLNu_HT-300To400_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1512ra2b_v66
#name=WJetsToLNu_HT-400ToInf_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1487ra2b_v66

#name=QCD_Pt-800to1000_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v2_AODSIM_UCSB1559ra2b_v66
if [[ -f $name.txt  ]]
then
  rm $name.txt
fi

for file in $dir/$name/*.root
do

  echo $file >> $name.txt 

done

if [[ $name == cfA_* ]]
then
  
  nameReal=${name#*cfA_}
  mv $name.txt $nameReal.txt

fi

exit

