#include "VOverlay.h"
#include "VOverlayVersion.h"
#include <string>



cr::video::VOverlay::~VOverlay()
{

}



std::string cr::video::VOverlay::getVersion()
{
    return VOVERLAY_VERSION;
}