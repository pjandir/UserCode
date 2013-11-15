#!/bin/bash

dir=/mnt/hadoop/cms/store/users/cfA/2012

if [[ $# -ne 1 ]]
then
  echo Error: usage. Provide argument.
  exit
fi

mkdir $dir/$1
chown pjandir:cms $dir/$1
chmod 775 $dir/$1

echo ""
cd $dir/$1
pwd -P
echo ""

exit


