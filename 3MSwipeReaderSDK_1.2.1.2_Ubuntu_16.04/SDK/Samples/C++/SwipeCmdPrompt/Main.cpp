#include "SwipeCmdPrompt.h"

int main(int argc, char **argv)
{
	printf("== 3M Swipe Reader Command Prompt Example == \n");

	SwipeCmdPrompt* lSwipeCmdPrompt = new SwipeCmdPrompt();
	
	if (lSwipeCmdPrompt->Run())
	{
		printf("Press any key to close the application\n\n");
		getchar();
		printf("Shutting down\n");
	}

	delete lSwipeCmdPrompt;

	return 0;
}
