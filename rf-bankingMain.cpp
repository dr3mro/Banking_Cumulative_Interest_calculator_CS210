/*
 * Amr Osman
 * amr.osman@snhu.edu
 * CS-210-12997- Project Two Banking
 * This program will get the following
 * Month: The number of months based on user input in the “Number of Years” field
 * Opening Amount: The initial investment amount as well as the opening balance each
 * month, which includes interest
 * Deposited Amount: The dollar amount the user plans to deposit each month. This value
 * will be the same every month for the duration of the investment.
 * Total: The sum of the opening and deposited amounts
 * Interest: Money earned based on the “annual interest” rate input by the user.
 * Closing Balance: The balance at the end of each month, which includes the opening balance, deposits, and interest.
 * Program will then display the results in an organized manner
 */
#include <iostream>
#include <string>
#include <sstream>
#include "rf-banking.h"

using namespace std;

int getInteger(const string & = "");

// Gets an integer that must be at least minNum.
int getInteger(const string&, const int);

// Gets an integer that must be between minValue and maxValue.
int getInteger(const string&, const int, const int);

double getDouble(const string&);

double getDouble(const string&, const double);

double getDouble(const string&, const double, const double);

int main()
{

    Banking airgead; // create an instance of the banking class

    int numYears{ 0 }; // the number of years until maturity
    double
        initialInvestment{ 0.0 }, // how much is deposited to start
        monthlyDeposit{ 0.0 },    // how much money is contributed each month
        interestRate{ 0.0 };      // interest rate in whole numbers to be converted to percentages

    /*
     * The follwing function call get the initial investment, monthly deposit,
     * interest rate and number of years passing the minimum valid value and a prompt for the user
     */

     // get the initial investment
    initialInvestment = getDouble("What is the initial investment? ", 1.0);

    // set the initial investment in the Banking object
    airgead.setInitialInvestment(initialInvestment);

    // get the monthly deposit
    monthlyDeposit = getDouble("What is the monthly deposit? ", 1.0);

    // set the monthly deposit in the Banking object
    airgead.setMonthlyDeposit(monthlyDeposit);

    // get the interest rate
    interestRate = getDouble("What is interest rate? ", 1.0);

    // set the interest rate in the Banking object
    airgead.setInterestRate(interestRate);

    // get the number of years
    numYears = getInteger("How many years should the investment grow? ", 1);

    // set the number of years in the Banking object
    airgead.setNumYears(numYears);

    // print the input details
    airgead.printInputDetails();

    // display and calculate the balances
    airgead.displayBalances();

    // Wait for user input before closing the console window
    cout << "Press any key to quit..." << endl;
    cin.get();
    return EXIT_SUCCESS;
} // main

/*
    Purpose:
    Prompts the user to enter an integer and continues prompting until valid
    input is received.

    The input is read as a complete string using getline(). The std::ws
    manipulator removes any leading whitespace before the input is stored.

    The function validates the input in three steps:
        1. Verifies that the input string is not empty.
        2. Verifies that the first character is a digit so that invalid
           leading characters are rejected.
        3. Uses the pos argument of stoi() to verify that the entire string
           was successfully converted to an integer. If pos does not equal
           the length of the string, trailing invalid characters were found.

    NOTE:
    Leading whitespace is allowed because std::ws removes it before getline()
    stores the input.
    However, trailing whitespace is not removed and isconsidered invalid input.
    For example, "123" is valid, but "123 " is
    rejected because characters remain after the valid integer.
    The function does not return until a valid integer has been entered.

    Parameter:
        prompt - The message displayed to the user requesting input.

    Returns:
        A valid integer entered by the user.
*/
int getInteger(const string& prompt)
{
    // Stores the complete line of input entered by the user.
    string input{ "" };

    // Stores the position of the first character not converted by stoi().
    size_t pos{ 0 };

    // Stores the integer value after the string has been successfully converted.
    int number{ 0 };

    // Controls the input-validation loop.
    bool validInput{ false };

    do
    {
        cout << prompt;

        // Read the entire line of input.
        // std::ws removes leading whitespace before getline() reads the input.
        getline(cin >> std::ws, input);

        // Make sure the user entered something before accessing input[0].
        if (input.empty())
        {
            cout << "\aString is empty- Please try again.\n";
            continue;
        }

        // The first character must be a digit or sign.
        // This prevents input such as "abc123" from being passed to stoi().
        if (!isdigit(input[0]))
        {
            // If it is not a digit, it must be a valid leading character.
            if (input[0] != '-' &&
                input[0] != '+')

            {
                cout << "Invalid leading characters - Please try again.\n";
                continue;
            }
        }

        // Convert the string to an integer.
        // pos receives the number of characters successfully processed by stoi().
        number = stoi(input, &pos);

        // Make sure there are no characters after the integer.
        // If pos is less than the string length, stoi() stopped before reaching
        // the end of the input. For example, "123abc" converts 123 but leaves
        // "abc" unprocessed.
        if (pos != input.length())
        {
            cout << "Invalid trailing characters Please try again.\n";
            continue;
        }

        // All validation checks passed, so the loop can terminate.
        validInput = true;

    } while (!validInput);

    // Return only after the user has entered a valid integer.
    return number;
}

