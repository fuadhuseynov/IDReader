#ifndef PRETTY_PRINTER_H
#define PRETTY_PRINTER_H

#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>

#include <MMMReaderDataTypes.h>

class SwipePrettyPrinter
{
public:
	SwipePrettyPrinter();

	TCHAR* StringifySwipeItem(MMMReaderSwipeItem aSwipeItem);
	TCHAR* StringifyEventCode(MMMReaderEventCode aEventCode);
	TCHAR* StringifyRTEDeviceTypeName(RTEProtocolDeviceType aDeviceType);
	TCHAR* StringifyRTEMessageTypeName(RTEProtocolMessageType aMessageType);
	TCHAR* StringifyMagtekMsrCardType(MagtekMsrProtocolCardType aCardType);

	void PrintEvent(MMMReaderEventCode aEventCode);
	void PrintError(MMMReaderErrorCode aErrorCode, TCHAR* aErrorMessage);
	void PrintData(TCHAR* aItemStr, TCHAR* aDataStr);

	void PrintCodelineData(TCHAR* aItemStr, MMMReaderCodelineData* aData);
	void PrintMsrData(TCHAR* aItemStr, MMMReaderMsrData* aData);
	void PrintSwipeATBData(TCHAR* aItemStr, MMMReaderAtbData* aData);
	void PrintRteQAData(TCHAR* aItemStr, MMMReaderRTEQAData* aData);
	void PrintQAData(TCHAR* aItemStr, MMMReaderRTEQALineData* aLineData);
	void PrintRteSwipeData(TCHAR* aItemStr, MMMReaderRTESwipeData* aData);
	void PrintMuseSwipeData(TCHAR* aItemStr, MMMReaderMuseSwipeData* aData);
	void PrintCuteSwipeData(TCHAR* aItemStr, MMMReaderCuteSwipeData* aData);
	void PrintTecsSwipeData(TCHAR* aItemStr, MMMReaderTecsSwipeData* aData);
	void PrintMsrSwipeData(TCHAR* aItemStr, MMMReaderMagtekMsrSwipeData* aData);
	void PrintAAMVAData(TCHAR* aItemStr, MMMReaderAAMVAData* aData);
	void PrintSwipeBarcodeData(TCHAR* aItemStr, MMMReaderSwipeBarcodeData* aData);

	void PrintIntData(TCHAR* aItemStr, int aData);
	void PrintBoolData(TCHAR* aItemStr, bool aData);
	void PrintFloatData(TCHAR* aItemStr, float aData);
	void PrintASCIIData(TCHAR* aItemStr, char* aData, size_t aStringLength);
	void PrintByteData(RTCHAR* aItemStr, MMMByte aData);
	void PrintByteArrayData(TCHAR* aItemStr, MMMByte* aData, int aArrayLength);
	void PrintMMMDateData(TCHAR* aItemStr, MMMReaderDate aData);
};

#endif // PRETTY_PRINTER_H
