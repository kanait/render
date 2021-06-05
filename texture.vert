////////////////////////////////////////////////////////////////////
//
// $Id: texture.vert 2021/06/05 13:11:15 kanai Exp $
//
// Copyright (c) 2021 Takashi Kanai
// Released under the MIT license
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

  // テクスチャ座標，頂点位置
  gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
  gl_Position = ftransform();
}
