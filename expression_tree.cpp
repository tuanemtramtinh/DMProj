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

void convert_number(string s, long double &x){
    int n = s.size() - 1;
    int find = s.find('.');
    for (int i = 0; i <= n; i++){
        if (find > 0){
            if (i < find){
                if (i != find - 1) x = x + (s[i] - '0') * pow(10, find - 1 - i);
                else x = x + (s[i] - '0');
            }
            else if (i >= find + 1){
                x = x + (s[i] - '0') * pow(10, find - i);
            }
        }
        else{
            if (i != n) x = x + (s[i] - '0') * pow(10, n - i);
            else x = x + (s[i] - '0');
        }
    }
}

string process(string oper4tor, string left, string right){
    long double left_hand = 0, right_hand = 0;
    long double res = 0;
    if (left.size() == 1 && left[0] >= 48 && left[0] <= 57) left_hand = left[0] - '0';
    else{
        int n = left.size() - 1;
        int find = left.find('.');
        if (left[0] == '-'){
            left.erase(0, 1);
            convert_number(left, left_hand);
            left_hand *= - 1;
        }
        else convert_number(left, left_hand);
    }
    if (right.size() == 1 && right[0] >= 48 && right[0] <= 57) right_hand = right[0] - '0';
    else{
        int n = right.size() - 1;
        int find = right.find('.');
        if (right[0] == '-'){
            right.erase(0, 1);
            convert_number(right, right_hand);
            right_hand *= -1;
        }
        else convert_number(right, right_hand);
    }
    if (oper4tor == "+") res = left_hand + right_hand;
    else if (oper4tor == "-") res = left_hand - right_hand;
    else if (oper4tor == "*") res = left_hand * right_hand;
    else if (oper4tor == "/") res = left_hand / right_hand;
    else if (oper4tor == "^") res = pow(left_hand, right_hand);
    //Để số sau khi chuyển đổi sang string không bị dư dấu . phẩy sau số nguyên
    /* * *
     Ví dụ 100 kiểu double nếu chuyển đổi sang string sẽ là 100.00000000 nên hàm này để ngăn không có
     các số 0 không cần thiết xuất hiện
     * * */
    /////////////////////////////////////////////////
    ostringstream oss;
    oss << fixed << res;
    string final ="";
    if (int(res) == res){
        final = oss.str();
        int find = final.find('.');
        string temp = final.substr(0, find);
        final = temp;
    }
    else{
        final = oss.str();
        /*string temp = final.substr(0, final.size() - 2);
        final = temp;*/
    }

    return final;
}

//Đệ quy Postorder Traversal để thực hiện tính toán các biểu thức Postfix và Prefix
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
//Đệ quy Postorder Traversal để thực hiện tính toán các biểu thức Postfix và Prefix

string Calculator(tree myTree){
    string s("");
    Calculate_process(myTree.root, s);
    return s;
}

/*  *  * - - -  Chuyển đổi biểu thức Postfix Notation thành Binary Tree - - - * * */

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
    return Calculator(myTree);
}

/* * * - - -  Chuyển đổi biểu thức Postfix Notation thành Binary Tree - - - * * */

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
    cin >> str;
    tempStr = str;
    str = '(' + str + ')';
    string postfix, prefix;
    postfix = Infix2Postfix(str);
    prefix = Infix2Prefix(str);
    cout << "Infix: " << tempStr << endl;
    cout << "Postfix: " << postfix << endl;
    cout << "Prefix: " << prefix << endl;
    //getline(cin, str);
    string res = PostfixPrefixCalculator(postfix);
    string temp = res.substr(0, res.size());
    cout << "Result: " << temp;

}