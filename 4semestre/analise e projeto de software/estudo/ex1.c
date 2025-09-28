#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define MAXN 100

int n;
int tri[MAXN][MAXN];

// ======== 1) FORÇA BRUTA ========
int best_sum_brut;
int path_brut[MAXN];
int temp_path[MAXN];

void brute_force(int i, int j, int sum) {
    sum += tri[i][j];
    temp_path[i] = tri[i][j];
    if (i == n-1) {
        if (sum > best_sum_brut) {
            best_sum_brut = sum;
            for (int k = 0; k < n; k++) path_brut[k] = temp_path[k];
        }
        return;
    }
    // descer esquerda
    brute_force(i+1, j, sum);
    // descer direita
    brute_force(i+1, j+1, sum);
}

// ======== 2) GULOSO ========
int path_guloso[MAXN];
int greedy() {
    int sum = tri[0][0];
    int j = 0;
    path_guloso[0] = tri[0][0];
    for (int i = 1; i < n; i++) {
        // compara tri[i][j] vs tri[i][j+1]
        if (tri[i][j] >= tri[i][j+1]) {
            sum += tri[i][j];
            path_guloso[i] = tri[i][j];
            // j permanece
        } else {
            sum += tri[i][j+1];
            path_guloso[i] = tri[i][j+1];
            j = j+1;
        }
    }
    return sum;
}

// ======== 3) PROGRAMAÇÃO DINÂMICA ========
int dp[MAXN][MAXN];
int path_dp[MAXN];

int dynamic_programming() {
    // inicializa última linha
    for (int j = 0; j < n; j++) dp[n-1][j] = tri[n-1][j];
    // bottom-up
    for (int i = n-2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            int esquerda = dp[i+1][j];
            int direita = dp[i+1][j+1];
            dp[i][j] = tri[i][j] + (esquerda > direita ? esquerda : direita);
        }
    }
    // reconstruir caminho
    int j = 0;
    path_dp[0] = tri[0][0];
    for (int i = 1; i < n; i++) {
        int esq = dp[i][j];
        int dir = dp[i][j+1];
        if (esq >= dir) {
            path_dp[i] = tri[i][j];
            // j mantém
        } else {
            path_dp[i] = tri[i][j+1];
            j = j+1;
        }
    }
    return dp[0][0];
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            scanf("%d", &tri[i][j]);
        }
    }

    // Força bruta
    best_sum_brut = INT_MIN;
    brute_force(0, 0, 0);
    printf("Forca Bruta: soma = %d, caminho:", best_sum_brut);
    for (int i = 0; i < n; i++) printf(" %d", path_brut[i]);
    printf("\n");

    // Guloso
    int sum_g = greedy();
    printf("Guloso: soma = %d, caminho:", sum_g);
    for (int i = 0; i < n; i++) printf(" %d", path_guloso[i]);
    printf("\n");

    // Programacao Dinamica
    int sum_dp = dynamic_programming();
    printf("Prog. Dinamica: soma = %d, caminho:", sum_dp);
    for (int i = 0; i < n; i++) printf(" %d", path_dp[i]);
    printf("\n");

    return 0;
}
