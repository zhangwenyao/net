#!/bin/bash

reset
date
echo BEGIN...

#gamma=(2.7)
nn=(32768	65536	131072	262144)
#nn=(128	256	512	1024	2048	4096	8192	16384	32768	65536	131072	262144)
seed1=1; seed2=300
for n in ${nn[@]}; do
    echo "n=$n"
    name=Min2.7_${n}
    mkdir ${name}
    cd ${name}
    #for ((seed=seed1; seed<=seed2; seed++)); do
    ~/test/net/bin/net --nodeSize ${n} > ../net.log/${name}.log 2>1&
    #done
    cd ..
done

echo "END"
date

