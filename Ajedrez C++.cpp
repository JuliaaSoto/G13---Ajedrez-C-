#include <iostream>
#include <vector>
#include <cctype>

using namespace std;

void movimiento (){

    string origen;
    string destino;
    char fila_origen;
    char fila_destino;
    char columna_origen;
    char columna_destino;
    bool captura = false;

    do{

        cout<<"Ingrese su casilla de origen: ";
        cin>>origen;

        if(origen.length() != 2){

            cout<<"Error, La casilla debe tener exactamente 2 caracteres"<<endl;

        }else{

            if(origen[0] >= 'a' && origen[0] <= 'h'){

                fila_origen = origen[0];

            }else{

                cout<<"Error, el primer digito debe ser una letra entre a y h"<<endl;

            }

            if(origen[1] >= '1' && origen[1] <= '8'){

                columna_origen = origen[1];

            }else{

                cout<<"Error, el segundo digito debe ser un numero entre 1 y 8"<<endl;

            }
        }

    }while(((origen.length() != 2) || (origen[0] < 'a' || origen[0] > 'h') || (origen[1] < '1' || origen[1] > '8')));

    cout<<endl;

    do{

        cout<<"Ingrese su casilla de destino: ";
        cin>>destino;

        if(destino.length() != 2){

            cout<<"Error, La casilla debe tener exactamente 2 caracteres"<<endl;

        }else{

            if(destino[0] >= 'a' && destino[0] <= 'h'){

                fila_destino = destino[0];

            }else{

                cout<<"Error, el primer digito debe ser una letra entre a y h"<<endl;

            }

            if(destino[1] >= '1' && destino[1] <= '8'){

                columna_destino = destino[1];

            }else{

                cout<<"Error, el segundo digito debe ser un numero entre 1 y 8"<<endl;

            }
        }

    }while(((destino.length() != 2) || (destino[0] < 'a' || destino[0] > 'h') || (destino[1] < '1' || destino[1] > '8')));

}

void IniciarTablero(){

    vector <vector<char>> tablero = {

        {'r', 'n' , 'b' , 'q' , 'k' , 'b' , 'n' , 'r'},
        {'p', 'p' , 'p' , 'p' , 'p' , 'p' , 'p' , 'p'},
        {'.', '.' , '.' , '.' , '.' , '.' , '.' , '.'},
        {'.', '.' , '.' , '.' , '.' , '.' , '.' , '.'},
        {'.', '.' , '.' , '.' , '.' , '.' , '.' , '.'},
        {'.', '.' , '.' , '.' , '.' , '.' , '.' , '.'},
        {'P', 'P' , 'P' , 'P' , 'P' , 'P' , 'P' , 'P'},
        {'R', 'N' , 'B' , 'K' , 'Q' , 'B' , 'N' , 'R'}
    };

    cout<<endl;

    for(int i = 0; i < 8 ; i++){

        for (int j = 0; j < 8; j++){

            cout<<tablero[i][j]<<" ";

        }

        cout<<endl;

    }

    cout<<endl;

    movimiento();


}

void menu(){

    int opcion = 0;

    cout<<"========================================"<<endl;
    cout<<"             Ajedrez en C++             "<<endl;
    cout<<"========================================"<<endl;

    cout<<endl;

    cout<<"1. Iniciar (PvP)"<<endl;
    cout<<"2. Instrucciones"<<endl;
    cout<<"3. Salir"<<endl;

    do{

        cout<<"Escoga su opcion: ";
        cin >> opcion;

        cout<<endl;

        if (opcion == 1){

            IniciarTablero();

        }else if (opcion == 2){

            cout<<"Funcion no hecha bruh";
            cout<<endl;

        }else if (opcion == 3){

            cout<<"Gracias por jugar uwu";
            cout<<endl;

        }else{

            cout<<"Deber escoger un número entre 1 y 3"<<endl;

        }

    }while(opcion < 1 || opcion > 3);

}

int main(){

    menu();

}