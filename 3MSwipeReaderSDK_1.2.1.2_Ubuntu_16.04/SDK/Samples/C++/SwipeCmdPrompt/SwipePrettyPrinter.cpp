#include "SwipePrettyPrinter.h"

SwipePrettyPrinter::SwipePrettyPrinter()
{
}

TCHAR* SwipePrettyPrinter::StringifySwipeItem(
	MMMReaderSwipeItem aSwipeItem
)
{
	#define SWIPE_DATA_ITEM(x) case x: lName = _T(#x); break;

	TCHAR* lName;
	switch (aSwipeItem)
	{
		SWIPE_DATA_ITEM(SWIPE_WHOLE_DATA)
		SWIPE_DATA_ITEM(SWIPE_MESSAGE_CONTENT)
		SWIPE_DATA_ITEM(SWIPE_OCR_CODELINE)
		SWIPE_DATA_ITEM(SWIPE_MSR_DATA)
		SWIPE_DATA_ITEM(SWIPE_BARCODE_PDF417)
		SWIPE_DATA_ITEM(SWIPE_BARCODE_1D_128)
		SWIPE_DATA_ITEM(SWIPE_BARCODE_1D_3_OF_9)
		SWIPE_DATA_ITEM(SWIPE_ATB_DATA)
		SWIPE_DATA_ITEM(SWIPE_RTE_QA_DATA)
		SWIPE_DATA_ITEM(SWIPE_RTE_DATA)
		SWIPE_DATA_ITEM(SWIPE_MUSE_DATA)
		SWIPE_DATA_ITEM(SWIPE_CUTE_DATA)
		SWIPE_DATA_ITEM(SWIPE_TECS_DATA)
		SWIPE_DATA_ITEM(SWIPE_MAGMSR_DATA)
		SWIPE_DATA_ITEM(SWIPE_AAMVA_DATA)
	default:
		lName = _T("UNKNOWN_SWIPE_ITEM");
	}

	return lName;

}

TCHAR* SwipePrettyPrinter::StringifyEventCode(
	MMMReaderEventCode aEventCode
)
{
	#define EVENT_CODE(x) case x: lName = _T(#x); break;

	TCHAR* lName;
	switch (aEventCode)
	{
		EVENT_CODE(DOC_ON_WINDOW)
		EVENT_CODE(DOC_REMOVED)
		EVENT_CODE(START_OF_DOCUMENT_DATA)
		EVENT_CODE(END_OF_DOCUMENT_DATA)
		EVENT_CODE(RF_CHIP_OPENED_SUCCESSFULLY)
		EVENT_CODE(RF_APPLICATION_OPENED_SUCCESSFULLY)
		EVENT_CODE(RF_CHIP_OPEN_FAILED)
		EVENT_CODE(READER_ERROR_RESOLVED)
		EVENT_CODE(SETTINGS_INITIALISED)
		EVENT_CODE(PLUGINS_INITIALISED)
		EVENT_CODE(START_OF_PLUGINS_DECODE)
		EVENT_CODE(RF_CHIP_OPEN_TIMEOUT)
		EVENT_CODE(RF_CHIP_REMOVAL_SUCCESS)
		EVENT_CODE(RF_CHIP_REMOVAL_TIMEOUT)
		EVENT_CODE(READY_FOR_SMARTCARD)
		EVENT_CODE(BEGIN_RESOLVING_ERROR)
		EVENT_CODE(COM_PORT_OPEN)
		EVENT_CODE(COM_PORT_CLOSED)
		EVENT_CODE(READING_DATA)
		EVENT_CODE(DATA_READ)
		EVENT_CODE(START_OF_SWIPE_DATA)
		EVENT_CODE(END_OF_SWIPE_DATA)
		EVENT_CODE(SWIPE_READER_CONNECTED)
		EVENT_CODE(SWIPE_READER_DISCONNECTED)
		EVENT_CODE(READER_STATE_CHANGED)
		EVENT_CODE(UHF_READ_TIMEOUT)
		EVENT_CODE(UHF_READ_COMPLETE)
		EVENT_CODE(DOC_FEED_COMPLETE)
		EVENT_CODE(DOC_FEED_FAILED)
		EVENT_CODE(DIRT_DETECTED_ON_SCANNER_WINDOW)
	default:
		lName = "UNKNOWN_EVENT_CODE";
	}

	return lName;
}

