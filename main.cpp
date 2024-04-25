#include"plcode.h"
deque <char> fuhao; //��ʱ

int  Type_now = 1;  // -1��const, 1��'var'(�����ֳ������ͺ�����),;



void GetContent(std::string temp);
void GET_SYM_RES();
void Match_char(char a);
int WORD_ANLISIS(string tmp);
void WORD_ANLISIS_OUTPUT(int tmp);




/*-------------- �ʷ�����  --------------------*/

//int main() {
//    init(); // ��ʼ��ͣ���ַ�����ʼ��
//    //string TEST_FILENAME = "mytestForEQ.txt"; //�����ļ���
//    string TEST_FILENAME = "EROORtest.txt"; //�����ļ���
//    WORD_ANLISIS(TEST_FILENAME);//�ִʺ󱣴���ProSave;
//    WORD_ANLISIS_OUTPUT(0);//����ִ�
//
//    //Grammar_Analysis();   //�����ַ���ֱ����� WordList_After_Grammer
//    //cout << "\nresult is:" << evaluatePostfix(infixToPostfix());
//
//      // �����ܸ���5������
//    //for (int i = 1; i <= 5; i++) {  
//    //    string TEST_FILENAME = "testcode"+to_string(i)+".txt"; //�����ļ���
//    //    WORD_ANLISIS(TEST_FILENAME);//�ִʺ󱣴���ProSave;
//    //    WORD_ANLISIS_OUTPUT(i);//����ִʵ�ProSave
//    //    //Grammar_Analysis();   //�����ַ���ֱ����� WordList_After_Grammer
//    //    //cout << "\nresult is:" << evaluatePostfix(infixToPostfix());
//    //}
//    return 0;
//}



/*-------------- �﷨���������ʽ��  --------------------*/

int main() {
    init(); // ��ʼ��ͣ���ַ�����ʼ��

    //string TEST_FILENAME = "mytest12.txt"; //�����ļ���
    //WORD_ANLISIS(TEST_FILENAME);//�ִʺ󱣴���ProSave;
    //if (CHECK_TRUE) {
    //    WORD_ANLISIS_OUTPUT(12);//����ִ�
    //    int a = Grammar_Analysis();   //�����ַ���ֱ����� WordList_After_Grammer
    //    if(a == 0)cout << "\nresult is:" << evaluatePostfix(infixToPostfix());
    //
    //}
    //else { cout << "Error happends"<<endl; }
    //ProSave.clear(); WordList_After_Grammer.clear();


      // ������5������
    for (int i = 11; i <= 11; i++) {
        string TEST_FILENAME = "testcode" + to_string(i) + ".txt"; //�����ļ���
        WORD_ANLISIS(TEST_FILENAME);//�ִʺ󱣴���ProSave;
        if (CHECK_TRUE) {
            WORD_ANLISIS_OUTPUT(12);//����ִ�
            int a = Grammar_Analysis();   //�����ַ���ֱ����� WordList_After_Grammer
            if (a == 0)cout << "\nresult is:" << evaluatePostfix(infixToPostfix()) << "\n\n\n";
        }
        else { cout << "Error happends" << endl; }
        ProSave.clear(); WordList_After_Grammer.clear();
    }
    //// �ܴ����5������
    //for (int i = 11; i <= 15; i++) {
    //    string TEST_FILENAME = "EROORtest" + to_string(i) + ".txt"; //�����ļ���
    //    WORD_ANLISIS(TEST_FILENAME);//�ִʺ󱣴���ProSave;
    //    WORD_ANLISIS_OUTPUT(12);//����ִ�
    //    int a = Grammar_Analysis();   //�����ַ���ֱ����� WordList_After_Grammer
    //    if (a == 0)cout << "\nresult is:" << evaluatePostfix(infixToPostfix()) << "\n\n\n";
    //    ProSave.clear(); WordList_After_Grammer.clear();
    //}


    return 0;
}









void GetContent(std::string temp) {
    string a = toLower(regex_replace(temp, regex("^\\s+|\\s+$"), "")); // ȥ����β�Ŀհ��ַ���ת��Сд
    a += '@';//������β
    Type_now = 1;// Ĭ�J�� 'var';

    int i = 0, len = a.length();
    fuhao.clear();
    while (i < len) {
        char t = a[i];
        if (MatchIsDigitOrAlpha(t) == false) // �����ʶ��/������
        {
            if (t == '=' )  // ˫�� �����
            {
                if (len == 2) {
                    ProSave.push_back(make_pair("eroor_equal", "="));
                    cout << "Error, �Ⱥ����֣�" << endl; CHECK_TRUE = false; return;
                } // ʶ�����Ϊ:"=@"
                char tmp = a[i - 1];
                if (tmp == '<' || tmp == '>' || tmp == ':' ) {
                    string tp; tp.push_back(tmp); tp.push_back('=');
                    ProSave.pop_back();//�ַ�������
                    ProSave.push_back(make_pair(Type_Double_op(tp), tp));
                    fuhao.clear();
                    i++;
                    continue;
                }
            }
            if (t == SENTENCE_END)
                if (i == len - 1) {
                    if (fuhao.empty() == false) {
                        GET_SYM_RES();// ������R�� ������
                        fuhao.clear();
                    }
                    return ;// ��ȷ��������
                }
                else { cout << "error"<<endl; CHECK_TRUE = false; return ; }
            GET_SYM_RES();// ������R�������� ������
            fuhao.clear();

            Match_char(t);//�Ϊ�̎�� ��� ��������� �Զ�����ͣ��
            i++;
            continue;
        }
        // ���ֺ���ĸ�Ž�fuhao
        fuhao.push_back(t);
        i++;
    }
    cout << "���۲���������ѭ��" << endl;
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
        ProSave.push_back(make_pair("number", tmp));// �����õ�ʱ��ת��������string����
    }else{
        //����R��;
        //connect(tmp, Type_now);//̎��׃���c���H���(���� �ֳ��� ׃��)
        if (isValidVariableName(tmp) == false) {
            cout << "Error!\n" << tmp << " is not valid, but firstly keep " << endl;
            CHECK_TRUE = false;
        }
        ProSave.push_back(make_pair("ident", tmp));            //��Ҫ���]ǰ����const�y�I߀��var�y�I

    }

}

int WORD_ANLISIS(string tmp) {
    ifstream PLCode(tmp);
    if (!PLCode) {
        cerr << "�޷����ļ�" << endl;
        CHECK_TRUE = false;
        return 1;
    }

    string line;
    while (getline(PLCode, line)) {
        GetContent(line);// ,ÿһ�и���һ��
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