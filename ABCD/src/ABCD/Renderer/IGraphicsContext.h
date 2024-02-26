#pragma once

namespace abcd 
{
    class IGraphicsContext
    {
    public:
        virtual ~IGraphicsContext() = default;

        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;

        static Scope<IGraphicsContext> Create(void* window);
    };
}