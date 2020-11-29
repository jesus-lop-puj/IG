// *********************************************************************
// **
// ** Gestión de matrices 4x4 (implementación)
// ** Copyright (C) 2014 Carlos Ureña
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#include <cmath>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <cassert>

#include "matrices-tr.h"


#define X 0
#define Y 1
#define Z 2

// ---------------------------------------------------------------------

Matriz4f MAT_Ident(  )
{
   Matriz4f res ;
   for( unsigned fil = 0 ; fil < 4 ; fil++ )
   for( unsigned col = 0 ; col < 4 ; col++ )
      res(fil,col) = (col == fil) ? 1.0f : 0.0f ;

   return res ;
}

//----------------------------------------------------------------------

Matriz4f MAT_Filas( const Tupla3f & fila0, const Tupla3f & fila1, const Tupla3f & fila2 )
{
   Matriz4f res = MAT_Ident();

   for( unsigned col = 0 ; col < 3 ; col++ )
   {  res(0,col) = fila0(col) ;
      res(1,col) = fila1(col) ;
      res(2,col) = fila2(col) ;
   }
   return res ;
}
// ---------------------------------------------------------------------

Matriz4f MAT_Traslacion( const float vec[3] )
{
   Matriz4f res = MAT_Ident();

   for( unsigned fil = 0 ; fil < 3 ; fil++ )
      res(fil,3) = vec[fil] ;

   return res ;
}

// ---------------------------------------------------------------------

Matriz4f MAT_Traslacion( const float dx, const float dy , const float dz )
{
   Matriz4f res = MAT_Ident();

   res(0,3) = dx ;
   res(1,3) = dy ;
   res(2,3) = dz ;

   return res ;
}
// ---------------------------------------------------------------------

Matriz4f MAT_Escalado( const float sx, const float sy, const float sz )
{
   Matriz4f res = MAT_Ident();

   res(0,0) = sx ;
   res(1,1) = sy ;
   res(2,2) = sz ;

   return res ;
}

// ---------------------------------------------------------------------

Matriz4f MAT_Rotacion( const float ang_gra, const float ex, const float ey , const float ez )
{
   const Tupla3f ejen = Tupla3f(ex,ey,ez).normalized() ;

   const double
      ang_rad = double(ang_gra)*double(2.0)*double(M_PI)/double(360.0) ,
      c       = cos(ang_rad),
      s       = sin(ang_rad);

   const double
      exn     = ejen[X],
      eyn     = ejen[Y],
      ezn     = ejen[Z],
      hx      = (1.0-c)*exn ,
      hy      = (1.0-c)*eyn ,
      hz      = (1.0-c)*ezn ;

   Matriz4f res = MAT_Ident();

   res(0,0) = hx*exn+c     ; res(0,1) = hx*eyn-s*ezn ; res(0,2) = hx*ezn+s*eyn ;
   res(1,0) = hy*exn+s*ezn ; res(1,1) = hy*eyn+c     ; res(1,2) = hy*ezn-s*exn ;
   res(2,0) = hz*exn-s*eyn ; res(2,1) = hz*eyn+s*exn ; res(2,2) = hz*ezn+c     ;

   return res ;
}

// ---------------------------------------------------------------------

Matriz4f MAT_Rotacion( const float ang_gra, const Tupla3f & eje )
{
   return MAT_Rotacion( ang_gra, eje(0), eje(1), eje(2) );
}

// ---------------------------------------------------------------------

Matriz4f MAT_LookAt( const float origen[3], const float centro[3], const float vup[3] )
{
   Tupla3f
      eje[3] ; // array con los tres vectores de los ejes del S.R. de la cámara

   eje[Z] = ( Tupla3f(origen) - Tupla3f(centro) ).normalized() ; // eje Z desde el p.a. hacia el obs., normalizado
   eje[X] = ( Tupla3f(vup).cross( eje[Z] )).normalized(),  // eje Z apunta en la dir. contraria a la camara
   eje[Y] = eje[Z].cross( eje[X] );                     // eje Y perpendicular a los otros dos.

   Matriz4f
      trasl = MAT_Traslacion( -origen[X], -origen[Y], -origen[Z] ),
      rot   = MAT_Ident() ; // matriz de cambio de base mundo --> camara

   for( unsigned col = X ; col <= Z ; col++ )
   for( unsigned fil = X ; fil <= Z ; fil++ )
      rot(fil,col) = eje[fil](col) ;

   return rot * trasl ;
}
// ---------------------------------------------------------------------

