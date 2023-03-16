#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Model.h"

class Controller
{
private:
    Model *model;
public:
    Controller(ExampleModel *m):model(m) {};
    double calculate_usual(double a);
    double calculate_deposit(double a);
    double calculate_credit(double a);
    void reset();
};

#endif CONTROLLER_H