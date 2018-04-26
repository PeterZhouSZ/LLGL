/*
 * TextureFlags.h
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015-2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef LLGL_TEXTURE_FLAGS_H
#define LLGL_TEXTURE_FLAGS_H


#include "Export.h"
#include <Gauss/Vector3.h>
#include <cstddef>
#include <cstdint>


namespace LLGL
{


/* ----- Enumerations ----- */

//! Texture type enumeration.
enum class TextureType
{
    Texture1D,          //!< 1-Dimensional texture.
    Texture2D,          //!< 2-Dimensional texture.
    Texture3D,          //!< 3-Dimensional texture.
    TextureCube,        //!< Cube texture.
    Texture1DArray,     //!< 1-Dimensional array texture.
    Texture2DArray,     //!< 2-Dimensional array texture.
    TextureCubeArray,   //!< Cube array texture.
    Texture2DMS,        //!< 2-Dimensional multi-sample texture.
    Texture2DMSArray,   //!< 2-Dimensional multi-sample array texture.
};

/**
\brief Hardware texture format enumeration.
\note All 32-bit integral formats are un-normalized!
*/
enum class TextureFormat
{
    Unknown,        //!< Unknown texture format.

    /* --- Color formats --- */
    R8,             //!< Color format: red 8-bit normalized unsigned integer component.
    R8Sgn,          //!< Color format: red 8-bit normalized signed integer component.

    R16,            //!< Color format: red 16-bit normalized unsigned interger component.
    R16Sgn,         //!< Color format: red 16-bit normalized signed interger component.
    R16Float,       //!< Color format: red 16-bit floating point component.

    R32UInt,        //!< Color format: red 32-bit un-normalized unsigned interger component.
    R32SInt,        //!< Color format: red 32-bit un-normalized signed interger component.
    R32Float,       //!< Color format: red 32-bit floating point component.

    RG8,            //!< Color format: red, green 8-bit normalized unsigned integer components.
    RG8Sgn,         //!< Color format: red, green 8-bit normalized signed integer components.

    RG16,           //!< Color format: red, green 16-bit normalized unsigned interger components.
    RG16Sgn,        //!< Color format: red, green 16-bit normalized signed interger components.
    RG16Float,      //!< Color format: red, green 16-bit floating point components.

    RG32UInt,       //!< Color format: red, green 32-bit un-normalized unsigned interger components.
    RG32SInt,       //!< Color format: red, green 32-bit un-normalized signed interger components.
    RG32Float,      //!< Color format: red, green 32-bit floating point components.

    RGB8,           //!< Color format: red, green, blue 8-bit normalized unsigned integer components. \note Only supported with: OpenGL, Vulkan.
    RGB8Sgn,        //!< Color format: red, green, blue 8-bit normalized signed integer components. \note Only supported with: OpenGL, Vulkan.

    RGB16,          //!< Color format: red, green, blue 16-bit normalized unsigned interger components. \note Only supported with: OpenGL, Vulkan.
    RGB16Sgn,       //!< Color format: red, green, blue 16-bit normalized signed interger components. \note Only supported with: OpenGL, Vulkan.
    RGB16Float,     //!< Color format: red, green, blue 16-bit floating point components. \note Only supported with: OpenGL, Vulkan.

    RGB32UInt,      //!< Color format: red, green, blue 32-bit un-normalized unsigned interger components.
    RGB32SInt,      //!< Color format: red, green, blue 32-bit un-normalized signed interger components.
    RGB32Float,     //!< Color format: red, green, blue 32-bit floating point components.

    RGBA8,          //!< Color format: red, green, blue, alpha 8-bit normalized unsigned integer components.
    RGBA8Sgn,       //!< Color format: red, green, blue, alpha 8-bit normalized signed integer components.

    RGBA16,         //!< Color format: red, green, blue, alpha 16-bit normalized unsigned interger components.
    RGBA16Sgn,      //!< Color format: red, green, blue, alpha 16-bit normalized signed interger components.
    RGBA16Float,    //!< Color format: red, green, blue, alpha 16-bit floating point components.

