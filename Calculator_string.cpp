/*
                                THIS CODE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
                                BY : VKEY
*/

// =========================================== PURPOSE OF THIS PROGRAM =================================================
/*
INPUT PARAMETER IS STRING
input : "26 - 78 * 3 / 2" => output : -91.00
*/

// ================================================== LIBRARY ==========================================================
#include <iostream> // std::cout, std::cin, std::fixed, std::endl
#include <string> // size(), std::string, erase(), insert(), substr()
#include <algorithm> // remove(), find()
#include <sstream> // std::stringstream
#include <cmath> // std::pow(), std::sqrt()
#include <iomanip> // std::setprecision()

// ================================================ PROTOTYPES =========================================================
void processOperation(std::string&, float&, float&, int& );
std::string toString(float );
int reverseInt(int& );
int factorialNumber(int );
int multiplesOfTen(int );
float numberBehindComma(int );
float leftNumber(std::string&, float&, int& );
float rightNumber(std::string&, float&, int& );
void removeSpace(std::string& );
void addition(std::string&, float&, float&, int& );
void substraction(std::string&, float&, float&, int& );
void multiplication(std::string&, float&, float&, int& );
void division(std::string&, float&, float&, int& );
void power(std::string&, float&, float&, int& );
void root(std::string&, float&, float&, int& );
void factorial(std::string&, float&, float&, int& );
void bracket(std::string&, float&, float&, int&, int& );

// =============================================== MAIN PROGRAM ========================================================
int main(){
    // variables
    std::string str;
    int index, indexBegin, indexEnd;
    float sum = 0, result = 0;
    // clear terminal screen
    //system("clear");
    std::cout << "INPUT NUMBERS AND OPERATORS (# for root operation) : ";
    getline(std::cin, str);
    removeSpace(str); // to remove spaces from the string

    while(true){
        if( str.find('(') != std::string::npos){
            indexBegin = str.find('('), indexEnd = str.find(')');
            bracket(str, result, sum, indexBegin, indexEnd);
        }else{
            processOperation(str, result, sum, index);
            break;
        }
    }

    // to set max length of the output
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "RESULT : " << result << std::endl;

    return 0;
}

// ================================================= FUNCTIONS =========================================================

// to calculate of '+', '-', '*', '/', '^', '#' and '!' operators
void processOperation(std::string& str, float& result, float& sum, int& index){
    // find operators in the string and point them to the function
    while(true){
        if( str.find('!') != std::string::npos ){
            index = str.find('!');
            factorial(str, result, sum, index);
        }else if( str.find('^') != std::string::npos ){
            index = str.find('^');
            power(str, result, sum, index);
        }else if( str.find('#') != std::string::npos ){
            index = str.find('#');
            root(str, result, sum, index);
        }else if( str.find('*') < str.find('/') ){
            index = str.find('*');
            multiplication(str, result, sum, index);
        }else if( str.find('/') < str.find('*') ){
            index = str.find('/');
            division(str, result, sum, index);
        }else if( str.find('+') < str.find('-', 1) ){
            index = str.find('+');
            addition(str, result, sum, index);
        }else if( str.find('-', 1) < str.find('+') ){
            index = str.find('-', 1);
            substraction(str, result, sum, index);
        }else{
            break;
        }
    }
}

// to convert float to string
std::string toString(float number){
    std::string tempStr;
    std::stringstream streamStr;
    // '<<' insert the value on the right-hand side to the stringstream object
    streamStr << number;
    // '>>' extracts the value of the stringstream object and stores it in a string variable of the right-hand side
    streamStr >> tempStr; // or tempStr = stream.str();
    return tempStr;
}

// to reverse an integer number
int reverseInt(int& number){
    int temp = 0;
    for(;number != 0; number/=10){
        temp = number % 10 + (temp*10);
    }
    return temp;
}

// to calculate the factorial number
int factorialNumber(int number){
    if(number == 1)
        return 1;
    return number*factorialNumber(number - 1);
}