TCHAR* SwipePrettyPrinter::StringifyRTEDeviceTypeName(
	RTEProtocolDeviceType aDeviceType
)
{
	#define RTE_DEVICE_ITEM(x) case   x: lName = _T(#x); break;

	TCHAR* lName;
	switch (aDeviceType)
	{
		RTE_DEVICE_ITEM(RTE_DT_DEVICE)
		RTE_DEVICE_ITEM(RTE_DT_ATB)
		RTE_DEVICE_ITEM(RTE_DT_MSR)
		RTE_DEVICE_ITEM(RTE_DT_OCR)
		RTE_DEVICE_ITEM(RTE_DT_SERIAL)
		RTE_DEVICE_ITEM(RTE_DT_SMARTCARD)
		RTE_DEVICE_ITEM(RTE_DT_RESERVED)

	default:
		lName = _T("UNKNOWN_RTE_DEVICE_TYPE");
		break;
	}

	return lName;
}

TCHAR* SwipePrettyPrinter::StringifyRTEMessageTypeName(
	RTEProtocolMessageType aMessageType
)
{
	#define RTE_MESSAGE_ITEM(x) case x: lName = _T(#x); break;

	TCHAR* lName;
	switch (aMessageType)
	{
		RTE_MESSAGE_ITEM(RTE_MT_COMMAND)
		RTE_MESSAGE_ITEM(RTE_MT_DATA)
		RTE_MESSAGE_ITEM(RTE_MT_UNSOLICITED_DATA)
		RTE_MESSAGE_ITEM(RTE_MT_ERROR_RESPONSE)

	default:
		lName = _T("UNKNOWN_RTE_MESSAGE_TYPE");
		break;
	}

	return lName;
}

TCHAR* SwipePrettyPrinter::StringifyMagtekMsrCardType(
	MagtekMsrProtocolCardType aCardType
)
{
	#define MAGTEK_CARD_TYPE(x) case x: lName = _T(#x); break;

	TCHAR* lName;
	switch (aCardType)
	{
		MAGTEK_CARD_TYPE(MAGMSR_CT_ISO_ABA)
		MAGTEK_CARD_TYPE(MAGMSR_CT_AAMVA)
		MAGTEK_CARD_TYPE(MAGMSR_CT_CADL)
		MAGTEK_CARD_TYPE(MAGMSR_CT_BLANK)
		MAGTEK_CARD_TYPE(MAGMSR_CT_OTHER)
		MAGTEK_CARD_TYPE(MAGMSR_CT_UNDETERMINED)
		MAGTEK_CARD_TYPE(MAGMSR_CT_NONE)
		MAGTEK_CARD_TYPE(MAGMSR_CT_JIS_TYPE_2)

		default:
			lName = _T("UNKNOWN_MAGMSR_CARD_TYPE");
			break;
	}

	return lName;
}

void SwipePrettyPrinter::PrintEvent(
	MMMReaderEventCode aEventCode
)
{
	_tprintf("EVENT:    %s\n", this->StringifyEventCode(aEventCode));
}

void SwipePrettyPrinter::PrintError(
	MMMReaderErrorCode aErrorCode,
	TCHAR* aErrorMessage
)
{
	_tprintf("ERROR:    %s\n", aErrorMessage);
}

void SwipePrettyPrinter::PrintData(
	TCHAR* aItemStr,
	TCHAR* aDataStr
)
{
	_tprintf("DATA :    %s: %s\n", aItemStr, aDataStr);
}

