#include "abpch.h"
#include "ABCD/Renderer/RenderCommand.h"

namespace abcd 
{
    Scope<IRendererAPI> RenderCommand::sRendererAPI = IRendererAPI::Create();
}