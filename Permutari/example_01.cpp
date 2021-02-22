#include <iostream>
#include <cstring>
#include <cstdlib>
#include "header.h"

class Om
{
protected:
    char * nume;

public:
    Om(const char * nume)
     : nume(strdup(nume))
    {
    }
    
virtual ∼Om() { free(nume); }
};

class Student : public Om {
double nota;
public:
Student(const char * nume, double nota) : Om(nume), nota(nota) { }
void display() {
std::cout << "(" << nume << "," << nota << ")\n";
}
};

int main()
{
Student s("Eric Cartman", 10.0f);
s.display();
return 0;
}