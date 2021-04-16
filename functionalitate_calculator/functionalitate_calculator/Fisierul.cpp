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
                    for (int i = 0; i < number.size(); i++){
                        if (openParantesis.find(number[i]) != -1)
                            parantesisNumber++;
                    }
 
                    string intermediarNumber = "";
 
 
                    for (int i = 1; i < number.size(); i++)
                        intermediarNumber += number[i];
 
                    if (intermediarNumber.find("rad(") != -1 || intermediarNumber.find("log(") != -1)
                        parantesisNumber--;
 
                    bool finished = false;
                    while (finished == false){
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
 
    while (finished == false)
    {
 
        //powerUp
 
        if (parsedOperation[pozition].find('^') != -1 && powerUp == true && vector_size > 0) {
            execute.powerUp(parsedOperation, pozition, vector_size);
            
        }
        else if(powerUp == true) {
            pozition++;
        }
 
        //multiply_division
 
        if ((parsedOperation[pozition].find('*') != -1 || parsedOperation[pozition].find('/') != -1) && multiply_division == true && vector_size > 0) {
            execute.multiplyDivision(parsedOperation, pozition, vector_size);
        
        }
        else if(multiply_division == true) {
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
            return to_string(atof(parsedOperation[0].c_str()));
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
 
void Operation::powerUp(string parsedOperation [], int pozition, int &vector_size) {
 
 
 
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
 
void Operation::multiplyDivision(string parsedOperation[], int pozition, int &vector_size) {
    int intNumber;
    float floatNumber;
 
    if (parsedOperation[pozition].find('*') != -1) {
 
        if (parsedOperation[pozition - 1].find('.') != -1) {
            auto Result = atof(parsedOperation[pozition - 1].c_str()) * (parsedOperation[pozition + 1].find('.') != -1 ? atof(parsedOperation[pozition + 1].c_str()) : atoi(parsedOperation[pozition + 1].c_str()));
            parsedOperation[pozition - 1] = to_string(Result);
        }
        else {
            auto Result = atoi(parsedOperation[pozition - 1].c_str()) * (parsedOperation[pozition + 1].find('.') != -1 ? atof(parsedOperation[pozition + 1].c_str()) : atoi(parsedOperation[pozition + 1].c_str()));
            parsedOperation[pozition - 1] = to_string(Result);
        }
 
    }
    else {
 
        auto rightNumber = atof(parsedOperation[pozition + 1].c_str());
        if (rightNumber == 0) {
            cout << "Impartire la 0 imposibila" << '\n';
            system("pause");
            exit(1);
        }
 
 
        if (parsedOperation[pozition - 1].find('.') != -1) {
            auto Result = atof(parsedOperation[pozition - 1].c_str()) / (parsedOperation[pozition + 1].find('.') != -1 ? atof(parsedOperation[pozition + 1].c_str()) : atoi(parsedOperation[pozition + 1].c_str()));
            parsedOperation[pozition - 1] = to_string(Result);
        }
        else {
            auto Result = atoi(parsedOperation[pozition - 1].c_str()) / (parsedOperation[pozition + 1].find('.') != -1 ? atof(parsedOperation[pozition + 1].c_str()) : atoi(parsedOperation[pozition + 1].c_str()));
            parsedOperation[pozition - 1] = to_string(Result);
        }
 
    }
 
    for (int i = pozition; i < vector_size; i++)
        parsedOperation[i] = parsedOperation[i + TWO];    
    vector_size -= TWO;
}
 
void Operation::gatherDecrease(string parsedOperation[], int pozition, int &vector_size) {
    int intNumber;
    float floatNumber;
 
    if (parsedOperation[pozition].find('+') != -1) {
 
        if (parsedOperation[pozition - 1].find('.') != -1) {
            auto Result = atof(parsedOperation[pozition - 1].c_str()) + (parsedOperation[pozition + 1].find('.') != -1 ? atof(parsedOperation[pozition + 1].c_str()) : atoi(parsedOperation[pozition + 1].c_str()));
            parsedOperation[pozition - 1] = to_string(Result);
        }
        else {
            auto Result = atoi(parsedOperation[pozition - 1].c_str()) + (parsedOperation[pozition + 1].find('.') != -1 ? atof(parsedOperation[pozition + 1].c_str()) : atoi(parsedOperation[pozition + 1].c_str()));
            parsedOperation[pozition - 1] = to_string(Result);
        }
 
    }
    else {
        if (parsedOperation[pozition - 1].find('.') != -1) {
            auto Result = atof(parsedOperation[pozition - 1].c_str()) - (parsedOperation[pozition + 1].find('.') != -1 ? atof(parsedOperation[pozition + 1].c_str()) : atoi(parsedOperation[pozition + 1].c_str()));
            parsedOperation[pozition - 1] = to_string(Result);
        }
        else {
            auto Result = atoi(parsedOperation[pozition - 1].c_str()) - (parsedOperation[pozition + 1].find('.') != -1 ? atof(parsedOperation[pozition + 1].c_str()) : atoi(parsedOperation[pozition + 1].c_str()));
            parsedOperation[pozition - 1] = to_string(Result);
        }
 
    }
 
    for (int i = pozition; i < vector_size; i++)
        parsedOperation[i] = parsedOperation[i + TWO];
    vector_size -= TWO;
}
 
 
void Operation::changeExecution(bool &powerUp, bool &multiply_division, bool &gather_decrease) {
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
 
//string Operation::parantesisCheck(string number) {
//  int vector_size;
//  string parsedOperation[MAX_STRING_VECTOR_LENGTH];
//  stringProcesing *execute = new stringProcesing();
//
//  execute->stringParsing(parsedOperation, number, vector_size);
//
//  return execute->calculate(parsedOperation, vector_size);
//  
//}