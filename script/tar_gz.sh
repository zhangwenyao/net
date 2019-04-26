#!/bin/sh

dir="/media/yao/Server1T/net/data/extremum/nature/2.5_4"
cd $dir
for i in `seq 33 33` ; do
  name="2^$i"
  echo "${name}"
  tar -zcvf "${name}.tar.gz" "${name}"
  rm -rf "${name}"
done

