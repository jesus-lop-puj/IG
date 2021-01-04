#include "malla-ind.h"
#include "malla-revol.h"
#include "matrices-tr.h"
#include "latapeones.h"

LataPeones :: LataPeones(){

  agregar(new Lata());

  agregar(new PeonNegro());
  agregar(new PeonBlanco());
  agregar(new PeonMadera());

  ponerNombre("Lata y peones");
}

PeonMadera :: PeonMadera(){
  Textura * textura = new Textura("../recursos/imgs/text-madera.jpg");

  agregar(MAT_Traslacion(1,0.4,0));
  agregar(MAT_Escalado(0.3,0.3,0.3));
  agregar(new Material(textura, 0.5, 1, 1, 30));
  agregar(new MallaRevolPLY("../recursos/plys/peon.ply",70));

  ponerIdentificador(1);
  ponerNombre("Peon de madera");
}


PeonBlanco :: PeonBlanco(){
  ponerColor({1,1,1});

  agregar(MAT_Traslacion(-1,0.4,0));
  agregar(MAT_Escalado(0.3,0.3,0.3));
  agregar(new Material(0.5, 1, 0, 30));
  agregar(new MallaRevolPLY("../recursos/plys/peon.ply",70));

  ponerIdentificador(2);
  ponerNombre("Peon de madera");
}


PeonNegro :: PeonNegro(){
  ponerColor({0,0,0});

  agregar(MAT_Traslacion(0,0.4,0));
  agregar(MAT_Escalado(0.3,0.3,0.3));
  agregar(new Material(0.5, 0.1, 1, 30));
  agregar(new MallaRevolPLY("../recursos/plys/peon.ply",70));

  ponerIdentificador(3);
  ponerNombre("Peon de madera");
}


Lata :: Lata(){
  agregar(MAT_Escalado(1.5,1.5,1.5));
  agregar(MAT_Traslacion(0,0,-1.5));

  agregar(new TapaSuperiorLata());
  agregar(new CuerpoLata("../recursos/imgs/lata-coke.jpg"));
  agregar(new TapaInferiorLata());

  ponerIdentificador(4);
  ponerNombre("Lata");
}


TapaSuperiorLata :: TapaSuperiorLata(){

  agregar(new Material(0.6, 0.8, 0.8, 30));
  agregar(new MallaRevolPLY("../recursos/plys/lata-psup.ply",70));

  ponerNombre("Tapa Superior Lata");
}


TapaInferiorLata :: TapaInferiorLata(){

  agregar(new Material(0.6, 0.8, 0.8, 30));
  agregar(new MallaRevolPLY("../recursos/plys/lata-pinf.ply",70));

  ponerNombre("Tapa Superior Lata");
}


CuerpoLata :: CuerpoLata(std::string nombre){
  Textura * textura = new Textura(nombre);

  agregar(new Material(textura, 0.6, 0.9, 0.9, 30));
  agregar(new MallaRevolPLY("../recursos/plys/lata-pcue.ply",100));

  ponerNombre("Cuerpo Lata");
}

//Práctica 5

VariasLatasPeones :: VariasLatasPeones(){

  agregar(new Lata());
  agregar(new LataPepsi());
  agregar(new LataUGR());

  agregar(new PeonNegro());
  agregar(new PeonBlanco());
  agregar(new PeonMadera());

  ponerNombre("Varias latas y peones");
}

LataPepsi :: LataPepsi(){
  agregar(MAT_Escalado(1.5,1.5,1.5));
  agregar(MAT_Traslacion(1.5,0,-1.5));

  agregar(new TapaSuperiorLata());
  agregar(new CuerpoLata("../recursos/imgs/lata-pepsi.jpg"));
  agregar(new TapaInferiorLata());

  ponerIdentificador(5);
  ponerNombre("Lata Pepsi");
}

LataUGR :: LataUGR(){
  agregar(MAT_Escalado(1.5,1.5,1.5));
  agregar(MAT_Traslacion(-1.5,0,-1.5));

  agregar(new TapaSuperiorLata());
  agregar(new CuerpoLata("../recursos/imgs/window-icon.jpg"));
  agregar(new TapaInferiorLata());

  ponerIdentificador(6);
  ponerNombre("Lata UGR");
}
