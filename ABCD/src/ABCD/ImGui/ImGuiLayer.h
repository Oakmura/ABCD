#pragma once

#include "ABCD/Layer.h"

namespace abcd 
{
    class AB_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach();
        void OnDetach();
        void OnUpdate();
        void OnEvent(Event& event);
    private:
        float mTime = 0.0f;
    };
}