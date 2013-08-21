#!/bin/bash

#name=T5tttt
#name=T1t1t
#name=pMSSM_b1
name=T1tttt_madgraph
#name=T1bbbb_madgraph
#name=T2tt
#name=T1tttt

mod=_ucsb1776

t="$(date +%s)"

echo Deleting supplementary files created from splitting process.
sleep 1

rm ./files/pj_eff_*.sh
rm ./files/pj_eff_*.jdl

mv ../btagEff_Ldp_${name}_*.txt ./txt/ldp/eff
mv ../lightMistag_Ldp_${name}_*.txt ./txt/ldp/mistag
mv ../eventCount_Ldp_${name}_*.txt ./txt/ldp/count
mv ../btagEff_Sig_${name}_*.txt ./txt/sig/eff
mv ../lightMistag_Sig_${name}_*.txt ./txt/sig/mistag
mv ../eventCount_Sig_${name}_*.txt ./txt/sig/count
mv ../btagEff_Sl_${name}_*.txt ./txt/sl/eff
mv ../lightMistag_Sl_${name}_*.txt ./txt/sl/mistag
mv ../eventCount_Sl_${name}_*.txt ./txt/sl/count


for file in ./txt/ldp/eff/*.txt
do
  head $file >> btagEff_${name}${mod}_LDP.txt
  echo  >> btagEff_${name}${mod}_LDP.txt
done
for file in ./txt/ldp/mistag/*.txt
do
  head $file >> lightMistag_${name}${mod}_LDP.txt
  echo  >> lightMistag_${name}${mod}_LDP.txt
done
for file in ./txt/ldp/count/*.txt
do
  head $file >> rawCounts_${name}${mod}_LDP.txt
  echo  >> rawCounts_${name}${mod}_LDP.txt
done
for file in ./txt/sig/eff/*.txt
do
  head $file >> btagEff_${name}${mod}_SIG.txt
  echo  >> btagEff_${name}${mod}_SIG.txt
done
for file in ./txt/sig/mistag/*.txt
do
  head $file >> lightMistag_${name}${mod}_SIG.txt
  echo  >> lightMistag_${name}${mod}_SIG.txt
done
for file in ./txt/sig/count/*.txt
do
  head $file >> rawCounts_${name}${mod}_SIG.txt
  echo  >> rawCounts_${name}${mod}_SIG.txt
done
for file in ./txt/sl/eff/*.txt
do
  head $file >> btagEff_${name}${mod}_SL.txt
  echo  >> btagEff_${name}${mod}_SL.txt
done
for file in ./txt/sl/mistag/*.txt
do
  head $file >> lightMistag_${name}${mod}_SL.txt
  echo  >> lightMistag_${name}${mod}_SL.txt
done
for file in ./txt/sl/count/*.txt
do
  head $file >> rawCounts_${name}${mod}_SL.txt
  echo  >> rawCounts_${name}${mod}_SL.txt
done

rm ./txt/ldp/eff/*
rm ./txt/sig/eff/*
rm ./txt/sl/eff/*
rm ./txt/ldp/count/*
rm ./txt/sig/count/*
rm ./txt/sl/count/*
rm ./txt/ldp/mistag/*
rm ./txt/sig/mistag/*
rm ./txt/sl/mistag/*

t="$(($(date +%s)-t))"
printf "Time it took to run this program: %02d:%02d:%02d\n" "$((t/3600))" "$((t/60))" "$((t%60))"

exit
