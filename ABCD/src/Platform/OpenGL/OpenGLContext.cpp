#include "abpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace abcd
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : mWindowHandle(windowHandle)
    {
        AB_CORE_ASSERT(windowHandle, "Window handle is null!")
    }

    void OpenGLContext::Init()
    {
        AB_PROFILE_FUNCTION();

        glfwMakeContextCurrent(mWindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        AB_CORE_ASSERT(status, "Failed to initialize Glad!");

        AB_CORE_INFO("OpenGL Info:");
        AB_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
        AB_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
        AB_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));

        AB_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "ABCD requires at least OpenGL version 4.5!");
    }

    void OpenGLContext::SwapBuffers()
    {
        AB_PROFILE_FUNCTION();

        glfwSwapBuffers(mWindowHandle);
    }
}