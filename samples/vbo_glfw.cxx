////////////////////////////////////////////////////////////////////
//
// $Id: vbo_glfw.cxx 2021/06/01 00:43:29 kanai Exp $
//
// Copyright (c) 2004-2021 by Takashi Kanai. All rights reserved.
//
////////////////////////////////////////////////////////////////////

#include "envDep.h"

#include "GL/glew.h"
#if defined(WIN32)
#include "GL/wglew.h"
#endif

#include <GLFW/glfw3.h>

#include "mydef.h"

#include <Point3.h>
#include <Vector3.h>
#ifdef VM_INCLUDE_NAMESPACE
using namespace kh_vecmath;
#endif // VM_INCLUDE_NAMESPACE

#include "GLPanel.hxx"
#include "GLMaterial.hxx"
#include "VWIO.hxx"
#include "PNGImage.hxx"

int width = 1024;
int height = 1024;

GLPanel pane;

bool pngflag = false;
// keyboard
bool shift_key_pressed = false;
bool control_key_pressed = false;
// mouse
bool left_button_pressed = false;
bool right_button_pressed = false;

#define RENDER_VBO 0
#define RENDER_VAR 1
unsigned short render_mode = RENDER_VBO;

// current shader for shading
unsigned short shading_program = PHONG_SHADING;

#include <sstream>

#include "strutil.h"
//#include "gzfileopen.h"

//GzFileOpen gzfile;

////////////////////////////////////////////////////////////////////////////////////

#include "nvtimer.h"

timer fps(10);
// char buf[BUFSIZ];
// char txt[BUFSIZ];
float max_fps = 0.0f;
// bool first = true;

////////////////////////////////////////////////////////////////////////////////////

#include "c11timer.hxx"

C11Timer c11fps;
double max_c11fps = 0.0;

////////////////////////////////////////////////////////////////////////////////////

#include "SMFRIO.hxx"
#include "OFFRIO.hxx"
#include "MeshR.hxx"
#include "GLMeshVBO.hxx"
#include "GLMeshR.hxx"

MeshR   meshR;

GLMeshVBO glmeshvbo;
GLMeshR glmeshr;

////////////////////////////////////////////////////////////////////////////////////

void checkGLErrors(char *s)
{
  GLenum error;
  while ((error = glGetError()) != GL_NO_ERROR) {
    fprintf(stderr, "%s: error - %s\n", s, (char *) gluErrorString(error));
  }
}

////////////////////////////////////////////////////////////////////////////////////

void display()
{
  pane.clear( width, height );
  pane.setView();

  float current_light[3];
  pane.getRealLightPosition( current_light );
  pane.setLightPos( 0, current_light[0], current_light[1], current_light[2], 1.0f );

  pane.setLight();

  pane.changeProgram( shading_program );
  if ( render_mode == RENDER_VBO )
    {
      glmeshvbo.drawShading();
    }
  else if ( render_mode == RENDER_VAR )
    {
      //       glmeshr.drawColor();
      glmeshr.drawShading();
    }
  if ( glmeshvbo.isDrawWireframe() )
    {
      pane.changeProgram( WIREFRAME );
      if ( render_mode == RENDER_VBO )
        {
          glmeshvbo.drawWireframe();
        }
      else if ( render_mode == RENDER_VAR )
        {
          //       glmeshr.drawColor();
          glmeshr.drawWireframe();
        }
    }

  pane.finish();
  //   checkGLErrors("display");
}

////////////////////////////////////////////////////////////////////////////////////

static void error_callback(int error, const char* description)
{
  fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  // ESC
  if ( (key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS) )
    glfwSetWindowShouldClose(window, GL_TRUE);

  // q
  else if ( (key == GLFW_KEY_Q) && (action == GLFW_PRESS) )
    glfwSetWindowShouldClose(window, GL_TRUE);

  // 1
  else if ( (key == GLFW_KEY_1) && (action == GLFW_PRESS) )
    render_mode = RENDER_VBO;

  // 2
  else if ( (key == GLFW_KEY_2) && (action == GLFW_PRESS) )
    render_mode = RENDER_VAR;

  // 3 PHONG_SHADING
  else if ( (key == GLFW_KEY_3) && (action == GLFW_PRESS) )
    {
      shading_program = PHONG_SHADING;
      pane.changeProgram( shading_program );
    }

  // 4 GOURAND_SHADING
  else if ( (key == GLFW_KEY_4) && (action == GLFW_PRESS) )
    {
      shading_program = GOURAND_SHADING;
      pane.changeProgram( shading_program );
    }

  // w
  else if ( (key == GLFW_KEY_W) && (action == GLFW_PRESS) )
    {
      if ( glmeshvbo.isDrawWireframe() == false )
        {
          glmeshvbo.setIsDrawWireframe( true );
        }
      else
        {
          glmeshvbo.setIsDrawWireframe( false );
        }
    }
  
  // s
  else if ( (key == GLFW_KEY_S) && (action == GLFW_PRESS) )
    {
      cout << "output to file ... " << endl;
      SMFRIO rio_output( meshR );
      rio_output.outputToFile( "tmp.smf" );
      cout << "done." << endl;
    }

  // i
  else if ( (key == GLFW_KEY_I) && (action == GLFW_PRESS) )
    {
      cout << "output to .vw file ... " << endl;
      VWIO vw_out;
      vw_out.outputToFile( "tmp.vw", pane.manip() );
      cout << "done." << endl;
    }

  // p
  else if ( (key == GLFW_KEY_P) && (action == GLFW_PRESS) )
    {
      pngflag = true;
    }

  // shift
  else if ( (key == GLFW_KEY_LEFT_SHIFT ) && (action == GLFW_PRESS) )
    {
      shift_key_pressed = true;
    }
  else if ( (key == GLFW_KEY_LEFT_SHIFT ) && (action == GLFW_RELEASE) )
    {
      shift_key_pressed = false;
    }

  // control
  else if ( (key == GLFW_KEY_LEFT_CONTROL ) && (action == GLFW_PRESS) )
    {
      control_key_pressed = true;
    }
  else if ( (key == GLFW_KEY_LEFT_CONTROL ) && (action == GLFW_RELEASE) )
    {
      control_key_pressed = false;
    }
}

