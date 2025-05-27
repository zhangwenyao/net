#!/bin/bash

beta=0.05

for  i in `seq 0 1`; do
  sleep 1
  echo "nohup ./bin/net.exe --config config/config_CondMat_beta${beta}_gamma1_$i.json > logs/CondMat_beta${beta}_gamma1_$i.log 2>&1 &"
  nohup ./bin/net.exe --config config/config_CondMat_beta${beta}_gamma1_$i.json > logs/CondMat_beta${beta}_gamma1_$i.log 2>&1 &
done

for  i in `seq 0 9`; do
  sleep 1
  echo "nohup ./bin/net.exe --config config/config_Email-Enron_beta${beta}_gamma1_$i.json > logs/Email-Enron_beta${beta}_gamma1_$i.log 2>&1 &"
  nohup ./bin/net.exe --config config/config_Email-Enron_beta${beta}_gamma1_$i.json > logs/Email-Enron_beta${beta}_gamma1_$i.log 2>&1 &
done

for  i in `seq 0 19`; do
  sleep 1
  echo "nohup ./bin/net.exe --config config/config_Facebook_beta${beta}_gamma1_$i.json > logs/Facebook_beta${beta}_gamma1_$i.log 2>&1 &"
  nohup ./bin/net.exe --config config/config_Facebook_beta${beta}_gamma1_$i.json > logs/Facebook_beta${beta}_gamma1_$i.log 2>&1 &
done
