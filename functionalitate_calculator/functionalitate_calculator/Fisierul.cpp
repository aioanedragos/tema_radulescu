#include "Fisierul.h"

///   1+2.6/3+12.76/4*3.001+1-rad(12)+5^3-log(8)

//****************************************************************
//stringProcesing
//


void stringProcesing::stringParsing(string parsedOperation[], string operationInput, int& vector_size) {
    int j = STARTING_POINT_FOR_STRING_VECTOR;
    string number = "";
    string operators = "/*%+-^ ";
    string numbers = "0123456789.";
    string acceptedCharacter = ")";
    string openParantesis = "(";

    string intermediarParsedString[MAX_STRING_VECTOR_LENGTH];
    int intermediarVectorSize = STARTING_POINT_FOR_STRING_VECTOR;

    Operation test;
    stringProcesing test1;

    for (int i = STARTING_POINT_FOR_STRING_VECTOR; i < operationInput.size(); i++)
        if (operators.find(operationInput[i]) == -1) {
            number = number + operationInput[i];
            if (i == operationInput.size() - 1) {
                if (number.find("rad(") != -1 || number.find("log(") != -1)
                    parsedOperation[j++] = number.find('rad') != -1 ? test.Rad(number, vector_size) : test.Log(number, vector_size);
                else if (test.isNumber(number) == 1)
                    parsedOperation[j++] = number;
                else if (test.isNumber(number) == 0) {
                    cout << "Ecuatie invalida" << '\n';
                    system("pause");
                    exit(1);
                }
                else
                    parsedOperation[j++] = number;
            }
        }

        else if (operators.find(operationInput[i]) != -1) {
            if (operators.find(operationInput[i + 1]) == -1) {

                if (number.find('(') == 0) {
                    int parantesisNumber = 0;
                    for (int i = 0; i < number.size(); i++) {
                        if (openParantesis.find(number[i]) != -1)
                            parantesisNumber++;
                    }

                    string intermediarNumber = "";


                    for (int i = 1; i < number.size(); i++)
                        intermediarNumber += number[i];

                    if (intermediarNumber.find("rad(") != -1 || intermediarNumber.find("log(") != -1)
                        parantesisNumber--;

                    bool finished = false;
                    while (finished == false) {
                        intermediarNumber += operationInput[i];
                        i++;
                        if (i > operationInput.size()) {
                            cout << "Ecuatie invalida" << '\n';
                            system("pause");
                            exit(1);
                        }

                        if (acceptedCharacter.find(operationInput[i]) != -1)
                            parantesisNumber--;

                        if (openParantesis.find(operationInput[i]) != -1)
                            parantesisNumber++;

                        if (parantesisNumber == 0) {
                            //intermediarNumber += operationInput[i];
                            finished = true;
                            test1.stringParsing(intermediarParsedString, intermediarNumber, intermediarVectorSize);
                            parsedOperation[j++] = test1.calculate(intermediarParsedString, intermediarVectorSize);
                            i++;
                        }

                    }
                }

                else if (number.find("rad(") != -1 || number.find("log(") != -1) {
                    int passedParantesisNumber = 0;
                    int parantesisNumber = 0;

                    for (int i = 0; i < number.size(); i++)
                        if (openParantesis.find(number[i]) != -1)
                            parantesisNumber++;

                    passedParantesisNumber = parantesisNumber - 1;

                    if (number[FOUR] == 'r' || number[FOUR] == 'l') {
                        parantesisNumber--;
                        passedParantesisNumber--;
                    }

                    string intermediarNumber = "";
                    bool finished = false;
                    while (finished == false && (passedParantesisNumber != 0 || number[number.size() - 1] != ')')) {
                        intermediarNumber += operationInput[i];
                        //number += operationInput[i];
                        i++;

                        if (acceptedCharacter.find(operationInput[i]) != -1)
                            parantesisNumber--;

                        if (openParantesis.find(operationInput[i]) != -1)
                            parantesisNumber++;
                        if (parantesisNumber == 0) {
                            finished = true;
                            intermediarNumber += operationInput[i];
                            //number += operationInput[i];
                            number += intermediarNumber;
                            i++;
                            intermediarNumber = "";
                        }

                    }

                    parsedOperation[j++] = number.find('rad(') != -1 ? test.Rad(number, passedParantesisNumber) : test.Log(number, vector_size);
                }
                else if (test.isNumber(number) == 1)
                    parsedOperation[j++] = number;
                else {
                    cout << "Ecuatie invalida" << '\n';
                    system("pause");
                    exit(1);
                }
                parsedOperation[j++] = operationInput[i];
                number = "";
            }
            else {
                cout << "Ecuatie invalida" << '\n';
                system("pause");
                exit(1);
            }
        }
        else
            number += operationInput[i];

    vector_size = j;

}


