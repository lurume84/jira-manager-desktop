// Copyright (c) 2012 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "renderer/client_renderer.h"

#include <sstream>
#include <string>

#include "cef/cef_crash_util.h"
#include "cef/cef_dom.h"
#include "cef/wrapper/cef_helpers.h"
#include "cef/wrapper/cef_message_router.h"
#include "browser/window_test_runner_win.h"

namespace client {
namespace renderer {

namespace {

// Must match the value in client_handler.cc.
const char kFocusedNodeChangedMessage[] = "ClientRenderer.FocusedNodeChanged";
const char kMinimizeWindow[] = "minimize";
const char kMaximizeWindow[] = "maximize";

class V8Handler : public CefV8Handler {
public:
	V8Handler(CefRefPtr<CefBrowser> browser) : m_browser(browser){}

	virtual bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments,
		CefRefPtr<CefV8Value>& retval, CefString& exception) OVERRIDE
	{
		if (name == kMinimizeWindow)
		{
			scoped_ptr<window_test::WindowTestRunnerWin> test_runner(
				new window_test::WindowTestRunnerWin());

			test_runner->Minimize(m_browser);
		}
		else if (name == kMaximizeWindow)
		{
			scoped_ptr<window_test::WindowTestRunnerWin> test_runner(
				new window_test::WindowTestRunnerWin());

			test_runner->Maximize(m_browser);
		}

		return true;
	}

private:
	IMPLEMENT_REFCOUNTING(V8Handler);

	CefRefPtr<CefBrowser> m_browser;
};

class ClientRenderDelegate : public ClientAppRenderer::Delegate {
 public:
  ClientRenderDelegate() : last_node_is_editable_(false) {}

  void OnRenderThreadCreated(CefRefPtr<ClientAppRenderer> app,
                             CefRefPtr<CefListValue> extra_info) OVERRIDE {
    if (CefCrashReportingEnabled()) {
      // Set some crash keys for testing purposes. Keys must be defined in the
      // "crash_reporter.cfg" file. See cef_crash_util.h for details.
      CefSetCrashKeyValue("testkey_small1", "value1_small_renderer");
      CefSetCrashKeyValue("testkey_small2", "value2_small_renderer");
      CefSetCrashKeyValue("testkey_medium1", "value1_medium_renderer");
      CefSetCrashKeyValue("testkey_medium2", "value2_medium_renderer");
      CefSetCrashKeyValue("testkey_large1", "value1_large_renderer");
      CefSetCrashKeyValue("testkey_large2", "value2_large_renderer");
    }
  }

  void OnWebKitInitialized(CefRefPtr<ClientAppRenderer> app) OVERRIDE {
    // Create the renderer-side router for query handling.
    CefMessageRouterConfig config;
    message_router_ = CefMessageRouterRendererSide::Create(config);
  }

  void OnContextCreated(CefRefPtr<ClientAppRenderer> app,
                        CefRefPtr<CefBrowser> browser,
                        CefRefPtr<CefFrame> frame,
                        CefRefPtr<CefV8Context> context) OVERRIDE {
    message_router_->OnContextCreated(browser, frame, context);

	CefRefPtr<CefV8Value> object = context->GetGlobal();

	CefRefPtr<CefV8Handler> handler = new V8Handler(browser);

	// Bind test functions.
	object->SetValue(kMinimizeWindow,
		CefV8Value::CreateFunction(kMinimizeWindow, handler),
		V8_PROPERTY_ATTRIBUTE_READONLY);

	object->SetValue(kMaximizeWindow,
		CefV8Value::CreateFunction(kMaximizeWindow, handler),
		V8_PROPERTY_ATTRIBUTE_READONLY);
  }

  void OnContextReleased(CefRefPtr<ClientAppRenderer> app,
                         CefRefPtr<CefBrowser> browser,
                         CefRefPtr<CefFrame> frame,
                         CefRefPtr<CefV8Context> context) OVERRIDE {
    message_router_->OnContextReleased(browser, frame, context);
  }

  void OnFocusedNodeChanged(CefRefPtr<ClientAppRenderer> app,
                            CefRefPtr<CefBrowser> browser,
                            CefRefPtr<CefFrame> frame,
                            CefRefPtr<CefDOMNode> node) OVERRIDE {
    bool is_editable = (node.get() && node->IsEditable());
    if (is_editable != last_node_is_editable_) {
      // Notify the browser of the change in focused element type.
      last_node_is_editable_ = is_editable;
      CefRefPtr<CefProcessMessage> message =
          CefProcessMessage::Create(kFocusedNodeChangedMessage);
      message->GetArgumentList()->SetBool(0, is_editable);
      browser->SendProcessMessage(PID_BROWSER, message);
    }
  }

  bool OnProcessMessageReceived(CefRefPtr<ClientAppRenderer> app,
                                CefRefPtr<CefBrowser> browser,
                                CefProcessId source_process,
                                CefRefPtr<CefProcessMessage> message) OVERRIDE {
    return message_router_->OnProcessMessageReceived(browser, source_process,
                                                     message);
  }

 private:
  bool last_node_is_editable_;

  // Handles the renderer side of query routing.
  CefRefPtr<CefMessageRouterRendererSide> message_router_;

  DISALLOW_COPY_AND_ASSIGN(ClientRenderDelegate);
  IMPLEMENT_REFCOUNTING(ClientRenderDelegate);
};

}  // namespace

void CreateDelegates(ClientAppRenderer::DelegateSet& delegates) {
  delegates.insert(new ClientRenderDelegate);
}

}  // namespace renderer
}  // namespace client
