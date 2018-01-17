#!/bin/bash

dir="`pwd`/data/extremum/sqrt"

for i in `seq 5 29` ; do
  for s in `seq 1 300` ; do
    echo "$dir/2^$i/2^${i}.Min_${s}.lkk3.txt" "$dir/2^$i/2^${i}_${s}.Min.lkk3.txt"
    mv "$dir/2^$i/2^${i}.Min_${s}.lkk3.txt" "$dir/2^$i/2^${i}_${s}.Min.lkk3.txt"
  done
done
