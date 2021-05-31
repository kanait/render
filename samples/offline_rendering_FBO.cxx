////////////////////////////////////////////////////////////////////
//
// $Id: offline_rendering_FBO.cxx 2021/06/01 01:03:32 kanai Exp $
//
// Copyright (c) 2004-2005 by Keio Research Institute at SFC
// All rights reserved. 
//
////////////////////////////////////////////////////////////////////

#include "envDep.h"

#include <string>
using namespace std;

#include <GL/glew.h>
//#include "GL/wglew.h"

#include <GL/glut.h>

#include "mydef.h"

#include <Point3.h>
#include <Vector3.h>
#ifdef VM_INCLUDE_NAMESPACE
using namespace kh_vecmath;
#endif // VM_INCLUDE_NAMESPACE

#include "GLPanel.hxx"
#include "GLMaterial.hxx"
#include "PNGImage.hxx"

static bool isCapture = false;
static bool isCaptureDepth = false;

////////////////////////////////////////////////////////////////////////////////

GLPanel pane;
int width = 512;
int height = 512;
// int capture_width = 512;
// int capture_height = 512;
int capture_width = 4096;
int capture_height = 4096;
// int capture_width = 8192;
// int capture_height = 8192;
GLMaterial glm;

static float myLight[] = {
  0.0f, 0.0f, 100.0f, 1.0f,
  0.8f, 0.8f, 0.8f, 1.0f,
  1.0f, 1.0f, 1.0f, 1.0f,
  0.8f, 0.8f, 0.8f, 1.0f,
  1.0f, // 0.1f,
  0.0f,  // 0.05f
  0.0f  // 0.05f
};

////////////////////////////////////////////////////////////////////////////////

#include "RenderTextureFBO.h"

RenderTextureFBO* rt;
GLenum texTarget = GL_TEXTURE_2D;
GLenum texInternalFormat = GL_RGB;
GLenum texFormat = GL_RGB;
GLenum texType = GL_UNSIGNED_BYTE;

////////////////////////////////////////////////////////////////////////////////

void display()
{
  if ( isCapture == true ) rt->Activate();
  {
    if ( isCapture == true ) pane.clear( capture_width, capture_height );
    else pane.clear( width, height );

    pane.setView();
    pane.setLight();

    ::glShadeModel( GL_SMOOTH );
    ::glEnable( GL_LIGHTING );

    glm.bind();

    glutSolidTeapot( 1.0f );
    
    ::glDisable( GL_LIGHTING );

    pane.finish();
  }

  if ( isCapture == true ) 
    {
      rt->Read();
      PNGImage pi( capture_width, capture_height, isCaptureDepth );
      string filename = (isCaptureDepth) ? "screend.png" : "screen.png";
      pi.capture_and_write( filename.c_str() );
      rt->Deactivate();

      isCapture = false;
      isCaptureDepth = false;
      ::glutPostRedisplay();

      delete rt;
    }

  ::glutSwapBuffers();
  ::glutReportErrors();
}

////////////////////////////////////////////////////////////////////////////////////

void mouse( int button, int state, int x, int y )
{
  pane.setScreenXY( x, y );
  
  // Rotate
  if ( state == GLUT_DOWN )
    {
      if ( button == GLUT_LEFT_BUTTON )        pane.startRotate();
      else if ( button == GLUT_MIDDLE_BUTTON ) pane.startZoom();
      else if ( button == GLUT_RIGHT_BUTTON )  pane.startMove();
      ::glutPostRedisplay();
    }
  else if ( state == GLUT_UP )
    {
      pane.finishRMZ();
      ::glutPostRedisplay();
    }
}

void motion( int x, int y )
{
  if ( pane.isRotate() )
    {
      pane.updateRotate( x, y );
      ::glutPostRedisplay();
    }
  if ( pane.isMove() )
    {
      pane.updateMove( x, y );
      ::glutPostRedisplay();
    }
  if ( pane.isZoom() )
    {
      pane.updateZoom( x, y );
      ::glutPostRedisplay();
    }
}

void keyboard( unsigned char c, int x, int y )
{
  switch ( c )
    {
    case 'q':
      
      exit(0);
      break;

    case 'o':

      isCapture = true;
      isCaptureDepth = true;
      texInternalFormat = GL_RGBA;
      texFormat = GL_RGBA;
      rt = new RenderTextureFBO( capture_width, capture_height, texTarget, texInternalFormat, texFormat, texType, 1 );

      break;

    case 'p':

      isCapture = true;
      texInternalFormat = GL_RGB;
      texFormat = GL_RGB;
      rt = new RenderTextureFBO( capture_width, capture_height, texTarget, texInternalFormat, texFormat, texType, 1 );

      break;

    default:
      break;

    }

  ::glutPostRedisplay();
}

int main( int argc, char* argv[] )
{
  ::glutInitWindowSize( width, height );
  ::glutInit( &argc, argv );
  ::glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
  ::glutCreateWindow( argv[0] );

  ::glutDisplayFunc( display );
  ::glutKeyboardFunc( keyboard );
  ::glutMouseFunc( mouse );
  ::glutMotionFunc( motion );

  pane.init( width, height );
  pane.initGL();
  pane.initGLEW();

  Point3f p( .0f, .0f, 8.0f );
  Vector3f v( .0f, .0f, -8.0f );
  pane.setViewPoint( p );
  pane.setViewVector( v ); 
  pane.setLightParameters( 0, myLight );
  pane.setIsGradientBackground( false );

  ::glutMainLoop();
  return 0;
}


////////////////////////////////////////////////////////////////////////////////////

