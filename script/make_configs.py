#!/usr/bin/env python
# -*- coding: utf-8 -*-
import json
import os.path

dataset = "www"
n = 15
# dataset = "EmailEnron"
# n = 10
# dataset = "Facebook"
# n = 20
# beta = 0.05
# beta_s = "0.05"
# gamma = 1.0
# gamma_s = "1"
mi = 7
ma = 1000
cur_dir = os.path.dirname(os.path.abspath(__file__))
dir = os.path.join(cur_dir, "..", "config")
configs = {
    "kSeedMin": 7,
    "kSeedMax": 10000,
    "kDataDir": "data/spreader",
    "kStatDir": "data/spreader",
    "kStatDir2": "2.0lambdac",
    "kLambdac": 2.0,
    "kCalcFlag": True,
    "kStatFlag": True,
    "kDatasetNames": ["www"],
    "version": "3.0.20250610",
}


def main():
    for i in range(n):
        l = mi + int(i * (ma - mi + 1) / n)
        r = mi + int((i + 1) * (ma - mi + 1) / n) - 1 if i < n - 1 else ma
        file_name = os.path.join(dir, f"spreader_{dataset}_{i}.json")
        with open(file_name, "w", encoding="utf-8") as f:
            configs["kSeedMin"] = l
            configs["kSeedMax"] = r
            json.dump(configs, f, ensure_ascii=False, indent=4)
        print(f"{file_name} created")


if __name__ == "__main__":
    main()
