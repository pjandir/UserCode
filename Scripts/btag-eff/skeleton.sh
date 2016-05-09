#!/bin/sh

file=dummy.txt
mgl=DUM1
mlsp=DUM2
mod=DUM3

# User specific aliases and functions
export VO_CMS_SW_DIR=/data/bottom/osg_app/cmssoft/cms
source $VO_CMS_SW_DIR/cmsset_default.sh

cd /home/cms/pjandir/down/april21_signalScans/CMSSW_5_3_8/src/NtupleTools/BasicLoopCU

export CVSROOT=:pserver:anonymous@cmscvs.cern.ch:/cvs_server/repositories/CMSSW

ROOTSYS=/data/bottom/osg_app/cmssoft/cms/slc5_amd64_gcc462/lcg/root/5.32.00

export LD_LIBRARY_PATH=$ROOTSYS/lib:$PYTHONDIR/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$ROOTSYS/lib:$PYTHONPATH
export SCRAM_ARCH=slc5_amd64_gcc462

alias setlha='export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:lib && export LHAPATH=share/lhapdf'

cmsenv
setlha

root -l -b -q 'EffVariation.C("'/home/cms/pjandir/down/CMSSW_4_2_3/src/reducedTrees_cfA/T1tttt_mad_UCSB1776/$file'",0,'$mgl','$mlsp',"'$mod'","'H'")'
root -l -b -q 'EffVariation.C("'/home/cms/pjandir/down/CMSSW_4_2_3/src/reducedTrees_cfA/T1tttt_mad_UCSB1776/$file'",0,'$mgl','$mlsp',"'$mod'","'L'")'
root -l -b -q  'CountEvents.C("'/home/cms/pjandir/down/CMSSW_4_2_3/src/reducedTrees_cfA/T1tttt_mad_UCSB1776/$file'",'$mgl','$mlsp',0,"'$mod'")'

exit

