#pragma once

#include "ABCD.h"

class Sandbox2D : public abcd::Layer
{
public:
    Sandbox2D();
    virtual ~Sandbox2D() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void OnUpdate(abcd::Timestep ts) override;
    virtual void OnImGuiRender() override;
    void OnEvent(abcd::Event& e) override;
private:
    abcd::OrthographicCameraController mCameraController;

    // Temp
    abcd::Ref<abcd::IVertexArray> mSquareVA;
    abcd::Ref<abcd::IShader> mFlatColorShader;
    abcd::Ref<abcd::IFramebuffer> mFramebuffer;

    abcd::Ref<abcd::Texture2D> mCheckerboardTexture;

    glm::vec4 mSquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};