#pragma once
#include "Frame.h"
#include <string>



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
     * @brief Get string of the current class version.
     * @return String of the current class version "Major.Minor.Patch"
     */
    static std::string getVersion();

    /**
     * @brief Overlay information on the video.
     * @param frame Frame on which to put information.
     * @param data Pointer to custom data. Depends on implementation.
     * @return TRUE if everything is OK or FALSE in case of any errors.
     */
    virtual bool overlay(cr::video::Frame& frame, void* data = nullptr) = 0;
};
}
}