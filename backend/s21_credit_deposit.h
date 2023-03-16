#ifndef CREDIT_DEPOSIT_H_
#define CREDIT_DEPOSIT_H_

#include "s21_calculate.h"

typedef struct {
  double sum;
  double prozent;
  int year;
  int month;
  double overpayment;
  double overpayment_edit;
  double result_edit;
} credit_t;

typedef struct {
  double sum;
  int type_of_term;
  int term;
  double interest_rate;
  double tax_rate;
  int frequency_of_payments;
  int capital;
  double result;
  double result_tax;
} deposit_t;

typedef struct {
  int day_begin;
  int month_begin;
  int year_begin;
} dates_t;

// credit
void init_credit(credit_t *credit);
int creditcalc(credit_t *credit, double sum, double prozent, int year,
               int month, int type);
int count_period(dates_t *data);

// deposit
void init_deposit(deposit_t *deposit);
void init_deposit_dates(dates_t *date);
int know_days_or_months_or_years(char *begin_of_term, int i);
void convert_dates_to_struct(dates_t *data, char *begin_of_term);
int depositcalc(deposit_t *deposit, dates_t *data);

#endif // CREDIT_DEPOSIT_H_
