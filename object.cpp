#include "object.h"

Object::Object() {}

Object::Object(double &s) {
    value = s;
    kind = VAR;
    proc_ptr = nullptr;
}

Object::Object(double (*p)(vector<double>&)) {
    proc_ptr = p;
    kind = PROC;
    value = 0;
}

Kind Object::get_kind() {
    return kind;
}

double Object::get_value() {
    return value;
}

double Object::apply(vector<double>&args) {
    return proc_ptr(args);
}

double Object::apply() {
    vector<double> empty_args;
    return proc_ptr(empty_args);
}

// Sexpr Object::get_arg_list() {
// }

// Sexpr Object::get_body() {
// }

