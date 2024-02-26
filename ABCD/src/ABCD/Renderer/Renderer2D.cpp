#include "abpch.h"
#include "ABCD/Renderer/Renderer2D.h"

#include "ABCD/Renderer/IVertexArray.h"
#include "ABCD/Renderer/IShader.h"
#include "ABCD/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace abcd 
{
    struct QuadVertex
    {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoord;
        // TODO: texid
    };

    struct Renderer2DData
    {
        const uint32_t MaxQuads = 10000;
        const uint32_t MaxVertices = MaxQuads * 4;
        const uint32_t MaxIndices = MaxQuads * 6;

        Ref<IVertexArray> QuadVertexArray;
        Ref<IVertexBuffer> QuadVertexBuffer;
        Ref<IShader> TextureShader;
        Ref<Texture2D> WhiteTexture;

        uint32_t QuadIndexCount = 0;
        QuadVertex* QuadVertexBufferBase = nullptr;
        QuadVertex* QuadVertexBufferPtr = nullptr;
    };

    static Renderer2DData sData;

    void Renderer2D::Init()
    {
        AB_PROFILE_FUNCTION();

        sData.QuadVertexArray = IVertexArray::Create();

        sData.QuadVertexBuffer = IVertexBuffer::Create(sData.MaxVertices * sizeof(QuadVertex));
        sData.QuadVertexBuffer->SetLayout({
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" },
            { ShaderDataType::Float2, "a_TexCoord" }
            });
        sData.QuadVertexArray->AddVertexBuffer(sData.QuadVertexBuffer);

        sData.QuadVertexBufferBase = new QuadVertex[sData.MaxVertices];

        uint32_t* quadIndices = new uint32_t[sData.MaxIndices];

        uint32_t offset = 0;
        for (uint32_t i = 0; i < sData.MaxIndices; i += 6)
        {
            quadIndices[i + 0] = offset + 0;
            quadIndices[i + 1] = offset + 1;
            quadIndices[i + 2] = offset + 2;

            quadIndices[i + 3] = offset + 2;
            quadIndices[i + 4] = offset + 3;
            quadIndices[i + 5] = offset + 0;

            offset += 4;
        }

        Ref<IIndexBuffer> quadIB = IIndexBuffer::Create(quadIndices, sData.MaxIndices);
        sData.QuadVertexArray->SetIndexBuffer(quadIB);
        delete[] quadIndices;

        sData.WhiteTexture = Texture2D::Create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        sData.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

        sData.TextureShader = IShader::Create("assets/shaders/Texture.glsl");
        sData.TextureShader->Bind();
        sData.TextureShader->SetInt("u_Texture", 0);
    }

    void Renderer2D::Shutdown()
    {
        AB_PROFILE_FUNCTION();
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        AB_PROFILE_FUNCTION();

        sData.TextureShader->Bind();
        sData.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

        sData.QuadIndexCount = 0;
        sData.QuadVertexBufferPtr = sData.QuadVertexBufferBase;
    }

    void Renderer2D::EndScene()
    {
        AB_PROFILE_FUNCTION();

        uint32_t dataSize = (uint8_t*)sData.QuadVertexBufferPtr - (uint8_t*)sData.QuadVertexBufferBase;
        sData.QuadVertexBuffer->SetData(sData.QuadVertexBufferBase, dataSize);

        Flush();
    }

    void Renderer2D::Flush()
    {
        RenderCommand::DrawIndexed(sData.QuadVertexArray, sData.QuadIndexCount);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        AB_PROFILE_FUNCTION();

        sData.QuadVertexBufferPtr->Position = position;
        sData.QuadVertexBufferPtr->Color = color;
        sData.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
        sData.QuadVertexBufferPtr++;

        sData.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, 0.0f };
        sData.QuadVertexBufferPtr->Color = color;
        sData.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
        sData.QuadVertexBufferPtr++;

        sData.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.0f };
        sData.QuadVertexBufferPtr->Color = color;
        sData.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
        sData.QuadVertexBufferPtr++;

        sData.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, 0.0f };
        sData.QuadVertexBufferPtr->Color = color;
        sData.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
        sData.QuadVertexBufferPtr++;

        sData.QuadIndexCount += 6;

        /*sData.TextureShader->SetFloat("u_TilingFactor", 1.0f);
        sData.WhiteTexture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        sData.TextureShader->SetMat4("u_Transform", transform);
        sData.QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(sData.QuadVertexArray);*/
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        AB_PROFILE_FUNCTION();

        sData.TextureShader->SetFloat4("u_Color", tintColor);
        sData.TextureShader->SetFloat("u_TilingFactor", tilingFactor);
        texture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        sData.TextureShader->SetMat4("u_Transform", transform);

        sData.QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(sData.QuadVertexArray);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
    {
        DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
    {
        AB_PROFILE_FUNCTION();

        sData.TextureShader->SetFloat4("u_Color", color);
        sData.TextureShader->SetFloat("u_TilingFactor", 1.0f);
        sData.WhiteTexture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        sData.TextureShader->SetMat4("u_Transform", transform);
        sData.QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(sData.QuadVertexArray);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        AB_PROFILE_FUNCTION();

        sData.TextureShader->SetFloat4("u_Color", tintColor);
        sData.TextureShader->SetFloat("u_TilingFactor", tilingFactor);
        texture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        sData.TextureShader->SetMat4("u_Transform", transform);

        sData.QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(sData.QuadVertexArray);
    }

}