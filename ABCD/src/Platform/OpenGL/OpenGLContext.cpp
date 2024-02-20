#include "abpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace abcd
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : mWindowHandle(windowHandle)
    {
        AB_CORE_ASSERT(windowHandle, "Window handle is null!")
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(mWindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        AB_CORE_ASSERT(status, "Failed to initialize Glad!");
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(mWindowHandle);
    }
}