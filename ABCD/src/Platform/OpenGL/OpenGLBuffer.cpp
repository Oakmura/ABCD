#include "abpch.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

#include <glad/glad.h>

namespace abcd
{
    /////////////////////////////////////////////////////////////////////////////
    // VertexBuffer /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
    {
        AB_PROFILE_FUNCTION();

        glCreateBuffers(1, &mRendererID);
        glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        AB_PROFILE_FUNCTION();

        glDeleteBuffers(1, &mRendererID);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        AB_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        AB_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    /////////////////////////////////////////////////////////////////////////////
    // IndexBuffer //////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
        : mCount(count)
    {
        AB_PROFILE_FUNCTION();

        glCreateBuffers(1, &mRendererID);
        glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        AB_PROFILE_FUNCTION();

        glDeleteBuffers(1, &mRendererID);
    }

    void OpenGLIndexBuffer::Bind() const
    {
        AB_PROFILE_FUNCTION();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
    }

    void OpenGLIndexBuffer::Unbind() const
    {
        AB_PROFILE_FUNCTION();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

}