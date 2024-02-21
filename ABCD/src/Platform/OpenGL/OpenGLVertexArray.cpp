#include "abpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace abcd 
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
        case abcd::ShaderDataType::Float:    return GL_FLOAT;
        case abcd::ShaderDataType::Float2:   return GL_FLOAT;
        case abcd::ShaderDataType::Float3:   return GL_FLOAT;
        case abcd::ShaderDataType::Float4:   return GL_FLOAT;
        case abcd::ShaderDataType::Mat3:     return GL_FLOAT;
        case abcd::ShaderDataType::Mat4:     return GL_FLOAT;
        case abcd::ShaderDataType::Int:      return GL_INT;
        case abcd::ShaderDataType::Int2:     return GL_INT;
        case abcd::ShaderDataType::Int3:     return GL_INT;
        case abcd::ShaderDataType::Int4:     return GL_INT;
        case abcd::ShaderDataType::Bool:     return GL_BOOL;
        }

        AB_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &mRendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &mRendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(mRendererID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<IVertexBuffer>& vertexBuffer)
    {
        AB_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

        glBindVertexArray(mRendererID);
        vertexBuffer->Bind();

        uint32_t index = 0;
        const auto& layout = vertexBuffer->GetLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                element.GetComponentCount(),
                ShaderDataTypeToOpenGLBaseType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (const void*)element.Offset);
            index++;
        }

        mVertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IIndexBuffer>& indexBuffer)
    {
        glBindVertexArray(mRendererID);
        indexBuffer->Bind();

        mIndexBuffer = indexBuffer;
    }
}