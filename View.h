#ifndef VIEW_H
#define VIEW_H

#include "Controller.h"

enum Choice
{
    USUAL = 1,
    CREDIT = 2,
    DEPOSIT = 3,
};

class View
{
private:
    Controller *controller;
public:
    ConsoleView(Controller *c):controller(c){};
    void displayMenu();
    int performChoice();
    double performNumericInput();
    void startEventLoop();
};

#endif