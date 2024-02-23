#pragma once

#include "ABCD/Core/Core.h"
#include "Layer.h"

namespace abcd
{
    class LayerStack
    {
    public:
        LayerStack() = default;
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        std::vector<Layer*>::iterator begin() { return mLayers.begin(); }
        std::vector<Layer*>::iterator end() { return mLayers.end(); }

    private:
        std::vector<Layer*> mLayers;
        unsigned int mLayerInsertIndex = 0;
    };
}