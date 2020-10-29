//
//  main.cpp
//  Printer
//
//  Created by Zoreslav on 22.06.2020.
//  Copyright © 2020 Zoreslav. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

class PrintDataBase
{
public:
    PrintDataBase() {}
    virtual ~PrintDataBase() {}
    virtual void print() = 0;
};

template <class T>
class PrintData : public PrintDataBase
{
public:
    PrintData(const T value) : m_value(value) {}
    ~PrintData() {}
    
    void print() override
    {
        cout << m_value << endl;
    }
    
private:
    T m_value;
};

template <class T>
class PrintData<T*> : public PrintDataBase
{
public:
    PrintData(T* value) : m_value(value) {}
    ~PrintData() {}
    
    void print() override
    {
        cout << '[' << *m_value << ']' << endl;
    }
    
private:
    T* m_value;
};

class Printer
{
public:
    Printer() : m_data(nullptr) {}
    
    ~Printer()
    {
        delete m_data;
    }
    
    template <class T>
    void operator=(const T& value)
    {
        m_data = new PrintData<T>(value);
    }
    
    void print()
    {
        if (m_data)
            m_data->print();
    }
    
private:
    PrintDataBase* m_data;
};
 
int main()
{
    Printer printer;
 
    printer = 42;
    printer.print(); //should print "42" to standard output
 
    int* value = new int(10);
    printer = value;
    printer.print(); // should print "[10]"
 
    *value = 20; // the value pointer did not change, changed a value by it
    printer.print(); // should print "[20]"
 
    float* fvalue = new float(9.81);
    printer = fvalue;
    printer.print(); // should print "[9.81]"
 
    *fvalue = 0.2+0.3;
    printer.print(); // should print "[0.5]"
 
    printer = std::string("Hello world");
    printer.print();
    //should print "Hello world"
 
    printer = 2.718281;
    printer.print();
    //should print "2.718281"
 
    delete fvalue;
    delete value;
    return 0;
}
