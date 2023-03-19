#ifndef MODEL_H
#define MODEL_H

#include <cstring>

extern "C" {
#include "/backend/s21_calculate.h"
#include "/backend/s21_credit_deposit.h"
}

enum Code {
    SUCCESS = 0,
    FAILURE = 1,
};

class Model {
private:
    struct input_data {
        char c_input[512] = {0},
        int need_graph = SUCCESS;
        double X = 0.0;
    } input_data;
    output_data output_data;
    // will add it later
    /* // credit
     double sum, prozent;
     int month, year, type = 1;
     double result, overpayment;
     // deposit
     int capital = 0; */

public:
    Model() { init_input(this->output_data); }

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

    void get_data();

    void set_data(Qstring *input);

};

#endif  // MODEL_H