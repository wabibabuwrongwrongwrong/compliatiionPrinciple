#include"plcode.h"
deque <char> fuhao; //临时

int  Type_now = 1;  // -1為const, 1為'var'(包括分程序名和函數名),;



void GetContent(std::string temp);
void GET_SYM_RES();
void Match_char(char a);
int WORD_ANLISIS(string tmp);
void WORD_ANLISIS_OUTPUT(int tmp);




/*-------------- 词法分析  --------------------*/

//int main() {
//    init(); // 初始化停用字符表；初始化
//    //string TEST_FILENAME = "mytestForEQ.txt"; //测试文件名
//    string TEST_FILENAME = "EROORtest.txt"; //测试文件名
//    WORD_ANLISIS(TEST_FILENAME);//分词后保存在ProSave;
//    WORD_ANLISIS_OUTPUT(0);//输出分词
//
//    //Grammar_Analysis();   //单个字符拆分保存在 WordList_After_Grammer
//    //cout << "\nresult is:" << evaluatePostfix(infixToPostfix());
//
//      // 正常跑给的5个样例
//    //for (int i = 1; i <= 5; i++) {  
//    //    string TEST_FILENAME = "testcode"+to_string(i)+".txt"; //测试文件名
//    //    WORD_ANLISIS(TEST_FILENAME);//分词后保存在ProSave;
//    //    WORD_ANLISIS_OUTPUT(i);//输出分词的ProSave
//    //    //Grammar_Analysis();   //单个字符拆分保存在 WordList_After_Grammer
//    //    //cout << "\nresult is:" << evaluatePostfix(infixToPostfix());
//    //}
//    return 0;
//}



/*-------------- 语法分析（表达式）  --------------------*/

int main() {
    init(); // 初始化停用字符表；初始化

    //string TEST_FILENAME = "mytest12.txt"; //测试文件名
    //WORD_ANLISIS(TEST_FILENAME);//分词后保存在ProSave;
    //if (CHECK_TRUE) {
    //    WORD_ANLISIS_OUTPUT(12);//输出分词
    //    int a = Grammar_Analysis();   //单个字符拆分保存在 WordList_After_Grammer
    //    if(a == 0)cout << "\nresult is:" << evaluatePostfix(infixToPostfix());
    //
    //}
    //else { cout << "Error happends"<<endl; }
    //ProSave.clear(); WordList_After_Grammer.clear();


      // 正常跑5个样例
    for (int i = 11; i <= 11; i++) {
        string TEST_FILENAME = "testcode" + to_string(i) + ".txt"; //测试文件名
        WORD_ANLISIS(TEST_FILENAME);//分词后保存在ProSave;
        if (CHECK_TRUE) {
            WORD_ANLISIS_OUTPUT(12);//输出分词
            int a = Grammar_Analysis();   //单个字符拆分保存在 WordList_After_Grammer
            if (a == 0)cout << "\nresult is:" << evaluatePostfix(infixToPostfix()) << "\n\n\n";
        }
        else { cout << "Error happends" << endl; }
        ProSave.clear(); WordList_After_Grammer.clear();
    }
    //// 跑错误的5个样例
    //for (int i = 11; i <= 15; i++) {
    //    string TEST_FILENAME = "EROORtest" + to_string(i) + ".txt"; //测试文件名
    //    WORD_ANLISIS(TEST_FILENAME);//分词后保存在ProSave;
    //    WORD_ANLISIS_OUTPUT(12);//输出分词
    //    int a = Grammar_Analysis();   //单个字符拆分保存在 WordList_After_Grammer
    //    if (a == 0)cout << "\nresult is:" << evaluatePostfix(infixToPostfix()) << "\n\n\n";
    //    ProSave.clear(); WordList_After_Grammer.clear();
    //}


    return 0;
}









void GetContent(std::string temp) {
    string a = toLower(regex_replace(temp, regex("^\\s+|\\s+$"), "")); // 去除首尾的空白字符和转成小写
    a += '@';//句子收尾
    Type_now = 1;// 默認為 'var';

    int i = 0, len = a.length();
    fuhao.clear();
    while (i < len) {
        char t = a[i];
        if (MatchIsDigitOrAlpha(t) == false) // 捕获标识符/保留字
        {
            if (t == '=' )  // 双字 运算符
            {
                if (len == 2) {
                    ProSave.push_back(make_pair("eroor_equal", "="));
                    cout << "Error, 等号起手！" << endl; CHECK_TRUE = false; return;
                } // 识别句子为:"=@"
                char tmp = a[i - 1];
                if (tmp == '<' || tmp == '>' || tmp == ':' ) {
                    string tp; tp.push_back(tmp); tp.push_back('=');
                    ProSave.pop_back();//字符返还；
                    ProSave.push_back(make_pair(Type_Double_op(tp), tp));
                    fuhao.clear();
                    i++;
                    continue;
                }
            }
            if (t == SENTENCE_END)
                if (i == len - 1) {
                    if (fuhao.empty() == false) {
                        GET_SYM_RES();// 保存標識符 或数字
                        fuhao.clear();
                    }
                    return ;// 正确跳出出口
                }
                else { cout << "error"<<endl; CHECK_TRUE = false; return ; }
            GET_SYM_RES();// 保存標識符或保留字 或数字
            fuhao.clear();

            Match_char(t);//單獨處理 界符 单字运算符 自定义暂停符
            i++;
            continue;
        }
        // 数字和字母放进fuhao
        fuhao.push_back(t);
        i++;
    }
    cout << "理论不可能跳出循环" << endl;
    CHECK_TRUE = false;
    return ;
}

void GET_SYM_RES() {
    if (fuhao.empty())return;
    int tag = 0;
    string tmp = "";
    for (int i = 0; !fuhao.empty(); i++) {
        tmp.push_back(fuhao.front());
        fuhao.pop_front();

    }

    if (Match_Sym(tmp)) {
        if (tmp == "const") Type_now = -1;
        ProSave.push_back(make_pair(type_sym(tmp), tmp));
    }
    else if(Match_number(tmp)){
        ProSave.push_back(make_pair("number", tmp));// 数字用到时再转换，先用string保留
    }else{
        //為標識符;
        //connect(tmp, Type_now);//處理變量與實際類型(函數 分程序 變量)
        if (isValidVariableName(tmp) == false) {
            cout << "Error!\n" << tmp << " is not valid, but firstly keep " << endl;
            CHECK_TRUE = false;
        }
        ProSave.push_back(make_pair("ident", tmp));            //需要考慮前面是const統領還是var統領

    }

}

int WORD_ANLISIS(string tmp) {
    ifstream PLCode(tmp);
    if (!PLCode) {
        cerr << "无法打开文件" << endl;
        CHECK_TRUE = false;
        return 1;
    }

    string line;
    while (getline(PLCode, line)) {
        GetContent(line);// ,每一行更新一次
    }

    PLCode.close();

};

void WORD_ANLISIS_OUTPUT(int tmp) {
    ofstream outfile("Out"+to_string(tmp)+".txt");
    for (const auto& pair : ProSave) {
        outfile << "(  " << pair.first << ": " << setw(3) << pair.second << "  )" << endl;
        cout << "(  " << pair.first << ": " << setw(3) << pair.second << "  )" << endl;
    }
    outfile.close();
};
//void connect(string a, int b) { return ; }