#!/bin/bash

points=allScanPoints_T1tttt_madgraph_1776.txt
loc=reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.SMS-MadGraph_T1tttt-775to1075-525to875_v3_UCSB1776reshuf_v68.root

#points=allScanPoints_T5tttt.txt
#loc=reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.SMS-MadGraph_T5tttt-900to1200-225to1025-50_UCSB1249reshuf_v68.root

#points=allScanPoints_T1t1t_200.txt
#loc=reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.SMS-MadGraph_T1t1t-1000-200to750-100to650_UCSB1753reshuf_v68.root
#points=allScanPoints_T1t1t_350.txt
#loc=reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.SMS-MadGraph_T1t1t-1000-350to750-100to500_UCSB1756reshuf_v68.root
#points=allScanPoints_T1t1t_775.txt
#loc=reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.SMS-MadGraph_T1t1t-1000-775to825-575to725_UCSB1755reshuf_v68.root
#points=allScanPoints_T1t1t_800.txt
#loc=reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.SMS-MadGraph_T1t1t-1000-800to800-100to550_UCSB1754reshuf_v68.root

#points=allScanPoints_T1tttt_madgraph.txt
#loc=reducedTree.CSVM_PF2PATjets_JES0_JER0_PFMETTypeI_METunc0_PUunc0_BTagEff05_HLTEff0.SMS-MadGraph_T1bbbb-400to750-0to700_UCSB1711reshuf_v68.root

signal=2

n=0
while read line; do    

  if [  $signal -eq 1  ]
  then
    eval pt="$line"
    t1=$pt
    t2=-1
  elif [  $signal -eq 2  ]
  then  
    re="^([^-]+) (.*)$"
    [[ "${line}" =~ $re ]] && t1="${BASH_REMATCH[1]}" && t2="${BASH_REMATCH[2]}"
  fi

  mgl=${t1}
  mlsp=${t2}
  n=`expr $n + 1`
  root -l -b -q 'GetString.C('$n')' > sampname.txt
  mod=$(tail -1 sampname.txt)
  rm sampname.txt
#  echo point $pt while I send in $mod   
  echo mgl mlsp  $mgl $mlsp - $n while I send in $mod

  sed -e 's/dummy.txt/'$loc'/g' -e 's/DUM1/'$mgl'/g' -e 's/DUM2/'$mlsp'/g' -e 's/DUM3/'$mod'/g' skeleton.sh > pj_eff_$n.sh

  sed -e 's/dummy.sh/'pj_eff_$n.sh'/g' -e 's/sampleName/'${mgl}_${mlsp}'/g' skeleton.jdl > pj_eff_$n.jdl

  mv pj_eff_$n.sh pj_eff_$n.jdl ./files
  condor_submit ./files/pj_eff_$n.jdl 

done < ./../$points

echo Submitted $n jobs. 

exit

