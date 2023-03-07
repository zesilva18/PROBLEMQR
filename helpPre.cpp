#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;

//crete a struct with an int and array bidimensional
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
            if(array[i][j] == 1){
                cout << "#";
            }
            if(array[i][j] == 0){
                cout << " ";
            }
            if(array[i][j] == 9){
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


void preprocessamento(int n, int array[][30], vector<int> &linhas, vector<int> &colunas, vector<int> &diagonais, vector<int> &difflinhas, vector<int> &diffcolunas, vector<int> &quadrants, int pretos, Resultado& res) {

    //preencher a matriz com -1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            array[i][j] = 9;
        }
    }

    for(int i = 0; i < 4; i++){
        if(quadrants[i] == 0){ //preencher o quadrante correspondete com 0
            if(i == 0){ //primeiro quadrante
                for(int j = 0; j < floor(n/2); j++){
                    for(int k = floor(n/2); k < n; k++){
                        array[j][k] = 0;
                    }
                }
            }
            if(i == 1){ //segundo quadrante
                for (int j = 0; j < floor(n/2); j++) {
                    for (int k = 0; k < floor(n/2); k++) {
                        array[j][k] = 0;
                    }
                }
            }

            if(i == 2){ //terceiro quadrante
                for (int j = floor(n/2); j < n; j++) {
                    for (int k = 0; k < floor(n/2); k++) {
                        array[j][k] = 0;
                    }
                }
            }

            if(i == 3){ //quarto quadrante

                for (int j = floor(n/2); j < n; j++) {
                    for (int k = floor(n/2); k < n; k++) {
                        array[j][k] = 0;
                    }
                }

            }
        }
        if(quadrants[i] == (floor(n/2+1)* floor(n/2+1))){ //preencher o quadrante correspondete com 1

            if(i == 0){ //primeiro quadrante

                for(int j = 0; j < floor(n/2); j++){
                    for(int k = floor(n/2); k < n; k++){
                        array[j][k] = 1;
                    }
                }

            }
            if(i == 1){ //segundo quadrante
                for (int j = 0; j < floor(n/2); j++) {
                    for (int k = 0; k < floor(n/2); k++) {
                        array[j][k] = 1;
                    }
                }
            }

            if(i == 2){ //terceiro quadrante
                for (int j = floor(n/2); j < n; j++) {
                    for (int k = 0; k < floor(n/2); k++) {
                        array[j][k] = 1;
                    }
                }
            }

            if(i == 3){ //quarto quadrante
                for (int j = floor(n/2); j < n; j++) {
                    for (int k = floor(n/2); k < n; k++) {
                        array[j][k] = 0;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if(linhas[i] == 0){
            //percorrer a linha e preencher a 0
            for (int j = 0; j < n; j++) {
                array[i][j] = 0;
            }
        }

        if(linhas[i] == n){
            //percorrer a linha e preencher a 1
            for (int j = 0; j < n; j++) {
                array[i][j] = 1;
            }
        }

        if(colunas[i] == 0){
            //percorrer a coluna e preencher a 0
            for (int j = 0; j < n; j++) {
                array[j][i] = 0;
            }
        }

        if(colunas[i] == n){
            //percorrer a coluna e preencher a 1
            for (int j = 0; j < n; j++) {
                array[j][i] = 1;
            }
        }
    }

    if(diagonais[0] == 0){
    //percorrer a diagonal e preencher a 0
        for (int i = 0; i < n; i++) {
            array[i][i] = 0;
        }
    }

    if(diagonais[0] == n){ //preprocessamento da diagonal principal
        //percorrer a diagonal e preencher a 1
        for (int i = 0; i < n; i++) {
            array[i][i] = 1;
        }
    }

    if(diagonais[1] == 0){ //preprocessamento da diagonal secundaria
        //percorrer a diagonal e preencher a 0
        for (int i = 0; i < n; i++) {
            array[i][n-i-1] = 0;
        }
    }

    if(diagonais[1] == n){ //preprocessamento da diagonal secundaria
        //percorrer a diagonal e preencher a 1
        for (int i = 0; i < n; i++) {
            array[i][n-i-1] = 1;
        }
    }

    int totalBlacks = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(array[i][j] == 1){
                totalBlacks++;
            }
        }
    }

    if(totalBlacks == pretos){
        //put all 9's in the array to 2´s
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if(array[i][j] == 9){
                    array[i][j] = 0;
                }
            }
        }
    }


    memcpy(res.qr, array, sizeof(res.qr));

}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int qr;

    int valid = 0;

    int numero;

    cin >> qr;

    for (int i = 0; i < qr; i++) //cada qr code
    {
        valid = 0;
        int array[30][30] = {0}; // inicializa a matriz com zeros
        int n; //tamanho do array
        int pretos = 0;
        int colunas = 0;
        int quadrantes = 0;

        int valida = 0;

        cin >> n;

        if (n > 30 || n < 2) //verifica o tamanho da matriz
        {
            valida = 1;
        }

        vector<int> lb;
        vector<int> cb;
        vector<int> lt;
        vector<int> ct;
        vector<int> qb;
        vector<int> db;

        for (int j = 0; j < n; j++) //leitura das linhas
        {
            cin >> numero;
            lb.push_back(numero);
            pretos += numero;
        }

        for (int j = 0; j < n; j++) //leitura das colunas
        {
            cin >> numero;
            cb.push_back(numero);
            colunas += numero;
        }


        for (int j = 0; j < n; j++) //leitura das diferenças de linhas
        {
            cin >> numero;
            lt.push_back(numero);
        }

        for (int j = 0; j < n; j++) //leitura das diferenças de colunas
        {
            cin >> numero;
            ct.push_back(numero);
        }

        for (int j = 0; j < 4; j++) //leitura dos quadrantes
        {
            cin >> numero;
            qb.push_back(numero);
            quadrantes += numero;
        }

        for (int j = 0; j < 2; j++) //leitura das diagonais
        {
            cin >> numero;
            db.push_back(numero);
        }

        Resultado res;
        res.n = valid;

        preprocessamento(n, array, lb, cb, db, lt, ct, qb, pretos, res);

        printArray(res.qr, n);
    }
}