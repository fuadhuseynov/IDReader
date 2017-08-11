#ifndef SWIPE_CMD_PROMPT_H
#define SWIPE_CMD_PROMPT_H

#ifndef __linux__
#include <windows.h>
#endif
#include <tchar.h>
#include <list>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>

#include <MMMReaderLowLevelAPI.h>
#include <MMMReaderDataTypes.h>

#include "SwipePrettyPrinter.h"

class SwipeCmdPrompt
{
public:
	SwipeCmdPrompt(bool aEnableLogging = true);
	~SwipeCmdPrompt();

	bool Run();

private:
	bool prEnableLogging;
	bool prCanContinue;
	MMMSwipeSettings poSwipeSettings;
	SwipePrettyPrinter* prSwipePrettyPrinter;

	static void StaticErrorCallback(MMMReaderErrorCode aErrorCode, TCHAR* aErrorMessage, void* aParam);
	static void StaticDataCallback(void* aParam, int aSequenceNum, MMMReaderDataFormat aDataFormat, int aDataLength, void* aData);
	static void StaticEventCallback(void* aParam, MMMReaderEventCode aEventCode);

	void ProcessErrorCallback(MMMReaderErrorCode aErrorCode, TCHAR* aErrorMessage);
	void ProcessDataCallback(int aSequenceNum, MMMReaderDataFormat aDataFormat, int aDataLength, void* aData);
	void ProcessEventCallback(MMMReaderEventCode aEventCode);
};

#endif
