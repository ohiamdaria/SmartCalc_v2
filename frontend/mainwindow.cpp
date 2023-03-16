#include "mainwindow.h"

#include <QMainWindow>
#include <cstring>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->push_run->setText("START");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::clicked_text_add(QString toAdd) {
  QString text = ui->Display->text();
  ui->Display->setText(text + toAdd);
}

void MainWindow::on_push_clear_clicked() {
  QString text = ui->Display->text();
  text.chop(1);
  if (text.isEmpty()) {
    text = "";
  }
  ui->Display->setText(text);
}

void MainWindow::on_push_1_clicked() { clicked_text_add("1"); }

void MainWindow::on_push_2_clicked() { clicked_text_add("2"); }

void MainWindow::on_push_3_clicked() { clicked_text_add("3"); }

void MainWindow::on_push_4_clicked() { clicked_text_add("4"); }

void MainWindow::on_push_5_clicked() { clicked_text_add("5"); }

void MainWindow::on_push_6_clicked() { clicked_text_add("6"); }

void MainWindow::on_push_7_clicked() { clicked_text_add("7"); }

void MainWindow::on_push_8_clicked() { clicked_text_add("8"); }

void MainWindow::on_push_9_clicked() { clicked_text_add("9"); }

void MainWindow::on_push_0_clicked() { clicked_text_add("0"); }

void MainWindow::on_push_plus_clicked() { clicked_text_add("+"); }

void MainWindow::on_push_minus_clicked() { clicked_text_add("-"); }

void MainWindow::on_push_mul_clicked() { clicked_text_add("*"); }

void MainWindow::on_push_div_clicked() { clicked_text_add("/"); }

void MainWindow::on_push_sin_clicked() { clicked_text_add("sin"); }

void MainWindow::on_push_cos_clicked() { clicked_text_add("cos"); }

void MainWindow::on_push_tan_clicked() { clicked_text_add("tan"); }

void MainWindow::on_push_asin_clicked() { clicked_text_add("asin"); }

void MainWindow::on_push_acos_clicked() { clicked_text_add("acos"); }

void MainWindow::on_push_atan_clicked() { clicked_text_add("atan"); }

void MainWindow::on_push_sqrt_clicked() { clicked_text_add("sqrt"); }

void MainWindow::on_push_pow_clicked() { clicked_text_add("^"); }

void MainWindow::on_push_mod_clicked() { clicked_text_add("mod"); }

void MainWindow::on_push_ln_clicked() { clicked_text_add("ln"); }

void MainWindow::on_push_right_clicked() { clicked_text_add("("); }

void MainWindow::on_push_left_clicked() { clicked_text_add(")"); }

void MainWindow::on_push_log_clicked() { clicked_text_add("log"); }

void MainWindow::on_push_X_clicked() { clicked_text_add("x"); }

void MainWindow::on_push_dot_clicked() { clicked_text_add("."); }

void MainWindow::on_push_eq_clicked() {
  ui->widget->clearGraphs();

  QString input = ui->Display->text();
  char c_input[512] = {0};

  strncpy(c_input, qPrintable(input), 255);
  if (!strcmp(c_input, "")) {
    ui->Display->setText("error");
  } else if (graph) {
    if_graph_exist();
  } else if (!graph) {
    if_graph_not_exist();
  }
}

void MainWindow::on_graph_clicked(bool checked) {
  if (checked)
    graph = 1;
  else
    graph = 0;
}

void MainWindow::TimerSlot() {
  ui->widget->clearGraphs();
  QString input = ui->Display->text();
  char c_input[512] = {0};

  ui->widget->addGraph();
  QPen DotPen;
  DotPen.setWidthF(2);
  ui->widget->graph(0)->setPen(DotPen);
  ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui->widget->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssDisc, 1));

  if (time <= 20 * N) {
    if (X <= -xBegin) {
      strncpy(c_input, qPrintable(input), 255);
      data_task_t data;
      init_input(&data);
      data.x = X;
      smart_calc(c_input, &data);
      x.push_back(X);
      y.push_back(data.result);
      X += h;
    }
    time += 20;
  } else {
    time = 0;
    timer->stop();
  }

  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
}

void MainWindow::Animation() {
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(TimerSlot()));
  ui->widget->clearGraphs();
  X = xBegin;
  x.clear();
  y.clear();
}

void MainWindow::StopAnimation() { timer->stop(); }

