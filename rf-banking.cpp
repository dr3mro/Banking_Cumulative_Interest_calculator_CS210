/*
 * Amr Osman
 * amr.osman@snhu.edu
 * CS-210-12997- Project Two Banking
 */

 // Provides console input/output operations.
#include <iostream>
// Provides alignment and decimal-formatting manipulators.
#include <iomanip>
// Declares the Banking class and its methods.
#include "rf-banking.h"
// Provides the std::string type and string utilities.
#include <string>

// Allows standard-library names to be used without the std:: prefix.
using namespace std;

/**
 * @brief Prints a centered title banner for a report section.
 * @param bannerText Text to display in the banner.
 * @return void This method writes the banner to standard output.
 */
void Banking::DrawBanner(const string& bannerText)
{
	// Separate the banner from the preceding report content.
	cout << endl;
	// Draw the top border using the configured report width.
	cout << std::string(REPORT_WIDTH + 6, EQ_CHAR) << endl;
	// Center the supplied title and leave a blank line below it.
	cout << centerText(bannerText, REPORT_WIDTH + 4, FILL_CHAR) << endl
		<< endl;
}

/**
 * @brief Prints the column headings and border for a balance table.
 * @return void This method writes the table header to standard output.
 */
void Banking::DrawHeader()
{
	// Print each table heading inside a pipe-delimited column.
	cout << BORDER_CHAR << FILL_CHAR << left
		<< setw(MONTHWIDTH) << "Month"
		<< FILL_CHAR << BORDER_CHAR << FILL_CHAR << setw(OPENINGBALANCEWIDTH) << "Opening Amount"
		<< FILL_CHAR << BORDER_CHAR << FILL_CHAR << setw(DEPOSITEDWIDTH) << "Deposited Amount"
		<< FILL_CHAR << BORDER_CHAR << FILL_CHAR << setw(TOTALWIDTH) << "Total"
		<< FILL_CHAR << BORDER_CHAR << FILL_CHAR << setw(INTERESTWIDTH) << "Interest"
		<< FILL_CHAR << BORDER_CHAR << FILL_CHAR << setw(CLOSINGBALANCEWIDTH) << "Closing Balance"
		<< FILL_CHAR << BORDER_CHAR << endl;

	// Print a border whose segments match the table columns.
	DrawBorder();
}

/**
 * @brief Calculates and prints monthly balances without additional deposits.
 * @return void This method updates balances and writes the report to standard output.
 */
void Banking::CalculateBalancesWithoutDeposits()
{
	CalculateBalancesImpl(false);
}

/**
 * @brief Calculates and prints monthly balances with recurring deposits.
 * @return void This method updates balances and writes the report to standard output.
 */
void Banking::CalculateBalancesWithDeposits()
{
	CalculateBalancesImpl(true);
}

/**
 * @brief Calculates and prints monthly balances for the selected deposit mode.
 * @param withMonthlyDeposits Whether to include the configured monthly deposit.
 * @return void This method updates balances and writes the report to standard output.
 */

void Banking::CalculateBalancesImpl(const bool withMonthlyDeposits)
{
	std::string title; // the report title
	double deposited;  // the monthly deposit
	// Convert the annual whole-number percentage to a monthly decimal fraction.
	const double monthlyRate = InterestRate * 0.01 / 12.0;
	if (withMonthlyDeposits)
	{
		title = "Balances and Interest With Additional Monthly Deposits";
		deposited = MonthlyDeposit;
	}
	else
	{
		title = "Balances and Interest Without Additional Monthly Deposits";
		deposited = 0.0;
	}

	// Start this report with the original investment.
	this->BeginningBalance = InitialInvestment; // reset for the report
	// Draws the report title for the selected deposit mode.
	DrawBanner(title);

	// Generate one table for each investment year.
	for (int year = 1; year <= NumYears; year++)
	{
		// Display the current year as a section heading.
		cout << CORNER_CHAR << centerText(" Year " + to_string(year) + FILL_CHAR, REPORT_WIDTH + 4, DASH_CHAR) << CORNER_CHAR << endl;
		DrawHeader(); // Print the column headings and border for the table.

		// Calculate and print the twelve months in the current year.
		for (int month = 1; month <= 12; month++)
		{
			// Capture the balance at the beginning of the month.
			double openingBalance = BeginningBalance;
			// Add the deposit before calculating interest.
			double total = openingBalance + deposited;
			// Calculate monthly interest from the total balance.
			Interest = total * monthlyRate;
			// Add the interest to determine the month's closing balance.
			ClosingBalance = total + Interest;
			// Carry the closing balance into the next month.
			UpdateBalances();

			DrawMonthlyRow(month, year, openingBalance, deposited, total);
		}
	}
	DrawBorder();

}

