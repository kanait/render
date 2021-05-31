////////////////////////////////////////////////////////////////////
//
// $Id: GLMeshL.hxx 2021/06/01 01:24:34 kanai Exp $
//
//   OpenGL MeshL draw class
//
// Copyright (c) by Takashi Kanai. All rights reserved. 
//
////////////////////////////////////////////////////////////////////

#ifndef _GLMESHL_HXX
#define _GLMESHL_HXX 1

#include "envDep.h"

#include "mydef.h"

#include <GL/gl.h>

#include "MeshL.hxx"
#include "FaceL.hxx"
#include "HalfedgeL.hxx"
#include "TexcoordL.hxx"
#include "VertexL.hxx"
#include "NormalL.hxx"
#include "BLoopL.hxx"
#include "GLMesh.hxx"

class GLMeshL : public GLMesh {

public:

  GLMeshL() : mesh_(NULL), isDrawWireframeBLoop_(true) {};
  ~GLMeshL() {
    //if ( mesh_ ) deleteMesh();
  };

  void setMesh( MeshL& mesh ) { mesh_ = &mesh; };
  MeshL& mesh() { return *mesh_; };
  void deleteMesh() { delete mesh_; mesh_ = NULL; };
  bool empty() const { return ( mesh_ != NULL ) ? false : true; };

  void setIsDrawWireframeBLoop( bool f ) { isDrawWireframeBLoop_ = f; };
  bool isDrawWireframeBLoop() const { return isDrawWireframeBLoop_; };

  void GLMeshL::draw()
  {
    ::glPushMatrix();
    if ( isDrawShading_ ) { drawShading(); }
    if ( isDrawPoint_ ) { drawPoint(); }
    if ( isDrawWireframe_ ) { drawWireframe(); }

    if ( isDrawWireframeBLoop_ ) { drawWireframeBLoop(); }


    ::glPopMatrix();
  };

  void GLMeshL::drawShading()
  {
    if ( empty() ) return;

    if ( isSmoothShading_ == false )
      ::glShadeModel( GL_FLAT );
    else
      ::glShadeModel( GL_SMOOTH );

    // ::glEnable( GL_LIGHTING );

    if ( isDrawTexture_ )
      {
        ::glEnable( GL_TEXTURE_2D );
        ::glBindTexture( GL_TEXTURE_2D, mesh().texID() );
        ::glColor3f( 1.0f, 1.0f, 1.0f );
        // cout << "on id " << mesh().texID() << endl;
      }
    else
      {
        ::glEnable( GL_LIGHTING );
        //cout << "off" << endl;
        mtl_.set(0);
        mtl_.bind();
      }

    foreach ( std::list<FaceL*>, mesh().faces(), fc )
      {
#if 0
        if ( !((*fc)->isSelected()) )
          mtl_.bind();
        else
          mtl_selected_.bind();
#endif

#if 0
        if ( !((*fc)->texID()) )
          mtl_.bind();
        else
          {
            GLMaterial myMtl;
            //myMtl.set( (*fc)->texID() * 3 );
            myMtl.bind();
          }
#endif

#if 0
        if ( isDrawTexture_ )
          {
            ::glBindTexture( GL_TEXTURE_2D, (*fc)->texID() );
            //cout << (*fc)->texID() << endl;
          }
#endif

        //::glBegin( GL_TRIANGLES );
        ::glBegin( GL_POLYGON );

        if ( isSmoothShading_ == false )
          {
            Vector3d& n = (*fc)->normal();
            ::glNormal3d( n.x, n.y, n.z );
          }

        foreach ( std::list<HalfedgeL*>, (*fc)->halfedges(), he )
          {

            if ( isSmoothShading_ && (*he)->isNormal() )
              {
                Vector3d& n = (*he)->normal()->point();
                ::glNormal3d( n.x, n.y, n.z );
              }

            if ( isDrawTexture_ && (*he)->isTexcoord() )
              {
                Point3d& t = (*he)->texcoord()->point();
                //cout << t << endl;
                ::glTexCoord2d( t.x, t.y );
              }

            Point3d& p = (*he)->vertex()->point();
            ::glVertex3d( p.x, p.y, p.z );

          }

        ::glEnd();
      }

    if ( isDrawTexture_ )
      {
        ::glBindTexture( GL_TEXTURE_2D, 0 );
        ::glDisable( GL_TEXTURE_2D );
      }
    else
      {
        ::glDisable( GL_LIGHTING );
      }
  };

