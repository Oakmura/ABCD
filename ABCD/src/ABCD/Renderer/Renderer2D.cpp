#include "abpch.h"
#include "ABCD/Renderer/Renderer2D.h"

#include "ABCD/Renderer/IVertexArray.h"
#include "ABCD/Renderer/IShader.h"
#include "ABCD/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace abcd 
{
    struct Renderer2DStorage
    {
        Ref<IVertexArray> QuadVertexArray;
        Ref<IShader> TextureShader;
        Ref<Texture2D> WhiteTexture;
    };

    static Renderer2DStorage* sData;

    void Renderer2D::Init()
    {
        sData = new Renderer2DStorage();
        sData->QuadVertexArray = IVertexArray::Create();

        float squareVertices[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        Ref<IVertexBuffer> squareVB = IVertexBuffer::Create(squareVertices, sizeof(squareVertices));
        squareVB->SetLayout({
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float2, "a_TexCoord" }
            });
        sData->QuadVertexArray->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        Ref<IIndexBuffer> squareIB = IIndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
        sData->QuadVertexArray->SetIndexBuffer(squareIB);

        sData->WhiteTexture = Texture2D::Create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        sData->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

        sData->TextureShader = IShader::Create("assets/shaders/Texture.glsl");
        sData->TextureShader->Bind();
        sData->TextureShader->SetInt("u_Texture", 0);
    }

    void Renderer2D::Shutdown()
    {
        delete sData;
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        sData->TextureShader->Bind();
        sData->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
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
        sData->TextureShader->SetFloat4("u_Color", color);
        sData->WhiteTexture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        sData->TextureShader->SetMat4("u_Transform", transform);

        sData->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(sData->QuadVertexArray);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, texture);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
    {
        sData->TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));
        texture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        sData->TextureShader->SetMat4("u_Transform", transform);

        sData->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(sData->QuadVertexArray);
    }
}