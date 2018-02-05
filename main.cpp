#include "HillClimbing.h"

int main() {
    clock_t t0;
    FILE *arq;
    int N;
    scanf("%d", &N);
    auto a = to_string(N) + ".txt";
    auto name = a.c_str();
    arq = fopen(name, "w");
    t0 = clock();
    int n = init_board(arq, N);
    printf("Time = %.3lf", ((clock() - t0) / (double) CLOCKS_PER_SEC));
    fprintf(arq, "N = %d & Time = %.3lf\n", n, ((clock() - t0) / (double) CLOCKS_PER_SEC));
    write_solution(N, arq);
    fclose(arq);
    return 0;
}