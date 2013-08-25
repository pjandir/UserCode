#!/bin/bash

###################################################################
# Master script to split a dataset into individual cfA root files
# (the entire process always in development btw..)
# 
# Written by Pawandeep Jandir
##################################################################

#-------------
# Usage
#	Entire 'split' (note name) directory should be under NtupleTools
#
#	Enter name of dataset you want to split in 'name'
#		Dataset must live in 'cfadir'
#		Can change other user settings if needed, but not needed
#	Wait for all jobs to finish in the batch system
# 	Use postmortem (with argument 1) to finish the process
#		No modification is required but, certain behaviors can be changed if desired
#		See postmortem for more details
#-------------

##### User Settings 

#name=TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1798_v69
name=QCD_Pt-1800_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1822_v69

#Name of user. Do not leave blank! 
user=pj

#Subdirectory where many temp files are stored.
dirname=./files/

#Directory where cfA datasets are stored. Change with caution.  
cfadir=/mnt/hadoop/cms/store/users/cfA/2012

#####


#Do some error-checking to make sure things will run smoothly in the process
if [[ $name == *txt ]]
then
  echo -e "Error: Remove .txt from end of file name"
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
if [[ ! -f ../btagEffMaps/histos_btageff_csvm_${name}.root ]] 
then
  echo -e "Error: btageff histo file does not exist"
  exit
fi

#Full path to directory where the reducedTree/EventCalculator_cfA code lives
#There is a better way to code this, and I'll figure it out later.  
here=$(pwd -P) #-P option not universal. One reason this method should be updated. 
cd ..
thepath=$(pwd -P)
cd $here

#Create some directories in case they don't exist yet
mkdir -p trees           #Make a dir for the individual tree files
mkdir -p logs            #Make a dir for condor log files
mkdir -p reducedTrees    #Make a dir for final reducedTree location. Duplicated in postmortem. 
mkdir -p $dirname        #Make a dir for temp files

#
sample=$(root -l -b -q 'GetSampleName.C("'$name'")' | tail -1) 
echo The sample to be done is $sample

sleep 1
echo -e "\nPreparing files.\n\n"
sleep 2

#Loop through the dataset text file and create a new text file for each individual cfA root file
#Use skeletons to create new files to submit to condor as batch jobs
#Each cfA root file is treated as a separate soon-to-be reducedTree--one batch job to each
while read p; do

  y=`expr $y + 1` 
  cp ../btagEffMaps/histos_btageff_csvm_${name}.root ../btagEffMaps/histos_btageff_csvm_${name}_batch_$y.root 

  echo $p > ${name}_batch_$y.txt
  mv ${name}_batch_$y.txt ..
   
  sed -e 's@dummy.txt@'${name}_batch_$y.txt'@g' -e 's@dumNum@'$y'@g' -e 's@dumPath@'$thepath'@g' skeleton.sh > ${user}_${sample}_$y.sh

  sed -e 's@dummy.sh@'$dirname/${user}_${sample}_$y.sh'@g' -e 's@sampleName@'$sample'@g' -e 's@dumPath@'$thepath'@g' skeleton.jdl > ${user}_${sample}_$y.jdl 

  mv ${user}_${sample}_$y.sh ${user}_${sample}_$y.jdl $dirname
  condor_submit ${dirname}${user}_${sample}_$y.jdl

done < ./../$name.txt

echo -e "\nSubmitted $y batch files for $sample."

#Send various variables/things to postmortem
sed -i 's@^nfiles=.*@'"nfiles=$y"'@g' postmortem.sh 
sed -i 's@^name=.*@'"name=$name"'@g' postmortem.sh 
sed -i 's@^user=.*@'"user=$user"'@g' postmortem.sh 
sed -i 's@^dirname=.*@'"dirname=$dirname"'@g' postmortem.sh 

exit
