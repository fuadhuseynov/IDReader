#include "SwipeCmdPrompt.h"

SwipeCmdPrompt::SwipeCmdPrompt(
	bool aEnableLogging /*= true*/
) :
	prEnableLogging(aEnableLogging),
	prCanContinue(true)
{
	MMMReaderErrorCode lErrorCode = NO_ERROR_OCCURRED;
	prSwipePrettyPrinter = new SwipePrettyPrinter();

	// Set the error handler callback to report any errors as they occur
	MMMReader_SetErrorHandler(&SwipeCmdPrompt::StaticErrorCallback, this);

	// Enable logging, if requested
	if (prEnableLogging)
	{
		lErrorCode = MMMReader_InitialiseLogging(
			true,
			4,
			LOGMASK_ALL,
			_T("SwipeCmdPrompt.log")
		);
		prCanContinue = (lErrorCode == NO_ERROR_OCCURRED);
	}

	// Load the swipe settings
	if (prCanContinue)
	{
		memset(&poSwipeSettings, 0, sizeof(MMMSwipeSettings));
		lErrorCode = MMMReader_LL_LoadSwipeSettings(&poSwipeSettings);
		prCanContinue = (lErrorCode == NO_ERROR_OCCURRED);
	}
}

SwipeCmdPrompt::~SwipeCmdPrompt()
{
	MMMReader_ShutdownLogging();
	MMMReader_SwipeShutdown();
	delete prSwipePrettyPrinter;
}

bool SwipeCmdPrompt::Run()
{
	MMMReaderErrorCode lErrorCode = NO_ERROR_OCCURRED;

	if (prCanContinue)
	{
		// Initialise the Swipe Reader. Data and events will be sent back in
		// an asynchronous fashion through the callbacks provided.
		lErrorCode = MMMReader_SwipeInitialise(
			&poSwipeSettings,
			&SwipeCmdPrompt::StaticDataCallback,
			&SwipeCmdPrompt::StaticEventCallback,
			this
		);
		prCanContinue = (lErrorCode == NO_ERROR_OCCURRED);
	}

	return prCanContinue;
}

void SwipeCmdPrompt::StaticErrorCallback(
	MMMReaderErrorCode aErrorCode,
	TCHAR* aErrorMessage,
	void* aParam
)
{
	SwipeCmdPrompt* lCmdPrompt = (SwipeCmdPrompt*)aParam;
	lCmdPrompt->ProcessErrorCallback(aErrorCode, aErrorMessage);
}

void SwipeCmdPrompt::StaticEventCallback(
	void* aParam,
	MMMReaderEventCode aEventCode
)
{
	SwipeCmdPrompt* lCmdPrompt = (SwipeCmdPrompt*)aParam;
	lCmdPrompt->ProcessEventCallback(aEventCode);
}

void SwipeCmdPrompt::StaticDataCallback(
	void* aParam,
	int aSequenceNum,
	MMMReaderDataFormat aDataFormat,
	int aDataLength,
	void* aData
)
{
	SwipeCmdPrompt* lCmdPrompt = (SwipeCmdPrompt*)aParam;
	lCmdPrompt->ProcessDataCallback(aSequenceNum, aDataFormat, aDataLength, aData);
}

void SwipeCmdPrompt::ProcessEventCallback(
	MMMReaderEventCode aEventCode
)
{
	prSwipePrettyPrinter->PrintEvent(aEventCode);
}

void SwipeCmdPrompt::ProcessErrorCallback(
	MMMReaderErrorCode aErrorCode,
	TCHAR* aErrorMessage
)
{
	prSwipePrettyPrinter->PrintError(aErrorCode, aErrorMessage);
}