/*
    Purpose:
        Prompts the user for an integer that must fall
        within a specified range.

    Parameters:
        prompt   - Prompt displayed to the user.
        minValue - Lowest acceptable value.

    Returns:
        A validated integer between minValue and maxValue.

    How It Works:
        1. Builds a prompt displaying the valid range.
        2. Calls the basic getInteger() function.
        3. Checks whether the value is outside the range.
        4. Repeats until a valid value is entered.
*/
int getInteger(const string& prompt, const int minNum)
{
    int number{ 0 };        // Stores validated input
    bool needValue{ true }; // Controls validation loop

    // Create prompt showing minimum requirement
    string newPrompt = prompt + " must be at least " +
        to_string(minNum) + ": ";

    do
    {

        // Reuse basic validation function
        number = getInteger(newPrompt);

        // Check whether value is below minimum
        needValue = (number < minNum);

        if (needValue)
        {

            // Display range error message
            cerr << "\aValue cannot be less than "
                << minNum << "\nRe-enter\n";

        } // if

    } while (needValue);

    // Return validated value
    return number;
}

/*
    Purpose:
        Prompts the user for an integer that must fall
        within a specified range.

    Parameters:
        prompt   - Prompt displayed to the user.
        minValue - Lowest acceptable value.
        maxValue - Highest acceptable value.

    Returns:
        A validated integer between minValue and maxValue.

    How It Works:
        1. Builds a prompt displaying the valid range.
        2. Calls the basic getInteger() function.
        3. Checks whether the value is outside the range.
        4. Repeats until a valid value is entered.
*/
int getInteger(const string& prompt, const int minValue, const int maxValue)
{
    int number{ 0 };    // Stores validated input
    bool needValue{}; // Controls validation loop

    // Create prompt showing acceptable range
    string newPrompt = prompt + " must be between " + to_string(minValue) + " and " + to_string(maxValue) + ": ";

    do
    {

        // Reuse integer validation function
        number = getInteger(newPrompt);

        /*
            Check whether the value falls outside
            the acceptable range.
        */
        needValue =
            (number < minValue) ||
            (number > maxValue);

        if (needValue)
        {

            // Display range validation message
            cerr << "Value cannot be less than "
                << minValue << " or "
                << "Greater than"
                << maxValue
                << " Re - enter\n";

        } // if

    } while (needValue);

    // Return validated value
    return number;
}

/*
    Purpose:
    Prompts the user to enter a double value and continues prompting until
    valid input is received.

    The input is read as a complete string using getline(). The std::ws
    manipulator removes any leading whitespace before the input is stored.

    The function validates the input in three steps:
        1. Verifies that the input string is not empty.
        2. Verifies that the first character is a digit so that invalid
           leading characters are rejected before stod() is called.
        3. Uses the pos argument of stod() to verify that the entire string
           was successfully converted to a double. If pos does not equal
           the length of the string, trailing invalid characters were found.

    A decimal value must begin with a digit. For example, "0.5" is valid,
    while ".5" is not accepted by this function.

    Leading whitespace is allowed because std::ws removes it before getline()
    stores the input. However, trailing whitespace is not removed and is
    considered invalid input. For example, "123.45" is valid, but "123.45 "
    is rejected because characters remain after the valid number.

    The function does not return until a valid double has been entered.

    Parameter:
        prompt - The message displayed to the user requesting input.

    Returns:
        A valid double value entered by the user.
*/
double getDouble(const string& prompt)
{
    // Stores the complete line of input entered by the user.
    string input{ "" };

    // Stores the position of the first character not converted by stod().
    size_t pos{ 0 };

    // Stores the double value after the string has been successfully converted.
    double number{ 0.0 };

    // Controls the input-validation loop.
    bool validInput{ false };

    do
    {
        cout << prompt;

        // Read the entire line of input.
        // std::ws removes leading whitespace before getline() reads the input.
        getline(cin >> std::ws, input);

        // Make sure the user entered something before accessing input[0].
        if (input.empty())
        {
            cout << "\aString is empty- Please try again.\n";
            continue;
        }

        // The first character must be a digit, decimal point (.) or sign (+ or -).
        // This prevents invalid input from being passed to stod().
        if (!isdigit(input[0]))
        {
            // If it is not a digit, it must be a valid leading character.
            if (input[0] != '.' &&
                input[0] != '-' &&
                input[0] != '+')
            {
                cout << "Invalid leading characters - Please try again.\n";
                continue;
            }
        }

        // Convert the string to a double.
        // pos receives the number of characters successfully processed by stod().
        number = stod(input, &pos);

        // Make sure there are no characters after the valid double.
        // For example, "123.45abc" converts 123.45 but leaves "abc".
        if (pos != input.length())
        {
            cout << "Invalid trailing characters Please try again.\n";
            continue;
        }

        // All validation checks passed.
        validInput = true;

    } while (!validInput);

    // Return only after the user has entered a valid double.
    return number;
}

