/* ------------------------------------------------------------
 * AlternativeFull
 * ------------------------------------------------------------ */
/* created by AlternativeFullFrontend. */
#define TEXTURE_THRESHOLD "shading_hint_katturi4_zoids_toon.png"
#define TEXTURE_SHADOW "miku_1_kage.png"
#define USE_HIGHLIGHT_TEXTURE
#define TEXTURE_HIGHLIGHT "miku_1.png"
#define USE_SELFSHADOW_MODE
#define USE_NONE_SELFSHADOW_MODE
float SelfShadowPower = 1;
#define USE_MATERIAL_SPECULAR
#define USE_SPECULAR_CHEET
float SpecularBoost = 0;
#define USE_MATERIAL_SPHERE
float3 DefaultModeShadowColor = {1,1,1};
#define MAX_ANISOTROPY 16

#include "AlternativeFull.fxsub"
