
#ifndef __BSP_UTIL_INCLUDED__
#define __BSP_UTIL_INCLUDED__

struct stTexCoord2
{
   float tu, tv;
};


struct stPoint3D
{
   float x, y, z;
};


enum enQ3LumpOffsets
{
   iEnitiesOffset = 0,
   iTextureOffset,
   iPlanesOffset,
   iNodesOffset,
   iLeafOffset,
   iLeafFacesOffset,
   iLeafBrushesOffset,
   iModelsOffset,
   iBrushesOffset,
   iBrushesSidesOffset,
   iVerticesOffset,
   iMeshVerticesOffset,
   iShaderFilesOffset,
   iFacesOffset,
   iLightMapsOffset,
   iLightVolumeOffset,
   iVisibleDataOffset,
   iMaxLumpsOffset
};


struct stQ3Header
{
   char bspID[4];
   int version;
};


struct stQ3FileLump
{
   int offset;
   int length;
};


struct stQ3Texture
{
   char file[64];
   int flags;
   int contents;
};


struct stQ3Face
{
   int texID;
   int effect;
   int type;
   int startVertexIndex;
   int totalVertices;
   int meshVertexIndex;
   int totalMeshVertices;
   int lightmapID;
   int lightMapCorner[2];
   int lightMapSize[2];
   stPoint3D lightMapPos;
   stPoint3D lightMapVectors[2];
   stPoint3D normal;
   int size[2];
};


struct stQ3Vertex
{
   stPoint3D vertex;
   stTexCoord2 texCoord;
   stTexCoord2 lightmapCoord;
   stPoint3D normal;
   unsigned char color[4];
};


struct stQ3LightMap
{
   unsigned char lightMap[128][128][3];
};

#endif
