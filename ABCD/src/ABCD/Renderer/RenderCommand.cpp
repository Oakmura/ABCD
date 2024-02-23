#include "abpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace abcd 
{
    IRendererAPI* RenderCommand::sRendererAPI = new OpenGLRendererAPI;
}