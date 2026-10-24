#include "VOverlay.h"
#include "VOverlayVersion.h"
#include <string>



rapidpixel::VOverlay::~VOverlay()
{

}



std::string rapidpixel::VOverlay::getVersion()
{
    return VOVERLAY_VERSION;
}