void MainWindow::if_graph_exist() {
  ui->widget->clearGraphs();
  QString input = ui->Display->text();
  char c_input[512] = {0};
  int code = OK;

  strncpy(c_input, qPrintable(input), 255);

  xBegin = ui->x_Begin->text().toDouble();
  yBegin = ui->y_Begin->text().toDouble();
  h = ui->add_h->text().toDouble();

  ui->widget->addGraph();
  QPen DotPen;
  DotPen.setWidthF(2);
  ui->widget->graph(0)->setPen(DotPen);
  ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui->widget->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssDisc, 1));

  ui->widget->graph(0)->setName("Sine envelope");

  ui->widget->xAxis->setRange(xBegin, xEnd);
  ui->widget->yAxis->setRange(yBegin, yEnd);
  ui->widget->addGraph();

  data_task_t data;
  N = (-xBegin + h - xBegin) / h + 2;

  for (X = xBegin; X < N; X += h) {
    strncpy(c_input, qPrintable(input), 255);
    init_input(&data);
    data.x = X;
    smart_calc(c_input, &data);
    code = data.code;
    if (!code) {
        x.push_back(X);
        y.push_back(data.result);
    } else {
        break;
    }
  }

  if (code) {
    ui->Display->clear();
    ui->Display->setText("Error");
  }
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();

  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
}

void MainWindow::if_graph_not_exist() {
  QString input = ui->Display->text();
  char c_input[512] = {0};
  strncpy(c_input, qPrintable(input), 255);
  int code = OK;

  X = ui->add_x->text().toDouble();
  data_task_t data;
  init_input(&data);
  data.x = X;
  smart_calc(c_input, &data);
  code = data.code;

  ui->Display->clear();
  if (!code) ui->Display->setText(QString::number(data.result, 'f', 7));
  else
    ui->Display->setText("Error");
}

void MainWindow::on_push_run_clicked() {
  flag = !flag;
  if (flag) {
    ui->push_run->setText("START");
    timer->stop();
  } else {
    if (count == 0) {
      Animation();
      count++;
    }
    ui->push_run->setText("STOP");
    timer->start(1);
  }
}

void MainWindow::on_push_stop_clicked() {
  time = 0;
  timer->stop();
  x.clear();
  y.clear();
  flag = true;
  count = 0;
  ui->widget->graph(0)->data()->clear();
  ui->widget->replot();
}

void MainWindow::clean_edit() {
  ui->every_month_edit->clear();
  ui->overpayment_edit->clear();
  ui->result_edit->clear();
}

void MainWindow::on_push_calc_clicked() {
  clean_edit();
  credit_t credit;
  init_credit(&credit);
  creditcalc(&credit, ui->sum_edit->text().toDouble(),
             ui->proz_edit->text().toDouble(),
             ui->time_year_edit->text().toInt(),
             ui->time_month_edit->text().toInt(), type);

  ui->every_month_edit->setText(QString::number(credit.overpayment, 'f', 2));
  ui->overpayment_edit->setText(
      QString::number(credit.overpayment_edit, 'f', 2));
  ui->result_edit->setText(QString::number(credit.result_edit, 'f', 2));
}

void MainWindow::on_type_an_clicked() { type = 1; }

void MainWindow::on_type_diff_clicked() { type = 2; }

void MainWindow::on_push_deposit_clicked() {
  deposit_t deposit;
  init_deposit(&deposit);
  double sum = ui->sum_deposit->text().toDouble();
  deposit.sum = sum;
  deposit.term = ui->term_deposit->text().toInt();
  QString input = ui->data_begin_term->text();

  dates_t date;
  init_deposit_dates(&date);
  char begin_of_term[15] = {0};
  strncpy(begin_of_term, qPrintable(input), 15);
  convert_dates_to_struct(&date, &begin_of_term[0]);

  deposit.capital = capital;
  deposit.interest_rate = ui->interest_rate->text().toDouble();
  deposit.tax_rate = ui->tax_rate->text().toDouble();
  deposit.type_of_term = ui->term_comboBox->currentIndex();
  deposit.frequency_of_payments = ui->frequency_of_pay->currentIndex();

  depositcalc(&deposit, &date);

  ui->deposit_sum->clear();
  ui->deposit_sum->setText(QString::number(deposit.result, 'f', 2));
  ui->tax_sum->clear();
  ui->tax_sum->setText(QString::number(deposit.result_tax, 'f', 2));
  ui->oversum->clear();
  ui->oversum->setText(QString::number(deposit.result - sum, 'f', 2));
}

void MainWindow::on_capital_clicked()
{
  flag2 = !flag2;
  if (flag2) {
    capital = 0;
  } else {
    capital = 1;
  }
}

void MainWindow::on_push_clear_2_clicked()
{
  ui->Display->clear();
  ui->Display->setText("");
}

