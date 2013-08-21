#!/bin/bash

##Do SMS sorting and then combine the results of the different search regions..
#model=T1bbbb_madgraph
model=T1bbbb
#model=T2tt

mod=

t="$(date +%s)"
echo Sorting through all search regions for the three sets of files for ${model}.
sleep 1

root -l -b -q 'SortSystematicFile.C("'btagEff_${model}_SIG.txt'")'
mv btagEff_${model}_SIG.txt.sorted btagEff_${model}_SIG${mod}.txt
mv btagEff_${model}_SIG.txt.original final_txt
root -l -b -q 'SortSystematicFile.C("'btagEff_${model}_LDP.txt'")'
mv btagEff_${model}_LDP.txt.sorted btagEff_${model}_LDP${mod}.txt
mv btagEff_${model}_LDP.txt.original final_txt
root -l -b -q 'SortSystematicFile.C("'btagEff_${model}_SL.txt'")'
mv btagEff_${model}_SL.txt.sorted btagEff_${model}_SL${mod}.txt
mv btagEff_${model}_SL.txt.original final_txt

root -l -b -q 'SortSystematicFile.C("'lightMistag_${model}_SIG.txt'")'
mv lightMistag_${model}_SIG.txt.sorted lightMistag_${model}_SIG${mod}.txt
mv lightMistag_${model}_SIG.txt.original final_txt
root -l -b -q 'SortSystematicFile.C("'lightMistag_${model}_LDP.txt'")'
mv lightMistag_${model}_LDP.txt.sorted lightMistag_${model}_LDP${mod}.txt
mv lightMistag_${model}_LDP.txt.original final_txt
root -l -b -q 'SortSystematicFile.C("'lightMistag_${model}_SL.txt'")'
mv lightMistag_${model}_SL.txt.sorted lightMistag_${model}_SL${mod}.txt
mv lightMistag_${model}_SL.txt.original final_txt

root -l -b -q 'SortSystematicFile.C("'rawCounts_${model}_SIG.txt'")'
mv rawCounts_${model}_SIG.txt.sorted rawCounts_${model}_SIG${mod}.txt
mv rawCounts_${model}_SIG.txt.original final_txt
root -l -b -q 'SortSystematicFile.C("'rawCounts_${model}_LDP.txt'")'
mv rawCounts_${model}_LDP.txt.sorted rawCounts_${model}_LDP${mod}.txt
mv rawCounts_${model}_LDP.txt.original final_txt
root -l -b -q 'SortSystematicFile.C("'rawCounts_${model}_SL.txt'")'
mv rawCounts_${model}_SL.txt.sorted rawCounts_${model}_SL${mod}.txt
mv rawCounts_${model}_SL.txt.original final_txt

echo Combining all search regions for the three sets of files.
sleep 1

root -l -b -q 'combine.C("'btagEff_${model}_SIG.txt'", "'btagEff_${model}_SL.txt'","'btagEff_${model}_LDP.txt'","''","'btagEff_${model}_SIG_SL_LDP${mod}.txt'")'
root -l -b -q 'combine.C("'lightMistag_${model}_SIG.txt'", "'lightMistag_${model}_SL.txt'","'lightMistag_${model}_LDP.txt'","''","'lightMistag_${model}_SIG_SL_LDP${mod}.txt'")'
root -l -b -q 'combine.C("'rawCounts_${model}_SIG.txt'", "'rawCounts_${model}_SL.txt'","'rawCounts_${model}_LDP.txt'","''","'rawCounts_${model}_SIG_SL_LDP${mod}.txt'")'

# If mod is not null delete all the original files..
if [ ! -z "$mod" ]
then
  rm btagEff_${model}_SIG.txt
  rm btagEff_${model}_SL.txt
  rm btagEff_${model}_LDP.txt
  rm lightMistag_${model}_SIG.txt
  rm lightMistag_${model}_SL.txt
  rm lightMistag_${model}_LDP.txt
  rm rawCounts_${model}_SIG.txt
  rm rawCounts_${model}_SL.txt
  rm rawCounts_${model}_LDP.txt
fi     


t="$(($(date +%s)-t))"
printf "Time it took to run this program: %02d:%02d:%02d\n" "$((t/3600))" "$((t/60))" "$((t%60))"
exit