void SwipePrettyPrinter::PrintCodelineData(
	TCHAR* aItemStr,
	MMMReaderCodelineData* aData
)
{
	PrintASCIIData(		aItemStr,					aData->Data,			sizeof(aData->Data));
	PrintASCIIData(		_T("OCR_LINE_1"),			aData->Line1,			sizeof(aData->Line1));
	PrintASCIIData(		_T("OCR_LINE_2"),			aData->Line2,			sizeof(aData->Line2));
	PrintASCIIData(		_T("OCR_LINE_3"),			aData->Line3,			sizeof(aData->Line3));
	PrintASCIIData(		_T("OCR_DOC_ID"),			aData->DocId,			sizeof(aData->DocId));
	PrintASCIIData(		_T("OCR_DOC_TYPE"),			aData->DocType,			sizeof(aData->DocType));
	PrintASCIIData(		_T("OCR_SURNAME"),			aData->Surname,			sizeof(aData->Surname));
	PrintASCIIData(		_T("OCR_FORENAME"),			aData->Forename,		sizeof(aData->Forename));
	PrintASCIIData(		_T("OCR_SECOND_NAME"),		aData->SecondName,		sizeof(aData->SecondName));
	PrintASCIIData(		_T("OCR_FORENAMES"),		aData->Forenames,		sizeof(aData->Forenames));
	PrintMMMDateData(	_T("OCR_DATE_OF_BIRTH"),	aData->DateOfBirth);
	PrintMMMDateData(	_T("OCR_EXPIRY_DATE"),		aData->ExpiryDate);
	PrintASCIIData(		_T("OCR_ISSUING_STATE"),	aData->IssuingState,	sizeof(aData->IssuingState));
	PrintASCIIData(		_T("OCR_NATIONALITY"),		aData->Nationality,		sizeof(aData->Nationality));
	PrintASCIIData(		_T("OCR_DOC_NUMBER"),		aData->DocNumber,		sizeof(aData->DocNumber));
	PrintASCIIData(		_T("OCR_SEX"),				aData->Sex,				sizeof(aData->Sex));
	PrintASCIIData(		_T("OCR_OPTIONAL_DATA1"),	aData->OptionalData1,	sizeof(aData->OptionalData1));
	PrintASCIIData(		_T("OCR_OPTIONAL_DATA2"),	aData->OptionalData2,	sizeof(aData->OptionalData2));
}

void SwipePrettyPrinter::PrintMsrData(
	TCHAR* aItemStr,
	MMMReaderMsrData* aData
)
{
	PrintData(		aItemStr,			_T(""));
	PrintASCIIData(	_T("MSR_TRACK_1"),	aData->Track1,	sizeof(aData->Track1));
	PrintASCIIData(	_T("MSR_TRACK_2"),	aData->Track2,	sizeof(aData->Track2));
	PrintASCIIData(	_T("MSR_TRACK_3"),	aData->Track3,	sizeof(aData->Track3));
}

void SwipePrettyPrinter::PrintSwipeATBData(
	TCHAR* aItemStr,
	MMMReaderAtbData* aData
)
{
	PrintData(		aItemStr,					_T(""));
	PrintASCIIData(	_T("ATB_TRACK_1_BLOCK_1"),	aData->Track1.Block1,	sizeof(aData->Track1.Block1));
	PrintASCIIData(	_T("ATB_TRACK_1_BLOCK_2"),	aData->Track1.Block2,	sizeof(aData->Track1.Block2));
	PrintASCIIData(	_T("ATB_TRACK_1_BLOCK_3"),	aData->Track1.Block3,	sizeof(aData->Track1.Block3));
	PrintASCIIData(	_T("ATB_TRACK_2_BLOCK_1"),	aData->Track2.Block1,	sizeof(aData->Track2.Block1));
	PrintASCIIData(	_T("ATB_TRACK_2_BLOCK_2"),	aData->Track2.Block2,	sizeof(aData->Track2.Block2));
	PrintASCIIData(	_T("ATB_TRACK_2_BLOCK_3"),	aData->Track2.Block3,	sizeof(aData->Track2.Block3));
	PrintASCIIData(	_T("ATB_TRACK_3_BLOCK_1"),	aData->Track3.Block1,	sizeof(aData->Track3.Block1));
	PrintASCIIData(	_T("ATB_TRACK_3_BLOCK_2"),	aData->Track3.Block2,	sizeof(aData->Track3.Block2));
	PrintASCIIData(	_T("ATB_TRACK_3_BLOCK_3"),	aData->Track3.Block3,	sizeof(aData->Track3.Block3));
	PrintASCIIData(	_T("ATB_TRACK_4_BLOCK_1"),	aData->Track4.Block1,	sizeof(aData->Track4.Block1));
	PrintASCIIData(	_T("ATB_TRACK_4_BLOCK_2"),	aData->Track4.Block2,	sizeof(aData->Track4.Block2));
	PrintASCIIData(	_T("ATB_TRACK_4_BLOCK_3"),	aData->Track4.Block3,	sizeof(aData->Track4.Block3));
}

