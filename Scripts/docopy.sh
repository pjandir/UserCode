#!/bin/bash

cat $1 | while read SRC DST; do
    lcg-cp --verbose -b -D srmv2 $SRC $DST
done
