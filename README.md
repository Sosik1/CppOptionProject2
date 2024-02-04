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

## API Usage

To use the c++ API, you need to include the Option and VarianceCalculator header classes. Option type and contract type also need to be included.

```cpp

#include "Option.hpp"
#include "VarianceCalculator.hpp"
#include "option_type.hpp"
#include "contract_type.hpp"

```

Next, create an option that will be added to the portfolio. Pass parameters to the constructor of the class:

```cpp

// Constructor:
// Option(double strike, option_type option_type, contract_type contract_type, double ttm, int volume)

Option newOption = Option(5000, call, longPosition, 60, 5);

```

Initialize a new instance of the VarianceCalculator class. Pass the parameters of the simulation of the underlying asset:

```cpp

// Constructor:
// VarianceCalculator(int N, double r, double sigma, double S_0, double dt)
// N: simulation resolution, r: annual return of underlying, sigma: standard deviation of underlying
// S_0: initial price of underlying, dt: time delta used in simulation (currently has to be = t / 365.0)

VarianceCalculator vc = VarianceCalculator(N, r, sigma, S_0, dt);

```

When the VarianceCalculator is initialized, it will precompute the simulation of the underlying asset and store it in memory. It is recommended to initialize this object before market open, and then call the addNewOption() method sequentially on an ad-hoc basis. 

Add the new option to the VarianceCalculator:

```cpp

vc.addNewOption(newOption);

```

Now, you can call the respective methods to get expected return and variance of the portfolio:

```cpp

double mean = vc.getPortfolioMean();
double varia = vc.estimateVariance();

```

If at any point, more options are to be added to the portfolio, add them sequentially using the addNewOption() method and pass in a Option object.

To reset the portfolio of options, run the reset() method:

```cpp

vc.reset();

```

### Complete API Usage Example

```cpp

#include "Option.hpp"
#include "VarianceCalculator.hpp"
#include "option_type.hpp"
#include "contract_type.hpp"

Option newOption = Option(5000, call, longPosition, 60, 5);

VarianceCalculator vc = VarianceCalculator(N, r, sigma, S_0, dt);

vc.addNewOption(newOption);

double mean = vc.getPortfolioMean();
double varia = vc.estimateVariance();

vc.reset();

```