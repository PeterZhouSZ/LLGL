/*
 * GLTexImage.cpp
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include "GLTexImage.h"
#include "../GLTypes.h"
#include "../GLImport.h"
#include "../GLImportExt.h"
#include <array>


namespace LLGL
{


static std::vector<ColorRGBAub> GenImageDataRGBAub(int numPixels, const ColorRGBAub& color)
{
    return std::vector<ColorRGBAub>(static_cast<std::size_t>(numPixels), color);
}

static void GLTexImage1DBase(
    GLenum target, const TextureFormat internalFormat, unsigned int width,
    GLenum format, GLenum type, const void* data, unsigned int compressedSize)
{
    if (IsCompressedFormat(internalFormat))
    {
        glCompressedTexImage1D(
            target, 0, GLTypes::Map(internalFormat),
            static_cast<GLsizei>(width),
            0, static_cast<GLsizei>(compressedSize), data
        );
    }
    else
    {
        glTexImage1D(
            target, 0, GLTypes::Map(internalFormat),
            static_cast<GLsizei>(width),
            0, format, type, data
        );
    }
}

static void GLTexImage2DBase(
    GLenum target, const TextureFormat internalFormat, unsigned int width, unsigned int height,
    GLenum format, GLenum type, const void* data, unsigned int compressedSize)
{
    if (IsCompressedFormat(internalFormat))
    {
        glCompressedTexImage2D(
            target, 0, GLTypes::Map(internalFormat),
            static_cast<GLsizei>(width),
            static_cast<GLsizei>(height),
            0, static_cast<GLsizei>(compressedSize), data
        );
    }
    else
    {
        glTexImage2D(
            target, 0, GLTypes::Map(internalFormat),
            static_cast<GLsizei>(width),
            static_cast<GLsizei>(height),
            0, format, type, data
        );
    }
}

static void GLTexImage3DBase(
    GLenum target, const TextureFormat internalFormat, unsigned int width, unsigned int height, unsigned int depth,
    GLenum format, GLenum type, const void* data, unsigned int compressedSize)
{
    if (IsCompressedFormat(internalFormat))
    {
        glCompressedTexImage3D(
            target, 0, GLTypes::Map(internalFormat),
            static_cast<GLsizei>(width),
            static_cast<GLsizei>(height),
            static_cast<GLsizei>(depth),
            0, static_cast<GLsizei>(compressedSize), data
        );
    }
    else
    {
        glTexImage3D(
            target, 0, GLTypes::Map(internalFormat),
            static_cast<GLsizei>(width),
            static_cast<GLsizei>(height),
            static_cast<GLsizei>(depth),
            0, format, type, data
        );
    }
}

static void GLTexImage2DMultisampleBase(
    GLenum target, unsigned int samples, const TextureFormat internalFormat, unsigned int width, unsigned int height, bool fixedSamples)
{
    glTexImage2DMultisample(
        target,
        static_cast<GLsizei>(samples),
        GLTypes::Map(internalFormat),
        static_cast<GLsizei>(width),
        static_cast<GLsizei>(height),
        (fixedSamples ? GL_TRUE : GL_FALSE)
    );
}

static void GLTexImage3DMultisampleBase(
    GLenum target, unsigned int samples, const TextureFormat internalFormat, unsigned int width, unsigned int height, unsigned int depth, bool fixedSamples)
{
    glTexImage3DMultisample(
        target,
        static_cast<GLsizei>(samples),
        GLTypes::Map(internalFormat),
        static_cast<GLsizei>(width),
        static_cast<GLsizei>(height),
        static_cast<GLsizei>(depth),
        (fixedSamples ? GL_TRUE : GL_FALSE)
    );
}

static void GLTexImage1D(
    const TextureFormat internalFormat, unsigned int width,
    GLenum format, GLenum type, const void* data, unsigned int compressedSize = 0)
{
    GLTexImage1DBase(GL_TEXTURE_1D, internalFormat, width, format, type, data, compressedSize);
}

static void GLTexImage2D(
    const TextureFormat internalFormat, unsigned int width, unsigned int height,
    GLenum format, GLenum type, const void* data, unsigned int compressedSize = 0)
{
    GLTexImage2DBase(GL_TEXTURE_2D, internalFormat, width, height, format, type, data, compressedSize);
}

static void GLTexImage3D(
    const TextureFormat internalFormat, unsigned int width, unsigned int height, unsigned int depth,
    GLenum format, GLenum type, const void* data, unsigned int compressedSize = 0)
{
    GLTexImage3DBase(GL_TEXTURE_3D, internalFormat, width, height, depth, format, type, data, compressedSize);
}

static void GLTexImageCube(
    const TextureFormat internalFormat, unsigned int width, unsigned int height, AxisDirection cubeFace,
    GLenum format, GLenum type, const void* data, unsigned int compressedSize = 0)
{
    GLTexImage2DBase(GLTypes::Map(cubeFace), internalFormat, width, height, format, type, data, compressedSize);
}

static void GLTexImage1DArray(
    const TextureFormat internalFormat, unsigned int width, unsigned int layers,
    GLenum format, GLenum type, const void* data, unsigned int compressedSize = 0)
{
    GLTexImage2DBase(GL_TEXTURE_1D_ARRAY, internalFormat, width, layers, format, type, data, compressedSize);
}

static void GLTexImage2DArray(
    const TextureFormat internalFormat, unsigned int width, unsigned int height, unsigned int layers,
    GLenum format, GLenum type, const void* data, unsigned int compressedSize = 0)
{
    GLTexImage3DBase(GL_TEXTURE_2D_ARRAY, internalFormat, width, height, layers, format, type, data, compressedSize);
}

static void GLTexImageCubeArray(
    const TextureFormat internalFormat, unsigned int width, unsigned int height, unsigned int layers,
    GLenum format, GLenum type, const void* data, unsigned int compressedSize = 0)
{
    GLTexImage3DBase(GL_TEXTURE_CUBE_MAP_ARRAY, internalFormat, width, height, layers*6, format, type, data, compressedSize);
}

static void GLTexImage2DMultisample(
    unsigned int samples, const TextureFormat internalFormat, unsigned int width, unsigned int height, bool fixedSamples)
{
    GLTexImage2DMultisampleBase(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, fixedSamples);
}

static void GLTexImage2DMultisampleArray(
    unsigned int samples, const TextureFormat internalFormat, unsigned int width, unsigned int height, unsigned int depth, bool fixedSamples)
{
    GLTexImage3DMultisampleBase(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, samples, internalFormat, width, height, depth, fixedSamples);
}

void GLBuildTexture1D(const TextureDescriptor& desc, const ImageDescriptor* imageDesc, const ColorRGBAub& defaultImageColor)
{
    if (imageDesc)
    {
        /* Setup texture image from descriptor */
        GLTexImage1D(
            desc.format,
            desc.texture1D.width,
            GLTypes::Map(imageDesc->format), GLTypes::Map(imageDesc->dataType), imageDesc->buffer, imageDesc->compressedSize
        );
    }
    else if (IsCompressedFormat(desc.format))
    {
        /* Initialize compressed texture image with null pointer */
        GLTexImage1D(
            desc.format,
            desc.texture1D.width,
            GL_RGBA, GL_UNSIGNED_BYTE, nullptr
        );
    }
    else
    {
        /* Initialize texture image with default color */
        auto image = GenImageDataRGBAub(
            desc.texture1D.width,
            defaultImageColor
        );

        GLTexImage1D(
            desc.format,
            desc.texture1D.width,
            GL_RGBA, GL_UNSIGNED_BYTE, image.data()
        );
    }
}