/*
    Purpose:
    Prompts the user to enter a double value that must be greater than or
    equal to a specified minimum value.

    This function is an overloaded version of getDouble(). It adds a minimum
    value requirement to the basic input validation performed by the
    getDouble(string) overload.

    The function first creates a new prompt that includes the minimum
    acceptable value. An ostringstream is used to convert minNum to a string
    without adding the unnecessary trailing decimal places that to_string()
    can add when converting a double.

    The function then calls the overloaded getDouble(string) function using
    the new prompt. The getDouble(string) function is responsible for obtaining
    and validating the user's input and does not return until a valid double
    has been entered.

    After a valid double is returned, this function checks whether the value
    is greater than or equal to minNum. If the value is less than minNum, an
    error message is displayed and the user is prompted again. The loop
    continues until the user enters a valid double that meets the minimum
    value requirement.

    Parameters:
        prompt - A constant reference to the string containing the basic
                 message displayed when requesting input. The function uses
                 this prompt to create a new prompt that also displays the
                 minimum acceptable value.

        minNum - The minimum double value that can be accepted. The value
                 entered by the user must be greater than or equal to minNum.

    Returns:
        A valid double value that is greater than or equal to minNum.

    Calls:
        getDouble(string) - The overloaded getDouble() function that obtains
                            and validates a double value before this function
                            checks the minimum-value requirement.
*/
double getDouble(const string& prompt, const double minNum)
{

    double number{ 0 };    // number to get
    bool needData{ true }; // set initial flag

    // Create an output string stream to convert minNum to a string
    // without adding unnecessary trailing decimal places that to_string() can add
    ostringstream output;

    // Insert the minimum value into the string stream.
    output << minNum;

    // Create a new prompt that tells the user the minimum allowed value.
    string newPrompt = prompt + " must be at least " +
        output.str() + ": ";

    do
    {
        number = getDouble(newPrompt);
        needData = (number < minNum);
        if (needData)
        {
            cout << "Invalid number - must be greater than or equal to " << (minNum) << endl;
        } // if needData

    } while (needData);

    return number;
}

/*
    Purpose:
    Prompts the user to enter a double value that must be greater than or
    equal to a specified minimum value.

    This function is an overloaded version of getDouble(). It adds a minimum
    value requirement to the basic input validation performed by the
    getDouble(string) overload.

    The function first creates a new prompt that includes the minimum
    acceptable value. An ostringstream is used to convert minNum to a string
    without adding the unnecessary trailing decimal places that to_string()
    can add when converting a double.

    The function then calls the overloaded getDouble(string) function using
    the new prompt. The getDouble(string) function is responsible for obtaining
    and validating the user's input and does not return until a valid double
    has been entered.

    After a valid double is returned, this function checks whether the value
    is greater than or equal to minNum. If the value is less than minNum, an
    error message is displayed and the user is prompted again. The loop
    continues until the user enters a valid double that meets the minimum
    value requirement.

    Parameters:
        prompt - A constant reference to the string containing the basic
                 message displayed when requesting input. The function uses
                 this prompt to create a new prompt that also displays the
                 minimum acceptable value.

        minNum - The minimum double value that can be accepted. The value
                 entered by the user must be greater than or equal to minNum.
        maxNum - The maximum double value that can be accepted. The value
                 entered by the user must be greater than or equal to minNum.


    Returns:
        A valid double value that is greater than or equal to minNum but less than maxNum

    Calls:
        getDouble(string) - The overloaded getDouble() function that obtains
                            and validates a double value before this function
                            checks the minimum-value requirement.
*/
double getDouble(const string& prompt, const double minNum, const double maxNum)
{
    /*
     * The purpose getDouble is get a double that is greater than or equal to the lowest passed
     * The prompt parameter allows to use this function for different inputs
     * Note this function does not check if data entered is a number. Use getline and regex for ths
     */
    double number{ 0.0 };  // number to get
    bool needData{ true }; // set initial flag

    // Create prompt showing minimum requirement
    std::ostringstream output;

    output << prompt << " must be at least " << minNum << " and " << maxNum;

    string newPrompt = output.str() + ": ";

    do
    {

        number = getDouble(newPrompt);

        needData = (number < minNum) || (number > maxNum);
        if (needData)
        {
            cout << "Invalid number - " << output.str() << endl;
        } // if needData

    } while (needData);

    return number;
}