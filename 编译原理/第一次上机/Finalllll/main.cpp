#include "LexAnalysis.h"


//�����
set<string> op = {
	"+", "-", "*", "/", "=",
};

//����
set<string> border = {"(", ")", "[", "]", "{", "}"};

unordered_set<string> gSymbols; //�ķ�����
unordered_set<string> VT; //�ս��
unordered_set<string> VN; //���ս��
map<int, map<string, string>> Action; //ACTION��
map<int, map<string, string>> Goto; //GOTO��


//�ж�s�Ƿ�Ϊ�����
bool isOp(string s)
{
	if (op.count(s) == 1) return true;
	return false;
}

//�ж�s�Ƿ�Ϊ���
bool isBorder(string s)
{
	if (border.count(s) == 1) return true;
	return false;
}


//���дʷ�����
void LexAnalyse()
{
	//���������ķ�
	string in;
	ifstream ifile_reg;
	ifile_reg.open("reg.txt", ios::in);

	//���ݶ������ʽ����NFA
	FA fa = FA();
	FANode nfaend = FANode("@"); //��̬��"@"��ʾ
	fa.endSet.insert(nfaend);
	while (ifile_reg)
	{
		ifile_reg >> in;
		fa.createNFA(in);
	}

	//NFAת��ΪDFA
	FA dfa = FA();
	fa.subset(dfa);


	//����Դ���룬���з���
	ifstream ifile_code;
	ifile_code.open("code.txt", ios::in);
	string path;
	FANode start = *dfa.startSet.begin();

	//���token����
	ofstream ofile_token;
	ofile_token.open("token.txt", ios::out);

	cout << "type" << "\t\ttoken" << endl;

	while (getline(ifile_code, in))
	{
		in = in.substr(in.find_first_not_of(" "));
		FANode state = start;
		for (int i = 0; i < in.length(); i++)
		{
			char c = ex(in[i]);
			if (c == ' ')
			{
				if (dfa.endSet.count(state) == 0)
				{
					cout << "error   " << "\t" << path << endl;
					return;
				}
				else
				{
					cout << judge(state, path) << "\t" << path << endl;
					ofile_token << judge(state, path) << endl;
				}
				state = start;
				path = "";
				continue;
			}
			if (dfa.endSet.count(state) == 1)
			{
				if (dfa.Dtran[state].find(c) != dfa.Dtran[state].end())
				{
					state = dfa.Dtran[state][c];
					path += in[i];
				}
				else
				{
					cout << judge(state, path) << "\t" << path << endl;
					ofile_token << judge(state, path) << endl;
					state = start;
					path = "";
					i--;
				}
				continue;
			}

			path += in[i];
			if (dfa.Dtran[state].find(c) == dfa.Dtran[state].end())
			{
				cout << "error   " << "\t" << path << endl;
				state = start;
				path = "";
				return;
			}
			else state = dfa.Dtran[state][c];
		}

		if (dfa.endSet.count(state) == 0)
		{
			cout << "error   " << "\t" << path << endl;
			return;
		}
		else
		{
			cout << judge(state, path) << "\t" << path << endl;
			ofile_token << judge(state, path) << endl;
		}
		state = start;
		path = "";
	}
	ofile_token << "#" << endl;
}

int main()
{
	LexAnalyse();
	return 0;
}
