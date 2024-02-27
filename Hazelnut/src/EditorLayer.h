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

        Ref<Scene> mActiveScene;
        Entity mSquareEntity;

		Ref<Texture2D> mCheckerboardTexture;

        bool mbViewportFocused = false;
        bool mbViewportHovered = false;
        glm::vec2 mViewportSize = { 0.0f, 0.0f };

		glm::vec4 mSquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	};
}