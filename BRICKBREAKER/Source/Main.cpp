// handles everything
#include "Application.h"
// program entry point
int main()
{
	Application BRICKBREAKER;
	if (BRICKBREAKER.Init()) {
		if (BRICKBREAKER.Run()) {
			return BRICKBREAKER.Shutdown() ? 0 : 1;
		}
	}
	return 1;
}