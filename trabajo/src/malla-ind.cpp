// Nombre: Jesús, Apellidos: López Pujazón, DNI/pasaporte: 26523483K (DDGG IG curso 20-21)

// *********************************************************************
// **
// ** Informática Gráfica, curso 2020-21
// ** Declaraciones de la clase Objeto3D.hpp
// **
// *********************************************************************

//#include <set>   // std::set
#include "ig-aux.h"
#include "tuplasg.h"
#include "malla-ind.h"   // declaración de 'ContextoVis'
#include "lector-ply.h"
#include "seleccion.h"


// *****************************************************************************
// funciones auxiliares

// *****************************************************************************
// métodos de la clase MallaInd.

MallaInd::MallaInd()
{
   // nombre por defecto
   ponerNombre("malla indexada, anónima");
}
// -----------------------------------------------------------------------------

MallaInd::MallaInd( const std::string & nombreIni )
{
   // 'identificador' puesto a 0 por defecto, 'centro_oc' puesto a (0,0,0)
   ponerNombre(nombreIni) ;
}

//-----------------------------------------------------------------------------
// calcula la tabla de normales de triángulos una sola vez, si no estaba calculada

void MallaInd::calcularNormalesTriangulos()
{

   // si ya está creada la tabla de normales de triángulos, no es necesario volver a crearla
   const unsigned nt = triangulos.size() ;
   assert( 1 <= nt );
   if ( 0 < nor_tri.size() )
   {
      assert( nt == nor_tri.size() );
      return ;
   }

   // COMPLETAR: Práctica 4: creación de la tabla de normales de triángulos
   // ....
   Tupla3f p,q,r;
   Tupla3f a,b,n_c;
   for(unsigned int i=0; i<triangulos.size(); i++){
     p=vertices[triangulos[i](0)];
     q = vertices[triangulos[i](1)];
     r = vertices[triangulos[i](2)];

     a=q-p;
     b=r-p;
     n_c=a.cross(b);

     if(n_c.lengthSq()>0)
      nor_tri.push_back(n_c.normalized());
     else
      nor_tri.push_back({0,0,0});

   }

}


// -----------------------------------------------------------------------------
// calcula las dos tablas de normales

void MallaInd::calcularNormales()
{
   // COMPLETAR: en la práctica 4: calculo de las normales de la malla
   // se debe invocar en primer lugar 'calcularNormalesTriangulos'
   // .......
   calcularNormalesTriangulos();

   nor_ver.insert(nor_ver.begin(), vertices.size(), {0.0,0.0,0.0});
   for(unsigned int i=0; i<triangulos.size(); i++){
     nor_ver[triangulos[i](0)]=nor_ver[triangulos[i](0)]+nor_tri[i];
     nor_ver[triangulos[i](1)]=nor_ver[triangulos[i](1)]+nor_tri[i];
     nor_ver[triangulos[i](2)]=nor_ver[triangulos[i](2)]+nor_tri[i];
   }

   for(unsigned int i=0; i<vertices.size(); i++){
     if(nor_ver[i].lengthSq()>0)
      nor_ver[i]=nor_ver[i].normalized();
   }

}




// ----------------------------------------------------------------------------


void MallaInd::visualizarGL( ContextoVis & cv )
{

   using namespace std ;
   assert( cv.cauce_act != nullptr );

   if ( triangulos.size() == 0 || vertices.size() == 0 )
   {  cout << "advertencia: intentando dibujar malla vacía '" << leerNombre() << "'" << endl << flush ;
      return ;
   }

   // guardar el color previamente fijado
   const Tupla4f color_previo = leerFijarColVertsCauce( cv );

   // COMPLETAR: práctica 1: si el puntero 'array_verts' es nulo, crear el objeto ArrayVerts
   //   * en el constructor se dan los datos de la tabla de coordenadas de vértices (tabla 'vertices')
   //   * después hay que invocar a 'fijarIndices', usando el formato y datos de la tabla de triángulos ('triangulos')
   //   * si las tablas 'col_ver', 'cc_tt_ver' o 'nor_ver' no están vacías, hay que invocar los métodos
   //     'fijarColores', 'fijarCoordText' y 'fijarNormales', como corresponda.
   if(array_verts==nullptr){
     array_verts = new ArrayVertices(GL_FLOAT, 3, vertices.size(), vertices.data());
     array_verts->fijarIndices(GL_UNSIGNED_INT, 3*triangulos.size(), triangulos.data());
   }

   if(cv.modo_seleccion){
     //Leemos el identificador del objeto
     int ident = leerIdentificador();

     //Fijamos el color del cauce
     if(ident != -1)
      FijarColVertsIdent(*cv.cauce_act, ident);
   }
   else{
     if(!col_ver.empty()){
       array_verts->fijarColores(GL_FLOAT, 3, col_ver.data());
     }
     if(!cc_tt_ver.empty()){
       array_verts->fijarCoordText(GL_FLOAT, 2, cc_tt_ver.data());
     }
     if(!nor_ver.empty()){
       array_verts->fijarNormales(GL_FLOAT, nor_ver.data());
     }
   }



   // COMPLETAR: práctica 1: visualizar según el modo (en 'cv.modo_envio')
   //   ** inmediato begin/end       : usar método 'visualizarGL_MI_BVE' de 'ArrayVerts'
   //   ** inmediato con una llamada : usar método 'visualizarGL_MI_DAE' de 'ArrayVerts'
   //   ** diferido (con un VAO)     : usar método 'visualizarGL_MD_VAO' de 'ArrayVerts'
   // (en cualquier caso hay que pasar como parámetro el tipo de primitiva adecuada a una malla de triángulos).
   // .....
   if(cv.modo_envio==ModosEnvio::inmediato_begin_end){
     array_verts->visualizarGL_MI_BVE(GL_TRIANGLES);
   }
   else if(cv.modo_envio==ModosEnvio::inmediato_drawelements){
     array_verts->visualizarGL_MI_DAE(GL_TRIANGLES);
   }
   else if(cv.modo_envio==ModosEnvio::diferido_vao){
     array_verts->visualizarGL_MD_VAO(GL_TRIANGLES);
   }

   // restaurar el color previamente fijado
   glColor4fv( color_previo );

}






