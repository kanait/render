////////////////////////////////////////////////////////////////////
//
// $Id: mtldata.h 2021/06/05 13:17:28 kanai Exp $
//
// Copyright (c) 2021 Takashi Kanai
// Released under the MIT license
//
////////////////////////////////////////////////////////////////////

#ifndef _MTLDATA_H
#define _MTLDATA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "envDep.h"

#if 0  
// material structure
  
typedef struct _material {
  float ambient[4];
  float diffuse[4];
  float emission[4];
  float specular[4];
  float shininess[1];
} Material;

#endif

#define MTLNUM 36
#define NUM_MTL_ITEMS 17

// 0 グレー（光沢あり）
// 1 黄（光沢なし）
// 2 黄土（光沢あり）
// 3 黄（光沢なし）
// 4 黄土（光沢あり）
// 5 オレンジ（光沢なし）
// 6 オレンジ（光沢あり）
// 7 オレンジ（光沢なし）
// 8 赤オレンジ（光沢あり）
// 9 赤オレンジ（光沢なし）
// 10 赤（光沢あり）
// 11 赤ピンク（光沢なし）
// 12 赤紫（光沢あり）
// 13 赤紫（光沢なし）
// 14 赤紫（光沢あり）
// 15 赤紫（光沢なし）
// 16 紫（光沢あり）
// 17 紫（光沢なし）
// 18 青紫（光沢あり）
// 19 青紫（光沢なし）
// 20 青（光沢あり）
// 21 青（光沢なし）
// 22 淡青（光沢あり）
// 23 淡青（光沢なし）
// 24 空青（光沢あり）
// 25 青緑（光沢なし）
// 26 青緑（光沢あり）
// 27 黄緑（光沢なし）
// 28 黄緑（光沢あり）
// 29 黄緑（光沢なし）
// 30 黄緑（光沢あり）
// 31 白（光沢あり）
// 32 濃グレー（光沢あり）
// 33 濃グレー（光沢なし）
// 34 黒（光沢あり）
// 35 黒（光沢なし）

static const char *(mtltxt[]) = {
  "default",
  "tropical0",
  "tropical1",
  "tropical2",
  "tropical3",
  "tropical4",
  "tropical5",
  "tropical6",
  "tropical7",
  "tropical8",
  "tropical9",
  "tropical10",
  "tropical11",
  "tropical12",
  "tropical13",
  "tropical14",
  "tropical15",
  "tropical16",
  "tropical17",
  "tropical18",
  "tropical19",
  "tropical20",
  "tropical21",
  "tropical22",
  "tropical23",
  "tropical24",
  "tropical25",
  "tropical26",
  "tropical27",
  "tropical28",
  "tropical29",
  "tropical30",
  "tropical31",
  "tropical32",
  "tropical33",
  "tropical34",
};

// material all

