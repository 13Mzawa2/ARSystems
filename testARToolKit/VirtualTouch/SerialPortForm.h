#pragma once

namespace VirtualTouch {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO::Ports;

	/// <summary>
	/// SerialPortForm �̊T�v
	/// </summary>
	public ref class SerialPortForm : public System::Windows::Forms::Form
	{
	public:
		SerialPortForm(void)
		{
			InitializeComponent();
			//
			//TODO: �����ɃR���X�g���N�^�[ �R�[�h��ǉ����܂�
			//
		}

	protected:
		/// <summary>
		/// �g�p���̃��\�[�X�����ׂăN���[���A�b�v���܂��B
		/// </summary>
		~SerialPortForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::Label^  label2;
	public: System::Windows::Forms::ComboBox^  comboBox1;
	private:
	public: System::Windows::Forms::ComboBox^  comboBox2;


	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label3;
	public: System::Windows::Forms::ComboBox^  comboBox3;
	private:

	private: System::Windows::Forms::Button^  button3;

	private:
		/// <summary>
		/// �K�v�ȃf�U�C�i�[�ϐ��ł��B
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �f�U�C�i�[ �T�|�[�g�ɕK�v�ȃ��\�b�h�ł��B���̃��\�b�h�̓��e��
		/// �R�[�h �G�f�B�^�[�ŕύX���Ȃ��ł��������B
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(17, 29);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(58, 12);
			this->label1->TabIndex = 0;
			this->label1->Text = L"COM�|�[�g";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(23, 57);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(52, 12);
			this->label2->TabIndex = 1;
			this->label2->Text = L"�{�[���[�g";
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(87, 26);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 20);
			this->comboBox1->TabIndex = 2;
			this->comboBox1->Text = L"�i�I�����Ă��������j";
			// 
			// comboBox2
			// 
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(6) { L"1200", L"2400", L"4800", L"9600", L"14400", L"115200" });
			this->comboBox2->Location = System::Drawing::Point(87, 54);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(121, 20);
			this->comboBox2->TabIndex = 3;
			this->comboBox2->Text = L"4800";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(237, 79);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 4;
			this->button1->Text = L"�ڑ�";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &SerialPortForm::button1_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(19, 84);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(56, 12);
			this->label3->TabIndex = 5;
			this->label3->Text = L"�t���[����";
			// 
			// comboBox3
			// 
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"�Ȃ�", L"����" });
			this->comboBox3->Location = System::Drawing::Point(87, 81);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(121, 20);
			this->comboBox3->TabIndex = 6;
			this->comboBox3->Text = L"�Ȃ�";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(237, 24);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 8;
			this->button3->Text = L"�X�V";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &SerialPortForm::button3_Click);
			// 
			// SerialPortForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(339, 116);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->comboBox3);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"SerialPortForm";
			this->Text = L"SerialPortForm";
			this->Load += gcnew System::EventHandler(this, &SerialPortForm::SerialPortForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		System::Void SerialPortForm_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void button3_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void refreshCOMPortList(System::Void);
		System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
};
}
