#include <bits/stdc++.h>
#include <queue>
#include <vector>

using namespace std;

class value {
public:
    double val;
    value(double val) : val(val) {}
    value() {}
    vector<value*> child;
    double grad = 0;
    string op = "";

    // operator overloading for +
    value operator+(value &other) {
        value res(val + other.val);
        res.op = "+";
        res.child.push_back(&other);
        res.child.push_back(this);
        return res;
    }

    value operator+(double other) {
        value res(val + other);
        res.op = "+";
        res.child.push_back(this);
        res.child.push_back(new value(other));
        return res;
    }

    // operator overloading for -
    value operator-(value &other) {
        value res(val - other.val);
        res.op = "-";
        res.child.push_back(&other);
        res.child.push_back(this);
        return res;
    }

    value operator-(double other) {
        value res(val - other);
        res.op = "-";
        res.child.push_back(this);
        res.child.push_back(new value(other));
        return res;
    }

    // operator overloading for *
    value operator*(value &other) {
        value res(val * other.val);
        res.op = "*";
        res.child.push_back(&other);
        res.child.push_back(this);
        return res;
    }

    value operator*(double other) {
        value res(val * other);
        res.op = "*";
        res.child.push_back(this);
        res.child.push_back(new value(other));
        return res;
    }

    // operator overloading for /
    value operator/(value &other) {
        value res(val / other.val);
        res.op = "/";
        res.child.push_back(&other);
        res.child.push_back(this);
        return res;
    }

    value operator/(double other) {
        value res(val / other);
        res.op = "/";
        res.child.push_back(this);
        res.child.push_back(new value(other));
        return res;
    }

    value tanh() {
        value res(std::tanh(val));
        res.op = "tanh";
        res.child.push_back(this);
        return res;
    }

    void back_prop() {
        if (op == "") {
            return;
        } else if (op == "+") {
            child[0]->grad += grad;
            child[1]->grad += grad;
        } else if (op == "-") {
            child[0]->grad += grad;
            child[1]->grad -= grad;
        } else if (op == "*") {
            child[0]->grad += grad * child[1]->val;
            child[1]->grad += grad * child[0]->val;
        } else if (op == "/") {
            child[0]->grad += grad / child[1]->val;
            child[1]->grad -= grad * child[0]->val / (child[1]->val * child[1]->val);
        } else if (op == "tanh") {
            child[0]->grad += grad * (1 - val * val);
        }
    }
};

void prt_exp_tree(value top) {
    if (top.op == "") {
        cout << top.val;
    } else if (top.op == "+") {
        cout << "(";
        prt_exp_tree(*top.child[0]);
        cout << " + ";
        prt_exp_tree(*top.child[1]);
        cout << ")";
    } else if (top.op == "-") {
        cout << "(";
        prt_exp_tree(*top.child[0]);
        cout << " - ";
        prt_exp_tree(*top.child[1]);
        cout << ")";
    } else if (top.op == "*") {
        cout << "(";
        prt_exp_tree(*top.child[0]);
        cout << " * ";
        prt_exp_tree(*top.child[1]);
        cout << ")";
    } else if (top.op == "/") {
        cout << "(";
        prt_exp_tree(*top.child[0]);
        cout << " / ";
        prt_exp_tree(*top.child[1]);
        cout << ")";
    } else if (top.op == "tanh") {
        cout << "tanh(";
        prt_exp_tree(*top.child[0]);
        cout << ")";
    }
}

int main() {
    value x(1.0);
    value y = x + 1.0;
    return 0;
}