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
  // ���_�ʒu�C�@���x�N�g��
  position = gl_ModelViewMatrix * gl_Vertex;
  normal = normalize(gl_NormalMatrix * gl_Normal);

  // �e�N�X�`�����W�C���_�ʒu
  gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
  gl_Position = ftransform();
}
