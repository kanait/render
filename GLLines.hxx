////////////////////////////////////////////////////////////////////
//
// $Id: GLLines.hxx 2021/06/05 13:22:11 kanai Exp $
//
// Copyright (c) 2021 Takashi Kanai
// Released under the MIT license
//
////////////////////////////////////////////////////////////////////

#ifndef _GLLINES_HXX
#define _GLLINES_HXX 1

#include "envDep.h"

#include <GL/gl.h>

#include <vector>
using namespace std;

#include "Point3.h"
#include "Vector3.h"
#ifdef VM_INCLUDE_NAMESPACE
using namespace kh_vecmath;
#endif // VM_INCLUDE_NAMESPACE

#include "GLMesh.hxx"

#define OFFSET 1.0e-02

class GLLines : public GLMesh {

public:

  GLLines() : points_(NULL), normals_(NULL) {};
  GLLines( std::vector<Point3f>& p ) { setPoints( p ); };
  ~GLLines(){};

  void setPoints( std::vector<Point3f>& p ) { points_ = &p; };
  std::vector<Point3f>& point() { return *points_; };
  void setNormals( std::vector<Vector3f>& p ) { normals_ = &p; };
  std::vector<Vector3f>& normal() { return *normals_; };

  bool empty() const { return ( points_ != NULL ) ? false : true; };

  void draw() {
    ::glPushMatrix();
    if ( isDrawWireframe_ ) drawLines();
    if ( isDrawPoint_ ) drawPoints();
    ::glPopMatrix();
  };

  void drawLines() {
    if ( empty() ) return;

    ::glColor3fv( wireColor() );
    ::glLineWidth( wireSize() );

    ::glBegin( GL_LINE_STRIP );
    for ( int i = 0; i < points_->size(); ++i )
      {
        Point3f& p = (*points_)[i];
        float x, y, z;
        if ( normals_ )
          {
            Vector3f& n =(*normals_)[i]; 
            x = p.x + OFFSET * n.x;
            y = p.y + OFFSET * n.y;
            z = p.z + OFFSET * n.z;
          }
        else
          {
            x = p.x; y = p.y; z = p.z;
          }
        glVertex3f( x, y, z );
      }
    ::glEnd();
  };

  void drawPoints() {
    if ( empty() ) return;
  
    ::glColor3fv( pointColor() );
    ::glPointSize( pointSize() );

    ::glBegin( GL_POINTS );
    for ( int i = 0; i < points_->size(); ++i )
      {
        Point3f& p = (*points_)[i];
        float x, y, z;
        if ( normals_ )
          {
            Vector3f& n =(*normals_)[i]; 
            x = p.x + OFFSET * n.x;
            y = p.y + OFFSET * n.y;
            z = p.z + OFFSET * n.z;
          }
        else
          {
            x = p.x; y = p.y; z = p.z;
          }
        glVertex3f( x, y, z );
      }
    ::glEnd();
  };

private:

  std::vector<Point3f>* points_;
  std::vector<Vector3f>* normals_;

};

#endif // _GLLINES_HXX

