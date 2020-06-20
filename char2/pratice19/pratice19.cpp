#include <iostream>
#include <vector>
#include<math.h>

using namespace std;

// 矩阵都为方阵
vector<vector<float>> miniorMatrix(vector<vector<float>> M, int col, int row) {
    int n = M.size();
    if (n <= 1) {
        vector<vector<float>>empty;
        return empty;
    }
    vector<vector<float>> subMat(n - 1, vector<float>(n - 1, 0.0f));
    int subI = 0;
    for (int i = 0; i < n; ++i) {
        if (i == col) continue;
        int subJ = 0;
        for (int j = 0; j < n; ++j) {
            if (j == row) continue;
            subMat[subI][subJ] = M[i][j];
            subJ++;
        }
        subI++;
    }
    return subMat;
}

// 使用高斯消元法更高效
float determinant(vector<vector<float>> M) {
    int n = M.size();
    float det = 0.0f;
    if (n == 1) {
        return M[0][0];
    } else {
        // 创建余子阵
        // vector<vector<float>> subMat(n - 1, vector<float>(n - 1, 0.0f));
        for (int i = 0; i < n; ++i) {
            // 空间优化，不用每次创建新数组
            vector<vector<float>> subMat = miniorMatrix(M, 0, i);
            det += pow(-1, i) * M[0][i] * determinant(subMat);
        }
        return det;
    }
}

vector<vector<float>> adjoinMatrix(vector<vector<float>> M) {
    int n = M.size();
    // init
    vector<vector<float>> adjM(n, vector<float>(n, 0.0f));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // bulid subMat i , j
            vector<vector<float>> subMat = miniorMatrix(M, i, j);
            // 伴随矩阵是代数余子式矩阵的转置矩阵
            adjM[j][i] = pow(-1, i + j) * determinant(subMat);
        }
    }
    return adjM;
}

vector<vector<float>> inverseMatrix(vector<vector<float>> adjM, float det) {
    int n = adjM.size();
    vector<vector<float>> invM(n, vector<float>(n, 0.0f));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            invM[i][j] = adjM[i][j] / det;
        }
    }
    return invM;
}

int main() {
    vector<vector<float>> A = { {-2.0f, 2.0f, -3.0f, 0.0f},
                                {-1.0f, 1.0f, 3.0f, 1.0f},
                                {2.0f, 0.0f, -1.0f, 2.0f},
                                {1.0f, 0.0f, 2.0f, 3.0f} };
    cout << "Determinant of the matrix is " << determinant(A) << endl;

    vector<vector<float>> ans = inverseMatrix(adjoinMatrix(A), determinant(A));

    cout << "InverseMatri of the matrix is:" << endl;
    for (auto &i : ans) {
        for (auto j : i) {
            cout << j << ", ";
        }
        cout << endl;
    }
}