#!/bin/bash

for  i in `seq 0 9`; do
  sleep 1
  nohup ./bin/net.exe --config config/config_Email-Enron_beta0.05_gamma1_$i.json >  logs/Email-Enron_beta0.05_gamma1_$i.log 2>&1 &
done