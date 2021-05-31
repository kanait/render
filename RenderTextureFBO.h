////////////////////////////////////////////////////////////////////
//
// $Id: RenderTextureFBO.h 2021/06/01 01:34:43 kanai Exp $
//
// simple wrapper to encapsulate a framebuffer object using 
// render-to-texture and its associated texture object
//
// v1.0 - initial release
// v1.1 - added texFormat_, texType_ attibutes in glTexImage2D
//        to create textures
//
// Copyright (c) by Takashi Kanai. All rights reserved. 
//
////////////////////////////////////////////////////////////////////

#ifndef RENDER_TEXTURE_FBO_H
#define RENDER_TEXTURE_FBO_H

#define MAX_BUFFERS  4

const GLenum colorAttachment_[] = {
  GL_COLOR_ATTACHMENT0,
  GL_COLOR_ATTACHMENT1,
  GL_COLOR_ATTACHMENT2,
  GL_COLOR_ATTACHMENT3
};
  
class RenderTextureFBO {

public:

  RenderTextureFBO( int texWidth, int texHeight, GLenum texTarget, GLenum texInternalFormat,
                    GLenum texFormat, GLenum texType, int nDrawBuffers )
    : texWidth_(texWidth), texHeight_(texHeight), 
      texTarget_(texTarget), texInternalFormat_(texInternalFormat),
      texFormat_(texFormat), texType_(texType),
      nDrawBuffers_(nDrawBuffers)
  {
    filterMode_ = ( (texTarget == GL_TEXTURE_RECTANGLE_NV) ||
                    (texTarget == GL_TEXTURE_RECTANGLE) ) ? GL_NEAREST : GL_LINEAR;
//     maxCoordS_  = texWidth;
//     maxCoordT_  = texHeight;
    maxCoordS_  = ( (texTarget == GL_TEXTURE_RECTANGLE_NV) ||
                    (texTarget == GL_TEXTURE_RECTANGLE) ) ? texWidth : 1.0f;
    maxCoordT_  = ( (texTarget == GL_TEXTURE_RECTANGLE_NV) ||
                    (texTarget == GL_TEXTURE_RECTANGLE) ) ? texHeight : 1.0f;

    glGenFramebuffers( 1, &fb_ );
    glGenRenderbuffers( 1, &depth_rb_ );

    glBindFramebuffer( GL_FRAMEBUFFER, fb_ );

    // init textures
    buffers_.resize( nDrawBuffers );
    for ( int i = 0; i < nDrawBuffers; ++i )
      {
        createTexture( i );
        buffers_[i] = colorAttachment_[i];
        glFramebufferTexture2D( GL_FRAMEBUFFER, buffers_[i], texTarget_, tex_[i], 0 );
      }

    // initialize depth renderbuffer
    glBindRenderbuffer( GL_RENDERBUFFER, depth_rb_ );
    //glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, texWidth, texHeight );
    glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT, texWidth, texHeight );
    glBindRenderbuffer( GL_RENDERBUFFER, 0 );

    glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_rb_ );

    checkFramebufferStatus();

    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
  };

  ~RenderTextureFBO()
  {
    for ( int i = 0; i < nDrawBuffers_; ++i )
      glDeleteTextures( 1, &(tex_[i]) );
    glDeleteRenderbuffers( 1, &depth_rb_ );
    glDeleteFramebuffers( 1, &fb_ );
  };

  void Activate() { 
    glBindTexture( texTarget_, 0 );
    glBindFramebuffer( GL_FRAMEBUFFER, fb_ );
  };

  void Deactivate() { 
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
  };

  void Read( int i = 0 ) {
    glReadBuffer( buffers_[i] );
  };

  GLint tex( int i = 0 ) const { return tex_[i]; };

  void Draw( int i = 0 ) {
    glDrawBuffer( buffers_[i] );
  };

  void Bind( int i = 0 ) {
    glBindTexture( texTarget_, tex_[i] );
    glEnable( texTarget_ );  
  };
  
  void Release( int i = 0 ) {
    glBindTexture( texTarget_, tex_[i] );
    glDisable( texTarget_ );  
  };

  inline int GetWidth() { return texWidth_; }
  inline int GetHeight() { return texHeight_; }

  void drawQuad() {

    glBegin( GL_QUADS );
    {
      glTexCoord2f( .0f,        .0f );        glVertex2f( -1.0f, -1.0f );
      glTexCoord2f( maxCoordS_, .0f );        glVertex2f(  1.0f, -1.0f );
      glTexCoord2f( maxCoordS_, maxCoordT_ ); glVertex2f(  1.0f,  1.0f );
      glTexCoord2f( .0f,        maxCoordT_ ); glVertex2f( -1.0f,  1.0f );
    }
    glEnd();

  };

  void checkFramebufferStatus()
  {
    GLenum status = (GLenum) glCheckFramebufferStatus(GL_FRAMEBUFFER);
    switch(status) {
    case GL_FRAMEBUFFER_COMPLETE:
      break;
    case GL_FRAMEBUFFER_UNSUPPORTED:
      printf("Unsupported framebuffer format\n");
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
      std::cout << "[ERROR] Framebuffer incomplete: Attachment is NOT complete." << std::endl;
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
      printf("Framebuffer incomplete, missing attachment\n");
      break;
//    case GL_FRAMEBUFFER_INCOMPLETE_DUPLICATE_ATTACHMENT:
//      printf("Framebuffer incomplete, duplicate attachment\n");
//      break;
    // case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS:
    //   printf("Framebuffer incomplete, attached images must have same dimensions\n");
    //   break;
    // case GL_FRAMEBUFFER_INCOMPLETE_FORMATS:
    //   printf("Framebuffer incomplete, attached images must have same format\n");
    //   break;
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
      printf("Framebuffer incomplete, missing draw buffer\n");
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
      printf("Framebuffer incomplete, missing read buffer\n");
      break;
    default:
      assert(0);
    }
  };

private:

  GLint  texWidth_;
  GLint  texHeight_;

  GLuint fb_;  // color render target
  GLuint depth_rb_; // depth render target
  GLuint tex_[MAX_BUFFERS]; // texture

  GLenum texTarget_;
  GLenum texInternalFormat_;
  GLenum texFormat_;
  GLenum texType_;

  // for multiple draw buffers
  std::vector<GLenum> buffers_;

  GLenum filterMode_;
  int maxCoordS_;
  int maxCoordT_;

  int nDrawBuffers_;

  void createTexture( int i ) {
    glGenTextures( 1, &(tex_[i]) );
    glBindTexture( texTarget_, tex_[i] );
    glTexParameterf( texTarget_, GL_TEXTURE_MIN_FILTER, filterMode_ );
    glTexParameterf( texTarget_, GL_TEXTURE_MAG_FILTER, filterMode_ );
    glTexParameterf( texTarget_, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameterf( texTarget_, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    //glTexImage2D( texTarget_, 0, GL_RGBA8, texWidth_, texHeight_, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glTexImage2D( texTarget_, 0, texInternalFormat_, texWidth_, texHeight_, 0, texFormat_, texType_, NULL );
  };
};

#endif // RENDER_TEXTURE_FBO_H
