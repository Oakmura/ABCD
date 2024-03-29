#pragma once

#include "ABCD/Core/Base.h"

namespace abcd 
{
    struct FramebufferSpecification
    {
        uint32_t Width = 0, Height = 0;
        // FramebufferFormat Format = 
        uint32_t Samples = 1;

        bool SwapChainTarget = false;
    };

    class IFramebuffer
    {
    public:
        virtual ~IFramebuffer() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void Resize(uint32_t width, uint32_t height) = 0;

        virtual uint32_t GetColorAttachmentRendererID() const = 0;

        virtual const FramebufferSpecification& GetSpecification() const = 0;

        static Ref<IFramebuffer> Create(const FramebufferSpecification& spec);
    };
}