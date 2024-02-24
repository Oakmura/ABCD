#pragma once

#include "ABCD.h"

class ExampleLayer : public abcd::Layer
{
public:
    ExampleLayer();
    virtual ~ExampleLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void OnUpdate(abcd::Timestep ts) override;
    virtual void OnImGuiRender() override;
    void OnEvent(abcd::Event& e) override;
private:
    abcd::ShaderLibrary mShaderLibrary;
    abcd::Ref<abcd::IShader> mShader;
    abcd::Ref<abcd::IVertexArray> mVertexArray;

    abcd::Ref<abcd::IShader> mFlatColorShader;
    abcd::Ref<abcd::IVertexArray> mSquareVA;

    abcd::Ref<abcd::Texture2D> mTexture, mChernoLogoTexture;

    abcd::OrthographicCameraController mCameraController;
    glm::vec3 mSquareColor = { 0.2f, 0.3f, 0.8f };
};
