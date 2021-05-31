////////////////////////////////////////////////////////////////////
//
// $Id: phong.vert 2021/06/01 01:30:54 kanai Exp $
//
// Copyright (c) by Takashi Kanai. All rights reserved. 
//
////////////////////////////////////////////////////////////////////

#version 120

varying vec4 position;
varying vec3 normal;

void main(void)
{
  // 頂点位置，法線ベクトル
  position = gl_ModelViewMatrix * gl_Vertex;
  normal = normalize(gl_NormalMatrix * gl_Normal);

  // 頂点位置
  gl_Position = ftransform();
}
