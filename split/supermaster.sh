#!/bin/bash

###########################################################################################
# Master script to split a dataset into individual cfA root files to make reducedTrees
# 
#   - Superscript to batch together multiple datasets at once
#   - Uses exisiting master/postmortem infrastructure as is 
#     - Sits on top of it without modification
#   - Must be EXTREMELY careful; there is limited protection against condor system    
#
# Written by: Pawandeep Jandir
###########################################################################################


#-------------
# Usage
#       Enter names in datasets 
#-------------


##### User Settings 

#All the datasets to run through this script
declare -a datasets=(
"QCD_Pt-1000to1400_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_trkalmb_castor_PHYS14_25_V1-v1_MINIAODSIM_UCSB2372_v78"
"QCD_Pt-1400to1800_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_trkalmb_castor_PHYS14_25_V1-v1_MINIAODSIM_UCSB2371_v78"
"QCD_Pt-1800to2400_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_trkalmb_PHYS14_25_V1-v2_MINIAODSIM_UCSB2370_v78"
"QCD_Pt-2400to3200_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_trkalmb_PHYS14_25_V1-v1_MINIAODSIM_UCSB2369_v78"
"QCD_Pt-300to470_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_trkalmb_castor_PHYS14_25_V1-v2_MINIAODSIM_UCSB2376_v78"
"QCD_Pt-3200_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_trkalmb_PHYS14_25_V1-v1_MINIAODSIM_UCSB2368_v78"
"QCD_Pt-470to600_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_trkalmb_castor_PHYS14_25_V1-v2_MINIAODSIM_UCSB2375_v78"
"QCD_Pt-600to800_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_trkalmb_castor_PHYS14_25_V1-v1_MINIAODSIM_UCSB2374_v78"
"QCD_Pt-800to1000_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_trkalmb_castor_PHYS14_25_V1-v2_MINIAODSIM_UCSB2373_v78"
)

#Your username at UCR's T3
fulluser=pjandir

#Name of the log file where all the important output will be printed
thelog=thelogfile

#Switch to keep logfile (see above) or delete it for this call of the script
keeplog=true

#Time to wait between checks on the jobs before doing postmortem 
timewait=300

#####

#Do some error-checking to make sure things will run smoothly in the process
root -l -b -q > trash.txt
rval=$?
rm trash.txt
if [[ $rval -ne 0 ]]
then
  echo -e "Error: ROOT not found. Is cmsenv (or similar) sourced?"
  exit
fi
if [[ -f $thelog ]] && ! $keeplog;
then
  rm $thelog
fi

tt="$(date +%s)"

#Send info to master
sed -i 's@^fulluser=.*@'"fulluser=$fulluser"'@g' master.sh 

echo -ne "\n" >> $thelog
echo "**************************************************************************" >> $thelog
thetime=`date`
echo "Starting the superscript.. $thetime " >> $thelog
echo "**************************************************************************" >> $thelog
echo -ne "\n\n" >> $thelog

echo -ne "There are ${#datasets[@]} datasets to submit \n\n" >> $thelog

for d in "${datasets[@]}"
do
  echo "Now on $d"

  t="$(date +%s)"
   
  y=`expr $y + 1`

  #Send info to master
  sed -i 's@^name=.*@'"name=$d"'@g' master.sh 
  thetime=`date`
  echo "===> Preparing dataset #$y: $d .. $thetime" >> $thelog

  sh master.sh > /dev/null
  echo -ne "\tSubmitted all jobs.. " >> $thelog 
  a=0
  while true ; do 
    a=`expr $a + 1`
    sleep $timewait
    treedone=$(condor_q $fulluser | tail -1)
    jobsleft=${treedone:0:1}
    if [[ $jobsleft -eq 0 ]] 
    then 
      thetime=`date`
      echo "  .. starting postmortem .. $thetime" >> $thelog
      sh postmortem.sh 1 > /dev/null
      a=0
      break
    fi
    if [[ $a -eq 1  ]] 
    then
      echo -ne "\n\tCheck if finished " >> $thelog
    fi
    echo -ne " ..$a" >> $thelog
  done 
  thetime=`date`
  echo -ne "\tFinished with this dataset .. $thetime \n" >> $thelog
  t="$(($(date +%s)-t))"
  timetaken=$(printf "\tTime it took to run this dataset: %02d:%02d:%02d\n\n" "$((t/3600))" "$((t/60))" "$((t%60))")
  echo -ne "$timetaken\n\n" >> $thelog

 
done

echo "**************************************************************************" >> $thelog
thetime=`date`
echo -ne "superscript is now done.. $thetime \n\n" >> $thelog

tt="$(($(date +%s)-tt))"
printf "Total time it took to run this script: %02d:%02d:%02d\n" "$((tt/3600))" "$((tt/60))" "$((tt%60))"
timetaken=$(printf "\tTotal time it took to run this script: %02d:%02d:%02d\n\n" "$((tt/3600))" "$((tt/60))" "$((tt%60))")
echo -ne "$timetaken\n\n" >> $thelog
echo "**************************************************************************" >> $thelog

exit
