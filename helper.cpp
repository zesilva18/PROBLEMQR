#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int BLACKCELLS = 0;

int linhasPretas[30];
int colunasPretas[30];
int diagonaisPretas[2] = {0, 0};
int difflinhasPretas[30];
int diffcolunasPretas[30];
int quadrantesPretas[4] = {0, 0, 0, 0};

// crete a struct with an int and array bidimensional
struct Resultado {
    int n;
    int qr[30][30];
};

void printArray(int array[][30], int n) {
    cout << "+";
    for (int j = 0; j < n; j++) {
        cout << "-";
    }
    cout << "+" << endl;

    for (int i = 0; i < n; i++) {
        cout << "|";
        for (int j = 0; j < n; j++) {
            if (array[i][j] == 1) {
                cout << "#";
            }
            if (array[i][j] == 0) {
                cout << " ";
            }

            if (array[i][j] == 9) {
                cout << "?";
            }
        }
        cout << "|" << endl;
    }

    cout << "+";
    for (int j = 0; j < n; j++) {
        cout << "-";
    }
    cout << "+" << endl;
}

int contaLinhasPelosVistos(int array[][30], int n, int linha) {  // conta transicoes, desculpe pelo nome eram 2:44 da manha
    int contador = 0;

    for (int i = 1; i < n; i++) {
        if (array[linha][i] == 0 && array[linha][i - 1] == 1 || array[linha][i] == 1 && array[linha][i - 1] == 0) {
            contador++;
        }
    }

    return contador;
}

int contarColunasPelosVistos(int array[][30], int n, int coluna) {  // conta transicoes, desculpe pelo nome eram 2:44 da manha
    int contador = 0;

    for (int i = 1; i < n; i++) {
        if (array[i][coluna] == 0 && array[i - 1][coluna] == 1 || array[i][coluna] == 1 && array[i - 1][coluna] == 0) {
            contador++;
        }
    }

    return contador;
}

int contaLinhasMesmo(int array[][30], int n, int linha) {
    int contador = 0;

    for (int i = 0; i < n; i++) {
        if (array[linha][i] == 1) {
            contador++;
        }
    }

    return contador;
}

int contaColunasMesmo(int array[][30], int n, int coluna) {
    int contador = 0;

    for (int i = 0; i < n; i++) {
        if (array[i][coluna] == 1) {
            contador++;
        }
    }

    return contador;
}

int contaDiagonaisMesmo(int array[][30], int n) {
    int contador = 0;

    for (int i = 0; i < n; i++) {
        if (array[i][i] == 1) {
            contador++;
        }
    }

    return contador;
}

int contaDiagonaisSecundariaMesmo(int array[][30], int n) {
    int contador = 0;

    for (int i = 0; i < n; i++) {
        if (array[i][n - 1 - i] == 1) {
            contador++;
        }
    }

    return contador;
}

int ContaCoisasQ1(int array[][30], int n) {
    int contador = 0;

    for (int i = 0; i < floor(n / 2); i++) {
        for (int j = floor(n / 2); j < n; j++) {
            if (array[i][j] == 1) {
                contador++;
            }
        }
    }
    return contador;
}

int ContaCoisasQ2(int array[][30], int n) {
    int contador = 0;

    for (int i = 0; i < floor(n / 2); i++) {
        for (int j = 0; j < floor(n / 2); j++) {
            if (array[i][j] == 1) {
                contador++;
            }
        }
    }

    return contador;
}

int ContaCoisasQ3(int array[][30], int n) {
    int contador = 0;

    for (int i = floor(n / 2); i < n; i++) {
        for (int j = 0; j < floor(n / 2); j++) {
            if (array[i][j] == 1) {
                contador++;
            }
        }
    }

    return contador;
}

int ContaCoisasQ4(int array[][30], int n) {
    int contador = 0;

    for (int i = floor(n / 2); i < n; i++) {
        for (int j = floor(n / 2); j < n; j++) {
            if (array[i][j] == 1) {
                contador++;
            }
        }
    }

    return contador;
}