void SwipeCmdPrompt::ProcessDataCallback(
	int aSequenceNum,
	MMMReaderDataFormat aDataFormat,
	int aDataLength,
	void* aData
)
{
	// The sequence number provided maps to the MMMReaderSwipeItem enum.
	MMMReaderSwipeItem lSwipeItem = (MMMReaderSwipeItem)aSequenceNum;
	TCHAR* lDataItemName = prSwipePrettyPrinter->StringifySwipeItem(lSwipeItem);

	// Pretty print struct data
	if (aDataFormat == DF_STRUCT)
	{
		switch (lSwipeItem)
		{
			case SWIPE_OCR_CODELINE:
				prSwipePrettyPrinter->PrintCodelineData(
					lDataItemName, (MMMReaderCodelineData*)aData
				);
				break;
			case SWIPE_MSR_DATA:
				prSwipePrettyPrinter->PrintMsrData(
					lDataItemName, (MMMReaderMsrData*)aData
				);
				break;
			case SWIPE_ATB_DATA:
				prSwipePrettyPrinter->PrintSwipeATBData(
					lDataItemName, (MMMReaderAtbData*)aData
				);
				break;
			case SWIPE_RTE_QA_DATA:
				prSwipePrettyPrinter->PrintRteQAData(
					lDataItemName, (MMMReaderRTEQAData*)aData
				);
				break;
			case SWIPE_RTE_DATA:
				prSwipePrettyPrinter->PrintRteSwipeData(
					lDataItemName, (MMMReaderRTESwipeData*)aData
				);
				break;
			case SWIPE_MUSE_DATA:
				prSwipePrettyPrinter->PrintMuseSwipeData(
					lDataItemName, (MMMReaderMuseSwipeData*)aData
				);
				break;
			case SWIPE_CUTE_DATA:
				prSwipePrettyPrinter->PrintCuteSwipeData(
					lDataItemName, (MMMReaderCuteSwipeData*)aData
				);
				break;
			case SWIPE_TECS_DATA:
				prSwipePrettyPrinter->PrintTecsSwipeData(
					lDataItemName, (MMMReaderTecsSwipeData*)aData
				);
				break;
			case SWIPE_MAGMSR_DATA:
				prSwipePrettyPrinter->PrintMsrSwipeData(
					lDataItemName, (MMMReaderMagtekMsrSwipeData*)aData
				);
				break;
			case SWIPE_AAMVA_DATA:
				prSwipePrettyPrinter->PrintAAMVAData(
					lDataItemName, (MMMReaderAAMVAData*)aData
				);
				break;
			case SWIPE_BARCODE_PDF417:
				prSwipePrettyPrinter->PrintSwipeBarcodeData(
					lDataItemName, (MMMReaderSwipeBarcodeData*)aData
				);
				break;
			case SWIPE_BARCODE_1D_128:
				prSwipePrettyPrinter->PrintSwipeBarcodeData(
					lDataItemName, (MMMReaderSwipeBarcodeData*)aData
				);
				break;
			case SWIPE_BARCODE_1D_3_OF_9:
				prSwipePrettyPrinter->PrintSwipeBarcodeData(
					lDataItemName, (MMMReaderSwipeBarcodeData*)aData
				);
				break;
			default:
				prSwipePrettyPrinter->PrintData(
					lDataItemName, _T("<Unknown Struct Data>")
				);
		}
	}

	// Pretty print fundemental data items
	else
	{
		switch (aDataFormat)
		{
			case DF_INT:
				prSwipePrettyPrinter->PrintIntData(lDataItemName, *(int*)aData);
				break;
			case DF_BOOLEAN:
				prSwipePrettyPrinter->PrintBoolData(lDataItemName, *(bool*)aData);
				break;
			case DF_FLOAT:
				prSwipePrettyPrinter->PrintFloatData(lDataItemName, *(float*)aData);
				break;
			case DF_STRING_ASCII:
				prSwipePrettyPrinter->PrintASCIIData(lDataItemName, (char*)aData, aDataLength);
				break;
			case DF_BYTE:
				prSwipePrettyPrinter->PrintByteData(lDataItemName, *(MMMByte*)aData);
				break;
			case DF_BYTE_ARRAY:
				prSwipePrettyPrinter->PrintByteArrayData(lDataItemName, (MMMByte*)aData, aDataLength);
				break;
			default:
				prSwipePrettyPrinter->PrintData(
					lDataItemName, _T("<Unknown Data>")
				);
		}
	}

}
