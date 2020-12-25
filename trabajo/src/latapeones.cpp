#include "malla-ind.h"
#include "malla-revol.h"
#include "matrices-tr.h"
#include "latapeones.h"

LataPeones :: LataPeones(){

  agregar(new PeonMadera());

  ponerNombre("Lata y peones");
}

PeonMadera :: PeonMadera(){
  Textura * textura = new Textura("../recursos/imgs/text-madera.jpg");

  agregar(new Material(textura, 0.2, 0.4, 0.4, 20));
  agregar(new MallaRevolPLY("../recursos/plys/peon.ply",50));

  ponerNombre("Peon de madera");
}
