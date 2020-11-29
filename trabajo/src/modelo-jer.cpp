// Nombre: Jesús, Apellidos: López Pujazón, DNI/pasaporte: 26523483K (DDGG IG curso 20-21)
/* *************************************
  Fichero: modelo-jer.cpp
  Autor: Jesús López Pujazón
  Informática Gráfica Curso 2020-2021
*************************************** */
#include "modelo-jer.h"
#include "malla-ind.h"
#include "malla-revol.h"
#include "matrices-tr.h"
#include <cmath>

// --------------------------------------------------------------------------
//Constructor de la clase C
C::C(){
  ponerNombre("Eva (Wall-e)");
  agregar(new Eva(traslacion, rotacionCabeza, movBrazoIzq, movBrazoDer));
}

// --------------------------------------------------------------------------
//Redefinimos la función leerNumParametros()
//Devuelve el número de parámetros activos
unsigned C::leerNumParametros() const{
  return 4;
}

// --------------------------------------------------------------------------
//Redefinimos la función actualizarEstadoParametro
//Modifica el estado de los parámetros de Eva
void C::actualizarEstadoParametro(const unsigned iParam, const float t_sec){
  assert(iParam<leerNumParametros());

  switch(iParam){
    case 0:
      fijarTraslacion(1.0 * sin(0.5*M_PI*t_sec));
      break;
    case 1:
      fijarRotacionCabeza(30 * sin(0.5*M_PI*t_sec));
      break;
    case 2:
      fijarMovBrazoD(45 * sin(0.5*M_PI*t_sec));
      break;
    case 3:
      fijarMovBrazoI(45 * sin(0.5*M_PI*t_sec));
      break;
  }
}

//-----------------------------------------------------------------------
void C :: fijarTraslacion(const float nuevaTraslacion){
    *traslacion = MAT_Traslacion(0.0, nuevaTraslacion, 0.0);
}

//-----------------------------------------------------------------------
void C :: fijarRotacionCabeza(const float nuevaRotacion){
    *rotacionCabeza = MAT_Rotacion(nuevaRotacion,0.0, 1.0, 0.0);
}

//-----------------------------------------------------------------------
void C :: fijarMovBrazoD(const float nuevaRotacion){
    *movBrazoDer = MAT_Rotacion(nuevaRotacion,1.0, 0.0, 0.0);
}

//-----------------------------------------------------------------------
void C :: fijarMovBrazoI(const float nuevaRotacion){
    *movBrazoIzq = MAT_Rotacion(nuevaRotacion,1.0, 0.0, 0.0);
}


//-----------------------------------------------------------------------
// Implementación del constructor de la clase Cuerpo
Cuerpo :: Cuerpo(){
  agregar( MAT_Escalado(0.75,2.0,0.75) );
  agregar ( MAT_Rotacion(180.0, 0.0, 0.0, 1.0));
  agregar(new mediaEsfera(30,30));
  ponerNombre("Cuerpo");
}

//-----------------------------------------------------------------------
// Implementación del constructor de la clase BrazoDer
BrazoDer :: BrazoDer(Matriz4f * &movBrazoDer){
  unsigned ind = agregar(MAT_Rotacion(0.0,1.0,0.0,0.0));

  agregar( MAT_Traslacion(0.80, -0.9, 0.0));
  agregar( MAT_Escalado(0.10,0.9,0.15) );
  agregar ( MAT_Rotacion(180.0, 0.0, 1.0, 0.0));
  agregar ( MAT_Rotacion(90.0, 0.0, 0.0, 1.0));
  agregar(new mediaEsfera(30,30));

  movBrazoDer = leerPtrMatriz(ind);

  ponerIdentificador(21);
  ponerNombre("BrazoD");
}

