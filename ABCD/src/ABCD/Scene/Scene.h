#pragma once

#include "entt.hpp"

#include "ABCD/Core/Timestep.h"

namespace abcd 
{
    class Scene
    {
    public:
        Scene();
        ~Scene();

        entt::entity CreateEntity();

        // TEMP
        entt::registry& Reg() { return mRegistry; }

        void OnUpdate(Timestep ts);
    private:
        entt::registry mRegistry;
    };
}