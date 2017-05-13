#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
#include <utility>
//#include <vector>
using namespace std;

class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      //Varibles de GPS
      bien_situado = false;
      posicion_togo = false;
      distancia_calculada = false;
      posicion_sensor_togo = 0;
      distancia = 0;
      distancia_lateral = 0;

      //Variables de brujula
      brujula = 0;
      brujula_start = false;

      //Variables matriz y mochila
      almacenamiento = 0;
      contador = 0;
      ultimoContador = 0;

      //Booleanos de estado
      colision = false;
      tengo_llave = false;

      iteraciones = 0;

      filas = 99;
      columnas = 99;

      //Inicializacion de matrices
      for (int i = 0; i < 200; ++i)
        for (int j = 0; j < 200; ++j)
            matriz_seguimiento[i][j] = 0;

      for (int i = 0; i < 200; ++i)
        for (int j = 0; j < 200; ++j)
            matriz_copia[i][j] = 0;

    }

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);

    int interact(Action accion, int valor);

    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}



    void Status (Sensores sensores);

    void MoveUpdate (Sensores sensores);

    void Reseteo (Sensores sensores);
    void ResetGoTo ();

    void MapTracking (Sensores sensores);
    void MapTrackingNorth(Sensores sensores);
    void MapTrackingEast(Sensores sensores);
    void MapTrackingSouth(Sensores sensores);
    void MapTrackingWest(Sensores sensores);

    bool Buscar (Sensores sensores, char lugar);
    bool Buscar_Entidad (Sensores sensores, char lugar);
    void CalcularDistancia (int posicion);
    Action GoTo ();

    //Action AddCoordenadaGiro (Sensores sensores);

    bool EsEsquina (Sensores sensores);
    bool Colision (Sensores sensores);

    void ActionItem(Sensores sensores, Action& accion);
    void ActionGoToGPS(Sensores sensores, Action& accion);

    void MatrizUpdate();
    void CopiarMatriz(int matriz);
    void InaccesibleMatriz (Sensores sensores);
    void InAHouse (Sensores sensores);

  private:
    // Declarar Variables de Estado
    int fil, col, brujula;
    int filas, columnas;
    Action ultimaAccion;
    bool brujula_start;

    bool bien_situado;
    int distancia;
    int distancia_lateral;
    int posicion_sensor_togo;
    int almacenamiento;
    bool posicion_togo;
    bool distancia_calculada;

    //vector<pair<bool, pair<int, int> > > coordenada_giro;
    bool colision;
    bool tengo_llave;

    static const int TAMANIO = 200;
    int matriz_seguimiento[TAMANIO][TAMANIO];
    int matriz_copia[TAMANIO][TAMANIO];
    int contador;
    int ultimoContador;

    int iteraciones;
};


#endif
