#!/usr/bin/env python
# -*- coding: utf-8 -*-
import json
import os.path

dataset = "CondMat"
n = 2
# dataset = "Email-Enron"
# n = 10
# dataset = "Facebook"
# n = 20
beta = 0.05
beta_s = "0.05"
gamma = 1.0
gamma_s = "1"
mi = 1
ma = 10000
cur_dir = os.path.dirname(os.path.abspath(__file__))
dir = os.path.join(cur_dir, '..', 'config')
configs = {
    "kSeedMin": 1,
    "kSeedMax": 10,
    "kDataDir": "data/spreader",
    "kStatDir2": f"beta{beta_s}_gamma{gamma_s}",
    "kDatasetNames": [
        dataset
    ],
    "kBeta": beta,
    "kGamma": gamma,
    "kCalcFlag": True,
    "kStatFlag": False,
    "version": "3.0.20250521"
}


def main():
    step = (ma - mi + 1) // n
    for i in range(n):
        l = mi + step * i
        r = mi + step * (i + 1) - 1 if i < n - 1 else ma
        file_name = os.path.join(dir,
                                 f"config_{dataset}_beta{beta_s}_gamma"
                                 f"{gamma_s}_{i}.json")
        with open(file_name, "w", encoding="utf-8") as f:
            configs["kSeedMin"] = l
            configs["kSeedMax"] = r
            json.dump(configs, f, ensure_ascii=False, indent=4)
        print(f"{file_name} created")


if __name__ == '__main__':
    main()