void SwipePrettyPrinter::PrintRteQAData(
	TCHAR* aItemStr,
	MMMReaderRTEQAData* aData
)
{
	PrintData(		aItemStr,						_T(""));
	PrintIntData(	_T("QA_CODELINE_COUNT"),		aData->CodelineCount);
	PrintBoolData(	_T("QA_CLEAR_AREA_PRESENT"),	(bool)aData->ClearAreaPresent);
	PrintIntData(	_T("QA_CODELINE_COUNT"),		aData->SpotCount);
	PrintQAData(	_T("LINE_1"),					&aData->Line1);
	PrintQAData(	_T("LINE_2"),					&aData->Line2);
	PrintQAData(	_T("LINE_3"),					&aData->Line3);
}

void SwipePrettyPrinter::PrintQAData(
	TCHAR* aItemStr,
	MMMReaderRTEQALineData* aLineData
)
{
	if (aLineData->HasData)
	{
		TCHAR lName[101];

		memset(lName, 0, sizeof(TCHAR) * (100 + 1));
		_sntprintf(lName, 100, _T("%s_QA_CHAR_COUNT"), aItemStr);
		PrintIntData(lName, aLineData->CharCount);

		memset(lName, 0, sizeof(TCHAR) * (100 + 1));
		_sntprintf(lName, 100, _T("%s_QA_LOWER_LINE_BOUNDARY"), aItemStr);
		PrintFloatData(lName, aLineData->LowerLineBoundary);

		memset(lName, 0, sizeof(TCHAR) * (100 + 1));
		_sntprintf(lName, 100, _T("%s_QA_UPPER_LINE_BOUNDARY"), aItemStr);
		PrintFloatData(lName, aLineData->UpperLineBoundary);

		memset(lName, 0, sizeof(TCHAR) * (100 + 1));
		_sntprintf(lName, 100, _T("%s_QA_RECOGNISED_COUNT"), aItemStr);
		PrintIntData(lName, aLineData->RecognisedCount);

		memset(lName, 0, sizeof(TCHAR) * (100 + 1));
		_sntprintf(lName, 100, _T("%s_QA_AVERAGE_STROKE_WIDTH"), aItemStr);
		PrintFloatData(lName, aLineData->AverageStrokeWidth);

		memset(lName, 0, sizeof(TCHAR) * (100 + 1));
		_sntprintf(lName, 100, _T("%s_QA_THINNEST_STROKE_WIDTH"), aItemStr);
		PrintFloatData(lName, aLineData->ThinnestStrokeWidth);

		memset(lName, 0, sizeof(TCHAR) * (100 + 1));
		_sntprintf(lName, 100, _T("%s_QA_THICKEST_STROKE_WIDTH"), aItemStr);
		PrintFloatData(lName, aLineData->ThickestStrokeWidth);

		memset(lName, 0, sizeof(TCHAR) * (100 + 1));
		_sntprintf(lName, 100, _T("%s_QA_NON_CONTINUOUS_COUNT"), aItemStr);
		PrintIntData(lName,aLineData->NonContinuousCount);
	}
}

void SwipePrettyPrinter::PrintRteSwipeData(
	TCHAR* aItemStr,
	MMMReaderRTESwipeData* aData
)
{
	TCHAR lOCRFlagByte[2];
	memset(lOCRFlagByte, 0, sizeof(TCHAR) * 2);
	_sntprintf(lOCRFlagByte, 1, "%c", aData->OCRFlagByte);

	TCHAR* lDeviceName = StringifyRTEDeviceTypeName(aData->DeviceType);
	TCHAR* lMessageType = StringifyRTEMessageTypeName(aData->MessageType);

	int lDeviceTypeBufferSize = strlen(lDeviceName) + 5;
	TCHAR* lDeviceTypeBuffer = new TCHAR[lDeviceTypeBufferSize + 1];
	memset(lDeviceTypeBuffer, 0, sizeof(lDeviceTypeBuffer));

	_sntprintf(
		lDeviceTypeBuffer, lDeviceTypeBufferSize, "%c - %s",
		aData->DeviceType,
		lDeviceName
	);

	int lMessageTypeBufferSize = strlen(lMessageType) + 5;
	TCHAR* lMessageTypeBuffer = new TCHAR[lMessageTypeBufferSize + 1];
	memset(lMessageTypeBuffer, 0, sizeof(lMessageTypeBuffer));

	_sntprintf(
		lMessageTypeBuffer,lMessageTypeBufferSize, "%c - %s",
		aData->MessageType,
		lMessageType
	);

	PrintData(aItemStr, _T(""));
	PrintData(_T("RTE_DEVICE_TYPE"), lDeviceTypeBuffer);
	PrintData(_T("RTE_MESSAGE_TYPE"), lMessageTypeBuffer);
	PrintIntData(_T("RTE_BCC"), aData->BCC);
	PrintData(_T("RTE_OCR_FLAG_BYTE"), lOCRFlagByte);

	delete [] lDeviceTypeBuffer;
	delete [] lMessageTypeBuffer;
}

