# C++ Option Portfolio Variance Calculator

This software serves to compute payout variance of a portfolio of options (before and after each purchase)

This program can be used to check whether the next purchase will fit within a variance constraint
The class can track the sequence of purchases, allowing for a reset to a blank portfolio when necessary.

Created in 2024 by Rafal K and Nhan N as part of the C++ in Quantitative Finance course at the University of Warsaw

## Getting Started

You can use this program as standalone or integrate it with your own C++ code by including Portfolio.h.

### Prerequisites

These are required to compile and build this project:
* gcc
* g++
* cmake
* MSBuild (Visual Studio 2022)

### Installation

1. Clone the repo

```sh
git clone https://github.com/github_username/repo_name.git
```

2. (Optional) Compile using MSBuild. The executable files have been provided in the release. Along with the sample input files.

## Usage

To run the program, execute the following command:

```sh
CppOptionProject.exe (options)
```

To run the program, with input file "sample_large.csv" the following command should be executed:

```sh
CppOptionProject.exe -f sample_large.csv
```

Available options:

* -f: file name (default: input.csv)
* -n: number of samples N (default: 30 000)
* -r: average annual return of underlying (default: 5%)
* -s: standard deviation of the price of underlying (default: 20%)
* -s0: initial price of underlying (default: 5 000)
* -t: time to expiration of the option in days (default: 60 days)
* -vl or --variance-limit: variance cutoff of the program (default: 1 billion)