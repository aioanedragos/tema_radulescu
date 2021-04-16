#include "Fisierul.h"

///  rad(((3+3)+3)-3)-7+8



int main()
{
    int vector_size = STARTING_POINT_FOR_STRING_VECTOR;

    string operationInput;

    string parsedOperation[MAX_STRING_VECTOR_LENGTH];

    cout << "Enter you ecuation : ";

    getline(cin, operationInput);

    stringProcesing* ceva = new stringProcesing();

    ceva->stringParsing(parsedOperation, operationInput, vector_size);

    cout << "The answer is : " << ceva->calculate(parsedOperation, vector_size) << '\n';

    system("pause");
    return 0;
}