// Nombre: Jesús, Apellidos: López Pujazón, DNI/pasaporte: 26523483K (DDGG IG curso 20-21)

// *********************************************************************
// **
// ** Informática Gráfica, curso 2019-20
// ** Implementación de la clase 'MallaRevol'
// **
// *********************************************************************

#include "ig-aux.h"
#include "tuplasg.h"
#include "lector-ply.h"
#include "matrices-tr.h"
#include "malla-revol.h"

using namespace std ;

// *****************************************************************************




// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar
(
   const std::vector<Tupla3f> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias  // número de copias del perfil
)
{
   // COMPLETAR: Práctica 2: completar: creación de la malla....
   Tupla3f q;
   Matriz4f giro;
   unsigned m=perfil.size();

   for(unsigned i=0; i<num_copias; i++){
     giro=MAT_Rotacion((360.0*i)/(num_copias-1), 0.0, 1.0, 0.0);
     for(unsigned j=0; j<=m-1; j++){
       q=giro*perfil[j];
       vertices.push_back(q);
     }
   }

   int k;
   Tupla3i l;

   for(unsigned i=0; i<num_copias-1; i++){
     for(unsigned j=0; j<=m-2; j++){
       k=i*m+j;
       l[0]=k;
       l[1]=k+m;
       l[2]=k+m+1;
       triangulos.push_back(l);
       l[1]=k+m+1;
       l[2]=k+1;
       triangulos.push_back(l);
     }
   }


}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY
(
   const std::string & nombre_arch,
   const unsigned      nperfiles
)
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'
   // ...........................
   vector<Tupla3f> perfil;
   LeerVerticesPLY(nombre_arch, perfil);
   inicializar(perfil, nperfiles);

}

// -----------------------------------------------------------------------------
Cilindro::Cilindro
(
  const int num_verts_per, // número de vértices del perfil original (m)
  const unsigned nperfiles // número de perfiles (n)
)
{
  ponerNombre( std::string("Cilindro por revolución de radio 1" ));
  vector<Tupla3f> perfil;

  assert(num_verts_per>=4);

  float y=0.0;
  perfil.push_back({0.0, 0.0, 0.0});
  for(int i=0; i<num_verts_per-2; i++){
    y=(float)i/(num_verts_per-3);
    perfil.push_back({0.0, y, 1.0});
  }
  perfil.push_back({0.0, 1.0, 0.0});

  inicializar(perfil,nperfiles);
}


// -----------------------------------------------------------------------------
Cono::Cono
(
  const int num_verts_per, // número de vértices del perfil original (m)
  const unsigned nperfiles // número de perfiles (n)
)
{
  ponerNombre( std::string("Cono por revolución de radio 1" ));
  vector<Tupla3f> perfil;

  assert(num_verts_per>=3);

  float y=0.0;
  perfil.push_back({0.0, 0.0, 0.0});
  for(int i=0; i<num_verts_per-1; i++){
    y=(float)i/(num_verts_per-2);
    perfil.push_back({0.0, y, 1.0-y});
  }
  perfil.push_back({0.0, 1.0, 0.0});

  inicializar(perfil,nperfiles);
}


// -----------------------------------------------------------------------------
Esfera::Esfera
(
  const int num_verts_per, // número de vértices del perfil original (m)
  const unsigned nperfiles // número de perfiles (n)
)
{
  ponerNombre( std::string("Esfera por revolución de radio 1" ));
  vector<Tupla3f> perfil;

  assert(num_verts_per>=3);

  Tupla3f radio={0.0, 1.0, 0.0};
  Tupla3f y;
  Matriz4f giro;


  for(int i=0; i<num_verts_per; i++){
    giro=MAT_Rotacion((180.0*i)/(num_verts_per-1), 0.0, 0.0, 1.0);
    y=giro*radio;
    perfil.push_back(y);
  }


  perfil.push_back({0.0, 1.0, 0.0});

  inicializar(perfil,nperfiles);
}

// -----------------------------------------------------------------------------
mediaEsfera::mediaEsfera
(
  const int num_verts_per, // número de vértices del perfil original (m)
  const unsigned nperfiles // número de perfiles (n)
)
{
  ponerNombre( std::string("Esfera por revolución de radio 1" ));
  vector<Tupla3f> perfil;

  assert(num_verts_per>=3);

  Tupla3f radio={0.0, 1.0, 0.0};
  Tupla3f y;
  Matriz4f giro;


  for(int i=0; i<num_verts_per; i++){
    giro=MAT_Rotacion((90.0*i)/(num_verts_per-1), 0.0, 0.0, 1.0);
    y=giro*radio;
    perfil.push_back(y);
  }


  perfil.push_back({0.0, 0.0, 0.0}); //Para rellenar la esfera

  inicializar(perfil,nperfiles);
}
