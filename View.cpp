#include "View.h"

void View::startEventLoop(QWidget *parent) {
    QMainWindow = parent;
    ui = new Ui::QMainWindow;
    ui->setupUi(this);
    ui->push_run->setText("START");
}

void View::displayMenu() {}

int View::performChoice() {}

void View::clicked_text_add(QString toAdd) {
    QString text = ui->Display->text();
    ui->Display->setText(text + toAdd);
}

void View::on_push_clear_clicked() {
    QString text = ui->Display->text();
    text.chop(1);
    if (text.isEmpty()) {
        text = "";
    }
    ui->Display->setText(text);
}

void View::on_push_1_clicked() { clicked_text_add("1"); }

void View::on_push_2_clicked() { clicked_text_add("2"); }

void View::on_push_3_clicked() { clicked_text_add("3"); }

void View::on_push_4_clicked() { clicked_text_add("4"); }

void View::on_push_5_clicked() { clicked_text_add("5"); }

void View::on_push_6_clicked() { clicked_text_add("6"); }

void View::on_push_7_clicked() { clicked_text_add("7"); }

void View::on_push_8_clicked() { clicked_text_add("8"); }

void View::on_push_9_clicked() { clicked_text_add("9"); }

void View::on_push_0_clicked() { clicked_text_add("0"); }

void View::on_push_plus_clicked() { clicked_text_add("+"); }

void View::on_push_minus_clicked() { clicked_text_add("-"); }

void View::on_push_mul_clicked() { clicked_text_add("*"); }

void View::on_push_div_clicked() { clicked_text_add("/"); }

void View::on_push_sin_clicked() { clicked_text_add("sin"); }

void View::on_push_cos_clicked() { clicked_text_add("cos"); }

void View::on_push_tan_clicked() { clicked_text_add("tan"); }

void View::on_push_asin_clicked() { clicked_text_add("asin"); }

void View::on_push_acos_clicked() { clicked_text_add("acos"); }

void View::on_push_atan_clicked() { clicked_text_add("atan"); }

void View::on_push_sqrt_clicked() { clicked_text_add("sqrt"); }

void View::on_push_pow_clicked() { clicked_text_add("^"); }

void View::on_push_mod_clicked() { clicked_text_add("mod"); }

void View::on_push_ln_clicked() { clicked_text_add("ln"); }

void View::on_push_right_clicked() { clicked_text_add("("); }

void View::on_push_left_clicked() { clicked_text_add(")"); }

void View::on_push_log_clicked() { clicked_text_add("log"); }

void View::on_push_X_clicked() { clicked_text_add("x"); }

void View::on_push_dot_clicked() { clicked_text_add("."); }

void View::on_push_eq_clicked() {
    ui->widget->clearGraphs();

    if (graph) {
        if_graph_exist();
    } else if (!graph) {
        if_graph_not_exist();
    }
}

void View::on_graph_clicked(bool checked) {
    if (checked)
        graph = 1;
    else
        graph = 0;
}

void View::TimerSlot() {
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

void View::Animation() {
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerSlot()));
    ui->widget->clearGraphs();
    X = xBegin;
    x.clear();
    y.clear();
}

void View::StopAnimation() { timer->stop(); }

void View::if_graph_exist() {
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

void View::if_graph_not_exist() {
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


void View::on_push_run_clicked() {
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