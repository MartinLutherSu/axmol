/****************************************************************************
Copyright (c) 2010-2013 cocos2d-x.org
Copyright (c) Microsoft Open Technologies, Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
Copyright (c) 2019-present Axmol Engine contributors (see AUTHORS.md).

https://axmol.dev/

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifndef __AX_APPLICATION_WINRT_H__
#define __AX_APPLICATION_WINRT_H__

#include "platform/PlatformConfig.h"
#if (AX_TARGET_PLATFORM == AX_PLATFORM_WINRT)

#    include "platform/StdC.h"
#    include "platform/Common.h"
#    include "platform/ApplicationBase.h"
#    include "platform/winrt/InputEvent.h"
#    include <string>
#    include <functional>

namespace ax
{

class AX_DLL Application : public ApplicationBase
{
public:
    Application();
    virtual ~Application();

    /**
    @brief    Run the message loop.
    */
    int run();

    /**
    * @brief frame step with FPS control
    */
    bool frameStep(const std::function<bool()>& onFrame);

    /**
    @brief    Get current application instance.
    @return Current application instance pointer.
    */
    static Application* getInstance();

    /* override functions */
    virtual void setAnimationInterval(float interval) override;
    // virtual void setAnimationInterval(float interval, SetIntervalReason reason) override;

    virtual LanguageType getCurrentLanguage() override;
    virtual const char* getCurrentLanguageCode() override;

    /**
     @brief Get target platform
     */
    virtual Platform getTargetPlatform() override;

    /**
     @brief Get application version
     */
    virtual std::string getVersion() override;

    /**
     @brief Open url in default browser
     @param String with url to open.
     @return true if the resource located by the URL was successfully opened; otherwise false.
     */
    virtual bool openURL(std::string_view url);

    /**
    @brief Set the callback responsible for opening a URL.
    @param del The delegate that will handle opening a URL. We can't pass back a Platform::String due to name clash.
    */
    void SetXamlOpenURLDelegate(const std::function<void(const winrt::hstring&)>& del) { m_openURLDelegate = del; }

    void setStartupScriptFilename(const std::string& startupScriptFile);

    const std::string& getStartupScriptFilename(void) { return m_startupScriptFilename; }

protected:
    LARGE_INTEGER m_nAnimationInterval;
    LARGE_INTEGER m_nFreq;
    LARGE_INTEGER m_nLast;
    LARGE_INTEGER m_nNow;

    std::string m_resourceRootPath;
    std::string m_startupScriptFilename;

    std::function<void(const winrt::hstring&)> m_openURLDelegate;

    static Application* sm_pSharedApplication;
};

}

#endif  // AX_TARGET_PLATFORM == AX_PLATFORM_WINRT

#endif  // __AX_APPLICATION_WINRT_H__
