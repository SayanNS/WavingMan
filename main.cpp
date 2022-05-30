#include "glad/glad.h"
#include "SDL2/SDL.h"
#include "Human.h"
#include "Renderer.h"
#include <iostream>

#define WINDOW_TITLE "Connective Games"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define FPS 60

int main(int argc, char *argv[])
{
	human::Human human;
	Uint32 oldTicks;

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_GLContext gl_context;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Could not initialize SDL video subsystem: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
			WINDOW_HEIGHT, SDL_WINDOW_OPENGL);

	if (window == nullptr) {
		std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
		goto quit;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		std::cerr << "Could not create SDL renderer: " << SDL_GetError() << std::endl;
		goto destroy_window;
	}

	gl_context = SDL_GL_CreateContext(window);

	if (gl_context == nullptr) {
		std::cerr << "Could not create SDL context: " << SDL_GetError() << std::endl;
		goto destroy_renderer;
	}

	if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
		std::cerr << "Failed to initialize the OpenGL context" << std::endl;
		goto delete_context;
	}

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (!init_shaders_and_vertexes()) {
		goto delete_context;
	}

	human.onWindowSizeChanged(WINDOW_WIDTH, WINDOW_HEIGHT);
	oldTicks = SDL_GetTicks();

	while (true) {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				goto delete_context;
			case SDL_KEYUP:
				SDL_KeyboardEvent *keyboardEvent = (SDL_KeyboardEvent *) &event;
				switch (keyboardEvent->keysym.sym) {
				case SDLK_l:
					human.waveLeftHand();
					break;
				case SDLK_r:
					human.waveRightHand();
					break;
				case SDLK_SPACE:
					human.takeStick();
					break;
				}
				break;
			}
		}

		Uint32 newTicks = SDL_GetTicks();
//		Uint32 delta = newTicks - oldTicks;

//		if (delta < 1000 / FPS) {
//			SDL_Delay(1000 / FPS - delta);
//			newTicks = SDL_GetTicks();
//		}

		human.update(newTicks - oldTicks);
		oldTicks = newTicks;

		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		human.draw();

		SDL_GL_SwapWindow(window);
	}

delete_context:
	SDL_GL_DeleteContext(gl_context);
destroy_renderer:
	SDL_DestroyRenderer(renderer);
destroy_window:
	SDL_DestroyWindow(window);
quit:
	SDL_Quit();

	return EXIT_SUCCESS;
}
