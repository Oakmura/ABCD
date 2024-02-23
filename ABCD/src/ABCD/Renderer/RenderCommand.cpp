#include "abpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace abcd 
{
    Scope<IRendererAPI> RenderCommand::sRendererAPI = CreateScope<OpenGLRendererAPI>();
}