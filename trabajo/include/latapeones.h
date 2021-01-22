// Nombre: Jesús, Apellidos: López Pujazón, DNI/pasaporte: 26523483K (DDGG IG curso 20-21)

#ifndef LATAPEONES_H
#define LATAPEONES_H

#include "objeto3d.h"
#include "grafo-escena.h"

class LataPeones: public NodoGrafoEscena{
    public:
        LataPeones();
};

class PeonMadera: public NodoGrafoEscena{
    public:
        PeonMadera();
};

class PeonBlanco: public NodoGrafoEscena{
    public:
        PeonBlanco();
};

class PeonNegro: public NodoGrafoEscena{
    public:
        PeonNegro();
};

class Lata: public NodoGrafoEscena{
    public:
        Lata();
};

class TapaSuperiorLata: public NodoGrafoEscena{
    public:
        TapaSuperiorLata();
};

class TapaInferiorLata: public NodoGrafoEscena{
    public:
        TapaInferiorLata();
};

class CuerpoLata: public NodoGrafoEscena{
    public:
        CuerpoLata(std::string nombre);
};

//Práctica 5

class VariasLatasPeones: public NodoGrafoEscena{
    public:
        VariasLatasPeones();
};

class LataPepsi: public NodoGrafoEscena{
    public:
        LataPepsi();
};

class LataUGR: public NodoGrafoEscena{
    public:
        LataUGR();
};

#endif
