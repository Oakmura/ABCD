#pragma once

#include "ABCD.h"
#include "Panels/SceneHierarchyPanel.h"

#include "ABCD/Renderer/EditorCamera.h"

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
        bool OnKeyPressed(KeyPressedEvent& e);

        void NewScene();
        void OpenScene();
        void SaveSceneAs();

	private:
		abcd::OrthographicCameraController mCameraController;

		// Temp
		Ref<IVertexArray> mSquareVA;
		Ref<IShader> mFlatColorShader;
		Ref<IFramebuffer> mFramebuffer;

        Ref<Scene> mActiveScene;
        Entity mSquareEntity;
        Entity mCameraEntity;
        Entity mSecondCamera;

        bool mbPrimaryCamera = true;

        EditorCamera mEditorCamera;

		Ref<Texture2D> mCheckerboardTexture;

        bool mbViewportFocused = false;
        bool mbViewportHovered = false;
        glm::vec2 mViewportSize = { 0.0f, 0.0f };

        glm::vec4 mSquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

        int mGizmoType = -1;

        // Panels
        SceneHierarchyPanel mSceneHierarchyPanel;
	};
}