    RGBA32UInt,     //!< Color format: red, green, blue, alpha 32-bit un-normalized unsigned interger components.
    RGBA32SInt,     //!< Color format: red, green, blue, alpha 32-bit un-normalized signed interger components.
    RGBA32Float,    //!< Color format: red, green, blue, alpha 32-bit floating point components.

    /* --- Depth-stencil formats --- */
    D32,            //!< Depth-stencil format: depth 32-bit floating point component.
    D24S8,          //!< Depth-stencil format: depth 24-bit normalized unsigned integer, and 8-bit unsigned integer stencil components.

    /* --- Compressed color formats --- */
    RGB_DXT1,       //!< Compressed color format: RGB S3TC DXT1 with 8 bytes per 4x4 block. \note Only supported with: OpenGL.
    RGBA_DXT1,      //!< Compressed color format: RGBA S3TC DXT1 with 8 bytes per 4x4 block.
    RGBA_DXT3,      //!< Compressed color format: RGBA S3TC DXT3 with 16 bytes per 4x4 block.
    RGBA_DXT5,      //!< Compressed color format: RGBA S3TC DXT5 with 16 bytes per 4x4 block.
};

//! Axis direction (also used for texture cube face).
enum class AxisDirection
{
    XPos = 0,   //!< X+ direction.
    XNeg,       //!< X- direction.
    YPos,       //!< Y+ direction.
    YNeg,       //!< Y- direction.
    ZPos,       //!< Z+ direction.
    ZNeg,       //!< Z- direction.
};

//! Texture flags enumeration.
struct TextureFlags
{
    enum
    {
        #if 0
        /**
        \brief Texture mapping with CPU read access is required.
        \see RenderSystem::MapTexture
        */
        MapReadAccess       = (1 << 0),

        /**
        \brief Texture mapping with CPU write access is required.
        \see RenderSystem::MapTexture
        */
        MapWriteAccess      = (1 << 1),

        /*
        \brief Texture mapping with CPU read and write access is required.
        \see TextureFlags::MapReadAccess
        \see TextureFlags::MapWriteAccess
        */
        MapReadWriteAccess  = (MapReadAccess | MapWriteAccess),
        #endif

        /**
        \brief Texture will be used with MIP-mapping. This will create all MIP-map levels at texture creation time.
        \see RenderSystem::GenerateMips
        */
        GenerateMips        = (1 << 3),

        /**
        \brief Texture can be used as render target attachment.
        \see AttachmentDescriptor::texture
        */
        AttachmentUsage     = (1 << 4),

        /**
        \brief Default texture flags: (GenerateMips | AttachmentUsage).
        \see GenerateMips
        \see AttachmentUsage
        */
        Default             = (GenerateMips | AttachmentUsage),
    };
};


/* ----- Structures ----- */

/**
\brief Texture descriptor structure.
\remarks This is used to specifiy the dimensions of a texture which is to be created.
*/
struct LLGL_EXPORT TextureDescriptor
{
    //! 1D- and 1D-Array texture specific descriptor structure.
    struct Texture1DDescriptor
    {
        std::uint32_t   width;          //!< Texture width.
        std::uint32_t   layers;         //!< Number of texture array layers.
    };

    //! 2D- and 2D-Array texture specific descriptor structure.
    struct Texture2DDescriptor
    {
        std::uint32_t   width;          //!< Texture width.
        std::uint32_t   height;         //!< Texture height.
        std::uint32_t   layers;         //!< Number of texture array layers.
    };

    //! 3D texture specific descriptor structure.
    struct Texture3DDescriptor
    {
        std::uint32_t   width;          //!< Texture width.
        std::uint32_t   height;         //!< Texture height.
        std::uint32_t   depth;          //!< Texture depth.
    };