string stringProcesing::calculate(string parsedOperation[], int vector_size) {
    bool finished = false;
    int pozition = STARTING_POINT_FOR_STRING_VECTOR;
    bool powerUp = true;
    bool multiply_division = false;
    bool gather_decrease = false;
    Operation execute;

    for (int i = 0; i < vector_size; i++) {
        cout << parsedOperation[i] << ' ';
    }
    cout << '\n';
    while (finished == false)
    {

        //powerUp

        if (parsedOperation[pozition].find('^') != -1 && powerUp == true && vector_size > 0) {
            execute.powerUp(parsedOperation, pozition, vector_size);

        }
        else if (powerUp == true) {
            pozition++;
        }

        //multiply_division

        if ((parsedOperation[pozition].find('*') != -1 || parsedOperation[pozition].find('/') != -1) && multiply_division == true && vector_size > 0) {
            execute.multiplyDivision(parsedOperation, pozition, vector_size);

        }
        else if (multiply_division == true) {
            pozition++;
        }



        //gather_decrease

        if ((parsedOperation[pozition].find('+') != -1 || parsedOperation[pozition].find('-') != -1) && gather_decrease == true && vector_size > 0) {
            execute.gatherDecrease(parsedOperation, pozition, vector_size);

        }
        else if (gather_decrease == true) {
            pozition++;
        }



        if (parsedOperation[pozition].empty() == true) {
            pozition = STARTING_POINT_FOR_STRING_VECTOR;
            execute.changeExecution(powerUp, multiply_division, gather_decrease);
        }

        if (powerUp == false && multiply_division == false && gather_decrease == false) {
            finished = true;
            return parsedOperation[0].c_str();
        }
    }
}


//****************************************************************
//Operation
//


string Operation::Rad(string OperationInput, int& passedParantesisNumber) {

    Operation execute;
    stringProcesing executeS;
    string stringVector[MAX_STRING_VECTOR_LENGTH];
    int intermediarVectorSize = 0;

    string stringNumber;
    int intNumber;
    float floatNumber;
    char separator = NULL;
    int stringSize = OperationInput.size() - TWO;
    if (passedParantesisNumber != 0)
        while (/*separator != '('*/ passedParantesisNumber != 0) {
            stringNumber = OperationInput[stringSize] + stringNumber;
            separator = OperationInput[stringSize - 1];
            if (separator == '(')
                passedParantesisNumber--;
            stringSize--;
            if (passedParantesisNumber == 0) {
                stringNumber = OperationInput[stringSize] + stringNumber;
            }
        }
    else
        /*while (separator != '(') {
            stringNumber = OperationInput[stringSize] + stringNumber;
            separator = OperationInput[stringSize - 1];
            stringSize--;
        }*/
        for (int i = 4; i < OperationInput.size() - 1; i++)
            stringNumber += OperationInput[i];

    if (stringNumber.find('.') != -1) {
        if (execute.isNumber(stringNumber) == 1) {
            /*floatNumber = sqrt(atof(stringNumber.c_str()));
            return to_string(floatNumber);*/
            executeS.stringParsing(stringVector, stringNumber, intermediarVectorSize);
            floatNumber = sqrt(atof(executeS.calculate(stringVector, intermediarVectorSize).c_str()));
            return to_string(floatNumber);
        }
        else {
            cout << "Ecuatie invalida" << '\n';
            system("pause");
            exit(1);
        }
    }

    else {
        //floatNumber = sqrt(atof(stringNumber.c_str()));
        executeS.stringParsing(stringVector, stringNumber, intermediarVectorSize);
        floatNumber = sqrt(atof(executeS.calculate(stringVector, intermediarVectorSize).c_str()));
        return to_string(floatNumber);

    }
}




