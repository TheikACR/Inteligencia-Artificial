#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
#include "stdlib.h"
using namespace std;


Action ComportamientoJugador::think(Sensores sensores){

    //Contador de iteraciones totales
    cout << iteraciones << endl;
    ++iteraciones;

	Action accion = actIDLE;

	//Reseteo de variables dependiendo de la situacion
    Reseteo(sensores);

    //Actualizacion del movimiento
    MoveUpdate(sensores);

    //Pintado sobre el mapaResultado
	MapTracking(sensores);

    /**
        He tenido que hacer esta inicializacion ya que
        la declaracion de la matriz_seguimiento me cambiaba
        de valor la brujula
    */
    if (!brujula_start || sensores.vida == 1000){
        brujula_start = true;
        brujula = 0;
    }

    //Booleano para determinar colision
    colision = Colision(sensores);

    //Actualizacion de matriz_seguimiento para evitar maximos locales
	InaccesibleMatriz(sensores);

	//Acciones segun los distintos encuentros con entidades
	ActionItem(sensores, accion);

	//Busqueda y movimiento hacia un GPS
    ActionGoToGPS(sensores, accion);

    //Movimiento tras encontrar un GPS
    if (accion == actIDLE && bien_situado){
        switch(brujula){
            case 0:
                if ((matriz_seguimiento[fil-1][col] < matriz_seguimiento[fil][col-1] ||
                    matriz_seguimiento[fil-1][col] <= matriz_seguimiento[fil][col+1]) &&
                    !colision)
                        accion = actFORWARD;
                else if (matriz_seguimiento[fil][col-1] < matriz_seguimiento[fil][col+1])
                    accion = actTURN_L;
                else if (matriz_seguimiento[fil][col+1] < matriz_seguimiento[fil][col-1])
                    accion = actTURN_R;
                else if (matriz_seguimiento[fil][col+1] == matriz_seguimiento[fil][col-1]){
                    if (rand() % 2 == 0)
                        accion = actTURN_L;
                    else
                        accion = actTURN_R;
                }
                break;
            case 1:
                if ((matriz_seguimiento[fil][col+1] < matriz_seguimiento[fil-1][col] ||
                    matriz_seguimiento[fil][col+1] <= matriz_seguimiento[fil+1][col]) &&
                    !colision)
                        accion = actFORWARD;
                else if (matriz_seguimiento[fil-1][col] < matriz_seguimiento[fil+1][col])
                    accion = actTURN_L;
                else if (matriz_seguimiento[fil+1][col] < matriz_seguimiento[fil-1][col])
                    accion = actTURN_R;
                else if (matriz_seguimiento[fil+1][col] == matriz_seguimiento[fil-1][col]){
                    if (rand() % 2 == 0)
                        accion = actTURN_L;
                    else
                        accion = actTURN_R;
                }
                break;
            case 2:
                if ((matriz_seguimiento[fil+1][col] < matriz_seguimiento[fil][col-1] ||
                    matriz_seguimiento[fil+1][col] <= matriz_seguimiento[fil][col+1]) &&
                    !colision)
                        accion = actFORWARD;
                else if (matriz_seguimiento[fil][col+1] < matriz_seguimiento[fil][col-1])
                    accion = actTURN_L;
                else if (matriz_seguimiento[fil][col-1] < matriz_seguimiento[fil][col+1])
                    accion = actTURN_R;
                else if (matriz_seguimiento[fil][col-1] == matriz_seguimiento[fil][col+1]){
                    if (rand() % 2 == 0)
                        accion = actTURN_L;
                    else
                        accion = actTURN_R;
                }
                break;
            case 3:
                if ((matriz_seguimiento[fil][col-1] < matriz_seguimiento[fil][col-1] ||
                    matriz_seguimiento[fil][col-1] <= matriz_seguimiento[fil][col+1]) &&
                    !colision){
                        accion = actFORWARD;
                    }
                else if (matriz_seguimiento[fil+1][col] < matriz_seguimiento[fil-1][col])
                    accion = actTURN_L;
                else if (matriz_seguimiento[fil-1][col] < matriz_seguimiento[fil+1][col])
                    accion = actTURN_R;
                else if (matriz_seguimiento[fil-1][col] == matriz_seguimiento[fil+1][col]){
                    if (rand() % 2 == 0)
                        accion = actTURN_L;
                    else
                        accion = actTURN_R;
                }
                break;
        }
    }

    //Movimiento mientras no este situado sobre un GPS
    if (accion == actIDLE && !bien_situado){
        switch(brujula){
            case 0:
                if ((matriz_seguimiento[filas-1][columnas] < matriz_seguimiento[filas][columnas-1] ||
                    matriz_seguimiento[filas-1][columnas] <= matriz_seguimiento[filas][columnas+1]) &&
                    !colision)
                        accion = actFORWARD;
                else if (matriz_seguimiento[filas][columnas-1] < matriz_seguimiento[filas][columnas+1])
                    accion = actTURN_L;
                else if (matriz_seguimiento[filas][columnas+1] < matriz_seguimiento[filas][columnas-1])
                    accion = actTURN_R;
                else if (matriz_seguimiento[filas][columnas+1] == matriz_seguimiento[filas][columnas-1]){
                    if (rand() % 2 == 0)
                        accion = actTURN_L;
                    else
                        accion = actTURN_R;
                }
                break;
            case 1:
                if ((matriz_seguimiento[filas][columnas+1] < matriz_seguimiento[filas-1][columnas] ||
                    matriz_seguimiento[filas][columnas+1] <= matriz_seguimiento[filas+1][columnas]) &&
                    !colision)
                        accion = actFORWARD;
                else if (matriz_seguimiento[filas-1][columnas] < matriz_seguimiento[filas+1][columnas])
                    accion = actTURN_L;
                else if (matriz_seguimiento[filas+1][columnas] < matriz_seguimiento[filas-1][columnas])
                    accion = actTURN_R;
                else if (matriz_seguimiento[filas+1][columnas] == matriz_seguimiento[filas-1][columnas]){
                    if (rand() % 2 == 0)
                        accion = actTURN_L;
                    else
                        accion = actTURN_R;
                }
                break;
            case 2:
                if ((matriz_seguimiento[filas+1][columnas] < matriz_seguimiento[filas][columnas-1] ||
                    matriz_seguimiento[filas+1][columnas] <= matriz_seguimiento[filas][columnas+1]) &&
                    !colision)
                        accion = actFORWARD;
                else if (matriz_seguimiento[filas][columnas+1] < matriz_seguimiento[filas][columnas-1])
                    accion = actTURN_L;
                else if (matriz_seguimiento[filas][columnas-1] < matriz_seguimiento[filas][columnas+1])
                    accion = actTURN_R;
                else if (matriz_seguimiento[filas][columnas-1] == matriz_seguimiento[filas][columnas+1]){
                    if (rand() % 2 == 0)
                        accion = actTURN_L;
                    else
                        accion = actTURN_R;
                }
                break;
            case 3:
                if ((matriz_seguimiento[filas][columnas-1] < matriz_seguimiento[filas][columnas-1] ||
                    matriz_seguimiento[filas][columnas-1] <= matriz_seguimiento[filas][columnas+1]) &&
                    !colision){
                        accion = actFORWARD;
                    }
                else if (matriz_seguimiento[filas+1][columnas] < matriz_seguimiento[filas-1][columnas])
                    accion = actTURN_L;
                else if (matriz_seguimiento[filas-1][columnas] < matriz_seguimiento[filas+1][columnas])
                    accion = actTURN_R;
                else if (matriz_seguimiento[filas-1][columnas] == matriz_seguimiento[filas+1][columnas]){
                    if (rand() % 2 == 0)
                        accion = actTURN_L;
                    else
                        accion = actTURN_R;
                }
                break;
        }
    }

    //Reseteo de variables de movimiento a un GPS
    ResetGoTo();

    //Memoria de la accion y del contador
    ultimaAccion = accion;
    ultimoContador = contador;

    //Evita quedarse encerrado en una casa
    InAHouse(sensores);

    //Copia de seguridad de la matriz
    CopiarMatriz(0);

    //Salida por pantalla de informacion util
    //Status(sensores);

	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}

