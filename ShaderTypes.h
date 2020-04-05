//
//  ShaderTypes.h
//  HelloWorld
//
//  Created by Adun Zhang on 4/4/20.
//  Copyright © 2020 AdunZhang. All rights reserved.
//

//
//  Header containing types and enum constants shared between Metal shaders and Swift/ObjC source
//
#ifndef ShaderTypes_h
#define ShaderTypes_h

enum
{
    BufferIndexMeshPositions = 0,
    BufferIndexMeshGenerics  = 1,
    BufferIndexUniforms      = 2
};

enum
{
    VertexAttributePosition  = 0,
    VertexAttributeTexcoord  = 1,
};

enum
{
    TextureIndexColor    = 0,
};

#include <simd/simd.h>

typedef struct
{
    matrix_float4x4 projectionMatrix;
    matrix_float4x4 modelViewMatrix;
} Uniforms;

#endif /* ShaderTypes_h */

