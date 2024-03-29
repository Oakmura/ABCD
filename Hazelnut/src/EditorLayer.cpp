#include "EditorLayer.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ABCD/Scene/SceneSerializer.h"

#include "ABCD/Utils/PlatformUtils.h"

#include "ImGuizmo.h"

#include "ABCD/Math/Math.h"

namespace abcd 
{
    EditorLayer::EditorLayer()
        : Layer("EditorLayer"), mCameraController(1280.0f / 720.0f), mSquareColor({ 0.2f, 0.3f, 0.8f, 1.0f })
    {
    }

    void EditorLayer::OnAttach()
    {
        AB_PROFILE_FUNCTION();

        mCheckerboardTexture = Texture2D::Create("assets/textures/Checkerboard.png");

        FramebufferSpecification fbSpec;
        fbSpec.Width = 1280;
        fbSpec.Height = 720;
        mFramebuffer = IFramebuffer::Create(fbSpec);

        mActiveScene = CreateRef<Scene>();

        mEditorCamera = EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);

#if 0
        // Entity
        auto square = mActiveScene->CreateEntity("Green Square");
        square.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f });
        mSquareEntity = square;

        auto redSquare = mActiveScene->CreateEntity("Red Square");
        redSquare.AddComponent<SpriteRendererComponent>(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });

        mCameraEntity = mActiveScene->CreateEntity("Camera A");
        mCameraEntity.AddComponent<CameraComponent>();

        mSecondCamera = mActiveScene->CreateEntity("Camera B");
        auto& cc = mSecondCamera.AddComponent<CameraComponent>();
        cc.Primary = false;

        class CameraController : public ScriptableEntity
        {
        public:
            virtual void OnCreate() override
            {
                auto& translation = GetComponent<TransformComponent>().Translation;
                translation.x = rand() % 10 - 5.0f;
            }

            virtual void OnDestroy() override
            {
            }

            virtual void OnUpdate(Timestep ts) override
            {
                auto& translation = GetComponent<TransformComponent>().Translation;
                float speed = 5.0f;

                if (Input::IsKeyPressed(Key::A))
                    translation.x -= speed * ts;
                if (Input::IsKeyPressed(Key::D))
                    translation.x += speed * ts;
                if (Input::IsKeyPressed(Key::W))
                    translation.y += speed * ts;
                if (Input::IsKeyPressed(Key::S))
                    translation.y -= speed * ts;
            }
        };

        mCameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
        mSecondCamera.AddComponent<NativeScriptComponent>().Bind<CameraController>();