Matriz4f MAT_Frustum( const float l, const float r, const float b, const float t, const float n, const float f )
{
   const float eps = 1e-6 ;
   assert( fabs(r-l) > eps && fabs(t-b) > eps  && fabs(n-f) > eps );

   const float
      irl = 1.0f/(r-l) ,
      itb = 1.0f/(t-b) ,
      inf = 1.0f/(n-f) ;
   const float
      a0 = 2.0f*n*irl ,
      a2 = (r+l)*irl,
      b1 = 2.0f*n*itb ,
      b2 = (t+b)*itb ,
      c2 = (n+f)*inf ,
      c3 = 2.0f*f*n*inf ;

   Matriz4f
      res ;

   res(0,0) = a0  ; res(0,1) = 0.0; res(0,2) = a2  ; res(0,3) = 0.0 ;
   res(1,0) = 0.0 ; res(1,1) = b1 ; res(1,2) = b2  ; res(1,3) = 0.0 ;
   res(2,0) = 0.0 ; res(2,1) = 0.0; res(2,2) = c2  ; res(2,3) = c3  ;
   res(3,0) = 0.0 ; res(3,1) = 0.0; res(3,2) = -1.0; res(3,3) = 0.0 ;

   return res ;
}

// ---------------------------------------------------------------------

Matriz4f MAT_Ortografica( const float l, const float r, const float b, const float t, const float n, const float f )
{
   const float eps = 1e-6 ;
   assert( fabs(r-l) > eps && fabs(t-b) > eps  && fabs(n-f) > eps );

   const float
      irl = 1.0f/(l-r) ,
      itb = 1.0f/(b-t) ,
      inf = 1.0f/(n-f) ;
   const float
      a0 = -2.0f*irl ,
      a3 = (r+l)*irl,
      b1 = -2.0f*itb ,
      b3 = (t+b)*itb ,
      c2 = 2.0f*inf ,
      c3 = (f+n)*inf ;

   Matriz4f
      res ;

   res(0,0) = a0  ; res(0,1) = 0.0 ; res(0,2) = 0.0 ; res(0,3) = a3  ;
   res(1,0) = 0.0 ; res(1,1) = b1  ; res(1,2) = 0.0 ; res(1,3) = b3  ;
   res(2,0) = 0.0 ; res(2,1) = 0.0 ; res(2,2) = c2  ; res(2,3) = c3  ;
   res(3,0) = 0.0 ; res(3,1) = 0.0 ; res(3,2) = 0.0 ; res(3,3) = 1.0 ;

   return res ;
}

// ---------------------------------------------------------------------

Matriz4f MAT_Perspectiva( const float fovy_grad, const float raz_asp, const float n, const float f )
{
   const float eps = 1e-6 ;
   assert( raz_asp > eps && fovy_grad > eps  && fabs(n-f) > eps );

   const float
      fovy_rad = fovy_grad*2.0f*M_PI/360.0f,
      t = n*tan(0.5*fovy_rad),
      r = t/raz_asp,
      b = -t ,
      l = -r ;

   return MAT_Frustum( l,r,b,t,n,f );
}


// ---------------------------------------------------------------------
// traspuesta (IGNORA LAS TRASLACIONES)

Matriz4f MAT_Transpuesta3x3( const Matriz4f & org )
{
   Matriz4f res = MAT_Ident() ;

   for( unsigned i = 0 ; i < 3 ; i++ )
   for( unsigned j = 0 ; j < 3 ; j++ )
      res(i,j) = org(j,i);

   return res ;
}
//----------------------------------------------------------------------
// construir la sub-matriz 3x3 dando sus tres filas

Matriz4f MAT_Filas( const Tupla3f fila[3] )
{
   Matriz4f res = MAT_Ident();

   for( unsigned col = 0 ; col < 3 ; col++ )
   {
      res(0,col) = fila[0](col) ;
      res(1,col) = fila[1](col) ;
      res(2,col) = fila[2](col) ;
   }
   return res ;
}
//----------------------------------------------------------------------
// construir la sub-matriz 3x3 dando sus tres columnas

Matriz4f MAT_Columnas( const Tupla3f colum[3] )
{
   Matriz4f res = MAT_Ident();

   for( unsigned fil = 0 ; fil < 3 ; fil++ )
   {
      res(fil,0) = colum[0](fil) ;
      res(fil,1) = colum[1](fil) ;
      res(fil,2) = colum[2](fil) ;
   }
   return res ;
}
// ---------------------------------------------------------------------
// matriz del viewport  (deja las Z igual: entre -1 y 1)

Matriz4f MAT_Viewport( int org_x, int org_y, int ancho, int alto )
{
   return MAT_Traslacion( float(org_x), float(org_y), 0.0 )*
          MAT_Escalado( float(ancho), float(alto), 1.0 )*
          MAT_Escalado( 0.5, 0.5, 1.0 )*
          MAT_Traslacion( 1.0, 1.0, 1.0 ) ;
}
// ---------------------------------------------------------------------
// matriz inversa de la matriz del viewport

Matriz4f MAT_Viewport_inv( int org_x, int org_y, int ancho, int alto )
{
   return MAT_Traslacion( -1.0, -1.0, -1.0 ) *
          MAT_Escalado( 2.0, 2.0, 1.0 )*
          MAT_Escalado( 1.0/float(ancho), 1.0/float(alto), 1.0 )*
          MAT_Traslacion( -float(org_x), -float(org_y), 0.0 ) ;
}

