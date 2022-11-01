#include "ege_pch.h"
#include "core/GameEngine.h"

int main(int argc, char* argv[]) {
	PROFILER_BEGIN();
	EGE::GameEngine game;
	game.run();
	PROFILER_END();

}
