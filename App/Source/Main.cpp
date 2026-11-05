#include "Core/Application.h"

#include "AppLayer.h"
#include "OverlayLayer.h"

int main()
{
	Core::ApplicationSpecification appSpec;
	appSpec.Name = "LayersSFML";
	
	Core::Application application(appSpec);
	application.pushLayer<AppLayer>();
	application.pushLayer<OverlayLayer>();
	application.run();
}

////////////////////////////
//
// Remember to enable the "Automatically close the console when debugging stops" option.
//
////////////////////////////
