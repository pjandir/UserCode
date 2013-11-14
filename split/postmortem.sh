#!/bin/bash

###########################################################################################
# Finish the job by removing ancillary files and add everything back together
# Command Line Argument required
# 	- A '1' to recombine trees into one, final reducedTree
#	- Anything else to delete all trees and not combine them
###########################################################################################

##### User settings
#Modify the final reducedTree file name, otherwise leave blank
#Please add "_" to the front, if you use it!
mod=

#Destination folder for final reducedTree in working directory
destfolder=reducedTrees

#File limit for hadd--try not to change
fileLimit=900
#####


##### Non-user settings (i.e. do not touch)
#Name of dataset. Written by master.
name=TTWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB1857_v71
#Number of files (or jobs) submitted. Written by master. 
nfiles=14
#Subdirectory where many temp files are stored. Written by master. 
subdir=./files/
#User name. Written by master. 
user=pj
#Worry about btag efficiency. Written by master. 
btageff=false
#####


#Error checking
root -l -b -q > trash.txt
rval=$?
rm trash.txt
if [[ $rval -ne 0 ]]
then
  echo -e "Error: ROOT not found. Is cmsenv (or similar) set?"
  exit
fi
if [[ $# -ne 1 ]]
then
  echo Error: usage. Provide argument to recombine trees. 
  exit
fi
if [[ ! $(ls -A  ./trees)  ]]
then
  echo Warning: There is nothing in ./trees!
  sleep 10
fi
mkdir -p $destfolder

t="$(date +%s)"

#
sample=$(root -l -b -q 'GetSampleName.C("'$name'")' | tail -1) 
echo The sample to be done is $sample


echo Deleting supplementary files created from splitting process.
sleep 1

rm ../${name}_batch_*.txt
rm $subdir${user}_${sample}_*.sh
rm $subdir${user}_${sample}_*.jdl
if $btageff; 
then
  rm ./../btagEffMaps/histos_btageff_csvm_${name}_batch_*.root 
fi

if [ $1 -eq 1  ]
then 

  #
  tname=$(ls trees/*root | head -1) 
  treename=$(root -l -b -q 'GetTreeName.C("'$tname'")' | tail -1)
  echo The sample will be written to ./${destfolder}/$treename${mod}.root

  if [[ -f ./${destfolder}/${treename}${mod}.root  ]]
  then
    echo -ne "\n\nWARNING: ${treename}${mod}.root already exists in the ${destfolder} directory. Overwriting in 10 seconds... "
    for ai in {1..10}
    do 
      sleep 1 
      echo -ne "..$ai"  
    done 
    sleep 1
    echo -e "\n"
  fi
  
  echo Adding reducedTrees back together.

  count=$(ls -l ./trees/*.root | wc -l )
  if [[ $count -ne $nfiles ]]
  then
    echo -e "\nWarning: Number of submitted jobs was $nfiles but number of split root files is $count.\n" 
    sleep 10
  fi 
  if [[ $count -gt $fileLimit ]] 
  then
    echo -e "\nThere are more files ($count) than are accepted (999) by hadd. Splitting the job (again)."
    echo -ne "Also as a warning, all files in trees will be destroyed in this process. sleeping... "
    for bi in {1..10}
    do 
      sleep 1 
      echo -ne "..$bi"  
    done 
    sleep 1
    echo ""
    mkdir partTrees
  
    # The idea here is to make a temp dir to successively hadd together an appropriate amount of files.
    # So, move files away from "trees" and hadd together the first piece. We continue until there is nothing
    # left in "trees." Then we hadd together all those pieces into the destination folder. 
    # Delete the temp dir at the end.

    echo "Begin hadd split process.."
    # This really is like a while loop.. we have no idea how many iterations it will really take beforehand. 
    # But we could in principle handle fileLimit^2 number of files.
    for (( a=1; a < $fileLimit; a+=1 )) 
    do 
      # If there are no more files left, then stop.
      if [[ $b -eq $count  ]]
      then
        break
      fi 
      mkdir haddTrees
      # Actual loop.. the 'c' variable makes this a do while loop basically
      # It will run over the fileLimit number of files
      # Note there are (in the first loop, at least) more files in the directory than fileLimit so we move 
      # files away and hadd the pieces first. 
      for treefile in ./trees/*.root  
      do
        b=`expr $b + 1` #count total number of files processed 
        c=`expr $c + 1` #count to the fileLimit and stop this for loop when limit reached.
        mv $treefile ./haddTrees
        echo -n .
        if [[ $c -eq $fileLimit ]] 
        then 
          break
        fi
      done
      hadd -f ./partTrees/part${a}.root ./haddTrees/*.root > trash.txt #Hadd with -stoptalking enabled
      rm -r trash.txt haddTrees
      c=0
      echo -e "\nCompleted: $b / $count."
    done
    echo Hadding together final piece: ${treename}${mod}.root ..
    hadd -f ./${destfolder}/${treename}${mod}.root ./partTrees/*root > trash.txt
    rm -r trash.txt partTrees
    echo Finished hadd process.

   else
     hadd -f ./${destfolder}/${treename}${mod}.root ./trees/reducedTree*root > trash.txt
     rm trash.txt
   fi

else
  echo -e "\nWarning--Not adding reducedTrees back together: deleting all batch ones.\n"
fi

tfiles=$(ls ./trees/*.root 2> /dev/null | wc -l)
if [ "$tfiles" != "0" ]
then
  echo Deleting initial root files in dir: ./trees/
  rm ./trees/*.root
fi


t="$(($(date +%s)-t))"
printf "Time it took to run this program: %02d:%02d:%02d\n" "$((t/3600))" "$((((t/60))%60))" "$((t%60))"

exit
