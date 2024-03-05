#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

double add(vector<double>&args) {
    if (args.size() == 0) {
        cerr << "Incorrect number of arguments";
        return 0;
    }
    double sum = args[0];
    for (int i = 1; i < args.size(); i++) {
        sum += args[i];
    }
    return sum;
}

double sub(vector<double>&args) {
    if (args.size() == 0) {
        cerr << "Incorrect number of arguments";
        return 0;
    }
    double sum = args[0];
    for (int i = 1; i < args.size(); i++) {
        sum -= args[i];
    }
    return sum;
}


double mult(vector<double>&args) {
    if (args.size() == 0) {
        cerr << "Incorrect number of arguments";
        return 0;
    }
    double prod = args[0];
    for (int i = 1; i < args.size(); i++) {
        prod *= args[i];
    }
    return prod; 
}

double div(vector<double>&args) {
    if (args.size() == 0) {
        cerr << "Incorrect number of arguments";
        return 0;
    }
    double quot = args[0];
    for (int i = 1; i < args.size(); i++) {
        quot /= args[i];
    }
    return quot; 
}

double mod(vector<double>&args) {
    if (args.size() == 0) {
        cerr << "Incorrect number of arguments";
        return 0;
    }
    double res = args[0];
    for (int i = 1; i < args.size(); i++) {
        res = fmod(res, args[i]);
    }
    return res; 
}

double equal(vector<double>&args) {
    if (args.size() == 1) return true;
    for (int i = 0; i < args.size() - 1; i++) {
        if (args[i] != args[i+1]) {
            return false;
        }
    }
    return true;
}

double less_than(vector<double>&args) {
    if (args.size() == 1) return true;
    for (int i = 0; i < args.size() - 1; i++) {
        if (args[i] >= args[i+1]) {
            return false;
        }
    }
    return true;
}

double greater_than(vector<double>&args) {
    if (args.size() == 1) return true;
    for (int i = 0; i < args.size() - 1; i++) {
        if (args[i] <= args[i+1]) {
            return false;
        }
    }
    return true;
}

