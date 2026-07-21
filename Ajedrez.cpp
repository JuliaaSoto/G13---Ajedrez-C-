#include <iostream>
#include <vector>

using namespace std;

vector<vector<char>> tablero(8, vector<char>(8));
bool turnoBlanco = true;

bool peon(int fila_origen, int fila_destino,
          int columna_origen, int columna_destino);

bool torre(int fila_origen, int fila_destino,
           int columna_origen, int columna_destino);

bool caballo(int fila_origen, int fila_destino,
             int columna_origen, int columna_destino);

bool alfil(int fila_origen, int fila_destino,
           int columna_origen, int columna_destino);

bool rey(int fila_origen, int fila_destino,
         int columna_origen, int columna_destino);

bool reina(int fila_origen, int fila_destino,
           int columna_origen, int columna_destino);
void promocionPeon();
void mostrarTablero();
                      
bool reyBlancoMovido = false;
bool reyNegroMovido = false;

bool torreBlancaIzquierdaMovida = false;
bool torreBlancaDerechaMovida = false;

bool torreNegraIzquierdaMovida = false;
bool torreNegraDerechaMovida = false;

bool esPiezaBlanca(char pieza){

    return pieza >= 'A' && pieza <= 'Z';

}


bool esPiezaNegra(char pieza){

    return pieza >= 'a' && pieza <= 'z';

}

