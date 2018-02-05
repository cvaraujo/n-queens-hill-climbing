#include "HillClimbing.h"

int *count_col, *atck_l, *atck_dp_b, *atck_dp_u, *atck_ds_b, *atck_ds_u, total_atck = 0;

int reduce(int lin, int col, int N) {
    int aux, t_queen;
    int result = total_atck;

    t_queen = count_col[col];
    if (t_queen > 1) {
        aux = t_queen * (t_queen - 1);
        count_col[col] = --t_queen;
        result -= aux - (t_queen * (t_queen - 1));
    } else {
        count_col[col] = 0;
    }

    if (lin == col) {
        t_queen = atck_dp_b[0];
        if (t_queen > 1) {
            aux = t_queen * (t_queen - 1);
            atck_dp_b[0] = --t_queen;
            result -= aux - (t_queen * (t_queen - 1));
        } else {
            atck_dp_b[0] = 0;
        }
    } else {
        int diag = lin - col;
        // Diag_p_b
        if (diag > 0) {
            t_queen = atck_dp_b[diag];
            if (t_queen > 1) {
                aux = t_queen * (t_queen - 1);
                atck_dp_b[diag] = --t_queen;
                result -= aux - (t_queen * (t_queen - 1));
            } else {
                atck_dp_b[diag] = 0;
            }
            // Diag_p_u
        } else {
            diag *= -1;
            t_queen = atck_dp_u[diag];
            if (t_queen > 1) {
                aux = t_queen * (t_queen - 1);
                atck_dp_u[diag] = --t_queen;
                result -= aux - (t_queen * (t_queen - 1));
            } else {
                atck_dp_u[diag] = 0;
            }
        }
    }

    int ds = lin + col;

    if (ds == N - 1) {
        t_queen = atck_ds_b[0];
        if (t_queen > 1) {
            aux = t_queen * (t_queen - 1);
            atck_ds_b[0] = --t_queen;
            result -= aux - (t_queen * (t_queen - 1));
        } else {
            atck_ds_b[0] = 0;
        }
    } else {
        int diag = lin + col;
        // diag_s_b
        if (diag >= N) {
            diag -= N - 1;
            t_queen = atck_ds_b[diag];
            if (t_queen > 1) {
                aux = t_queen * (t_queen - 1);
                atck_ds_b[diag] = --t_queen;
                result -= aux - (t_queen * (t_queen - 1));
            } else {
                atck_ds_b[diag] = 0;
            }
            // diag_ds_u
        } else {
            t_queen = atck_ds_u[diag];
            if (t_queen > 1) {
                aux = t_queen * (t_queen - 1);
                atck_ds_u[diag] = --t_queen;
                result -= aux - (t_queen * (t_queen - 1));
            } else {
                atck_ds_u[diag] = 0;
            }
        }
    }
    return result;
}

int realoc(int lin, int col, int N, int result) {
    int aux, t_queen;

    t_queen = count_col[col];
    if (t_queen > 0) {
        aux = t_queen * (t_queen - 1);
        count_col[col] = ++t_queen;
        result += (t_queen * (t_queen - 1)) - aux;
    } else {
        count_col[col]++;
    }
    if (lin == col) {
        t_queen = atck_dp_b[0];
        if (t_queen > 0) {
            aux = t_queen * (t_queen - 1);
            atck_dp_b[0] = ++t_queen;
            result += (t_queen * (t_queen - 1)) - aux;
        } else {
            atck_dp_b[0]++;
        }
    } else {
        int diag = lin - col;
        // Diag_p_b
        if (diag > 0) {
            t_queen = atck_dp_b[diag];
            if (t_queen > 0) {
                aux = t_queen * (t_queen - 1);
                atck_dp_b[diag] = ++t_queen;
                result += (t_queen * (t_queen - 1)) - aux;
            } else {
                atck_dp_b[diag]++;
            }
            // Diag_p_u
        } else {
            diag *= -1;
            t_queen = atck_dp_u[diag];
            if (t_queen > 0) {
                aux = t_queen * (t_queen - 1);
                atck_dp_u[diag] = ++t_queen;
                result += (t_queen * (t_queen - 1)) - aux;
            } else {
                atck_dp_u[diag]++;
            }
        }
    }
    //printf("3. %d\n", result);
    int ds = lin + col;

    if (ds == N - 1) {
        t_queen = atck_ds_b[0];
        if (t_queen > 0) {
            aux = t_queen * (t_queen - 1);
            atck_ds_b[0] = ++t_queen;
            result += (t_queen * (t_queen - 1)) - aux;
        } else {
            atck_ds_b[0]++;
        }
    } else {
        // diag_s_b
        if (ds >= N) {
            ds -= (N - 1);
            t_queen = atck_ds_b[ds];
            if (t_queen > 0) {
                aux = t_queen * (t_queen - 1);
                atck_ds_b[ds] = ++t_queen;
                result += (t_queen * (t_queen - 1)) - aux;
            } else {
                atck_ds_b[ds]++;
            }
            // diag_ds_u
        } else {
            t_queen = atck_ds_u[ds];
            if (t_queen > 0) {
                aux = t_queen * (t_queen - 1);
                atck_ds_u[ds] = ++t_queen;
                result += (t_queen * (t_queen - 1)) - aux;
            } else {
                atck_ds_u[ds]++;
            }
        }
    }
    return result;
}

