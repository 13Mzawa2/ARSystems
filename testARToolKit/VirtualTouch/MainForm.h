#pragma once

namespace VirtualTouch {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MainForm �̊T�v
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
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
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::IO::Ports::SerialPort^  serialPort1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  �t�@�C��ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ���f�����J��ToolStripMenuItem;



	private: System::Windows::Forms::ToolStripMenuItem^  �I��ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �ҏWToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �ݒ�ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �R���g���[��ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �E�B���h�EToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �w���vToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::ToolStripMenuItem^  �V���A���|�[�gToolStripMenuItem;




	private: System::Windows::Forms::ToolStripMenuItem^  aRToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aR�}�[�J�[ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �J�����p�����[�^ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ���[�hToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ���f���\��ToolStripMenuItem;


	private: System::Windows::Forms::ToolStripMenuItem^  �������[�hToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �J����ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ����ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �ꎞ��~ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �X�i�b�v��ۑ�ToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  �I��ToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  �E�C���h�E�T�C�YToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  x05ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  x10ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �U���q�ʒu�\��ToolStripMenuItem;

	protected:
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::ToolStripMenuItem^  �U��ONToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �f�v�X�}�b�vToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  d���f��ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ��ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �~��ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �~��ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �e�B�[�|�b�gToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �g�[���XToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �����ʑ�ToolStripMenuItem;

	private:
		/// <summary>
		/// �K�v�ȃf�U�C�i�[�ϐ��ł��B
		/// </summary>
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �f�U�C�i�[ �T�|�[�g�ɕK�v�ȃ��\�b�h�ł��B���̃��\�b�h�̓��e��
		/// �R�[�h �G�f�B�^�[�ŕύX���Ȃ��ł��������B
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->�t�@�C��ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->���f�����J��ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�I��ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�ҏWToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�ݒ�ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�V���A���|�[�gToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aRToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aR�}�[�J�[ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�J�����p�����[�^ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�R���g���[��ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->���[�hToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->���f���\��ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�U���q�ʒu�\��ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�U��ONToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�f�v�X�}�b�vToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�������[�hToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�J����ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->����ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�ꎞ��~ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�X�i�b�v��ۑ�ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�I��ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->d���f��ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->��ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�~��ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�~��ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�g�[���XToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�e�B�[�|�b�gToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�E�B���h�EToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�E�C���h�E�T�C�YToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->x05ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->x10ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�w���vToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->�����ʑ�ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// serialPort1
			// 
			this->serialPort1->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(this, &MainForm::serialPort1_DataReceived);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->�t�@�C��ToolStripMenuItem,
					this->�ҏWToolStripMenuItem, this->�ݒ�ToolStripMenuItem, this->�R���g���[��ToolStripMenuItem, this->�E�B���h�EToolStripMenuItem, this->�w���vToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(640, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// �t�@�C��ToolStripMenuItem
			// 
			this->�t�@�C��ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->���f�����J��ToolStripMenuItem,
					this->�I��ToolStripMenuItem
			});
			this->�t�@�C��ToolStripMenuItem->Name = L"�t�@�C��ToolStripMenuItem";
			this->�t�@�C��ToolStripMenuItem->Size = System::Drawing::Size(53, 20);
			this->�t�@�C��ToolStripMenuItem->Text = L"�t�@�C��";
			// 
			// ���f�����J��ToolStripMenuItem
			// 
			this->���f�����J��ToolStripMenuItem->Name = L"���f�����J��ToolStripMenuItem";
			this->���f�����J��ToolStripMenuItem->Size = System::Drawing::Size(130, 22);
			this->���f�����J��ToolStripMenuItem->Text = L"���f�����J��";
			// 
			// �I��ToolStripMenuItem
			// 
			this->�I��ToolStripMenuItem->Name = L"�I��ToolStripMenuItem";
			this->�I��ToolStripMenuItem->Size = System::Drawing::Size(130, 22);
			this->�I��ToolStripMenuItem->Text = L"�I��";
			this->�I��ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::�I��ToolStripMenuItem_Click);
			// 
			// �ҏWToolStripMenuItem
			// 
			this->�ҏWToolStripMenuItem->Name = L"�ҏWToolStripMenuItem";
			this->�ҏWToolStripMenuItem->Size = System::Drawing::Size(43, 20);
			this->�ҏWToolStripMenuItem->Text = L"�ҏW";
			// 
			// �ݒ�ToolStripMenuItem
			// 
			this->�ݒ�ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->�V���A���|�[�gToolStripMenuItem,
					this->aRToolStripMenuItem
			});
			this->�ݒ�ToolStripMenuItem->Name = L"�ݒ�ToolStripMenuItem";
			this->�ݒ�ToolStripMenuItem->Size = System::Drawing::Size(43, 20);
			this->�ݒ�ToolStripMenuItem->Text = L"�ݒ�";
			// 
			// �V���A���|�[�gToolStripMenuItem
			// 
			this->�V���A���|�[�gToolStripMenuItem->Name = L"�V���A���|�[�gToolStripMenuItem";
			this->�V���A���|�[�gToolStripMenuItem->Size = System::Drawing::Size(138, 22);
			this->�V���A���|�[�gToolStripMenuItem->Text = L"�V���A���|�[�g";
			this->�V���A���|�[�gToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::�V���A���|�[�gToolStripMenuItem_Click);
			// 
			// aRToolStripMenuItem
			// 
			this->aRToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->aR�}�[�J�[ToolStripMenuItem,
					this->�J�����p�����[�^ToolStripMenuItem
			});
			this->aRToolStripMenuItem->Name = L"aRToolStripMenuItem";
			this->aRToolStripMenuItem->Size = System::Drawing::Size(138, 22);
			this->aRToolStripMenuItem->Text = L"AR";
			// 
			// aR�}�[�J�[ToolStripMenuItem
			// 
			this->aR�}�[�J�[ToolStripMenuItem->Name = L"aR�}�[�J�[ToolStripMenuItem";
			this->aR�}�[�J�[ToolStripMenuItem->Size = System::Drawing::Size(143, 22);
			this->aR�}�[�J�[ToolStripMenuItem->Text = L"AR�}�[�J�[";
			// 
			// �J�����p�����[�^ToolStripMenuItem
			// 
			this->�J�����p�����[�^ToolStripMenuItem->Name = L"�J�����p�����[�^ToolStripMenuItem";
			this->�J�����p�����[�^ToolStripMenuItem->Size = System::Drawing::Size(143, 22);
			this->�J�����p�����[�^ToolStripMenuItem->Text = L"�J�����p�����[�^";
			// 
			// �R���g���[��ToolStripMenuItem
			// 
			this->�R���g���[��ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->���[�hToolStripMenuItem,
					this->�J����ToolStripMenuItem, this->d���f��ToolStripMenuItem
			});
			this->�R���g���[��ToolStripMenuItem->Name = L"�R���g���[��ToolStripMenuItem";
			this->�R���g���[��ToolStripMenuItem->Size = System::Drawing::Size(73, 20);
			this->�R���g���[��ToolStripMenuItem->Text = L"�R���g���[��";
			// 
			// ���[�hToolStripMenuItem
			// 
			this->���[�hToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->���f���\��ToolStripMenuItem,
					this->�U���q�ʒu�\��ToolStripMenuItem, this->�U��ONToolStripMenuItem, this->�f�v�X�}�b�vToolStripMenuItem, this->�������[�hToolStripMenuItem
			});
			this->���[�hToolStripMenuItem->Name = L"���[�hToolStripMenuItem";
			this->���[�hToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->���[�hToolStripMenuItem->Text = L"���[�h";
			// 
			// ���f���\��ToolStripMenuItem
			// 
			this->���f���\��ToolStripMenuItem->Checked = true;
			this->���f���\��ToolStripMenuItem->CheckOnClick = true;
			this->���f���\��ToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->���f���\��ToolStripMenuItem->Name = L"���f���\��ToolStripMenuItem";
			this->���f���\��ToolStripMenuItem->Size = System::Drawing::Size(158, 22);
			this->���f���\��ToolStripMenuItem->Text = L"���f���\��";
			// 
			// �U���q�ʒu�\��ToolStripMenuItem
			// 
			this->�U���q�ʒu�\��ToolStripMenuItem->Checked = true;
			this->�U���q�ʒu�\��ToolStripMenuItem->CheckOnClick = true;
			this->�U���q�ʒu�\��ToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->�U���q�ʒu�\��ToolStripMenuItem->Name = L"�U���q�ʒu�\��ToolStripMenuItem";
			this->�U���q�ʒu�\��ToolStripMenuItem->Size = System::Drawing::Size(158, 22);
			this->�U���q�ʒu�\��ToolStripMenuItem->Text = L"�U���q�ʒu�\��";
			// 
			// �U��ONToolStripMenuItem
			// 
			this->�U��ONToolStripMenuItem->Name = L"�U��ONToolStripMenuItem";
			this->�U��ONToolStripMenuItem->Size = System::Drawing::Size(158, 22);
			this->�U��ONToolStripMenuItem->Text = L"�U��ON";
			this->�U��ONToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::�U��ONToolStripMenuItem_Click);
			// 
			// �f�v�X�}�b�vToolStripMenuItem
			// 
			this->�f�v�X�}�b�vToolStripMenuItem->CheckOnClick = true;
			this->�f�v�X�}�b�vToolStripMenuItem->Name = L"�f�v�X�}�b�vToolStripMenuItem";
			this->�f�v�X�}�b�vToolStripMenuItem->Size = System::Drawing::Size(158, 22);
			this->�f�v�X�}�b�vToolStripMenuItem->Text = L"�f�v�X�}�b�v";
			this->�f�v�X�}�b�vToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::�f�v�X�}�b�vToolStripMenuItem_Click);
			// 
			// �������[�hToolStripMenuItem
			// 
			this->�������[�hToolStripMenuItem->Name = L"�������[�hToolStripMenuItem";
			this->�������[�hToolStripMenuItem->Size = System::Drawing::Size(158, 22);
			this->�������[�hToolStripMenuItem->Text = L"�������[�h";
			// 
			// �J����ToolStripMenuItem
			// 
			this->�J����ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->����ToolStripMenuItem,
					this->�ꎞ��~ToolStripMenuItem, this->�X�i�b�v��ۑ�ToolStripMenuItem1, this->�I��ToolStripMenuItem1
			});
			this->�J����ToolStripMenuItem->Name = L"�J����ToolStripMenuItem";
			this->�J����ToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->�J����ToolStripMenuItem->Text = L"�J����";
			// 
			// ����ToolStripMenuItem
			// 
			this->����ToolStripMenuItem->Name = L"����ToolStripMenuItem";
			this->����ToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->����ToolStripMenuItem->Text = L"����";
			this->����ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::����ToolStripMenuItem_Click);
			// 
			// �ꎞ��~ToolStripMenuItem
			// 
			this->�ꎞ��~ToolStripMenuItem->Name = L"�ꎞ��~ToolStripMenuItem";
			this->�ꎞ��~ToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->�ꎞ��~ToolStripMenuItem->Text = L"�ꎞ��~";
			this->�ꎞ��~ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::�ꎞ��~ToolStripMenuItem_Click);
			// 
			// �X�i�b�v��ۑ�ToolStripMenuItem1
			// 
			this->�X�i�b�v��ۑ�ToolStripMenuItem1->Name = L"�X�i�b�v��ۑ�ToolStripMenuItem1";
			this->�X�i�b�v��ۑ�ToolStripMenuItem1->Size = System::Drawing::Size(142, 22);
			this->�X�i�b�v��ۑ�ToolStripMenuItem1->Text = L"�X�i�b�v��ۑ�";
			this->�X�i�b�v��ۑ�ToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MainForm::�X�i�b�v��ۑ�ToolStripMenuItem1_Click);
			// 
			// �I��ToolStripMenuItem1
			// 
			this->�I��ToolStripMenuItem1->Name = L"�I��ToolStripMenuItem1";
			this->�I��ToolStripMenuItem1->Size = System::Drawing::Size(142, 22);
			this->�I��ToolStripMenuItem1->Text = L"�I��";
			this->�I��ToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MainForm::�I��ToolStripMenuItem1_Click);
			// 
			// d���f��ToolStripMenuItem
			// 
			this->d���f��ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
				this->��ToolStripMenuItem,
					this->������ToolStripMenuItem, this->�~��ToolStripMenuItem, this->�~��ToolStripMenuItem, this->�g�[���XToolStripMenuItem, this->�����ʑ�ToolStripMenuItem,
					this->�e�B�[�|�b�gToolStripMenuItem
			});
			this->d���f��ToolStripMenuItem->Name = L"d���f��ToolStripMenuItem";
			this->d���f��ToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->d���f��ToolStripMenuItem->Text = L"3D���f��";
			// 
			// ��ToolStripMenuItem
			// 
			this->��ToolStripMenuItem->Name = L"��ToolStripMenuItem";
			this->��ToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->��ToolStripMenuItem->Text = L"��";
			this->��ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::��ToolStripMenuItem_Click);
			// 
			// ������ToolStripMenuItem
			// 
			this->������ToolStripMenuItem->Name = L"������ToolStripMenuItem";
			this->������ToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->������ToolStripMenuItem->Text = L"������";
			this->������ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::������ToolStripMenuItem_Click);
			// 
			// �~��ToolStripMenuItem
			// 
			this->�~��ToolStripMenuItem->Name = L"�~��ToolStripMenuItem";
			this->�~��ToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->�~��ToolStripMenuItem->Text = L"�~��";
			this->�~��ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::�~��ToolStripMenuItem_Click);
			// 
			// �~��ToolStripMenuItem
			// 
			this->�~��ToolStripMenuItem->Name = L"�~��ToolStripMenuItem";
			this->�~��ToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->�~��ToolStripMenuItem->Text = L"�~��";
			this->�~��ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::�~��ToolStripMenuItem_Click);
			// 
			// �g�[���XToolStripMenuItem
			// 
			this->�g�[���XToolStripMenuItem->Name = L"�g�[���XToolStripMenuItem";
			this->�g�[���XToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->�g�[���XToolStripMenuItem->Text = L"�g�[���X";
			this->�g�[���XToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::�g�[���XToolStripMenuItem_Click);
			// 
			// �e�B�[�|�b�gToolStripMenuItem
			// 
			this->�e�B�[�|�b�gToolStripMenuItem->Name = L"�e�B�[�|�b�gToolStripMenuItem";
			this->�e�B�[�|�b�gToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->�e�B�[�|�b�gToolStripMenuItem->Text = L"�e�B�[�|�b�g";
			this->�e�B�[�|�b�gToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::�e�B�[�|�b�gToolStripMenuItem_Click);
			// 
			// �E�B���h�EToolStripMenuItem
			// 
			this->�E�B���h�EToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->�E�C���h�E�T�C�YToolStripMenuItem });
			this->�E�B���h�EToolStripMenuItem->Name = L"�E�B���h�EToolStripMenuItem";
			this->�E�B���h�EToolStripMenuItem->Size = System::Drawing::Size(61, 20);
			this->�E�B���h�EToolStripMenuItem->Text = L"�E�B���h�E";
			// 
			// �E�C���h�E�T�C�YToolStripMenuItem
			// 
			this->�E�C���h�E�T�C�YToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->x05ToolStripMenuItem,
					this->x10ToolStripMenuItem
			});
			this->�E�C���h�E�T�C�YToolStripMenuItem->Name = L"�E�C���h�E�T�C�YToolStripMenuItem";
			this->�E�C���h�E�T�C�YToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->�E�C���h�E�T�C�YToolStripMenuItem->Text = L"�E�C���h�E�T�C�Y";
			// 
			// x05ToolStripMenuItem
			// 
			this->x05ToolStripMenuItem->Name = L"x05ToolStripMenuItem";
			this->x05ToolStripMenuItem->Size = System::Drawing::Size(123, 22);
			this->x05ToolStripMenuItem->Text = L"320x240";
			this->x05ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::x05ToolStripMenuItem_Click);
			// 
			// x10ToolStripMenuItem
			// 
			this->x10ToolStripMenuItem->Checked = true;
			this->x10ToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->x10ToolStripMenuItem->Name = L"x10ToolStripMenuItem";
			this->x10ToolStripMenuItem->Size = System::Drawing::Size(123, 22);
			this->x10ToolStripMenuItem->Text = L"640x480";
			this->x10ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::x10ToolStripMenuItem_Click);
			// 
			// �w���vToolStripMenuItem
			// 
			this->�w���vToolStripMenuItem->Name = L"�w���vToolStripMenuItem";
			this->�w���vToolStripMenuItem->Size = System::Drawing::Size(48, 20);
			this->�w���vToolStripMenuItem->Text = L"�w���v";
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Location = System::Drawing::Point(0, 24);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(640, 480);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// �����ʑ�ToolStripMenuItem
			// 
			this->�����ʑ�ToolStripMenuItem->Name = L"�����ʑ�ToolStripMenuItem";
			this->�����ʑ�ToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->�����ʑ�ToolStripMenuItem->Text = L"�����ʑ�";
			this->�����ʑ�ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::�����ʑ�ToolStripMenuItem_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(640, 504);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &MainForm::MainForm_FormClosed);
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		//	MainForm�̐ݒ�
		System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void MainForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
		System::Void MainForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e);
		//	�t�@�C��
		System::Void �I��ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		//	�E�C���h�E
		System::Void x05ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void x10ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		//	�R���g���[��->�J����
		System::Void ����ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void �ꎞ��~ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void �I��ToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void �X�i�b�v��ۑ�ToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e);
		//	�R���g���[��->���[�h
		System::Void �U��ONToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void �f�v�X�}�b�vToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		//	�R���g���[��->3D���f��	
		System::Void ��ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void ������ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void �~��ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void �~��ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void �g�[���XToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void �����ʑ�ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void �e�B�[�|�b�gToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		//	�ݒ�
		System::Void �V���A���|�[�gToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void serialPort1_DataReceived(System::Object^  sender, System::IO::Ports::SerialDataReceivedEventArgs^  e);
		//	���̑�
		System::Void draw3DObject(int objNum);
};
}

//#include "ARToolKitAdapter.h"
//#include "OpenCVAdapter.h"
#include "ARTKBasedOpenCVWrapper.h"

//----------------------
//	�K�v�ȃO���[�o���ϐ�
//----------------------
extern bool		camStop;		//	�ꎞ��~����true
extern bool		camIsOpen;		//	�J�������J���Ă����Ԃ�true
extern cv::Mat	depthMap;		//	�擾�����f�v�X�}�b�v
extern cv::Mat	ZMap;			//	����
extern bool		serialPorrtIsSet;

System::Void winShowImage(System::Windows::Forms::PictureBox^ picturebox, cv::Mat img);
void lighting(void);
System::Void setMotorState(Mat& zmap);