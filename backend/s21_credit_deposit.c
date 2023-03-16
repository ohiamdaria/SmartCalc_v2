#include "s21_credit_deposit.h"

void init_deposit(deposit_t *deposit) {
  deposit->sum = 0.0;
  deposit->type_of_term = 0;
  deposit->term = 0;
  deposit->interest_rate = 0.0;
  deposit->tax_rate = 0.0;
  deposit->frequency_of_payments = 0;
  deposit->capital = 0;
  deposit->result = 0.0;
}

void init_deposit_dates(dates_t *date) {
  date->day_begin = 0;
  date->month_begin = 0;
  date->year_begin = 0;
}

int know_days_or_months_or_years(char *begin_of_term, int i) {
  int number = 0;
  while (i >= 0) {
    number = (*begin_of_term - '0') * pow(10, i) + number;
    begin_of_term++;
    i--;
  }
  return number;
}

void convert_dates_to_struct(dates_t *data, char *begin_of_term) {
  data->day_begin = know_days_or_months_or_years(begin_of_term, 1);
  data->month_begin = know_days_or_months_or_years(begin_of_term += 3, 1);
  data->year_begin = know_days_or_months_or_years(begin_of_term += 3, 3);
}

int count_period(dates_t *data) {
  data->month_begin++;
  int add_days = 0;
  if (data->month_begin > 12)
    data->month_begin = 1;
  if (data->month_begin == 1)
    add_days = 31;
  else if (data->month_begin == 2 && fmod(data->year_begin, 4) > 0.0)
    add_days = 28;
  else if (data->month_begin == 2 && !fmod(data->year_begin, 4))
    add_days = 29;
  else if (data->month_begin == 3)
    add_days = 31;
  else if (data->month_begin == 4)
    add_days = 30;
  else if (data->month_begin == 5)
    add_days = 31;
  else if (data->month_begin == 6)
    add_days = 30;
  else if (data->month_begin == 7)
    add_days = 31;
  else if (data->month_begin == 8)
    add_days = 31;
  else if (data->month_begin == 9)
    add_days = 30;
  else if (data->month_begin == 10)
    add_days = 31;
  else if (data->month_begin == 11)
    add_days = 30;
  else if (data->month_begin == 12)
    add_days = 31;

  return add_days;
}

int convert_term(deposit_t *deposit, dates_t *data) {
  int begin = data->month_begin, convert_term = 0;
  for (int i = 0; i < deposit->term; i++)
    convert_term += count_period(data);
  data->month_begin = begin;
  return convert_term;
}

int depositcalc(deposit_t *deposit, dates_t *data) {
  int L = 36500;

  int status = 0, add_days = count_period(data);
  deposit->term = ((deposit->type_of_term == 0) ? deposit->term
                                                : convert_term(deposit, data));
  int copy_term = deposit->term, count = 0;
  double added = 0;

  for (int i = add_days; i <= deposit->term; i += add_days) {
    double div = (double)add_days / (double)L;
    double tmp =
        floor(deposit->sum * deposit->interest_rate * div * 1e+6) / 1e+6;
    deposit->result_tax += floor(tmp * deposit->tax_rate * div * 1e+6) / 1e+6;

    if (deposit->capital)
      deposit->sum += floor(tmp * (1 - deposit->tax_rate * div) * 1e+6) / 1e+6;
    else
      added += floor(tmp * (1 - deposit->tax_rate * div) * 1e+6) / 1e+6;
    if (deposit->sum < 0) {
      status = 1;
      break;
    }
    copy_term -= add_days;
    add_days = count_period(data);
    if (L == 36500 && (copy_term - add_days < 0) && count < 1) {
      add_days = copy_term;
      count++;
    }
  }

  deposit->result = floor(deposit->sum * 1e+6) / 1e+6;
  if (!deposit->capital)
    deposit->result += added;
  deposit->result = floor(deposit->result * 1e+6) / 1e+6;
  return status;
}

void init_credit(credit_t *credit) {
  credit->sum = 0.0;
  credit->prozent = 0.0;
  credit->year = 0;
  credit->month = 0;
  credit->overpayment = 0.0;
  credit->overpayment_edit = 0.0;
  credit->result_edit = 0.0;
}

int creditcalc(credit_t *credit, double sum, double prozent, int year,
               int month, int type) {
  int status = OK;
  credit->sum = sum;
  credit->prozent = prozent;
  credit->year = year;
  credit->month = month;
  month += year * 12;
  double p = (double)prozent / ((double)100 * (double)12);

  if (type == 1) {
    double overpayment = sum * (p / (1 - (double)1 / pow(1 + p, month)));
    credit->overpayment = overpayment;
    credit->overpayment_edit = overpayment * month - sum;
    credit->result_edit = overpayment * month;
  } else {
    double sn = sum;
    double b = (double)sum / (double)month;
    double P = sn * p;
    double overpayment = b + P;
    double overpayment_all = floor(overpayment * 1e+6) / 1e+6;
    credit->overpayment = overpayment;

    while (sn - b > 1) {
      sn -= b;
      P = sn * p;
      overpayment = b + P;
      overpayment_all += floor(overpayment * 1e+6) / 1e+6;
    }

    credit->result_edit = overpayment_all;
    credit->overpayment_edit = overpayment_all - sum;
  }
  return status;
}
