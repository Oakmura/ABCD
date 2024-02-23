#pragma once

#include <glm/glm.hpp>

namespace abcd 
{
    class OrthographicCamera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);

        void SetProjection(float left, float right, float bottom, float top);

        const glm::vec3& GetPosition() const { return mPosition; }
        void SetPosition(const glm::vec3& position) { mPosition = position; recalculateViewMatrix(); }

        float GetRotation() const { return mRotation; }
        void SetRotation(float rotation) { mRotation = rotation; recalculateViewMatrix(); }

        const glm::mat4& GetProjectionMatrix() const { return mProjectionMatrix; }
        const glm::mat4& GetViewMatrix() const { return mViewMatrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return mViewProjectionMatrix; }
    private:
        void recalculateViewMatrix();

    private:
        glm::mat4 mProjectionMatrix;
        glm::mat4 mViewMatrix;
        glm::mat4 mViewProjectionMatrix;

        glm::vec3 mPosition = { 0.0f, 0.0f, 0.0f };
        float mRotation = 0.0f;
    };
}