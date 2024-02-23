#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), mCameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
    mCheckerboardTexture = abcd::Texture2D::Create("assets/textures/Checkerboard.png");
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

    abcd::Renderer2D::BeginScene(mCameraController.GetCamera());
    {
        abcd::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
        abcd::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
        abcd::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, mCheckerboardTexture);
    }
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