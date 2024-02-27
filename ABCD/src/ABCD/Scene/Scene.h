#pragma once

#include "entt.hpp"

#include "ABCD/Core/Timestep.h"

namespace abcd 
{
    class Entity;

    class Scene
    {
    public:
        Scene();
        ~Scene();

        Entity CreateEntity(const std::string& name = std::string());

        void OnUpdate(Timestep ts);
    private:
        entt::registry mRegistry;

        friend class Entity;
    };
}