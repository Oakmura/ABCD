#include <ABCD.h>
#include <ABCD/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace abcd 
{
	class Hazelnut : public Application
	{
	public:
		Hazelnut()
			: Application("Hazelnut")
		{
			PushLayer(new EditorLayer());
		}

		~Hazelnut()
		{
		}
	};

	Application* CreateApplication()
	{
		return new Hazelnut();
	}
}