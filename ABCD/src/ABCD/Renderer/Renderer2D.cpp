#include "abpch.h"
#include "Renderer2D.h"

#include "IVertexArray.h"
#include "IShader.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace abcd 
{
    struct Renderer2DStorage
    {
        Ref<IVertexArray> QuadVertexArray;
        Ref<IShader> FlatColorShader;
    };

    static Renderer2DStorage* sData;

    void Renderer2D::Init()
    {
        sData = new Renderer2DStorage();
        sData->QuadVertexArray = IVertexArray::Create();

        float squareVertices[3 * 4] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };

        Ref<IVertexBuffer> squareVB;
        squareVB = IVertexBuffer::Create(squareVertices, sizeof(squareVertices));
        squareVB->SetLayout({
            { ShaderDataType::Float3, "a_Position" }
            });
        sData->QuadVertexArray->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        Ref<IIndexBuffer> squareIB;
        squareIB = IIndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
        sData->QuadVertexArray->SetIndexBuffer(squareIB);

        sData->FlatColorShader = IShader::Create("assets/shaders/FlatColor.glsl");
    }

    void Renderer2D::Shutdown()
    {
        delete sData;
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        std::dynamic_pointer_cast<OpenGLShader>(sData->FlatColorShader)->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(sData->FlatColorShader)->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
        std::dynamic_pointer_cast<OpenGLShader>(sData->FlatColorShader)->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
    }

    void Renderer2D::EndScene()
    {

    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        std::dynamic_pointer_cast<OpenGLShader>(sData->FlatColorShader)->Bind();
        std::dynamic_pointer_cast<abcd::OpenGLShader>(sData->FlatColorShader)->UploadUniformFloat4("u_Color", color);

        sData->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(sData->QuadVertexArray);
    }
}