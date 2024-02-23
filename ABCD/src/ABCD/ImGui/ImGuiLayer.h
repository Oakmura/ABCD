#pragma once

#include "ABCD/Core/Layer.h"

#include "ABCD/Events/ApplicationEvent.h"
#include "ABCD/Events/KeyEvent.h"
#include "ABCD/Events/MouseEvent.h"

namespace abcd 
{
    class AB_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();

    private:
        float mTime = 0.0f;
    };
}