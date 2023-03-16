#include "test.h"

#define ln(x) log(x)


START_TEST(test_1) {
    data_task_t data;
    init_input(&data);
    char str[1024] = "cos( 9.456+ 909  /sin((-1  )*log(2.3  ))) + 5689.98 ^ (-1.9)";
    double  check_result = cos(9.456+909/sin((-1)*log10(2.3)))+pow(5689.98, (-1.9));
    smart_calc(&str[0], &data);
    ck_assert_double_eq_tol(data.result, check_result, 1e-7);
}
END_TEST

START_TEST(test_2) {
    data_task_t data;
    init_input(&data);
    char str[1024] = "tan(6.08123 / log(5.6321 + 345 * (-5.2345) * (-13.111))) / ln(45.32 / (+99.1334)) ^ (  +2)";
    double check_result = tan(6.08123 / log10(5.6321 + 345 * (-5.2345) * (-13.111))) / pow(ln(45.32 / (+99.1334)), 2);
    smart_calc(&str[0], &data);
    ck_assert_double_eq_tol(data.result, check_result, 1e-7);
}
END_TEST

START_TEST(test_3) {
    data_task_t data;
    init_input(&data);
    char str[1024] = "2.4474 /8.0162/ 3.2142+tan( 0.6211 +sin(tan( 7.5952 +5.3702) ) - 4.7121^sin(  1.9427- 2.8496) )"
        "/cos(0.2688 ^0.5391+cos( tan(cos( cos(  5.6221 ))  ) /sin( 2.3295)  -tan( cos(tan( cos(9.2239)  ))"
        ") ) )";

    double check_result = 1.660108415837855;
    smart_calc(&str[0], &data);
    ck_assert_double_eq_tol(data.result, check_result, 1e-7);
}
END_TEST

START_TEST(test_4) {
    data_task_t data;
    init_input(&data);
    char str[1024] = "asin(0.256) * acos(-0.3456) / atan(0.000023456) + (2345.667 ^ (0.5) - 12.3)";
    double result = 0.0l, check_result = asin(0.256) * acos(-0.3456) / atan(0.000023456) + (pow(2345.667, 0.5) - 12.3);
    smart_calc(&str[0], &data);
    ck_assert_double_eq_tol(data.result, check_result, 1e-7);
}
END_TEST

START_TEST(test_5) {
    data_task_t data;
    init_input(&data);
    char str[1024] = "2 ^ 3 ^ 2";
    double result = 0.0l, check_result = 512.0;
    smart_calc(&str[0], &data);
    ck_assert_double_eq_tol(data.result, check_result, 1e-7);
}
END_TEST

START_TEST(test_6) {
    data_task_t data;
    init_input(&data);
    char str[1024] = "22 + - - 2";
    double result = 0.0l, check_result = 24.0;
    smart_calc(&str[0], &data);
    ck_assert_double_eq_tol(data.result, check_result, 1e-7);
}
END_TEST

START_TEST(test_7) {
    data_task_t data;
    init_input(&data);
    char str[1024] = "22 * - - 2";
    double result = 0.0l, check_result = 44.0;
    smart_calc(&str[0], &data);
    ck_assert_double_eq_tol(data.result, check_result, 1e-7);
}
END_TEST

START_TEST(test_8) {
    data_task_t data;
    init_input(&data);
    char str[1024] = "1 + --- 5";
    double result = 0.0l, check_result = -4.0;
    smart_calc(&str[0], &data);
    ck_assert_double_eq_tol(data.result, check_result, 1e-7);
}
END_TEST

START_TEST(test_x_1) {
    data_task_t data;
    init_input(&data);
    char str[1024] = "tan(6.08123 /log(   5.6321 + 345 * (-x) *(-   13.111))   ) /ln(45.32 / (+99.1334)   )^(  +2)";
    double check_result = tan(6.08123 / log10(5.6321 + 345 * (-5.2345) * (-13.111))) / pow(ln(45.32 / (+99.1334)), 2);
    data.x = 5.2345;
    smart_calc(&str[0], &data);
    ck_assert_double_eq_tol(data.result, check_result, 1e-7);
}
END_TEST

START_TEST(test_x_2) {
    data_task_t data;
    init_input(&data);
    char str[1024] = "555.666 mod 3.456 + ( ( atan(0.9876/x) + (-asin(0.222)  )  )  * cos((x * 3) ^ (  0.7889 ) ) - 2222.2 / ( -777.7 ) )";
    data.x = 17.239;
    double check_result = fmod(555.666, 3.456) + ((atan(0.9876/17.239) + (-asin(0.222))) * cos(pow(17.239 * 3, 0.7889)) - 2222.2 / (-777.7));
    smart_calc(&str[0], &data);
    ck_assert_double_eq_tol(data.result, check_result, 1e-7);
}
END_TEST

