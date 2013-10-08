#!/bin/sh

file=dummy.txt

# User specific aliases and functions
export VO_CMS_SW_DIR=/data/bottom/osg_app/cmssoft/cms
source $VO_CMS_SW_DIR/cmsset_default.sh

cd dumPath

ROOTSYS=/data/bottom/osg_app/cmssoft/cms/slc5_amd64_gcc462/lcg/root/5.32.00
export LD_LIBRARY_PATH=$ROOTSYS/lib:$PYTHONDIR/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$ROOTSYS/lib:$PYTHONPATH
export SCRAM_ARCH=slc5_amd64_gcc462

#alias cmsenv='eval `scramv1 runtime -sh`'
alias setlha='export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:lib && export LHAPATH=share/lhapdf'

setlha
cmsenv

./run_Analysis $file 
mv reducedTree*batch_dumNum.root ./dumPath2/trees

exit
