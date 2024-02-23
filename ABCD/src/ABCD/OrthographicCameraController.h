#pragma once

#include "ABCD/Renderer/OrthographicCamera.h"
#include "ABCD/Core/Timestep.h"

#include "ABCD/Events/ApplicationEvent.h"
#include "ABCD/Events/MouseEvent.h"

namespace abcd
{
    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void OnUpdate(Timestep ts);
        void OnEvent(Event& e);

        OrthographicCamera& GetCamera() { return mCamera; }
        const OrthographicCamera& GetCamera() const { return mCamera; }

        float GetZoomLevel() const { return mZoomLevel; }
        void SetZoomLevel(float level) { mZoomLevel = level; }
    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);
    private:
        float mAspectRatio;
        float mZoomLevel = 1.0f;
        OrthographicCamera mCamera;

        bool mbRotation;

        glm::vec3 mCameraPosition = { 0.0f, 0.0f, 0.0f };
        float mCameraRotation = 0.0f;
        float mCameraTranslationSpeed = 5.0f, mCameraRotationSpeed = 180.0f;
    };
}