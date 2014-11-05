#include "MainForm.h"
#include "SerialPortForm.h"

using namespace VirtualTouch;

extern bool serialPortIsSet;

System::Void SerialPortForm::SerialPortForm_Load(System::Object^  sender, System::EventArgs^  e)
{
	MainForm^ parentForm = static_cast<MainForm^>(this->Owner);		//	�e�t�H�[����ݒ�
	refreshCOMPortList();
}
//	�X�V
System::Void SerialPortForm::button3_Click(System::Object^  sender, System::EventArgs^  e)
{
	refreshCOMPortList();
}
//	�X�V�p�֐�
System::Void SerialPortForm::refreshCOMPortList(System::Void)
{
	comboBox1->Items->Clear();										//	COM�|�[�g���N���A
	//	�|�[�g���擾
	try
	{
		comboBox1->Items->AddRange(SerialPort::GetPortNames());
	}
	//	��O�����i�V���A���|�[�g���Ɖ�ł��܂���ł����j
	catch (Win32Exception^ e)
	{
		MessageBox::Show(e->Message, "�V���A���|�[�g�G���[", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
//	�ڑ�OR�ؒf
System::Void SerialPortForm::button1_Click(System::Object^  sender, System::EventArgs^  e)
{
	button1->Text = "�ؒf";
	serialPortIsSet = true;
	this->Close();
}