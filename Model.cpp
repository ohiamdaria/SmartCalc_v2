#include "Model.h"

void Model::get_data() { return data_; }

void Model::set_data(QString *input, double X, int need_graph) {
    strncpy(this->input_data.c_input, qPrintable(input), 255);
    this->input_data.X = X;
    return data_;
}

void Model::calculate() {
    output->x = X;
    smart_calc(this->input_data, this->output_data);
}

