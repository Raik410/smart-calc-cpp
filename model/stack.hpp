#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <memory>

enum class Type {
    NUMBER = 1, X, PLUS, MINUS, MUL, DIV, POW, MOD,
    COS, SIN, TAN, ACOS, ASIN, ATAN, SQRT, LN, LOG, UNARY_MINUS,
    LEFT_BRACKET, RIGHT_BRACKET
};

enum class Priority {
    BRACKET = 0, NUM = 1, LOW = 10, MID = 100, UNARY = 99, HIGH = 1000
};

class Node {
public:

    Node() = default;
    ~Node() = default;

    double data;
    Type type;
    Priority priority;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;

    Node(double d, Type t, Priority p) : data(d), type(t), priority(p) {}
};


class Stack {
public:
    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;

    Stack() : head(nullptr), tail(nullptr) {}
     ~Stack() = default;

    void push_left(double data, Type type, Priority priority);
    void push_right(double data, Type type, Priority priority);
    std::shared_ptr<Node> pop_head();
    std::shared_ptr<Node> pop_tail();
    std::shared_ptr<Node> peek_left() const;
    std::shared_ptr<Node> peek_right() const;
    void clear_stack();
    bool isEmpty() const;
    void printStack() const;
};

#endif  // STACK_HPP