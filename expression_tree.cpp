//
// Created by Nguyễn Tuấn Anh on 30/04/2023.
//
#include "expression_tree.h"

void createStringArr(string * arr, string str, int &size){
    int i = 0, j = 0;
    while (i <= str.size() - 1){
        if (str[i] >= 48 && str[i] <=57){
            while (str[i] >= 48 && str[i] <= 57){
                arr[j] += str[i];
                i++;
            }
            j++;
        }
        else{
            if (str[i] == ' '){
                i++;
            }
            else {
                arr[j] = str[i];
                j++;
                i++;
            }
        }
    }
    size = j;
}

node * init_data(string val){
    node * tempNode = new node;
    tempNode -> data = val;
    tempNode -> left = nullptr;
    tempNode -> right = nullptr;
    return tempNode;
}

int getPriority(string s){
    if (s == "+" || s == "-") return 1;
    if (s == "*" || s == "/") return 2;
    if (s == "^") return 3;
    return 0;
}

bool pushConditionCheck(string s, stack <string> Stack){
    if (s == "(") return true;
    if (s == "+" && getPriority(s) > getPriority(Stack.top())) return true;
    if (s == "-" && getPriority(s) > getPriority(Stack.top())) return true;
    if (s == "*" && getPriority(s) > getPriority(Stack.top())) return true;
    if (s == "/" && getPriority(s) > getPriority(Stack.top())) return true;
    if (s == "-" && getPriority(s) > getPriority(Stack.top())) return true;
    if (s == "^" && getPriority(s) > getPriority(Stack.top())) return true;
    return false;
}

void tree_create(stack <node*> &node_stack, stack <string> &operator_stack, tree &myTree, string s){
    node * x = init_data(operator_stack.top());
    operator_stack.pop();
    myTree.root = x;
    if (x -> right == nullptr){
        x -> right = node_stack.top();
        node_stack.pop();
    }
    if (x -> left == nullptr){
        x -> left = node_stack.top();
        node_stack.pop();
    }
    if (x -> left != nullptr && x -> right != nullptr){
        node_stack.push(x);
        if (s != ")") operator_stack.push(s);
        if (operator_stack.top() == "(") operator_stack.pop();
    }
}

void infix2_tree(tree &myTree, stack <node*> &node_stack, stack <string> &operator_stack, string * arr, int size){
    for (int i = 0; i < size; i++){
        if (arr[i] == "(" || arr[i] == ")" || arr[i] == "+" || arr[i] == "-" || arr[i] == "*" || arr[i] == "/" || arr[i] == "^"){
            if(operator_stack.empty()) operator_stack.push(arr[i]);
            else if (pushConditionCheck(arr[i], operator_stack)) operator_stack.push(arr[i]);
            else{
                if (i == size - 1)
                    while (!operator_stack.empty())
                        tree_create(node_stack, operator_stack, myTree, arr[i]);
                else tree_create(node_stack, operator_stack, myTree, arr[i]);
            }
        }
        else{
            node * temp;
            temp = init_data(arr[i]);
            node_stack.push(temp);
        }
    }
}

void PostfixTraversal(node * x, string &s){
    if (x == nullptr) return;
    PostfixTraversal(x -> left, s);
    PostfixTraversal(x -> right, s);
    s = s + x -> data + " ";
}

void PrefixTraversal(node * x, string &s){
    if (x == nullptr) return;
    s = s + x -> data + " ";
    PrefixTraversal(x -> left, s);
    PrefixTraversal(x -> right, s);
}

/* * * * *
ID for Traversal Binary Tree
ID = 1 : PostOrder
ID = 2 : PreOrder
* * * * */

void Traversal(tree myTree, string &s, int id){
    if (id == 1)
        PostfixTraversal(myTree.root, s);
    if (id == 2)
        PrefixTraversal(myTree.root, s);
}

string Infix2Postfix(string input){
    stack <node*> node_stack;
    stack <string> operator_stack;
    string arr[input.size()];
    int size = 0;
    tree myTree;
    createStringArr(arr, input, size);
    infix2_tree(myTree, node_stack, operator_stack, arr, size);
    string tempStr("");
    Traversal(myTree, tempStr, 1);
    string printResult(tempStr, 0, tempStr.size() - 1);
    return printResult;
}

