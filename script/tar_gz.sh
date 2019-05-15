#!/bin/sh

dir="/media/yao/Server1T/net/data/extremum/nature/2.5_4/"
dir2="/media/yao/YAO2/2.5_4/"
cd $dir
for i in `seq 60 60` ; do
  name="2^$i"
  echo "${name}"
  tar -zcvf "${dir2}${name}.tgz" "${name}"
  rm -rf "${name}"
done

