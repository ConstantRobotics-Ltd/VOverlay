#pragma once
#include "Frame.h"
#include <string>



namespace cr
{
namespace video
{
/**
 * @brief Video overlay interface class.
 *
 * The class only declares the interface: all checks of the frame and of the
 * custom data are done by the implementation.
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
     * @note The method is thread-safe.
     * @return String of the current class version "Major.Minor.Patch".
     */
    static std::string getVersion();

    /**
     * @brief Overlay information on the video.
     *
     * The interface does not check the frame and the custom data: they are
     * passed to the implementation as is. The implementation must validate
     * them before use.
     *
     * @note The interface does not define thread safety of the method. The
     * implementation documents whether it can be called from several threads.
     * @param frame Frame on which to put information. The frame data is
     * changed in place. The content of the frame after an error depends on
     * the implementation.
     * @param data Pointer to custom data. Type, size and lifetime depend on
     * implementation. The method does not take ownership of the data.
     * Can be nullptr if the implementation does not need custom data.
     * @return TRUE if everything is OK or FALSE in case of any errors
     * (unsupported frame format, invalid frame data, invalid custom data).
     */
    virtual bool overlay(cr::video::Frame& frame, void* data = nullptr) = 0;

protected:

    /**
     * @brief Default constructor. The class can be used as a base only.
     */
    VOverlay() = default;

    /**
     * @brief Copy constructor.
     * @param src Source object.
     */
    VOverlay(const VOverlay& src) = default;

    /**
     * @brief Move constructor.
     * @param src Source object.
     */
    VOverlay(VOverlay&& src) = default;

    /**
     * @brief Copy assignment operator.
     * @param src Source object.
     * @return Reference to the object.
     */
    VOverlay& operator= (const VOverlay& src) = default;

    /**
     * @brief Move assignment operator.
     * @param src Source object.
     * @return Reference to the object.
     */
    VOverlay& operator= (VOverlay&& src) = default;
};
}
}