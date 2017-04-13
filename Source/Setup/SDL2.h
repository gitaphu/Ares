// SDL2
#pragma once

// ImGUI
#include "../ImGUI/imgui.h"
#include "../ImGUI/imgui_impl_sdl.h"
#include "../ImGUI/imgui_internal.h"

extern uintptr_t* m_piSwapWindowPtr; // Pointer to swap window
extern uintptr_t m_iSwapWindowOriginal; // Pointer to original swap window

namespace SDL2 {
  void hkSwapWindow(SDL_Window*);
  void SetupSwapWindow();
}
