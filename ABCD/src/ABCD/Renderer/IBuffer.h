#pragma once

namespace abcd 
{
    class IVertexBuffer
    {
    public:
        virtual ~IVertexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        static IVertexBuffer* Create(float* vertices, uint32_t size);
    };

    class IIndexBuffer
    {
    public:
        virtual ~IIndexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetCount() const = 0;

        static IIndexBuffer* Create(uint32_t* indices, uint32_t size);
    };

}