/**
    Salida por pantalla de datos utiles
*/
void ComportamientoJugador::Status (Sensores sensores){

    cout << endl << endl;

    cout << "Terreno: ";
	for (int i=0; i<sensores.terreno.size(); i++)
		cout << sensores.terreno[i];
	cout << endl;

	cout << "Superficie: ";
	for (int i=0; i<sensores.superficie.size(); i++)
		cout << sensores.superficie[i];
	cout << endl;

	cout << "Colision: " << sensores.colision << endl;
	cout << "Mochila: " << sensores.mochila << endl;
	cout << "Reset: " << sensores.reset << endl;
	cout << "Vida: " << sensores.vida << endl;
	cout << "Fila: " << sensores.mensajeF << endl;
	cout << "Columna: " << sensores.mensajeC << endl;
	cout << "objetoActivo: " << sensores.objetoActivo << endl;
	cout << "bien situado: " << bien_situado << endl;
	cout << "brujula: "  << brujula << endl;
	cout << "colision: " << colision << endl;
	if (bien_situado){
        cout << "matriz: " << matriz_seguimiento[fil][col] << endl;
        cout << "matriz arriba: " << matriz_seguimiento[fil-1][col] << endl;
        cout << "matriz derecha: " << matriz_seguimiento[fil][col+1] << endl;
        cout << "matriz abajo: " << matriz_seguimiento[fil+1][col] << endl;
        cout << "matriz izquierda: " << matriz_seguimiento[fil][col-1] << endl;
    }
	cout << "tengo llave: " << tengo_llave << endl;
	cout << endl;
}

