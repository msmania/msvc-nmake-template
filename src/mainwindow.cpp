#ifdef WIN32
#include <memory>
#include <tchar.h>
#include <windows.h>
#include "basewindow.h"

void Log(LPCTSTR format, ...) {
  TCHAR linebuf[1024];
  va_list v;
  va_start(v, format);
  wvsprintf(linebuf, format, v);
  va_end(v);
  OutputDebugString(linebuf);
}
class MainWindow : public BaseWindow<MainWindow> {
private:
  bool InitWindow() {
    return true;
  }

public:
  LPCTSTR ClassName() const {
    return _T("MainWindow");
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
#endif // WIN32

int UIThreadMain() {
#ifdef WIN32
  const auto flags = COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE;
  if (SUCCEEDED(CoInitializeEx(nullptr, flags))) {
    if (auto p = std::make_unique<MainWindow>()) {
      if (p->Create(_T("MainWindow Title"),
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
#endif // WIN32
  return 0;
}