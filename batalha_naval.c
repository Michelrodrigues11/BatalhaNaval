#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 10  // Tamanho do tabuleiro
#define NAVIO_TAMANHO 3  // Tamanho dos navios
#define HABILIDADE_TAMANHO 5  // Tamanho das matrizes de habilidades
#define AFETADO 5  // Valor para representar áreas afetadas

void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char direcao) {
    if (direcao == 'H') {
        if (coluna + NAVIO_TAMANHO > TAMANHO) return 0;
        for (int i = 0; i < NAVIO_TAMANHO; i++) {
            if (tabuleiro[linha][coluna + i] != 0) return 0;
        }
        for (int i = 0; i < NAVIO_TAMANHO; i++) {
            tabuleiro[linha][coluna + i] = 3;
        }
    } else if (direcao == 'V') {
        if (linha + NAVIO_TAMANHO > TAMANHO) return 0;
        for (int i = 0; i < NAVIO_TAMANHO; i++) {
            if (tabuleiro[linha + i][coluna] != 0) return 0;
        }
        for (int i = 0; i < NAVIO_TAMANHO; i++) {
            tabuleiro[linha + i][coluna] = 3;
        }
    } else {
        return 0;
    }
    return 1;
}

void aplicarHabilidade(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char tipo) {
    int habilidade[HABILIDADE_TAMANHO][HABILIDADE_TAMANHO] = {0};
    int centro = HABILIDADE_TAMANHO / 2;

    if (tipo == 'C') { // Cruz
        for (int i = 0; i < HABILIDADE_TAMANHO; i++) {
            habilidade[centro][i] = 1;
            habilidade[i][centro] = 1;
        }
    } else if (tipo == 'O') { // Octaedro
        for (int i = 0; i < HABILIDADE_TAMANHO; i++) {
            for (int j = 0; j < HABILIDADE_TAMANHO; j++) {
                if (abs(i - centro) + abs(j - centro) <= centro) {
                    habilidade[i][j] = 1;
                }
            }
        }
    } else if (tipo == 'N') { // Cone
        for (int i = 0; i < HABILIDADE_TAMANHO; i++) {
            for (int j = centro - i; j <= centro + i; j++) {
                if (j >= 0 && j < HABILIDADE_TAMANHO) {
                    habilidade[i][j] = 1;
                }
            }
        }
    }

    for (int i = 0; i < HABILIDADE_TAMANHO; i++) {
        for (int j = 0; j < HABILIDADE_TAMANHO; j++) {
            int x = linha + i - centro;
            int y = coluna + j - centro;
            if (x >= 0 && x < TAMANHO && y >= 0 && y < TAMANHO && habilidade[i][j] == 1) {
                if (tabuleiro[x][y] == 0) {
                    tabuleiro[x][y] = AFETADO;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    inicializarTabuleiro(tabuleiro);
    
    int linha1 = 2, coluna1 = 3;
    int linha2 = 5, coluna2 = 6;
    char direcao1 = 'H';
    char direcao2 = 'V';

    if (!posicionarNavio(tabuleiro, linha1, coluna1, direcao1)) {
        printf("Erro ao posicionar o primeiro navio!\n");
    }
    if (!posicionarNavio(tabuleiro, linha2, coluna2, direcao2)) {
        printf("Erro ao posicionar o segundo navio!\n");
    }
    
    aplicarHabilidade(tabuleiro, 4, 4, 'C'); // Cruz no centro do tabuleiro
    aplicarHabilidade(tabuleiro, 7, 7, 'O'); // Octaedro
    aplicarHabilidade(tabuleiro, 2, 2, 'N'); // Cone
    
    exibirTabuleiro(tabuleiro);
    
    return 0;
}