void SwipePrettyPrinter::PrintMuseSwipeData(
	TCHAR* aItemStr,
	MMMReaderMuseSwipeData* aData
)
{
	PrintData(aItemStr, _T(""));
	PrintIntData(_T("MUSE_DEVICE_TYPE"), (int)aData->DeviceType);
	PrintIntData(_T("MUSE_CRC_HIGH"), (int)aData->CrcHigh);
	PrintIntData(_T("MUSE_CRC_LOW"), (int)aData->CrcLow);
}

void SwipePrettyPrinter::PrintCuteSwipeData(
	TCHAR* aItemStr,
	MMMReaderCuteSwipeData* aData
)
{
	PrintData(aItemStr, _T(""));
	PrintIntData(_T("CUTE_DEVICE_TYPE"), (int)aData->DeviceType);
}

void SwipePrettyPrinter::PrintTecsSwipeData(
	TCHAR* aItemStr,
	MMMReaderTecsSwipeData* aData
)
{
	PrintData(aItemStr, _T(""));
	PrintIntData(_T("TECS_DEVICE_TYPE"), (int)aData->DeviceType);
}
void SwipePrettyPrinter::PrintMsrSwipeData(
	TCHAR* aItemStr,
	MMMReaderMagtekMsrSwipeData* aData
)
{
	PrintData(aItemStr, _T(""));

	PrintData(_T("MAGTEK_MSR_CARD_TYPE"), StringifyMagtekMsrCardType(aData->CardEncodeType));
}

void SwipePrettyPrinter::PrintAAMVAData(
	TCHAR* aItemStr,
	MMMReaderAAMVAData* aData
)
{
	PrintData(		aItemStr,							_T(""));
	PrintASCIIData(	_T("AAMVA_FULLNAME"),				aData->Parsed.FullName,				sizeof(aData->Parsed.FullName));
	PrintASCIIData(	_T("AAMVA_FORENAME"),				aData->Parsed.Forename,				sizeof(aData->Parsed.Forename));
	PrintASCIIData(	_T("AAMVA_SURNAME"),				aData->Parsed.Surname,				sizeof(aData->Parsed.Surname));
	PrintASCIIData(	_T("AAMVA_LICENCE_NUMBER"),			aData->Parsed.LicenceNumber,		sizeof(aData->Parsed.LicenceNumber));
	PrintASCIIData(	_T("AAMVA_ADDRESS_STREET"),			aData->Parsed.AddressStreet,		sizeof(aData->Parsed.AddressStreet));
	PrintASCIIData(	_T("AAMVA_ADDRESS_CITY"),			aData->Parsed.AddressCity,			sizeof(aData->Parsed.AddressCity));
	PrintASCIIData(	_T("AAMVA_ADDRESS_POSTALCODE"),		aData->Parsed.AddressPostalCode,	sizeof(aData->Parsed.AddressPostalCode));
	PrintASCIIData(	_T("AAMVA_ADDRESS_STATE"),			aData->Parsed.AddressState,			sizeof(aData->Parsed.AddressState));
	PrintASCIIData(	_T("AAMVA_ADDRESS_COUNTRY"),		aData->Parsed.AddressCountry,		sizeof(aData->Parsed.AddressCountry));
}

void SwipePrettyPrinter::PrintSwipeBarcodeData(
	TCHAR* aItemStr,
	MMMReaderSwipeBarcodeData* aData
)
{
	PrintASCIIData(aItemStr, aData->DataField, sizeof(aData->DataField));
}