void GLBuildTexture2D(const TextureDescriptor& desc, const ImageDescriptor* imageDesc, const ColorRGBAub& defaultImageColor)
{
    if (imageDesc)
    {
        /* Setup texture image from descriptor */
        GLTexImage2D(
            desc.format,
            desc.texture2D.width, desc.texture2D.height,
            GLTypes::Map(imageDesc->format), GLTypes::Map(imageDesc->dataType), imageDesc->buffer, imageDesc->compressedSize
        );
    }
    else if (IsCompressedFormat(desc.format))
    {
        /* Initialize compressed texture image with null pointer */
        GLTexImage2D(
            desc.format,
            desc.texture2D.width, desc.texture2D.height,
            GL_RGBA, GL_UNSIGNED_BYTE, nullptr
        );
    }
    else
    {
        /* Initialize texture image with default color */
        auto image = GenImageDataRGBAub(
            desc.texture2D.width * desc.texture2D.height,
            defaultImageColor
        );

        GLTexImage2D(
            desc.format,
            desc.texture2D.width, desc.texture2D.height,
            GL_RGBA, GL_UNSIGNED_BYTE, image.data()
        );
    }
}

void GLBuildTexture3D(const TextureDescriptor& desc, const ImageDescriptor* imageDesc, const ColorRGBAub& defaultImageColor)
{
    if (imageDesc)
    {
        /* Setup texture image from descriptor */
        GLTexImage3D(
            desc.format,
            desc.texture3D.width, desc.texture3D.height, desc.texture3D.depth,
            GLTypes::Map(imageDesc->format), GLTypes::Map(imageDesc->dataType), imageDesc->buffer, imageDesc->compressedSize
        );
    }
    else if (IsCompressedFormat(desc.format))
    {
        /* Initialize compressed texture image with null pointer */
        GLTexImage3D(
            desc.format,
            desc.texture3D.width, desc.texture3D.height, desc.texture3D.depth,
            GL_RGBA, GL_UNSIGNED_BYTE, nullptr
        );
    }
    else
    {
        /* Initialize texture image with default color */
        auto image = GenImageDataRGBAub(
            desc.texture3D.width * desc.texture3D.height * desc.texture3D.depth,
            defaultImageColor
        );

        GLTexImage3D(
            desc.format,
            desc.texture3D.width, desc.texture3D.height, desc.texture3D.depth,
            GL_RGBA, GL_UNSIGNED_BYTE, image.data()
        );
    }
}