// *****************************************************************************


// ****************************************************************************
// Clase 'MallaPLY'

MallaPLY::MallaPLY( const std::string & nombre_arch )
{
   ponerNombre( std::string("malla leída del archivo '") + nombre_arch + "'" );

   // COMPLETAR: práctica 2: leer archivo PLY e inicializar la malla
   // ..........................
   LeerPLY(nombre_arch, vertices, triangulos);

   // COMPLETAR: práctica 4: invocar  a 'calcularNormales' para el cálculo de normales
   // .................
   calcularNormales();


}

// ****************************************************************************
// Clase 'Cubo

Cubo::Cubo()
:  MallaInd( "cubo 8 vértices" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

      calcularNormales();
}
// -----------------------------------------------------------------------------------------------

// ****************************************************************************
// Clase 'Tetraedro

Tetraedro::Tetraedro()
:  MallaInd( "tetraedro 4" )
{

   vertices =
      {  { +1.0, +0.0, +0.0 }, // 0
         { +0.0, +1.0, +0.0 }, // 1
         { +0.0, +0.0, +1.0 }, // 2
         { -1.0, +0.0, -1.0 }, // 3
      } ;



   triangulos =
      {  {0,1,2}, {0,1,3}, // X-
         {1,2,3}, {2,3,0}, // X+
      } ;


    col_ver =
      {
        { +0.0, +1.0, +1.0},
        { +0.0, +1.0, +1.0},
        { +0.0, +1.0, +1.0},
        { +0.0, +1.0, +1.0},
      };

      calcularNormales();
}
// -----------------------------------------------------------------------------------------------
// ****************************************************************************
// Clase 'CuboColores

CuboColores::CuboColores()
:  MallaInd( "cubo 8 vértices" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

      col_ver =
        {    { -1.0, -1.0, -1.0 }, // 0
             { -1.0, -1.0, +1.0 }, // 1
             { -1.0, +1.0, -1.0 }, // 2
             { -1.0, +1.0, +1.0 }, // 3
             { +1.0, -1.0, -1.0 }, // 4
             { +1.0, -1.0, +1.0 }, // 5
             { +1.0, +1.0, -1.0 }, // 6
             { +1.0, +1.0, +1.0 }, // 7
        };

        calcularNormales();
}



// -----------------------------------------------------------------------------------------------
// ****************************************************************************
// Clase Cubo24

Cubo24::Cubo24(){
  vertices = {
     {-1.0,-1.0,-1.0}, {-1.0,-1.0,1.0},
     {1.0,-1.0,-1.0}, {1.0,-1.0,1.0},

     {-1.0,1.0,-1.0}, {-1.0,1.0,1.0},
     {1.0,1.0,-1.0}, {1.0,1.0,1.0},

     {-1.0,1.0,1.0},{1.0,1.0,1.0},
     {-1.0,-1.0,1.0},{1.0,-1.0,1.0},

     {-1.0,1.0,-1.0},{1.0,1.0,-1.0},
     {-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},

     {-1.0,1.0,-1.0},{-1.0,1.0,1.0},
     {-1.0,-1.0,-1.0},{-1.0,-1.0,1.0},

     {1.0,1.0,-1.0},{1.0,1.0,1.0},
     {1.0,-1.0,-1.0},{1.0,-1.0,1.0}
  };

  triangulos = {
     {0,2,1},{3,1,2},
     {4,5,6},{7,6,5},
     {9,8,10},{9,10,11},
     {13,14,12},{13,15,14},
     {17,16,18},{17,18,19},
     {21,20,22},{21,23,22}

  };

  cc_tt_ver = {
     {0.0, 1.0},{0.0, 0.0},
     {1.0,1.0},{1.0,0.0},
     {0.0, 0.0},{0.0, 1.0},
     {1.0,0.0},{1.0,1.0},
     {0.0,0.0},{1.0,0.0},
     {0.0,1.0},{1.0,1.0},
     {1.0,0.0},{0.0,0.0},
     {1.0,1.0},{0.0,1.0},
     {0.0,0.0},{1.0,0.0},
     {0.0,1.0},{1.0,1.0},
     {1.0,0.0},{0.0,0.0},
     {1.0,1.0},{0.0,1.0},
  };

  calcularNormales();
}


// -----------------------------------------------------------------------------------------------
// ****************************************************************************
// Clase NodoCubo24

NodoCubo24::NodoCubo24(){
  Textura * textura = new Textura("../recursos/imgs/window-icon.jpg");
   agregar( new Material(textura, 1, 0.5, 1, 70) );

   agregar(new Cubo24());

   ponerNombre("Nodo de cubo con 24 vertices");
}
