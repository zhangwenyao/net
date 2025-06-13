#!/bin/bash

datasets=("CondMat" "EmailEnron" "Facebook")
betas=(0.05 0.1 0.2)
for dataset in ${datasets[@]}; do
  for beta in ${betas[@]}; do
    ./bin/net.exe --config config/config_${dataset}_beta${beta}_gamma1.json
  done
done
