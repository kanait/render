////////////////////////////////////////////////////////////////////
//
// $Id: SelMeshA.hxx 2021/06/05 13:14:48 kanai Exp $
//
// Copyright (c) 2021 Takashi Kanai
// Released under the MIT license
//
////////////////////////////////////////////////////////////////////

#ifndef _SELMESHA_HXX
#define _SELMESHA_HXX 1

#include <GL/gl.h>

#include <vector>
using namespace std;

#include "MeshA.hxx"
#include "GLMeshA.hxx"
#include "SelList.hxx"
#include "SelMesh.hxx"

class SelMeshA : public SelMesh {

public:

  SelMeshA( GLPanel* glpane, MeshA* mesh, GLMeshA* glmesh,
            BBox2* bbox, int mode ) : SelMesh( *glpane, *bbox ) {
    mesh_ = mesh;
    glmesh_ = glmesh;
    SelMesh::setRectMode( true );
    init( mode );
  };
  ~SelMeshA(){};
  SelMeshA( GLPanel* glpane, MeshA* mesh, GLMeshA* glmesh,
            int x, int y, int mode ) : SelMesh( *glpane ) {
    mesh_ = mesh;
    glmesh_ = glmesh;
    setCoord( x, y );
    SelMesh::setRectMode( false );
    init( mode );
  };

  void init( int mode ) {
    SelMesh::setMode( mode );
    if ( SelMesh::mode() == SEL_FACE )
      SelMesh::setSelectID( mesh_->faces().size() );
    else if ( SelMesh::mode() == SEL_VERTEX )
      SelMesh::setSelectID( mesh_->vertices().size() );
  };

  void draw( std::vector<int>& selected_id ) {
    GLuint* selectBuf = draw_pick();

    GLint hits = ::glRenderMode( GL_RENDER );
    if ( hits == -1 ) // 何も選択されなかったとき
      {
        delete [] selectBuf;
        return;
      }

    GLuint* ptr = selectBuf;
    for ( int i = 0; i < hits; ++i )
      {
        GLuint name = *ptr;
        // Skip
        ptr++; ptr++; ptr++;
        // 
        int id = *ptr;
        if ( (id >= 0) && ( id < maxID_ ) )
          {
            selected_id.push_back( *ptr );
          }
        ptr++;
      }

    delete [] selectBuf;

  };

  void draw( SelList& selList ) {
    selList.setType( mode() );

    GLuint* selectBuf = draw_pick();

    GLint hits = ::glRenderMode( GL_RENDER );
    if ( hits == -1 ) // 何も選択されなかったとき
      {
        delete [] selectBuf;
        return;
      }

    cout << "hitted: " << hits << endl;
    GLuint* ptr = selectBuf;
    for ( int i = 0; i < hits; ++i )
      {
        GLuint name = *ptr;
        // Skip
        ptr++; ptr++; ptr++;
        // 
        int id = *ptr;
        if ( (id >= 0) && ( id < maxID_ ) )
          {
            selList.add(*ptr);
          }
        ptr++;
      }

    delete [] selectBuf;
  };

  void applySelected( std::vector<int>& selected ) {
    for ( unsigned int i = 0; i < selected.size(); ++i )
      {
        if ( mode() == SEL_FACE )
          {
            mesh_->faces()[ selected[i] ].setIsSelected( true );
          }
        else if ( mode() == SEL_VERTEX )
          {
            mesh_->vertices()[ selected[i] ].setIsSelected( true );
          }
      }
  };

  void applySelected( SelList& selList ) {
    foreach( std::list<SelNode*>, selList.nodes(), n )
      {
        if ( mode() == SEL_FACE )
          {
            mesh_->faces()[ (*n)->id() ].setIsSelected( true );
          }
        else if ( mode() == SEL_VERTEX )
          {
            mesh_->vertices()[ (*n)->id() ].setIsSelected( true );
          }
      }
  };

private:

  MeshA* mesh_;
  GLMeshA* glmesh_;

  GLuint* draw_pick() {
    GLuint* selectBuf = SelMesh::initialize();

    ::glPushMatrix();

    SelMesh::setProjectionView();
    glpane_->setModelView();

    if ( SelMesh::mode() == SEL_FACE )
      glmesh_->drawFacesSelect();
    else if ( SelMesh::mode() == SEL_VERTEX )
      glmesh_->drawPointsSelect();

    ::glPopMatrix();
    ::glFlush();

    return selectBuf;

  };

};

#endif // _SELMESHA_HXX