string Infix2Prefix(string input){
    stack <node*> node_stack;
    stack <string> operator_stack;
    string arr[input.size()];
    int size = 0;
    tree myTree;
    createStringArr(arr, input, size);
    infix2_tree(myTree, node_stack, operator_stack, arr, size);
    string tempStr("");
    Traversal(myTree, tempStr, 2);
    string printResult(tempStr, 0, tempStr.size() - 1);
    return printResult;
}

string process(string oper4tor, string left, string right){
    int left_hand = 0, right_hand = 0;
    int res = 0;
    if (left.size() == 1 && left[0] >= 48 && left[0] <= 57) left_hand = left[0] - '0';
    else{
        int n = left.size() - 1;
        for (int i = 0; i <= n; i++){
            if (i != n){
                left_hand = left_hand + (left[i] - '0') * 10 * (n - i);
            }
            else left_hand = left_hand + (left[i] - '0');
        }
    }
    if (right.size() == 1 && right[0] >= 48 && right[0] <= 57) right_hand = right[0] - '0';
    else{
        int n = right.size() - 1;
        for (int i = 0; i <= n; i++){
            if (i != n){
                right_hand = right_hand + (right[0] - '0') * 10 * (n - i);
            }
            else right_hand = right_hand + (right[i] - '0');
        }
    }
    if (oper4tor == "+") res = left_hand + right_hand;
    else if (oper4tor == "-") res = left_hand - right_hand;
    else if (oper4tor == "*") res = left_hand * right_hand;
    else if (oper4tor == "/") res = left_hand / right_hand;
    string final = to_string(res);
    return final;
}

void Calculate_process(node *x, string &s){
    if (x == nullptr) return;
    Calculate_process(x -> left, s);
    Calculate_process(x -> right, s);
    if (x -> data == "+" || x -> data == "-" || x -> data == "*" || x -> data == "/" || x -> data == "^"){
        s = process(x -> data, x -> left -> data, x -> right -> data);
        delete x -> left;
        delete x -> right;
        x -> left = nullptr;
        x -> right = nullptr;
        x -> data = s;
    }
}

string Calculator(tree myTree){
    string s("");
    Calculate_process(myTree.root, s);
    return s;
}

string PostfixProcess(string input){
    int size = 0;
    string arr[input.size()];
    createStringArr(arr, input, size);
    stack <node*> node_stack;
    stack <string> number_stack;
    tree myTree;
    for (int i = 0; i < size; i++){
        if (arr[i] == "+" || arr[i] == "-" || arr[i] == "*" || arr[i] == "/" || arr[i] == "^"){
            node * temp = init_data(arr[i]);
            myTree.root = temp;
            if (temp -> right == nullptr){
                temp -> right = node_stack.top();
                node_stack.pop();
            }
            if (temp -> left == nullptr){
                temp -> left = node_stack.top();
                node_stack.pop();
            }
            if (temp -> left != nullptr && temp -> right != nullptr){
                node_stack.push(temp);
            }
        }
        else{
            node * temp = new node;
            temp = init_data(arr[i]);
            node_stack.push(temp);
        }
    }
    cout << "DONE";
    return Calculator(myTree);
}

void PrefixEvaluation(string input){
    int size = input.size();
}

string PostfixPrefixCalculator(string input){
    if (input[0] >= 48 || input[0] <= 57){
        return PostfixProcess(input);
    }
    else{

    }
}

void main_process(){
    string str, tempStr;
    /*cin >> str;
    tempStr = str;
    str = '(' + str + ')';
    string postfix, prefix;
    postfix = Infix2Postfix(str);
    prefix = Infix2Prefix(str);
    cout << "Infix: " << tempStr << endl;
    cout << "Postfix: " << postfix << endl;
    cout << "Prefix: " << prefix << endl;*/
    getline(cin, str);
    cout << PostfixPrefixCalculator(str);

}