#pragma once

#include <glm/glm.hpp>

#include "ABCD/Core/KeyCodes.h"
#include "ABCD/Core/MouseCodes.h"

namespace abcd 
{
    class Input
    {
    public:
        static bool IsKeyPressed(KeyCode key);

        static bool IsMouseButtonPressed(MouseCode button);
        static glm::vec2 GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();
    };
}