#include "MainForm.h"
#include "SerialPortForm.h"

using namespace VirtualTouch;

extern bool serialPortIsSet;

System::Void SerialPortForm::SerialPortForm_Load(System::Object^  sender, System::EventArgs^  e)
{
	MainForm^ parentForm = static_cast<MainForm^>(this->Owner);		//	親フォームを設定
	refreshCOMPortList();
}
//	更新
System::Void SerialPortForm::button3_Click(System::Object^  sender, System::EventArgs^  e)
{
	refreshCOMPortList();
}
//	更新用関数
System::Void SerialPortForm::refreshCOMPortList(System::Void)
{
	comboBox1->Items->Clear();										//	COMポートをクリア
	//	ポート名取得
	try
	{
		comboBox1->Items->AddRange(SerialPort::GetPortNames());
	}
	//	例外処理（シリアルポートを照会できませんでした）
	catch (Win32Exception^ e)
	{
		MessageBox::Show(e->Message, "シリアルポートエラー", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
//	接続OR切断
System::Void SerialPortForm::button1_Click(System::Object^  sender, System::EventArgs^  e)
{
	button1->Text = "切断";
	serialPortIsSet = true;
	this->Close();
}