//-----------------------------------------------------------------------
// Implementación del constructor de la clase BrazoIzq
BrazoIzq :: BrazoIzq(Matriz4f * &movBrazoIzq){
  unsigned ind = agregar(MAT_Rotacion(0.0,1.0,0.0,0.0));

  agregar( MAT_Traslacion(-0.80, -0.9, 0.0));
  agregar( MAT_Escalado(0.10,0.9,0.15) );
  agregar ( MAT_Rotacion(90.0, 0.0, 0.0, 1.0));
  agregar(new mediaEsfera(30,30));

  movBrazoIzq = leerPtrMatriz(ind);

  ponerIdentificador(22);
  ponerNombre("BrazoI");
}

//-----------------------------------------------------------------------
// Implementación del constructor de la clase mediaCabezaA
mediaCabezaA :: mediaCabezaA(){
  agregar( MAT_Traslacion(0.0, 0.5, 0.0));
  agregar( MAT_Escalado(0.75,0.75,0.75) );
  agregar(new mediaEsfera(30,30));
  ponerNombre("mediaCabezaA");

  agregar( MAT_Traslacion(0.0, 0.0, 0.35));
  agregar( MAT_Escalado(0.80,0.75,0.75) );
  mediaEsfera * pantalla =new mediaEsfera(30,30);
  pantalla->ponerColor({0.0,0.0,0.0});
  agregar(pantalla);
}

//-----------------------------------------------------------------------
// Implementación del constructor de la clase mediaCabezaB
mediaCabezaB :: mediaCabezaB(){
  agregar( MAT_Traslacion(0.0, 0.5, 0.0));
  agregar ( MAT_Rotacion(180.0, 0.0, 0.0, 1.0));
  agregar( MAT_Escalado(0.75,0.40,0.75) );
  agregar(new mediaEsfera(30,30));
  ponerNombre("mediaCabezaB");

  agregar( MAT_Traslacion(0.0, 0.0, 0.35));
  agregar( MAT_Escalado(0.80,0.65,0.75) );
  mediaEsfera * pantalla =new mediaEsfera(30,30);
  pantalla->ponerColor({0.0,0.0,0.0});
  agregar(pantalla);
}

//-----------------------------------------------------------------------
// Implementación del constructor de la clase Ojos
Ojos :: Ojos(){
  agregar( MAT_Traslacion(0.0, 0.5, 0.69));
  agregar( MAT_Escalado(0.15,0.15,0.15) );
  agregar( MAT_Traslacion(-1.25, 0.0, 0.0));

  mediaEsfera * ojoI =new mediaEsfera(30,30);
  ojoI->ponerColor({0.2,0.41,1.0});
  agregar(ojoI);

  agregar( MAT_Traslacion(2.5, 0.0, 0.0));
  mediaEsfera * ojoD =new mediaEsfera(30,30);
  ojoD->ponerColor({0.2,0.41,1.0});
  agregar(ojoD);
  ponerNombre("Ojos");
}


//-----------------------------------------------------------------------
// Implementación del constructor de la clase Cabeza
Cabeza :: Cabeza(Matriz4f * &rotacionCabeza){
  unsigned ind = agregar(MAT_Rotacion(0.0,0.0,1.0,0.0));
  agregar(new mediaCabezaA());
  agregar(new mediaCabezaB());
  agregar(new Ojos());

  rotacionCabeza = leerPtrMatriz(ind);

  ponerIdentificador(1);
  ponerNombre("Cabeza");
}


//-----------------------------------------------------------------------
// Implementación del constructor de la clase Eva
Eva::Eva(Matriz4f * &traslacion, Matriz4f * &rotacionCabeza, Matriz4f * &movBrazoIzq, Matriz4f * &movBrazoDer){
  unsigned ind = agregar( MAT_Traslacion(0.0, 0.0, 0.0) );
  agregar(new Cuerpo());
  agregar(new BrazoDer(movBrazoDer));
  agregar(new BrazoIzq(movBrazoIzq));
  agregar(new Cabeza(rotacionCabeza));

  traslacion = leerPtrMatriz(ind);

  ponerIdentificador(0);
  ponerNombre("Eva");
}
