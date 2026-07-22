#include <iostream>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

vector<vector<char>> tablero(8, vector<char>(8));
bool turnoBlanco = true;
string jugadorBlanco;
string jugadorNegro;

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
           
bool tablas(bool blancas);
bool materialInsuficiente();

bool capturaAlPasoDisponible = false;

int filaPeonAlPaso = -1;
int columnaPeonAlPaso = -1;

bool peonAlPasoBlanco;

void promocionPeon();
void mostrarTablero();
void actualizarPuntaje(string jugador, int puntosGanados);
void mostrarPuntajes();
void guardarMovimiento(string origen, string destino);
int contarMovimientos(ifstream &archivo);
                      
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

bool capturaAlPaso(int filaOrigen, int filaDestino,
                   int columnaOrigen, int columnaDestino){

    // Debe existir una captura al paso disponible
    if(!capturaAlPasoDisponible){

        return false;

    }

    char pieza = tablero[filaOrigen][columnaOrigen];

    // Solo los peones pueden hacer captura al paso
    if(pieza != 'P' && pieza != 'p'){

        return false;

    }

    // El movimiento debe ser diagonal de una casilla
    if(abs(columnaDestino - columnaOrigen) != 1){

        return false;

    }

    if(abs(filaDestino - filaOrigen) != 1){

        return false;

    }
	
    // La casilla de destino debe estar vacía
    if(tablero[filaDestino][columnaDestino] != '.'){

        return false;

    }

    // ===========================
    // Captura al paso de blancas
    // ===========================
    if(pieza == 'P'){
    	
		//Para blancas
		if(tablero[filaPeonAlPaso][columnaPeonAlPaso] != 'p'){

    		return false;

		}

        // El peón negro debe estar al lado
        if(filaOrigen != filaPeonAlPaso){

    		return false;

		}


		if(abs(columnaOrigen - columnaPeonAlPaso) != 1){

    		return false;

		}


		if(columnaDestino != columnaPeonAlPaso){

    		return false;

		}

        if(peonAlPasoBlanco){

            return false;

        }

        // Eliminar el peón negro
        tablero[filaPeonAlPaso][columnaPeonAlPaso] = '.';

        // Mover el peón blanco
        tablero[filaDestino][columnaDestino] = 'P';
        tablero[filaOrigen][columnaOrigen] = '.';

        capturaAlPasoDisponible = false;

        return true;

    }

    // ===========================
    // Captura al paso de negras
    // ===========================
    if(pieza == 'p'){
		
		//Para negras
		if(tablero[filaPeonAlPaso][columnaPeonAlPaso] != 'P'){

    		return false;

		}
	
        // El peón blanco debe estar al lado
        if(filaOrigen != filaPeonAlPaso){

    		return false;

		}


		if(abs(columnaOrigen - columnaPeonAlPaso) != 1){

    		return false;

		}


		if(columnaDestino != columnaPeonAlPaso){

    		return false;

		}

        if(!peonAlPasoBlanco){

            return false;

        }

        // Eliminar el peón blanco
        tablero[filaPeonAlPaso][columnaPeonAlPaso] = '.';

        // Mover el peón negro
        tablero[filaDestino][columnaDestino] = 'p';
        tablero[filaOrigen][columnaOrigen] = '.';

        capturaAlPasoDisponible = false;

        return true;

    }

    return false;

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

bool tablas(bool blancas){

    if(!reyEnJaque(blancas) &&
       !tieneMovimientosLegales(blancas)){

        return true;

    }

    return false;

}

bool materialInsuficiente(){

    int peones = 0;
    int torres = 0;
    int reinas = 0;

    int alfiles = 0;
    int caballos = 0;

    for(int i = 0; i < 8; i++){

        for(int j = 0; j < 8; j++){

            switch(tablero[i][j]){

                case 'P':
                case 'p':
                    peones++;
                    break;

                case 'R':
                case 'r':
                    torres++;
                    break;

                case 'Q':
                case 'q':
                    reinas++;
                    break;

                case 'B':
                case 'b':
                    alfiles++;
                    break;

                case 'N':
                case 'n':
                    caballos++;
                    break;

            }

        }

    }

    // Si existe un peón, torre o reina todavía es posible hacer mate.
    if(peones > 0 || torres > 0 || reinas > 0){

        return false;

    }

    // Rey contra rey
    if(alfiles == 0 && caballos == 0){

        return true;

    }

    // Rey + un alfil contra rey
    if(alfiles == 1 && caballos == 0){

        return true;

    }

    // Rey + un caballo contra rey
    if(alfiles == 0 && caballos == 1){

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
                        char piezaMovida, char piezaCapturada,
                        bool fueCapturaAlPaso){

    // Restaurar la pieza que se movió

    tablero[fila_origen][columna_origen] = piezaMovida;


    if(fueCapturaAlPaso){

        // Restaurar el peón eliminado

        if(piezaMovida == 'P'){

            tablero[fila_destino + 1][columna_destino] = 'p';

        }


        if(piezaMovida == 'p'){

            tablero[fila_destino - 1][columna_destino] = 'P';

        }


        // Vaciar la casilla donde terminó el peón

        tablero[fila_destino][columna_destino] = '.';


    }else{


        // Movimiento normal

        tablero[fila_destino][columna_destino] = piezaCapturada;


    }

}

void restaurarEstadoMovimiento(

    bool reyBlanco,
    bool reyNegro,

    bool torreBI,
    bool torreBD,

    bool torreNI,
    bool torreND){

    reyBlancoMovido = reyBlanco;
    reyNegroMovido = reyNegro;

    torreBlancaIzquierdaMovida = torreBI;
    torreBlancaDerechaMovida = torreBD;

    torreNegraIzquierdaMovida = torreNI;
    torreNegraDerechaMovida = torreND;

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

	// Guardar el estado de las banderas
	bool reyBlancoMovidoAnterior = reyBlancoMovido;
	bool reyNegroMovidoAnterior = reyNegroMovido;

	bool torreBlancaIzquierdaMovidaAnterior = torreBlancaIzquierdaMovida;
	bool torreBlancaDerechaMovidaAnterior = torreBlancaDerechaMovida;

	bool torreNegraIzquierdaMovidaAnterior = torreNegraIzquierdaMovida;
	bool torreNegraDerechaMovidaAnterior = torreNegraDerechaMovida;	

	if(piezaCapturada == 'R'){

    if(filaDestino == 7 && columnaDestino == 0)
        torreBlancaIzquierdaMovida = true;

    if(filaDestino == 7 && columnaDestino == 7)
        torreBlancaDerechaMovida = true;

}

if(piezaCapturada == 'r'){

    if(filaDestino == 0 && columnaDestino == 0)
        torreNegraIzquierdaMovida = true;

    if(filaDestino == 0 && columnaDestino == 7)
        torreNegraDerechaMovida = true;

}
	bool fueCapturaAlPaso = false;
	
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

if((pieza == 'K' || pieza == 'k') &&
   abs(columnaDestino - columnaOrigen) == 2){

    movimientoRealizado = enroque(filaOrigen,
                                  filaDestino,
                                  columnaOrigen,
                                  columnaDestino);

    if(movimientoRealizado){

        fueEnroque = true;

    }

}
else if(pieza == 'P' || pieza == 'p'){

    movimientoRealizado = capturaAlPaso(filaOrigen,
                                        filaDestino,
                                        columnaOrigen,
                                        columnaDestino);

    if(movimientoRealizado){

        fueCapturaAlPaso = true;

    }
    else{

        movimientoRealizado = movimientoValido(filaOrigen,
                                               filaDestino,
                                               columnaOrigen,
                                               columnaDestino);

    }

}
else{

    movimientoRealizado = movimientoValido(filaOrigen,
                                           filaDestino,
                                           columnaOrigen,
                                           columnaDestino);

}

if(!movimientoRealizado){

    cout<<"Movimiento inválido: Esa pieza no puede moverse a esa casilla"<<endl;
    return;

}

    if(movimientoRealizado){

    if(!fueEnroque && !fueCapturaAlPaso){

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
            restaurarEstadoMovimiento(

    reyBlancoMovidoAnterior,
    reyNegroMovidoAnterior,

    torreBlancaIzquierdaMovidaAnterior,
    torreBlancaDerechaMovidaAnterior,

    torreNegraIzquierdaMovidaAnterior,
    torreNegraDerechaMovidaAnterior);

        }else{

            deshacerEnroque(true,false);
			restaurarEstadoMovimiento(

    reyBlancoMovidoAnterior,
    reyNegroMovidoAnterior,

    torreBlancaIzquierdaMovidaAnterior,
    torreBlancaDerechaMovidaAnterior,

    torreNegraIzquierdaMovidaAnterior,
    torreNegraDerechaMovidaAnterior);
        }

    }else{

        deshacerMovimiento(filaOrigen, filaDestino,
                           columnaOrigen, columnaDestino,
                           piezaMovida, piezaCapturada, fueCapturaAlPaso);
                           
        restaurarEstadoMovimiento(

    reyBlancoMovidoAnterior,
    reyNegroMovidoAnterior,

    torreBlancaIzquierdaMovidaAnterior,
    torreBlancaDerechaMovidaAnterior,

    torreNegraIzquierdaMovidaAnterior,
    torreNegraDerechaMovidaAnterior);

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
            restaurarEstadoMovimiento(

    reyBlancoMovidoAnterior,
    reyNegroMovidoAnterior,

    torreBlancaIzquierdaMovidaAnterior,
    torreBlancaDerechaMovidaAnterior,

    torreNegraIzquierdaMovidaAnterior,
    torreNegraDerechaMovidaAnterior);

        }else{

            deshacerEnroque(false,false);
            restaurarEstadoMovimiento(

    reyBlancoMovidoAnterior,
    reyNegroMovidoAnterior,

    torreBlancaIzquierdaMovidaAnterior,
    torreBlancaDerechaMovidaAnterior,

    torreNegraIzquierdaMovidaAnterior,
    torreNegraDerechaMovidaAnterior);

        }

    }else{

        deshacerMovimiento(filaOrigen, filaDestino,
                           columnaOrigen, columnaDestino,
                           piezaMovida, piezaCapturada, fueCapturaAlPaso);
        
        restaurarEstadoMovimiento(

    reyBlancoMovidoAnterior,
    reyNegroMovidoAnterior,

    torreBlancaIzquierdaMovidaAnterior,
    torreBlancaDerechaMovidaAnterior,

    torreNegraIzquierdaMovidaAnterior,
    torreNegraDerechaMovidaAnterior);

    }

    cout<<"Movimiento inválido: El rey negro queda en jaque"<<endl;
    return;

    }

}