#endif

        mSceneHierarchyPanel.SetContext(mActiveScene);
    }

    void EditorLayer::OnDetach()
    {
        AB_PROFILE_FUNCTION();
    }

    void EditorLayer::OnUpdate(Timestep ts)
    {
        AB_PROFILE_FUNCTION();

        // Resize
        if (FramebufferSpecification spec = mFramebuffer->GetSpecification();
            mViewportSize.x > 0.0f && mViewportSize.y > 0.0f && // zero sized framebuffer is invalid
            (spec.Width != mViewportSize.x || spec.Height != mViewportSize.y))
        {
            mFramebuffer->Resize((uint32_t)mViewportSize.x, (uint32_t)mViewportSize.y);
            mCameraController.OnResize(mViewportSize.x, mViewportSize.y);

            mEditorCamera.SetViewportSize(mViewportSize.x, mViewportSize.y);
            mActiveScene->OnViewportResize((uint32_t)mViewportSize.x, (uint32_t)mViewportSize.y);
        }

        // Update
        if (mbViewportFocused)
            mCameraController.OnUpdate(ts);

        mEditorCamera.OnUpdate(ts);

        // Render
        Renderer2D::ResetStats();
        mFramebuffer->Bind();
        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        RenderCommand::Clear();

        // Update scene
        mActiveScene->OnUpdateEditor(ts, mEditorCamera);

        mFramebuffer->Unbind();
    }

    void EditorLayer::OnImGuiRender()
    {
        AB_PROFILE_FUNCTION();

        // Note: Switch this to true to enable dockspace
        static bool dockspaceOpen = true;
        static bool opt_fullscreen_persistant = true;
        bool opt_fullscreen = opt_fullscreen_persistant;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(viewport->Size);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        ImGuiStyle& style = ImGui::GetStyle();
        float minWinSizeX = style.WindowMinSize.x;
        style.WindowMinSize.x = 370.0f;
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        style.WindowMinSize.x = minWinSizeX;

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows, 
                // which we can't undo at the moment without finer window depth/z control.
                //ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);
                if (ImGui::MenuItem("New", "Ctrl+N"))
                    NewScene();

                if (ImGui::MenuItem("Open...", "Ctrl+O"))
                    OpenScene();

                if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
                    SaveSceneAs();

                if (ImGui::MenuItem("Exit")) Application::Get().Close();
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        mSceneHierarchyPanel.OnImGuiRender();

        ImGui::Begin("Stats");
        {
            auto stats = Renderer2D::GetStats();
            ImGui::Text("Renderer2D Stats:");
            ImGui::Text("Draw Calls: %d", stats.DrawCalls);
            ImGui::Text("Quads: %d", stats.QuadCount);
            ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
            ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
        }
        ImGui::End();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::Begin("Viewport");

        mbViewportFocused = ImGui::IsWindowFocused();
        mbViewportHovered = ImGui::IsWindowHovered();
        Application::Get().GetImGuiLayer()->BlockEvents(!mbViewportFocused && !mbViewportHovered);

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        mViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
        uint64_t textureID = mFramebuffer->GetColorAttachmentRendererID();
        ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ mViewportSize.x, mViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

        // Gizmos
        Entity selectedEntity = mSceneHierarchyPanel.GetSelectedEntity();
        if (selectedEntity && mGizmoType != -1)
        {
            ImGuizmo::SetOrthographic(false);
            ImGuizmo::SetDrawlist();

            float windowWidth = (float)ImGui::GetWindowWidth();
            float windowHeight = (float)ImGui::GetWindowHeight();
            ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

            // Camera
            // Runtime camera from entity
            // auto cameraEntity = mActiveScene->GetPrimaryCameraEntity();
            // const auto& camera = cameraEntity.GetComponent<CameraComponent>().Camera;
            // const glm::mat4& cameraProjection = camera.GetProjection();
            // glm::mat4 cameraView = glm::inverse(cameraEntity.GetComponent<TransformComponent>().GetTransform());

            // Editor camera
            const glm::mat4& cameraProjection = mEditorCamera.GetProjection();
            glm::mat4 cameraView = mEditorCamera.GetViewMatrix();

            // Entity transform
            auto& tc = selectedEntity.GetComponent<TransformComponent>();
            glm::mat4 transform = tc.GetTransform();

            // Snapping
            bool snap = Input::IsKeyPressed(Key::LeftControl);
            float snapValue = 0.5f; // Snap to 0.5m for translation/scale
            // Snap to 45 degrees for rotation
            if (mGizmoType == ImGuizmo::OPERATION::ROTATE)
                snapValue = 45.0f;

            float snapValues[3] = { snapValue, snapValue, snapValue };

            ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
                (ImGuizmo::OPERATION)mGizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform),
                nullptr, snap ? snapValues : nullptr);

            if (ImGuizmo::IsUsing())
            {
                glm::vec3 translation, rotation, scale;
                Math::DecomposeTransform(transform, translation, rotation, scale);

                glm::vec3 deltaRotation = rotation - tc.Rotation;
                tc.Translation = translation;
                tc.Rotation += deltaRotation;
                tc.Scale = scale;
            }
        }

        ImGui::End();
        ImGui::PopStyleVar();

        ImGui::End();
    }

    void EditorLayer::OnEvent(Event& e)
    {
        mCameraController.OnEvent(e);
        mEditorCamera.OnEvent(e);

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<KeyPressedEvent>(AB_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
    }

    bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
    {
        // Shortcuts
        if (e.GetRepeatCount() > 0)
            return false;

        bool control = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);
        bool shift = Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift);
        switch (e.GetKeyCode())
        {
        case Key::N:
        {
            if (control)
                NewScene();

            break;
        }
        case Key::O:
        {
            if (control)
                OpenScene();

            break;
        }
        case Key::S:
        {
            if (control && shift)
                SaveSceneAs();

            break;
        }
        // Gizmos
        case Key::Q:
            mGizmoType = -1;
            break;
        case Key::W:
            mGizmoType = ImGuizmo::OPERATION::TRANSLATE;
            break;
        case Key::E:
            mGizmoType = ImGuizmo::OPERATION::ROTATE;
            break;
        case Key::R:
            mGizmoType = ImGuizmo::OPERATION::SCALE;
            break;
        }
    }

    void EditorLayer::NewScene()
    {
        mActiveScene = CreateRef<Scene>();
        mActiveScene->OnViewportResize((uint32_t)mViewportSize.x, (uint32_t)mViewportSize.y);
        mSceneHierarchyPanel.SetContext(mActiveScene);
    }

    void EditorLayer::OpenScene()
    {
        std::optional<std::string> filepath = FileDialogs::OpenFile("ABCD Scene (*.abcd)\0*.abcd\0");
        if (filepath)
        {
            mActiveScene = CreateRef<Scene>();
            mActiveScene->OnViewportResize((uint32_t)mViewportSize.x, (uint32_t)mViewportSize.y);
            mSceneHierarchyPanel.SetContext(mActiveScene);

            SceneSerializer serializer(mActiveScene);
            serializer.Deserialize(*filepath);
        }
    }

    void EditorLayer::SaveSceneAs()
    {
        std::optional<std::string> filepath = FileDialogs::SaveFile("ABCD Scene (*.abcd)\0*.abcd\0");
        if (filepath)
        {
            SceneSerializer serializer(mActiveScene);
            serializer.Serialize(*filepath);
        }
    }
}