string Operation::Log(string OperationInput, int& passedParantesisNumber) {
    stringProcesing executeS;
    string stringVector[MAX_STRING_VECTOR_LENGTH];
    int intermediarVectorSize = 0;

    string stringNumber;
    int intNumber;
    float floatNumber;
    Operation execute;
    char separator = NULL;
    int stringSize = OperationInput.size() - TWO;

    if (passedParantesisNumber != 0)
        while (/*separator != '('*/ passedParantesisNumber != 0) {
            stringNumber = OperationInput[stringSize] + stringNumber;
            separator = OperationInput[stringSize - 1];
            if (separator == '(')
                passedParantesisNumber--;
            stringSize--;
            if (passedParantesisNumber == 0) {
                stringNumber = OperationInput[stringSize] + stringNumber;
            }
        }
    else
        for (int i = 4; i < OperationInput.size() - 1; i++)
            stringNumber += OperationInput[i];

    if (stringNumber.find('.') != -1) {
        if (execute.isNumber(stringNumber) == 1) {
            executeS.stringParsing(stringVector, stringNumber, intermediarVectorSize);
            floatNumber = log2(atof(executeS.calculate(stringVector, intermediarVectorSize).c_str()));
            return to_string(floatNumber);
        }
        else {
            cout << "Ecuatie invalida" << '\n';
            system("pause");
            exit(1);
        }
    }
    else {
        if (execute.isNumber(stringNumber) == 1) {
            executeS.stringParsing(stringVector, stringNumber, intermediarVectorSize);
            floatNumber = log2(atof(executeS.calculate(stringVector, intermediarVectorSize).c_str()));
            return to_string(floatNumber);
        }
        else {
            cout << "Ecuatie invalida" << '\n';
            system("pause");
            exit(1);
        }
    }
}




//string Operation::Log(string OperationInput, int& vector_size) {
//  string stringNumber;
//  int intNumber;
//  float floatNumber;
//  Operation execute;
//  char separator = NULL;
//  int stringSize = OperationInput.size() - 2;
//
//  while (separator != '(') {
//      stringNumber = OperationInput[stringSize] + stringNumber;
//      separator = OperationInput[stringSize - 1];
//      stringSize--;
//  }
//
//  if (stringNumber.find('.') != -1) {
//      if (execute.isNumber(stringNumber) == 1) {
//          floatNumber = log2f(atof(stringNumber.c_str()));
//          return to_string(floatNumber);
//      }
//      else {
//          cout << "Ecuatie invalida" << '\n';
//          system("pause");
//          exit(1);
//      }
//  }
//  else {
//      if (execute.isNumber(stringNumber) == 1) {
//          floatNumber = log2(atoi(stringNumber.c_str()));
//          return to_string(floatNumber);
//      }
//      else {
//          cout << "Ecuatie invalida" << '\n';
//          system("pause");
//          exit(1);
//      }
//  }
//}

void Operation::powerUp(string parsedOperation[], int pozition, int& vector_size) {



    float rightNumber = atof(parsedOperation[pozition + 1].c_str());
    float leftNumber = atof(parsedOperation[pozition - 1].c_str());
    if (rightNumber == 0 || leftNumber == 0)
    {
        cout << "Ridicare la putere invalida" << '\n';
        system("pause");
        exit(1);
    }

    if (parsedOperation[pozition - 1].find('.') != -1) {
        auto Result = pow(atof(parsedOperation[pozition - 1].c_str()), (parsedOperation[pozition + 1].find('.') != -1 ? atof(parsedOperation[pozition + 1].c_str()) : atoi(parsedOperation[pozition + 1].c_str())));
        parsedOperation[pozition - 1] = to_string(Result);
    }
    else {
        auto Result = pow(atoi(parsedOperation[pozition - 1].c_str()), (parsedOperation[pozition + 1].find('.') != -1 ? atof(parsedOperation[pozition + 1].c_str()) : atoi(parsedOperation[pozition + 1].c_str())));
        parsedOperation[pozition - 1] = to_string(Result);
    }

    for (int i = pozition; i < vector_size; i++)
        parsedOperation[i] = parsedOperation[i + TWO];
    vector_size -= TWO;
}