// to calculate the result if there is a zero number in behind the number
int multiplesOfTen(int number){
    if(number == 1)
        return 10;
    return 10*multiplesOfTen(number - 1);

}

// to calculate how many digits behind the comma with recursion function
float numberBehindComma(int number){
    if(number == 1)
        return 0.1;
    return 0.1*numberBehindComma(number-1);
}

// to take number from the left side
float leftNumber(std::string& str, float& sum, int& index, int& length){
    sum = 0, length = 0;
    // variable to store the index number of the comma
    // tempNumber to store the value of the sum to int because we will use function reverseInt()
    int commaIndex, tempNumber, zeroNumber = 0;
    // variable to store value if there is a comma and a minus symbol or not
    bool checkComma = false, checkMinus = false;
    // variable to store value if zero is behind the number and the number has been read
    bool checkZero = false, checkNumber = false;

    // to take the number before the operator
    for(int i = index-1; i >= -1; i--){
        if( str[i] >= '0' and str[i] <= '9' and checkMinus == false){
            // to check if there is a zero or not
            // if we don't use this, it won't count the zero number
            if(str[i] == '0' and checkNumber == false){
                zeroNumber++;
                checkZero = true;
            }
            // to prevent the zero number overload
            else
                checkNumber = true;
            // it takes the number from right to the left so we need to reverse it
            sum = sum*10 + (int(str[i] - '0'));
            length++;
        }else{
            // to check if before the operator there is a comma
            if( str[i] == '.' ){
                // to tell the index of the comma
                commaIndex = i + 1;
                checkComma = true;
                length++;
                continue;
            }
            // to check if before the operator there is a minus symbol
            if( str[i] == '-'){
                checkMinus = true;
                length++;
                continue;
            }
            tempNumber = sum;
            // to reverse the sum
            sum = reverseInt(tempNumber);

            // if there is a zero, it will be multipliy by multiplesOfTen()
            if(checkZero == true){
                sum *= multiplesOfTen(zeroNumber);
            }
            // if there is a comma, it will be multiply by numberBehindComma()
            if(checkComma == true){
                sum *= numberBehindComma(index - commaIndex);
            }
            // if there is a minus symbol, it will be multiply by -1 to makes the numbers negative
            if(checkMinus == true)
                sum *= -1;
            break;
        }
    }
    return sum;
}

// to take number from the right side
float rightNumber(std::string& str, float& sum, int& index, int& length){
    sum = 0, length = 0;
    // variable to store the index number of the comma
    int commaIndex;
    // variable to store value if there is a comma and a minus symbol or not
    bool checkComma = false, checkMinus = false;
    // to store the value if it has been read a number
    bool checkNumber = false;

    // we use <= so that ELSE will be run if it reach the end of the string
    for( int i = index+1; i <= str.size(); i++ ){
        length++; // put here so when we erase it, the operator will be deleted too
        if( str[i] >= '0' and str[i] <= '9' ){
            sum = sum*10 + int(str[i]-'0');
            // to prevent it reading to the next number
            checkNumber = true;
        }else{
            // to check if after the operator there is a comma
            if(str[i] == '.'){
                // to tell the index of the comma
                commaIndex = i + 1;
                checkComma = true;
                continue;
            }
            // to check if after the operator there is a minus symbol
            if(str[i] == '-' and checkNumber == false){
                checkMinus = true;
                continue;
            }
            // if there is a comma, it will be multiply by numberBehindComma()
            if(checkComma == true){
                sum *= numberBehindComma(i - commaIndex);
            }
            // if there is a minus symbol, it will be multiply by -1 to makes the numbers negative
            if(checkMinus == true){
                sum *= -1;
            }
            break;
        }
    }
    return sum;
}

