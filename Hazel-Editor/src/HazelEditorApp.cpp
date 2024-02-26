#include <ABCD.h>
#include <ABCD/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace abcd 
{
	class HazelEditor : public Application
	{
	public:
		HazelEditor()
			: Application("Hazel Editor")
		{
			PushLayer(new EditorLayer());
		}

		~HazelEditor()
		{
		}
	};

	Application* CreateApplication()
	{
		return new HazelEditor();
	}
}