    //! Cube- and Cube-Array texture specific descriptor structure.
    struct TextureCubeDescriptor
    {
        std::uint32_t   width;          //!< Texture width.
        std::uint32_t   height;         //!< Texture height.
        std::uint32_t   layers;         //!< Number of texture array layers, one for each cube.
    };

    //! Multi-sampled 2D- and 2D-Array texture specific descriptor structure.
    struct Texture2DMSDescriptor
    {
        std::uint32_t   width;          //!< Texture width.
        std::uint32_t   height;         //!< Texture height.
        std::uint32_t   layers;         //!< Number of texture array layers.
        std::uint32_t   samples;        //!< Number of samples.
        bool            fixedSamples;   //!< Specifies whether the sample locations are fixed or not. By default true. \note Only supported with: OpenGL.
    };
    
    TextureDescriptor()
    {
        texture2DMS.width           = 0;
        texture2DMS.height          = 0;
        texture2DMS.layers          = 0;
        texture2DMS.samples         = 0;
        texture2DMS.fixedSamples    = true;
    }

    ~TextureDescriptor()
    {
        // Dummy
    }

    //! Hardware texture type. By default TextureType::Texture1D.
    TextureType                 type        = TextureType::Texture1D;

    //! Hardware texture format. By default TextureFormat::RGBA8.
    TextureFormat               format      = TextureFormat::RGBA8;

    /**
    \brief Specifies the texture creation flags (e.g. if MIP-mapping is required). By default TextureFlags::Default.
    \remarks This can be bitwise OR combination of the entries of the TextureFlags enumeration.
    \see TextureFlags
    */
    long                        flags       = TextureFlags::Default;

    union
    {
        Texture1DDescriptor     texture1D;      //!< Descriptor for 1D- and 1D-Array textures.
        Texture2DDescriptor     texture2D;      //!< Descriptor for 2D- and 2D-Array textures.
        Texture3DDescriptor     texture3D;      //!< Descriptor for 3D textures.
        TextureCubeDescriptor   textureCube;    //!< Descriptor for Cube- and Cube-Array textures.
        Texture2DMSDescriptor   texture2DMS;    //!< Descriptor for multi-sampled 2D- and 2D-Array textures.
    };
};

/**
\brief Sub-texture descriptor structure.
\remarks This is used to write (or partially write) the image data of a texture MIP-map level.
*/
struct LLGL_EXPORT SubTextureDescriptor
{
    struct Texture1DDescriptor
    {
        std::uint32_t x;              //!< Sub-texture X-axis offset.
        std::uint32_t layerOffset;    //!< Zero-based layer offset.
        std::uint32_t width;          //!< Sub-texture width.
        std::uint32_t layers;         //!< Number of texture array layers.
    };

    struct Texture2DDescriptor
    {
        std::uint32_t x;              //!< Sub-texture X-axis offset.
        std::uint32_t y;              //!< Sub-texture Y-axis offset.
        std::uint32_t layerOffset;    //!< Zero-based layer offset.
        std::uint32_t width;          //!< Sub-texture width.
        std::uint32_t height;         //!< Sub-texture height.
        std::uint32_t layers;         //!< Number of texture array layers.
    };

    struct Texture3DDescriptor
    {
        std::uint32_t x;              //!< Sub-texture X-axis offset.
        std::uint32_t y;              //!< Sub-texture Y-axis offset.
        std::uint32_t z;              //!< Sub-texture Z-axis offset.
        std::uint32_t width;          //!< Sub-texture width.
        std::uint32_t height;         //!< Sub-texture height.
        std::uint32_t depth;          //!< Number of texture array layers.
    };

    struct TextureCubeDescriptor
    {
        std::uint32_t x;              //!< Sub-texture X-axis offset.
        std::uint32_t y;              //!< Sub-texture Y-axis offset.
        std::uint32_t layerOffset;    //!< Zero-based layer offset.
        std::uint32_t width;          //!< Sub-texture width.
        std::uint32_t height;         //!< Sub-texture height.
        std::uint32_t cubeFaces;      //!< Number of cube-faces. To have all faces of N cube-texture layers, this value must be N*6.
        AxisDirection cubeFaceOffset; //!< First cube face in the current layer.
    };