START_TEST(test_x_3) {
    data_task_t data;
    init_input(&data);
    char str[1024] = "-1678.2322 * x +  sqrt( log  (38.38 /24.55 ) + ln(58.2 - (-300.4))) * x * x * (-x)";
    data.x = 0.009;
    double check_result = -1678.2322 * 0.009 +  sqrt( log10 (38.38 /24.55 ) + ln(58.2 - (-300.4)))* 0.009 * 0.009 * (-0.009);
    smart_calc(&str[0], &data);
    ck_assert_double_eq_tol(data.result, check_result, 1e-7);
}
END_TEST

START_TEST(test_x_4) {
    data_task_t data;
    init_input(&data);
    char str[1024] = "678.987 * sin ( 23.2 -  6.7 +  sin(x *   x) -9.789 * cos(22.37/2.32)) + tan(342.35 ^ 0.7) + sin ( 23.2 -  6.7 +  sin(x *   x)"
                        "* cos(22.37/2.32) + tan(-3.4235))";
    data.x = 17.239;
    double check_result = 678.987 * sin ( 23.2 -  6.7 +  sin(17.239 *   17.239) -9.789 * cos(22.37/2.32)) + tan(pow(342.35, 0.7)) + sin ( 23.2 -  6.7 +  sin(17.239 *   17.239)
                        * cos(22.37/2.32) + tan(-3.4235));
    smart_calc(&str[0], &data);
    ck_assert_double_eq_tol(data.result, check_result, 1e-7);
}
END_TEST

START_TEST(test_x_5) {
    data_task_t data;
    init_input(&data);
    char str[1024] = "-(-87.543*sin(0.999+tan(x)-2.234))-50.66*(acos(0.234)/atan(0.55))";
    data.x = 55.5;
    double check_result = -(-87.543*sin(0.999+tan(55.5)-2.234))-50.66*(acos(0.234)/atan(0.55));
    smart_calc(&str[0], &data);
    ck_assert_double_eq_tol(data.result, check_result, 1e-7);
}
END_TEST

START_TEST(test_error_1) {
    data_task_t data;
    init_input(&data);
    char str[1024] = "-(-87.543*(sin(0.999+tan(55.5)))-2.234)-50.66*(acos(0.234)/atan(0.55)))";
    smart_calc(&str[0], &data);
    ck_assert_int_eq(data.code, ERROR);
}
END_TEST

START_TEST(test_error_2) {
    data_task_t data;
    init_input(&data);
    char str[1024] = "-(-87.543*sin(0.999+tan(55.5)-2.234))-50.66*(acos(0.234)/atan(0.55)))-(-87.543*sin(0.999+tan(55.5)-2.234))-50.66*(acos(0.234)/atan(0.55)))-(-87.543*sin(0.999+tan(55.5)-2.234))-50.66*(acos(0.234)/atan(0.55)))-(-87.543*sin(0.999+tan(55.5)-2.234))-50.66*(acos(0.234)/atan(0.55)))";
    smart_calc(&str[0], &data);
    ck_assert_int_eq(data.code, ERROR);
}
END_TEST

START_TEST(test_error_3) {
    data_task_t data;
    init_input(&data);
    char str[1024] = "-((-87.543*sin(0.999+tan(55.5)-2.234))-50.66*(acos(0.234)/atan(0.55)))-(-87.543*sin(0.999+tan(55.5)-2.234))-50.66*(acos(0.234)/atan(0.55)))-(-87.543*sin(0.999+tan(55.5)-2.234))-50.66*(acos(0.234)/atan(0.55)))-(-87.543*sin(0.999+tan(55.5)-2.234))-50.66*(acos(0.234)/atan(0.55)))";
    smart_calc(&str[0], &data);
    ck_assert_int_eq(data.code, ERROR);
}
END_TEST

START_TEST(test_null) {
    int expectedcode = ERROR;
    char str[1024] = "555.666 / x";
    data_task_t data;
    init_input(&data);
    data.x = 0.0;
    smart_calc(&str[0], &data);
    ck_assert_int_eq(data.code, expectedcode);
}
END_TEST