static float mtlall[] = {
  
  // default
  //{
  0.2f, 0.2f, 0.2f, 1.0f, 
  0.8f, 0.8f, 0.8f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.8f, 0.8f, 0.8f, 1.0f, 
  80.0f,
  //}
  // tropical0
  //{ 
  0.219385f, 0.226102f, 0.0f, 1.0f, 
  0.877539f, 0.904409f, 0.0f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f,
  0.095591f, 0.095591f, 0.095591f, 1.0f, 
  10.0f,
  //}
  // tropical1
  //{
  0.187004f, 0.155212f, 0.0f, 1.0f, 
  0.748014f, 0.620850f, 0.0f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.860606f, 0.860606f, 0.860599f, 1.0f, 
  120.241997f,
  //}
  // tropical2
  //{
  0.226102f, 0.193685f, 0.020767f, 1.0f, 
  0.904409f, 0.774741f, 0.083067f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.095591f, 0.095591f, 0.095591f, 1.0f, 
  10.0f,
  //}
  // tropical3
  //{
  0.187004f, 0.138930f, 0.0f, 1.0f, 
  0.748016f, 0.555721f, 0.0f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.836364f, 0.836364f, 0.836364f, 1.0f, 
  77.575798f,
  //}
  // tropical4
  //{
  0.226102f, 0.103065f, 0.0f, 1.0f, 
  0.904409f, 0.412258f, 0.0f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.095591f, 0.095591f, 0.095591f, 1.0f, 
  10.0f,
  //}
  // tropical5
  //{
  0.187004f, 0.074884f, 0.0f, 1.0f, 
  0.748016f, 0.299537f, 0.0f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.836364f, 0.836364f, 0.836364f, 1.0f, 
  117.915001f,
  //}
  // tropical6
  //{
  0.226102f, 0.070938f, 0.0f, 1.0f, 
  0.904409f, 0.283754f, 0.0f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.095591f, 0.095591f, 0.095591f, 1.0f, 
  10.0f,
  //}
  // tropical7
  //{
  0.187004f, 0.034892f, 0.0f, 1.0f, 
  0.748016f, 0.139569f, 0.0f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.709091f, 0.709091f, 0.709091f, 1.0f, 
  61.284901f,
  //}
  // tropical8
  //{
  0.226102f, 0.037578f, 0.0f, 1.0f, 
  0.904409f, 0.150314f, 0.0f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.095591f, 0.095591f, 0.095591f, 1.0f, 
  10.0f,
  //}
  // tropical9
  //{
  0.187004f, 0.0f, 0.010022f, 1.0f, 
  0.748016f, 0.0f, 0.040087f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.896970f, 0.896970f, 0.896970f, 1.0f, 
  128.0f,
  //}
  // tropical10
  //{
  0.226102f, 0.0f, 0.077463f, 1.0f, 
  0.904409f, 0.0f, 0.309851f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.095591f, 0.095591f, 0.095591f, 1.0f, 
  10.0f,
  //}
  // tropical11
  //{
  0.187004f, 0.001565f, 0.062983f, 1.0f, 
  0.748016f, 0.006259f, 0.251931f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.684848f, 0.684848f, 0.684848f, 1.0f, 
  119.467003f,
  //}
  // tropical12
  //{
  0.226102f, 0.011737f, 0.124027f, 1.0f, 
  0.904409f, 0.046947f, 0.496108f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.095591f, 0.095591f, 0.095591f, 1.0f, 
  10.0f,
  //}
  // tropical13
  //{
  0.187004f, 0.0f, 0.137588f, 1.0f, 
  0.748016f, 0.0f, 0.550351f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.672727f, 0.672727f, 0.672727f, 1.0f, 
  29.478800f,
  //}
  // tropical14
  //{
  0.223992f, 0.0f, 0.172818f, 1.0f, 
  0.895967f, 0.0f, 0.691271f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.095591f, 0.086256f, 0.093458f, 1.0f, 
  10.0f,
  //}
  // tropical15
  //{
  0.156092f, 0.0f, 0.187004f, 1.0f, 
  0.624368f, 0.0f, 0.748016f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.951515f, 0.951515f, 0.951515f, 1.0f, 
  71.369698f,
  //}
  // tropical16
  //{
  0.155445f, 0.005229f, 0.220045f, 1.0f, 
  0.621780f, 0.020917f, 0.880181f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.087726f, 0.069438f, 0.095591f, 1.0f, 
  10.0f,
  //}
  // tropical17
  //{
  0.093502f, 0.0f, 0.187004f, 1.0f, 
  0.374008f, 0.0f, 0.748016f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.909091f, 0.909091f, 0.909091f, 1.0f, 
  51.975800f,
  //}
  // tropical18
  //{
  0.069875f, 0.001285f, 0.211477f, 1.0f, 
  0.279501f, 0.005142f, 0.845907f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.052278f, 0.031298f, 0.095591f, 1.0f, 
  10.0f,
  //}
  // tropical19
  //{
  0.000579f, 0.0f, 0.187004f, 1.0f, 
  0.002317f, 0.0f, 0.748016f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.884848f, 0.884848f, 0.884848f, 1.0f, 
  106.278999f,
  //}
  // tropical20
  //{
  0.0f, 0.051239f, 0.211311f, 1.0f, 
  0.0f, 0.204955f, 0.845242f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.030170f, 0.046033f, 0.095591f, 1.0f, 
  10.0f,
  //}
  // tropical21
  //{
  0.005183f, 0.084911f, 0.187004f, 1.0f, 
  0.020732f, 0.339645f, 0.748016f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.903030f, 0.903030f, 0.903030f, 1.0f, 
  118.691002f,
  //}
  // tropical22
  //{
  0.0f, 0.149246f, 0.204489f, 1.0f, 
  0.0f, 0.596985f, 0.817956f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.0f, 0.069767f, 0.095591f, 1.0f, 
  10.0f,
  //}
  // tropical23
  //{
  0.0f, 0.157811f, 0.187004f, 1.0f, 
  0.0f, 0.631244f, 0.748016f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.915152f, 0.915152f, 0.915152f, 1.0f, 
  82.230301f,
  //}
  // tropical24
  //{
  0.0f, 0.204489f, 0.138459f, 1.0f, 
  0.0f, 0.817956f, 0.553836f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.0f, 0.095591f, 0.064724f, 1.0f, 
  10.0f,
  //}
  // tropical25
  //{
  0.0f, 0.187004f, 0.117351f, 1.0f, 
  0.0f, 0.748016f, 0.469403f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  1.0f, 1.0f, 1.0f, 1.0f, 
  104.726997f,
  //}
  // tropical26
  //{
  0.013288f, 0.204489f, 0.022004f, 1.0f, 
  0.053153f, 0.817956f, 0.088018f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.006212f, 0.095591f, 0.010286f, 1.0f, 
  10.0f,
  //}
  // tropical27
  //{
  0.0f, 0.187004f, 0.044004f, 1.0f, 
  0.0f, 0.748016f, 0.176015f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.981818f, 0.981818f, 0.981818f, 1.0f, 
  92.315102f,
  //}
  // tropical28
  //{
  0.088844f, 0.204489f, 0.003949f, 1.0f, 
  0.355377f, 0.817956f, 0.015797f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.041531f, 0.095591f, 0.001846f, 1.0f, 
  10.0f,
  //}
  // tropical29
  //{
  0.095486f, 0.187004f, 0.0f, 1.0f, 
  0.381944f, 0.748016f, 0.0f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.963636f, 0.963636f, 0.963636f, 1.0f, 
  125.672997f,
  //}
  // tropical30
  //{
  0.247933f, 0.234873f, 0.250000f, 1.0f, 
  0.991732f, 0.939493f, 1.0f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.0f,
  //}
  // tropical31
  //{
  0.106266f, 0.101217f, 0.106572f, 1.0f, 
  0.425062f, 0.404868f, 0.426289f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.860606f, 0.860606f, 0.860606f, 1.0f, 
  115.587997f,
  //}
  // tropical32
  //{
  0.106059f, 0.106059f, 0.106059f, 1.0f, 
  0.424238f, 0.424238f, 0.424238f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.168000f, 0.168000f, 0.168000f, 1.0f, 
  19.673100f,
  //}
  // tropical33
  //{
  0.038095f, 0.036285f, 0.038205f, 1.0f, 
  0.152381f, 0.145141f, 0.152820f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.745455f, 0.745455f, 0.745455f, 1.0f, 
  122.570000f,
  //}
  // tropical34
  //{
  0.034667f, 0.034667f, 0.034667f, 1.0f, 
  0.138667f, 0.138667f, 0.138667f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.168000f, 0.168000f, 0.168000f, 1.0f, 
  19.673100f,
  //}
};

