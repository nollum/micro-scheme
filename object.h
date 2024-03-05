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

    Kind get_kind();

    double get_value();

    double apply(vector<double>&args);

    double apply();

};