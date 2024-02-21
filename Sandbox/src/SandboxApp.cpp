#include "ABCD.h"

#include "imgui/imgui.h"

class ExampleLayer : public abcd::Layer
{
public:
    ExampleLayer()
        : Layer("Example"), mCamera(-1.6f, 1.6f, -0.9f, 0.9f), mCameraPosition(0.0f)
    {
        mVertexArray.reset(abcd::IVertexArray::Create());

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        std::shared_ptr<abcd::IVertexBuffer> vertexBuffer;
        vertexBuffer.reset(abcd::IVertexBuffer::Create(vertices, sizeof(vertices)));
        abcd::BufferLayout layout = {
            { abcd::ShaderDataType::Float3, "a_Position" },
            { abcd::ShaderDataType::Float4, "a_Color" }
        };
        vertexBuffer->SetLayout(layout);
        mVertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };
        std::shared_ptr<abcd::IIndexBuffer> indexBuffer;
        indexBuffer.reset(abcd::IIndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        mVertexArray->SetIndexBuffer(indexBuffer);

        mSquareVA.reset(abcd::IVertexArray::Create());
        float squareVertices[3 * 4] = {
            -0.75f, -0.75f, 0.0f,
             0.75f, -0.75f, 0.0f,
             0.75f,  0.75f, 0.0f,
            -0.75f,  0.75f, 0.0f
        };

        std::shared_ptr<abcd::IVertexBuffer> squareVB;
        squareVB.reset(abcd::IVertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout({
            { abcd::ShaderDataType::Float3, "a_Position" }
            });
        mSquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<abcd::IIndexBuffer> squareIB;
        squareIB.reset(abcd::IIndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        mSquareVA->SetIndexBuffer(squareIB);

        std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;

				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
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

        mShader.reset(new abcd::Shader(vertexSrc, fragmentSrc));

        std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
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

        mBlueShader.reset(new abcd::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
    }

    void OnUpdate(abcd::Timestep ts) override
    {
        if (abcd::Input::IsKeyPressed(AB_KEY_LEFT))
        {
            mCameraPosition.x -= mCameraMoveSpeed * ts;
        }
        else if (abcd::Input::IsKeyPressed(AB_KEY_RIGHT))
        {
            mCameraPosition.x += mCameraMoveSpeed * ts;
        }
        
        if (abcd::Input::IsKeyPressed(AB_KEY_UP))
        {
            mCameraPosition.y += mCameraMoveSpeed * ts;
        }
        else if (abcd::Input::IsKeyPressed(AB_KEY_DOWN))
        {
            mCameraPosition.y -= mCameraMoveSpeed * ts;
        }

        if (abcd::Input::IsKeyPressed(AB_KEY_A))
        {
            mCameraRotation += mCameraRotationSpeed * ts;
        }

        if (abcd::Input::IsKeyPressed(AB_KEY_D))
        {
            mCameraRotation -= mCameraRotationSpeed * ts;
        }

        abcd::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        abcd::RenderCommand::Clear();

        mCamera.SetPosition(mCameraPosition);
        mCamera.SetRotation(mCameraRotation);

        abcd::Renderer::BeginScene(mCamera);
        {
            abcd::Renderer::Submit(mBlueShader, mSquareVA);
            abcd::Renderer::Submit(mShader, mVertexArray);
        }

        abcd::Renderer::EndScene();
    }

    virtual void OnImGuiRender() override
    {
    }

    void OnEvent(abcd::Event& event) override
    {
    }

private:
    std::shared_ptr<abcd::Shader> mShader;
    std::shared_ptr<abcd::IVertexArray> mVertexArray;

    std::shared_ptr<abcd::Shader> mBlueShader;
    std::shared_ptr<abcd::IVertexArray> mSquareVA;

    abcd::OrthographicCamera mCamera;
    glm::vec3 mCameraPosition;
    float mCameraMoveSpeed = 5.0f;

    float mCameraRotation = 0.0f;
    float mCameraRotationSpeed = 180.0f;
};

class Sandbox : public abcd::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox()
    {
        
    }
};

abcd::Application* abcd::CreateApplication()
{
    return new Sandbox();
}