/**
    Reset de las variables en caso de morir
    o de haber problemas con la busqueda de un gps
*/
void ComportamientoJugador::Reseteo(Sensores sensores){

    if (!bien_situado && posicion_togo && ultimaAccion == actIDLE){
        posicion_togo = false;
    }

    if (sensores.reset){
        matriz_seguimiento[99][99];

        for (int i = 0; i < TAMANIO; ++i)
            for (int j = 0; j < TAMANIO; ++j)
                matriz_seguimiento[i][j] = 0;

        CopiarMatriz(1);
        brujula = 0;
        distancia = 0;
        distancia_lateral = 0;
        posicion_sensor_togo = 0;
        almacenamiento = 0;
        filas = 99;
        columnas = 99;
        contador = ultimoContador;
        colision = false;
        posicion_togo = false;
        distancia_calculada = false;
        brujula_start = false;
        bien_situado = false;
    }

}

/**
    Actualizacion de la posicion en el mapa del agente
*/
void ComportamientoJugador::MoveUpdate(Sensores sensores){

	switch (ultimaAccion){
        case actFORWARD:
            if (!sensores.colision){
                switch (brujula){
                    case 0:
                        --fil;
                        break;
                    case 1:
                        ++col;
                        break;
                    case 2:
                        ++fil;
                        break;
                    case 3:
                        --col;
                        break;
                }
                MatrizUpdate();
            }
            break;
        case actTURN_L:
            brujula = (brujula + 3) % 4;
            break;
        case actTURN_R:
            brujula = (brujula + 1) % 4;
            break;
	}
}

/**
    Pintado en el mapa resultado en funcion de los sensores
*/
void ComportamientoJugador::MapTracking(Sensores sensores){

    if ((sensores.terreno[0]=='K') && !bien_situado){
        fil = sensores.mensajeF;
        col = sensores.mensajeC;
        bien_situado = true;
    }

    if (bien_situado && !sensores.reset){
        switch (brujula){
            case 0:
                MapTrackingNorth(sensores);
                break;
            case 1:
                MapTrackingEast(sensores);
                break;
            case 2:
                MapTrackingSouth(sensores);
                break;
            case 3:
                MapTrackingWest(sensores);
                break;
        }
    }
}

