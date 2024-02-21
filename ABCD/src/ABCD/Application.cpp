#include "abpch.h"
#include "Application.h"

#include "ABCD/Log.h"

#include <glad/glad.h>

#include "Input.h"

namespace abcd
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::sInstance = nullptr;

    Application::Application()
    {
        AB_CORE_ASSERT(!sInstance, "Application already exists!");
        sInstance = this;

        mWindow = std::unique_ptr<IWindow>(IWindow::Create());
        mWindow->SetEventCallback(BIND_EVENT_FN(OnEvent));

        mImGuiLayer = new ImGuiLayer();
        PushOverlay(mImGuiLayer);

        mVertexArray.reset(IVertexArray::Create());

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        std::shared_ptr<IVertexBuffer> vertexBuffer;
        vertexBuffer.reset(IVertexBuffer::Create(vertices, sizeof(vertices)));
        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" }
        };
        vertexBuffer->SetLayout(layout);
        mVertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };
        std::shared_ptr<IIndexBuffer> indexBuffer;
        indexBuffer.reset(IIndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        mVertexArray->SetIndexBuffer(indexBuffer);

        mSquareVA.reset(IVertexArray::Create());
        float squareVertices[3 * 4] = {
            -0.75f, -0.75f, 0.0f,
             0.75f, -0.75f, 0.0f,
             0.75f,  0.75f, 0.0f,
            -0.75f,  0.75f, 0.0f
        };

        std::shared_ptr<IVertexBuffer> squareVB;
        squareVB.reset(IVertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout({
            { ShaderDataType::Float3, "a_Position" }
            });
        mSquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<IIndexBuffer> squareIB;
        squareIB.reset(IIndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        mSquareVA->SetIndexBuffer(squareIB);

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

        std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

        std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

        mBlueShader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
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

            mBlueShader->Bind();
            mSquareVA->Bind();
            glDrawElements(GL_TRIANGLES, mSquareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

            mShader->Bind();
            mVertexArray->Bind();
            glDrawElements(GL_TRIANGLES, mVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

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