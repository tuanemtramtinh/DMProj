//
// Created by Nguyễn Tuấn Anh on 30/04/2023.
//
#include "expression_tree.h"

//- - - Xử lý chuỗi - - -//
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
//- - - Xử lý chuỗi - - -//

//- - - Truyền dữ liệu vàp cây - - -//
node * init_data(string val){
    node * tempNode = new node;
    tempNode -> data = val;
    tempNode -> left = nullptr;
    tempNode -> right = nullptr;
    return tempNode;
}

node * init_num_data(long double val){
    node * tempNode = new node;
    tempNode -> number_data = val;
    tempNode -> left = nullptr;
    tempNode -> right = nullptr;
    return tempNode;
}
//- - - Truyền dữ liệu vàp cây - - -//

//- - - Sắp xếp độ ưu tiên cho các phép tính - - -//
int getPriority(string s){
    if (s == "+" || s == "-") return 1;
    if (s == "*" || s == "/") return 2;
    if (s == "^") return 3;
    return 0; //Nếu không phải các phép toán trên thì trả về 0 hay nói cách khác là dấu '(' đó fen
}
//- - - Sắp xếp độ ưu tiên cho các phép tính - - -//

//Kiểm tra điều kiện để đẩy vào hàng chờ các đỉnh cây
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
//Kiểm tra điều kiện để đẩy vào hàng chờ các đỉnh cây

// - - - Tạo ra một đỉnh cây gồm hai bên trái và phải - - - //

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

// - - - Tạo ra một đỉnh cây gồm hai bên trái và phải - - - //

/* * * - - - Chuyển đổi biểu thức Infix thành dạng cây Binary Tree (KHÓ) ToT - - - * * */

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

/* * * - - - Chuyển đổi biểu thức Infix thành dạng cây Binary Tree (KHÓ) ToT - - - * * */

/* * * - - - Thuật toán đi Traversal để in ra các biểu thức Postfix và Prefix từ biểu thức Infix * * */
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
/* * * - - - Thuật toán đi Traversal để in ra các biểu thức Postfix và Prefix từ biểu thức Infix * * */

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


long double _process(string oper4tor, long double left, long double right){
    if (oper4tor == "+") return left + right;
    if (oper4tor == "-") return left - right;
    if (oper4tor == "*") return left * right;
    if (oper4tor == "/") return left / right;
    if (oper4tor == "^") return pow(left, right);
}

//Đệ quy Postorder Traversal để thực hiện tính toán các biểu thức Postfix và Prefix
void Calculate_process(node *x, long double &res){
    if (x == nullptr) return;
    Calculate_process(x -> left, res);
    Calculate_process(x -> right, res);
    if (x -> data == "+" || x -> data == "-" || x -> data == "*" || x -> data == "/" || x -> data == "^"){
        //s = process(x -> data, x -> left -> data, x -> right -> data);
        x -> number_data = _process(x -> data, x -> left -> number_data, x -> right -> number_data);
        res = x -> number_data;
        delete x -> left;
        delete x -> right;
        x -> left = nullptr;
        x -> right = nullptr;
    }
}
//Đệ quy Postorder Traversal để thực hiện tính toán các biểu thức Postfix và Prefix

string Calculator(tree myTree){
    string s("");
    long double res = 0;
    Calculate_process(myTree.root, res);
    ostringstream oss;
    oss << fixed << setprecision(4) << res;
    s = oss.str();
    if (res == int(res)){
        int pos = s.find('.');
        string temp = s.substr(0, pos);
        s = temp;
    }
    else{
        int i = s.size() - 1;
        while (s[i] == '0') i--;
        s.erase(i + 1, s.size() - 1 - i);
    }
    return s;
}

/*  *  * - - -  Chuyển đổi biểu thức Postfix Notation thành Binary Tree - - - * * */

string PostfixProcess(string input){
    int size = 0;
    string arr[input.size()];
    createStringArr(arr, input, size);
    stack <node*> node_stack;
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
            long double x = stod(arr[i]);
            temp = init_num_data(x);
            node_stack.push(temp);
        }
    }
    return Calculator(myTree);
}

/* * * - - -  Chuyển đổi biểu thức Postfix Notation thành Binary Tree - - - * * */

string PrefixProcess(string input){
    int size = 0;
    string arr[input.size()];
    createStringArr(arr, input, size);
    stack <node*> node_stack;
    tree myTree;
    for (int i = size - 1; i >= 0; i--){
        if (arr[i] == "+" || arr[i] == "-" || arr[i] == "*" || arr[i] == "/" || arr[i] == "^"){
            node * temp = init_data(arr[i]);
            myTree.root = temp;
            if (temp -> left == nullptr){
                temp -> left = node_stack.top();
                node_stack.pop();
            }
            if (temp -> right == nullptr){
                temp -> right = node_stack.top();
                node_stack.pop();
            }
            if (temp -> left != nullptr && temp -> right != nullptr){
                node_stack.push(temp);
            }
        }
        else{
            node * temp = new node;
            long double x = stod(arr[i]);
            temp = init_num_data(x);
            node_stack.push(temp);
        }
    }
    return Calculator(myTree);
}

string PostfixPrefixCalculator(string input){
    if (input[0] >= 48 && input[0] <= 57){
        return PostfixProcess(input);
    }
    return PrefixProcess(input);
}

void main_process(){
    string str, tempStr;
    cin >> str;
    tempStr = str;
    str = '(' + str + ')';
    string postfix, prefix;
    postfix = Infix2Postfix(str);
    prefix = Infix2Prefix(str);
    cout << "Infix: " << tempStr << endl;
    cout << "Postfix: " << postfix << endl;
    cout << "Prefix: " << prefix << endl;
    string res = PostfixPrefixCalculator(postfix);
    cout << "Result: " << res << " (Postfix)" << endl;
    res = PostfixPrefixCalculator(prefix);
    cout << "Result: " << res << " (Prefix)";

}