void GLBuildTextureCube(const TextureDescriptor& desc, const ImageDescriptor* imageDesc, const ColorRGBAub& defaultImageColor)
{
    const std::array<AxisDirection, 6> cubeFaces
    {{
        AxisDirection::XPos,
        AxisDirection::XNeg,
        AxisDirection::YPos,
        AxisDirection::YNeg,
        AxisDirection::ZPos,
        AxisDirection::ZNeg
    }};

    if (imageDesc)
    {
        /* Setup texture image cube-faces from descriptor */
        auto imageFace          = reinterpret_cast<const char*>(imageDesc->buffer);
        auto imageFaceStride    = (desc.textureCube.width * desc.textureCube.height * ImageFormatSize(imageDesc->format) * DataTypeSize(imageDesc->dataType));

        if (IsCompressedFormat(desc.format))
            imageFaceStride = imageDesc->compressedSize;

        auto dataFormatGL       = GLTypes::Map(imageDesc->format);
        auto dataTypeGL         = GLTypes::Map(imageDesc->dataType);

        for (auto face : cubeFaces)
        {
            GLTexImageCube(
                desc.format,
                desc.textureCube.width, desc.textureCube.height, face,
                dataFormatGL, dataTypeGL, imageFace, imageDesc->compressedSize
            );
            imageFace += imageFaceStride;
        }
    }
    else if (IsCompressedFormat(desc.format))
    {
        /* Initialize compressed texture image with null pointer */
        for (auto face : cubeFaces)
        {
            GLTexImageCube(
                desc.format,
                desc.textureCube.width, desc.textureCube.height, face,
                GL_RGBA, GL_UNSIGNED_BYTE, nullptr
            );
        }
    }
    else
    {
        /* Initialize texture image cube-faces with default color */
        auto image = GenImageDataRGBAub(
            desc.textureCube.width * desc.textureCube.height,
            defaultImageColor
        );

        for (auto face : cubeFaces)
        {
            GLTexImageCube(
                desc.format,
                desc.textureCube.width, desc.textureCube.height, face,
                GL_RGBA, GL_UNSIGNED_BYTE, image.data()
            );
        }
    }
}