  void drawWireframe() {
    if ( empty() ) return;

    ::glColor3fv( wireColor() );
    ::glLineWidth( wireSize() );

    foreach ( std::list<FaceL*>, mesh().faces(), fc )
      {
        foreach ( std::list<HalfedgeL*>,(*fc)->halfedges(), he )
          {
            // foreach ( std::list<HalfedgeL*>, mesh().halfedges(), he )
            //   {
            ::glBegin( GL_LINES );
            Point3d& p1 = (*he)->vertex()->point();
            ::glVertex3d( p1.x, p1.y, p1.z );
            Point3d& p2 = (*he)->next()->vertex()->point();
            ::glVertex3d( p2.x, p2.y, p2.z );
            ::glEnd();
          }
      }
  };

  void drawPoint() {
    if ( empty() ) return;

    if ( isSmoothShading_ == false )
      {
        ::glPointSize( pointSize() );

        ::glBegin( GL_POINTS );
        foreach ( std::list<VertexL*>, mesh().vertices(), vt )
          {
#if 1
            if ( (*vt)->isSelected() == false )
              {
                ::glColor3fv( pointColor() );
              }
            else
              {
                ::glColor3fv( selectedColor() );
              }
#endif
            Point3d& p = (*vt)->point();
            ::glVertex3d( p.x, p.y, p.z );
          }
        ::glEnd();

      }
    else
      {
        ::glShadeModel( GL_SMOOTH );
        ::glEnable( GL_LIGHTING );
        mtl_point_.bind();

        ::glBegin( GL_POINTS );
        foreach ( std::list<FaceL*>, mesh().faces(), fc )
          {
            foreach ( std::list<HalfedgeL*>,(*fc)->halfedges(), he )
              {
                // foreach ( std::list<HalfedgeL*>, mesh().halfedges(), he )
                //   {
                Vector3d& n = (*he)->normal()->point();
                ::glNormal3d( n.x, n.y, n.z );
                Point3d& p = (*he)->vertex()->point();
                ::glVertex3d( p.x, p.y, p.z );
              }
          }
        ::glEnd();

        ::glDisable( GL_LIGHTING );
      }

  };

  void drawWireframeBLoop() {
    if ( empty() ) return;
    if ( mesh().emptyBLoop() ) return;

    ::glColor3fv( boundaryColor() );
    ::glLineWidth( boundarySize() );

    BLoopL* bl = mesh().bloop();
    ::glBegin( GL_LINE_LOOP );
    foreach ( std::vector<VertexL*>, bl->vertices(), vt )
      {
        Point3d& p = (*vt)->point();
        ::glVertex3d( p.x, p.y, p.z );
      }
    ::glEnd();

    ::glColor3f( 1.0f, 1.0f, 1.0f );

  };

  void drawPointsSelect() {
    foreach ( std::list<VertexL*>, mesh().vertices(), vt )
      {
        //cout << (*vt)->id() << endl;
        ::glLoadName( (GLuint ) (*vt)->id() );
        ::glBegin( GL_POINTS );
        Point3d& p = (*vt)->point();
        ::glVertex3d( p.x, p.y, p.z );
        ::glEnd();
      }
  };

  void drawFacesSelect() {
    foreach ( std::list<FaceL*>, mesh().faces(), fc )
      {
        ::glLoadName( (GLuint ) (*fc)->id() );
        //        ::glBegin( GL_TRIANGLES );
        ::glBegin( GL_POLYGON );
        foreach ( std::list<HalfedgeL*>, (*fc)->halfedges(), he )
          {
            Point3d& p = (*he)->vertex()->point();
            ::glVertex3d( p.x, p.y, p.z );
          }
        ::glEnd();
      }
  };

private:

  MeshL* mesh_;

  bool isDrawWireframeBLoop_;

};

#endif // _GLMESHL_HXX
