#include "abpch.h"
#include "LayerStack.h"

namespace abcd
{
    LayerStack::LayerStack()
    {
    }

    LayerStack::~LayerStack()
    {
        for (Layer* layer : mLayers)
        {
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        mLayers.emplace(mLayers.begin() + m_LayerInsertIndex, layer);
        m_LayerInsertIndex++;
    }

    void LayerStack::PushOverlay(Layer* overlay)
    {
        mLayers.emplace_back(overlay);
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        auto it = std::find(mLayers.begin(), mLayers.end(), layer);
        if (it != mLayers.end())
        {
            mLayers.erase(it);
            m_LayerInsertIndex--;
        }
    }

    void LayerStack::PopOverlay(Layer* overlay)
    {
        auto it = std::find(mLayers.begin(), mLayers.end(), overlay);
        if (it != mLayers.end())
        {
            mLayers.erase(it);
        }
    }
}