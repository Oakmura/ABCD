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
        float TexIndex;
        float TilingFactor;
    };

    struct Renderer2DData
    {
        static const uint32_t MaxQuads = 20000;
        static const uint32_t MaxVertices = MaxQuads * 4;
        static const uint32_t MaxIndices = MaxQuads * 6;
        static const uint32_t MaxTextureSlots = 32; // TODO: RenderCaps

        Ref<IVertexArray> QuadVertexArray;
        Ref<IVertexBuffer> QuadVertexBuffer;
        Ref<IShader> TextureShader;
        Ref<Texture2D> WhiteTexture;

        uint32_t QuadIndexCount = 0;
        QuadVertex* QuadVertexBufferBase = nullptr;
        QuadVertex* QuadVertexBufferPtr = nullptr;

        std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
        uint32_t TextureSlotIndex = 1; // 0 = white texture

        glm::vec4 QuadVertexPositions[4];

        Renderer2D::Statistics Stats;
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
            { ShaderDataType::Float2, "a_TexCoord" },
            { ShaderDataType::Float, "a_TexIndex" },
            { ShaderDataType::Float, "a_TilingFactor" }
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

        int32_t samplers[sData.MaxTextureSlots];
        for (uint32_t i = 0; i < sData.MaxTextureSlots; i++)
            samplers[i] = i;

        sData.TextureShader = IShader::Create("assets/shaders/Texture.glsl");
        sData.TextureShader->Bind();
        sData.TextureShader->SetIntArray("u_Textures", samplers, sData.MaxTextureSlots);

        // Set all texture slots to 0
        sData.TextureSlots[0] = sData.WhiteTexture;

        sData.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
        sData.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
        sData.QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
        sData.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
    }

    void Renderer2D::Shutdown()
    {
        AB_PROFILE_FUNCTION();

        delete[] sData.QuadVertexBufferBase;
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        AB_PROFILE_FUNCTION();

        sData.TextureShader->Bind();
        sData.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

        sData.QuadIndexCount = 0;
        sData.QuadVertexBufferPtr = sData.QuadVertexBufferBase;

        sData.TextureSlotIndex = 1;
    }

    void Renderer2D::BeginScene(const Camera& camera, const glm::mat4& transform)
    {
        AB_PROFILE_FUNCTION();

        glm::mat4 viewProj = camera.GetProjection() * glm::inverse(transform);

        sData.TextureShader->Bind();
        sData.TextureShader->SetMat4("u_ViewProjection", viewProj);

        sData.QuadIndexCount = 0;
        sData.QuadVertexBufferPtr = sData.QuadVertexBufferBase;

        sData.TextureSlotIndex = 1;
    }

    void Renderer2D::EndScene()
    {
        AB_PROFILE_FUNCTION();

        uint32_t dataSize = (uint32_t)((uint8_t*)sData.QuadVertexBufferPtr - (uint8_t*)sData.QuadVertexBufferBase);
        sData.QuadVertexBuffer->SetData(sData.QuadVertexBufferBase, dataSize);

        Flush();
    }

    void Renderer2D::Flush()
    {
        if (sData.QuadIndexCount == 0)
            return; // Nothing to draw

        // Bind textures
        for (uint32_t i = 0; i < sData.TextureSlotIndex; i++)
            sData.TextureSlots[i]->Bind(i);

        RenderCommand::DrawIndexed(sData.QuadVertexArray, sData.QuadIndexCount);
        sData.Stats.DrawCalls++;
    }

    void Renderer2D::FlushAndReset()
    {
        EndScene();

        sData.QuadIndexCount = 0;
        sData.QuadVertexBufferPtr = sData.QuadVertexBufferBase;

        sData.TextureSlotIndex = 1;
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        AB_PROFILE_FUNCTION();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        DrawQuad(transform, color);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        AB_PROFILE_FUNCTION();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        DrawQuad(transform, texture, tilingFactor);
    }

    void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
    {
        AB_PROFILE_FUNCTION();

        constexpr size_t quadVertexCount = 4;
        const float textureIndex = 0.0f; // White Texture
        constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
        const float tilingFactor = 1.0f;

        if (sData.QuadIndexCount >= Renderer2DData::MaxIndices)
            FlushAndReset();

        for (size_t i = 0; i < quadVertexCount; i++)
        {
            sData.QuadVertexBufferPtr->Position = transform * sData.QuadVertexPositions[i];
            sData.QuadVertexBufferPtr->Color = color;
            sData.QuadVertexBufferPtr->TexCoord = textureCoords[i];
            sData.QuadVertexBufferPtr->TexIndex = textureIndex;
            sData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
            sData.QuadVertexBufferPtr++;
        }

        sData.QuadIndexCount += 6;

        sData.Stats.QuadCount++;
    }

    void Renderer2D::DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        AB_PROFILE_FUNCTION();

        constexpr size_t quadVertexCount = 4;
        constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

        if (sData.QuadIndexCount >= Renderer2DData::MaxIndices)
            FlushAndReset();

        float textureIndex = 0.0f;
        for (uint32_t i = 1; i < sData.TextureSlotIndex; i++)
        {
            if (*sData.TextureSlots[i].get() == *texture.get())
            {
                textureIndex = (float)i;
                break;
            }
        }

        if (textureIndex == 0.0f)
        {
            if (sData.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
                FlushAndReset();

            textureIndex = (float)sData.TextureSlotIndex;
            sData.TextureSlots[sData.TextureSlotIndex] = texture;
            sData.TextureSlotIndex++;
        }

        for (size_t i = 0; i < quadVertexCount; i++)
        {
            sData.QuadVertexBufferPtr->Position = transform * sData.QuadVertexPositions[i];
            sData.QuadVertexBufferPtr->Color = tintColor;
            sData.QuadVertexBufferPtr->TexCoord = textureCoords[i];
            sData.QuadVertexBufferPtr->TexIndex = textureIndex;
            sData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
            sData.QuadVertexBufferPtr++;
        }

        sData.QuadIndexCount += 6;

        sData.Stats.QuadCount++;
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
    {
        DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
    {
        AB_PROFILE_FUNCTION();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        DrawQuad(transform, color);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        AB_PROFILE_FUNCTION();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        DrawQuad(transform, texture, tilingFactor, tintColor);
    }

    void Renderer2D::ResetStats()
    {
        memset(&sData.Stats, 0, sizeof(Statistics));
    }

    Renderer2D::Statistics Renderer2D::GetStats()
    {
        return sData.Stats;
    }
}