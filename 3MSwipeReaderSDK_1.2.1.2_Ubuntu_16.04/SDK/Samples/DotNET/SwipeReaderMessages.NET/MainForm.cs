using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Text;

namespace SwipeReaderMessages.NET
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class MainForm : System.Windows.Forms.Form
	{
		
		enum RowType
		{
			Data,
			Event,
			Error,
			Command,
			CommandResponse
		}
	
		private MMM.Readers.Modules.Swipe.SwipeSettings swipeSettings;
		
		// Helper control to get around .NET 2.0 threadsafe control problem
		private Control _threadHelperControl;
	
		private System.Windows.Forms.ListView listViewMessages;
		private System.Windows.Forms.ColumnHeader columnMessageId;
		private System.Windows.Forms.ColumnHeader columnMessageName;
		private System.Windows.Forms.ColumnHeader columnSize;
		private System.Windows.Forms.ColumnHeader columnData;
		private System.Windows.Forms.Button buttonClearList;
		private System.Windows.Forms.Label labelHardwareProto;
		private System.Windows.Forms.Timer timerInit;
		private System.ComponentModel.IContainer components;

		public MainForm()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			// Initialize helper control to get around .NET 2.0 threadsafe control problem
			_threadHelperControl = new Control();
			_threadHelperControl.CreateControl();
			
			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}		

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			this.listViewMessages = new System.Windows.Forms.ListView();
			this.columnMessageId = new System.Windows.Forms.ColumnHeader();
			this.columnMessageName = new System.Windows.Forms.ColumnHeader();
			this.columnSize = new System.Windows.Forms.ColumnHeader();
			this.columnData = new System.Windows.Forms.ColumnHeader();
			this.buttonClearList = new System.Windows.Forms.Button();
			this.labelHardwareProto = new System.Windows.Forms.Label();
			this.timerInit = new System.Windows.Forms.Timer(this.components);
			this.SuspendLayout();
			// 
			// listViewMessages
			// 
			this.listViewMessages.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
				| System.Windows.Forms.AnchorStyles.Left) 
				| System.Windows.Forms.AnchorStyles.Right)));
			this.listViewMessages.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
																							   this.columnMessageId,
																							   this.columnMessageName,
																							   this.columnSize,
																							   this.columnData});
			this.listViewMessages.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.listViewMessages.FullRowSelect = true;
			this.listViewMessages.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
			this.listViewMessages.Location = new System.Drawing.Point(8, 8);
			this.listViewMessages.MultiSelect = false;
			this.listViewMessages.Name = "listViewMessages";
			this.listViewMessages.Size = new System.Drawing.Size(728, 448);
			this.listViewMessages.TabIndex = 0;
			this.listViewMessages.View = System.Windows.Forms.View.Details;
			// 
			// columnMessageId
			// 
			this.columnMessageId.Text = "ID";
			// 
			// columnMessageName
			// 
			this.columnMessageName.Text = "Name";
			this.columnMessageName.Width = 160;
			// 
			// columnSize
			// 
			this.columnSize.Text = "Size";
			this.columnSize.Width = 80;
			// 
			// columnData
			// 
			this.columnData.Text = "Data";
			this.columnData.Width = 400;
			// 
			// buttonClearList
			// 
			this.buttonClearList.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.buttonClearList.Location = new System.Drawing.Point(664, 472);
			this.buttonClearList.Name = "buttonClearList";
			this.buttonClearList.TabIndex = 1;
			this.buttonClearList.Text = "Clear List";
			this.buttonClearList.Click += new System.EventHandler(this.buttonClearList_Click);
			// 
			// labelHardwareProto
			// 
			this.labelHardwareProto.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
				| System.Windows.Forms.AnchorStyles.Right)));
			this.labelHardwareProto.Location = new System.Drawing.Point(8, 472);
			this.labelHardwareProto.Name = "labelHardwareProto";
			this.labelHardwareProto.Size = new System.Drawing.Size(648, 23);
			this.labelHardwareProto.TabIndex = 2;
			// 
			// timerInit
			// 
			this.timerInit.Interval = 1;
			this.timerInit.Tick += new System.EventHandler(this.timerInit_Tick);
			// 
			// MainForm
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(744, 502);
			this.Controls.Add(this.labelHardwareProto);
			this.Controls.Add(this.buttonClearList);
			this.Controls.Add(this.listViewMessages);
			this.Name = "MainForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Swipe Reader Messages .NET";
			this.Load += new System.EventHandler(this.MainForm_Load);
			this.Closed += new System.EventHandler(this.MainForm_Closed);
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new MainForm());
		}
		
		/// Insert a new row into the list view.
		private void InsertRow(
			int aMessageID,
			string aMessageName,
			int aSize,
			string aData,
			RowType aType
		)
		{
			string lIDStr = string.Empty;
			
			switch (aType)
			{
				case RowType.Data:
				{
					lIDStr = "D: " + aMessageID.ToString();
					break;
				}
				case RowType.Event:
				{
					lIDStr = "Ev: " + aMessageID.ToString();
					break;
				}
				case RowType.Error:
				{
					lIDStr = "Err: " + aMessageID.ToString();
					break;
				}
				case RowType.Command:
				{
					lIDStr = "Command";
					break;
				}
				case RowType.CommandResponse:
				{
					lIDStr = "Response";
					break;
				}
			}
			
			listViewMessages.BeginUpdate();
			
			ListViewItem item = listViewMessages.Items.Add(lIDStr);
			item.SubItems.Add(aMessageName);
			item.SubItems.Add(aSize.ToString());
			item.SubItems.Add(aData);
			
			listViewMessages.EndUpdate();
			
			item.EnsureVisible();
		}
		
		// Thread helper callback to make sure data is received on the correct thread.
		private void ProcessDataThreadHelper(
			MMM.Readers.Modules.Swipe.SwipeItem aDataItem,
			object aData
		)
		{
			if (_threadHelperControl.InvokeRequired)
			{
				_threadHelperControl.Invoke(
					new MMM.Readers.Modules.Swipe.DataDelegate(ProcessData), 
					new object[] { aDataItem, aData }
				);
			}
			else
			{
				ProcessData(aDataItem, aData);
			}
		}
		
		// Thread helper callback to make sure data is received on the correct thread.
		private void ProcessEventThreadHelper(MMM.Readers.FullPage.EventCode aEventCode)
		{
			if (_threadHelperControl.InvokeRequired)
			{
				_threadHelperControl.Invoke(
					new MMM.Readers.FullPage.EventDelegate(ProcessEvent), 
					new object[] { aEventCode }
				);
			}
			else
			{
				ProcessEvent(aEventCode);
			}
		}
		
		// Thread helper callback to make sure data is received on the correct thread.
		private void ProcessErrorThreadHelper(
			MMM.Readers.ErrorCode aErrorCode, 
			string aErrorMessage
		)
		{
			if (_threadHelperControl.InvokeRequired)
			{
				_threadHelperControl.Invoke(
					new MMM.Readers.ErrorDelegate(ProcessError), 
					new object[] { aErrorCode, aErrorMessage }
				);
			}
			else
			{
				ProcessError(aErrorCode, aErrorMessage);
			}
		}

		private void ShowQALineData(
			int aMessageID, 
			int line, 
			MMM.Readers.Modules.Swipe.RTEQALineData qaLineData
		)
		{
			if (Convert.ToBoolean(qaLineData.HasData))
			{
				string lineStr = string.Format("LINE {0} - ", line);

				InsertRow(aMessageID, lineStr + "QA_CHAR_COUNT", 0, qaLineData.CharCount.ToString(), RowType.Data);
				InsertRow(aMessageID, lineStr + "QA_LOWER_LINE_BOUNDARY", 0, qaLineData.LowerLineBoundary.ToString(), RowType.Data);
				InsertRow(aMessageID, lineStr + "QA_UPPER_LINE_BOUNDARY", 0, qaLineData.UpperLineBoundary.ToString(), RowType.Data);
				InsertRow(aMessageID, lineStr + "QA_RECOGNISED_COUNT", 0, qaLineData.RecognisedCount.ToString(), RowType.Data);
				InsertRow(aMessageID, lineStr + "QA_AVERAGE_STROKE_WIDTH", 0, qaLineData.AverageStrokeWidth.ToString(), RowType.Data);
				InsertRow(aMessageID, lineStr + "QA_THINNEST_STROKE_WIDTH", 0, qaLineData.ThinnestStrokeWidth.ToString(), RowType.Data);
				InsertRow(aMessageID, lineStr + "QA_THICKEST_STROKE_WIDTH", 0, qaLineData.ThickestStrokeWidth.ToString(), RowType.Data);
				InsertRow(aMessageID, lineStr + "QA_NON_CONTINUOUS_COUNT", 0, qaLineData.NonContinuousCount.ToString(), RowType.Data);
			}
		}
		
		private void ProcessData(MMM.Readers.Modules.Swipe.SwipeItem aDataItem, object aData)
		{
			string dataStr = string.Empty;
			
			if (aData is int || aData is bool || aData is float || aData is string)
			{
				dataStr = aData.ToString();
				InsertRow((int)aDataItem, aDataItem.ToString(), 0, dataStr, RowType.Data);
			}
			else if (aData is MMM.Readers.CodelineData)
			{
				MMM.Readers.CodelineData codeline = (MMM.Readers.CodelineData)aData;
				InsertRow((int)aDataItem, aDataItem.ToString(), codeline.Data.Length, codeline.Data, RowType.Data);
				InsertRow((int)aDataItem, "OCR_LINE_1", codeline.Line1.Length, codeline.Line1, RowType.Data);
				InsertRow((int)aDataItem, "OCR_LINE_2", codeline.Line2.Length, codeline.Line2, RowType.Data);
				InsertRow((int)aDataItem, "OCR_LINE_3", codeline.Line3.Length, codeline.Line3, RowType.Data);
				InsertRow((int)aDataItem, "OCR_DOC_ID", codeline.DocId.Length, codeline.DocId, RowType.Data);
				InsertRow((int)aDataItem, "OCR_DOC_TYPE", codeline.DocType.Length, codeline.DocType, RowType.Data);
				InsertRow((int)aDataItem, "OCR_SURNAME", codeline.Surname.Length, codeline.Surname, RowType.Data);
				InsertRow((int)aDataItem, "OCR_FORENAME", codeline.Forename.Length, codeline.Forename, RowType.Data);
				InsertRow((int)aDataItem, "OCR_SECOND_NAME", codeline.SecondName.Length, codeline.SecondName, RowType.Data);
				InsertRow((int)aDataItem, "OCR_FORENAMES", codeline.Forenames.Length, codeline.Forenames, RowType.Data);

                if (codeline.DateOfBirth.Day == -1 &&
                    codeline.DateOfBirth.Month == -1 &&
                    codeline.DateOfBirth.Year == -1)
                {
                    InsertRow((int)aDataItem, "OCR_DATE_OF_BIRTH", 0, "", RowType.Data);
                }
                else
                {
                    string lD, lM, lY;

                    if (codeline.DateOfBirth.Day == -1)
                        lD = "??-";
                    else
                        lD = string.Format("{0:00}-", codeline.DateOfBirth.Day);

                    if (codeline.DateOfBirth.Month == -1)
                        lM = "??-";
                    else
                        lM = string.Format("{0:00}-", codeline.DateOfBirth.Month);

                    if (codeline.DateOfBirth.Year == -1)
                        lY = "??";
                    else
                        lY = string.Format("{0:00}", codeline.DateOfBirth.Year);


                    InsertRow((int)aDataItem, "OCR_DATE_OF_BIRTH", 0, (lD+lM+lY), RowType.Data);

                }


                if (codeline.ExpiryDate.Day == -1 &&
                    codeline.ExpiryDate.Month == -1 &&
                    codeline.ExpiryDate.Year == -1)
                {
                    InsertRow((int)aDataItem, "OCR_EXPIRY_DATE", 0, "", RowType.Data);
                }
                else
                {
                    string lD, lM, lY;

                    if (codeline.ExpiryDate.Day == -1)
                        lD = "??-";
                    else
                        lD = string.Format("{0:00}-", codeline.ExpiryDate.Day);

                    if (codeline.ExpiryDate.Month == -1)
                        lM = "??-";
                    else
                        lM = string.Format("{0:00}-", codeline.ExpiryDate.Month);

                    if (codeline.ExpiryDate.Year == -1)
                        lY = "??";
                    else
                        lY = string.Format("{0:00}", codeline.ExpiryDate.Year);


                    InsertRow((int)aDataItem, "OCR_EXPIRY_DATE", 0, (lD+lM+lY), RowType.Data);

                }  
				
                InsertRow((int)aDataItem, "OCR_ISSUING_STATE", codeline.IssuingState.Length, codeline.IssuingState, RowType.Data);
				InsertRow((int)aDataItem, "OCR_NATIONALITY", codeline.Nationality.Length, codeline.Nationality, RowType.Data);
				InsertRow((int)aDataItem, "OCR_DOC_NUMBER", codeline.DocNumber.Length, codeline.DocNumber, RowType.Data);
				InsertRow((int)aDataItem, "OCR_SEX", codeline.Sex.Length, codeline.Sex, RowType.Data);
				InsertRow((int)aDataItem, "OCR_SHORT_SEX", 1, Convert.ToChar(codeline.ShortSex).ToString(), RowType.Data);
#if !DOTNET_11
                InsertRow((int)aDataItem, "OCR_OPTIONALDATA1", codeline.OptionalData1.Length, codeline.OptionalData1, RowType.Data);
                InsertRow((int)aDataItem, "OCR_OPTIONALDATA2", codeline.OptionalData2.Length, codeline.OptionalData2, RowType.Data);
#endif
			}
			else if (aData is MMM.Readers.Modules.Swipe.MsrData)
			{
				MMM.Readers.Modules.Swipe.MsrData msrData = (MMM.Readers.Modules.Swipe.MsrData)aData;
				InsertRow((int)aDataItem, "MSR_TRACK_1", msrData.Track1.Length, msrData.Track1, RowType.Data);
				InsertRow((int)aDataItem, "MSR_TRACK_2", msrData.Track2.Length, msrData.Track2, RowType.Data);
				InsertRow((int)aDataItem, "MSR_TRACK_3", msrData.Track3.Length, msrData.Track3, RowType.Data);
			}
            else if (aData is MMM.Readers.Modules.Swipe.SwipeBarcodePDF417Data)
            {
                MMM.Readers.Modules.Swipe.SwipeBarcodePDF417Data swipeBarcodeData = (MMM.Readers.Modules.Swipe.SwipeBarcodePDF417Data)aData;
                InsertRow((int)aDataItem, "BARCODE PDF417", swipeBarcodeData.DataField.Length, swipeBarcodeData.DataField, RowType.Data);
            }
            else if (aData is MMM.Readers.Modules.Swipe.SwipeBarcodeCode128Data)
            {
                MMM.Readers.Modules.Swipe.SwipeBarcodeCode128Data swipeBarcodeData = (MMM.Readers.Modules.Swipe.SwipeBarcodeCode128Data)aData;
                InsertRow((int)aDataItem, "BARCODE CODE 128", swipeBarcodeData.DataField.Length, swipeBarcodeData.DataField, RowType.Data);
            }
            else if (aData is MMM.Readers.Modules.Swipe.SwipeBarcodeCode39Data)
            {
                MMM.Readers.Modules.Swipe.SwipeBarcodeCode39Data swipeBarcodeData = (MMM.Readers.Modules.Swipe.SwipeBarcodeCode39Data)aData;
                InsertRow((int)aDataItem, "BARCODE CODE 39", swipeBarcodeData.DataField.Length, swipeBarcodeData.DataField, RowType.Data);
            }
			else if (aData is MMM.Readers.AAMVAData)
			{
				MMM.Readers.AAMVAData AAMVAData = (MMM.Readers.AAMVAData)aData;
                InsertRow((int)aDataItem, "AAMVA_FULLNAME", AAMVAData.Parsed.FullName.Length, AAMVAData.Parsed.FullName, RowType.Data);
                InsertRow((int)aDataItem, "AAMVA_FORENAME", AAMVAData.Parsed.Forename.Length, AAMVAData.Parsed.Forename, RowType.Data);
                InsertRow((int)aDataItem, "AAMVA_SURNAME", AAMVAData.Parsed.Surname.Length, AAMVAData.Parsed.Surname, RowType.Data);
                InsertRow((int)aDataItem, "AAMVA_LICENCE_NUMBER", AAMVAData.Parsed.LicenceNumber.Length, AAMVAData.Parsed.LicenceNumber, RowType.Data);
                InsertRow((int)aDataItem, "AAMVA_ADDRESS_STREET", AAMVAData.Parsed.AddressStreet.Length, AAMVAData.Parsed.AddressStreet, RowType.Data);
                InsertRow((int)aDataItem, "AAMVA_ADDRESS_CITY", AAMVAData.Parsed.AddressCity.Length, AAMVAData.Parsed.AddressCity, RowType.Data);
                InsertRow((int)aDataItem, "AAMVA_ADDRESS_POSTALCODE", AAMVAData.Parsed.AddressPostalCode.Length, AAMVAData.Parsed.AddressPostalCode, RowType.Data);
                InsertRow((int)aDataItem, "AAMVA_ADDRESS_STATE", AAMVAData.Parsed.AddressState.Length, AAMVAData.Parsed.AddressState, RowType.Data);
                InsertRow((int)aDataItem, "AAMVA_ADDRESS_COUNTRY", AAMVAData.Parsed.AddressCountry.Length, AAMVAData.Parsed.AddressCountry, RowType.Data);
			}
            else if (aData is MMM.Readers.Modules.Swipe.AtbData)
            {
                MMM.Readers.Modules.Swipe.AtbData atbData = (MMM.Readers.Modules.Swipe.AtbData)aData;
                InsertRow((int)aDataItem, "ATB_TRACK_1_BLOCK_1", atbData.Track1.Block1.Length, atbData.Track1.Block1, RowType.Data);
                InsertRow((int)aDataItem, "ATB_TRACK_1_BLOCK_2", atbData.Track1.Block2.Length, atbData.Track1.Block2, RowType.Data);
                InsertRow((int)aDataItem, "ATB_TRACK_1_BLOCK_3", atbData.Track1.Block3.Length, atbData.Track1.Block3, RowType.Data);
                InsertRow((int)aDataItem, "ATB_TRACK_2_BLOCK_1", atbData.Track2.Block1.Length, atbData.Track2.Block1, RowType.Data);
                InsertRow((int)aDataItem, "ATB_TRACK_2_BLOCK_2", atbData.Track2.Block2.Length, atbData.Track2.Block2, RowType.Data);
                InsertRow((int)aDataItem, "ATB_TRACK_2_BLOCK_3", atbData.Track2.Block3.Length, atbData.Track2.Block3, RowType.Data);
                InsertRow((int)aDataItem, "ATB_TRACK_3_BLOCK_1", atbData.Track3.Block1.Length, atbData.Track3.Block1, RowType.Data);
                InsertRow((int)aDataItem, "ATB_TRACK_3_BLOCK_2", atbData.Track3.Block2.Length, atbData.Track3.Block2, RowType.Data);
                InsertRow((int)aDataItem, "ATB_TRACK_3_BLOCK_3", atbData.Track3.Block3.Length, atbData.Track3.Block3, RowType.Data);
                InsertRow((int)aDataItem, "ATB_TRACK_4_BLOCK_1", atbData.Track4.Block1.Length, atbData.Track4.Block1, RowType.Data);
                InsertRow((int)aDataItem, "ATB_TRACK_4_BLOCK_2", atbData.Track4.Block2.Length, atbData.Track4.Block2, RowType.Data);
                InsertRow((int)aDataItem, "ATB_TRACK_4_BLOCK_3", atbData.Track4.Block3.Length, atbData.Track4.Block3, RowType.Data);
            }
			else if (aData is MMM.Readers.Modules.Swipe.RTEQAData)
			{
				MMM.Readers.Modules.Swipe.RTEQAData qaData = (MMM.Readers.Modules.Swipe.RTEQAData)aData;
				InsertRow((int)aDataItem, "QA_CODELINE_COUNT", 0, qaData.CodelineCount.ToString(), RowType.Data);
				InsertRow((int)aDataItem, "QA_COLUMN_COUNT", 0, qaData.ColumnCount.ToString(), RowType.Data);
				InsertRow((int)aDataItem, "QA_CLEAR_AREA_PRESENT", 0, Convert.ToBoolean(qaData.ClearAreaPresent).ToString(), RowType.Data);
				InsertRow((int)aDataItem, "QA_SPOT_COUNT", 0, qaData.SpotCount.ToString(), RowType.Data);
				ShowQALineData((int)aDataItem, 1, qaData.Line1);
				ShowQALineData((int)aDataItem, 2, qaData.Line2);
				ShowQALineData((int)aDataItem, 3, qaData.Line3);
			}
			else if (aData is MMM.Readers.Modules.Swipe.RTESwipeData)
			{
				MMM.Readers.Modules.Swipe.RTESwipeData rteData = (MMM.Readers.Modules.Swipe.RTESwipeData)aData;
				InsertRow((int)aDataItem, "RTE_DEVICE_TYPE", 0, rteData.DeviceType.ToString(), RowType.Data);
				InsertRow((int)aDataItem, "RTE_MESSAGE_TYPE", 0, rteData.MessageType.ToString(), RowType.Data);
				InsertRow((int)aDataItem, "RTE_BCC", 0, rteData.BCC.ToString(), RowType.Data);
				InsertRow((int)aDataItem, "RTE_OCR_FLAG_BYTE", 0, rteData.OCRFlagByte.ToString(), RowType.Data);
			}
			else if (aData is MMM.Readers.Modules.Swipe.MuseSwipeData)
			{
				MMM.Readers.Modules.Swipe.MuseSwipeData museData = (MMM.Readers.Modules.Swipe.MuseSwipeData)aData;
				InsertRow((int)aDataItem, "MUSE_DEVICE_TYPE", 0, museData.DeviceType.ToString(), RowType.Data);
				InsertRow((int)aDataItem, "MUSE_CRC_HIGH", 0, museData.CrcHigh.ToString(), RowType.Data);
				InsertRow((int)aDataItem, "MUSE_CRC_LOW", 0, museData.CrcLow.ToString(), RowType.Data);
			}
			else if (aData is MMM.Readers.Modules.Swipe.CuteSwipeData)
			{
				MMM.Readers.Modules.Swipe.CuteSwipeData cuteData = (MMM.Readers.Modules.Swipe.CuteSwipeData)aData;
				InsertRow((int)aDataItem, "CUTE_DEVICE_TYPE", 0, cuteData.DeviceType.ToString(), RowType.Data);
			}
			else if (aData is MMM.Readers.Modules.Swipe.MagtekMsrSwipeData)
			{
				MMM.Readers.Modules.Swipe.MagtekMsrSwipeData magtekData = (MMM.Readers.Modules.Swipe.MagtekMsrSwipeData)aData;
				InsertRow((int)aDataItem, "MAGTEK_MSR_CARD_TYPE", 0, magtekData.CardEncodeType.ToString(), RowType.Data);
			}
            else if (aData is MMM.Readers.Modules.Swipe.TecsSwipeData)
            {
                MMM.Readers.Modules.Swipe.TecsSwipeData tecsData = (MMM.Readers.Modules.Swipe.TecsSwipeData)aData;
                InsertRow((int)aDataItem, "TECS_DEVICE_TYPE", 0, tecsData.DeviceType.ToString(), RowType.Data);
            }
            else if (aData is byte)
			{
				byte dataValue = (byte)aData;
				dataStr = dataValue.ToString("X2");
				InsertRow((int)aDataItem, aDataItem.ToString(), 0, dataStr, RowType.Data);
			}
			else if (aData is byte[])
			{
				byte[] dataArray = aData as byte[];
				if (aDataItem == MMM.Readers.Modules.Swipe.SwipeItem.WHOLE_DATA)
				{
					dataStr = ConvertSwipeDataByteArray(dataArray);
				}
				else
				{
					foreach (byte byteVal in dataArray)
					{
						dataStr = string.Concat(dataStr, byteVal.ToString("X2"), " ");
					}
				}
				InsertRow((int)aDataItem, aDataItem.ToString(), 0, dataStr, RowType.Data);
			}			
		}
		
		private void ProcessEvent(MMM.Readers.FullPage.EventCode aEventCode)
		{
			InsertRow((int)aEventCode, aEventCode.ToString(), 0, string.Empty, RowType.Event);
		}
		
		private void ProcessError(MMM.Readers.ErrorCode aErrorCode, string aErrorMessage)
		{
			InsertRow((int)aErrorCode, aErrorCode.ToString(), 0, aErrorMessage, RowType.Error);
		}
		
		private void InitialiseSwipeAPI()
		{
			MMM.Readers.ErrorCode lErrorCode = MMM.Readers.ErrorCode.NO_ERROR_OCCURRED;
			
			// Initialise logging and error handling first. The error handler callback
			// will receive all error messages generated by the 3M Page Reader SDK
			MMM.Readers.Modules.Reader.SetErrorHandler(
				new MMM.Readers.ErrorDelegate(ProcessErrorThreadHelper),
                IntPtr.Zero 
			);
			lErrorCode = MMM.Readers.Modules.Reader.InitialiseLogging(
				true,
				3,
				-1,
				"SwipeReader.Net.log"
			);
			
			if (lErrorCode == MMM.Readers.ErrorCode.NO_ERROR_OCCURRED)
			{
				// Next load the settings for the Swipe Reader from the ini files. You can 
				// also modify and save settings back to the ini files using 
				// MMM.Readers.Modules.Reader.SaveSwipeSettings()
				lErrorCode = MMM.Readers.Modules.Reader.LoadSwipeSettings(
					ref swipeSettings
				);
			}
			
			if (lErrorCode == MMM.Readers.ErrorCode.NO_ERROR_OCCURRED)
			{
				// Initialise the Swipe Reader. Data and events will be sent back in a 
				// non-blocking fashion through the callbacks provided
				//
				// Thread helper delegates are used to avoid thread-safety issues, 
				// particularly with .NET framework 2.0
				lErrorCode = MMM.Readers.Modules.Swipe.Initialise(
					swipeSettings,
					new MMM.Readers.Modules.Swipe.DataDelegate(ProcessDataThreadHelper),
					new MMM.Readers.FullPage.EventDelegate(ProcessEventThreadHelper)
				);
			}
			
			if (lErrorCode != MMM.Readers.ErrorCode.NO_ERROR_OCCURRED)
			{
				InsertRow(
					(int)lErrorCode, 
					lErrorCode.ToString(), 
					0, 
					"Failed to initialise Swipe Reader API", 
					RowType.Error
				);
			}
			else
			{
				// Display the hardware device and protocol in use
				string lProtocolName = new string(swipeSettings.Protocol.ProtocolName);
				
				if (lProtocolName.StartsWith("RTE"))
				{
					// For RTE_INTERRUPT and RTE_POLLED modes, the Swipe Reader API can 
					// automatically send Enable Device commands once finished reading so
					// that you do not have to
					if (
						!lProtocolName.Equals("RTE_NATIVE") && 
						swipeSettings.Protocol.RTE.AutoSendEnableDevice > 0
					)
					{
						lProtocolName = string.Concat(
							lProtocolName, 
							", Auto Send Enable Command"
						);
					}
					
					if (swipeSettings.Protocol.RTE.UseBCC > 0)
					{
						lProtocolName = string.Concat(
							lProtocolName, 
							", with BCC"
						);
					}
					else
					{
						lProtocolName = string.Concat(
							lProtocolName, 
							", no BCC"
						);
					}
				}
				
				labelHardwareProto.Text = string.Format(
					"{0}, Hardware: {1}", 
					lProtocolName, 
					swipeSettings.Hardware.DeviceType.ToString()
				);
			}
		}
		
		private string ConvertSwipeDataByteArray(byte[] array)
		{
			StringBuilder builder = new StringBuilder();
			
			foreach (byte val in array)
			{
				switch (val)
				{
					case 0 : builder.Append("{NUL}"); break;
					case MMM.Readers.Modules.Swipe.ByteConstants.SOH : builder.Append("{SOH}"); break;
					case MMM.Readers.Modules.Swipe.ByteConstants.STX : builder.Append("{STX}"); break;
					case MMM.Readers.Modules.Swipe.ByteConstants.ETX : builder.Append("{ETX}"); break;
					case MMM.Readers.Modules.Swipe.ByteConstants.LF : builder.Append("{LF}"); break;
					case MMM.Readers.Modules.Swipe.ByteConstants.CR : builder.Append("{CR}"); break;
					case MMM.Readers.Modules.Swipe.ByteConstants.ACK : builder.Append("{ACK}"); break;
					case MMM.Readers.Modules.Swipe.ByteConstants.NACK : builder.Append("{NACK"); break;					
					case MMM.Readers.Modules.Swipe.CuteProtocolByteConstants.SOD1 : builder.Append("{SOD1}"); break;
					case MMM.Readers.Modules.Swipe.CuteProtocolByteConstants.EOD1 : builder.Append("{EOD1}"); break;
					case MMM.Readers.Modules.Swipe.CuteProtocolByteConstants.SOD2 : builder.Append("{SOD2}"); break;
					case MMM.Readers.Modules.Swipe.CuteProtocolByteConstants.EOD2 : builder.Append("{EOD2}"); break;
					default : builder.Append(Convert.ToChar(val)); break;
				}
			}
			
			return builder.ToString();
		}

		private void MainForm_Load(object sender, System.EventArgs e)
		{
			// Use a timer to initialise the Swipe Reader API, this allows the dialog
			// to be drawn to the screen so the user can see something happening
			timerInit.Enabled = true;
		}

		private void MainForm_Closed(object sender, System.EventArgs e)
		{
			MMM.Readers.Modules.Swipe.Shutdown();
			MMM.Readers.Modules.Reader.ShutdownLogging();
		}

		private void timerInit_Tick(object sender, System.EventArgs e)
		{
			timerInit.Enabled = false;
			InitialiseSwipeAPI();
		}

		private void buttonClearList_Click(object sender, System.EventArgs e)
		{
			listViewMessages.Items.Clear();
		}
		
	}
}