/**
    Memoria para recordar los lugares en los que he colisionado
*/
/*Action ComportamientoJugador::AddCoordenadaGiro(Sensores sensores){

    if (colision && !EsEsquina(sensores)){
        bool encontrado = false;
        int pos_encontrado, i = 0;
        vector<pair<bool, pair<int, int> > >::iterator it;
        for (it = coordenada_giro.begin(); it != coordenada_giro.end() && !encontrado; ++it){
            if (fil == (*it).second.first && col == (*it).second.second){
                    encontrado = true;
                    pos_encontrado = i;
            }
            ++i;
        }
        if (encontrado && !coordenada_giro.at(pos_encontrado).first){
            coordenada_giro.at(pos_encontrado).first = true;
            return actTURN_R;
        }
        else if (encontrado && coordenada_giro.at(pos_encontrado).first){
            coordenada_giro.erase(coordenada_giro.begin()+pos_encontrado-1);
            return actIDLE;
        }
        if (!encontrado){
            pair<bool, pair<int, int> > lugar;
            lugar.second.first = fil;
            lugar.second.second = col;
            lugar.first = false;
            coordenada_giro.push_back(lugar);
            return actTURN_L;
        }
    }
}*/

/**
    Busqueda de un tipo concreto de casilla en los sensores
*/
bool ComportamientoJugador::Buscar(Sensores sensores, char lugar){

    bool encontrado = false;

    if (posicion_sensor_togo == 0){
        for (int i = 0; i < sensores.terreno.size(); ++i){
            if (sensores.terreno[i] == lugar){
                posicion_sensor_togo = i;
                posicion_togo = true;
                encontrado = true;
                CalcularDistancia(posicion_sensor_togo);
            }
        }
    } else if (posicion_togo){
        encontrado = true;
    }

    return encontrado;
}

/**
    Busqueda de un tipo concreto de entidad en los sensores
*/
bool ComportamientoJugador::Buscar_Entidad(Sensores sensores, char lugar){

    bool encontrado = false;

    if (posicion_sensor_togo == 0){
        for (int i = 0; i < sensores.superficie.size(); ++i){
            if (sensores.superficie[i] == lugar){
                posicion_sensor_togo = i;
                encontrado = true;
                //CalcularDistancia(posicion_sensor_togo);
            }
        }
    } else {
        encontrado = true;
    }

    return encontrado;
}

/**
    Calculo de distancia a la que se encuentra el agente de una posicion
*/
void ComportamientoJugador::CalcularDistancia(int posicion){

    //Calculo de bloques que hay delante hasta posicion
    if (posicion == 0 || posicion <= 3)
        distancia = 1;
    if (posicion >= 4 || posicion <= 8)
        distancia = 2;
    if (posicion >= 9 || posicion <= 15)
        distancia = 3;

    //Calculo de bloques que hay lateralmente hasta posicion
    if (posicion == 2 || posicion == 6 || posicion == 12)
        distancia_lateral = 0;
    if (posicion == 1 || posicion == 5 || posicion == 11)
        distancia_lateral = -1;
    if (posicion == 3 || posicion == 7 || posicion == 13)
        distancia_lateral = 1;
    if (posicion == 4 || posicion == 10)
        distancia_lateral = -2;
    if (posicion == 8 || posicion == 14)
        distancia_lateral = 2;
    if (posicion == 9)
        distancia_lateral = -3;
    if (posicion == 15)
        distancia_lateral = 3;

}

/**
    Acciones que debe realizar el agente en funcion
    de la distancia a la casilla que se quiere ir
*/
Action ComportamientoJugador::GoTo(){

    if (distancia > 0){
        distancia -= 1;
        return actFORWARD;
    }
    else if (distancia == 0 && distancia_lateral < 0){
        distancia = -  distancia_lateral;
        distancia_lateral = 0;
        return actTURN_L;
    }
    else if (distancia == 0 && distancia_lateral > 0){
        distancia = distancia_lateral;
        distancia_lateral = 0;
        return actTURN_R;
    }

}

