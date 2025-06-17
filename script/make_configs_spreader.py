#!/usr/bin/env python
# -*- coding: utf-8 -*-
import json
import os.path

datasets = [
    "cond-mat-2003",
    "p2p-Gnutella30",
    "EmailEnron",
    "cond-mat-2005",
    "p2p-Gnutella31",
    "Facebook",
    "www",
]
kStatDir2 = "1.5lambdac"
n = 2
mi = 1
ma = 10000

cur_dir = os.path.dirname(os.path.abspath(__file__))
dir = os.path.join(cur_dir, "..", "config", f"spreader_{kStatDir2}")
configs = {
    "kSeedMin": mi,
    "kSeedMax": ma,
    "kDataDir": "data/spreader",
    "kStatDir": "data/spreader",
    "kStatDir2": kStatDir2,
    "kLambdac": 1.5,
    "kCalcFlag": True,
    "kStatFlag": True,
    "kDatasetNames": datasets[:1],
    "version": "3.0.20250610",
}


def main():
    os.path.mkdirs(dir)
    for dataset in datasets:
        configs["kDatasetName"] = [dataset]
        for i in range(n):
            if n <= 0:
                left = mi
                right = ma
                file_name = os.path.join(dir, f"{dataset}.json")
            else:
                left = mi + i * (ma - mi + 1) // n
                right = mi + (i + 1) * (ma - mi + 1) // n - 1 if i < n - 1 else ma
                file_name = os.path.join(dir, f"{dataset}_{i}.json")
            with open(file_name, "w", encoding="utf-8") as f:
                configs["kSeedMin"] = left
                configs["kSeedMax"] = right
                json.dump(configs, f, ensure_ascii=False, indent=4)
            print(f"{file_name} created")


if __name__ == "__main__":
    main()