bool peon(int fila_origen, int fila_destino, int columna_origen, int columna_destino){

    int movimiento = fila_destino - fila_origen;
    bool validacion = true;

    if (turnoBlanco){

        if (movimiento == -2){

            if (columna_origen == columna_destino){

                if (fila_origen == 6){

                    if (tablero[fila_origen - 1][columna_origen] == '.'){

                        if(tablero[fila_destino][columna_destino] == '.'){

                            return true;

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

                    return true;

                }else{

                    validacion = false;
            
                }

            }else if (columna_destino == columna_origen+1 || columna_destino == columna_origen-1){

                if(islower(tablero[fila_destino][columna_destino])){

                    return true;

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

                            return true;

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

                    return true;

                }else{

                    validacion = false;
            
                }

            }else if (columna_destino == columna_origen+1 || columna_destino == columna_origen-1){

                if(isupper(tablero[fila_destino][columna_destino])){

                    return true;

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

    return validacion;
}

bool torre(int fila_origen, int fila_destino, int columna_origen, int columna_destino){
	
    bool validacion = true;
    
    // La torre debe moverse únicamente en línea recta

	if(fila_origen != fila_destino && columna_origen != columna_destino){

   		return false;

	}else{


        // Movimiento horizontal
        if(fila_origen == fila_destino){

            if(columna_destino > columna_origen){

                for(int i = columna_origen + 1; i < columna_destino; i++){

                    if(tablero[fila_origen][i] != '.'){

                        return false;

                    }

                }

            }else{

                for(int i = columna_destino + 1; i < columna_origen; i++){

                    if(tablero[fila_origen][i] != '.'){

                        return false;

                    }

                }

            }

        }

        // Movimiento vertical
        if(columna_origen == columna_destino){

            if(fila_destino > fila_origen){

                for(int i = fila_origen + 1; i < fila_destino; i++){

                    if(tablero[i][columna_origen] != '.'){

                        return false;

                    }

                }

            }else{

                for(int i = fila_destino + 1; i < fila_origen; i++){

                    if(tablero[i][columna_origen] != '.'){

                        return false;

                    }

                }

            }

        }
        // Si el camino está libre, revisar la casilla destino
        
        if(validacion){

            if(turnoBlanco){

                // No puede capturar una pieza blanca
                if(isupper(tablero[fila_destino][columna_destino])){

                    return false;

                }else{
            	
				return true;
                }

            }else{

                // No puede capturar una pieza negra
                if(islower(tablero[fila_destino][columna_destino])){

                    return false;

                }else{
						
        			return true;


           		}

        	}

    }
    
    return false;
}
}
bool caballo(int fila_origen, int fila_destino, int columna_origen, int columna_destino){

    bool validacion = true;

    int diferenciaFilas = abs(fila_destino - fila_origen);
    int diferenciaColumnas = abs(columna_destino - columna_origen);

    // El caballo se mueve en forma de L
    if(!((diferenciaFilas == 2 && diferenciaColumnas == 1) ||
         (diferenciaFilas == 1 && diferenciaColumnas == 2))){

        validacion = false;

    }else{

        if(turnoBlanco){

            // No puede capturar una pieza blanca
            if(isupper(tablero[fila_destino][columna_destino])){

                validacion = false;

            }else{

                return true;

            }

        }else{

            // No puede capturar una pieza negra
            if(islower(tablero[fila_destino][columna_destino])){

                validacion = false;

            }else{

               return true;

            }

        }

    }

    return validacion;
}


bool alfil(int fila_origen, int fila_destino, int columna_origen, int columna_destino){

    bool validacion = true;

    int diferenciaFilas = abs(fila_destino - fila_origen);
    int diferenciaColumnas = abs(columna_destino - columna_origen);

    // El alfil solo puede moverse en diagonal
    if(diferenciaFilas != diferenciaColumnas){

        validacion = false;

    }else{

        int pasoFila;
        int pasoColumna;

        if(fila_destino > fila_origen){

            pasoFila = 1;

        }else{

            pasoFila = -1;

        }

        if(columna_destino > columna_origen){

            pasoColumna = 1;

        }else{

            pasoColumna = -1;

        }

        int fila = fila_origen + pasoFila;
        int columna = columna_origen + pasoColumna;

        while(fila != fila_destino && columna != columna_destino){

            if(tablero[fila][columna] != '.'){

                validacion = false;

            }

            fila += pasoFila;
            columna += pasoColumna;

        }

        if(validacion){

            if(turnoBlanco){

                // No puede capturar una pieza blanca
                if(isupper(tablero[fila_destino][columna_destino])){

                    validacion = false;

                }else{

                    return true;

                }

            }else{

                // No puede capturar una pieza negra
                if(islower(tablero[fila_destino][columna_destino])){

                    validacion = false;

                }else{

                    return true;

                }

            }

        }

    }

    return validacion;
}

bool rey(int fila_origen, int fila_destino, int columna_origen, int columna_destino){

    bool validacion = true;

    int diferenciaFilas = abs(fila_destino - fila_origen);
    int diferenciaColumnas = abs(columna_destino - columna_origen);

    // El rey solo puede moverse una casilla
    if(diferenciaFilas > 1 || diferenciaColumnas > 1){

        validacion = false;

    }else{

        if(turnoBlanco){

            // No puede capturar una pieza blanca
            if(isupper(tablero[fila_destino][columna_destino])){

                validacion = false;

            }else{

                return true;

            }

        }else{

            // No puede capturar una pieza negra
            if(islower(tablero[fila_destino][columna_destino])){

                validacion = false;

            }else{

                return true;

            }

        }

    }

    return validacion;
}

bool casillaAtacada(int fila, int columna, bool porBlancas){
    if(porBlancas){

        if(fila + 1 < 8){

            if(columna - 1 >= 0){

                if(tablero[fila + 1][columna - 1] == 'P'){

                    return true;

                }

            }

            if(columna + 1 < 8){

                if(tablero[fila + 1][columna + 1] == 'P'){

                    return true;

                }

            }

        }

    }else{

        if(fila - 1 >= 0){

            if(columna - 1 >= 0){

                if(tablero[fila - 1][columna - 1] == 'p'){

                    return true;

                }

            }

            if(columna + 1 < 8){

                if(tablero[fila - 1][columna + 1] == 'p'){

                    return true;

                }

            }

        }

    }

	
	int movimientoFila[8] = {-2,-2,-1,-1,1,1,2,2};
	int movimientoColumna[8] = {-1,1,-2,2,-2,2,-1,1};

	for(int i = 0; i < 8; i++){

    	int nuevaFila = fila + movimientoFila[i];
		int nuevaColumna = columna + movimientoColumna[i];

   		if(nuevaFila >= 0 && nuevaFila < 8 &&
      	nuevaColumna >= 0 && nuevaColumna < 8){

    	if(porBlancas){

            if(tablero[nuevaFila][nuevaColumna] == 'N'){

                return true;

            }

        }else{

            if(tablero[nuevaFila][nuevaColumna] == 'n'){

                return true;

            }

        }

    }

}
for(int i = -1; i <= 1; i++){

    for(int j = -1; j <= 1; j++){

        if(i == 0 && j == 0){

            continue;

        }

        int nuevaFila = fila + i;
        int nuevaColumna = columna + j;

        if(nuevaFila >= 0 && nuevaFila < 8 &&
           nuevaColumna >= 0 && nuevaColumna < 8){

            if(porBlancas){

                if(tablero[nuevaFila][nuevaColumna] == 'K'){

                    return true;

                }

            }else{

                if(tablero[nuevaFila][nuevaColumna] == 'k'){

                    return true;

                }

            }

        }

    }

}
for(int i = fila - 1; i >= 0; i--){

    if(tablero[i][columna] != '.'){

        if(porBlancas){

            if(tablero[i][columna] == 'R' || tablero[i][columna] == 'Q'){

                return true;

            }

        }else{

            if(tablero[i][columna] == 'r' || tablero[i][columna] == 'q'){

                return true;

            }

        }

        break;

    }

}

// Abajo
for(int i = fila + 1; i < 8; i++){

    if(tablero[i][columna] != '.'){

        if(porBlancas){

            if(tablero[i][columna] == 'R' || tablero[i][columna] == 'Q'){

                return true;

            }

        }else{

            if(tablero[i][columna] == 'r' || tablero[i][columna] == 'q'){

                return true;

            }

        }

        break;

    }

}

// Izquierda
for(int i = columna - 1; i >= 0; i--){

    if(tablero[fila][i] != '.'){

        if(porBlancas){

            if(tablero[fila][i] == 'R' || tablero[fila][i] == 'Q'){

                return true;

            }

        }else{

            if(tablero[fila][i] == 'r' || tablero[fila][i] == 'q'){

                return true;

            }

        }

        break;

    }

}

// Derecha
for(int i = columna + 1; i < 8; i++){

    if(tablero[fila][i] != '.'){

        if(porBlancas){

            if(tablero[fila][i] == 'R' || tablero[fila][i] == 'Q'){

                return true;

            }

        }else{

            if(tablero[fila][i] == 'r' || tablero[fila][i] == 'q'){

                return true;

            }

        }

        break;

    }

}

// Arriba - Izquierda
for(int i = 1; fila - i >= 0 && columna - i >= 0; i++){

    if(tablero[fila - i][columna - i] != '.'){

        if(porBlancas){

            if(tablero[fila - i][columna - i] == 'B' || tablero[fila - i][columna - i] == 'Q'){

                return true;

            }

        }else{

            if(tablero[fila - i][columna - i] == 'b' || tablero[fila - i][columna - i] == 'q'){

                return true;

            }

        }

        break;

    }

}

// Arriba - Derecha
for(int i = 1; fila - i >= 0 && columna + i < 8; i++){

    if(tablero[fila - i][columna + i] != '.'){

        if(porBlancas){

            if(tablero[fila - i][columna + i] == 'B' || tablero[fila - i][columna + i] == 'Q'){

                return true;

            }

        }else{

            if(tablero[fila - i][columna + i] == 'b' || tablero[fila - i][columna + i] == 'q'){

                return true;

            }

        }

        break;

    }

}

// Abajo - Izquierda
for(int i = 1; fila + i < 8 && columna - i >= 0; i++){

    if(tablero[fila + i][columna - i] != '.'){

        if(porBlancas){

            if(tablero[fila + i][columna - i] == 'B' || tablero[fila + i][columna - i] == 'Q'){

                return true;

            }

        }else{

            if(tablero[fila + i][columna - i] == 'b' || tablero[fila + i][columna - i] == 'q'){

                return true;

            }

        }

        break;

    }

}

// Abajo - Derecha
for(int i = 1; fila + i < 8 && columna + i < 8; i++){

    if(tablero[fila + i][columna + i] != '.'){

        if(porBlancas){

            if(tablero[fila + i][columna + i] == 'B' || tablero[fila + i][columna + i] == 'Q'){

                return true;

            }

        }else{

            if(tablero[fila + i][columna + i] == 'b' || tablero[fila + i][columna + i] == 'q'){

                return true;

            }

        }

        break;

    }

}
    return false;

}

bool reyEnJaque(bool reyBlanco){

    int filaRey;
    int columnaRey;

    // Buscar el rey en el tablero
    bool encontrado = false;
    for(int i = 0; i < 8 && !encontrado; i++){

        for(int j = 0; j < 8; j++){

            if(reyBlanco){

                if(tablero[i][j] == 'K'){

                    filaRey = i;
                    columnaRey = j;
                    encontrado = true;
                    break;

                }

            }else{

                if(tablero[i][j] == 'k'){

                    filaRey = i;
                    columnaRey = j;
					encontrado = true;
					break;
					
                }

            }

        }

    }

    // Verificar si la casilla del rey está atacada
    if(!encontrado){

    return false;

	}
    if(reyBlanco){

        return casillaAtacada(filaRey, columnaRey, false);

    }else{

        return casillaAtacada(filaRey, columnaRey, true);

    }

}

bool movimientoValido(int filaOrigen, int filaDestino,
                      int columnaOrigen, int columnaDestino){
	
	if(filaOrigen < 0 || filaOrigen > 7 ||
   filaDestino < 0 || filaDestino > 7 ||
   columnaOrigen < 0 || columnaOrigen > 7 ||
   columnaDestino < 0 || columnaDestino > 7){

    return false;

	}
	
	char pieza = tablero[filaOrigen][columnaOrigen];
	
	if(pieza == '.'){

    return false;

	}
	


    if(pieza == 'P' || pieza == 'p'){

        return peon(filaOrigen,filaDestino,
                    columnaOrigen,columnaDestino);

    }

    else if(pieza == 'R' || pieza == 'r'){

          return torre(filaOrigen, filaDestino,
                 columnaOrigen, columnaDestino);
    }

    else if(pieza == 'N' || pieza == 'n'){

        return caballo(filaOrigen,filaDestino,
                       columnaOrigen,columnaDestino);

    }

    else if(pieza == 'B' || pieza == 'b'){

        return alfil(filaOrigen,filaDestino,
                     columnaOrigen,columnaDestino);

    }

    else if(pieza == 'Q' || pieza == 'q'){

        return reina(filaOrigen,filaDestino,
                     columnaOrigen,columnaDestino);

    }

	    else if(pieza == 'K' || pieza == 'k'){

        	return rey(filaOrigen,filaDestino,
                   columnaOrigen,columnaDestino);

    }

    return false;

}


bool tieneMovimientosLegales(bool blancas){

    bool turnoAnterior = turnoBlanco;


    // Simulamos el turno del jugador
    turnoBlanco = blancas;


    for(int filaOrigen = 0; filaOrigen < 8; filaOrigen++){

        for(int columnaOrigen = 0; columnaOrigen < 8; columnaOrigen++){


            char pieza = tablero[filaOrigen][columnaOrigen];


            // Buscar piezas del jugador
            if(blancas && !esPiezaBlanca(pieza))
                continue;


            if(!blancas && !esPiezaNegra(pieza))
                continue;



            for(int filaDestino = 0; filaDestino < 8; filaDestino++){

                for(int columnaDestino = 0; columnaDestino < 8; columnaDestino++){
					
					// No tiene sentido intentar mover una pieza a la misma casilla
       				if(filaOrigen == filaDestino && columnaOrigen == columnaDestino){

            			continue;

        			}
	
					// No puede capturar una pieza del mismo color
					char destino = tablero[filaDestino][columnaDestino];

					if(blancas){

					    if(isupper(destino)){

    					   continue;

   					}

					}else{

   					 	if(islower(destino)){

       						 continue;

    					}

					}

                    if(movimientoValido(filaOrigen, filaDestino, columnaOrigen, columnaDestino)){


                        char capturada =
                        tablero[filaDestino][columnaDestino];


                        // Hacer movimiento temporal

                        tablero[filaDestino][columnaDestino] = pieza;

                        tablero[filaOrigen][columnaOrigen] = '.';



                        bool sigueEnJaque = reyEnJaque(blancas);



                        // Deshacer

                        tablero[filaOrigen][columnaOrigen]=pieza;

                        tablero[filaDestino][columnaDestino]=capturada;

						//cout << "Movimiento encontrado: "<< pieza << " de (" << filaOrigen << "," << columnaOrigen<< ") a ("<< filaDestino << "," << columnaDestino<< ")" << endl;

                        if(!sigueEnJaque){
							

							
                            turnoBlanco = turnoAnterior;

                            return true;

                        }

                    }


                }

            }


        }

    }


    turnoBlanco = turnoAnterior;


    return false;

}

bool jaqueMate(bool blancas){

    if(reyEnJaque(blancas) && !tieneMovimientosLegales(blancas)){

        return true;

    }


    return false;

}

bool enroque(int filaOrigen, int filaDestino, int columnaOrigen, int columnaDestino){

     // Verificar que el rey no se haya movido
    if(turnoBlanco){

        if(reyBlancoMovido){

            cout<<"El rey ya se movió"<<endl;
            return false;

        }

    }else{

        if(reyNegroMovido){

            cout<<"El rey ya se movió"<<endl;
            return false;

        }

    }

    // Verificar que el rey no esté en jaque
    if(turnoBlanco){

        if(reyEnJaque(true)){

            cout<<"No puedes enrocar estando en jaque"<<endl;
            return false;

        }

    }else{

        if(reyEnJaque(false)){

            cout<<"No puedes enrocar estando en jaque"<<endl;
            return false;

        }

    }

    // Aquí seguiremos en el siguiente paso
	// Determinar si es enroque corto o largo
	if(columnaDestino > columnaOrigen){

    // Enroque corto
    if(turnoBlanco){

        if(torreBlancaDerechaMovida){

            cout<<"La torre ya se movió"<<endl;
            return false;

        }

        if(tablero[7][5] != '.' || tablero[7][6] != '.'){

            cout<<"Hay piezas entre el rey y la torre"<<endl;
            return false;

        }
        
        if(casillaAtacada(7,5,false) || casillaAtacada(7,6,false)){

   		cout<<"El rey pasaría por una casilla atacada"<<endl;
   		return false;

		}
		// Realizar el enroque corto blanco
		tablero[7][6] = 'K';
		tablero[7][5] = 'R';

		tablero[7][4] = '.';
		tablero[7][7] = '.';

		reyBlancoMovido = true;
		torreBlancaDerechaMovida = true;

		return true;
    }else{

    if(torreNegraDerechaMovida){

        cout<<"La torre ya se movió"<<endl;
        return false;

    }

    if(tablero[0][5] != '.' || tablero[0][6] != '.'){

        cout<<"Hay piezas entre el rey y la torre"<<endl;
        return false;

    }

    if(casillaAtacada(0,5,true) || casillaAtacada(0,6,true)){

        cout<<"El rey pasaría por una casilla atacada"<<endl;
        return false;

    }

    // Realizar el enroque corto negro
    tablero[0][6] = 'k';
    tablero[0][5] = 'r';

    tablero[0][4] = '.';
    tablero[0][7] = '.';

    reyNegroMovido = true;
    torreNegraDerechaMovida = true;

    return true;

}
}else{

    // Enroque largo

    if(turnoBlanco){

        // Verificar que la torre izquierda no se haya movido
        if(torreBlancaIzquierdaMovida){

            cout<<"La torre ya se movió"<<endl;
            return false;

        }

        // Deben estar libres las casillas entre rey y torre
        if(tablero[7][1] != '.' ||
           tablero[7][2] != '.' ||
           tablero[7][3] != '.'){

            cout<<"Hay piezas entre el rey y la torre"<<endl;
            return false;

        }

        // El rey no puede pasar por una casilla atacada
        if(casillaAtacada(7,3,false) ||
           casillaAtacada(7,2,false)){

            cout<<"El rey pasaría por una casilla atacada"<<endl;
            return false;

        }

        // Realizar el enroque
        tablero[7][2] = 'K';
        tablero[7][3] = 'R';

        tablero[7][4] = '.';
        tablero[7][0] = '.';

        reyBlancoMovido = true;
        torreBlancaIzquierdaMovida = true;

        return true;

    }else{

    if(torreNegraIzquierdaMovida){

        cout<<"La torre ya se movió"<<endl;
        return false;

    }

    if(tablero[0][1] != '.' ||
       tablero[0][2] != '.' ||
       tablero[0][3] != '.'){

        cout<<"Hay piezas entre el rey y la torre"<<endl;
        return false;

    }

    if(casillaAtacada(0,3,true) ||
       casillaAtacada(0,2,true)){

        cout<<"El rey pasaría por una casilla atacada"<<endl;
        return false;

    }

    // Realizar el enroque largo negro
    tablero[0][2] = 'k';
    tablero[0][3] = 'r';

    tablero[0][4] = '.';
    tablero[0][0] = '.';

    reyNegroMovido = true;
    torreNegraIzquierdaMovida = true;

    return true;

}

}

    return false;

}

void deshacerMovimiento(int fila_origen, int fila_destino,
                        int columna_origen, int columna_destino,
                        char piezaMovida, char piezaCapturada){

    // Regresar la pieza a su casilla original
    tablero[fila_origen][columna_origen] = piezaMovida;

    // Restaurar la pieza que había en el destino
    tablero[fila_destino][columna_destino] = piezaCapturada;

}

bool simularMovimiento(int filaOrigen, int columnaOrigen,
                       int filaDestino, int columnaDestino){

    char pieza = tablero[filaOrigen][columnaOrigen];

    // No hay pieza
    if(pieza == '.'){
        return false;
    }

    // Guardar la pieza capturada
    char capturada = tablero[filaDestino][columnaDestino];

    // Simular movimiento
    tablero[filaDestino][columnaDestino] = pieza;
    tablero[filaOrigen][columnaOrigen] = '.';

    return true;
}

void deshacerEnroque(bool blancas, bool corto){

    if(blancas){

        if(corto){

            // Rey
            tablero[7][4] = 'K';
            tablero[7][6] = '.';

            // Torre
            tablero[7][7] = 'R';
            tablero[7][5] = '.';

        }else{

            // Rey
            tablero[7][4] = 'K';
            tablero[7][2] = '.';

            // Torre
            tablero[7][0] = 'R';
            tablero[7][3] = '.';

        }

    }else{

        if(corto){

            // Rey
            tablero[0][4] = 'k';
            tablero[0][6] = '.';

            // Torre
            tablero[0][7] = 'r';
            tablero[0][5] = '.';

        }else{

            // Rey
            tablero[0][4] = 'k';
            tablero[0][2] = '.';

            // Torre
            tablero[0][0] = 'r';
            tablero[0][3] = '.';

        }

    }

}

bool reina(int fila_origen, int fila_destino, int columna_origen, int columna_destino){

    bool validacion = true;

    // Movimiento de torre
    if(fila_origen == fila_destino || columna_origen == columna_destino){

        if(fila_origen == fila_destino){

            if(columna_destino > columna_origen){

                for(int i = columna_origen + 1; i < columna_destino; i++){

                    if(tablero[fila_origen][i] != '.'){

                        validacion = false;

                    }

                }

            }else{

                for(int i = columna_destino + 1; i < columna_origen; i++){

                    if(tablero[fila_origen][i] != '.'){

                        validacion = false;

                    }

                }

            }

        }

        if(columna_origen == columna_destino){

            if(fila_destino > fila_origen){

                for(int i = fila_origen + 1; i < fila_destino; i++){

                    if(tablero[i][columna_origen] != '.'){

                        validacion = false;

                    }

                }

            }else{

                for(int i = fila_destino + 1; i < fila_origen; i++){

                    if(tablero[i][columna_origen] != '.'){

                        validacion = false;

                    }

                }

            }

        }

    }

    // Movimiento de alfil
    else if(abs(fila_destino - fila_origen) == abs(columna_destino - columna_origen)){

        int pasoFila;
        int pasoColumna;

        if(fila_destino > fila_origen){

            pasoFila = 1;

        }else{

            pasoFila = -1;

        }

        if(columna_destino > columna_origen){

            pasoColumna = 1;

        }else{

            pasoColumna = -1;

        }

        int fila = fila_origen + pasoFila;
        int columna = columna_origen + pasoColumna;

        while(fila != fila_destino && columna != columna_destino){

            if(tablero[fila][columna] != '.'){

                validacion = false;

            }

            fila += pasoFila;
            columna += pasoColumna;

        }

    }else{

        validacion = false;

    }

    if(validacion){

        if(turnoBlanco){

            if(isupper(tablero[fila_destino][columna_destino])){

                validacion = false;

            }else{

                return true; 

            }

        }else{

            if(islower(tablero[fila_destino][columna_destino])){

                validacion = false;

            }else{

                return true;
            }

        }

    }
	return validacion;
}

void promocionPeon(){

    // Revisar peones blancos
    for(int j = 0; j < 8; j++){

        if(tablero[0][j] == 'P'){

            char opcion;

            cout << "¡Promoción del peón blanco!" << endl;
            cout << "Q = Reina" << endl;
            cout << "R = Torre" << endl;
            cout << "B = Alfil" << endl;
            cout << "N = Caballo" << endl;
            cout << "Seleccione: ";

            cin >> opcion;

            opcion = toupper(opcion);

            if(opcion == 'Q')
                tablero[0][j] = 'Q';

            else if(opcion == 'R')
                tablero[0][j] = 'R';

            else if(opcion == 'B')
                tablero[0][j] = 'B';

            else if(opcion == 'N')
                tablero[0][j] = 'N';

            else{

                cout << "Opción inválida. Se promociona a reina." << endl;
                tablero[0][j] = 'Q';

            }

        }

    }

    // Revisar peones negros
    for(int j = 0; j < 8; j++){

        if(tablero[7][j] == 'p'){

            char opcion;

            cout << "¡Promoción del peón negro!" << endl;
            cout << "q = Reina" << endl;
            cout << "r = Torre" << endl;
            cout << "b = Alfil" << endl;
            cout << "n = Caballo" << endl;
            cout << "Seleccione: ";

            cin >> opcion;

            opcion = tolower(opcion);

            if(opcion == 'q')
                tablero[7][j] = 'q';

            else if(opcion == 'r')
                tablero[7][j] = 'r';

            else if(opcion == 'b')
                tablero[7][j] = 'b';

            else if(opcion == 'n')
                tablero[7][j] = 'n';

            else{

                cout << "Opción inválida. Se promociona a reina." << endl;
                tablero[7][j] = 'q';

            }

        }

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

                cout<<"Error, el primer carácter debe ser una letra entre a y h"<<endl;

            }

            if(origen[1] >= '1' && origen[1] <= '8'){

                columna_origen = origen[1];

            }else{

                cout<<"Error, el segundo carácter debe ser un numero entre 1 y 8"<<endl;

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

                cout<<"Error, el primer carácter debe ser una letra entre a y h"<<endl;

            }

            if(destino[1] >= '1' && destino[1] <= '8'){

                columna_destino = destino[1];

            }else{

                cout<<"Error, el segundo carácter debe ser un número entre 1 y 8"<<endl;

            }
        }

    }while(((destino.length() != 2) || (destino[0] < 'a' || destino[0] > 'h') || (destino[1] < '1' || destino[1] > '8')));

    int filaOrigen = 8 - (columna_origen - '0');
    int columnaOrigen = tolower(fila_origen) - 'a';

    int filaDestino = 8 - (columna_destino - '0');
    int columnaDestino = tolower(fila_destino) - 'a';

    char pieza = tablero[filaOrigen][columnaOrigen];
    
    if(pieza == '.'){

    	cout << "No hay ninguna pieza en esta casilla" << endl;
    	return;

	}
	
    if(turnoBlanco && islower(pieza)){

    cout<<"Es el turno de las blancas"<<endl;
    return;

	}

	if(!turnoBlanco && isupper(pieza)){

  		cout<<"Es el turno de las negras"<<endl;
   		return;

	}
    	if(filaOrigen == filaDestino && columnaOrigen == columnaDestino){

    	cout<<"No puedes mover una pieza a la misma casilla"<<endl;
   		return;

	}
    // Guardar el estado antes del movimiento
	char piezaMovida = tablero[filaOrigen][columnaOrigen];
	char piezaCapturada = tablero[filaDestino][columnaDestino];

	bool movimientoRealizado = false;
	bool fueEnroque = false;
    char piezaDestino = tablero[filaDestino][columnaDestino];


if(turnoBlanco && isupper(piezaDestino)){

    cout<<"No puedes capturar una pieza tuya"<<endl;
    return;

}


if(!turnoBlanco && islower(piezaDestino)){

    cout<<"No puedes capturar una pieza tuya"<<endl;
    return;

}

if((pieza == 'K' || pieza == 'k') && abs(columnaDestino - columnaOrigen) == 2){

    movimientoRealizado = enroque(filaOrigen, filaDestino,
                                  columnaOrigen, columnaDestino);

    if(movimientoRealizado){

    	fueEnroque = true;

	}

}else{

    movimientoRealizado = movimientoValido(filaOrigen, filaDestino,
                                           columnaOrigen, columnaDestino);

}

if(!movimientoRealizado){

    cout<<"Movimiento inválido: Esa pieza no puede moverse a esa casilla"<<endl;
    return;

}

    if(movimientoRealizado){

    if(!fueEnroque){

        tablero[filaDestino][columnaDestino] = piezaMovida;
        tablero[filaOrigen][columnaOrigen] = '.';
		
		
    }
        
    if(piezaMovida == 'R'){

        if(filaOrigen == 7 && columnaOrigen == 0)
            torreBlancaIzquierdaMovida = true;

        if(filaOrigen == 7 && columnaOrigen == 7)
            torreBlancaDerechaMovida = true;

    }

    if(piezaMovida == 'r'){

        if(filaOrigen == 0 && columnaOrigen == 0)
            torreNegraIzquierdaMovida = true;

        if(filaOrigen == 0 && columnaOrigen == 7)
            torreNegraDerechaMovida = true;

    }

    // Actualizar si se movió un rey
    if(piezaMovida == 'K'){

        reyBlancoMovido = true;

    }

    if(piezaMovida == 'k'){

        reyNegroMovido = true;

    }

}

if(movimientoRealizado){
	// Revisar si el jugador que movió dejó su propio rey en jaque
	if(turnoBlanco){

    // Acaba de mover el jugador blanco
    if(reyEnJaque(true)){

        if(fueEnroque){

        if(columnaDestino > columnaOrigen){

            deshacerEnroque(true,true);

        }else{

            deshacerEnroque(true,false);

        }

    }else{

        deshacerMovimiento(filaOrigen, filaDestino,
                           columnaOrigen, columnaDestino,
                           piezaMovida, piezaCapturada);

    }

    cout<<"Movimiento inválido: El rey blanco queda en jaque"<<endl;
    return;
    }

}else{

    // Acaba de mover el jugador negro
    if(reyEnJaque(false)){

        if(fueEnroque){

        if(columnaDestino > columnaOrigen){

            deshacerEnroque(false,true);

        }else{

            deshacerEnroque(false,false);

        }

    }else{

        deshacerMovimiento(filaOrigen, filaDestino,
                           columnaOrigen, columnaDestino,
                           piezaMovida, piezaCapturada);

    }

    cout<<"Movimiento inválido: El rey negro queda en jaque"<<endl;
    return;

    }

}

turnoBlanco = !turnoBlanco;
if(turnoBlanco){

    // Ahora juegan las blancas.
    // Revisar si el rey blanco está en jaque.

    if(reyEnJaque(true)){

    cout << "¡Jaque al rey blanco!" << endl;


    if(jaqueMate(true)){
        cout<<"¡¡JAQUE MATE!! Ganaron las negras"<<endl;
		
		mostrarTablero();
		
        exit(0);

    }

}

}else{

    // Ahora juegan las negras.

    if(reyEnJaque(false)){

    cout << "¡Jaque al rey negro!" << endl;


    if(jaqueMate(false)){
		
        cout<<"¡¡JAQUE MATE!! Ganaron las blancas"<<endl;
		
		mostrarTablero();
		
        exit(0);

    }

}

}
// Revisar si un peón llegó al final del tablero
        promocionPeon();
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

        for (int j = 0; j < 8; j++){

            cout<<tablero[i][j]<<" ";

        }

        cout<<endl;

    }

    cout<<endl;

}

void partida(){

    IniciarTablero();

    while(true){

        cout<<endl;

        mostrarTablero();

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

        cout<<"Escoja su opción: ";
        cin >> opcion;

        cout<<endl;

        if (opcion == 1){

            partida();

        }else if (opcion == 2){

            cout<<"Función no hecha bruh";
            cout<<endl;

        }else if (opcion == 3){

            cout<<"Gracias por jugar";
            cout<<endl;

        }else{

            cout<<"Debes escoger un número entre 1 y 3"<<endl;

        }

    }while(opcion < 1 || opcion > 3);

}


int main(){
	setlocale(LC_ALL, "Spanish");
    menu();

}
