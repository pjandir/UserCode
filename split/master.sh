#!/bin/bash

###########################################################################################
# Master script to split a dataset into individual cfA root files to make reducedTrees
# 
# 
#   - This entire process is still in development
#     - It is not mandatory to be completely up-to-date to the code however
#       - Though it is recommended
#   - Please report to the author for bug reports and any other requests
#
#
# Written by: Pawandeep Jandir
###########################################################################################

# Some notes:
#
# Entire "split" (can change that name, if desired) directory should be under NtupleTools
# ROOT and hadd are used in this process, so make sure ROOT is sourced properl

#-------------
# Usage
#	Enter name of dataset you want to split in 'name'
#		Dataset must live in 'cfadir'
#		Can change other user settings if needed, but not needed
#	Wait for all jobs to finish in the batch system
# 	Use postmortem (with argument 1) to finish the process
#		No modification is required but, certain behaviors can be changed if desired
#		See postmortem for more details
#-------------

##### User Settings 

#Full cfA name of dataset
name=TTJets_WToBC_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V19-v1_AODSIM_UCSB1966_v71

#Name of user. Keep it short with no spaces. Do not leave blank! 
user=pj

#Directory where cfA datasets are stored. Change with caution.  
cfadir=/mnt/hadoop/cms/store/users/cfA/2012

#Number of cfA root files per batch job. Default is one. 
multiple=1

#Subdirectory where many temp files are stored.
subdir=./files/

#Produce btag efficiency variables. If this is not needed/wanted, it is safe to turn off.
btageff=true

#Mode for testing purposes
debug=false

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
if [[ ! -d $cfadir ]]  
then
  echo -e "Error: The cfA directory does not seem to exist. Please check the file system."
  exit
fi
if [[ ! -f ../$name.txt ]] 
then
  echo -e "Sample text file does not seem to exist: $name.txt\n"
  echo -e "Will attempt to make one..."
  sleep 5

  echo -e "\nDataset: $name"
  echo -e "cfA dir: $cfadir"

  if [[ ! -d $cfadir/$name  ]]
  then
    echo -e "Error: Dataset does not exist in the cfA directory"
    exit
  fi

  for file in $cfadir/$name/*.root
  do
    echo $file >> $name.txt 
  done
  mv $name.txt .. 
  echo -e "\nCreated text file: $name.txt\n"  
fi
count=$(cat ../$name.txt | wc -l)
if [[ $count -eq 0 ]]
then
  echo -e "Error: No files in $name.txt \nCheck text file"
  exit
fi
if [[ ! -f ../btagEffMaps/histos_btageff_csvm_${name}.root ]] && $btageff;
then
  echo -e "Error: btageff histo file does not exist"
  exit
fi


t="$(date +%s)"

#Get some paths that are needed
fullpath="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )" 	#Full path to the directory where this script lives
thisdir=${fullpath##*/} 					#Name of this directory where this script lives
thepath=${fullpath%${thisdir}} 					#Full path to directory where the reducedTree/EventCalculator_cfA code lives

#Create some directories in case they don't exist yet
mkdir -p trees           #Make a dir for the individual tree files
mkdir -p logs            #Make a dir for condor log files
mkdir -p reducedTrees    #Make a dir for final reducedTree location. Duplicated in postmortem. 
mkdir -p $subdir        #Make a dir for temp files

#
sample=$(root -l -b -q 'GetSampleName.C("'$name'")' | tail -1) 
echo The sample to be done is $sample

#Send various variables/things to postmortem
sed -i 's@^name=.*@'"name=$name"'@g' postmortem.sh 
sed -i 's@^user=.*@'"user=$user"'@g' postmortem.sh 
sed -i 's@^subdir=.*@'"subdir=$subdir"'@g' postmortem.sh 
sed -i 's@^btageff=.*@'"btageff=$btageff"'@g' postmortem.sh 

sleep 1
echo -e "\nPreparing files.\n\n"
sleep 2

#Loop through the dataset text file and create a new text file for each individual cfA root file
#Use skeletons to create new files to submit to condor as batch jobs
#Each cfA root file is treated as a separate soon-to-be reducedTree--one batch job to each
while read p; do

  y=`expr $y + 1` 

  if ! $debug ;
  then 

    if $btageff ;
    then
      cp ../btagEffMaps/histos_btageff_csvm_${name}.root ../btagEffMaps/histos_btageff_csvm_${name}_batch_$y.root 
    fi

    echo $p > ${name}_batch_$y.txt
    for (( a=1; a<$multiple; a++ ))
    do  
      read p2 
      echo $p2 >> ${name}_batch_$y.txt
    done 

    mv ${name}_batch_$y.txt ..
 
    sed -e 's@dummy.txt@'${name}_batch_$y.txt'@g' -e 's@dumNum@'$y'@g' -e 's@dumPath2@'$thisdir'@g' -e 's@dumPath@'$thepath'@g' skeleton.sh > ${user}_${sample}_$y.sh

    sed -e 's@dummy.sh@'$subdir/${user}_${sample}_$y.sh'@g' -e 's@sampleName@'$sample'@g' -e 's@dumPath@'$fullpath'@g' skeleton.jdl > ${user}_${sample}_$y.jdl 

    mv ${user}_${sample}_$y.sh ${user}_${sample}_$y.jdl $subdir
    condor_submit ${subdir}${user}_${sample}_$y.jdl >/dev/null

    echo -ne "."

    mo=$(((y+1)%710))
    if [[ $mo -eq 0 ]]
    then
      sleep 120
    fi

  fi

done < ./../$name.txt

echo -e "\n\nSubmitted $y batch files for $sample."

#Also send number of files
sed -i 's@^nfiles=.*@'"nfiles=$y"'@g' postmortem.sh 

t="$(($(date +%s)-t))"
printf "\nTime it took to run this program: %02d:%02d:%02d\n" "$((t/3600))" "$((t/60))" "$((t%60))"

exit
