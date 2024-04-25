#pragma warning(disable:4996)
#include<bits/stdc++.h>
#include<regex>
#include <unordered_map>

using namespace std;
/*-------ȫ�ֱ���ͳ��--------*/
deque<pair<string, string> > ProSave;
//  <˵����λ, �洢��> �ܿس���洢
bool CHECK_TRUE = true;//�������






/*-----------------------------------------
��ź��ں�������ͷ
------------------------------------*/
void init_terminal();

/* ��ź��ڱ��� */
deque<string > WordList_After_Grammer;  // �洢���ʽ�����磺 �� number ��      ��string������char�ǰ�number��ident����һ��



vector<char> alpha_and_int; // ���ֺ���ĸ
// ���屣���ּ���
const set<string> keywords = { "begin","call", "const", "do",
    "else", "end", "if", "odd", "procedure","program",
    "read","repeat", "then","until", "var", "while", "write" };

// �������������
const set<string> algorithm_opertor = { "+", "-", "*", "/" };

const set<string> compare_opertor = { ":=", "=", "<", "<=", ">", ">=" };

// �������ļ���
const set<string> delimiters = { "(", ")", ",", ";" ,"." };

// �Զ��x��ͣ��
const char SENTENCE_END = '@';
const string DICTIONARY_END = "&";