#if 0
  
static Material tropical0[] = {
  {0.219385f, 0.226102f, 0.0f, 1.0f}, 
  {0.877539f, 0.904409f, 0.0f, 1.0f}, 
  {0.0f, 0.0f, 0.0f, 1.0f}, 
  {0.095591f, 0.095591f, 0.095591f, 1.0f}, 
  {10.0f}
};


static Material tropical1[] = {
  0.187004f, 0.155212f, 0.0f, 1.0f, 
  0.748014f, 0.620850f, 0.0f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.860606f, 0.860606f, 0.860599f, 1.0f, 
  120.241997f
};


static Material tropical10[] = {
  0.226102f, 0.0f, 0.077463f, 1.0f, 
  0.904409f, 0.0f, 0.309851f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.095591f, 0.095591f, 0.095591f, 1.0f, 
  10.0f
};


static Material tropical11[] = {
  0.187004f, 0.001565f, 0.062983f, 1.0f, 
  0.748016f, 0.006259f, 0.251931f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.684848f, 0.684848f, 0.684848f, 1.0f, 
  119.467003f
};


static Material tropical12[] = {
  0.226102f, 0.011737f, 0.124027f, 1.0f, 
  0.904409f, 0.046947f, 0.496108f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.095591f, 0.095591f, 0.095591f, 1.0f, 
  10.0f
};


