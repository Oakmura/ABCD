#pragma once

#include "ABCD/Core/Base.h"
#include "ABCD/Scene/Scene.h"
#include "ABCD/Scene/Entity.h"

namespace abcd 
{
    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel() = default;
        SceneHierarchyPanel(const Ref<Scene>& scene);

        void SetContext(const Ref<Scene>& scene);

        void OnImGuiRender();

        Entity GetSelectedEntity() const { return mSelectionContext; }
    private:
        void DrawEntityNode(Entity entity);
        void DrawComponents(Entity entity);
    private:
        Ref<Scene> mContext;
        Entity mSelectionContext;
    };
}