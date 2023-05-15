import numpy as np
import math

class value:
    def __init__(self, val):
        self.val = val
        self.child = []
        self.grad = 0
        self.op = ""

    def __add__(self, other):
        res = value(self.val + other.val)
        res.op = "+"
        res.child.append(other)
        res.child.append(self)
        return res

    def __sub__(self, other):
        res = value(self.val - other.val)
        res.op = "-"
        res.child.append(other)
        res.child.append(self)
        return res

    def __mul__(self, other):
        res = value(self.val * other.val)
        res.op = "*"
        res.child.append(other)
        res.child.append(self)
        return res

    def __truediv__(self, other):
        res = value(self.val / other.val)
        res.op = "/"
        res.child.append(other)
        res.child.append(self)
        return res

    def tanh(self):
        res = value(np.tanh(self.val))
        res.op = "tanh"
        res.child.append(self)
        return res

    def back_prop(self):
        if self.op == "":
            return
        elif self.op == "+":
            self.child[0].grad += self.grad
            self.child[1].grad += self.grad
        elif self.op == "-":
            self.child[0].grad += self.grad
            self.child[1].grad -= self.grad
        elif self.op == "*":
            self.child[0].grad += self.grad * self.child[1].val
            self.child[1].grad += self.grad * self.child[0].val
        elif self.op == "/":
            self.child[0].grad += self.grad / self.child[1].val
            self.child[1].grad -= self.grad * self.child[0].val / (self.child[1].val * self.child[1].val) 
        elif self.op == "tanh":
            self.child[0].grad += self.grad * (1 - self.val * self.val)

    def prt_exp_tree(self):
        if self.op == "":
            print(self.val, end="")
        elif self.op == "+":
            print("(", end="")
            self.child[0].prt_exp_tree()
            print(" + ", end="")
            self.child[1].prt_exp_tree()
            print(")", end="")
        elif self.op == "-":
            print("(", end="")
            self.child[0].prt_exp_tree()
            print(" - ", end="")
            self.child[1].prt_exp_tree()
            print(")", end="")
        elif self.op == "*":
            print("(", end="")
            self.child[0].prt_exp_tree()
            print(" * ", end="")
            self.child[1].prt_exp_tree()
            print(")", end="")
        elif self.op == "/":
            print("(", end="")
            self.child[0].prt_exp_tree()
            print(" / ", end="")
            self.child[1].prt_exp_tree()
            print(")", end="")
        elif self.op == "tanh":
            print("tanh(", end="")
            self.child[0].prt_exp_tree()
            print(")", end="")
        else:
            print("error")

x = value(1.0)
z = value(2.0)
y = x + value(3.0)
k = y * z
# y.prt_exp_tree()
k.grad = 1.0
k.back_prop()
z.back_prop()
y.back_prop()
x.back_prop()
print()
print(x.grad)
print(z.grad)
print(y.grad)
print(k.grad)