#include <iostream>   // includes
#include <fstream>
#include <string>

using std::string;    // so we can write string instead of std::string
using std::ifstream;  // so we can write ifstream instead of std::ifstream
using std::cout;      // so we can write cout instead of std::cout
using std::cin;       // so we can write cin instead of std::cin
using std::endl;      // so we can write endl instead of std::endl

// a function to check if a character is a digit
// returns true if character is '0' through '9' and if else it returns false
bool isDigit(char character) {
    return character >= '0' && character <= '9';
}

// a function to check if a string is a double, we also might have to use this function a lot thats why its a function
bool isDouble(const string & string) {
    int i = 0;
    bool found = false;       // to track if a decimal point has been found
    int digitsBeforeDot = 0;  // number of digits before the decimal point
    int digitsAfterDot = 0;   // number of digits after the decimal point
    
    if (string.empty()) {     // returns false if given an empty string
        return false;
    }
    
    // handle operator signs
    if (string[0] == '+' || string[0] == '-') {
        i = 1;
        
        if (string.size() == 1) {
            return false;
        }
    }
    
    // iterate through the rest of the string
    for (i; i < (int)string.size(); ++i) {
        char character = string[i];
        
        if (character == '.') {     // handle a decimal point if found
            if (found) {            // if more than one decimal point is found then its invalid
                return false;
            }
                
            found = true;
            continue;
        }
        
        if (!isDigit(character)) { // if a non digit is found the character is invalid
            return false;
        }
            
        if (!found) {
            ++digitsBeforeDot;    // add 1 to count for digits before the decimal point
        }
            
        else {
            ++digitsAfterDot;     // add 1 to count for digits after the decimal point
        }
    }
    
    // if a decimal point exists we need to make sure there are digits on both sides
    if (found) {
        return (digitsBeforeDot >= 1 && digitsAfterDot >= 1);
    } 
    
    else {  // if no decimal point is found then there must be one digit
        return (digitsBeforeDot >= 1);
    }
}

// a function to compare the magnitudes of A & B
// returns 1 if A > B
// returns 0 if they are equal
// returns -1 if A < B
int compareMagnitudes(const string & stringA, const string & remainderA, const string & stringB, const string & remainderB) {
    int intA = 0;
    while (intA < (int) stringA.size() && stringA[intA] == '0') {   // remove leading zeros from integer parts
        ++intA;
    }
    
    string new_stringA;
    if (intA == (int) stringA.size()) {
        new_stringA = string("0");                                  // populate the new string A
    } 
    else {
        new_stringA = stringA.substr(intA);                         // otherwise we remove the leading zeros
    }

    int intB = 0;                                                   // same as string A
    while (intB < (int) stringB.size() && stringB[intB] == '0') {
        ++intB;
    }
    
    string new_stringB;
    if (intB == (int) stringB.size()) {
        new_stringB = string("0");
    } 
    else {
        new_stringB = stringB.substr(intB);
    }

    if (new_stringA.size() > new_stringB.size()) {    // compare integer parts by length first
        return 1;
    }
    
    if (new_stringA.size() < new_stringB.size()) {
        return -1;
    }
    
    if (new_stringA > new_stringB) {                  // if they are the same length then we just let the compiler compare them by default
        return 1;
    }
    
    if (new_stringA < new_stringB) {
        return -1;
    }
    
    // if the integer parts are equal then we compare the remainders
    int lengthA = (int) remainderA.size();
    int lengthB = (int) remainderB.size();
    
    int max_length;
    if (lengthA > lengthB) {
        max_length = lengthA;
    } 
    else {
        max_length = lengthB;
    }
    
    for (int i = 0; i < max_length; ++i) {
        char characterA;
        if (i < lengthA) {
            characterA = remainderA[i];
        } 
        else {
            characterA = '0';
        }

        char characterB;
        if (i < lengthB) {
            characterB = remainderB[i];
        } 
        else {
            characterB = '0';
        }
        
        if (characterA > characterB) {
            return 1; // A is greater
        }
        
        if (characterA < characterB) {
            return -1; // B is greater
        }
    }
    return 0; // numbers are equal
}

