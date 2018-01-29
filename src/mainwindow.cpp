#include <windows.h>
#include <memory>
#include "basewindow.h"

class MainWindow : public BaseWindow<MainWindow> {
private:
  bool InitWindow() {
    return true;
  }

public:
  LPCWSTR ClassName() const {
    return L"MainWindow";
  }

  LRESULT HandleMessage(UINT msg, WPARAM w, LPARAM l) {
    LRESULT ret = 0;
    switch (msg) {
    case WM_CREATE:
      if (!InitWindow()) {
        return -1;
      }
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    default:
      ret = DefWindowProc(hwnd(), msg, w, l);
      break;
    }
    return ret;
  }
};

int UIThreadMain() {
  const auto flags = COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE;
  if (SUCCEEDED(CoInitializeEx(nullptr, flags))) {
    if (auto p = std::make_unique<MainWindow>()) {
      if (p->Create(L"MainWindow",
                    WS_OVERLAPPEDWINDOW,
                    /*style_ex*/0,
                    CW_USEDEFAULT, 0,
                    486, 300)) {
        ShowWindow(p->hwnd(), SW_SHOW);
        MSG msg{};
        while (GetMessage(&msg, nullptr, 0, 0)) {
          TranslateMessage(&msg);
          DispatchMessage(&msg);
        }
      }
    }
    CoUninitialize();
  }
  return 0;
}