#include <stdio.h>
#include <stdbool.h>

#define P 5 // 프로세스 수
#define R 3 // 자원 종류 수

bool isSafe(int processes[], int avail[], int max[][R], int allot[][R]) {
    int need[P][R];
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allot[i][j];

    bool finish[P] = {0};
    int safeSeq[P];
    int work[R];
    for (int i = 0; i < R; i++) work[i] = avail[i];

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j]) break;

                if (j == R) {
                    for (int k = 0; k < R; k++) work[k] += allot[p][k];
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("시스템이 불안전 상태(Unsafe State)입니다.\n");
            return false;
        }
    }

    printf("안전 상태입니다. 안전 순서열: ");
    for (int i = 0; i < P; i++) printf("P%d ", safeSeq[i]);
    printf("\n");
    return true;
}

int main() {
    int processes[] = {0, 1, 2, 3, 4};
    int avail[] = {3, 3, 2};
    int max[P][R] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
    int allot[P][R] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};

    isSafe(processes, avail, max, allot);
    return 0;
}
