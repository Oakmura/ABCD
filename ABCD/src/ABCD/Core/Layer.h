#pragma once

#include "ABCD/Core/Base.h"
#include "ABCD/Core/Timestep.h"
#include "ABCD/Events/Event.h"

namespace abcd 
{
    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep ts) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event& event) {}

        const std::string& GetName() const { return mDebugName; }

    protected:
        std::string mDebugName;
    };
}