/**
 * @brief Prints a single row of the monthly balance table.
 * @param month The current month number.
 * @param year The current year number.
 * @param openingBalance The balance at the beginning of the month.
 * @param deposited The amount deposited this month.
 * @param total The total balance before interest is applied.
 * @return void This method writes the row to standard output.
 */
void Banking::DrawMonthlyRow(int month, int year, double openingBalance, double deposited, double total)
{
	// Print the completed monthly row with two decimal places.
	std::cout << BORDER_CHAR << FILL_CHAR << left << setw(MONTHWIDTH) << (month + (year - 1) * 12)
		<< FILL_CHAR << BORDER_CHAR << FILL_CHAR << fixed << setprecision(2) << setw(OPENINGBALANCEWIDTH) << openingBalance
		<< FILL_CHAR << BORDER_CHAR << FILL_CHAR << setw(DEPOSITEDWIDTH) << deposited
		<< FILL_CHAR << BORDER_CHAR << FILL_CHAR << setw(TOTALWIDTH) << total
		<< FILL_CHAR << BORDER_CHAR << FILL_CHAR << setw(INTERESTWIDTH) << Interest
		<< FILL_CHAR << BORDER_CHAR << FILL_CHAR << setw(CLOSINGBALANCEWIDTH) << ClosingBalance
		<< " |" << endl;
}

/**
 * @brief Prints a border whose segments match the table columns.
 * @return void This method writes the border to standard output.
 */
void Banking::DrawBorder()
{
	// Print a border whose segments match the table columns.
	std::cout << CORNER_CHAR << std::string(MONTHWIDTH + 2, DASH_CHAR) << CORNER_CHAR
		<< std::string(OPENINGBALANCEWIDTH + 2, DASH_CHAR) << CORNER_CHAR
		<< std::string(DEPOSITEDWIDTH + 2, DASH_CHAR) << CORNER_CHAR
		<< std::string(TOTALWIDTH + 2, DASH_CHAR) << CORNER_CHAR
		<< std::string(INTERESTWIDTH + 2, DASH_CHAR) << CORNER_CHAR
		<< std::string(CLOSINGBALANCEWIDTH + 2, DASH_CHAR) << CORNER_CHAR << endl;
}

/**
 * @brief Gets the user's preferred report mode.
 * @return ReportMode The selected report mode.
 * This is a dead code, but it is left in place for future use if the user is allowed to select a report mode.
 */

Banking::ReportMode Banking::GetReportMode()
{
	// Prompt the user to choose whether to see the report with or without monthly deposits.
	std::cout << "Do you want to see an extra report without monthly deposits? (y/N) (Enter for default): ";
	// Read the complete line so pressing Enter can select the default.
	std::string choice;
	// Use std::ws to skip leading whitespace before reading the line.
	std::getline(std::cin, choice);

	char selection{}; // Initialize selection to an empty character

	// If the user provided input, convert the first character to uppercase for comparison.
	if (!choice.empty())
		selection = toupper(choice[0]);

	// An empty response defaults to the report with monthly deposits.
	while (selection != 'Y' && selection != 'N' && !choice.empty())
	{
		// Prompt the user again for valid input.
		std::cout << "Invalid input. Please enter 'y' or 'n', or press Enter: ";
		// Use std::ws to skip leading whitespace before reading the line.
		std::getline(std::cin, choice);
		// Convert the first character to uppercase for comparison.
		selection = toupper(choice[0]);
	}
	return (selection == 'Y') ? ReportMode::WithAndWithoutMonthlyDeposits : ReportMode::WithMonthlyDepositsOnly;
}

