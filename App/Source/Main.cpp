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
//  Pamiętaj o opcji "Automatycznie zamknij okno po zakończeniu debugowania"
// 
//	TODO:
//  1. Stworzenie własnych typów eventów
//  2. Uzupełnienie OverlayLayer
//  3. Dodanie VoidLayer
//
////////////////////////////
