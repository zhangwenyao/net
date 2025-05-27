#!/bin/bash

for  i in `seq 0 1`; do
  sleep 1
  nohup ./bin/net.exe --config config/config_CondMat_beta0.05_gamma1_$i.json > logs/CondMat_beta0.05_gamma1_$i.log 2>&1 &
done