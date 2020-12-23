//
// Created by christan on 2020/11/5.
//

#ifndef CLIMBHILL_CLIMBHILL_H
#define CLIMBHILL_CLIMBHILL_H

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#define random(x) (rand()%x)  // �������������ĺ���

using namespace std;
class climbHill {
private:
    int N;                // ���̴�С
    int step;			  // ��¼���еĲ���
    int maxSteps;         // �ﵽ���ɨ���������δ���������
    int rowPosition;      // �ڸ���λ�ü������λ��
public:
    climbHill(int N) {
        step = 0;
        maxSteps = 10000;
        this->N = N;
        rowPosition = 0;
    }

    int rand_X(int x)
    {
        return rand()%x;
    }

    //����������ﵽһ���Ĳ�������δ�����ô�����´�������
    //�����ɶԽ��ߵĻʺ����ӣ�Ȼ������������У�
    void reset(vector<int>& chessboard) {
        chessboard.clear();
        for (int i = 0; i < N; i++) {
            chessboard.push_back(i);    //���ɶԽ�������
        }
        for (int row1 = 0; row1 < N; row1++) {
            int row2 = rand_X(N-1);
            // ��������У���ɢ���̣�����֤�ʺ��ڲ�ͬ��
            swap(chessboard[row1], chessboard[row2]);
        }
    }

    // ���㵱ǰ���̴��ڵ��໥�����Ļʺ����
    int getNumofConflicts(vector<int> *chessboard) {
        int numOfConflicts = 0;
        int width = this->N;
        for (int i = 0; i < width; i++) {
            for (int j = i + 1; j < width; j++) {
                // �����ڻʺ�λ�ڶԽ��ߵ�ʱ�� ��ͻ��+1
                if (abs(j - i) == abs((*chessboard)[i] - (*chessboard)[j])) {
                    numOfConflicts++;
                }
                // �����ڻʺ�λ��ͬһ�е�ʱ�򣬳�ͻ��+1
                if ((*chessboard)[i] == (*chessboard)[j]) {
                    numOfConflicts++;
                }
            }
        }
        return numOfConflicts;
    }

    // ����ĳһ�е�����λ��
    int chooseTheBestPosition(vector<int>* chessboard, int row) {
        // ��¼Ϊ�ƶ�֮ǰ��λ��
        int originPosition = (*chessboard)[row];
        //cout<<originPosition<<endl;
        // ��¼ÿһ��λ�ö�Ӧ������״̬����Ӧ�ĳ�ͻ��
        vector<int> conflictData;
        for (int i = 0; i < N; i++) {
            (*chessboard)[row] = i; //�в��䣬����һ�е����Ӵ�0�ƶ���N���ֱ��ȡÿ������µĳ�ͻ����
            conflictData.push_back(getNumofConflicts(chessboard));
        }

        //��¼��ͻ����С�ļ���λ�ã�Ȼ�����Ȼ��һ��λ��
        int less = 0;
        vector<int> bestPosition;
        for (int i = 0; i < N; i++) {
            if (i == 0) {
                bestPosition.push_back(0);
                less = conflictData[0];
                continue;
            }
            // �ж�iλ�ó�ͻ��С������λ��,����������洢��С��ͻ��λ��
            if (conflictData[i] < less) {
                bestPosition.clear();
                bestPosition.push_back(i);
                less = conflictData[i];
            }
                // ��ͬ����С�ĳ�ͻλ��Ҳ��ӵ�������
                // ��������ǵ�ǰ���ֵ���С��ͻλ�ú��Ѿ����ֵ���С��ͻλ�ó�ͻ����ͬ��
            else if(conflictData[i] == less) {
                bestPosition.push_back(i);
            }
        }
        //���ֻ��һ�����λ�ã��Ǿ���������λ��
        if (bestPosition.size() == 1)
            return bestPosition[0];

        // ���λ���ж���������ɸѡ
        srand((unsigned)time(0));
        return bestPosition[rand() % bestPosition.size()];
    }


    int moveToTheBestPlace(vector<int>* chessboard, int row)
    {
        // ��¼Ϊ�ƶ�֮ǰ��λ��
        int originPosition = (*chessboard)[row];
        int newPosition;
        int originConflicts = getNumofConflicts(chessboard);;
        int numOfConflicts,index;

        if((*chessboard)[row]<N-1){
            //cout<<"first"<<(*chessboard)[row]<<endl;
            (*chessboard)[row]++;
            //cout<<"down"<<(*chessboard)[row]<<endl;
            index = (*chessboard)[row];
            numOfConflicts = getNumofConflicts(chessboard);

            (*chessboard)[row]--;
            //cout<<"back"<<(*chessboard)[row]<<endl;
        }
        else if((*chessboard)[row]==N-1){
            //cout<<"first"<<(*chessboard)[row]<<endl;
            (*chessboard)[row]--;
            //cout<<"up"<<(*chessboard)[row]<<endl;
            index = (*chessboard)[row];
            numOfConflicts = getNumofConflicts(chessboard);

            (*chessboard)[row]++;
            //cout<<"back"<<(*chessboard)[row]<<endl;
        }

        if(originConflicts <= numOfConflicts){
            newPosition = originPosition;
            //cout<<"return "<<newPosition<<endl;
        }
        else if(originConflicts > numOfConflicts){
            newPosition = index;
            //cout<<"return "<<newPosition<<endl;
        }
        return newPosition;

    }

    void printboard(vector<int>& chessboard) {
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



    // ÿ��ѡ������λ��
    vector<int>* scanChessboard(vector<int>* chessboard, int row){
        (*chessboard)[row] = moveToTheBestPlace(chessboard,row);
        return chessboard;
    }

    // ��⣬������Ѱ״̬���õ������ֱ����ͻ��Ϊ0
    vector<int>* solve(vector<int> *chessboard) {
        // �������
        srand(time(NULL));
        int resetTime = 0;  // ��������
        step = 0;   // ͳ�����в���
        // ����ͻ��Ϊ0ʱ��ֹ��ɽ
        cout<<"������"<<endl;
        while (getNumofConflicts(chessboard) > 0) {
            if (step >= maxSteps) {
                cout<<step<<endl;
                reset(*chessboard);
                resetTime++;
                step = 0;
                printboard(*chessboard);
                //cout << "�������" << endl;
            }
            // ��rowPostion�еĻʺ��Ƶ�ͬһ�е�����λ��
            chessboard = scanChessboard(chessboard,rowPosition++);
            // �ж�rowPosition�Ƿ���㣬��ֹԽ��
            rowPosition = rowPosition >= N ? rowPosition % N : rowPosition;
            step++;
        }
        cout << "Solved the problem, totally " << step << " steps. Including "<< resetTime<< " reset times."  << endl;
        return chessboard;
    }

};

#endif //CLIMBHILL_CLIMBHILL_H
