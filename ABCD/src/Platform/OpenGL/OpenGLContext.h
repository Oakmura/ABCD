#pragma once

#include "ABCD/Renderer/IGraphicsContext.h"

struct GLFWwindow;

namespace abcd 
{
    class OpenGLContext : public IGraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        virtual void Init() override;
        virtual void SwapBuffers() override;
    private:
        GLFWwindow* mWindowHandle;
    };
}