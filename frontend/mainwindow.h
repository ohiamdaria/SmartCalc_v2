#ifndef MAINWINDOW_H
#define MAINWINDOW_H

extern "C" {
#include "../backend/s21_calculate.h"
#include "../backend/s21_credit_deposit.h"
}

#include <QComboBox>
#include <QDateEdit>
#include <QLineEdit>
#include <QMainWindow>
#include <QTimer>
#include <QVector>

#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_push_1_clicked();

  void on_push_2_clicked();

  void on_push_3_clicked();

  void on_push_4_clicked();

  void on_push_5_clicked();

  void on_push_6_clicked();

  void on_push_7_clicked();

  void on_push_8_clicked();

  void on_push_9_clicked();

  void on_push_0_clicked();

  void on_push_plus_clicked();

  void on_push_minus_clicked();

  void on_push_mul_clicked();

  void on_push_div_clicked();

  void on_push_sin_clicked();

  void on_push_cos_clicked();

  void on_push_tan_clicked();

  void on_push_asin_clicked();

  void on_push_acos_clicked();

  void on_push_atan_clicked();

  void on_push_sqrt_clicked();

  void on_push_pow_clicked();

  void on_push_mod_clicked();

  void on_push_ln_clicked();

  void on_push_right_clicked();

  void on_push_left_clicked();

  void clicked_text_add(QString toAdd);

  void on_push_clear_clicked();

  void on_push_log_clicked();

  void on_push_eq_clicked();

  void on_push_X_clicked();

  void TimerSlot();

  void on_push_dot_clicked();

  void on_graph_clicked(bool checked);

  void Animation();

  void StopAnimation();

  void if_graph_exist();

  void if_graph_not_exist();

  void on_push_run_clicked();

  void on_push_stop_clicked();

  void on_push_calc_clicked();

  void on_type_an_clicked();

  void on_type_diff_clicked();

  void clean_edit();

  void on_push_deposit_clicked();

  void on_capital_clicked();

  void on_push_clear_2_clicked();

private:
  Ui::MainWindow *ui;
  double xBegin, xEnd, yBegin, yEnd, h, X;
  int N, graph = 0, count = 0;

  // credit
  double sum, prozent;
  int month, year, type = 1;
  double result, overpayment;

  // animation
  QVector<double> x, y;
  QTimer *timer;
  int time;
  bool flag = true, flag2 = true;

  // deposit
  int capital = 0;
};

#endif  // MAINWINDOW_H
