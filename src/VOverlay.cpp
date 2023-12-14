#include "VOverlay.h"
#include "VOverlayVersion.h"



cr::video::VOverlay::~VOverlay()
{

}



std::string cr::video::VOverlay::getVersion()
{
    return VOVERLAY_VERSION;
}