/*
 * TextureFlags.h
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef __LLGL_TEXTURE_FLAGS_H__
#define __LLGL_TEXTURE_FLAGS_H__


#include "RenderSystemFlags.h"


namespace LLGL
{


//! Texture type enumeration.
enum class TextureType
{
    Undefined,          //!< Initial value of a Texture object.
    Texture1D,          //!< 1-Dimensional texture.
    Texture2D,          //!< 2-Dimensional texture.
    Texture3D,          //!< 3-Dimensional texture.
    TextureCube,        //!< Cube texture.
    Texture1DArray,     //!< 1-Dimensional array texture.
    Texture2DArray,     //!< 2-Dimensional array texture.
    TextureCubeArray,   //!< Cube array texture.
};

//! Hardware texture format enumeration.
enum class TextureFormat
{
    /* --- Base formats --- */
    DepthComponent, //!< Base internal format: depth component.
    DepthStencil,   //!< Base internal format: depth- and stencil components.
    R,              //!< Base internal format: red component.
    RG,             //!< Base internal format: red and green components.
    RGB,            //!< Base internal format: red, green and blue components.
    RGBA,           //!< Base internal format: red, green, blue and alpha components.

    /* --- Sized formats --- */
    R8UInt,         //!< Sized internal format: red 8-bit unsigned integer component.
    R8SInt,         //!< Sized internal format: red 8-bit signed integer component.

    R16UInt,        //!< Sized internal format: red 16-bit unsigned interger component.
    R16SInt,        //!< Sized internal format: red 16-bit signed interger component.
    R16Float,       //!< Sized internal format: red 16-bit floating point component.

    R32UInt,        //!< Sized internal format: red 32-bit unsigned interger component.
    R32SInt,        //!< Sized internal format: red 32-bit signed interger component.
    R32Float,       //!< Sized internal format: red 32-bit floating point component.

    RG8UInt,        //!< Sized internal format: red, green 8-bit unsigned integer components.
    RG8SInt,        //!< Sized internal format: red, green 8-bit signed integer components.

    RG16UInt,       //!< Sized internal format: red, green 16-bit unsigned interger components.
    RG16SInt,       //!< Sized internal format: red, green 16-bit signed interger components.
    RG16Float,      //!< Sized internal format: red, green 16-bit floating point components.

    RG32UInt,       //!< Sized internal format: red, green 32-bit unsigned interger components.
    RG32SInt,       //!< Sized internal format: red, green 32-bit signed interger components.
    RG32Float,      //!< Sized internal format: red, green 32-bit floating point components.

    RGB8UInt,       //!< Sized internal format: red, green, blue 8-bit unsigned integer components.
    RGB8SInt,       //!< Sized internal format: red, green, blue 8-bit signed integer components.

    RGB16UInt,      //!< Sized internal format: red, green, blue 16-bit unsigned interger components.
    RGB16SInt,      //!< Sized internal format: red, green, blue 16-bit signed interger components.
    RGB16Float,     //!< Sized internal format: red, green, blue 16-bit floating point components.

    RGB32UInt,      //!< Sized internal format: red, green, blue 32-bit unsigned interger components.
    RGB32SInt,      //!< Sized internal format: red, green, blue 32-bit signed interger components.
    RGB32Float,     //!< Sized internal format: red, green, blue 32-bit floating point components.

    RGBA8UInt,      //!< Sized internal format: red, green, blue, alpha 8-bit unsigned integer components.
    RGBA8SInt,      //!< Sized internal format: red, green, blue, alpha 8-bit signed integer components.

    RGBA16UInt,     //!< Sized internal format: red, green, blue, alpha 16-bit unsigned interger components.
    RGBA16SInt,     //!< Sized internal format: red, green, blue, alpha 16-bit signed interger components.
    RGBA16Float,    //!< Sized internal format: red, green, blue, alpha 16-bit floating point components.

    RGBA32UInt,     //!< Sized internal format: red, green, blue, alpha 32-bit unsigned interger components.
    RGBA32SInt,     //!< Sized internal format: red, green, blue, alpha 32-bit signed interger components.
    RGBA32Float,    //!< Sized internal format: red, green, blue, alpha 32-bit floating point components.
};

//! Color format used to write texture data.
enum class ColorFormat
{
    Gray,           //!< Single color component: Gray or rather brightness.
    GrayAlpha,      //!< Two color components: Gray, Alpha.
    RGB,            //!< Three color components: Red, Green, Blue.
    BGR,            //!< Three color components: Blue, Green, Red.
    RGBA,           //!< Four color components: Red, Green, Blue, Alpha.
    BGRA,           //!< Four color components: Blue, Green, Red, Alpha.
    Depth,          //!< Single color component used as depth component.
    DepthStencil,   //!< Pair of depth and stencil component.
};


//! Texture data descriptor structure.
struct LLGL_EXPORT TextureDataDescriptor
{
    TextureDataDescriptor(const void* data, ColorFormat dataFormat, DataType dataType) :
        data        ( data       ),
        dataFormat  ( dataFormat ),
        dataType    ( dataType   )
    {
    }

    const void* data;
    ColorFormat dataFormat;
    DataType    dataType;
};


} // /namespace LLGL


#endif



// ================================================================================