#ifndef SRC_TESTS_SRC_TEST_H
#define SRC_TESTS_SRC_TEST_H

#include "../s21_calculate.h"
#include "../s21_credit_deposit.h"
#include <check.h>
#include <stdlib.h>
#include <time.h>

Suite *suite_smartcalc(void);
Suite *suite_smartcalc_x(void);
Suite *suite_smartcalc_credit(void);
Suite *suite_smartcalc_deposit(void);

void run_tests(void);
void run_testcase(Suite *testcase);

double get_rand(double min, double max);
#endif  //  SRC_TESTS_SRC_TEST_H