// Actualizar captura al paso solamente después de un movimiento válido

capturaAlPasoDisponible = false;

if((piezaMovida == 'P' || piezaMovida == 'p') &&
   abs(filaDestino - filaOrigen) == 2){

    capturaAlPasoDisponible = true;

    filaPeonAlPaso = filaDestino;
    columnaPeonAlPaso = columnaDestino;

    peonAlPasoBlanco = isupper(piezaMovida);

}

guardarMovimiento(origen,destino);
//Cambio de turno.
turnoBlanco = !turnoBlanco;

if(turnoBlanco){

    // Ahora juegan las blancas.
    // Revisar si el rey blanco está en jaque.

    if(reyEnJaque(true)){

    cout << "¡Jaque al rey blanco!" << endl;


    if(jaqueMate(true)){
        cout<<"¡¡JAQUE MATE!! Ganaron las negras"<<endl;
		
		mostrarTablero();
		
		actualizarPuntaje(jugadorNegro,1);
		
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
		
		actualizarPuntaje(jugadorBlanco,1);
		
        exit(0);

    }

}

}

if(turnoBlanco){

    if(tablas(true)){

        cout<<"TABLAS: El jugador blanco no tiene movimientos legales"<<endl;
        mostrarTablero();
        exit(0);

    }

}else{

    if(tablas(false)){

        cout<<"TABLAS: El jugador negro no tiene movimientos legales"<<endl;
        mostrarTablero();
        exit(0);

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

void tableroJaque(){

    tablero = {

        {'r','n','b','.','k','b','n','r'},
        {'p','p','p','.','.','p','p','p'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','p','q','.','.','.'},
        {'.','.','B','.','P','.','.','.'},
        {'.','.','.','.','.','N','.','.'},
        {'P','P','P','P','.','P','P','P'},
        {'R','N','B','.','K','.','.','R'}

    };

    turnoBlanco = true;

}

void tableroJaqueMate(){

    tablero = {

        {'r','.','b','q','k','b','.','r'},
        {'p','p','p','p','.','p','p','p'},
        {'.','.','n','.','.','.','.','.'},
        {'.','.','.','.','p','.','.','.'},
        {'.','.','B','.','P','.','.','.'},
        {'.','.','.','.','.','Q','.','.'},
        {'P','P','P','P','.','P','P','P'},
        {'R','N','B','.','K','.','N','R'}

    };

    turnoBlanco = true;

}

void tableroEnroqueCorto(){

    tablero = {

        {'r','n','b','q','k','.','.','r'},
        {'p','p','p','p','b','p','p','p'},
        {'.','.','.','.','.','n','.','.'},
        {'.','.','.','.','p','.','.','.'},
        {'.','.','.','.','P','.','.','.'},
        {'.','.','.','.','.','N','.','.'},
        {'P','P','P','P','B','P','P','P'},
        {'R','N','B','Q','K','.','.','R'}

    };

    turnoBlanco = true;

}

void tableroEnroqueLargo(){

    tablero = {

        {'r','.','.','.','k','b','n','r'},
        {'p','p','p','q','.','p','p','p'},
        {'.','.','n','.','.','.','.','.'},
        {'.','.','.','p','p','.','.','.'},
        {'.','.','B','.','P','.','.','.'},
        {'.','.','N','.','.','.','.','.'},
        {'P','P','P','Q','.','P','P','P'},
        {'R','.','.','.','K','B','N','R'}

    };

    turnoBlanco = true;

}

void tableroCapturaAlPaso(){

    tablero = {

        {'r','n','b','q','k','b','.','r'},
        {'p','p','p','p','.','p','p','p'},
        {'.','.','.','.','.','n','.','.'},
        {'.','.','.','.','P','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','N','.','.','.','.','.'},
        {'P','P','P','P','.','P','P','P'},
        {'R','.','B','Q','K','B','N','R'}

    };

    turnoBlanco = false;

}

void tableroPromocion(){

    tablero = {

        {'.','.','b','.','k','b','.','r'},
        {'P','.','p','.','.','p','p','.'},
        {'.','.','n','.','.','.','.','.'},
        {'.','.','.','p','.','.','.','.'},
        {'.','.','.','.','P','.','.','.'},
        {'.','.','.','.','.','N','.','.'},
        {'P','P','P','P','.','P','P','P'},
        {'R','N','B','Q','K','B','.','R'}

    };

    turnoBlanco = true;

}

void tableroPiezaClavada(){

    tablero = {

        {'r','.','.','.','q','.','k','.'},
        {'p','p','p','.','.','p','p','p'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'P','P','P','.','R','P','P','P'},
        {'R','N','B','Q','K','B','N','.'}

    };

    turnoBlanco = true;

}

void tableroAhogado(){

    tablero = {

        {'k','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'.','K','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','Q','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'}

    };

    turnoBlanco = true;

}

void mostrarTablero(){

    cout << endl;

    // Letras superiores
    cout << "      a   b   c   d   e   f   g   h" << endl;

    cout << "    ---------------------------------" << endl;


    for(int i = 0; i < 8; i++){

        // Número de fila izquierda
        cout << " " << 8-i << "  | ";

        for(int j = 0; j < 8; j++){

            cout << tablero[i][j];

            if(j < 7){
                cout << " | ";
            }

        }

        // Número de fila derecha
        cout << " | " << 8-i << endl;

        cout << "    ---------------------------------" << endl;

    }


    // Letras inferiores
    cout << "      a   b   c   d   e   f   g   h" << endl;

    cout << endl;

}

void actualizarPuntaje(string jugador, int puntosGanados){

    map<string,int> puntajes;

    ifstream archivoEntrada("puntajes.txt");

    string nombre;
    int puntos;

    while(archivoEntrada >> nombre >> puntos){
        puntajes[nombre] = puntos;
    }

    archivoEntrada.close();

    puntajes[jugador] += puntosGanados;

    ofstream archivoSalida("puntajes.txt");

    for(auto jugador : puntajes){
        archivoSalida << jugador.first << " " << jugador.second << endl;
    }

    archivoSalida.close();
}

void mostrarPuntajes(){

    ifstream archivo("puntajes.txt");

    if(!archivo.is_open()){

        cout << "No existe el archivo de puntajes." << endl;
        return;

    }

    string nombre;
    int puntos;

    cout << endl;
    cout << "========== PUNTAJES ==========" << endl;

    while(archivo >> nombre >> puntos){

        cout << nombre << " : " << puntos << " puntos" << endl;

    }

    cout << "==============================" << endl << endl;

    archivo.close();

}

void guardarMovimiento(string origen, string destino){

    ofstream archivo("movimientos.txt", ios::app);

    if(archivo.is_open()){

        archivo << origen << "-" << destino << endl;

        archivo.close();

    }

}

int contarMovimientos(ifstream &archivo){

    string linea;

    if(!getline(archivo, linea)){

        return 0;

    }
    
    cout << linea << endl;

    return 1 + contarMovimientos(archivo);

}


void partida(){
	
	cout << "Nombre del jugador de las blancas: ";
    cin >> jugadorBlanco;

    cout << "Nombre del jugador de las negras: ";
    cin >> jugadorNegro;

    IniciarTablero();
    
    //Jugadas para mostrar: blancas c4 -> b5
    //tableroJaque();
    
    //Jugadas para mostrar: blancas f3 -> f7
	//tableroJaqueMate();
	
	//Jugadas para mostrar: blancas e1 -> g1
	//tableroEnroqueCorto();
	
	//Jugadas para mostrar: blancas e1 -> c1
	//tableroEnroqueLargo();
	
	//Jugadas para mostrar: negras d7 -> d5, blancas e5 -> d6
	//tableroCapturaAlPaso(); 
	
	//Jugadas para mostrar: blancas a7 -> a8
	//tableroPromocion();
	
	//Jugadas para mostrar: blancas intentar e2 -> d2
	//tableroPiezaClavada();
	
	//Jugadas para mostrar: blancas c4 -> c7
	//tableroAhogado();

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
	cout<<"2. Ver puntajes"<<endl;
	cout<<"3. Contar movimientos"<<endl;
	cout<<"4. Instrucciones"<<endl;
	cout<<"5. Salir"<<endl;

    do{

        cout<<"Escoja su opción: ";
        cin >> opcion;

        cout<<endl;

        if (opcion == 1){

            partida();

        }else if (opcion == 2){

            mostrarPuntajes();

        }else if(opcion == 3){

    ifstream archivo("movimientos.txt");

    if(!archivo.is_open()){

        cout << "No hay movimientos registrados." << endl;

    }else{

        cout << "===== HISTORIAL DE MOVIMIENTOS =====" << endl;

    int cantidad = contarMovimientos(archivo);

    cout << "===================================" << endl;
    cout << "Total de movimientos: " << cantidad << endl;

    archivo.close();

    }

	}else if (opcion == 4){

            cout << "==============================================================" << endl;
			cout << "                    INSTRUCCIONES DEL JUEGO                   " << endl;
			cout << "==============================================================" << endl;
			cout << endl;

			cout << "OBJETIVO DEL JUEGO" << endl;
			cout << "El objetivo del ajedrez es dar jaque mate al rey enemigo." << endl;
			cout << "Un rey esta en jaque mate cuando no puede escapar de un" << endl;
			cout << "ataque y la partida termina inmediatamente." << endl;
			cout << endl;

			cout << "MOVIMIENTO DE LAS PIEZAS" << endl;
			cout << "- Peon (P): Avanza una casilla. En su primer movimiento" << endl;
			cout << "  puede avanzar dos casillas. Captura en diagonal." << endl;
			cout << "- Torre (R): Se mueve cualquier cantidad de casillas en" << endl;
			cout << "  linea recta, horizontal o vertical." << endl;
			cout << "- Caballo (N): Se mueve en forma de L y puede saltar" << endl;
			cout << "  sobre otras piezas." << endl;
			cout << "- Alfil (B): Se mueve cualquier cantidad de casillas en" << endl;
			cout << "  diagonal." << endl;
			cout << "- Reina (Q): Combina los movimientos de la torre y el" << endl;
			cout << "  alfil." << endl;
			cout << "- Rey (K): Se mueve una casilla en cualquier direccion." << endl;
			cout << endl;

			cout << "REGLAS ESPECIALES" << endl;
			cout << "- Enroque: Se realiza si el rey y la torre no se han" << endl;
			cout << "  movido y no existen piezas entre ellos." << endl;
			cout << "- Promocion: Cuando un peon llega al extremo opuesto del" << endl;
			cout << "  tablero puede convertirse en Reina, Torre, Alfil o" << endl;
			cout << "  Caballo." << endl;
			cout << endl;

			cout << "COMO JUGAR" << endl;
			cout << "Ingrese primero la casilla de origen y luego la casilla" << endl;
			cout << "de destino utilizando la notacion del tablero." << endl;
			cout << endl;
			cout << "Ejemplos:" << endl;
			cout << "Origen : e2" << endl;
			cout << "Destino: e4" << endl;
			cout << endl;
			cout << "Origen : g1" << endl;
			cout << "Destino: f3" << endl;
			cout << endl;

			cout << "El programa verificara automaticamente si el movimiento" << endl;
			cout << "es valido segun las reglas del ajedrez." << endl;
			cout << endl;

			cout << "PUNTAJES" << endl;
			cout << "Al finalizar una partida por jaque mate, el ganador" << endl;
			cout << "obtendra un punto. Los puntajes se almacenan en el" << endl;
			cout << "archivo 'puntajes.txt' y pueden consultarse desde el menu." << endl;
			cout << endl;

			cout << "==============================================================" << endl;
            
        }else if(opcion == 5){
        	
        	cout<<"Gracias por jugar";
            cout<<endl;
            
		}else{

            cout<<"Debes escoger un número entre 1 y 5"<<endl;

        }

    }while(opcion < 1 || opcion > 5);

}


int main(){
	setlocale(LC_ALL, "Spanish");
    menu();

}
