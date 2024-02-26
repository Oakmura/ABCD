#pragma once

#include "ABCD.h"

namespace abcd 
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:
		abcd::OrthographicCameraController mCameraController;

		// Temp
		Ref<IVertexArray> mSquareVA;
		Ref<IShader> mFlatColorShader;
		Ref<IFramebuffer> mFramebuffer;

		Ref<Texture2D> mCheckerboardTexture;

		glm::vec4 mSquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	};
}