/**
 * @brief Prints both balance reports, pausing between them.
 * @return void This method calculates and prints the reports, then updates state.
 */
void Banking::CalcBalance()
{
	// Default to showing both reports for testing
	Banking::ReportMode mode = Banking::ReportMode::WithAndWithoutMonthlyDeposits;

	if (mode == ReportMode::WithAndWithoutMonthlyDeposits)
	{
		// Print the report without recurring deposits.
		CalculateBalancesWithoutDeposits();
		// Print the report with recurring deposits.
		CalculateBalancesWithDeposits();
	}
	else if (mode == ReportMode::WithMonthlyDepositsOnly)
	{
		// Print the report with recurring deposits.
		CalculateBalancesWithDeposits();
	}
	else
	{
		// This should never happen, but handle it gracefully.
		std::cerr << "Error: Invalid report mode selected." << std::endl;
	}
}

/**
 * @brief Moves the closing balance into the next month's opening balance.
 * @return void This method updates the internal beginning-balance state.
 */
void Banking::UpdateBalances()
{
	// The next period starts with the current period's closing balance.
	this->BeginningBalance = this->ClosingBalance;
}

/**
 * @brief Sets the initial investment amount.
 * @param initialInvestment Amount invested at the start of the calculation.
 * @return void This method stores the value and initializes the starting balance.
 */
void Banking::setInitialInvestment(double initialInvestment)
{
	// Store the original investment for both reports.
	this->InitialInvestment = initialInvestment;
	// The first period begins with the initial investment.
	this->BeginningBalance = initialInvestment;
}

/**
 * @brief Sets the investment duration.
 * @param numYears The number of years.
 * @return void This method stores the investment duration.
 */
void Banking::setNumYears(int numYears)
{
	// Store the number of annual report sections to generate.
	this->NumYears = numYears;
}

/**
 * @brief Sets the recurring monthly deposit amount.
 * @param monthlyDeposit The monthly deposit amount.
 * @return void This method stores the recurring deposit amount.
 */
void Banking::setMonthlyDeposit(double monthlyDeposit)
{
	// Store the deposit applied in the second report.
	this->MonthlyDeposit = monthlyDeposit;
}

/**
 * @brief Sets the annual interest rate.
 * @param interestRate The interest rate.
 * @return void This method stores the annual rate as a whole-number percentage.
 */
void Banking::setInterestRate(double interestRate)
{
	// Store the annual percentage before it is converted to a monthly rate.
	this->InterestRate = interestRate;
}

/**
 * @brief Gets the investment duration.
 * @return int The number of years configured for the investment.
 */
int Banking::getNumYears() const
{
	// Return the configured number of years without changing object state.
	return this->NumYears;
}

/**
 * @brief Gets the initial investment amount.
 * @return double The original amount invested.
 */
double Banking::getInitialInvestment() const
{
	// Return the original investment value.
	return InitialInvestment;
}

/**
 * @brief Gets the recurring monthly deposit amount.
 * @return double The configured monthly deposit.
 */
double Banking::getMonthlyDeposit() const
{
	// Return the recurring deposit value.
	return this->MonthlyDeposit;
}

/**
 * @brief Gets the annual interest rate.
 * @return double The annual interest rate as a whole-number percentage.
 */
double Banking::getInterestRate() const
{
	// Return the configured annual percentage.
	return this->InterestRate;
}

/**
 * @brief Displays both balance reports.
 * @return void This method calculates and prints the reports, then updates state.
 */
void Banking::displayBalances()
{
	// Calculate and print both reports.
	CalcBalance();
	// Leave the object synchronized with the final closing balance.
	UpdateBalances();
}