void Operation::multiplyDivision(string parsedOperation[], int pozition, int& vector_size) {
    int intNumber;
    float floatNumber;

    if (parsedOperation[pozition].find('*') != -1) {

        //if (parsedOperation[pozition - 1].find('.') != -1) {
        //    //auto Result = atof(parsedOperation[pozition - 1].c_str()) * (parsedOperation[pozition + 1].find('.') != -1 ? atof(parsedOperation[pozition + 1].c_str()) : atoi(parsedOperation[pozition + 1].c_str()));
        //    auto Result = multiply(parsedOperation[pozition - 1].c_str(), parsedOperation[pozition = 1].c_str());
        //    parsedOperation[pozition - 1] = Result;
        //}

            //auto Result = atoi(parsedOperation[pozition - 1].c_str()) * (parsedOperation[pozition + 1].find('.') != -1 ? atof(parsedOperation[pozition + 1].c_str()) : atoi(parsedOperation[pozition + 1].c_str()));
        auto Result = multiply(parsedOperation[pozition - 1].c_str(), parsedOperation[pozition + 1].c_str());
        parsedOperation[pozition - 1] = Result;


    }
    else {

        auto rightNumber = atof(parsedOperation[pozition + 1].c_str());
        if (rightNumber == 0) {
            cout << "Impartire la 0 imposibila" << '\n';
            system("pause");
            exit(1);
        }


        //if (parsedOperation[pozition - 1].find('.') != -1) {
            //auto Result = atof(parsedOperation[pozition - 1].c_str()) / (parsedOperation[pozition + 1].find('.') != -1 ? atof(parsedOperation[pozition + 1].c_str()) : atoi(parsedOperation[pozition + 1].c_str()));
         //   string Result = longDivision(parsedOperation[pozition - 1].c_str(), atoi(parsedOperation[pozition + 1].c_str()));
          //  parsedOperation[pozition - 1] = Result;
        //}

            //auto Result = atoi(parsedOperation[pozition - 1].c_str()) / (parsedOperation[pozition + 1].find('.') != -1 ? atof(parsedOperation[pozition + 1].c_str()) : atoi(parsedOperation[pozition + 1].c_str()));
        string Result = longDivision(parsedOperation[pozition - 1].c_str(), atoi(parsedOperation[pozition + 1].c_str()));
        parsedOperation[pozition - 1] = Result;


    }

    for (int i = pozition; i < vector_size; i++)
        parsedOperation[i] = parsedOperation[i + TWO];
    vector_size -= TWO;
}

void Operation::gatherDecrease(string parsedOperation[], int pozition, int& vector_size) {
    int intNumber;
    float floatNumber;

    if (parsedOperation[pozition].find('+') != -1) {

        //if (parsedOperation[pozition - 1].find('.') != -1) {
        //    //auto Result = atof(parsedOperation[pozition - 1].c_str()) + (parsedOperation[pozition + 1].find('.') != -1 ? atof(parsedOperation[pozition + 1].c_str()) : atoi(parsedOperation[pozition + 1].c_str()));
        //    auto Result = bigNumberSum(parsedOperation[pozition - 1].c_str(), parsedOperation[pozition + 1].c_str());
        //    parsedOperation[pozition - 1] = Result;
        //}

            //auto Result = atoi(parsedOperation[pozition - 1].c_str()) + (parsedOperation[pozition + 1].find('.') != -1 ? atof(parsedOperation[pozition + 1].c_str()) : atoi(parsedOperation[pozition + 1].c_str()));
        auto Result = bigNumberSum(parsedOperation[pozition - 1].c_str(), parsedOperation[pozition + 1].c_str());
        parsedOperation[pozition - 1] = Result;


    }
    else {
        //if (parsedOperation[pozition - 1].find('.') != -1) {
        //    //auto Result = atof(parsedOperation[pozition - 1].c_str()) - (parsedOperation[pozition + 1].find('.') != -1 ? atof(parsedOperation[pozition + 1].c_str()) : atoi(parsedOperation[pozition + 1].c_str()));
        //    auto Result = findDiff(parsedOperation[pozition - 1].c_str(), parsedOperation[pozition + 1].c_str());
        //    parsedOperation[pozition - 1] = Result;
        //}
        // 
            //auto Result = atoi(parsedOperation[pozition - 1].c_str()) - (parsedOperation[pozition + 1].find('.') != -1 ? atof(parsedOperation[pozition + 1].c_str()) : atoi(parsedOperation[pozition + 1].c_str()));
        auto Result = findDiff(parsedOperation[pozition - 1].c_str(), parsedOperation[pozition + 1].c_str());
        parsedOperation[pozition - 1] = Result;

    }

    for (int i = pozition; i < vector_size; i++)
        parsedOperation[i] = parsedOperation[i + TWO];
    vector_size -= TWO;
}


void Operation::changeExecution(bool& powerUp, bool& multiply_division, bool& gather_decrease) {
    if (powerUp == true && multiply_division == false && gather_decrease == false) {
        powerUp = false;
        multiply_division = true;
    }
    else if (powerUp == false && multiply_division == true && gather_decrease == false) {
        multiply_division = false;
        gather_decrease = true;
    }
    else
        gather_decrease = false;
}

int Operation::isNumber(string Number) {

    string numbers = "0123456789.";

    for (int i = 0; i < Number.size(); i++)
        if (numbers.find(Number[i]) == -1)
            return 0;
    return 1;
}

