#include "abpch.h"
#include "Application.h"

#include "ABCD/Log.h"

#include <glad/glad.h>

#include "Input.h"

namespace abcd
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::sInstance = nullptr;

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

    Application::Application()
    {
        AB_CORE_ASSERT(!sInstance, "Application already exists!");
        sInstance = this;

        mWindow = std::unique_ptr<IWindow>(IWindow::Create());
        mWindow->SetEventCallback(BIND_EVENT_FN(OnEvent));

        mImGuiLayer = new ImGuiLayer();
        PushOverlay(mImGuiLayer);

        glGenVertexArrays(1, &mVertexArray);
        glBindVertexArray(mVertexArray);

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        mVertexBuffer.reset(IVertexBuffer::Create(vertices, sizeof(vertices)));

        {
            BufferLayout layout = 
            {
                { ShaderDataType::Float3, "a_Position" },
                { ShaderDataType::Float4, "a_Color" }
            };

            mVertexBuffer->SetLayout(layout);
        }

        uint32_t index = 0;
        const auto& layout = mVertexBuffer->GetLayout();
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

        uint32_t indices[3] = { 0, 1, 2 };
        mIndexBuffer.reset(IIndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

        std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

        std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

        mShader.reset(new Shader(vertexSrc, fragmentSrc));
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

        for (auto it = mLayerStack.end(); it != mLayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if (e.mbHandled)
            {
                break;
            }
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        mLayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* layer)
    {
        mLayerStack.PushOverlay(layer);
    }

    bool Application::onWindowClose(WindowCloseEvent& e)
    {
        mbRunning = false;

        return true;
    }

    void Application::Run()
    {
        while (mbRunning)
        {
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            mShader->Bind();
            glBindVertexArray(mVertexArray);
            glDrawElements(GL_TRIANGLES, mIndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

            for (Layer* layer : mLayerStack)
            {
                layer->OnUpdate();
            }

            mImGuiLayer->Begin();
            for (Layer* layer : mLayerStack)
            {
                layer->OnImGuiRender();
            }
            mImGuiLayer->End();

            mWindow->OnUpdate();
        }
    }
}