/**
 * @brief Displays the values currently entered for the investment.
 * @return void This method writes the input summary to standard output.
 */
void Banking::printInputDetails()
{
	// Clear the console before displaying the input summary.
	std::cout << "\033[2J\033[1;1H"; // ANSI escape code to clear the console screen
	// Print the summary border and title.

	std::cout << INPUT_CORNER_CHAR << std::string(INPUT_DETAILS_WIDTH, INPUT_DASH_CHAR) << INPUT_CORNER_CHAR << endl;
	std::cout << INPUT_BORDER_CHAR << centerText("Input Details", INPUT_DETAILS_WIDTH, ' ') << INPUT_BORDER_CHAR << endl;
	std::cout << INPUT_CORNER_CHAR << std::string(INPUT_DETAILS_WIDTH, INPUT_DASH_CHAR) << INPUT_CORNER_CHAR << endl;
	// Print each configured input value.
	std::cout << INPUT_BORDER_CHAR << INPUT_FILL_CHAR << setw(INPUT_KEY_WIDTH) << left << "Initial Investment: " << '$' << std::fixed << std::setprecision(2) << setw(INPUT_VALUE_WIDTH) << InitialInvestment << INPUT_FILL_CHAR << INPUT_BORDER_CHAR << endl;
	std::cout << INPUT_BORDER_CHAR << INPUT_FILL_CHAR << setw(INPUT_KEY_WIDTH) << left << "Monthly Deposit: " << '$' << std::fixed << std::setprecision(2) << setw(INPUT_VALUE_WIDTH) << MonthlyDeposit << INPUT_FILL_CHAR << INPUT_BORDER_CHAR << endl;
	std::cout << INPUT_BORDER_CHAR << INPUT_FILL_CHAR << setw(INPUT_KEY_WIDTH) << left << "Interest Rate: " << '%' << std::fixed << std::setprecision(2) << setw(INPUT_VALUE_WIDTH) << InterestRate << INPUT_FILL_CHAR << INPUT_BORDER_CHAR << endl;
	std::cout << INPUT_BORDER_CHAR << INPUT_FILL_CHAR << setw(INPUT_KEY_WIDTH) << left << "Number of Years: " << setw(INPUT_VALUE_WIDTH + 1) << NumYears << INPUT_FILL_CHAR << INPUT_BORDER_CHAR << endl;
	std::cout << INPUT_CORNER_CHAR << std::string(INPUT_DETAILS_WIDTH, INPUT_DASH_CHAR) << INPUT_CORNER_CHAR << endl;

	std::cout << "Press Enter to continue..." << std::endl;
	std::cin.get(); // Wait for the user to press Enter before proceeding

}

/**
 * @brief Centers text within a field of the requested length.
 * @param text Text to center.
 * @param length Total width of the resulting field.
 * @param fill Character used to pad the field.
 * @return string The padded, centered text, or the original text if it is too long.
 */
string Banking::centerText(string text, int length, char fill)
{
	// Measure the text and prepare storage for the padded result.
	int textLength = text.length();
	string centeredText = "";

	// Do not truncate text that already fills or exceeds the requested width.
	if (textLength >= length)
	{
		return text;
	}
	else
	{
		// Determine how much padding is needed on both sides.
		int charsNeeded = (length - textLength);
		int paddingNeeded = (charsNeeded / 2);
		string leftPadding = string(paddingNeeded, fill);
		string rightPadding = leftPadding;
		centeredText = (leftPadding + text + rightPadding);

		if (charsNeeded % 2 != 0)
		{
			// Add the extra character to keep the result at the requested width.
			centeredText.insert(0, 1, fill);
		}
		return (centeredText);
	}
}

/**
 * @brief Prints a repeated character string.
 * @param times Number of times to repeat the character.
 * @param charToPrint Character to repeat.
 * @return void This method writes the generated string to standard output.
 */
void Banking::printChar(int times, char charToPrint)
{
	// Build the repeated-character string without a manual loop.
	string str(times, charToPrint);
	// Write the string followed by a newline.
	cout << str << endl;
}