// ---------------------------------------------------------------------
// matriz de vista, a partir del marco de coordenadas de la camara:
Matriz4f MAT_Vista( const Tupla3f eje[3], const Tupla3f& org )
{
   // traslación por -origen, seguida de productos escalares
   return MAT_Filas( eje )*MAT_Traslacion( -org ) ;
}
// ---------------------------------------------------------------------
// matriz inversa de la vista, a partir del marco de coordenadas de la camara:
Matriz4f MAT_Vista_inv( const Tupla3f eje[3], const Tupla3f& org )
{
   // rotaciones seguidas de traslación por origen
   return  MAT_Traslacion( org )*MAT_Columnas( eje );
}

// --------------------------------------------------
// métodos auxiliares para calcular la inversa de una matriz

// -----------------------------------------------------------------------
// calculo del determinante de la submatriz 3x3
float MAT_Determinante3x3( const Matriz4f & m )
{
   return + m(0,0)*m(1,1)*m(2,2)
          + m(0,1)*m(1,2)*m(2,0)
          + m(0,2)*m(1,0)*m(2,1)

          - m(0,0)*m(1,2)*m(2,1)
          - m(0,1)*m(1,0)*m(2,2)
          - m(0,2)*m(1,1)*m(2,0) ;
}

// --------------------------------------------------------------------
// calcula la inversa de una matriz 4x4 (sin términos de proyección)
// (la última fila debe ser 0, 0, 0, 1)

Matriz4f MAT_Inversa( const Matriz4f & m )
{
   assert( m(3,0) == 0.0 );
   assert( m(3,1) == 0.0 );
   assert( m(3,2) == 0.0 );
   assert( m(3,3) == 1.0 );

   // 1. calcular matriz de cofactores ('cofac')
   Matriz4f cofac = MAT_Ident();

   for( int i = 0 ; i < 3 ; i++ )
   for( int j = 0 ; j < 3 ; j++ )
   {
      const int i1 = (i+1)%3, i2 = (i+2)%3,
                j1 = (j+1)%3, j2 = (j+2)%3;
      cofac(i,j) = m(i1,j1)*m(i2,j2) - m(i1,j2)*m(i2,j1) ;
   }

   // 2. calcular determinante (det) (usando la primera fila de 'm' y de 'cofac')
   const float det = m(0,0)*cofac(0,0) +  m(0,1)*cofac(0,1) + m(0,2)*cofac(0,2) ;
   assert( 1e-6 < fabs(det) );
   const float inv_det = 1.0/det ;

   // 3. calcular la matriz inversa de la sub-matrix 3x3 (inv3x3) como la
   // adjunta (transpuesta de los cofactores), dividida por el determinante:
   Matriz4f inv3x3 = MAT_Ident();
   for( int i = 0 ; i < 3 ; i++ )
   for( int j = 0 ; j < 3 ; j++ )
      inv3x3(i,j) = inv_det * cofac(j,i) ;

   // 4. calcular la matriz de traslación inversa
   Matriz4f trasl_inv = MAT_Ident() ;
   for( int i = 0 ; i < 3 ; i++ )
      trasl_inv(i,3) = -m(i,3) ;

   // 5. calcular (y devolver) la inversa completa
   // (traslación inversa seguida de la inversa 3x3)
   return inv3x3 * trasl_inv;
}


// ---------------------------------------------------------------------
// juego de tests de la matrices

void MAT_TestInv( const Matriz4f & mat )
{
   using namespace std ;

   // print determinante, solo para test
   const float det = MAT_Determinante3x3( mat );
   cout << "det (1) == " << det << endl ;

   const Matriz4f inv = MAT_Inversa( mat );
   const Matriz4f ide = inv*mat ;

   cout << "mat == " << endl
        << mat << endl
        << "inv == " << endl
        << inv << endl
        << "ide == " << endl
        << ide << endl ;

}

void MAT_Tests()
{

   // test de la matriz inversa:
   const Matriz4f mat1 = MAT_Escalado( 0.5, 0.9, -1.1 )*
                        MAT_Rotacion( 34.0, 1.0, 2.0, 3.0 )*MAT_Traslacion( 1.5, -2.2, -1.1 )*MAT_Escalado( -1.5, -2.7, 5.0 )*
                        MAT_Rotacion( -130.0, -3.2, 2.0, -1.0 )*MAT_Traslacion( -0.8, 1.0, -1.7 )*MAT_Escalado( 0.5, 2.0, -1.5 );

   const Matriz4f mt = MAT_Traslacion( 1.0, 2.0, 3.0 ),
                  mr = MAT_Rotacion( -130.0, -3.2, 2.0, -1.0 ),
                  me = MAT_Escalado( 2.0, -1.0, 0.7 ) ;

   MAT_TestInv( me*mat1*mt*mr*me );

}