bool verifyTrue(int array[][30], int n, vector<int> &linhas, vector<int> &colunas, vector<int> &diagonais, vector<int> &difflinhas, vector<int> &diffcolunas, vector<int> &quadrants) {
    int line = 0;
    int column = 0;
    int diagonal = 0;
    int inversediagonal = 0;
    int countTransLinhas = 0;
    int countTransColunas = 0;
    int quadrantsEqual[4] = {0, 0, 0, 0};

    for (int i = 0; i < n; i++) {
        int valorLinha = array[i][0];
        countTransLinhas = 0;
        int valorColuna = array[0][i];
        countTransColunas = 0;

        for (int j = 0; j < n; j++) {
            if (array[i][j] == 1) {  // linhas
                line++;
            }
            if (array[j][i] == 1) {  // colunas
                column++;
            }

            if (i == j && array[i][j] == 1) {  // diagonias
                diagonal++;
            }

            if (n - 1 == j + i && array[i][j] == 1) {  // inversediagonais
                inversediagonal++;
            }

            if (array[i][j] != valorLinha) {  // transições de linhas
                countTransLinhas++;
            }

            if (array[j][i] != valorColuna) {  // transições de colunas
                countTransColunas++;
            }

            // quadrante 1
            if (i < floor(n / 2) && j >= floor(n / 2) && array[i][j] == 1) {
                quadrantsEqual[0]++;
            }

            // quadrante 2
            else if (i < floor(n / 2) && j < floor(n / 2) && array[i][j] == 1) {
                quadrantsEqual[1]++;
            }

            // quadrante 3
            else if (i >= floor(n / 2) && j < floor(n / 2) && array[i][j] == 1) {
                quadrantsEqual[2]++;
            }

            // quadrante 4
            else if (i >= floor(n / 2) && j >= floor(n / 2) && array[i][j] == 1) {
                quadrantsEqual[3]++;
            }

            valorColuna = array[j][i];
            valorLinha = array[i][j];
        }

        if (line != linhas[i] || column != colunas[i] || countTransLinhas != difflinhas[i] || countTransColunas != diffcolunas[i]) {
            return false;
        }

        line = 0;
        column = 0;
    }

    if (diagonal != diagonais[0] || inversediagonal != diagonais[1]) {
        return false;
    }

    for (int i = 0; i < 4; i++) {
        if (quadrantsEqual[i] != quadrants[i]) {
            return false;
        }
    }

    return true;
}

void generateArrays(int n, int array[][30], int i, int j, vector<int> &linhas, vector<int> &colunas, vector<int> &diagonais, vector<int> &difflinhas, vector<int> &diffcolunas, vector<int> &quadrants, int pretos, Resultado &res) {
    if (i == n) {  // encontrou uma combinação válida
        if (pretos == BLACKCELLS && verifyTrue(array, n, linhas, colunas, diagonais, difflinhas, diffcolunas, quadrants) == true) {
            res.n++;
            memcpy(res.qr, array, sizeof(res.qr));
        }
        return;
    }

    if (j == n) {  // passou da última coluna, muda para a próxima linha
        generateArrays(n, array, i + 1, 0, linhas, colunas, diagonais, difflinhas, diffcolunas, quadrants, pretos, res);
        return;
    }

    // Backtrackings (verificar casos anteriores)

    // Caso 1 - Se a linha anterior tiver células pretas diferentes do suposto, não é necessário continuar a linha
    if (i > 0 && contaLinhasMesmo(array, n, i - 1) != linhas[i - 1]) {
        return;
    }

    // Caso 2 - Se a coluna anterior tiver células pretas diferentes do suposto, não é necessário continuar a coluna

    if (i > 0 && contaColunasMesmo(array, n, j - 1) > colunas[j - 1]) {
        return;
    }

    // Caso 3 - Se a linha anterior tiver transições diferentes do suposto, não é necessário continuar a linha
    if (i > 0 && contaLinhasPelosVistos(array, n, i - 1) != difflinhas[i - 1]) {
        return;
    }

    // Caso 4 - Se a coluna anterior tiver células pretas diferentes do suposto, não é necessário continuar a coluna

    if (i > 0 && contarColunasPelosVistos(array, n, j - 1) > diffcolunas[j - 1]) {
        return;
    }

    // Caso 5 - Se a diagonal principal tiver mais celulas pretas que  o suposto, não é necessário continuar
    if (i > 0 && contaDiagonaisMesmo(array, n) > diagonais[0]) {
        return;
    }

    // Caso 6 - Se a diagonal secundaria tiver mais celulas pretas que  o suposto, não é necessário continuar
    if (i > 0 && contaDiagonaisSecundariaMesmo(array, n) > diagonais[1]) {
        return;
    }

    // Caso 7 - Se o quadrante 1 tiver mais celulas pretas que  o suposto, não é necessário continuar

    if (i > 0 && ContaCoisasQ1(array, n) > quadrants[0]) {
        return;
    }

    // Caso 8 - Se o quadrante 2 tiver mais celulas pretas que  o suposto, não é necessário continuar

    if (i > 0 && ContaCoisasQ2(array, n) > quadrants[1]) {
        return;
    }

    // Caso 9 - Se o quadrante 3 tiver mais celulas pretas que  o suposto, não é necessário continuar

    if (i > 0 && ContaCoisasQ3(array, n) > quadrants[2]) {
        return;
    }

    // Caso 10 - Se o quadrante 4 tiver mais celulas pretas que  o suposto, não é necessário continuar

    if (i > 0 && ContaCoisasQ4(array, n) > quadrants[3]) {
        return;
    }

    if (array[i][j] == 9) {  // se a posição (i,j) já estiver preenchida com 1, não precisa tentar colocar 0
        array[i][j] = 1;     // tenta colocar 0 na posição (i,j)
        BLACKCELLS++;
        generateArrays(n, array, i, j + 1, linhas, colunas, diagonais, difflinhas, diffcolunas, quadrants, pretos, res);  // faz chamada recursiva para a próxima coluna
        array[i][j] = 0;                                                                                                  // tenta colocar 1 na posição (i,j)
        BLACKCELLS--;
        generateArrays(n, array, i, j + 1, linhas, colunas, diagonais, difflinhas, diffcolunas, quadrants, pretos, res);  // faz chamada recursiva para a próxima coluna
        array[i][j] = 9;                                                                                                  // volta a posição (i,j) para o valor original
    }

    else {
        generateArrays(n, array, i, j + 1, linhas, colunas, diagonais, difflinhas, diffcolunas, quadrants, pretos, res);  // faz chamada recursiva para a próxima coluna
    }
}

