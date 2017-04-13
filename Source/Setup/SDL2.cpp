// SDL2
#include "../Ares.h"

uintptr_t* m_piSwapWindowPtr; // Pointer to swap window
uintptr_t m_iSwapWindowOriginal; // Pointer to original swap window
SDL_GLContext sdlContext = nullptr;

void SDL2::hkSwapWindow(SDL_Window* sdlWindow) {

	static void(*oSDL_GL_SwapWindow)(SDL_Window*) = reinterpret_cast<void(*)(SDL_Window*)>(m_iSwapWindowOriginal);

	static SDL_GLContext sdlOriginalContext = SDL_GL_GetCurrentContext();

	if (!sdlContext) {

		sdlContext = SDL_GL_CreateContext(sdlWindow);
		ImGui_ImplSdl_Init(sdlWindow);

	}

	SDL_GL_MakeCurrent(sdlWindow, sdlContext);

	ImGui_ImplSdl_NewFrame(sdlWindow); // Start Rendering

	ImGui::Render(); // End Rendering

	SDL_GL_MakeCurrent(sdlWindow, sdlOriginalContext);
	oSDL_GL_SwapWindow(sdlWindow); /* When replacing a pointer to a function with our own
	we must make sure to call the original to ensure the original process runs
	smoothly. */

}

void SDL2::SetupSwapWindow() {

	uintptr_t m_iSwapWindowFn = reinterpret_cast<uintptr_t>(dlsym(RTLD_NEXT, "SDL_GL_SwapWindow"));
	m_piSwapWindowPtr = GetAbsoluteAddress<uintptr_t>(m_iSwapWindowFn, 3, 7);
	m_iSwapWindowOriginal = *m_piSwapWindowPtr;
	*m_piSwapWindowPtr = reinterpret_cast<uintptr_t>(&hkSwapWindow);

}