/**
    Pintado en el mapa resultado si la brujula apunta al norte
*/
void ComportamientoJugador::MapTrackingNorth(Sensores sensores){

    int pos = 1;

    mapaResultado[fil][col] = sensores.terreno[0];

    for (int i = 1; i < 4; ++i)
        for (int j = i*-1; j < i+1; ++j){
            mapaResultado[fil-i][col+j] = sensores.terreno[pos];
            ++pos;
        }

}

/**
    Pintado en el mapa resultado si la brujula apunta al este
*/
void ComportamientoJugador::MapTrackingEast(Sensores sensores){

    int pos = 1;

    mapaResultado[fil][col] = sensores.terreno[0];

    for (int i = 1; i < 4; ++i)
        for (int j = i*-1; j < i+1; ++j){
            mapaResultado[fil+j][col+i] = sensores.terreno[pos];
            ++pos;
        }

}

/**
    Pintado en el mapa resultado si la brujula apunta al sur
*/
void ComportamientoJugador::MapTrackingSouth(Sensores sensores){

    int pos = 1;

    mapaResultado[fil][col] = sensores.terreno[0];

    for (int i = 1; i < 4; ++i)
        for (int j = i*-1; j < i+1; ++j){
            mapaResultado[fil+i][col-j] = sensores.terreno[pos];
            ++pos;
        }

}

/**
    Pintado en el mapa resultado si la brujula apunta al oeste
*/
void ComportamientoJugador::MapTrackingWest(Sensores sensores){

    int pos = 1;

    mapaResultado[fil][col] = sensores.terreno[0];

    for (int i = 1; i < 4; ++i)
        for (int j = i*-1; j < i+1; ++j){
            mapaResultado[fil-j][col-i] = sensores.terreno[pos];
            ++pos;
        }

}

/**
    Devuelve si la casilla siguiente es una esquina
*/
bool ComportamientoJugador::EsEsquina(Sensores sensores){

    bool es_esquina = false;
    //Esquina superior izq
    if ((mapaResultado[fil-1][col] == 'P' || mapaResultado[fil-1][col] == 'B' ||
        mapaResultado[fil-1][col] == 'M' || mapaResultado[fil-1][col] == 'A') &&
        (mapaResultado[fil][col-1] == 'P' || mapaResultado[fil][col-1] == 'B' ||
        mapaResultado[fil][col-1] == 'M' || mapaResultado[fil][col-1] == 'A'))
            es_esquina = true;

    //Esquina superior dcha
    if ((mapaResultado[fil-1][col] == 'P' || mapaResultado[fil-1][col] == 'B' ||
        mapaResultado[fil-1][col] == 'M' || mapaResultado[fil-1][col] == 'A') &&
        (mapaResultado[fil][col+1] == 'P' || mapaResultado[fil][col+1] == 'B' ||
        mapaResultado[fil][col+1] == 'M' || mapaResultado[fil][col+1] == 'A'))
            es_esquina = true;

    //Esquina inferior izq
    if ((mapaResultado[fil+1][col] == 'P' || mapaResultado[fil+1][col] == 'B' ||
        mapaResultado[fil+1][col] == 'M' || mapaResultado[fil+1][col] == 'A') &&
        (mapaResultado[fil][col-1] == 'P' || mapaResultado[fil][col-1] == 'B' ||
        mapaResultado[fil][col-1] == 'M' || mapaResultado[fil][col-1] == 'A'))
            es_esquina = true;

    //Esquina inferior dcha
    if ((mapaResultado[fil+1][col] == 'P' || mapaResultado[fil+1][col] == 'B' ||
        mapaResultado[fil+1][col] == 'M' || mapaResultado[fil+1][col] == 'A') &&
        (mapaResultado[fil][col+1] == 'P' || mapaResultado[fil][col+1] == 'B' ||
        mapaResultado[fil][col+1] == 'M' || mapaResultado[fil][col+1] == 'A'))
            es_esquina = true;

    return es_esquina;

}

