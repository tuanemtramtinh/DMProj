//
// Created by Nguyễn Tuấn Anh on 30/04/2023.
//

#ifndef DISCRETEMATHPROJ_EXPRESSION_TREE_H
#define DISCRETEMATHPROJ_EXPRESSION_TREE_H

#include <iostream>
#include <math.h>
#include <string>
#include <stack>
#include <vector>
using namespace std;

struct node {
    string data;
    node * left;
    node * right;
};

struct tree{
    node * root;
};

/* * * Normal Notiation * * */

node * init_data(string val);
int getPriority(string s);
void createStringArr(string * arr, string str, int & size);
bool pushConditionCheck(string s, stack <string> Stack);
void tree_create(stack <node*> &node_stack, stack <string> &operator_stack, tree &myTree, string s);
void infix2_tree(tree &myTree, stack <node*> &node_stack, stack <string> &operator_stack, string * arr, int size);

/* * * Thực hiện các phép toán + - * / ^ * * */
string process();
void Calculate_process(node * x, string &s);
string Calculator(tree myTree, int id);
string PostfixProcess(string input);
string PostfixPrefixCalculator(string input);
/* * * Thực hiện các phép toán + - * / ^ * * */

/* * * Thực hiện đổi từ Infix Notation sang Các loaị Prefix and Postfix * * */
void PostfixTraversal(node * x, string &s);
void PrefixTraversal(node * x, string &s);
void Traversal(tree myTree, string &s, int id);
string Infix2Postfix(string input);
string Infix2Prefix(string input);
/* * * Thực hiện đổi từ Infix Notation sang Các loaị Prefix and Postfix * * */

void main_process();

/* * * Normal Notiation * * */

/* * * Logic Notation * * */

/* * * Logic Notation * * */

#endif //DISCRETEMATHPROJ_EXPRESSION_TREE_H
