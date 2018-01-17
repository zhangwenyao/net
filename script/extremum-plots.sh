#!/bin/bash

dir="data/extremum/nature"
dirPlt="config"
names=("2" "r-1" "1" "r-2" "(r-2)d1.5" "(r-2)d2" "(r-2)d3" "(2-r)d2" "2-r"
"1.5-r" "1-r")
for i in ${names[@]} ; do
  script/extremum-eps.sh "$dirPlt/extremum_${i}.plt" "${dir}/${i}" \"${dir}\"
done