static void mousebutton_callback(GLFWwindow* window, int button, int action, int mods)
{
  double xd, yd;
  glfwGetCursorPos( window, &xd, &yd );
  pane.setScreenXY( (int) xd, (int) yd );

  if ( (button == GLFW_MOUSE_BUTTON_1) && (action == GLFW_PRESS) )
    {
      // cout << "left button pressed." << endl;
      left_button_pressed = true;
      pane.startRotate();
      pane.startZoom();
      pane.startMove();
    }
  else if ( (button == GLFW_MOUSE_BUTTON_1) && (action == GLFW_RELEASE) )
    {
      left_button_pressed = false;
      pane.finishRMZ();
    }
  else if ( (button == GLFW_MOUSE_BUTTON_2) && (action == GLFW_PRESS) )
    {
      // cout << "right button pressed." << endl;
      right_button_pressed = true;
    }
  else if ( (button == GLFW_MOUSE_BUTTON_2) && (action == GLFW_RELEASE) )
    {
      right_button_pressed = false;
    }
}

static void cursorpos_callback(GLFWwindow* window, double xd, double yd )
{
  int x = (int) xd;
  int y = (int) yd;

  if ( left_button_pressed && !shift_key_pressed && !control_key_pressed )
    {
      pane.updateRotate( x, y );
    }
  else if ( left_button_pressed && shift_key_pressed && !control_key_pressed )
    {
      pane.updateZoom( x, y );
    }
  else if ( left_button_pressed && !shift_key_pressed && control_key_pressed )
    {
      pane.updateMove( x, y );
    }
}

// mouse wheel
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  //cout << yoffset << endl;
  pane.updateWheelZoom( yoffset );
}

// window resize
static void windowsize_callback(GLFWwindow* window, int w, int h )
{
  width = w;
  height = h;
  pane.changeSize( w, h );
}

////////////////////////////////////////////////////////////////////////////////////

int main( int argc, char **argv )
{
  char filename[BUFSIZ];
  if ( (argc < 2) || (argc > 2) )
    {
      std::cerr << "Usage: " << argv[0] << " in.off (or in.off.gz) ." << std::endl;
      exit(1);
    }

  strcpy( filename, argv[1] );
  std::string fstr( filename );
  StrUtil s;
  std::string ext = s.GetExtension( fstr );

  OFFRIO offrio_input( meshR );
  if ( !ext.compare("gz") )
    {
      // gzip file open
      offrio_input.inputGZFromFile( filename );
    }
  else
    {
      // ascii file open
      offrio_input.inputFromFile( filename );
    }

  meshR.normalize();
  if ( meshR.normals().empty() ) meshR.createVertexNormals();

  // GLGW initialization
  glfwSetErrorCallback(error_callback);
  if ( !glfwInit() ) return EXIT_FAILURE;

  GLFWwindow* window = glfwCreateWindow( width, height, "VBO GLFW", NULL, NULL );
  if ( !window )
    {
      glfwTerminate();
      return EXIT_FAILURE;
    }
  glfwMakeContextCurrent( window );
  glfwSetKeyCallback( window, key_callback );
  glfwSetMouseButtonCallback( window, mousebutton_callback );
  glfwSetCursorPosCallback( window, cursorpos_callback );
  glfwSetScrollCallback( window, scroll_callback );
  glfwSetWindowSizeCallback( window, windowsize_callback );

  pane.init( width, height );

  // Initialize some state for window's rendering context.
  pane.initGL();
  pane.initGLEW();

  if ( !pane.initShader() ) return -1;

  Point3f p( .0f, .0f, 2.5f );
  Vector3f v( .0f, .0f, -2.5f );
  pane.setViewPoint( p );
  pane.setViewVector( v ); 
  pane.setIsGradientBackground( false );

  glfwSwapInterval(0);

  VWIO vw_in;
  if ( argc == 3 )
    {
      vw_in.inputFromFile( argv[2], pane.manip() );
    }

  glmeshr.setMesh( meshR );
  glmeshr.setIsSmoothShading( true );

  glmeshvbo.setMesh( meshR );
  glmeshvbo.setIsSmoothShading( true );

  c11fps.ResetFPS();

  // GLFW rendering process
  while ( !glfwWindowShouldClose(window) )
    {
      display();

      char buf[BUFSIZ];
      char txt[BUFSIZ];

      // for measuring fps
      double f = c11fps.CheckGetFPS();
      if ( max_c11fps < f ) max_c11fps = f;
      sprintf( buf, "%.3f fps - max %.3f fps", f, max_c11fps );

      sprintf( txt, "VBO GLFW - %s", buf );
      glfwSetWindowTitle( window, txt );

      if ( pngflag )
        {
          PNGImage pi( width, height, false );
          pi.capture_and_write("screen.png");
          pngflag = false;
        }

      glfwSwapBuffers(window);
      glfwPollEvents();
    }

  glfwDestroyWindow(window);
  glfwTerminate();

  return EXIT_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////