// a function to add the magnitudes of A & B
string addMagnitudes(string stringA, string remainderA, string stringB, string remainderB) {
    int lengthA = (int) remainderA.size();
    int lengthB = (int) remainderB.size();
    
    int max_length;
    if (lengthA > lengthB) {
        max_length = lengthA;
    } 
    else {
        max_length = lengthB;
    }
    // populate zeros to the remainders respectively
    while ((int) remainderA.size() < max_length) {
        remainderA.push_back('0');
    }
    
    while ((int) remainderB.size() < max_length) {
        remainderB.push_back('0');
    }

    int intA = (int) stringA.size();
    int intB = (int) stringB.size();
    // then populate until equal length
    int largerInt;
    if (intA > intB) {
        largerInt = intA;
    } 
    else {
        largerInt = intB;
    }
    
    while ((int) stringA.size() < largerInt) {
        stringA = '0' + stringA;
    }
    
    while ((int) stringB.size() < largerInt) {
        stringB = '0' + stringB;
    }
    // add the remainders
    string result_remainder = "";
    for (int i = 0; i < max_length; ++i) {
        result_remainder += '0';
    }

    int result_remainder_int = 0;
    for (int i = max_length - 1; i >= 0; --i) {
        int digitA = remainderA[i] - '0';
        int digitB = remainderB[i] - '0';
        int sum = digitA + digitB + result_remainder_int;
        
        char character = '0' + (sum % 10);
        result_remainder[i] = character;
        result_remainder_int = sum / 10;
    }
    // add the ints
    string result_int = "";
    for (int i = 0; i < largerInt; ++i) {
        result_int += '0';
    }
    
    for (int i = largerInt - 1; i >= 0; --i) {
        int digitA = stringA[i] - '0';
        int digitB = stringB[i] - '0';
        int sum = digitA + digitB + result_remainder_int;
        
        char character = '0' + (sum % 10);
        result_int[i] = character;
        result_remainder_int = sum / 10;
    }
    // handle any remaining remainders
    if (result_remainder_int) {
        char character = '0' + result_remainder_int;
        result_int = character + result_int;
    }
    // remove the filled in zeros
    int k = 0;
    while (k < (int) result_int.size() && result_int[k] == '0') {
        ++k;
    }
    
    if (k == (int) result_int.size()) {
        result_int = "0";
    }
    else {
        result_int = result_int.substr(k);
    }

    int t = (int) result_remainder.size() - 1;
    while (t >= 0 && result_remainder[t] == '0') {
        --t;
    }
    
    if (t < 0) {
        result_remainder.clear();
    }
    else {
        string new_string = "";
        for (int i = 0; i <= t; ++i) {
            new_string += result_remainder[i];
        }
        result_remainder = new_string;          
    }

    if (result_remainder.empty()) {
        return result_int;
    }
    
    return result_int + "." + result_remainder;
}

// a function to subtract the magnitudes of A & B
string subtractMagnitudes(string stringA, string remainderA, string stringB, string remainderB) {
    int lengthA = (int) remainderA.size();
    int lengthB = (int) remainderB.size();
    
    int max_length;
    if (lengthA > lengthB) {
        max_length = lengthA;
    } 
    else {
        max_length = lengthB;
    }
    // populate remainders
    while ((int) remainderA.size() < max_length) {
        remainderA.push_back('0');
    }
    
    while ((int) remainderB.size() < max_length) {
        remainderB.push_back('0');
    }
    
    int intA = (int) stringA.size();
    int intB = (int) stringB.size();
    
    int largerInt;
    if (intA > intB) {
        largerInt = intA;
    } 
    else {
        largerInt = intB;
    }
    // populate integers
    while ((int) stringA.size() < largerInt) {
        stringA = '0' + stringA;
    }
    
    while ((int) stringB.size() < largerInt) { 
        stringB = '0' + stringB;
    }

    string result_remainder = "";
    for (int i = 0; i < max_length; ++i) {
        result_remainder += '0';
    }
    
     // subtract the remainders
    int result_remainder_int = 0;
    for (int i = max_length - 1; i >= 0; --i) {
        int digitA = remainderA[i] - '0';
        int digitB = remainderB[i] - '0';
        int digit = digitA - result_remainder_int - digitB;
        
        if (digit < 0) {
            digit += 10;
            result_remainder_int = 1;
        } 
        else {
            result_remainder_int = 0;
        }
        char character = '0' + digit;
        result_remainder[i] = character;
    }
    
    // subtract the integers
    string result_int = "";
    for (int i = 0; i < largerInt; ++i) {
        result_int += '0';
    }
    
    for (int i = largerInt - 1; i >= 0; --i) {
        int digitA = stringA[i] - '0';
        int digitB = stringB[i] - '0';
        int digit = digitA - result_remainder_int - digitB;
        
        if (digit < 0) {
            digit += 10;
            result_remainder_int = 1;
        } 
        else {
            result_remainder_int = 0;
        }
        
        char character = '0' + digit;
        result_int[i] = character;
    }
    // remove the filled in zeros
    int k = 0;
    while (k < (int) result_int.size() && result_int[k] == '0') {
        ++k;
    }
    
    if (k == (int) result_int.size()) {
        result_int = "0";
    }
    else {
        result_int = result_int.substr(k);
    }

    int t = (int) result_remainder.size() - 1;
    while (t >= 0 && result_remainder[t] == '0') {
        --t;
    }
    
    if (t < 0) {
        result_remainder.clear();
    }
    else {
        string new_string = "";
        for (int i = 0; i <= t; ++i) {
            new_string += result_remainder[i];
        }
        result_remainder = new_string;   ;
    }

    if (result_remainder.empty()) {
        return result_int;
    }
    
    return result_int + "." + result_remainder;
}