void GLBuildTexture1DArray(const TextureDescriptor& desc, const ImageDescriptor* imageDesc, const ColorRGBAub& defaultImageColor)
{
    if (imageDesc)
    {
        /* Setup texture image from descriptor */
        GLTexImage1DArray(
            desc.format,
            desc.texture1D.width, desc.texture1D.layers,
            GLTypes::Map(imageDesc->format), GLTypes::Map(imageDesc->dataType), imageDesc->buffer, imageDesc->compressedSize
        );
    }
    else if (IsCompressedFormat(desc.format))
    {
        /* Initialize compressed texture image with null pointer */
        GLTexImage1DArray(
            desc.format,
            desc.texture1D.width, desc.texture1D.layers,
            GL_RGBA, GL_UNSIGNED_BYTE, nullptr
        );
    }
    else
    {
        /* Initialize texture image with default color */
        auto image = GenImageDataRGBAub(
            desc.texture1D.width * static_cast<int>(desc.texture1D.layers),
            defaultImageColor
        );

        GLTexImage1DArray(
            desc.format,
            desc.texture1D.width, desc.texture1D.layers,
            GL_RGBA, GL_UNSIGNED_BYTE, image.data()
        );
    }
}

void GLBuildTexture2DArray(const TextureDescriptor& desc, const ImageDescriptor* imageDesc, const ColorRGBAub& defaultImageColor)
{
    if (imageDesc)
    {
        /* Setup texture image from descriptor */
        GLTexImage2DArray(
            desc.format,
            desc.texture2D.width, desc.texture2D.height, desc.texture2D.layers,
            GLTypes::Map(imageDesc->format), GLTypes::Map(imageDesc->dataType), imageDesc->buffer, imageDesc->compressedSize
        );
    }
    else if (IsCompressedFormat(desc.format))
    {
        /* Initialize compressed texture image with null pointer */
        GLTexImage2DArray(
            desc.format,
            desc.texture2D.width, desc.texture2D.height, desc.texture2D.layers,
            GL_RGBA, GL_UNSIGNED_BYTE, nullptr
        );
    }
    else
    {
        /* Initialize texture image with default color */
        auto image = GenImageDataRGBAub(
            desc.texture2D.width * desc.texture2D.height * static_cast<int>(desc.texture2D.layers),
            defaultImageColor
        );

        GLTexImage2DArray(
            desc.format,
            desc.texture2D.width, desc.texture2D.height, desc.texture2D.layers,
            GL_RGBA, GL_UNSIGNED_BYTE, image.data()
        );
    }
}

void GLBuildTextureCubeArray(const TextureDescriptor& desc, const ImageDescriptor* imageDesc, const ColorRGBAub& defaultImageColor)
{
    if (imageDesc)
    {
        /* Setup texture image cube-faces from descriptor */
        GLTexImageCubeArray(
            desc.format,
            desc.textureCube.width, desc.textureCube.height, desc.textureCube.layers,
            GLTypes::Map(imageDesc->format), GLTypes::Map(imageDesc->dataType), imageDesc->buffer, imageDesc->compressedSize
        );
    }
    else if (IsCompressedFormat(desc.format))
    {
        /* Initialize compressed texture image with null pointer */
        GLTexImageCubeArray(
            desc.format,
            desc.textureCube.width, desc.textureCube.height, desc.textureCube.layers,
            GL_RGBA, GL_UNSIGNED_BYTE, nullptr
        );
    }
    else
    {
        /* Initialize texture image cube-faces with default color */
        auto image = GenImageDataRGBAub(
            desc.textureCube.width * desc.textureCube.height * static_cast<int>(desc.textureCube.layers*6),
            defaultImageColor
        );

        GLTexImageCubeArray(
            desc.format,
            desc.textureCube.width, desc.textureCube.height, desc.textureCube.layers,
            GL_RGBA, GL_UNSIGNED_BYTE, image.data()
        );
    }
}

void GLBuildTexture2DMS(const TextureDescriptor& desc)
{
    /* Setup multi-sampled texture storage from descriptor */
    GLTexImage2DMultisample(
        desc.texture2DMS.samples, desc.format,
        desc.texture2DMS.width, desc.texture2DMS.height,
        desc.texture2DMS.fixedSamples
    );
}

void GLBuildTexture2DMSArray(const TextureDescriptor& desc)
{
    /* Setup multi-sampled array texture storage from descriptor */
    GLTexImage2DMultisampleArray(
        desc.texture2DMS.samples, desc.format,
        desc.texture2DMS.width, desc.texture2DMS.height, desc.texture2DMS.layers,
        desc.texture2DMS.fixedSamples
    );
}


} // /namespace LLGL



// ================================================================================