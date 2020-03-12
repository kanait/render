////////////////////////////////////////////////////////////////////
//
// $Id: SelMeshL.hxx 2020/03/12 22:04:57 kanai Exp $
//
// Copyright (c) 2002-2020 by Takashi Kanai. All rights reserved. 
//
////////////////////////////////////////////////////////////////////

#ifndef _SELMESHL_HXX
#define _SELMESHL_HXX 1

#include "envDep.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include <vector>
#include <cmath>
#include <set>
using namespace std;

#include "VertexL.hxx"
#include "FaceL.hxx"
#include "MeshL.hxx"
#include "GLMeshL.hxx"
#include "SelList.hxx"
#include "SelMesh.hxx"

class SelMeshL : public SelMesh {

public:

  // pick nodes into a selected box
  SelMeshL( GLPanel* glpane, MeshL* mesh, GLMeshL* glmesh,
            BBox2* bbox, int mode ) : SelMesh( *glpane, *bbox ) {
    mesh_ = mesh;
    glmesh_ = glmesh;
    SelMesh::setRectMode( true );
    init( mode );
  };
  // pick one node
  SelMeshL( GLPanel* glpane, MeshL* mesh, GLMeshL* glmesh,
            int x, int y, int mode ) : SelMesh( *glpane ) {
    setMesh( mesh );
    setGLMesh( glmesh );
    setCoord( x, y );
    SelMesh::setRectMode( false );
    init( mode );
  };
  ~SelMeshL(){};

  void init( int mode ) {
    SelMesh::setMode( mode );
    if ( SelMesh::mode() == SEL_FACE )
      SelMesh::setSelectID( mesh_->faces().size() );
    else if ( SelMesh::mode() == SEL_VERTEX )
      SelMesh::setSelectID( mesh_->vertices().size() );
    isUseEye_ = true;
  };

  void setMesh( MeshL* mesh ) { mesh_ = mesh; };
  MeshL& mesh() { return *mesh_; };

  void setGLMesh( GLMeshL* glmesh ) { glmesh_ = glmesh; };
  GLMeshL& glmesh() { return *glmesh_; };

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
            break;
          }
        ptr++;
      }

    delete [] selectBuf;
  };

  void draw( SelList& selList ) {
    selList.setType( mode() );

    ::glCullFace( GL_BACK );
    ::glEnable( GL_CULL_FACE );
    GLuint* selectBuf = draw_pick();
    ::glDisable( GL_CULL_FACE );

    GLint hits = ::glRenderMode( GL_RENDER );
    if ( hits == -1 ) // 何も選択されなかったとき
      {
        //        cout << "c" << endl;
        delete [] selectBuf;
        return;
      }

    GLuint* ptr = selectBuf;

#if 0
    for ( int j = 0; j < hits; ++j )
      cout << selectBuf[j] << endl;
#endif

    cout << hits << " hitted." << endl;

    if ( hits == 0 )
      {
        delete [] selectBuf;
        return;
      }

    std::multiset< IDInfo > idinfo;
    for ( int i = 0; i < hits; ++i )
      {
        GLuint name = *ptr;
        // 識別番号の階層の深さ

        ptr++;
        // デプスの最小値
        float depth = (float) *ptr/0x7fffffff;

        ptr++;
        // デプスの最大値

        ptr++;
        // 識別番号
        int id = *ptr;
        //        cout << "id " << id << endl;
        //        if ( (id >= 0) && ( id < maxID_ ) && (i == (hits-1)) )
        if ( (id >= 0) && ( id < maxID_ ) )
          {
            //selList.add(*ptr);
            idinfo.insert( IDInfo( id, depth ) );
          }
        ptr++;
      }

    // 最小デプス値のものだけを選択
    std::multiset<IDInfo>::iterator iiiter = idinfo.begin();
    selList.add( (*iiiter).id() );

    delete [] selectBuf;
  };

  void SelMeshL::applySelected( std::vector<int>& selected, Point3d& eye ) {
    for ( unsigned int i = 0; i < selected.size(); ++i )
      {
        if ( SelMesh::mode() == SEL_FACE )
          {
            FaceL* fc = mesh_->face( selected[i] );
            assert( fc );
            fc->setSelected( true );
            ++numSelected_;
          }
        else if ( SelMesh::mode() == SEL_VERTEX )
          {
            VertexL* vt = mesh_->vertex( selected[i] );
            assert( vt );

            if ( isUseEye_ )
              {
                Vector3d an;
                vt->calcNormal( an );
                Vector3d v1( eye - vt->point() );
                if ( an.dot( v1 ) > .0f )
                  {
                    vt->setSelected( true );
                    ++numSelected_;
                  }
              }
            else
              {
                vt->setSelected( true );
                ++numSelected_;
              }

          }
      }
  };

  void applySelected( std::vector<int>& selected ) {
    isUseEye_ = false;
    Point3d p;
    applySelected( selected, p );
  };

  void applySelected( SelList& selTemp, SelList& selList, Point3d& eye ) {
    foreach( std::list<SelNode*>, selTemp.nodes(), n )
      {
        if ( SelMesh::mode() == SEL_FACE )
          {
            FaceL* fc = mesh_->face((*n)->id());
            assert( fc );
            fc->setSelected( true );
            ++numSelected_;
          }
        else if ( SelMesh::mode() == SEL_VERTEX )
          {
            VertexL* vt = mesh_->vertex((*n)->id());
            assert( vt );

            if ( isUseEye_ )
              {
                Vector3d an;
                vt->calcNormal( an );
                Vector3d v1( eye - vt->point() );
                v1.normalize();
                if ( an.dot( v1 ) > .0f )
                  {
                    selList.add( (*n)->id() );
                    cout << "vt No." << vt->id() << " selected."
                         << " " << vt->point() << endl;
                    vt->setSelected( true );
                    ++numSelected_;
                  }
              }
            else
              {
                cout << "vt No." << vt->id() << " selected."
                     << " " << vt->point() << endl;
                selList.add( (*n)->id() );
                vt->setSelected( true );
                ++numSelected_;
              }

          }
        //break;
      }
  };

  void applySelected( SelList& selTemp, SelList& selList ) {
    isUseEye_ = false;
    Point3d p;
    applySelected( selTemp, selList, p );
  };

  void applySelected( SelList& selList ) {
    isUseEye_ = false;
    Point3d p;
    SelList selTemp;
    applySelected( selTemp, selList, p );
  };

  void SelMeshL::clearSelected() {
    if ( SelMesh::mode() == SEL_VERTEX )
      {
        foreach ( std::list<VertexL*>, mesh().vertices(), vt )
          {
            (*vt)->setSelected( false );
          }
      }
    else if ( SelMesh::mode() == SEL_FACE )
      {
        foreach ( std::list<FaceL*>, mesh().faces(), fc )
          {
            (*fc)->setSelected( false );
          }
      }

    SelMesh::clearNumSelected();
    cout << "all of selected elements were cleared." << endl;
  };

private:

  GLuint* SelMeshL::draw_pick() {
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

  MeshL* mesh_;
  GLMeshL* glmesh_;

  bool isUseEye_;

};

#endif // _SELMESHL_HXX
