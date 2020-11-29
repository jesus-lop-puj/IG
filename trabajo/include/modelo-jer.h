// Nombre: Jesús, Apellidos: López Pujazón, DNI/pasaporte: 26523483K (DDGG IG curso 20-21)

/* *************************************
  Fichero: modelo-jer.cpp
  Autor: Jesús López Pujazón
  Informática Gráfica Curso 2020-2021
*************************************** */

#ifndef MODELO_JER_H
#define MODELO_JER_H

#include "grafo-escena.h"


//-----------------------------------------------------------------------
// Nodo Raíz del grafo
class C : public NodoGrafoEscena{

  protected:
    Matriz4f * traslacion = nullptr;
    Matriz4f * rotacionCabeza = nullptr;
    Matriz4f * movBrazoIzq = nullptr;
    Matriz4f * movBrazoDer = nullptr;

    void actualizarEstadoParametro(const unsigned iParam, const float t_sec);

  public:
    C();
    unsigned leerNumParametros() const;
    void fijarTraslacion(const float nuevaTraslacion); //Fijamos la traslacion de Eva
    void fijarRotacionCabeza(const float nuevaRotacion); //Fijamos la rotacion de la cabeza
    void fijarMovBrazoD(const float nuevaRotacion); //Fijamos movimiento del brazo derecho
    void fijarMovBrazoI(const float nuevaRotacion); //Fijamos movimiento del brazo izquierdo
};

//-----------------------------------------------------------------------
// Clase que representa el cuerpo de Eva
class Cuerpo : public NodoGrafoEscena{
  public:
    Cuerpo();
};

//-----------------------------------------------------------------------
// Clase que representa un brazo de Eva
class BrazoDer : public NodoGrafoEscena{
  public:
    BrazoDer(Matriz4f * &movBrazoDer);
};

//-----------------------------------------------------------------------
// Clase que representa un brazo de Eva
class BrazoIzq : public NodoGrafoEscena{
  public:
    BrazoIzq(Matriz4f * &movBrazoIzq);
};

//-----------------------------------------------------------------------
// Clase que representa la mitad superior de la cabeza de Eva
class mediaCabezaA : public NodoGrafoEscena{
  public:
    mediaCabezaA();
};

//-----------------------------------------------------------------------
// Clase que representa la mitad inferior de la cabeza de Eva
class mediaCabezaB : public NodoGrafoEscena{
  public:
    mediaCabezaB();
};

//-----------------------------------------------------------------------
// Clase que representa los ojos de Eva
class Ojos : public NodoGrafoEscena{
  public:
    Ojos();
};

//-----------------------------------------------------------------------
// Clase que representa la cabeza de Eva
class Cabeza : public NodoGrafoEscena{
  public:
    Cabeza(Matriz4f * &rotacionCabeza);
};

//-----------------------------------------------------------------------
// Clase que representa a Eva
class Eva : public NodoGrafoEscena{
  public:
    Eva(Matriz4f * &traslacion, Matriz4f * &rotacionCabeza, Matriz4f * &movBrazoIzq, Matriz4f * &movBrazoDer);
};
#endif