void preprocessamento(int n, int array[][30], vector<int> &linhas, vector<int> &colunas, vector<int> &diagonais, vector<int> &difflinhas, vector<int> &diffcolunas, vector<int> &quadrants, int pretos, Resultado &res) {
    // preencher a matriz com -1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            array[i][j] = 9;
        }
    }

    for (int i = 0; i < 4; i++) {
        if (quadrants[i] == 0) {  // preencher o quadrante correspondete com 0
            if (i == 0) {         // primeiro quadrante
                for (int j = 0; j < floor(n / 2); j++) {
                    for (int k = floor(n / 2); k < n; k++) {
                        array[j][k] = 0;
                    }
                }
            }
            if (i == 1) {  // segundo quadrante
                for (int j = 0; j < floor(n / 2); j++) {
                    for (int k = 0; k < floor(n / 2); k++) {
                        array[j][k] = 0;
                    }
                }
            }

            if (i == 2) {  // terceiro quadrante
                for (int j = floor(n / 2); j < n; j++) {
                    for (int k = 0; k < floor(n / 2); k++) {
                        array[j][k] = 0;
                    }
                }
            }

            if (i == 3) {  // quarto quadrante

                for (int j = floor(n / 2); j < n; j++) {
                    for (int k = floor(n / 2); k < n; k++) {
                        array[j][k] = 0;
                    }
                }
            }
        }
        if (quadrants[i] == (floor(n / 2 + 1) * floor(n / 2 + 1))) {  // preencher o quadrante correspondete com 1

            if (i == 0) {  // primeiro quadrante

                for (int j = 0; j < floor(n / 2); j++) {
                    for (int k = floor(n / 2); k < n; k++) {
                        array[j][k] = 1;
                    }
                }
            }
            if (i == 1) {  // segundo quadrante
                for (int j = 0; j < floor(n / 2); j++) {
                    for (int k = 0; k < floor(n / 2); k++) {
                        array[j][k] = 1;
                    }
                }
            }

            if (i == 2) {  // terceiro quadrante
                for (int j = floor(n / 2); j < n; j++) {
                    for (int k = 0; k < floor(n / 2); k++) {
                        array[j][k] = 1;
                    }
                }
            }

            if (i == 3) {  // quarto quadrante
                for (int j = floor(n / 2); j < n; j++) {
                    for (int k = floor(n / 2); k < n; k++) {
                        array[j][k] = 1;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (linhas[i] == 0) {
            // percorrer a linha e preencher a 0
            for (int j = 0; j < n; j++) {
                array[i][j] = 0;
            }
        }

        if (linhas[i] == n) {
            // percorrer a linha e preencher a 1
            for (int j = 0; j < n; j++) {
                array[i][j] = 1;
            }
        }

        if (colunas[i] == 0) {
            // percorrer a coluna e preencher a 0
            for (int j = 0; j < n; j++) {
                array[j][i] = 0;
            }
        }

        if (colunas[i] == n) {
            // percorrer a coluna e preencher a 1
            for (int j = 0; j < n; j++) {
                array[j][i] = 1;
            }
        }
    }

    if (diagonais[0] == 0) {
        // percorrer a diagonal e preencher a 0
        for (int i = 0; i < n; i++) {
            array[i][i] = 0;
        }
    }

    if (diagonais[0] == n) {  // preprocessamento da diagonal principal
        // percorrer a diagonal e preencher a 1
        for (int i = 0; i < n; i++) {
            array[i][i] = 1;
        }
    }

    if (diagonais[1] == 0) {  // preprocessamento da diagonal secundaria
        // percorrer a diagonal e preencher a 0
        for (int i = 0; i < n; i++) {
            array[i][n - i - 1] = 0;
        }
    }

    if (diagonais[1] == n) {  // preprocessamento da diagonal secundaria
        // percorrer a diagonal e preencher a 1
        for (int i = 0; i < n; i++) {
            array[i][n - i - 1] = 1;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (array[i][j] == 1) {
                BLACKCELLS++;
            }
        }
    }

    if (BLACKCELLS == pretos) {
        // put all 9's in the array to 2´s
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (array[i][j] == 9) {
                    array[i][j] = 0;
                }
            }
        }
    }

    memcpy(res.qr, array, sizeof(res.qr));
}

void contagemNextProcess(int array[][30], int n) {
    int valorLinha;
    int valorColuna;

    for (int i = 0; i < n; i++) {
        int linhas = 0;
        int colunas = 0;

        valorLinha = array[i][0];
        valorColuna = array[0][i];

        for (int j = 0; j < n; j++) {
            if (array[i][j] == 1) {  // linhas pretas

                linhas++;
            }

            if (array[j][i] == 1) {  // colunas pretas

                colunas++;
            }

            if (array[i][j] == 1 && i == j) {  // diagonais pretas
                diagonaisPretas[0]++;
            }

            if (array[i][j] == 1 && i == n - j - 1) {  // diagonais inversas pretas
                diagonaisPretas[1]++;
            }

            // quadrante 1
            if (i < floor(n / 2) && j >= floor(n / 2) && array[i][j] == 1) {
                quadrantesPretas[0]++;
            }

            // quadrante 2
            else if (i < floor(n / 2) && j < floor(n / 2) && array[i][j] == 1) {
                quadrantesPretas[1]++;
            }

            // quadrante 3
            else if (i >= floor(n / 2) && j < floor(n / 2) && array[i][j] == 1) {
                quadrantesPretas[2]++;
            }

            // quadrante 4
            else if (i >= floor(n / 2) && j >= floor(n / 2) && array[i][j] == 1) {
                quadrantesPretas[3]++;
            }

            if (array[i][j] != valorLinha) {  // linhas brancas
                valorLinha = array[i][j];
                difflinhasPretas[i]++;
            }

            if (array[j][i] != valorColuna) {  // colunas brancas
                valorColuna = array[j][i];
                diffcolunasPretas[i]++;
            }
        }

        linhasPretas[i] = linhas;
        colunasPretas[i] = colunas;
    }
}

void clearArrays() {
    for (int i = 0; i < 30; i++) {
        linhasPretas[i] = 0;
        colunasPretas[i] = 0;
        difflinhasPretas[i] = 0;
        diffcolunasPretas[i] = 0;
    }

    for (int i = 0; i < 2; i++) {
        diagonaisPretas[i] = 0;
    }

    for (int i = 0; i < 4; i++) {
        quadrantesPretas[i] = 0;
    }

    BLACKCELLS = 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int qr;

    int aceita = 0;

    int numero;
    cin >> qr;

    for (int i = 0; i < qr; i++)  // cada qr code
    {
        clearArrays();

        aceita = 0;
        int array[30][30] = {0};  // inicializa a matriz com zeros
        int n;                    // tamanho do array
        int pretos = 0;
        int colunas = 0;
        int quadrantes = 0;

        int valida = 0;

        cin >> n;

        if (n > 30 || n < 2) {
            valida = 1;
        }

        vector<int> lb;
        vector<int> cb;
        vector<int> lt;
        vector<int> ct;
        vector<int> qb;
        vector<int> db;

        int metade1 = floor(n / 2);

        int metade_linhas = 0;
        int metade2_black = 0;
        int metade_colunas = 0;
        int metade2_colunas = 0;

        for (int j = 0; j < n; j++)  // leitura das linhas
        {
            cin >> numero;
            if (numero > n || numero < 0) {
                valida = 1;
            }
            lb.push_back(numero);
            pretos += numero;

            if (j < metade1) {
                metade_linhas += numero;
            } else {
                metade2_black += numero;
            }
        }

        for (int j = 0; j < n; j++)  // leitura das colunas
        {
            cin >> numero;
            if (numero > n || numero < 0) {
                valida = 1;
            }
            cb.push_back(numero);
            colunas += numero;

            if (j < metade1) {
                metade_colunas += numero;
            } else {
                metade2_colunas += numero;
            }
        }

        for (int j = 0; j < n; j++)  // leitura das diferenças de linhas
        {
            cin >> numero;
            if (numero > lb[j] * 2 || numero < 0) {
                valida = 1;
            }
            lt.push_back(numero);
        }

        for (int j = 0; j < n; j++)  // leitura das diferenças de colunas
        {
            cin >> numero;
            if (numero > cb[j] * 2 || numero < 0) {
                valida = 1;
            }
            ct.push_back(numero);
        }

        int sumq1 = 0;
        int sumq2 = 0;
        int sumq3 = 0;
        int sumq4 = 0;

        for (int j = 0; j < 4; j++)  // leitura dos quadrantes
        {
            cin >> numero;
            if ((floor(n / 2 + 1) * floor(n / 2 + 1)) < numero || numero < 0) {
                valida = 1;
            }
            qb.push_back(numero);
            quadrantes += numero;

            if (j < 2) {
                sumq1 += numero;
            } else {
                sumq2 += numero;
            }

            if (j == 1 || j == 2) {
                sumq3 += numero;
            }

            else {
                sumq4 += numero;
            }
        }

        if (metade_linhas != sumq1 || metade2_black != sumq2 || sumq3 != metade_colunas || sumq4 != metade2_colunas)  // da 40 pontos
        {
            valida = 1;
        }

        for (int j = 0; j < 2; j++)  // leitura das diagonais
        {
            cin >> numero;
            if (numero > n) {
                valida = 1;
            }
            db.push_back(numero);
        }

        if (quadrantes != pretos || colunas != pretos || colunas != quadrantes) {  // opha isto resolveu mais casos de teste +20 pontitos
            valida = 1;
        }

        for (int j = 0; j < n; j++)  // leitura das diagonais
        {
            if (lb[j] == 0 && cb[j] == n)  // se a linha for toda branca e a coluna toda preta
            {
                valida = 1;
            }

            if (lb[j] == n && cb[j] == 0)  // se a linha for toda preta e a coluna toda branca
            {
                valida = 1;
            }

            if ((lb[j] == 0 || lb[j] == n) && lt[j] != 0) {
                valida = 1;
            }

            if ((cb[j] == 0 || cb[j] == n) && ct[j] != 0) {
                valida = 1;
            }
        }

        if (valida == 1) {
            cout << "DEFECT: No QR Code generated!" << endl;
        }

        else if (valida == 0) {
            Resultado res;
            res.n = aceita;

            preprocessamento(n, array, lb, cb, db, lt, ct, qb, pretos, res);

            contagemNextProcess(array, n);

            generateArrays(n, array, 0, 0, lb, cb, db, lt, ct, qb, pretos, res);

            if (res.n == 0) {
                cout << "DEFECT: No QR Code generated!" << endl;
            } else if (res.n == 1) {
                cout << "VALID: 1 QR Code generated!" << endl;
                printArray(res.qr, n);
            } else if (res.n > 1) {
                cout << "INVALID: " << res.n << " QR Codes generated!" << endl;
            }
        }
    }
    return 0;
}