/**
    Booleano que determina si se ha colisionado
*/
bool ComportamientoJugador::Colision(Sensores sensores){

    if (sensores.terreno[2] == 'A' && sensores.objetoActivo == '1'){
        return false;
    }

    if (sensores.terreno[2] == 'B' && sensores.objetoActivo == '2'){
        return false;
    }

    if (sensores.terreno[2] == 'P' || sensores.terreno[2] == 'B' ||
        sensores.terreno[2] == 'M' || sensores.terreno[2] == 'A' ||
        sensores.superficie[2] == 'a' || sensores.superficie[2] == 'l')
        return true;

    if ((sensores.terreno[2] == 'T' || sensores.terreno[2] == 'S' || sensores.terreno[2] == 'K') && sensores.superficie[2] == '_'){
        return false;
    }

    else
        return false;
}

/**
    Acciones a realizar en caso de encontrar un objeto o una entidad
*/
void ComportamientoJugador::ActionItem(Sensores sensores, Action& accion){

    if (sensores.superficie[2] == 'l' && sensores.objetoActivo == '0'){
        accion = actGIVE;
    }

    if (sensores.superficie[2] == 'd' && sensores.objetoActivo == '3'){
        accion = actGIVE;
    }

    if ((sensores.superficie[2] == '0' ||
        sensores.superficie[2] == '1' ||
        sensores.superficie[2] == '2' ||
        sensores.superficie[2] == '3') && !tengo_llave){
            if((sensores.objetoActivo == '0' ||
               sensores.objetoActivo == '1' ||
               sensores.objetoActivo == '2' ||
               sensores.objetoActivo == '3') && almacenamiento < 4){
                accion = actPUSH;
                ++almacenamiento;
            }
            else if (sensores.objetoActivo == '_'){
                accion = actPICKUP;
            }
    }

    if (sensores.vida <= 10 && almacenamiento > 0){
        accion = actPUTDOWN;
        --almacenamiento;
    }
}

/**
    Acciones para llegar a un GPS en caso de no estar bien situado
    y haber encontrado uno
*/
void ComportamientoJugador::ActionGoToGPS(Sensores sensores, Action& accion){

    if (Buscar(sensores, 'K') && !bien_situado && accion == actIDLE){
        if (!distancia_calculada){
            CalcularDistancia(posicion_sensor_togo);
        }
        distancia_calculada = true;
        accion = GoTo();
	}

}

/**
    Reseteo de las variables de busqueda
*/
void ComportamientoJugador::ResetGoTo(){

    if (distancia == 0 && distancia_lateral == 0){
        posicion_sensor_togo = 0;
        distancia_calculada = false;
        posicion_togo = false;
    }

    if (bien_situado){
        if (mapaResultado[fil][col+1] == 'K'){
            distancia = 0;
            distancia_lateral = 0;
            posicion_sensor_togo = 0;
            distancia_calculada = false;
            posicion_togo = false;
        }
    }

}

/**
    Actualizacion de la matriz pulgarcito
*/
void ComportamientoJugador::MatrizUpdate(){

    if (bien_situado){
        matriz_seguimiento[fil][col] = contador;
        ++contador;
    }

}

/**
    Copia de la matriz_seguimiento a una memoria
    o viceversa
*/
void ComportamientoJugador::CopiarMatriz (int matriz){

    if (matriz == 0){
        for (int i = 0; i < 200; ++i)
            for (int j = 0; j < 200; ++j)
                matriz_copia[i][j] = matriz_seguimiento[i][j];
    }

    if (matriz == 1){
        for (int i = 0; i < 200; ++i)
            for (int j = 0; j < 200; ++j)
                matriz_seguimiento[i][j] = matriz_copia[i][j];
    }

}

