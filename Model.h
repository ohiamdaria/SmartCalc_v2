#ifndef MODEL_H
#define MODEL_H

extern "C" {
#include "/backend/s21_calculate.h"
#include "/backend/s21_credit_deposit.h"
}

class Model {
private:
    double data_;
    // will add it later
    /* // credit
     double sum, prozent;
     int month, year, type = 1;
     double result, overpayment;
     // deposit
     int capital = 0; */
public:
    Model() : data_(0);

    ~Model();

    /* CHOOSE FUNCTION THAT U NEED */

    void calculate();

    /* CALL FUNCTION "smart_calc"
     * need:
     *     c_input - c_string converted to usual str
     *     data - struct data_task_t
     * */

    void calculate_default();

    void calculate_deposit();

    void calculate_credit();

};

#endif  // MODEL_H