int totalAttack(int lin, int col, int N) {
    int total = count_col[col];
    if (lin == col) {
        total += atck_dp_b[0];
    } else {
        int diag = lin - col;
        if (diag > 0) {
            total += atck_dp_b[diag];
        } else {
            total += atck_dp_u[-diag];
        }
    }

    int ds = lin + col;

    if (ds == N - 1) {
        total += atck_ds_b[0];
    } else {
        if (ds >= N) {
            ds -= (N - 1);
            total += atck_ds_b[ds];
        } else {
            total += atck_ds_u[ds];
        }
    }

    return total;
}

void climbing(int N, FILE *arq) {
    srandom(time(NULL));
    long long int count = (N * 100);
    int ini, q1, q2;
    bool find = false;

    while (count > 0) {
        do {
            q1 = rand() % N;
            q2 = rand() % N;
        } while (q1 == q2);

        int result_q1 = totalAttack(q1, atck_l[q1], N);
        int result_q2 = totalAttack(q2, atck_l[q2], N);

        if (result_q1 > result_q2) {
            ini = q1;
        } else {
            ini = q2;
        }

        int col = atck_l[ini];

        int result = reduce(ini, col, N);

        do {
            atck_l[ini] = rand() % N;
        } while (atck_l[ini] == col);

        result = realoc(ini, atck_l[ini], N, result);

        int aux = total_atck;
        total_atck = result;

        if (total_atck == 0) {
            find = true;
            break;
        } else if (total_atck > aux) {
            result = reduce(ini, atck_l[ini], N);
            atck_l[ini] = col;
            result = realoc(ini, col, N, result);
            total_atck = result;
        }
        count++;
    }

    if (!find) {
        total_atck = 0;
        init_board(arq, N);
    }

}

int init_board(FILE *arq, int n) {
    int N = n;
    int diag = N * 2;
    srandom(time(NULL));

    atck_l = (int *) malloc(N * sizeof(int));
    count_col = (int *) malloc(N * sizeof(int));

    atck_dp_b = (int *) malloc(diag * sizeof(int));
    atck_ds_b = (int *) malloc(diag * sizeof(int));

    atck_dp_u = (int *) malloc(diag * sizeof(int));
    atck_ds_u = (int *) malloc(diag * sizeof(int));

    for (int i = 0; i < N; ++i) {
        atck_l[i] = count_col[i] = 0;
    }
    for (int i = 0; i < diag; ++i) {
        atck_dp_u[i] = atck_dp_b[i] = 0;
        atck_ds_u[i] = 0;
        atck_ds_b[i] = 0;
    }

    int c, l_inp = -1;
    for (int i = 0; i < N; ++i) {
        c = rand() % N;
        if (c == l_inp - 1 || c == l_inp + 1) {
            if (c + 3 >= N) {
                c -= 3;
            } else {
                c += 3;
            }
        }
        l_inp = c;
        atck_l[i] = c;
        total_atck = realoc(i, c, N, total_atck);
    }
    climbing(N, arq);
    return N;
}

void write_solution(int N, FILE *arq) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (j == N - 1) {
                if (atck_l[i] == j) {
                    fprintf(arq, "%d", 1);
                } else {
                    fprintf(arq, "%d", 0);
                }
            } else {
                if (atck_l[i] == j) {
                    fprintf(arq, "%d ", 1);
                } else {
                    fprintf(arq, "%d ", 0);
                }
            }
        }
        fprintf(arq, "\n");
    }
}