string toLower(string str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

void init_alpha_and_int() {
    for(char i='0'; i<='9';i++)
        alpha_and_int.push_back(i);
    for (char i = 'a'; i <= 'z'; i++)
        alpha_and_int.push_back(i);
}

void init() {
    init_alpha_and_int();
    init_terminal();
}


/*-----------------------------------------------------����ʶ��------------------------------------------------------*/

//�����жϺ���
bool MatchIsDigitOrAlpha(char a) {
    return find(alpha_and_int.begin(), alpha_and_int.end(), a) != alpha_and_int.end();
    //�ҵ����ֻ���ĸ�t��߅ ֵ����,����true;
}

bool Match_Sym(string t) {
    return find(keywords.begin(), keywords.end(), t) != keywords.end();
}

bool Match_number(string a) {
    if (a.length() == 0) return false;
    for (auto ch : a)//ch����ȡ����a������ַ�,ֱ��ȡ��Ϊֹ
    {
        if (ch < '0' || ch>'9') return false;
    }
    return true;

}

bool isValidVariableName(const string& variableName) {
    return regex_match(variableName, regex("^[a-z][a-z0-9]*$"));
}

string type_sym(string a) {
    return "SYM_" + a;
}

string type_value_const() {
    return " ";
}

string Type_Double_op(string a) {
    if (a == ">=") return "Gt or eq";
    if (a == "<=") return "Lt or eq";
    if (a == ":=") return "Define as";
    return "Error";
}

void Match_char(char a) {
    string tmp; tmp.push_back(a);
    if (a == '+') {
        ProSave.push_back(make_pair("plus", tmp));
    }
    else if (a == '-') {
        ProSave.push_back(make_pair("minus", tmp));
    }
    else if (a == '*') {
        ProSave.push_back(make_pair("multiple", tmp));
    }
    else if (a == '/') {
        ProSave.push_back(make_pair("divide", tmp));
    }
    else if (a == '=') {
        ProSave.push_back(make_pair("equal", tmp));
    }
    else if (a == '<') {
        ProSave.push_back(make_pair("less", tmp));
    }
    else if (a == '>') {
        ProSave.push_back(make_pair("greater", tmp));
    }
    else if (a == '(') {
        ProSave.push_back(make_pair("Lparen", tmp));
    }
    else if (a == ')') {
        ProSave.push_back(make_pair("Rparen", tmp));
    }
    else if (a == ',') {
        ProSave.push_back(make_pair("comma", tmp));
    }
    else if (a == ';') {
        ProSave.push_back(make_pair("semicolon", tmp));
    }
    else if (a == '.') {
        ProSave.push_back(make_pair("period", tmp));
    }
    else if (a == '#') {
        ProSave.push_back(make_pair("not equal", tmp));
    }
    else if (a == ':') {
        ProSave.push_back(make_pair("error_single_colon", tmp));
    }
    else if (a == SENTENCE_END || a == ' ') {
        ;
    }
    else {
        ProSave.push_back(make_pair("ERROR_UNDIFIEND", tmp));
    }
}

/*---- ��׺��ֵ -----*/
// �ж��ַ��Ƿ�Ϊ�����
bool isOperator(string c) {
    return c == "+"  || c == "-" || c == "*" || c == "/";
}

// ��ȡ����������ȼ�
int getPriority(string op) {
    if (op == "+" || op == "-") {
        return 1;
    }
    else if (op == "*" || op == "/") {
        return 2;
    }
    return 0; // �������ȼ���ߣ�������Ҫ����ֵ����Ϊ���Ų������˺���
}

bool IsNumber(string tmp) {
    for (char a : tmp) {
        if (a > '9' || a < '0') {
            return false;
        }
    }return true;
}
// ��׺���ʽת��Ϊ��׺���ʽ
vector<string> infixToPostfix( ) {

    stack<string> s;
    vector<string> postfix ;
    unordered_map<char, int> priority = {
        {'+', 1}, {'-', 1},
        {'*', 2}, {'/', 2}
    };

    for (string c : WordList_After_Grammer) {
        if (IsNumber(c)) {
            postfix.push_back(c);
        }
        else if (c == "(") {
            s.push(c);
        }
        else if (c == ")") {
            while (!s.empty() && s.top() != "(") {
                postfix.push_back( s.top());
                s.pop();
            }
            s.pop(); // ����������
        }
        else if (isOperator(c)) {
            while (!s.empty() && getPriority(s.top()) >= getPriority(c)) {
                postfix.push_back(s.top());
                s.pop();
            }
            s.push(c);
        }
    }

    while (!s.empty()) {
        postfix.push_back(s.top());
        s.pop();
    }

    return postfix;
}

// �����׺���ʽ
int evaluatePostfix(vector<string>postfix) {
    stack<int> s;
    int tmp;
    for (string c : postfix) {
        tmp = 0;
        if (IsNumber(c)) {
            for (char a : c) {
                tmp = tmp * 10 + (a - '0');
            }
            s.push(tmp); // ���ַ�ת��Ϊ��Ӧ������ֵ
        }
        else if (isOperator(c)) {
            int operand2 = s.top();
            s.pop();
            int operand1 = s.top();
            s.pop();
            switch (c[0]) {
            case '+':
                s.push(operand1 + operand2);
                break;
            case '-':
                s.push(operand1 - operand2);
                break;
            case '*':
                s.push(operand1 * operand2);
                break;
            case '/':
                if (operand2 == 0) {
                    cout << "Error! dividing ZERO!" << endl;
                    return 0;
                }
                s.push(operand1 / operand2);
                break;
            }
        }
    }

    return s.top();
}
/*---- ��׺��ֵ -----*/




/*------�A�y������--------*/
string EPSILON = "EPSILON";

unordered_map<string, unordered_map<string, string> > predict_table = {
        {"S", {
            {"ident", "IB"},
            {"number", "IB"},
            {"Lparen", "IB"},
            {"plus", "AIB"},
            {"minus", "AIB"},
        }},
        {"I", {
            {"ident", "EC"},
            {"number", "EC"},
            {"Lparen", "EC"}
        }},
        {"E", {
            {"ident", "ident"},  
            {"number", "number"}, 
            {"Lparen", "(S)"},
        }},
        {"B", {
            {"plus", "AIB"},
            {"minus", "AIB"},
            {"Rparen", EPSILON},
            {DICTIONARY_END, EPSILON}
        }},
        {"C", {
            {"multiple", "MEC"},
            {"divide", "MEC"},
            {"Rparen", EPSILON},
            {"plus", EPSILON},
            {"minus", EPSILON},
            {DICTIONARY_END, EPSILON}
        }},
        {"A", {
            {"plus", "+"},
            {"minus", "-"},
        }},
        {"M", {
            {"multiple", "*"},
            {"divide", "/"},
        }},

};

/*-----------------------------------------�﷨����-----------------------------------------*/
// ʹ���Զ����µ�Ԥ��������б���


set<string> TERMINAL; // ��ʼ����init����
void init_terminal() {
    TERMINAL.insert(algorithm_opertor.begin(), algorithm_opertor.end());
    TERMINAL.insert(compare_opertor.begin(), compare_opertor.end());
    TERMINAL.insert(delimiters.begin(), delimiters.end());
    TERMINAL.insert(keywords.begin(), keywords.end());
    TERMINAL.insert(DICTIONARY_END);
};
bool BelongToTerminal(string a) { // ʶ��˫���ս���������˺����жϣ�
    return ( a == "number"|| a== "ident") || (find(TERMINAL.begin(), TERMINAL.end(), a) != TERMINAL.end());
}

// ��ȡ����������ʶ���ķ���ֵ
string Get_Value(pair<string,string> tmp) {
    if (tmp.second == "a") return "1";
    else if (tmp.second == "b")return "2";
    else if (tmp.second == "c") return "3";
    return "999";
}

void print_dict() {
    for (string t: WordList_After_Grammer) {
        cout << t << "  ";
    }
}

int Grammar_Analysis() {
    /*---------------------------------*/
    stack<pair<string, string> > GrammarList;
    GrammarList.push(make_pair(DICTIONARY_END,DICTIONARY_END ));
    for (auto it = ProSave.rbegin(); it != ProSave.rend(); ++it) {
        GrammarList.push(*it);
    }// ��β�����뵽GrammarList��
    stack<string> symbolStack;
    symbolStack.push(DICTIONARY_END);  // ��ʼ��ѹ���ĩ����ѹ����������S
    symbolStack.push("S");
    string symbol;
    pair<string, string> tmp ;
 

    while (!symbolStack.empty()) {
        symbol = symbolStack.top();
        symbolStack.pop(); 
        if (GrammarList.empty() == true)
            ;
        else
            tmp =  GrammarList.top();
        if (BelongToTerminal(symbol)) { // ̎��K�Y��
            if (symbol == DICTIONARY_END) {
                GrammarList.pop();
            }else if (tmp.first == "number" || symbol == tmp.second) {
                WordList_After_Grammer.push_back(tmp.second);  // �������
                GrammarList.pop();
            }else if (tmp.first == "ident") {
                WordList_After_Grammer.push_back(Get_Value(tmp));
                GrammarList.pop();
            }else {
                cout << "Error: �Ǳ��_ʽ�K�Y��\n";
                return -1;
            }
        }
        else if (tmp.first != "ERROR_UNDIFIEND") {//���ս��
            string entry = predict_table[symbol][tmp.first];

            if (entry == "AIB" && symbol=="S") { WordList_After_Grammer.push_back("0"); }// ��������ʽ


            if (entry == EPSILON) {//Ϊ���ַ�
                continue;
            }else if (entry == "") {
                cout << "Error: �A�y��δ���x\nNow Searching [ " << symbol << "  ][ " << tmp.first << " ],matching char is " << tmp.second << endl;
                return -1;
            }// �����ǵ�һ�㻹�ǵڶ��㣬�±겻�����򷵻ؿմ���
            if (entry == "ident" || entry == "number") {
                symbolStack.push(entry);
            }else {
                // ������ʽ�Ҳ��������ѹջ����ʱ�����Ƿ��ս�������ս�� ��λ����ʱΪ�����ַ�
                for (int i = entry.size() - 1; i >= 0; --i) {
                    symbolStack.push(string(1, entry[i]));
                }
            }
        }
        else {
            cout << "Error: ���F�Ǳ��_ʽ�����\n";
            return -1;
        }


    }

    if ( GrammarList.empty()) {
        cout << "Input accepted ���ϱ��ʽҪ��\n";
        print_dict();
        cout << "ʶ����ʽΪ��";
        for (const auto& pair : ProSave) {
            cout << pair.second << "    ";
        }cout << "\n\n";
        return 0;
    }
    else {
        cout << "Input rejected\n\n\n";
        return -1;
    }

}


//int Grammar_Analysis() {
//    /*---------------------------------*/
//    vector<pair<string, string> > GrammarList;
//    for (pair<string, string> a : ProSave) {
//        GrammarList.push_back(a);
//    }
//    stack<string> symbolStack;
//    symbolStack.push(DICTIONARY_END);  // ��ʼ��ѹ���ĩ����ѹ����������S
//    symbolStack.push( "S");
//    size_t position = 0;
//
//    while (!symbolStack.empty()) {
//        string symbol = symbolStack.top();
//        pair<string, string > tmp = GrammarList[position];
//        symbolStack.pop();
//        cout << symbol << endl;
//        if (BelongToTerminal(symbol)) { // ̎��K�Y��
//            if (symbol == tmp.second) {
//                WordList_After_Grammer.push_back(tmp.second);  // �������
//                ++position;
//            }
//            else if (tmp.first == "number") {
//                WordList_After_Grammer.push_back(tmp.second); // �����Ӧ�����֣�string��
//                ++position;
//            }
//            else if (tmp.first == "ident") {
//                WordList_After_Grammer.push_back(Get_Value(tmp));
//                ++position;
//            }
//            else {
//                cout << "Error: Unexpected terminal symbol\n";
//                return 1;
//            }
//        }
//        else if (tmp.first == "error_single_colon") {
//            cout << "ð�ź��޵Ⱥ�" << endl;
//            return -1;
//        }
//        else if (tmp.first != "ERROR_UNDIFIEND") {//���ս��
//            string entry = predict_table[symbol][tmp.first];
//            if (entry == "") {// �����ǵ�һ�㻹�ǵڶ��㣬�±겻�����򷵻ؿմ���
//                cout << "Error: No production found in parsing table\n";
//                return -1;
//            }
//            else if (entry == "EPSILON") {//Ϊ���ַ�
//                continue;
//            }
//
//            // ������ʽ�Ҳ��������ѹջ����ʱ�����Ƿ��ս�������ս�� ��λ����ʱΪ�����ַ�
//            for (int i = entry.size() - 1; i >= 0; --i) {
//                symbolStack.push(string(1, entry[i]));
//            }
//            
//        }
//        else {
//            cout << "Error: Invalid symbol type\n";
//            return -1;
//        }
//    }
//
//    if (position == GrammarList.size( )) {
//        cout << "Input accepted\n";
//        print_dict();
//    }
//    else {
//        cout << "Input rejected\n";
//    }
//
//
//    //������չENBF���ڷ��ս��Ϊ˫�ַ��Ŀ���
//
//
//    return 0;
//}
//int Grammar_Analysis( ) {
//    /*-----------------��ʼ������----------------*/
//    vector<pair<string, string> > GrammarList;
//    for (pair<string, string> a : ProSave) {
//        GrammarList.push_back(a);
//    }
//    stack<pair<string, string> > symbolStack;
//    symbolStack.push({ "END", DICTIONARY_END});  // ��ʼ��ѹ���ĩ����ѹ����������S
//    symbolStack.push({ "S","FIRST" });
//    size_t position = 0;
//
//    while (!symbolStack.empty()) {
//        pair<string, string> symbol = symbolStack.top();
//        symbolStack.pop();
//        if ( BelongToTerminal(symbol.first) ) { // ̎��K�Y��
//            if (symbol.second == GrammarList[position].second) {
//                ++position;
//            }
//            else {
//                cout << "Error: Unexpected terminal symbol\n";
//                return 1;
//            }
//        }else if (symbol.first == "error_single_colon") {
//            cout << "ð�ź��޵Ⱥ�" << endl;
//            return -1;
//        }
//        else if (symbol.first != "ERROR_UNDIFIEND") {
//            string entry = predict_table[symbol.first][GrammarList[position].first];
//            if (entry == "") {// �����ǵ�һ�㻹�ǵڶ��㣬�±겻�����򷵻ؿմ���
//                cout << "Error: No production found in parsing table\n";
//                return -1;
//            }
//            else if (entry == "EPSILON") {//Ϊ���ַ�
//                continue;
//            }
//            else {
//                // ������ʽ�Ҳ��������ѹջ
//                for (int i = entry.size() - 1; i >= 0; --i) {
//                    if (entry[i] <= 'Z' && entry[i] >= 'A')
//                        symbolStack.push(make_pair("UNTerminal", string(1, entry[i])));
//                    else
//                        symbolStack.push(make_pair(" ", string(1, entry[i]));
//                }
//            }
//        }
//        else {
//            cout << "Error: Invalid symbol type\n";
//            return -1;
//        }
//    }
//
//    if (position == GrammarList.size()) {
//        cout << "Input accepted\n";
//    }
//    else {
//        cout << "Input rejected\n";
//    }
//
//
//    //���ڷ��ս��Ϊ˫�ַ��Ŀ���
//
//
//    return 0;
//}