string Operation::bigNumberSum(string str1, string str2) {

    // Before proceeding further, make sure length
    // of str2 is larger.
    if (str1.length() > str2.length())
        swap(str1, str2);

    // Take an empty string for storing result
    string str = "";

    // Calculate length of both string
    int n1 = str1.length(), n2 = str2.length();

    // Reverse both of strings
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());

    int carry = 0;
    for (int i = 0; i < n1; i++)
    {
        // Do school mathematics, compute sum of
        // current digits and carry
        int sum = ((str1[i] - '0') + (str2[i] - '0') + carry);
        str.push_back(sum % 10 + '0');

        // Calculate carry for next step
        carry = sum / 10;
    }

    // Add remaining digits of larger number
    for (int i = n1; i < n2; i++)
    {
        int sum = ((str2[i] - '0') + carry);
        str.push_back(sum % 10 + '0');
        carry = sum / 10;
    }

    // Add remaining carry
    if (carry)
        str.push_back(carry + '0');

    // reverse resultant string
    reverse(str.begin(), str.end());

    return str;
}

bool Operation::isSmaller(string str1, string str2)
{
    // Calculate lengths of both string
    int n1 = str1.length(), n2 = str2.length();

    if (n1 < n2)
        return true;
    if (n2 < n1)
        return false;

    for (int i = 0; i < n1; i++)
        if (str1[i] < str2[i])
            return true;
        else if (str1[i] > str2[i])
            return false;

    return false;
}

// Function for find difference of larger numbers
string Operation::findDiff(string str1, string str2)
{
    // Before proceeding further, make sure str1
    // is not smaller
    if (isSmaller(str1, str2))
        swap(str1, str2);

    // Take an empty string for storing result
    string str = "";

    // Calculate length of both string
    int n1 = str1.length(), n2 = str2.length();

    // Reverse both of strings
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());

    int carry = 0;

    // Run loop till small string length
    // and subtract digit of str1 to str2
    for (int i = 0; i < n2; i++) {
        // Do school mathematics, compute difference of
        // current digits

        int sub
            = ((str1[i] - '0') - (str2[i] - '0') - carry);

        // If subtraction is less then zero
        // we add then we add 10 into sub and
        // take carry as 1 for calculating next step
        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;

        str.push_back(sub + '0');
    }

    // subtract remaining digits of larger number
    for (int i = n2; i < n1; i++) {
        int sub = ((str1[i] - '0') - carry);

        // if the sub value is -ve, then make it positive
        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;

        str.push_back(sub + '0');
    }

    // reverse resultant string
    reverse(str.begin(), str.end());

    return str;
}

string Operation::multiply(string num1, string num2)
{
    int len1 = num1.size();
    int len2 = num2.size();
    if (len1 == 0 || len2 == 0)
        return "0";

    // will keep the result number in vector
    // in reverse order
    vector<int> result(len1 + len2, 0);

    // Below two indexes are used to find positions
    // in result.
    int i_n1 = 0;
    int i_n2 = 0;

    // Go from right to left in num1
    for (int i = len1 - 1; i >= 0; i--)
    {
        int carry = 0;
        int n1 = num1[i] - '0';

        // To shift position to left after every
        // multiplication of a digit in num2
        i_n2 = 0;

        // Go from right to left in num2            
        for (int j = len2 - 1; j >= 0; j--)
        {
            // Take current digit of second number
            int n2 = num2[j] - '0';

            // Multiply with current digit of first number
            // and add result to previously stored result
            // at current position.
            int sum = n1 * n2 + result[i_n1 + i_n2] + carry;

            // Carry for next iteration
            carry = sum / 10;

            // Store result
            result[i_n1 + i_n2] = sum % 10;

            i_n2++;
        }

        // store carry in next cell
        if (carry > 0)
            result[i_n1 + i_n2] += carry;

        // To shift position to left after every
        // multiplication of a digit in num1.
        i_n1++;
    }

    // ignore '0's from the right
    int i = result.size() - 1;
    while (i >= 0 && result[i] == 0)
        i--;

    // If all were '0's - means either both or
    // one of num1 or num2 were '0'
    if (i == -1)
        return "0";

    // generate the result string
    string s = "";

    while (i >= 0)
        s += std::to_string(result[i--]);

    return s;
}

string Operation::longDivision(string number, int divisor)
{
    // As result can be very large store it in string
    string ans;

    // Find prefix of number that is larger
    // than divisor.
    int idx = 0;
    int temp = number[idx] - '0';
    while (temp < divisor)
        temp = temp * 10 + (number[++idx] - '0');

    // Repeatedly divide divisor with temp. After
    // every division, update temp to include one
    // more digit.
    while (number.size() > idx) {
        // Store result in answer i.e. temp / divisor
        ans += (temp / divisor) + '0';

        // Take next digit of number
        temp = (temp % divisor) * 10 + number[++idx] - '0';
    }

    // If divisor is greater than number
    if (ans.length() == 0)
        return "0";

    // else return ans
    return ans;
}