    SubTextureDescriptor()
    {
        mipLevel                    = 0;
        textureCube.x               = 0;
        textureCube.y               = 0;
        textureCube.layerOffset     = 0;
        textureCube.width           = 0;
        textureCube.height          = 0;
        textureCube.cubeFaces       = 0;
        textureCube.cubeFaceOffset  = AxisDirection::XPos;
    }
    ~SubTextureDescriptor()
    {
    }

    std::uint32_t               mipLevel;       //!< MIP-map level for the sub-texture, where 0 is the base texture, and n > 0 is the n-th MIP-map level.

    union
    {
        Texture1DDescriptor     texture1D;      //!< Descriptor for 1D- and 1D-Array textures.
        Texture2DDescriptor     texture2D;      //!< Descriptor for 2D- and 2D-Array textures.
        Texture3DDescriptor     texture3D;      //!< Descriptor for 3D textures.
        TextureCubeDescriptor   textureCube;    //!< Descriptor for Cube- and Cube-Array textures.
    };
};


/* ----- Functions ----- */

/**
\brief Returns the number of MIP-map levels for a texture with the specified size.
\param[in] width Specifies the texture width.
\param[in] height Specifies the texture height or number of layers for 1D array textures. By default 1 (if 1D textures are used).
\param[in] depth Specifies the texture depth or number of layers for 2D array textures. By default 1 (if 1D or 2D textures are used).
\remarks The height and depth are optional parameters, so this function can be easily used for 1D, 2D, and 3D textures.
\return 1 + floor(log2(max{ x, y, z })).
*/
LLGL_EXPORT std::uint32_t NumMipLevels(std::uint32_t width, std::uint32_t height = 1, std::uint32_t depth = 1);

/**
\brief Returns the required buffer size (in bytes) of a texture with the specified hardware format and size.
\param[in] format Specifies the hardware format.
\param[in] numTexels Specifies the number of texture elements (texels).
For the DXT compressed texture formats, this must be a multiple of 16, since these formats compress the image in 4x4 texel blocks.
\return The required buffer size (in bytes), or zero if the input is invalid.
*/
LLGL_EXPORT std::uint32_t TextureBufferSize(const TextureFormat format, std::uint32_t numTexels);

/**
\brief Returns true if the specified texture format is a compressed format,
i.e. either TextureFormat::RGB_DXT1, TextureFormat::RGBA_DXT1, TextureFormat::RGBA_DXT3, or TextureFormat::RGBA_DXT5.
\see TextureFormat
*/
LLGL_EXPORT bool IsCompressedFormat(const TextureFormat format);

/**
\brief Returns true if the specified texture format is a depth or depth-stencil format,
i.e. either TextureFormat::DepthComponent, or TextureFormat::DepthStencil.
\see TextureFormat
*/
LLGL_EXPORT bool IsDepthStencilFormat(const TextureFormat format);

/**
\brief Returns true if the specified texture type is an array texture.
\return True if 'type' is . either TextureType::Texture1DArray, TextureType::Texture2DArray,
TextureType::TextureCubeArray, or TextureType::Texture2DMSArray.
*/
LLGL_EXPORT bool IsArrayTexture(const TextureType type);

/**
\brief Returns true if the specified texture type is a multi-sample texture.
\return True if 'type' is either TextureType::Texture2DMS, or TextureType::Texture2DMSArray.
*/
LLGL_EXPORT bool IsMultiSampleTexture(const TextureType type);

/**
\brief Returns true if the specified texture type is a cube texture.
\return True if 'type' is either TextureType::TextureCube or TextureType::TextureCubeArray.
*/
LLGL_EXPORT bool IsCubeTexture(const TextureType type);


} // /namespace LLGL


#endif



// ================================================================================
