#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), mCameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
    mSquareVA = abcd::IVertexArray::Create();

    float squareVertices[5 * 4] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    abcd::Ref<abcd::IVertexBuffer> squareVB;
    squareVB.reset(abcd::IVertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    squareVB->SetLayout({
        { abcd::ShaderDataType::Float3, "a_Position" }
        });
    mSquareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
    abcd::Ref<abcd::IIndexBuffer> squareIB;
    squareIB.reset(abcd::IIndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
    mSquareVA->SetIndexBuffer(squareIB);

    mFlatColorShader = abcd::IShader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(abcd::Timestep ts)
{
    // Update
    mCameraController.OnUpdate(ts);

    // Render
    abcd::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    abcd::RenderCommand::Clear();

    abcd::Renderer::BeginScene(mCameraController.GetCamera());

    std::dynamic_pointer_cast<abcd::OpenGLShader>(mFlatColorShader)->Bind();
    std::dynamic_pointer_cast<abcd::OpenGLShader>(mFlatColorShader)->UploadUniformFloat4("u_Color", mSquareColor);

    abcd::Renderer::Submit(mFlatColorShader, mSquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    abcd::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(mSquareColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(abcd::Event& e)
{
    mCameraController.OnEvent(e);
}