static Material tropical13[] = {
  0.187004f, 0.0f, 0.137588f, 1.0f, 
  0.748016f, 0.0f, 0.550351f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.672727f, 0.672727f, 0.672727f, 1.0f, 
  29.478800f
};


static Material tropical14[] = {
  0.223992f, 0.0f, 0.172818f, 1.0f, 
  0.895967f, 0.0f, 0.691271f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.095591f, 0.086256f, 0.093458f, 1.0f, 
  10.0f
};


static Material tropical15[] = {
  0.156092f, 0.0f, 0.187004f, 1.0f, 
  0.624368f, 0.0f, 0.748016f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.951515f, 0.951515f, 0.951515f, 1.0f, 
  71.369698f
};


static Material tropical16[] = {
  0.155445f, 0.005229f, 0.220045f, 1.0f, 
  0.621780f, 0.020917f, 0.880181f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.087726f, 0.069438f, 0.095591f, 1.0f, 
  10.0f
};


static Material tropical17[] = {
  0.093502f, 0.0f, 0.187004f, 1.0f, 
  0.374008f, 0.0f, 0.748016f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.909091f, 0.909091f, 0.909091f, 1.0f, 
  51.975800f
};


static Material tropical18[] = {
  0.069875f, 0.001285f, 0.211477f, 1.0f, 
  0.279501f, 0.005142f, 0.845907f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.052278f, 0.031298f, 0.095591f, 1.0f, 
  10.0f
};


static Material tropical19[] = {
  0.000579f, 0.0f, 0.187004f, 1.0f, 
  0.002317f, 0.0f, 0.748016f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.884848f, 0.884848f, 0.884848f, 1.0f, 
  106.278999f
};


static Material tropical2[] = {
  0.226102f, 0.193685f, 0.020767f, 1.0f, 
  0.904409f, 0.774741f, 0.083067f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.095591f, 0.095591f, 0.095591f, 1.0f, 
  10.0f
};


static Material tropical20[] = {
  0.0f, 0.051239f, 0.211311f, 1.0f, 
  0.0f, 0.204955f, 0.845242f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.030170f, 0.046033f, 0.095591f, 1.0f, 
  10.0f
};


static Material tropical21[] = {
  0.005183f, 0.084911f, 0.187004f, 1.0f, 
  0.020732f, 0.339645f, 0.748016f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.903030f, 0.903030f, 0.903030f, 1.0f, 
  118.691002f
};


static Material tropical22[] = {
  0.0f, 0.149246f, 0.204489f, 1.0f, 
  0.0f, 0.596985f, 0.817956f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.0f, 0.069767f, 0.095591f, 1.0f, 
  10.0f
};


static Material tropical23[] = {
  0.0f, 0.157811f, 0.187004f, 1.0f, 
  0.0f, 0.631244f, 0.748016f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.915152f, 0.915152f, 0.915152f, 1.0f, 
  82.230301f
};


static Material tropical24[] = {
  0.0f, 0.204489f, 0.138459f, 1.0f, 
  0.0f, 0.817956f, 0.553836f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.0f, 0.095591f, 0.064724f, 1.0f, 
  10.0f
};


static Material tropical25[] = {
  0.0f, 0.187004f, 0.117351f, 1.0f, 
  0.0f, 0.748016f, 0.469403f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  1.0f, 1.0f, 1.0f, 1.0f, 
  104.726997f
};


