#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <variant>

using namespace std;

typedef enum {ATOM, LIST} ExprType;

struct Sexpr {
    ExprType type;
    variant<string, double> atom;
    vector<shared_ptr<Sexpr>> list;
};
