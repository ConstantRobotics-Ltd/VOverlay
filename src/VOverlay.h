#pragma once
#include "Frame.h"



namespace cr
{
namespace video
{
/**
 * @brief Video overlay interface class.
 */
class VOverlay
{
public:

    /**
     * @brief Class destructor.
     */
    virtual ~VOverlay();

    /**
     * @brief Get string of current class version.
     * @return String of current class version "Major.Minor.Patch"
     */
    static std::string getVersion();

    /**
     * @brief Overlay the information on the video.
     * @param frame Frame to put information.
     * @param data Pointer to custom data. Depends on implementation.
     * @return TRUE if everything OK or FALSE in case any errors.
     */
    virtual bool overlay(cr::video::Frame& frame, void* data = nullptr) = 0;
};
}
}