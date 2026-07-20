#include <iostream>
#include <vector>

using namespace std;

vector<vector<char>> tablero(8, vector<char>(8));
bool turnoBlanco = true;
string JugadorBlancas;
string JugadorNegras;

void peon(int fila_origen, int fila_destino, int columna_origen, int columna_destino){

    int movimiento = fila_destino - fila_origen;
    bool validacion = true;

    if (turnoBlanco){

        if (movimiento == -2){

            if (columna_origen == columna_destino){

                if (fila_origen == 6){

                    if (tablero[fila_origen - 1][columna_origen] == '.'){

                        if(tablero[fila_destino][columna_destino] == '.'){

                            tablero[fila_destino][columna_destino] = tablero[fila_origen][columna_origen];
                            tablero[fila_origen][columna_origen] = '.';
                            turnoBlanco = false;

                        }else{

                            validacion = false;
            
                        }

                    }else{

                        validacion = false;

                    }

                }else{

                    validacion = false;

                }

            }else{

                validacion = false;

            }
        
        }else if(movimiento == -1){

            if (columna_origen == columna_destino){

                if(tablero[fila_destino][columna_destino] == '.'){

                    tablero[fila_destino][columna_destino] = tablero[fila_origen][columna_origen];
                    tablero[fila_origen][columna_origen] = '.';
                    turnoBlanco = false;

                }else{

                    validacion = false;
            
                }

            }else if (columna_destino == columna_origen+1 || columna_destino == columna_origen-1){

                if(islower(tablero[fila_destino][columna_destino])){

                    tablero[fila_destino][columna_destino] = tablero[fila_origen][columna_origen];
                    tablero[fila_origen][columna_origen] = '.';
                    turnoBlanco = false;

                }else{

                    validacion = false;

                }

            }else{

                validacion = false;

            }

        }else{

            validacion = false;

        }
        
    }else{

        if (movimiento == 2){

            if (columna_origen == columna_destino){

                if (fila_origen == 1){

                    if (tablero[fila_origen + 1][columna_origen] == '.'){

                        if(tablero[fila_destino][columna_destino] == '.'){

                            tablero[fila_destino][columna_destino] = tablero[fila_origen][columna_origen];
                            tablero[fila_origen][columna_origen] = '.';
                            turnoBlanco = true;

                        }else{

                            validacion = false;
            
                        }

                    }else{

                        validacion = false;

                    }

                }else{

                    validacion = false;

                }

            }else{

                validacion = false;

            }
        
        }else if(movimiento == 1){

            if (columna_origen == columna_destino){

                if(tablero[fila_destino][columna_destino] == '.'){

                    tablero[fila_destino][columna_destino] = tablero[fila_origen][columna_origen];
                    tablero[fila_origen][columna_origen] = '.';
                    turnoBlanco = true;

                }else{

                    validacion = false;
            
                }

            }else if (columna_destino == columna_origen+1 || columna_destino == columna_origen-1){

                if(isupper(tablero[fila_destino][columna_destino])){

                    tablero[fila_destino][columna_destino] = tablero[fila_origen][columna_origen];
                    tablero[fila_origen][columna_origen] = '.';
                    turnoBlanco = true;

                }else{

                    validacion = false;

                }

            }else{

                validacion = false;

            }

        }else{

            validacion = false;

        }

    }

    if(!validacion){

        cout<<"Movimiento invalido"<<endl;

    }
    
}


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

    int filaOrigen = 8 - (columna_origen - '0');
    int columnaOrigen = tolower(fila_origen) - 'a';

    int filaDestino = 8 - (columna_destino - '0');
    int columnaDestino = tolower(fila_destino) - 'a';

    char pieza = tablero[filaOrigen][columnaOrigen];
    

    if(pieza == 'P' || pieza == 'p'){

        peon(filaOrigen,filaDestino,columnaOrigen, columnaDestino  );

    }else if(pieza == 'R'){

        //torre()

    }else if(pieza == 'N'){

        //caballo()

    }else if(pieza == 'B'){

        //alfil()

    }else if(pieza == 'K'){

        //rey()

    }else if(pieza == 'Q'){

        //reina()

    }else if(pieza == '.'){

        cout<<"No hay ninguna pieza en esta casilla"<<endl;
        return;
        
    }else{

        cout<<"Movimiento invalido"<<endl;
        return;

    }

}



void IniciarTablero(){

    tablero = {
        {'r', 'n' , 'b' , 'q' , 'k' , 'b' , 'n' , 'r'},
        {'p', 'p' , 'p' , 'p' , 'p' , 'p' , 'p' , 'p'},
        {'.', '.' , '.' , '.' , '.' , '.' , '.' , '.'},
        {'.', '.' , '.' , '.' , '.' , '.' , '.' , '.'},
        {'.', '.' , '.' , '.' , '.' , '.' , '.' , '.'},
        {'.', '.' , '.' , '.' , '.' , '.' , '.' , '.'},
        {'P', 'P' , 'P' , 'P' , 'P' , 'P' , 'P' , 'P'},
        {'R', 'N' , 'B' , 'Q' , 'K' , 'B' , 'N' , 'R'}
    };

    cout<<endl;

}

void mostrarTablero(){

    for(int i = 0; i < 8 ; i++){

        if(i==0){

            cout<<"                            a   b   c   d   e   f   g   h "<<endl;
            cout<<"                          ---------------------------------"<<endl;

        }

        cout<<"                       "<<8-i<<"  ";

        for (int j = 0; j < 8; j++){

            if(j==0){

                cout<<"| ";

            }

            if(tablero[i][j] == '.'){

                cout<<"  | ";

            }else{

                cout<<tablero[i][j]<<" "<<"|"<<" ";

            }
                

        }

        cout<<" "<<8-i<<endl;;

        cout<<"                          ---------------------------------"<<endl;

        if(i==7){

            cout<<"                            a   b   c   d   e   f   g   h "<<endl;

        }
        
    }

    cout<<endl;

}

void partida(){

    cout<<"Ingrese el nombre del jugador de las blancas (porfavor no agregar espacios): ";
    cin>>JugadorBlancas;

    cout<<"Ingrese el nombre del jugador de las negras (porfavor no agregar espacios): ";
    cin>>JugadorNegras;

    IniciarTablero();

    while(true){

        cout<<endl;

        mostrarTablero();

        if(turnoBlanco){

            cout<<"Turno de los blancos ("<<JugadorBlancas<<")";

        }else{

            cout<<"Turno de los negros ("<<JugadorNegras<<")";

        }

        cout<<endl;

        movimiento();

    }

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

            partida();

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