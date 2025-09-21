#include <stdio.h>
#include <stdlib.h>

#define LINHAS 10     // Linhas da matriz do tabuleiro
#define COLUNAS 10    // Colunas da matriz do tabuleiro
#define HABLINHAS 5   // Linhas da matriz das habilidades
#define HABCOLUNAS 5  // Colunas da matriz das habilidades

// Imprime o tabuleiro

void imprimirTabuleiro(int matriz[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

// Imprime uma habilidade

void imprimirHabilidade(int hab[HABLINHAS][HABCOLUNAS]) {
    for (int i = 0; i < HABLINHAS; i++) {
        for (int j = 0; j < HABCOLUNAS; j++) {
            printf("%d ", hab[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Matriz do cone

void habcone(int matriz[HABLINHAS][HABCOLUNAS]) {

    for (int i = 0; i < HABLINHAS; i++)
        for (int j = 0; j < HABCOLUNAS; j++)
            matriz[i][j] = 0;

    matriz[0][2] = 1;

    for (int j = 1; j <= 3; j++)
        matriz[1][j] = 1;

    for (int j = 0; j < 5; j++)
        matriz[2][j] = 1;
}

// Cruz

void habcruz(int matriz[HABLINHAS][HABCOLUNAS]) {
    for (int i = 0; i < HABLINHAS; i++){
        for (int j = 0; j < HABCOLUNAS; j++){
            if (i == HABLINHAS/2 || j == HABCOLUNAS/2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Octaedro

void haboctaedro(int matriz[HABLINHAS][HABCOLUNAS]) {
    for (int i = 0; i < HABLINHAS; i++){
        for (int j = 0; j < HABCOLUNAS; j++){
            if (abs(i - HABLINHAS/2) + abs(j - HABCOLUNAS/2) <= HABLINHAS/2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Função para aplicar habilidade no tabuleiro
void aplicarHabilidade(int matriz[LINHAS][COLUNAS], int habilidade[HABLINHAS][HABCOLUNAS], int origemX, int origemY) {
    int offset = HABLINHAS/2;

    for (int i = 0; i < HABLINHAS; i++) {
        for (int j = 0; j < HABCOLUNAS; j++) {
            if (habilidade[i][j] == 1) {
                int x = origemX + (i - offset);
                int y = origemY + (j - offset);

                // Garante que fique dentro do tabuleiro
                if (x >= 0 && x < LINHAS && y >= 0 && y < COLUNAS) {
                    if (matriz[x][y] == 0) // não sobrescreve navio (3)
                        matriz[x][y] = 5;  // marca área de habilidade
                }
            }
        }
    }
}

int main() {

    int matriz[LINHAS][COLUNAS];

    printf("*** TABULEIRO DE BATALHA NAVAL ***\n\n");

    // Inicializar tabuleiro com zeros
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            matriz[i][j] = 0;
        }
    }

    // Navio horizontal
    for (int j = 5; j <= 7; j++) {
        matriz[3][j] = 3;
    }

    // Navio vertical
    for (int i = 7; i <= 9; i++) {
        matriz[i][0] = 3;
    }

    // Navio diagonal 1
    for (int i = 7, j = 2; i <= 9; i++, j++) {
        matriz[i][j] = 3;
    }

    // Navio diagonal 2
    for (int i = 0, j = 6; i <= 2; i++, j++) {
        matriz[i][j] = 3;
    }

    // Mostrar tabuleiro inicial
    printf("Tabuleiro inicial:\n");
    imprimirTabuleiro(matriz);
    printf("\n");

    // Criar matrizes de habilidades
    int cone[HABLINHAS][HABCOLUNAS], cruz[HABLINHAS][HABCOLUNAS], octaedro[HABLINHAS][HABCOLUNAS];
    habcone(cone);
    habcruz(cruz);
    haboctaedro(octaedro);

    // Aplicar habilidades em pontos diferentes
    aplicarHabilidade(matriz, cone, 2, 2); // cone em (3,3)
    aplicarHabilidade(matriz, cruz, 5, 4); // cruz em (6,5)
    aplicarHabilidade(matriz, octaedro, 7, 7);  // octaedro em (7,7)

    // Mostrar tabuleiro final
    printf("Tabuleiro com habilidades:\n");
    imprimirTabuleiro(matriz);

    return 0;
}