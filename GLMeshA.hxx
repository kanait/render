////////////////////////////////////////////////////////////////////
//
// $Id: GLMeshA.hxx 2020/03/12 21:51:46 kanai Exp $
//
//   OpenGL MeshA draw class
//
// Copyright (c) 2002-2020 by Takashi Kanai. All rights reserved. 
//
////////////////////////////////////////////////////////////////////

#ifndef _GLMESHA_HXX
#define _GLMESHA_HXX 1

#include "envDep.h"

#include "mydef.h"

#include <GL/gl.h>

#include "MeshA.hxx"
#include "Face.hxx"
#include "GLMesh.hxx"

#ifdef _NV_STRIP
#include "NvTriStrip.h"
#endif

static float blackvec[] = {0.0f, 0.0f, 0.0f};
static float bluevec[]  = {0.0f, 0.0f, 1.0f};
//  static float redvec[] = {1.000, 0.000, 0.000};
//  static float greenvec[] = {0.000, 1.000, 0.000}; 

static GLfloat onespecA[] = {1.f, 1.f, 1.f, 1.f};
static float grayvec[]  = { .7f, .7f, .7f };
static float darkgreenvec[] = {0.0f, 0.392f, 0.0f};


class GLMeshA : public GLMesh {

public:

  GLMeshA() { mesh_ = NULL; };
  virtual ~GLMeshA() {};

  void setMesh( MeshA& mesh ) { mesh_ = &mesh; };
  MeshA& mesh() { return *mesh_; };
  void deleteMesh() { delete mesh_; mesh_ = NULL; };
  bool empty() const { return ( mesh_ != NULL ) ? false : true; };

  void draw() {
    ::glPushMatrix();
    if ( isDrawShading_ ) { drawShading(); }
    if ( isDrawPoint_ ) { drawPoint(); }
    if ( isDrawWireframe_ ) { drawWireframe(); }
    ::glPopMatrix();
  };

  void drawShading() {

    if ( empty() ) return;

    if ( isSmoothShading_ == true ) ::glShadeModel( GL_SMOOTH );
    else ::glShadeModel( GL_FLAT );

#ifdef _RENDER_ARRAY
    if ( isSmoothShading_ )
      {
        ::glEnableClientState( GL_NORMAL_ARRAY );
        ::glNormalPointer( GL_FLOAT, 0, (GLfloat *) mesh_->normals.begin() );
      }
    ::glEnableClientState( GL_VERTEX_ARRAY );
    ::glVertexPointer( 3, GL_FLOAT, 0, (GLfloat *) mesh_->points.begin() );
    //    ::glLockArraysEXT( 0, (GLsizei) mesh_->vertices.size() );
#endif

    // Materials
    //    ::glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, onespecA );
    //    ::glMateriali( GL_FRONT_AND_BACK, GL_SHININESS, 100 );
    //    ::glColor3fv( grayvec );

    //    ::glColor3fv( whitevec );

    ::glEnable( GL_LIGHTING );

    mtl_.bind();

    if ( isSmoothShading_ )
      {
#ifdef _NV_STRIP
        for ( int i = 0; i < mesh_->n_strips; ++i )
          {
            PrimitiveGroup* tmpPG = &(mesh_->strips[i]);
            ::glDrawElements( GL_TRIANGLE_STRIP, tmpPG->numIndices,
                              GL_UNSIGNED_SHORT, (unsigned short *) tmpPG->indices );
          }
#else // _NV_STRIP
        ::glBegin( GL_TRIANGLES );
        foreach ( std::vector<Face>, mesh_->faces(), fc )
          {
            foreach ( std::vector<Vertex*>, fc->vertex(), fv )
              {
                ::glArrayElement( (*fv)->id() );
              }
          }
        ::glEnd();
#endif // _NV_STRIP
      }
    else // Flat shading
      {
        ::glBegin( GL_TRIANGLES );

        foreach ( std::vector<Face>, mesh_->faces(), fc )
          {
#ifdef _RENDER_ARRAY
            ::glNormal3fv( (GLfloat *) &mesh_->normals()[fc->getID()*3] );
#else
            Vector3d& nrm = fc->normal();
            ::glNormal3d( nrm.x, nrm.y, nrm.z );
#endif
            foreach ( std::vector<Vertex*>, fc->vertex(), fv )
              {
#ifdef _RENDER_ARRAY
                ::glArrayElement( (*fv)->getID() );
#else
                Point3d& p = (*fv)->point();
                ::glVertex3d( p.x, p.y, p.z );
#endif
              }
          }

        ::glEnd();

      }

    ::glDisable( GL_LIGHTING );

#ifdef _RENDER_ARRAY
    //    ::glUnlockArraysEXT();
    ::glDisableClientState( GL_VERTEX_ARRAY );
    if ( isSmoothShading_ )
      {
        ::glDisableClientState( GL_NORMAL_ARRAY );
      }
#endif

  };

  void drawWireframe() {
    if ( empty() ) return;

#ifdef _RENDER_ARRAY
    ::glEnableClientState( GL_VERTEX_ARRAY );
    ::glVertexPointer( 3, GL_FLOAT, 0, (GLfloat *) mesh_->points.begin() );
#endif

    //::glColor3fv( darkgreenvec );
    ::glColor3fv( blackvec );
    ::glLineWidth( .1f );

    foreach ( std::vector<Face>, mesh_->faces(), fc )
      {

        ::glBegin( GL_LINE_LOOP );
        foreach ( std::vector<Vertex*>, fc->vertex(), fv )
          {
#ifdef _RENDER_ARRAY
            ::glArrayElement( (*fv)->id() );
#else
            Point3d& p = (*fv)->point();
            ::glVertex3d( p.x, p.y, p.z );
#endif
          }
        ::glEnd();
      }

#ifdef _RENDER_ARRAY
    ::glDisableClientState( GL_VERTEX_ARRAY );
#endif

  };

  void drawPoint() {
    if ( empty() ) return;

#ifdef _RENDER_ARRAY
    ::glEnableClientState( GL_VERTEX_ARRAY );
    ::glVertexPointer( 3, GL_FLOAT, 0, (GLfloat *) mesh_->points.begin() );
#endif

    ::glPointSize( 2.5 );
    ::glColor3fv( bluevec );

    ::glBegin( GL_POINTS );
    foreach ( std::vector<Vertex>, mesh_->vertices(), vt )
      {
#ifdef _RENDER_ARRAY
        ::glArrayElement( vt->id() );
#else
        Point3d& p = vt->point();
        ::glVertex3d( p.x, p.y, p.z );
#endif
      }
    ::glEnd();
  };

  void drawPointsSelect() {

    foreach ( std::vector<Vertex>, mesh_->vertices(), vt )
      {
        ::glLoadName( (GLuint ) vt->id() );
        ::glBegin( GL_POINTS );
        Point3d& p = vt->point();
        ::glVertex3d( p.x, p.y, p.z );
        ::glEnd();
      }
  };

  void drawFacesSelect() {
    foreach ( std::vector<Face>, mesh_->faces(), fc )
      {
        ::glLoadName( (GLuint ) fc->id() );
        ::glBegin( GL_TRIANGLES );
        foreach ( std::vector<Vertex*>, fc->vertex(), fv )
          {
            Point3d& p = (*fv)->point();
            ::glVertex3d( p.x, p.y, p.z );
          }
        ::glEnd();
      }
  };

private:

  MeshA* mesh_;

};

#endif // _GLMESHA_HXX
