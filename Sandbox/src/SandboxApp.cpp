#include "ABCD.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

        abcd::Ref<abcd::IVertexBuffer> vertexBuffer;
        vertexBuffer.reset(abcd::IVertexBuffer::Create(vertices, sizeof(vertices)));
        abcd::BufferLayout layout = {
            { abcd::ShaderDataType::Float3, "a_Position" },
            { abcd::ShaderDataType::Float4, "a_Color" }
        };
        vertexBuffer->SetLayout(layout);
        mVertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };
        abcd::Ref<abcd::IIndexBuffer> indexBuffer;
        indexBuffer.reset(abcd::IIndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        mVertexArray->SetIndexBuffer(indexBuffer);

        mSquareVA.reset(abcd::IVertexArray::Create());
        float squareVertices[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        abcd::Ref<abcd::IVertexBuffer> squareVB;
        squareVB.reset(abcd::IVertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout({
            { abcd::ShaderDataType::Float3, "a_Position" },
            { abcd::ShaderDataType::Float2, "a_TexCoord" }
            });
        mSquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        abcd::Ref<abcd::IIndexBuffer> squareIB;
        squareIB.reset(abcd::IIndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        mSquareVA->SetIndexBuffer(squareIB);

        std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;

				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
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

        mShader = abcd::IShader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

        mFlatColorShader = abcd::IShader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);
        auto textureShader = mShaderLibrary.Load("assets/shaders/Texture.glsl");

        mTexture = abcd::Texture2D::Create("assets/textures/Checkerboard.png");
        mChernoLogoTexture = abcd::Texture2D::Create("assets/textures/ChernoLogo.png");

        std::dynamic_pointer_cast<abcd::OpenGLShader>(textureShader)->Bind();
        std::dynamic_pointer_cast<abcd::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
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
            glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

            std::dynamic_pointer_cast<abcd::OpenGLShader>(mFlatColorShader)->Bind();
            std::dynamic_pointer_cast<abcd::OpenGLShader>(mFlatColorShader)->UploadUniformFloat3("u_Color", mSquareColor);

            for (int y = 0; y < 20; y++)
            {
                for (int x = 0; x < 20; x++)
                {
                    glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                    glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

                    abcd::Renderer::Submit(mFlatColorShader, mSquareVA, transform);
                }
            }

            auto textureShader = mShaderLibrary.Get("Texture");

            mTexture->Bind();
            abcd::Renderer::Submit(textureShader, mSquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
            mChernoLogoTexture->Bind();
            abcd::Renderer::Submit(textureShader, mSquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

            // Triangle
            // abcd::Renderer::Submit(m_Shader, m_VertexArray);
        }

        abcd::Renderer::EndScene();
    }

    virtual void OnImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(mSquareColor));
        ImGui::End();
    }

    void OnEvent(abcd::Event& event) override
    {
    }

private:
    abcd::ShaderLibrary mShaderLibrary;
    abcd::Ref<abcd::IShader> mShader;
    abcd::Ref<abcd::IVertexArray> mVertexArray;
        
    abcd::Ref<abcd::IShader> mFlatColorShader;
    abcd::Ref<abcd::IVertexArray> mSquareVA;

    abcd::Ref<abcd::Texture2D> mTexture, mChernoLogoTexture;

    abcd::OrthographicCamera mCamera;
    glm::vec3 mCameraPosition;
    float mCameraMoveSpeed = 5.0f;

    float mCameraRotation = 0.0f;
    float mCameraRotationSpeed = 180.0f;

    glm::vec3 mSquareColor = { 0.2f, 0.3f, 0.8f };
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