// a function to add the magnitudes of two doubles A & B
string addStringDoubles(const string & stringA, const string & stringB) {
    bool negativeA = false;
    bool negativeB = false;
    int startA = 0;
    int startB = 0;
    // check and store negative signs for A
    if (!stringA.empty() && (stringA[0] == '+' || stringA[0] == '-')) {
        bool isNegative = stringA[0] == '-';
        negativeA = isNegative;
        startA = 1;
    }
    // check and store negative signs for B
    if (!stringB.empty() && (stringB[0] == '+' || stringB[0] == '-')) {
        bool isNegative = stringB[0] == '-';
        negativeB = isNegative;
        startB = 1;
    }
    // split A into integers and remainders
    int dotA = -1;
    for (int i = startA; i < (int) stringA.size(); ++i) {
        if (stringA[i] == '.') { 
          dotA = i; 
          break; 
        }
    }

    string intA = "";
    string remainderA = "";
    for (int i = startA; i < (dotA == -1 ? (int) stringA.size() : dotA); ++i) {
        intA += stringA[i];
    }
    if (dotA != -1) {
        for (int i = dotA + 1; i < (int) stringA.size(); ++i) {
            remainderA += stringA[i];
        }
    }
    // split B into integers and remainders
    int dotB = -1;
    for (int i = startB; i < (int) stringB.size(); ++i) {
        if (stringB[i] == '.') { 
          dotB = i; 
          break; 
        }
    }

    string intB = "";
    string remainderB = "";
    for (int i = startB; i < (dotB == -1 ? (int) stringB.size() : dotB); ++i) {
        intB += stringB[i];
    }
    if (dotB != -1) {
        for (int i = dotB + 1; i < (int) stringB.size(); ++i) {
            remainderB += stringB[i];
        }
    }
    // remove the filled in zeros
    int resultA = 0; 
    while (resultA < (int) intA.size() && intA[resultA] == '0') { 
        ++resultA;
    }
    
    if (resultA == (int) intA.size()) {
        intA = "0";
    } 
    else {
        intA = intA.substr(resultA);
    }

    int resultB = 0; 
    while (resultB < (int) intB.size() && intB[resultB] == '0') {
        ++resultB;
    }
    
    if (resultB == (int) intB.size()) {
        intB = "0";
    } 
    else {
        intB = intB.substr(resultB);
    }
    // compare the values
    int compared_value = compareMagnitudes(intA, remainderA, intB, remainderB);

    string resultValue;
    bool isNegative = false;
    // if the signs are the same then we add them together
    if (negativeA == negativeB) {
        resultValue = addMagnitudes(intA, remainderA, intB, remainderB);
        isNegative = negativeA;
    } 
    // if the signs are different then we subtract them together
    else {
        if (compared_value == 0) {
            return "0";
        } 
        else if (compared_value > 0) {
            resultValue = subtractMagnitudes(intA, remainderA, intB, remainderB);
            isNegative = negativeA;
        } 
        else {
            resultValue = subtractMagnitudes(intB, remainderB, intA, remainderA);
            isNegative = negativeB;
        }
    }
    // attach sign if negative
    if (resultValue == "0") {
        return "0";
    }
    if (isNegative) {
        return "-" + resultValue;
    } 
    else {
        return resultValue;
    }
}

int main() {
    string filename;
    cout << "Enter filename to read pairs of numbers: ";
    cout << "\n";
    
    getline(cin, filename);           // get file name
    ifstream file(filename);          // try to open the file
    
    if (!file) {                      // check if opening failed
        cout << "Cannot open file: " << filename << endl;
        return 1;
    }
    else {
        cout << "File opened successfully!" << endl;
    }

    string stringA;
    string stringB;
    int row = 0;
    // read each pair of numbers from the file
    while (file >> stringA >> stringB) {
        ++row;
        bool validA = isDouble(stringA); // check if first number is valid
        bool validB = isDouble(stringB); // check if second number is valid
        
        // handle invalid numbers
        if (!validA || !validB) {
            cout << "Line " << row << ": "; // print line
            
            if (!validA && !validB) {
                cout << "Both numbers are invalid: '" << stringA << "' and '" << stringB << "'.\n";
            }
            else if (!validA) {
                cout << "First number is invalid: '" << stringA << "'.\n";
            }
            else {
                cout << "Second number is invalid: '" << stringB << "'.\n";
            }
            continue;
        }
        // add the two valid numbers
        string sum = addStringDoubles(stringA, stringB);
        cout << "Line " << row << ": " << stringA << " + " << stringB << " = " << sum << "\n";
    }

    file.close(); // close file
    return 0; // end program

}
