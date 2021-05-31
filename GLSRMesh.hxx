////////////////////////////////////////////////////////////////////
//
// $Id: GLSRMesh.hxx 2021/06/01 01:25:55 kanai Exp $
//
//   OpenGL SRMesh rendering class
//
// Copyright (c) by Takashi Kanai. All rights reserved. 
//
////////////////////////////////////////////////////////////////////

#ifndef _GLSRMESH_HXX
#define _GLSRMESH_HXX 1

#include "envDep.h"

#include "mydef.h"

#include <GL/gl.h>

//  #include <Point3.h>
#include <Vector3.h>
#ifdef VM_INCLUDE_NAMESPACE
using namespace kh_vecmath;
#endif // VM_INCLUDE_NAMESPACE

#include "SRMesh.hxx"
#include "PMVertex.hxx"
#include "GLMesh.hxx"

//static float blackvec[] = {0.0f, 0.0f, 0.0f};
//static float bluevec[] = {0.0f, 0.0f, 1.0f};
//  static float redvec[] = {1.000, 0.000, 0.000};
//  static float greenvec[] = {0.000, 1.000, 0.000}; 

//static GLfloat onespecA[] = {1.f, 1.f, 1.f, 1.f};
//static float grayvec[] = { .5f, .5f, .5f };


class GLSRMesh : public GLMesh {

public:

  GLSRMesh() { mesh_ = NULL; };
  virtual ~GLSRMesh() {};
  
  void setMesh( SRMesh& mesh ) { mesh_ = &mesh; };
  SRMesh& mesh() { return *mesh_; };
  void deleteMesh() { delete mesh_; mesh_ = NULL; };
  bool empty() const { return ( mesh_ != NULL ) ? false : true; };

  void drawShading() {
    if ( empty() ) return;

//    ::glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, onespecA);
//    ::glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 128);
//    ::glColor3fv( grayvec );
  //::glColor3f( 0, .5, 1.0 );

//    GLMaterial glm;
    ::glEnable( GL_LIGHTING );

    mtl_.bind();

    ::glBegin( GL_TRIANGLES );
    foreach ( std::list<PMAFace*>, mesh_->active_faces(), fc )
      {
        Vector3d& nrm = (*fc)->normal();
        ::glNormal3d( nrm.x, nrm.y, nrm.z );
        //glm.bindingMaterial( &(mesh_->material) );

        for ( int i = 0; i < 3; ++i )
          {
            //foreach ( std::vector<PMAVertex*>, (*fc)->vertex, fv ) {
            //        PMVertex& vt = (*fc)->pmavertex(i)->pmvertex();
            Point3d& p = (*fc)->pmavertex(i)->pmvertex().point();
            ::glVertex3d( p.x, p.y, p.z );
            //cout << "\tmate " << fc->face_mate[i]->id << endl;
          }
      }
    ::glEnd();
    ::glDisable( GL_LIGHTING );
  };

  void drawWireframe() {
    if ( empty() ) return;

    //::glColor3fv( darkgreenvec );
    ::glColor3fv( blackvec );
    ::glLineWidth( .1f );

    foreach ( std::list<PMAFace*>, mesh_->active_faces(), fc ) {

      ::glBegin( GL_LINE_LOOP );
      for ( int i = 0; i < 3; ++i ) {
        Point3d& p = (*fc)->pmavertex(i)->pmvertex().point();
        ::glVertex3d( p.x, p.y, p.z );
      }
      ::glEnd();

    }

  };

  void drawPoint() {
    if ( empty() ) return;

    ::glPointSize( 2.5 );
    ::glColor3fv( bluevec );

    ::glBegin( GL_POINTS );
    foreach ( std::list<PMAVertex*>, mesh_->active_vertices(), vt )
      {
//      PMVertex* p = (*vt)->vertex;
        Point3d& p = (*vt)->pmvertex().point();
        ::glVertex3d( p.x, p.y, p.z );
      }
    ::glEnd();
  };

private:

  SRMesh* mesh_;

};

#endif // _GLSRMESH_HXX
