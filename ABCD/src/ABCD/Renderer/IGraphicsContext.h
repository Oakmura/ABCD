#pragma once

namespace abcd 
{
    class IGraphicsContext
    {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };
}