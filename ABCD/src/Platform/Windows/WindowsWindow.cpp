#include "abpch.h"

#include "Platform/Windows/WindowsWindow.h"

#include "ABCD/Events/ApplicationEvent.h"
#include "ABCD/Events/MouseEvent.h"
#include "ABCD/Events/KeyEvent.h"

#include "ABCD/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace abcd
{
    static uint8_t sGLFWWindowCount = 0;

    static void GLFWErrorCallback(int error, const char* description)
    {
        AB_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    Scope<IWindow> IWindow::Create(const WindowProps& props)
    {
        return CreateScope<WindowsWindow>(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props)
    {
        AB_PROFILE_FUNCTION();

        Init(props);
    }

    WindowsWindow::~WindowsWindow()
    {
        AB_PROFILE_FUNCTION();

        Shutdown();
    }

    void WindowsWindow::Init(const WindowProps& props)
    {
        AB_PROFILE_FUNCTION();

        mData.Title = props.Title;
        mData.Width = props.Width;
        mData.Height = props.Height;

        AB_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

        if (sGLFWWindowCount == 0)
        {
            AB_PROFILE_SCOPE("glfwInit");
            int success = glfwInit();
            AB_CORE_ASSERT(success, "Could not intialize GLFW!");

            glfwSetErrorCallback(GLFWErrorCallback);
        }

        {
            AB_PROFILE_SCOPE("glfwCreateWindow");
#if defined(AB_DEBUG)
            if (Renderer::GetAPI() == IRendererAPI::API::OpenGL)
            {
                glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
            }
#endif
            mWindow = glfwCreateWindow((int)props.Width, (int)props.Height, mData.Title.c_str(), nullptr, nullptr);
            ++sGLFWWindowCount;
        }

        mContext = IGraphicsContext::Create(mWindow);
        mContext->Init();

        glfwSetWindowUserPointer(mWindow, &mData);
        SetVSync(true);

        glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                data.Width = width;
                data.Height = height;

                WindowResizeEvent event(width, height);
                data.EventCallback(event);
            });

        glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                WindowCloseEvent event;
                data.EventCallback(event);
            });

        glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

                switch (action)
                {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
                default:
                {
                    AB_CORE_ASSERT(false, "Unknown key action!");
                    break;
                }
                }
            });

        glfwSetCharCallback(mWindow, [](GLFWwindow* window, unsigned int keycode)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

                KeyTypedEvent event(keycode);
                data.EventCallback(event);
            });

        glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

                switch (action)
                {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                default:
                {
                    AB_CORE_ASSERT(false, "Unknown Button!");
                    break;
                }
                }
            });

        glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xOffset, double yOffset)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

                MouseScrolledEvent event((float)xOffset, (float)yOffset);
                data.EventCallback(event);
            });

        glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double xPos, double yPos)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

                MouseMovedEvent event((float)xPos, (float)yPos);
                data.EventCallback(event);
            }); 
    }

    void WindowsWindow::Shutdown()
    {
        AB_PROFILE_FUNCTION();

        glfwDestroyWindow(mWindow);

        --sGLFWWindowCount;
        if (sGLFWWindowCount == 0)
        {
            glfwTerminate();
        }
    }

    void WindowsWindow::OnUpdate()
    {
        AB_PROFILE_FUNCTION();

        glfwPollEvents();
        mContext->SwapBuffers();
    }

    void WindowsWindow::SetVSync(bool enabled)
    {
        AB_PROFILE_FUNCTION();

        if (enabled)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(0);
        }

        mData.VSync = enabled;
    }

    bool WindowsWindow::IsVSync() const
    {
        return mData.VSync;
    }

}