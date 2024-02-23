#include "abpch.h"
#include "ABCD/Renderer/OrthographicCameraController.h"

#include "ABCD/Core/Input.h"
#include "ABCD/Core/KeyCodes.h"

namespace abcd 
{
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
        : mAspectRatio(aspectRatio), mCamera(-mAspectRatio * mZoomLevel, mAspectRatio* mZoomLevel, -mZoomLevel, mZoomLevel), mbRotation(rotation)
    {
    }

    void OrthographicCameraController::OnUpdate(Timestep ts)
    {
        if (Input::IsKeyPressed(AB_KEY_A))
        {
            mCameraPosition.x -= cos(glm::radians(mCameraRotationInDegree)) * mCameraTranslationSpeed * ts;
            mCameraPosition.y -= sin(glm::radians(mCameraRotationInDegree)) * mCameraTranslationSpeed * ts;
        }
        else if (Input::IsKeyPressed(AB_KEY_D))
        {
            mCameraPosition.x += cos(glm::radians(mCameraRotationInDegree)) * mCameraTranslationSpeed * ts;
            mCameraPosition.y += sin(glm::radians(mCameraRotationInDegree)) * mCameraTranslationSpeed * ts;
        }

        if (Input::IsKeyPressed(AB_KEY_W))
        {
            mCameraPosition.x += -sin(glm::radians(mCameraRotationInDegree)) * mCameraTranslationSpeed * ts;
            mCameraPosition.y += cos(glm::radians(mCameraRotationInDegree)) * mCameraTranslationSpeed * ts;
        }
        else if (Input::IsKeyPressed(AB_KEY_S))
        {
            mCameraPosition.x -= -sin(glm::radians(mCameraRotationInDegree)) * mCameraTranslationSpeed * ts;
            mCameraPosition.y -= cos(glm::radians(mCameraRotationInDegree)) * mCameraTranslationSpeed * ts;
        }

        if (mbRotation)
        {
            if (Input::IsKeyPressed(AB_KEY_Q))
            {
                mCameraRotationInDegree += mCameraRotationSpeed * ts;
            }
            if (Input::IsKeyPressed(AB_KEY_E))
            {
                mCameraRotationInDegree -= mCameraRotationSpeed * ts;
            }

            if (mCameraRotationInDegree > 180.0f)
            {
                mCameraRotationInDegree -= 360.0f;
            }
            else if (mCameraRotationInDegree <= -180.0f)
            {
                mCameraRotationInDegree += 360.0f;
            }

            mCamera.SetRotation(mCameraRotationInDegree);
        }

        mCamera.SetPosition(mCameraPosition);

        mCameraTranslationSpeed = mZoomLevel;
    }

    void OrthographicCameraController::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(AB_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(AB_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        mZoomLevel -= e.GetYOffset() * 0.25f;
        mZoomLevel = std::max(mZoomLevel, 0.25f);
        mCamera.SetProjection(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel);
        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
    {
        mAspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        mCamera.SetProjection(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel);
        return false;
    }
}