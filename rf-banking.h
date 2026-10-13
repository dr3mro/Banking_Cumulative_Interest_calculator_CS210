/*
 * Amr Osman
 * amr.osman@snhu.edu
 * CS-210-12997- Project Two Banking
 */

#pragma once
#ifndef banking_h
#define banking_h

 // Provides the std::string type used by the class interface.
#include <string>

// Sets the width used by report banners.
constexpr int INPUT_DETAILS_WIDTH = 38; // Width of the input details section
constexpr char INPUT_DASH_CHAR = '-'; // Character used for dashed lines
constexpr char INPUT_FILL_CHAR = ' '; // Character used for padding
constexpr char INPUT_CORNER_CHAR = '+'; // Character used for table corners
constexpr char INPUT_BORDER_CHAR = '|'; // Character used for table borders
constexpr int INPUT_KEY_WIDTH = 25; // Width of the input key column
constexpr int INPUT_VALUE_WIDTH = 10; // Width of the input value column


constexpr char BORDER_CHAR = '|'; // Character used for table borders
constexpr char FILL_CHAR = ' ';   // Character used for padding
constexpr char DASH_CHAR = '-';   // Character used for dashed lines
constexpr char CORNER_CHAR = '+'; // Character used for table corners
constexpr char EQ_CHAR = '=';         // Character used for the top banner border

constexpr int MONTHWIDTH = 5;
constexpr int OPENINGBALANCEWIDTH = 15;
constexpr int DEPOSITEDWIDTH = 16;
constexpr int TOTALWIDTH = 15;
constexpr int INTERESTWIDTH = 8;
constexpr int CLOSINGBALANCEWIDTH = 16;
constexpr int REPORT_WIDTH = 13 + MONTHWIDTH + OPENINGBALANCEWIDTH + DEPOSITEDWIDTH + TOTALWIDTH + INTERESTWIDTH + CLOSINGBALANCEWIDTH; // Total width of the report

// Allows standard-library names to be used without the std:: prefix.
using namespace std;

/**
 * @brief Stores investment inputs and generates balance reports.
 */
class Banking
{
private:
	// enum the deposit mode to be used in the report
	enum class ReportMode
	{
		WithMonthlyDepositsOnly,
		WithAndWithoutMonthlyDeposits
	};

	// Number of years included in each report.
	int NumYears{ 0 };
	double
		// Original amount invested.
		InitialInvestment{ 0.0 },
		// Recurring amount deposited each month.
		MonthlyDeposit{ 0.0 },
		// Annual rate stored as a whole-number percentage.
		InterestRate{ 0.0 },
		// Balance at the beginning of the current month.
		BeginningBalance{ 0.0 },
		// Interest calculated for the current month.
		Interest{ 0.0 },
		// Balance at the end of the current month.
		ClosingBalance{ 0.0 };

	/** @brief Prints the monthly balance report without recurring deposits. */
	void CalculateBalancesWithoutDeposits();

	/** @brief Prints the monthly balance report with recurring deposits. */
	void CalculateBalancesWithDeposits();

	/**
	 * @brief Calculates and prints a balance report for the selected deposit mode.
	 * @param withMonthlyDeposits Whether to include the configured monthly deposit.
	 */
	void CalculateBalancesImpl(const bool withMonthlyDeposits);

	/**
	 * @brief Prints a single row of the monthly balance table.
	 * @param month The current month number.
	 * @param year The current year number.
	 * @param openingBalance The balance at the beginning of the month.
	 * @param deposited The amount deposited this month.
	 * @param total The total balance before interest is applied.
	 * @return void This method writes the row to standard output.
	 */
	void DrawMonthlyRow(int month, int year, double openingBalance, double deposited, double total);

	/**
	 * @brief Prints a border whose segments match the table columns.
	 * @return void This method writes the border to standard output.
	 */
	void DrawBorder();

	/** @brief Asks the user to select a deposit mode.
	 * @return ReportMode The selected report mode.
	 * This is a dead code, but it is left in place for future use if the user is allowed to select a report mode.
	 */
	ReportMode GetReportMode();

	/** @brief Prints both balance reports, pausing between them. */
	void CalcBalance();

	/** @brief Carries the closing balance into the next monthly period. */
	void UpdateBalances();

	/**
	 * @brief Draws a centered title banner for a report section.
	 * @param bannerText Text to display in the banner.
	 */
	void DrawBanner(const string& bannerText);

	/** @brief Draw the headings and border for a balance table. */
	void DrawHeader();



public:
	/** @brief Creates an object with zero-valued investment inputs. */
	Banking() = default;
	/**
	 * @brief Sets the original investment amount.
	 * @param initialInvestment Amount invested at the start of the calculation.
	 */
	void setInitialInvestment(double initialInvestment);
	/**
	 * @brief Sets the investment duration.
	 * @param numYears Number of years to include in each report.
	 */
	void setNumYears(int numYears);
	/**
	 * @brief Sets the recurring monthly deposit.
	 * @param monthlyDeposit Amount deposited each month in the deposit report.
	 */
	void setMonthlyDeposit(double monthlyDeposit);
	/**
	 * @brief Sets the annual interest rate.
	 * @param interestRate Annual interest rate as a whole-number percentage.
	 */
	void setInterestRate(double interestRate);
	/** @brief Returns the investment duration. */
	int getNumYears() const;
	/** @brief Returns the original investment amount. */
	double getInitialInvestment() const;
	/** @brief Returns the recurring monthly deposit. */
	double getMonthlyDeposit() const;
	/** @brief Returns the annual interest rate. */
	double getInterestRate() const;
	/** @brief Calculates and prints both balance reports. */
	void displayBalances();
	/**
	 * @brief Centers text within a field of the requested length.
	 * @param text Text to center.
	 * @param length Total width of the resulting field.
	 * @param fill Character used to pad the field.
	 * @return The padded, centered text, or the original text if it is too long.
	 */
	string centerText(string text, int length, char fill = ' ');
	/**
	 * @brief Prints a repeated character string.
	 * @param times Number of times to repeat the character.
	 * @param charToPrint Character to repeat.
	 */
	void printChar(int times, char charToPrint = ' ');
	/** @brief Prints the configured investment input values. */
	void printInputDetails();
};

#endif
