#!/bin/bash

reset
date
echo BEGIN...

gamma=(2.7)
nn=(128	256	512	1024	2048	4096	8192	16384	32768	65536	131072	262144)
#nn=(128	256	512	1024)
#nn=(128	256	512	1024	2048	4096	8192	16384	32768	65536	131072	262144)
seed1=1; seed2=300
dir=(Min)
for d in ${dir[@]}; do
    echo "$r"
    for r in ${gamma[@]}; do
        echo "$r"
        touch ps.log sp.log kt.log
        for n in ${nn[@]}; do
            echo "n=$n"
            name=${d}${r}_${n}
            #mkdir $name
            #mv ${name}_*_*.txt ${name} 
            ~/test/bin/mean ${name}_ps.log --pearson ${name}/*_params.txt && cat ${name}_ps.log >> ps.log
            ~/test/bin/mean ${name}_sp.log --spearman ${name}/*_params.txt && cat ${name}_sp.log >> sp.log 
            ~/test/bin/mean ${name}_kt.log --kendallTau ${name}/*_params.txt && cat ${name}_kt.log >> kt.log
        done
        paste ps.log sp.log kt.log > ${dir}${r}.log
        rm *_ps.log ps.log *_sp.log sp.log *_kt.log kt.log
    done
done

echo "END"
date

