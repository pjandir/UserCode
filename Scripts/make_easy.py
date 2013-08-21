#/usr/bin/env python

# You most likely will have to change line 14. 

import os,sys,re,random
from string import *

f = file(sys.argv[1]+"_list.txt" , "r")
w = file(sys.argv[1]+"_copy.txt" , "w")

for line in f.readlines():
   word = line.split()
   file = word[1].split("/")
   w.write("srm://osg-se.cac.cornell.edu:8443/srm/v2/server?SFN=" + word[1] + " " + "file:/home/cms/pjandir/down/CMSSW_4_2_3/src/reducedTrees_cfA/"+sys.argv[1]+"/" +file[9] + '\n')
#   w.write("srm://osg-se.cac.cornell.edu:8443/srm/v2/server?SFN=" + word[1] + " " + "file:/mnt/hadoop/cms/store/users/cfA/2012/reducedTrees/"+sys.argv[1]+"/reducedTrees_cfA/" +file[9] + '\n')
#   w.write("srm://hepse01.colorado.edu:8443/srm/v2/server?SFN=" + word[1] + " " + "file:/mnt/hadoop/cms/store/users/cfA/2012/reducedTrees/"+sys.argv[1]+"/" +file[7] + '\n')

f.close()
w.close()