void SwipePrettyPrinter::PrintIntData(
	TCHAR* aItemStr,
	int aData
)
{
	TCHAR lBuffer[15];
	memset(lBuffer, 0, 15 * sizeof(TCHAR));
	_sntprintf(lBuffer, 14, "%d", aData);

	PrintData(aItemStr, lBuffer);
}

void SwipePrettyPrinter::PrintBoolData(
	TCHAR* aItemStr,
	bool aData
)
{
	TCHAR* lValue;
	if (aData)
		lValue = _T("TRUE");
	else
		lValue = _T("FALSE");

	PrintData(aItemStr, lValue);
}

void SwipePrettyPrinter::PrintFloatData(
	TCHAR* aItemStr,
	float aData
)
{
	TCHAR* lBuffer = new TCHAR[15];

	memset(lBuffer, 0, sizeof(lBuffer));
	_sntprintf(lBuffer, 14, "%11.3f", aData);
	PrintData(aItemStr, lBuffer);

	delete [] lBuffer;
}

void SwipePrettyPrinter::PrintASCIIData(
	TCHAR* aItemStr,
	char* aData,
	size_t aStringLength
)
{
	TCHAR* lBuffer = new TCHAR[aStringLength + 1];

	_sntprintf(lBuffer, aStringLength, "%s", aData);
	lBuffer[aStringLength] = 0x00;

	for (int x = 0; x < aStringLength; x++)
	{
		if (lBuffer[x] == '\r')
			lBuffer[x] = ' ';
	}

	PrintData(aItemStr, lBuffer);

	delete [] lBuffer;
}

void SwipePrettyPrinter::PrintByteData(
	TCHAR* aItemStr,
	MMMByte aData
)
{
	TCHAR* lBuffer = new TCHAR[5];

	memset(lBuffer, 0, 5 * sizeof(TCHAR));
	_sntprintf(lBuffer, 4, "%X", aData);
	PrintData(aItemStr, lBuffer);

	delete [] lBuffer;
}

void SwipePrettyPrinter::PrintByteArrayData(
	TCHAR* aItemStr,
	MMMByte* aData,
	int aArrayLength
)
{
	TCHAR* lByteArrayStr = (TCHAR*)malloc(sizeof(TCHAR) * aArrayLength * 6);
	memset(lByteArrayStr, 0, aArrayLength * 6 * sizeof(TCHAR));

	int lLength = 0;
	for (int x = 0; x < aArrayLength; x++)
	{
		TCHAR* lByteStr = (TCHAR*)malloc(sizeof(TCHAR) * 7);
		memset(lByteStr, 0, sizeof(TCHAR) * 7);
		_sntprintf(lByteStr, 6, _T("(%X)"), (unsigned short)aData[x]);

		size_t lByteLen = _tcslen(lByteStr);
		memcpy(lByteArrayStr + lLength, lByteStr, lByteLen);
		lLength += lByteLen;
		free(lByteStr);
	}

	PrintData(aItemStr, lByteArrayStr);

	free(lByteArrayStr);
}

void SwipePrettyPrinter::PrintMMMDateData(
	TCHAR* aItemStr,
	MMMReaderDate aData
)
{
	TCHAR lDay[3], lMonth[3], lYear[3];
	memset(lDay, 0, 3);
	memset(lMonth, 0, 3);
	memset(lYear, 0, 3);

	TCHAR* lDateStr = new TCHAR[10];
	memset(lDateStr, 0, sizeof(lDateStr));

	if (
		aData.Day != -1 ||
		aData.Month != -1 ||
		aData.Year != -1
	)
	{
		if (aData.Day == -1)
			_stprintf(lDay, _T("??"));
		else
			_stprintf(lDay, "%02d", aData.Day);
		if (aData.Month == -1)
			_stprintf(lMonth, _T("??"));
		else
			_stprintf(lMonth, _T("%02d"), aData.Month);
		if (aData.Year == -1)
			_stprintf(lYear, _T("??"));
		else
			_stprintf(lYear, _T("%02d"), aData.Year);

		_stprintf(lDateStr, _T("%s-%s-%s"), lDay, lMonth, lYear);
	}

	PrintData(aItemStr, lDateStr);

	delete [] lDateStr;
}
