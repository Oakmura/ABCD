#include "abpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace abcd 
{
    RendererAPI* RenderCommand::sRendererAPI = new OpenGLRendererAPI;
}