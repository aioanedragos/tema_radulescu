#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <math.h>


using namespace std;

#define FOUR 4

#define TWO 2

#define MAX_STRING_VECTOR_LENGTH 100

#define STARTING_POINT_FOR_STRING_VECTOR 0

class stringProcesing {
public:
    /// ************************************************************************************
    /// @brief putting each string from the input(numbers and operators to a string vector)_
    /// @param[in] parsedOperation: a vector of strings where tha input is parsed
    /// @param[in] operationInput: the ecuation that need to be calculated
    /// @param[in] vector_size: the length of the vector after the function execution
    ///

    void stringParsing(string parsedOperation[], string operationInput, int& vector_size);

    /// ************************************************************************************
    /// @brief calculate the answer for the given ecuation
    /// @param[in] parsedOperation: a vector of strings that have the parsed input stored
    /// @param[in] vector_size: the length of the vector
    /// return a string that represents the result of the input ecuation
    ///

    string calculate(string parsedOperation[], int vector_size);

};

class Operation {

public:

    string Rad(string Operation, int& vector_size);

    /// ************************************************************************************
    /// @brief calculate the rad(x) operation and returns the answer
    /// @param[in] parsedOperation: a vector of strings that have the parsed input stored
    /// @param[in] vector_size: the update of the vector length
    /// return the result of rad operation
    ///

    string Log(string operation, int& vector_size);

    /// ************************************************************************************
    /// @brief calculate the log(x) operation and returns the answer
    /// @param[in] parsedOperation: a vector of strings that have the parsed input stored
    /// @param[in] vector_size: the update of the vector length
    /// return the result of log operation
    ///

    void powerUp(string parsedOperation[], int pozition, int& vector_size);

    /// ************************************************************************************
    /// @brief calculate the x^y(power up) operation 
    /// @param[in] parsedOperation: a vector of strings that have the parsed input stored
    /// @param[in] pozition: the index where the "^" character is found in the vector
    /// @param[in] vector_size: the update of the vector length
    ///

    void multiplyDivision(string parsedOperation[], int pozition, int& vector_size);

    /// ************************************************************************************
    /// @brief calculate the multiply or the division operation. it depends to the given sign('*' or '/')
    /// @param[in] parsedOperation: a vector of strings that have the parsed input stored
    /// @param[in] pozition: the index where the "*" or "/" character is found in the vector
    /// @param[in] vector_size: the update of the vector length
    ///

    void gatherDecrease(string parsedOperation[], int pozition, int& vector_size);

    /// ************************************************************************************
    /// @brief calculate the gather or the decrease operation. it depends to the given sign('+' or '-')
    /// @param[in] parsedOperation: a vector of strings that have the parsed input stored
    /// @param[in] pozition: the index where the "+" or "-" character is found in the vector
    /// @param[in] vector_size: the update of the vector length
    ///

    void changeExecution(bool& powerUp, bool& multiply_division, bool& gather_decrease);

    /// ************************************************************************************
    /// @brief decides what type of operation must be made at moment
    /// @param[in] powerUp: the powerUp function token
    /// @param[in] multiply_division: the multiply_division token
    /// @param[in] gather_decrease: the gather_decrease token
    ///

    int isNumber(string Number);

    /// ************************************************************************************
    /// @brief cheack if the given string is formed only with number;
    /// @param[in] Number: the string that need to be checked
    /// return 1 if the string is formed only with numbers
    /// return 0 if the string isn`t formed only with numbers
    ///

    //string parantesisCheck(string number);
};
