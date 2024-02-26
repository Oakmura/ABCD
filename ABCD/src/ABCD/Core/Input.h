#pragma once

#include "ABCD/Core/Base.h"
#include "ABCD/Core/KeyCodes.h"
#include "ABCD/Core/MouseCodes.h"

namespace abcd 
{
    class Input
    {
    public:
        static bool IsKeyPressed(KeyCode key);

        static bool IsMouseButtonPressed(MouseCode button);
        static std::pair<float, float> GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();
    };
}