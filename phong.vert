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
  // ���_�ʒu�C�@���x�N�g��
  position = gl_ModelViewMatrix * gl_Vertex;
  normal = normalize(gl_NormalMatrix * gl_Normal);

  // ���_�ʒu
  gl_Position = ftransform();
}