// to remove a certain characters from a string
void removeSpace(std::string& str){
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

// to process addition operation ( plus symbol '+' )
void addition(std::string& str, float& result, float&sum, int& index){
    // lengthLeft = length of the number in the left side of the operator
    // lengthRight = length of the number in the right side of the operator
    // posBegin = index of the first number in the left side of the operator
    int posBegin, lengthLeft = 0, lengthRight = 0;
    // tempStr = string to store the result of the operator
    std::string tempStr;
    result = leftNumber(str, sum, index, lengthLeft) + rightNumber(str, sum, index, lengthRight);
    posBegin = index - lengthLeft;
    // erase(index, length want to delete)
    str.erase(posBegin, lengthLeft + lengthRight);
    tempStr = toString(result);
    // if the operation returns positive number and there isn't opeartor before it
    // so we need to insert plus symbol so the string won't cause an unxpected result
    if( (str[posBegin - 1] >= '0' and str[posBegin -1] <= '9') and posBegin != 0 )
        tempStr.insert(0, "+");
    // insert(index, string)
    str.insert(posBegin, tempStr);
}

// to process substraction operation ( minus symbol '-' )
void substraction(std::string& str, float& result, float&sum, int& index){
    // lengthLeft = length of the number in the left side of the operator
    // lengthRight = length of the number in the right side of the operator
    // posBegin = index of the first number in the left side of the operator
    int posBegin, lengthLeft = 0, lengthRight = 0;
    // tempStr = string to store the result of the operator
    std::string tempStr;
    result = leftNumber(str, sum, index, lengthLeft) - rightNumber(str, sum, index, lengthRight);
    posBegin = index - lengthLeft;
    // erase(index, length want to delete)
    str.erase(posBegin, lengthLeft + lengthRight);
    tempStr = toString(result);
    // if the operation returns positive number and there isn't opeartor before it
    // so we need to insert plus symbol so the string won't cause an unxpected result
    if( str[posBegin - 1] >= '0' and str[posBegin -1] <= '9' )
        tempStr.insert(0, "+");
    // insert(index, string)
    str.insert(posBegin, tempStr);
}

// to process multiplication operation ( asterisks symbol '*' )
void multiplication(std::string& str, float& result, float&sum, int& index){
    // lengthLeft = length of the number in the left side of the operator
    // lengthRight = length of the number in the right side of the operator
    // posBegin = index of the first number in the left side of the operator
    int posBegin, lengthLeft = 0, lengthRight = 0;
    // tempStr = string to store the result of the operator
    std::string tempStr;
    result = leftNumber(str, sum, index, lengthLeft) * rightNumber(str, sum, index, lengthRight);
    posBegin = index - lengthLeft;
    // erase(index, length want to delete)
    str.erase(posBegin, lengthLeft + lengthRight);
    tempStr = toString(result);
    // if the operation returns positive number and there isn't opeartor before it
    // so we need to insert plus symbol so the string won't cause an unxpected result
    if( str[posBegin - 1] >= '0' and str[posBegin -1] <= '9' )
        tempStr.insert(0, "+");
    // insert(index, string)
    str.insert(posBegin, tempStr);
}

// to process division operation ( slash symbol '/' )
void division(std::string& str, float& result, float&sum, int& index){
    // lengthLeft = length of the number in the left side of the operator
    // lengthRight = length of the number in the right side of the operator
    // posBegin = index of the first number in the left side of the operator
    int posBegin, lengthLeft = 0, lengthRight = 0;
    // tempStr = string to store the result of the operator
    std::string tempStr;
    result = leftNumber(str, sum, index, lengthLeft) / rightNumber(str, sum, index, lengthRight);
    posBegin = index - lengthLeft;
    // erase(index, length want to delete)
    str.erase(posBegin, lengthLeft + lengthRight);
    tempStr = toString(result);
    // if the operation returns positive number and there isn't opeartor before it
    // so we need to insert plus symbol so the string won't cause an unxpected result
    if( str[posBegin - 1] >= '0' and str[posBegin -1] <= '9' )
        tempStr.insert(0, "+");
    // insert(index, string)
    str.insert(posBegin, tempStr);
}

// to process power operation ( caret symbol '^' )
void power(std::string& str, float& result, float& sum, int& index){
    // lengthLeft = length of the number in the left side of the operator
    // lengthRight = length of the number in the right side of the operator
    // posBegin = index of the first number in the left side of the operator
    int posBegin, lengthLeft = 0, lengthRight = 0;
    // tempStr = string to store the result of the operator
    std::string tempStr;
    result = std::pow( leftNumber(str, sum, index, lengthLeft), rightNumber(str, sum, index, lengthRight) );
    posBegin = index - lengthLeft;
    // erase(index, length want to delete)
    str.erase(posBegin, lengthLeft + lengthRight);
    tempStr = toString(result);
    // if the operation returns positive number and there isn't opeartor before it
    // so we need to insert plus symbol so the string won't cause an unxpected result
    if( str[posBegin - 1] >= '0' and str[posBegin -1] <= '9' )
        tempStr.insert(0, "+");
    // insert(index, string)
    str.insert(posBegin, tempStr);
}

// to process root operation ( caret symbol '^' )
void root(std::string& str, float& result, float& sum, int& index){
    // lengthRight = length of the number in the right side of the operator
    int lengthRight;
    // tempStr = string to store the result of the operator
    std::string tempStr;
    result = std::sqrt( rightNumber(str, sum, index, lengthRight) );
    tempStr = toString(result);
    // if the operation returns positive number and there isn't opeartor before it
    // so we need to insert plus symbol so the string won't cause an unxpected result
    if( str[index - 1] >= '0' and str[index -1] <= '9' )
        tempStr.insert(0, "*");
    // erase(index, length want to delete)
    str.erase(index, lengthRight);
    // insert(index, string)
    str.insert(index, tempStr);
}

// to process factorial operation ( exclamation symbol '!' )
void factorial(std::string& str, float& result, float& sum, int& index){
    // lengthLeft = length of the number in the left side of the operator
    // posBegin = index of the first number in the left side of the operator
    int posBegin, lengthLeft = 0;
    // tempStr = string to store the result of the operator
    std::string tempStr;
    // variable to store the value if the number in the left side has a minus symbol
    bool checkMinus = false;
    // if the value of numberLeft() is negative, we need to make it positive first
    if( leftNumber(str, sum, index, lengthLeft) < 0){
        checkMinus = true;
        result = factorialNumber( -1*leftNumber(str, sum, index, lengthLeft) );
    }else{
        result = factorialNumber( leftNumber(str, sum, index, lengthLeft) );
    }
    posBegin = index - lengthLeft;
    tempStr = toString(result);
    // if there is no operator after the bracket, we need to insert "*"
    if( str[ index + 1 ] >= '0' and str[ index + 1 ] <= '9' )
        tempStr.insert(tempStr.size(), "*");
    // after we make it to positive, we need to make it negative
    if(checkMinus == true)
        tempStr.insert(0, "-");
    // erase(index, length want to delete)
    str.erase(posBegin, lengthLeft + 1);
    // insert(index, string)
    str.insert(posBegin, tempStr);
}

// to process the number between bracket ( parantheses symbol '(' and ')' )
void bracket(std::string& str, float& result, float& sum, int& indexBegin, int& indexEnd){
    // tempStr = string to store the value betweem the bracket
    std::string tempStr;
    int index;
    // substr(index, length want to take)
    // +1 and -1 because we don't need to insert the bracket into the tempStr
    tempStr = str.substr( (indexBegin + 1), (indexEnd - indexBegin - 1) );
    processOperation(tempStr, result, sum, index);
    // if there is no operator before the bracket, we need to insert "*"
    if( str[ (indexBegin - 1) ] >= '0' and str[ (indexBegin - 1) ] <= '9' )
        tempStr.insert(0, "*");
    // if there is no operator after the bracket, we need to insert "*"
    if( str[ (indexEnd + 1) ] >= '0' and str[ (indexEnd + 1) ] <= '9' ){
        tempStr.insert(tempStr.size(), "*");
    }
    // erase(index, length want to delete)
    str.erase(indexBegin, (indexEnd - indexBegin + 1) );
    // insert(index, string)
    str.insert(indexBegin, tempStr);
}
