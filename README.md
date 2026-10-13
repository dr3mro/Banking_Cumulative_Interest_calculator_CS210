# Banking Application

This project is a C++ console application for projecting the growth of an
investment over a user-selected number of years. It was developed for the
SNHU CS-210 Project Two assignment.

The application accepts an initial investment, a recurring monthly deposit, an
annual interest rate, and an investment duration. It then prints monthly
balance tables for:

1. Growth without additional monthly deposits.
2. Growth with the configured monthly deposit.

Each report includes the month, opening amount, deposited amount, total before
interest, interest earned, and closing balance.

## Requirements

- A C++ compiler with C++20 support
- GNU Make (for the Makefile workflow)
- Doxygen (only required to regenerate the API documentation)

The project also includes a Visual Studio project file,
[`BankingApp.vcxproj`](./BankingApp.vcxproj), configured for C++20.

## Building and running

From the project directory, run:

```sh
make build
make run
```

The executable is written to `build/bin/banking` on macOS and Linux, or
`build/bin/banking.exe` on Windows.

The `build` target also regenerates the Doxygen documentation. To build,
regenerate documentation, and run the program in one command:

```sh
make
```

For a debug build with debugging symbols:

```sh
make debug
```

To remove compiled object files and the executable:

```sh
make clean
```

### Building without Make

The two source files can be compiled directly with any C++20 compiler:

```sh
c++ -std=c++20 -Wall -Wextra -pedantic rf-banking.cpp rf-bankingMain.cpp -o banking
./banking
```

On Windows, open `BankingApp.slnx` or `BankingApp.vcxproj` in Visual Studio
and build the desired configuration.

## Using the application

When the program starts, enter the following values when prompted:

| Input | Description | Accepted values |
| --- | --- | --- |
| Initial investment | Starting balance | At least `1.0` |
| Monthly deposit | Amount added each month in the deposit report | At least `1.0` |
| Interest rate | Annual interest rate, entered as a percentage | At least `1.0` |
| Number of years | Projection length | At least `1` |

Input is read and validated as complete lines. The program continues prompting
until each value is numeric, contains no trailing characters, and meets its
minimum value.

After the input summary is displayed, press **Enter** to generate the reports.
Press **Enter** at the final prompt to exit.

## Calculation model

The annual interest rate is converted to a monthly decimal rate:

```text
monthly rate = annual rate / 100 / 12
```

For every month, the application:

1. Uses the previous month's closing balance as the opening balance.
2. Adds the monthly deposit when generating the deposit report.
3. Calculates interest on the resulting total.
4. Adds the interest to produce the closing balance.

The report values are displayed with two decimal places. The calculation
continues from the unrounded internal `double` values.

## Project structure

| File or directory | Purpose |
| --- | --- |
| [`rf-banking.h`](./rf-banking.h) | `Banking` class declaration and report formatting constants |
| [`rf-banking.cpp`](./rf-banking.cpp) | Balance calculations, formatting, and report output |
| [`rf-bankingMain.cpp`](./rf-bankingMain.cpp) | Program entry point and input validation helpers |
| [`Makefile`](./Makefile) | Build, run, debug, documentation, and cleanup targets |
| [`BankingApp.vcxproj`](./BankingApp.vcxproj) | Visual Studio project configuration |
| [`Doxyfile`](./Doxyfile) | Doxygen configuration |
| [`html/`](./html/) | Generated HTML API documentation |
| [`latex/`](./latex/) | Generated LaTeX documentation |

## API documentation

To regenerate the documentation after changing the source:

```sh
make docs
```

Open [`html/index.html`](./html/index.html) in a browser to browse the
generated class and function reference.

## Notes

- The program prints both report types during each run.
- The monthly deposit is applied before monthly interest is calculated.
- The application is intentionally interactive and does not accept command-line
  arguments or read from an input file.