static Material tropical26[] = {
  0.013288f, 0.204489f, 0.022004f, 1.0f, 
  0.053153f, 0.817956f, 0.088018f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.006212f, 0.095591f, 0.010286f, 1.0f, 
  10.0f
};


static Material tropical27[] = {
  0.0f, 0.187004f, 0.044004f, 1.0f, 
  0.0f, 0.748016f, 0.176015f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.981818f, 0.981818f, 0.981818f, 1.0f, 
  92.315102f
};


static Material tropical28[] = {
  0.088844f, 0.204489f, 0.003949f, 1.0f, 
  0.355377f, 0.817956f, 0.015797f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.041531f, 0.095591f, 0.001846f, 1.0f, 
  10.0f
};


static Material tropical29[] = {
  0.095486f, 0.187004f, 0.0f, 1.0f, 
  0.381944f, 0.748016f, 0.0f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.963636f, 0.963636f, 0.963636f, 1.0f, 
  125.672997f
};


static Material tropical3[] = {
  0.187004f, 0.138930f, 0.0f, 1.0f, 
  0.748016f, 0.555721f, 0.0f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.836364f, 0.836364f, 0.836364f, 1.0f, 
  77.575798f
};


static Material tropical30[] = {
  0.247933f, 0.234873f, 0.250000f, 1.0f, 
  0.991732f, 0.939493f, 1.0f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.0f
};


static Material tropical31[] = {
  0.106266f, 0.101217f, 0.106572f, 1.0f, 
  0.425062f, 0.404868f, 0.426289f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.860606f, 0.860606f, 0.860606f, 1.0f, 
  115.587997f
};


static Material tropical32[] = {
  0.106059f, 0.106059f, 0.106059f, 1.0f, 
  0.424238f, 0.424238f, 0.424238f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.168000f, 0.168000f, 0.168000f, 1.0f, 
  19.673100f
};


static Material tropical33[] = {
  0.038095f, 0.036285f, 0.038205f, 1.0f, 
  0.152381f, 0.145141f, 0.152820f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.745455f, 0.745455f, 0.745455f, 1.0f, 
  122.570000f
};


static Material tropical34[] = {
  0.034667f, 0.034667f, 0.034667f, 1.0f, 
  0.138667f, 0.138667f, 0.138667f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.168000f, 0.168000f, 0.168000f, 1.0f, 
  19.673100f
};


static Material tropical4[] = {
  0.226102f, 0.103065f, 0.0f, 1.0f, 
  0.904409f, 0.412258f, 0.0f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.095591f, 0.095591f, 0.095591f, 1.0f, 
  10.0f
};


static Material tropical5[] = {
  0.187004f, 0.074884f, 0.0f, 1.0f, 
  0.748016f, 0.299537f, 0.0f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.836364f, 0.836364f, 0.836364f, 1.0f, 
  117.915001f
};


static Material tropical6[] = {
  0.226102f, 0.070938f, 0.0f, 1.0f, 
  0.904409f, 0.283754f, 0.0f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.095591f, 0.095591f, 0.095591f, 1.0f, 
  10.0f
};


static Material tropical7[] = {
  0.187004f, 0.034892f, 0.0f, 1.0f, 
  0.748016f, 0.139569f, 0.0f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.709091f, 0.709091f, 0.709091f, 1.0f, 
  61.284901f
};


static Material tropical8[] = {
  0.226102f, 0.037578f, 0.0f, 1.0f, 
  0.904409f, 0.150314f, 0.0f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.095591f, 0.095591f, 0.095591f, 1.0f, 
  10.0f
};


static Material tropical9[] = {
  0.187004f, 0.0f, 0.010022f, 1.0f, 
  0.748016f, 0.0f, 0.040087f, 1.0f, 
  0.0f, 0.0f, 0.0f, 1.0f, 
  0.896970f, 0.896970f, 0.896970f, 1.0f, 
  128.0f
};

#endif
  
#ifdef __cplusplus
}
#endif

#endif // _MTLDATA_H
