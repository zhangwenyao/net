#!/bin/bash

if [ ! $# -eq 2 ];then
  echo "$0 'plt' 'name'"
  exit 1
fi

dir="data/extremum/nature"

script/extremum-eps.sh "$1" "${dir}/$2" \"${dir}\"
