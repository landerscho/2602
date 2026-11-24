#include <stdio.h>
#include <stdint.h>

void printBinary(int8_t num) {
    for (int i = 7; i >= 0; i--) printf("%d", (num >> i) & 1);
}

void boothsAlgorithm(int8_t M, int8_t Q) {
    int8_t A = 0;
    int Q_1 = 0;
    int count = 8;

    printf("초기 상태 | A: "); printBinary(A);
    printf(" | Q: "); printBinary(Q);
    printf(" | Q-1: %d\n", Q_1);

    while (count > 0) {
        int Q0 = Q & 1;
        if (Q0 == 1 && Q_1 == 0) {
            A -= M;
        } else if (Q0 == 0 && Q_1 == 1) {
            A += M;
        }

        // 산술 우측 시프트 (A, Q, Q_1 결합)
        Q_1 = Q & 1;
        Q = ((uint8_t)Q >> 1) | ((A & 1) << 7);
        A = A >> 1; // C에서 signed int의 >> 는 산술 시프트로 동작
        count--;
    }

    int16_t result = ((int16_t)A << 8) | (uint8_t)Q;
    printf("최종 결과 | %d * %d = %d (이진수: ", M, Q, result);
    printBinary(A); printf(" "); printBinary(Q); printf(")\n");
}

int main() {
    boothsAlgorithm(-7, 3);
    return 0;
}
