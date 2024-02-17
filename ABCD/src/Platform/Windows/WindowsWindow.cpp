#include "abpch.h"

#include "WindowsWindow.h"

namespace abcd
{
    static bool s_GLFWInitialized = false;

    IWindow* IWindow::Create(const WindowProps& props)
    {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props)
    {
        Init(props);
    }

    WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    void WindowsWindow::Init(const WindowProps& props)
    {
        mData.Title = props.Title;
        mData.Width = props.Width;
        mData.Height = props.Height;

        AB_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

        if (!s_GLFWInitialized)
        {
            // TODO: glfwTerminate on system shutdown
            int success = glfwInit();
            AB_CORE_ASSERT(success, "Could not intialize GLFW!");

            s_GLFWInitialized = true;
        }

        mWindow = glfwCreateWindow((int)props.Width, (int)props.Height, mData.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(mWindow);
        glfwSetWindowUserPointer(mWindow, &mData);
        SetVSync(true);
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(mWindow);
    }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(mWindow);
    }

    void WindowsWindow::SetVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        mData.VSync = enabled;
    }

    bool WindowsWindow::IsVSync() const
    {
        return mData.VSync;
    }

}