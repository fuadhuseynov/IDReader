package com.mmm.readers.Swipe.samples.SwipeMessages;

import com.mmm.readers.CodelineData;
import com.mmm.readers.DataFormat;
import com.mmm.readers.ErrorCode;
import com.mmm.readers.FullPage.EventCode;
import com.mmm.readers.modules.Swipe.AtbData;
import com.mmm.readers.modules.Swipe.RTEQAData;
import com.mmm.readers.modules.Swipe.RTEQALineData;
import com.mmm.readers.modules.Swipe.SwipeItem;

/**
 * Created by Fuad on 8/8/17.
 */
public class Reader implements com.mmm.readers.ErrorHandler,
        com.mmm.readers.modules.Swipe.DataHandler, com.mmm.readers.FullPage.EventHandler {

    boolean swipeDone;

    public Reader() {
        swipeDone = false;
        initialise();
        //Wait until the user swipes the ID
        while (!swipeDone) {}
    }

    //Initialise the libraries, check the device
    private void initialise() {
        try {
            com.mmm.readers.modules.Reader.SetErrorHandler(this);
            ErrorCode lResult = com.mmm.readers.modules.Reader.InitialiseLogging(true, 5, -1, "SwipeMessagesJava.log");
            if (lResult == ErrorCode.NO_ERROR_OCCURRED) {
                lResult = com.mmm.readers.modules.Swipe.Reader.Initialise(this, this);
            }
            if (lResult == ErrorCode.NO_ERROR_OCCURRED) {
                System.out.println("Swipe Reader initialised");
            } else {
                System.out.println("FAILED TO INITIALISE! - " + lResult.toString());
            }
            if (lResult == ErrorCode.NO_ERROR_OCCURRED) {
                com.mmm.readers.modules.Swipe.DataToSend lDataToSend = new com.mmm.readers.modules.Swipe.DataToSend();
                lResult = com.mmm.readers.modules.Swipe.Reader.GetDataToSend(lDataToSend);
                if (lResult == ErrorCode.NO_ERROR_OCCURRED) {
                    System.out.println("Successfully read optional data to send. AAMVA data =" + lDataToSend.puAAMVA);
                } else {
                    System.out.println("Failed to read DataToSend - " + lResult.toString());
                }
            }
        } catch (Throwable ex) {
            System.out.println("Unable to initialise " + ex.toString());
        }
    }

    //Shut down the device
    private void shutDown() {
        System.out.println("Shutting down Swipe Reader...");
        com.mmm.readers.modules.Swipe.Reader.Shutdown();
        com.mmm.readers.modules.Reader.ShutdownLogging();
        System.out.println("Swipe Reader shut down");
    }

    @Override
    public void OnMMMReaderError(ErrorCode aErrorCode, String aErrorMsg) {
        System.out.println("Error: " + aErrorCode.toString() + " - " + aErrorMsg);
    }

    @Override
    public void OnFullPageReaderEvent(EventCode aEventType) {
        System.out.println("Event: " + aEventType.toString());
    }

    @Override
    public void OnSwipeReaderData(SwipeItem aDataItem, DataFormat dataFormat, int aDataLen, byte[] aDataPtr) {
        switch (dataFormat) {
            case INT:
                int lValue = com.mmm.readers.interop.Marshal.toInt(aDataPtr);
                System.out.println("Data: " + aDataItem.toString() + " = " + lValue);
                break;

            case BOOLEAN:
                boolean blValue = com.mmm.readers.interop.Marshal.toBoolean(aDataPtr);
                System.out.println("Data: " + aDataItem.toString() + " = " + blValue);
                break;

            case FLOAT:
                float flValue = com.mmm.readers.interop.Marshal.toFloat(aDataPtr);
                System.out.println("Data: " + aDataItem.toString() + " = " + flValue);
                break;

            case STRING_ASCII:
                String lString = com.mmm.readers.interop.Marshal.toNewString(aDataPtr, aDataLen);
                System.out.println("Data: " + aDataItem.toString() + " = " + lString);
                break;

            case BYTE:
                byte btlValue = com.mmm.readers.interop.Marshal.toByte(aDataPtr);
                System.out.println("Data: " + aDataItem.toString() + " = " + btlValue);
                break;

            case BYTE_ARRAY:
                StringBuffer balString = new StringBuffer();
                for (int loop = 0; loop < aDataLen; loop++) {
                    balString.append(Integer.toHexString(aDataPtr[loop]));
                    balString.append(" ");
                }
                System.out.println("Data: " + aDataItem.toString() + " = " + balString);
                break;

            case STRUCT:
                DisplayStructData(aDataItem, aDataLen, aDataPtr);
                swipeDone = true;
                shutDown();
        }
    }

    private void DisplayStructData(SwipeItem aDataItem, int aDataLen, byte[] aDataPtr) {
        switch (aDataItem) {
            case OCR_CODELINE:
                CodelineData lCodeline = com.mmm.readers.modules.Swipe.Reader.ConstructCodelineData(aDataPtr);

                System.out.println("Data: " + aDataItem.toString() + " = " + lCodeline.Data);
                System.out.println("OCR Line 1 = " + lCodeline.Line1);
                System.out.println("OCR Line 2 = " + lCodeline.Line2);
                System.out.println("OCR Line 3 = " + lCodeline.Line3);
                System.out.println("OCR Doc ID = " + lCodeline.DocId);
                System.out.println("OCR Doc Type = " + lCodeline.DocType);
                System.out.println("OCR Surname = " + lCodeline.Surname);
                System.out.println("OCR Forename = " + lCodeline.Forename);
                System.out.println("OCR Second Name = " + lCodeline.SecondName);
                System.out.println("OCR Forenames = " + lCodeline.Forenames);
                System.out.println("OCR Date of Birth = " + lCodeline.DateOfBirth.Day + "-" + lCodeline.DateOfBirth.Month + "-"
                        + lCodeline.DateOfBirth.Year);
                System.out.println("OCR Expiry Date = " + lCodeline.ExpiryDate.Day + "-" + lCodeline.ExpiryDate.Month + "-"
                        + lCodeline.ExpiryDate.Year);
                System.out.println("OCR Issuing State = " + lCodeline.IssuingState);
                System.out.println("OCR Nationality = " + lCodeline.Nationality);
                System.out.println("OCR DocNumber = " + lCodeline.DocNumber);
                System.out.println("OCR Sex = " + lCodeline.Sex);
                System.out.println("OCR Short Sex = " + lCodeline.ShortSex);
                System.out.println("OCR OptionalData1 = " + lCodeline.OptionalData1);
                System.out.println("OCR OptionalData2 = " + lCodeline.OptionalData2);
                System.out.println("OCR CodelineValidationResult = " + lCodeline.CodelineValidationResult);
                break;

            case MSR_DATA:
                com.mmm.readers.modules.Swipe.MsrData lData = com.mmm.readers.modules.Swipe.Reader
                        .ConstructMsrData(aDataPtr);

                System.out.println("MSR Track 1 = " + lData.Track1);
                System.out.println("MSR Track 2 = " + lData.Track2);
                System.out.println("MSR Track 3 = " + lData.Track3);
                break;

            case SWIPE_BARCODE_PDF417:
                com.mmm.readers.modules.Swipe.SwipeBarcodePDF417Data lData1 = com.mmm.readers.modules.Swipe.Reader
                        .ConstructSwipeBarcodePDF417Data(aDataPtr);

                System.out.println("PDF417 data = " + lData1.DataField);
                break;

            case SWIPE_BARCODE_1D_128:
                com.mmm.readers.modules.Swipe.SwipeBarcodeCode128Data lData2 = com.mmm.readers.modules.Swipe.Reader
                        .ConstructSwipeBarcodeCode128Data(aDataPtr);

                System.out.println("Code128 data = " + lData2.DataField);
                break;

            case SWIPE_BARCODE_1D_3_OF_9:
                com.mmm.readers.modules.Swipe.SwipeBarcodeCode39Data lData3 = com.mmm.readers.modules.Swipe.Reader
                        .ConstructSwipeBarcodeCode39Data(aDataPtr);

                System.out.println("Code39 data = " + lData3.DataField);
                break;

            case ATB_DATA:
                AtbData lData4 = com.mmm.readers.modules.Swipe.Reader.ConstructAtbData(aDataPtr);

                System.out.println("ATB Track 1 Block 1 = " + lData4.Track1.Block1);
                System.out.println("ATB Track 1 Block 2 = " + lData4.Track1.Block2);
                System.out.println("ATB Track 1 Block 3 = " + lData4.Track1.Block3);

                System.out.println("ATB Track 2 Block 1 = " + lData4.Track2.Block1);
                System.out.println("ATB Track 2 Block 2 = " + lData4.Track2.Block2);
                System.out.println("ATB Track 2 Block 3 = " + lData4.Track2.Block3);

                System.out.println("ATB Track 3 Block 1 = " + lData4.Track3.Block1);
                System.out.println("ATB Track 3 Block 2 = " + lData4.Track3.Block2);
                System.out.println("ATB Track 3 Block 3 = " + lData4.Track3.Block3);

                System.out.println("ATB Track 4 Block 1 = " + lData4.Track4.Block1);
                System.out.println("ATB Track 4 Block 2 = " + lData4.Track4.Block2);
                System.out.println("ATB Track 4 Block 3 = " + lData4.Track4.Block3);
                break;

            case RTE_QA_DATA:
                RTEQAData lData5 = com.mmm.readers.modules.Swipe.Reader.ConstructRTEQAData(aDataPtr);

                System.out.println("QA Codeline Count = " + lData5.CodelineCount);
                System.out.println("QA Column Count = " + lData5.ColumnCount);
                System.out.println("QA Clear Area Present = " + lData5.ClearAreaPresent);
                System.out.println("QA Spot Count = " + lData5.SpotCount);

                DisplayQALineData(1, lData5.Line1);
                DisplayQALineData(2, lData5.Line2);
                DisplayQALineData(3, lData5.Line3);
                break;

            case AAMVA_DATA:
                com.mmm.readers.AAMVAData lAAMVAData = com.mmm.readers.interop.Marshal.ConstructAAMVAData(aDataPtr);

                System.out.println("AAMVA Full Name: " + lAAMVAData.Parsed.FullName);
                System.out.println("AAMVA Licence Number: " + lAAMVAData.Parsed.LicenceNumber);
                break;
        }
    }

    private void DisplayQALineData(int aLine, RTEQALineData aData) {
        if (aData.HasData) {
            System.out.println("Line " + aLine + " - QA Char Count = " + aData.CharCount);
            System.out.println("Line " + aLine + " - QA Lower Line Boundary = " + aData.LowerLineBoundary);
            System.out.println("Line " + aLine + " - QA Upper Line Boundary = " + aData.UpperLineBoundary);
            System.out.println("Line " + aLine + " - QA Recognised Count = " + aData.RecognisedCount);
            System.out.println("Line " + aLine + " - QA Average Stroke Width = " + aData.AverageStrokeWidth);
            System.out.println("Line " + aLine + " - QA Thinnest Stroke Width = " + aData.ThinnestStrokeWidth);
            System.out.println("Line " + aLine + " - QA Thickest Stroke Width = " + aData.ThickestStrokeWidth);
            System.out.println("Line " + aLine + " - QA Non Continuous Count = " + aData.NonContinuousCount);
        }
    }
}
