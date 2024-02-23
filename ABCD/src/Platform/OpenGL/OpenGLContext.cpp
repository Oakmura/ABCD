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

        AB_CORE_INFO("OpenGL Info:");
        AB_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
        AB_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
        AB_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));

#ifdef AB_ENABLE_ASSERTS
        int versionMajor;
        int versionMinor;
        glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
        glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

        AB_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "ABCD requires at least OpenGL version 4.5!");
#endif
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(mWindowHandle);
    }
}