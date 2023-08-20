#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Method for integer add formula
string add(string num1, string num2, int base);
// Method for integer subtract formula
string subtract(string num1, string num2, int base);
// Method for integer multiply formula
string multiply(string num1, string num2, int base);
// Method for multiply one digit number
string multiplyOneDigit(string num1, int digit, int base);
// Method for integer divide
string divide(string num1, string num2, int base);
// Method for comparing the value of two strings
bool compareStrings(string num1, string num2);

int main()
{
    // Variables
    string num1, num2;
    int base;
    cin >> num1 >> num2 >> base;
    
	// Strings output from methods
    string sum = add(num1, num2, base);
    string product = multiply(num1, num2, base);
    string quotient = divide(num1, num2, base);

    cout << sum << " " << product << " " << quotient << " " << endl;
    return 0;
}

// Method for integer add formula
string add(string num1, string num2, int base)
{
    // Attributes
    int carry = 0;
    string result = "";
    int sum;

    int i = num1.length() - 1, j = num2.length() - 1;

    // While loop by getting the current digit of number 1 and number 2, then subtracting the character'0'
   // If either number 1 and number 2 has no more digits, 0 is used instead
    while (i >= 0 || j >= 0 || carry)
    {
        int x = i >= 0 ? num1[i] - '0' : 0;
        int y = j >= 0 ? num2[j] - '0' : 0;

        // Adding 2 digits, carry and storing the result in variable sum
        int sum = x + y + carry;
        carry = sum / base;

        // Calculating the new sum by taking the remainder sum divided by base
        sum = sum % base;

        // Converting the new sum back to a character by adding the character 0 to it and appends it to result
        result += (char)(sum + '0');

        i--, j--;
    }
    // Result is reversed and returned as the reversed string showing the correct sum of two input numbers
    reverse(result.begin(), result.end());
    return result;
}

// Method for integer subtract formula
string subtract(string num1, string num2, int base)
{
    // Attributes
    int borrow = 0;
    string result = "";
    int diff;

    int i = num1.length() - 1, j = num2.length() - 1;

    // While loop by getting the current digit of number 1 and number 2, then subtracting the character'0'
   	// If either number 1 and number 2 has no more digits, 0 is used instead
    while (i >= 0 || j >= 0)
    {
        int x = i >= 0 ? num1[i] - '0' : 0;
        int y = j >= 0 ? num2[j] - '0' : 0;

        // Subtracting 2 digits, borrow and storing the result in variable diff
        int diff = x - y - borrow;

        // If diff is negative, adding base to diff and sets borrow to 1; otherwise, setting borrow to 0
        if (diff < 0)
        {
            diff += base;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        result += (char)(diff + '0');

        i--, j--;
    }

    // Result is reversed and returned as the reversed string showing the correct difference of two input numbers
    // Note: This function assumes number 1 > or = than number 2; hence, if number 2 > number 1, result will be incorrect
    reverse(result.begin(), result.end());
    return result;
}

// Method for integer multiply formula
string multiply(string num1, string num2, int base)
{
    // If either number 1 or number 2 is a single digit, it calls the function MultiplyOneDigit which multiplies a string by a single digit
    if (num1.length() == 1 && num2.length() == 1)
    {
        return multiplyOneDigit(num1, num2[0] - '0', base);
    }

    // If both number 1 and number 2 have multiple digits, the function initializes variables n: the length of number 1, m: the length of number 2
    int n = num1.length(), m = num2.length();
    string result(n + m, '0');

    // Nested loop that multiplies each digit of number 1 by each digit of number 2, starting from the least significant digit.
    for (int i = n - 1; i >= 0; i--)
    {
        int carry = 0;
        for (int j = m - 1; j >= 0; j--)
        {
            int temp = (num1[i] - '0') * (num2[j] - '0') + (result[i + j + 1] - '0') + carry;
            result[i + j + 1] = (char)(temp % base + '0');
            carry = temp / base;
        }
        result[i +0] += carry;
	}
	// Remove leading zeros
	result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));
	return result;
}

// Method for multiply one digit number
string multiplyOneDigit(string num1, int digit, int base)
{
	int carry = 0;
	string result = "";

    // For loop that multiplies each digit of number 1 by digit, starting from the least significant digit.
	for (int i = num1.length() - 1; i >= 0; i--)
	{
    	int temp = (num1[i] - '0') * digit + carry;
        result += (char)(temp % base + '0');
        carry = temp / base;
	}

	if (carry > 0)
	{
        result += (char)(carry + '0');
	}

	reverse(result.begin(), result.end());
	return result;
}

// Method for integer divide
string divide(string num1, string num2, int base)
{
	// Handle num1 < num2 case
	if (num1.length() < num2.length() || (num1.length() == num2.length() && num1 < num2))
	{
        return "0";
	}

	string result;
	string remainder = "0";

	for (int i = 0; i < num1.length(); i++)
	{
        remainder += num1[i];

        int quotient = 0;
        while (compareStrings(remainder, num2))
        {
            remainder = subtract(remainder, num2, base);
            quotient++;
        }

        result += to_string(quotient);
	}

    // Handle to remove head with 0
	while (result[0] == '0' && result.length() > 1)
	{
        result.erase(0, 1);
	}

	return result;
}

// Method for comparing the value of two strings
bool compareStrings(string num1, string num2) {
	// Remove leading zeroes
    while (num1.length() > 1 && num1[0] == '0') 
	{
        num1.erase(0, 1);
    }
    while (num2.length() > 1 && num2[0] == '0') 
	{
        num2.erase(0, 1);
    }

    int len1 = num1.length();
    int len2 = num2.length();

    if (len1 != len2) {
        return len1 > len2;
    }

    for (int i = 0; i < len1; i++) {
        if (num1[i] != num2[i]) 
		{
            return num1[i] > num2[i];
        }
    }
    return false;
}





