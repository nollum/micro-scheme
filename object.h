#include <string>
#include <vector>
#include "sexpr.h"

using namespace std;

typedef enum {VAR, PROC} Kind;

class Object {

    double (*proc_ptr)(vector<double>&);
    Kind kind;
    double value;

public:
    Object();

    Object(double &s);

    Object(double (*p)(vector<double>&));

    // Object(Procedure &proc);

    Kind get_kind();

    double get_value();

    double apply(vector<double>&args);

    double apply();

    // Sexpr get_arg_list();

    // Sexpr get_body();

    // Procedure get_proc();
};