START_TEST(credit_1) {
    credit_t credit;
    init_credit(&credit);

    int code = OK;
    double sum = 100000.0, prozent = 4.5;
    int year = 3, month = 0, type = 1;

    creditcalc(&credit, sum, prozent, year, month, type);
    printf("%.6f\n", credit.overpayment);
    printf("%.6f\n", credit.result_edit);
    printf("%.6f\n", credit.overpayment_edit);
}
END_TEST

START_TEST(credit_2) {
    credit_t credit;
    init_credit(&credit);

    int code = OK;
    double sum = 100000.0, prozent = 13.9;
    int year = 5, month = 0, type = 2;

    creditcalc(&credit, sum, prozent, year, month, type);
    printf("%.6f\n", credit.overpayment);
    printf("%.6f\n", credit.result_edit);
    printf("%.6f\n", credit.overpayment_edit);
}
END_TEST

START_TEST(deposit_1) {
    deposit_t deposit;
    init_deposit(&deposit);
    dates_t date;
    init_deposit_dates(&date);

    int code = OK;
    double sum = 250000.0, type_of_term = 1,
        interest_rate = 24.1, tax_rate = 0.0;
    deposit.sum = sum;
    deposit.type_of_term = type_of_term;
    deposit.interest_rate = interest_rate;
    deposit.tax_rate = tax_rate;
    int term = 90, capital = 0,
        day_begin = 1, month_begin = 1, year_begin = 2000;
    deposit.term = term;
    deposit.capital = capital;
    deposit.frequency_of_payments = 1;
    date.day_begin = day_begin;
    date.month_begin = month_begin;
    date.year_begin = year_begin;

    depositcalc(&deposit, &date);
    printf("%lf\n", deposit.result);
    printf("%lf\n", deposit.result_tax);
    printf("%lf\n", deposit.result - sum);
}
END_TEST

START_TEST(deposit_2) {
    deposit_t deposit;
    init_deposit(&deposit);
    dates_t date;
    init_deposit_dates(&date);

    int code = OK;
    double sum = 250000.0, type_of_term = 2,
        interest_rate = 24.1, tax_rate = 0.0;
    deposit.sum = sum;
    deposit.type_of_term = type_of_term;
    deposit.interest_rate = interest_rate;
    deposit.tax_rate = tax_rate;
    int term = 9, capital = 0;
    char begin_of_term[15] = "07.07.2022";
    convert_dates_to_struct(&date, &begin_of_term[0]);
    deposit.term = term;
    deposit.capital = capital;
    deposit.frequency_of_payments = 2;

    depositcalc(&deposit, &date);
    printf("%lf\n", deposit.result);
    printf("%lf\n", deposit.result_tax);
    printf("%lf\n", deposit.result - sum);
}
END_TEST


Suite *suite_smartcalc(void) {
    Suite *s = suite_create("suite_s21_smartcalc");
    TCase *tc = tcase_create("s21_smartcalc");

    tcase_add_test(tc, test_1);
    tcase_add_test(tc, test_2);
    tcase_add_test(tc, test_3);
    tcase_add_test(tc, test_4);
    tcase_add_test(tc, test_5);
    tcase_add_test(tc, test_6);
    tcase_add_test(tc, test_7);
    tcase_add_test(tc, test_8);

    tcase_add_test(tc, test_error_1);
    tcase_add_test(tc, test_error_2);
    tcase_add_test(tc, test_error_3);
    tcase_add_test(tc, test_null);

    suite_add_tcase(s, tc);
    return s;
}


Suite *suite_smartcalc_x(void) {
    Suite *s1 = suite_create("suite_s21_smartcalc_x");
    TCase *tc1 = tcase_create("s21_smartcalc_x");

    tcase_add_test(tc1, test_x_1);
    tcase_add_test(tc1, test_x_2);
    tcase_add_test(tc1, test_x_3);
    tcase_add_test(tc1, test_x_4);
    tcase_add_test(tc1, test_x_5);

    suite_add_tcase(s1, tc1);
    return s1;
}

Suite *suite_smartcalc_credit(void) {
    Suite *s2 = suite_create("suite_s21_smartcalc_2");
    TCase *tc2 = tcase_create("s21_smartcalc_2");

    tcase_add_test(tc2, credit_1);
    tcase_add_test(tc2, credit_2);

    suite_add_tcase(s2, tc2);
    return s2;
}


Suite *suite_smartcalc_deposit(void) {
    Suite *s3 = suite_create("suite_s21_smartcalc_3");
    TCase *tc3 = tcase_create("s21_smartcalc_3");

    tcase_add_test(tc3, deposit_1);
    tcase_add_test(tc3, deposit_2);

    suite_add_tcase(s3, tc3);
    return s3;
}


