/*  LOOT

    A load order optimisation tool for Oblivion, Skyrim, Fallout 3 and
    Fallout: New Vegas.

    Copyright (C) 2014-2016    WrinklyNinja

    This file is part of LOOT.

    LOOT is free software: you can redistribute
    it and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version.

    LOOT is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with LOOT.  If not, see
    <https://www.gnu.org/licenses/>.
    */

#ifndef LOOT_GUI_LOOT_APP
#define LOOT_GUI_LOOT_APP

#include <include/cef_app.h>
#include <include/base/cef_lock.h>
#include <include/wrapper/cef_message_router.h>

#include "backend/app/loot_state.h"

namespace loot {
class LootApp : public CefApp,
  public CefBrowserProcessHandler,
  public CefRenderProcessHandler {
public:
  void Initialise(const std::string& defaultGame,
                  const std::string& lootDataPath,
                  const std::string& url);

  // Override CefApp methods.
  virtual void OnBeforeCommandLineProcessing(const CefString& process_type,
                                             CefRefPtr<CefCommandLine> command_line);
  virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE;
  virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE;

  // Override CefBrowserProcessHandler methods.
  virtual void OnContextInitialized() OVERRIDE;
  virtual void OnWebKitInitialized() OVERRIDE;

  // Override CefRenderProcessHandler methods.
  virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                        CefProcessId source_process,
                                        CefRefPtr<CefProcessMessage> message) OVERRIDE;

private:
  virtual void OnContextCreated(CefRefPtr<CefBrowser> browser,
                                CefRefPtr<CefFrame> frame,
                                CefRefPtr<CefV8Context> context) OVERRIDE;

  LootState lootState_;
  CefRefPtr<CefMessageRouterRendererSide> message_router_;
  std::string url_;

  IMPLEMENT_REFCOUNTING(LootApp);
};
}

#endif
