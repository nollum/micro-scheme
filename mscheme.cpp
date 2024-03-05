#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <unordered_map>
#include "sexpr.h"
#include "object.h"
#include "procedures.h"

using namespace std;

typedef unordered_map<string, Object> Environment;

vector<string> tokenize(string &input) {
    vector<string> tokens;
    string token = "";
    for (auto i = input.begin(); i < input.end(); i++) {
        switch (*i) {
            case '(':
            case ')':
                if (!token.empty()) {
                    tokens.push_back(token);
                    token = "";
                }
                tokens.push_back(string(1, *i));
                break;
            case ' ':
                if (!token.empty()) {
                    tokens.push_back(token);
                    token = "";
                }
                break;
            default:
                token += *i;
                break;
        }
    }
    
    return tokens;
}

shared_ptr<Sexpr> atom(const std::string& token) {
    shared_ptr<Sexpr> e = make_shared<Sexpr>();
    e->type = ATOM;
    try {
        e->atom = std::stod(token);
    } catch (const std::invalid_argument&) {
        e->atom = token;
    }
    return e;
}

shared_ptr<Sexpr> parse(vector<string> &tokens) {
    if (tokens.empty()) {
        cerr << "Unexpected EOF" << endl;
        return nullptr;
    }
    string token = tokens.front();
    tokens.erase(tokens.begin());
    shared_ptr<Sexpr> expr = make_shared<Sexpr>();
    expr->type = LIST;
    if (token == "(") {
        while (tokens.at(0) != ")")
            expr->list.push_back(parse(tokens));
        tokens.erase(tokens.begin());
        return expr; 
    } else if (token == ")") {
        cerr << "Parsing error" << endl;
        return nullptr;
    } else {
        return atom(token);
    }
}

// for debug
void print_ast(const std::shared_ptr<Sexpr>& expr) {
    if (expr->type == ATOM) {
        if (holds_alternative<string>(expr->atom))
            cout << get<string>(expr->atom);
        else 
            cout << get<double>(expr->atom);
    }
    else {
        cout << "(";
        for (size_t i = 0; i < expr->list.size(); i++) {
            print_ast(expr->list[i]);
            if (i != expr->list.size() - 1) {
                cout << " ";
            }
        }
        cout << ")";
    }
}

Object eval(Environment &env, shared_ptr<Sexpr> node) {
    
    if (node->type == ATOM && holds_alternative<string>(node->atom)) {
        return env[get<string>(node->atom)];
    } else if (node->type == ATOM && holds_alternative<double>(node->atom)) {
        return get<double>(node->atom);
    } else if (get<string>(((node->list.at(0)))->atom) == "define") {
        string symbol = get<string>((*(node->list.at(1))).atom);
        shared_ptr<Sexpr> expr = node->list[2];
        env[symbol] = eval(env, expr);
        return nullptr;
    } else if (get<string>(((node->list.at(0)))->atom) == "begin") {
        vector<double> args;
        for (int i = 1; i < node->list.size(); ++i) {
            args.push_back(eval(env, node->list[i]).get_value());
        }
        return args.back();
    } else {
        auto proc = eval(env, node->list[0]);
        vector<double> args;
        for (int i = 1; i < node->list.size(); ++i) {
            args.push_back(eval(env, node->list[i]).get_value());
        }
        double res = proc.apply(args);
        return Object(res);
    }
}

int main() {

    string input = "(begin (define r 10) (define s 22.5) (* pi (* r s)))";
    vector<string> tokens;
    tokens = tokenize(input);
    shared_ptr<Sexpr> ast = parse(tokens);
    Environment env;

    env["+"] = add;
    env["-"] = sub;
    env["*"] = mult;
    env["/"] = div;
    env["%"] = mod;
    env["=="] = equal;
    env["<"] = less_than;
    env[">"] = greater_than;
    double pi = 3.14;
    env["pi"] = Object(pi);

    Object output = eval(env, ast);
    cout << output.get_value() << endl;
    return 0; 
}