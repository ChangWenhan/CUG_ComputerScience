#include <iostream>
#include "climbHill.h"
#include "geneticAlgorithm.h"
#include <vector>
#include <time.h>
#include <string>
#include <stdlib.h>

using namespace std;
// ����N�ʺ����⣬�ʺ���ĿΪN
#define random(x) (rand()%x)  // �������������ĺ���

int N;

// ��ʼ������
void initChessboard(vector<int>& chessboard) {
    for (int i = 0; i < N; i++) {
        chessboard.push_back(i);
    }

    srand((unsigned)time(0));
    for (int row1 = 0; row1 < N; row1++) {
        int row2 = random(N);
        // ��������У���ɢ���̣�����֤�ʺ��ڲ�ͬ��
        swap(chessboard[row1], chessboard[row2]);
    }
}

// ��ӡ����
void printChessboard(vector<int>& chessboard) {
    for (int i = 0; i < N; i++) {
        int num = chessboard[i];
        for (int j = 0; j < num; j++) {
            cout << " = ";
        }
        cout << " Q ";
        for (int k = num + 1; k < N; k++) {
            cout << " = ";
        }
        cout << endl;
    }
}

// ת������string Ϊint
int stringToInt(string choose)
{
    if (choose == "1") return 1;
    if (choose == "2") return 2;
    if (choose == "3") return 3;
}

int main() {
    //�������ݽṹVector<int> �±����������ֵ������������ʾһ������
    N = 0;
    cout << "������Ҫ�����N�ʺ������Nֵ������8���ϣ�" << endl;
    cin >> N;
    cout << N << "���N�ʺ�����" << endl;
    cout << "Choose one algorithhm to solve the problem " << endl;
    cout << "1. HillClimbing Algorithm " << endl;
    cout << "2. Genetic Algorithm " << endl;
    cout << "3. quit " << endl;
    string choose;

    // ��ʼ������
    // 1. �����㷨��Ӧ��������
    vector<int> temp1_chessboard;
    vector<int> temp3_chessboard;

    // 2.ͳ��ʱ��
    clock_t startTime;
    clock_t endTime;
    double totalTime;

    // 3.����㷨�Ķ���
    climbHill sol1(N);
    geneticAlgorithm sol3(N);


    while (1) {
        cout<<"��ѡ���㷨(1~2)���˳�(3)"<<endl;
        cin >> choose;
        int num = stringToInt(choose);
        int t = 0;   // ִ���㷨�Ĵ���
        double average = 0;  // �㷨ƽ��ʱ��
        int big = 0;      // �㷨�ʱ��
        int small = 100;     // �㷨���ʱ��
        int sum = 0;          // ʱ���
        switch (num){
            case 1:
                cout << "Solution 1 --- Hill Climbing Algorithm �����������ɽ����" << endl;
                cout << "����ִ���㷨�Ĵ���" << endl;
                cin >> t;

                for (int i = 0; i < t; i++) {
                    cout << "���̳�ʼ������ӡ" << endl;
                    initChessboard(temp1_chessboard);
                    printChessboard(temp1_chessboard);
                    startTime = clock();

                    // ��ⲿ��
                    temp1_chessboard = *sol1.solve(&temp1_chessboard);

                    endTime = clock();
                    totalTime = (double)(endTime - startTime);
                    if (totalTime > big) {
                        big = totalTime;
                    }
                    if (totalTime < small) {
                        small = totalTime;
                    }
                    sum += totalTime;
                    cout << "[ " << i << "]" << " total time: " << totalTime << " ms." << endl;
                    printChessboard(temp1_chessboard);
                    cout << "-----------------------------------------------------------" << endl;
                }
                average = sum * 1.0 / t;
                cout << "average time�� " << average << " ms" << endl;
                cout << "longest time:  " << big << " ms" << endl;
                cout << "shortest time:  " << small << " ms" << endl;

                break;
            case 2:
                cout << "Solution 3 --- Genetic Algorithm���Ŵ��㷨�� " << endl;
                cout << "���̳�ʼ������ӡ" << endl;
                cout << "����ִ���㷨�Ĵ���" << endl;
                cin >> t;

                for (int i = 0; i < t; i++) {
                    initChessboard(temp3_chessboard);
                    printChessboard(temp3_chessboard);
                    startTime = clock();

                    // ��ⲿ��
                    temp3_chessboard = *sol3.solve(temp3_chessboard);

                    endTime = clock();
                    totalTime = (double)(endTime - startTime);
                    if (totalTime > big) {
                        big = totalTime;
                    }
                    if (totalTime < small) {
                        small = totalTime;
                    }
                    sum += totalTime;
                    cout << "[ " << i << "]" << " total time: " << totalTime << " ms." << endl;
                    printChessboard(temp3_chessboard);
                    cout << "-----------------------------------------------------------" << endl;
                }
                average = sum * 1.0 / t;
                cout << "average time�� " << average << " ms" << endl;
                cout << "longest time:  " << big << " ms" << endl;
                cout << "shortest time:  " << small << " ms" << endl;

                break;
            case 3:
                exit(0);
                break;
            default:
                break;
        }
    }
}