/**
    Actualiza la matriz_seguimiento para evitar maximos locales
*/
void ComportamientoJugador::InaccesibleMatriz(Sensores sensores){

    if (bien_situado){
        switch(brujula){
            case 0:
                if ((sensores.terreno[2] == 'A' && sensores.objetoActivo != '1') ||
                    (sensores.terreno[2] == 'B' && sensores.objetoActivo != '2') ||
                    sensores.superficie[2] == 'a' || sensores.superficie[2] == 'l'){
                        matriz_seguimiento[fil-1][col] = contador + 1;
                }

                if ((sensores.superficie[2] == '0' ||
                    sensores.superficie[2] == '1' ||
                    sensores.superficie[2] == '2' ||
                    sensores.superficie[2] == '3') && (tengo_llave || almacenamiento == 4))
                        matriz_seguimiento[fil-1][col] = contador + 1;

                if (sensores.objetoActivo != '3' && sensores.superficie[2] == 'd')
                    matriz_seguimiento[fil-1][col] = contador + 1;

                if (sensores.terreno[2] == 'P' || sensores.terreno[2] == 'M')
                    matriz_seguimiento[fil-1][col] = contador + 1000;
                break;
            case 1:
                if ((sensores.terreno[2] == 'A' && sensores.objetoActivo != '1') ||
                    (sensores.terreno[2] == 'B' && sensores.objetoActivo != '2') ||
                    sensores.superficie[2] == 'a' || sensores.superficie[2] == 'l'){
                        matriz_seguimiento[fil][col+1] = contador + 1;
                }

                if ((sensores.superficie[2] == '0' ||
                    sensores.superficie[2] == '1' ||
                    sensores.superficie[2] == '2' ||
                    sensores.superficie[2] == '3') && (tengo_llave || almacenamiento == 4))
                        matriz_seguimiento[fil][col+1] = contador + 1;

                if (sensores.objetoActivo != '3' && sensores.superficie[2] == 'd')
                    matriz_seguimiento[fil][col+1] = contador + 1;

                if (sensores.terreno[2] == 'P' || sensores.terreno[2] == 'M')
                    matriz_seguimiento[fil][col+1] = contador + 1000;
                break;
            case 2:
                if ((sensores.terreno[2] == 'A' && sensores.objetoActivo != '1') ||
                    (sensores.terreno[2] == 'B' && sensores.objetoActivo != '2') ||
                    sensores.superficie[2] == 'a' || sensores.superficie[2] == 'l'){
                        matriz_seguimiento[fil+1][col] = contador + 1;
                }

                if ((sensores.superficie[2] == '0' ||
                    sensores.superficie[2] == '1' ||
                    sensores.superficie[2] == '2' ||
                    sensores.superficie[2] == '3') && (tengo_llave || almacenamiento == 4))
                        matriz_seguimiento[fil+1][col] = contador + 1;

                if (sensores.objetoActivo != '3' && sensores.superficie[2] == 'd')
                    matriz_seguimiento[fil+1][col] = contador + 1;

                if (sensores.terreno[2] == 'P' || sensores.terreno[2] == 'M')
                    matriz_seguimiento[fil+1][col] = contador + 1000;
                break;
            case 3:
                if ((sensores.terreno[2] == 'A' && sensores.objetoActivo != '1') ||
                    (sensores.terreno[2] == 'B' && sensores.objetoActivo != '2') ||
                    sensores.superficie[2] == 'a' || sensores.superficie[2] == 'l'){
                        matriz_seguimiento[fil][col-1] = contador + 1;
                }

                if ((sensores.superficie[2] == '0' ||
                    sensores.superficie[2] == '1' ||
                    sensores.superficie[2] == '2' ||
                    sensores.superficie[2] == '3') && (tengo_llave || almacenamiento == 4))
                        matriz_seguimiento[fil][col-1] = contador + 1;

                if (sensores.objetoActivo != '3' && sensores.superficie[2] == 'd')
                    matriz_seguimiento[fil][col-1] = contador + 1;

                if (sensores.terreno[2] == 'P' || sensores.terreno[2] == 'M')
                    matriz_seguimiento[fil][col-1] = contador + 1000;
                break;

        }
    }

}

/**
    Determina si el agente esta en una superficie
    delimitada por paredes
*/
void ComportamientoJugador::InAHouse(Sensores sensores){

    if (sensores.superficie[2] == 'd' && sensores.objetoActivo == '3' && tengo_llave)
            tengo_llave = false;
    else if (sensores.superficie[2] == 'd' && sensores.objetoActivo == '3' && ultimaAccion == actGIVE && !tengo_llave)
            tengo_llave = true;

}
