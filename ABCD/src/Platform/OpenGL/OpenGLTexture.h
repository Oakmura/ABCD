#pragma once

#include "ABCD/Renderer/ITexture.h"

#include <glad/glad.h>

namespace abcd 
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(uint32_t width, uint32_t height);
        OpenGLTexture2D(const std::string& path);
        virtual ~OpenGLTexture2D();

        virtual uint32_t GetWidth() const override { return mWidth; }
        virtual uint32_t GetHeight() const override { return mHeight; }
        virtual uint32_t GetRendererID() const override { return mRendererID; }

        virtual void SetData(void* data, uint32_t size) override;

        virtual void Bind(uint32_t slot = 0) const override;

        virtual bool operator==(const ITexture& other) const override
        {
            return mRendererID == ((OpenGLTexture2D&)other).mRendererID;
        }
    private:
        std::string mPath;
        uint32_t mWidth, mHeight;
        uint32_t mRendererID;
        GLenum mInternalFormat, mDataFormat;
    };
}