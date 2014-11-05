#pragma once

namespace VirtualTouch {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MainForm の概要
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
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
	private: System::Windows::Forms::ToolStripMenuItem^  ファイルToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  モデルを開くToolStripMenuItem;



	private: System::Windows::Forms::ToolStripMenuItem^  終了ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  編集ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  設定ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  コントロールToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ウィンドウToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ヘルプToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::ToolStripMenuItem^  シリアルポートToolStripMenuItem;




	private: System::Windows::Forms::ToolStripMenuItem^  aRToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aRマーカーToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  カメラパラメータToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  モードToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  モデル表示ToolStripMenuItem;


	private: System::Windows::Forms::ToolStripMenuItem^  実験モードToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  カメラToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  入力ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  一時停止ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  スナップを保存ToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  終了ToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  ウインドウサイズToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  x05ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  x10ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  振動子位置表示ToolStripMenuItem;

	protected:
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::ToolStripMenuItem^  振動ONToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  デプスマップToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  dモデルToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  球ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  立方体ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  円柱ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  円錐ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ティーポットToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  トーラスToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  正八面体ToolStripMenuItem;

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->ファイルToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->モデルを開くToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->終了ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->編集ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->設定ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->シリアルポートToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aRToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aRマーカーToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->カメラパラメータToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->コントロールToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->モードToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->モデル表示ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->振動子位置表示ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->振動ONToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->デプスマップToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->実験モードToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->カメラToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->入力ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->一時停止ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->スナップを保存ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->終了ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dモデルToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->球ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->立方体ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->円柱ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->円錐ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->トーラスToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ティーポットToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ウィンドウToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ウインドウサイズToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->x05ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->x10ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ヘルプToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->正八面体ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
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
				this->ファイルToolStripMenuItem,
					this->編集ToolStripMenuItem, this->設定ToolStripMenuItem, this->コントロールToolStripMenuItem, this->ウィンドウToolStripMenuItem, this->ヘルプToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(640, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// ファイルToolStripMenuItem
			// 
			this->ファイルToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->モデルを開くToolStripMenuItem,
					this->終了ToolStripMenuItem
			});
			this->ファイルToolStripMenuItem->Name = L"ファイルToolStripMenuItem";
			this->ファイルToolStripMenuItem->Size = System::Drawing::Size(53, 20);
			this->ファイルToolStripMenuItem->Text = L"ファイル";
			// 
			// モデルを開くToolStripMenuItem
			// 
			this->モデルを開くToolStripMenuItem->Name = L"モデルを開くToolStripMenuItem";
			this->モデルを開くToolStripMenuItem->Size = System::Drawing::Size(130, 22);
			this->モデルを開くToolStripMenuItem->Text = L"モデルを開く";
			// 
			// 終了ToolStripMenuItem
			// 
			this->終了ToolStripMenuItem->Name = L"終了ToolStripMenuItem";
			this->終了ToolStripMenuItem->Size = System::Drawing::Size(130, 22);
			this->終了ToolStripMenuItem->Text = L"終了";
			this->終了ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::終了ToolStripMenuItem_Click);
			// 
			// 編集ToolStripMenuItem
			// 
			this->編集ToolStripMenuItem->Name = L"編集ToolStripMenuItem";
			this->編集ToolStripMenuItem->Size = System::Drawing::Size(43, 20);
			this->編集ToolStripMenuItem->Text = L"編集";
			// 
			// 設定ToolStripMenuItem
			// 
			this->設定ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->シリアルポートToolStripMenuItem,
					this->aRToolStripMenuItem
			});
			this->設定ToolStripMenuItem->Name = L"設定ToolStripMenuItem";
			this->設定ToolStripMenuItem->Size = System::Drawing::Size(43, 20);
			this->設定ToolStripMenuItem->Text = L"設定";
			// 
			// シリアルポートToolStripMenuItem
			// 
			this->シリアルポートToolStripMenuItem->Name = L"シリアルポートToolStripMenuItem";
			this->シリアルポートToolStripMenuItem->Size = System::Drawing::Size(138, 22);
			this->シリアルポートToolStripMenuItem->Text = L"シリアルポート";
			this->シリアルポートToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::シリアルポートToolStripMenuItem_Click);
			// 
			// aRToolStripMenuItem
			// 
			this->aRToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->aRマーカーToolStripMenuItem,
					this->カメラパラメータToolStripMenuItem
			});
			this->aRToolStripMenuItem->Name = L"aRToolStripMenuItem";
			this->aRToolStripMenuItem->Size = System::Drawing::Size(138, 22);
			this->aRToolStripMenuItem->Text = L"AR";
			// 
			// aRマーカーToolStripMenuItem
			// 
			this->aRマーカーToolStripMenuItem->Name = L"aRマーカーToolStripMenuItem";
			this->aRマーカーToolStripMenuItem->Size = System::Drawing::Size(143, 22);
			this->aRマーカーToolStripMenuItem->Text = L"ARマーカー";
			// 
			// カメラパラメータToolStripMenuItem
			// 
			this->カメラパラメータToolStripMenuItem->Name = L"カメラパラメータToolStripMenuItem";
			this->カメラパラメータToolStripMenuItem->Size = System::Drawing::Size(143, 22);
			this->カメラパラメータToolStripMenuItem->Text = L"カメラパラメータ";
			// 
			// コントロールToolStripMenuItem
			// 
			this->コントロールToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->モードToolStripMenuItem,
					this->カメラToolStripMenuItem, this->dモデルToolStripMenuItem
			});
			this->コントロールToolStripMenuItem->Name = L"コントロールToolStripMenuItem";
			this->コントロールToolStripMenuItem->Size = System::Drawing::Size(73, 20);
			this->コントロールToolStripMenuItem->Text = L"コントロール";
			// 
			// モードToolStripMenuItem
			// 
			this->モードToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->モデル表示ToolStripMenuItem,
					this->振動子位置表示ToolStripMenuItem, this->振動ONToolStripMenuItem, this->デプスマップToolStripMenuItem, this->実験モードToolStripMenuItem
			});
			this->モードToolStripMenuItem->Name = L"モードToolStripMenuItem";
			this->モードToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->モードToolStripMenuItem->Text = L"モード";
			// 
			// モデル表示ToolStripMenuItem
			// 
			this->モデル表示ToolStripMenuItem->Checked = true;
			this->モデル表示ToolStripMenuItem->CheckOnClick = true;
			this->モデル表示ToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->モデル表示ToolStripMenuItem->Name = L"モデル表示ToolStripMenuItem";
			this->モデル表示ToolStripMenuItem->Size = System::Drawing::Size(158, 22);
			this->モデル表示ToolStripMenuItem->Text = L"モデル表示";
			// 
			// 振動子位置表示ToolStripMenuItem
			// 
			this->振動子位置表示ToolStripMenuItem->Checked = true;
			this->振動子位置表示ToolStripMenuItem->CheckOnClick = true;
			this->振動子位置表示ToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->振動子位置表示ToolStripMenuItem->Name = L"振動子位置表示ToolStripMenuItem";
			this->振動子位置表示ToolStripMenuItem->Size = System::Drawing::Size(158, 22);
			this->振動子位置表示ToolStripMenuItem->Text = L"振動子位置表示";
			// 
			// 振動ONToolStripMenuItem
			// 
			this->振動ONToolStripMenuItem->Name = L"振動ONToolStripMenuItem";
			this->振動ONToolStripMenuItem->Size = System::Drawing::Size(158, 22);
			this->振動ONToolStripMenuItem->Text = L"振動ON";
			this->振動ONToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::振動ONToolStripMenuItem_Click);
			// 
			// デプスマップToolStripMenuItem
			// 
			this->デプスマップToolStripMenuItem->CheckOnClick = true;
			this->デプスマップToolStripMenuItem->Name = L"デプスマップToolStripMenuItem";
			this->デプスマップToolStripMenuItem->Size = System::Drawing::Size(158, 22);
			this->デプスマップToolStripMenuItem->Text = L"デプスマップ";
			this->デプスマップToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::デプスマップToolStripMenuItem_Click);
			// 
			// 実験モードToolStripMenuItem
			// 
			this->実験モードToolStripMenuItem->Name = L"実験モードToolStripMenuItem";
			this->実験モードToolStripMenuItem->Size = System::Drawing::Size(158, 22);
			this->実験モードToolStripMenuItem->Text = L"実験モード";
			// 
			// カメラToolStripMenuItem
			// 
			this->カメラToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->入力ToolStripMenuItem,
					this->一時停止ToolStripMenuItem, this->スナップを保存ToolStripMenuItem1, this->終了ToolStripMenuItem1
			});
			this->カメラToolStripMenuItem->Name = L"カメラToolStripMenuItem";
			this->カメラToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->カメラToolStripMenuItem->Text = L"カメラ";
			// 
			// 入力ToolStripMenuItem
			// 
			this->入力ToolStripMenuItem->Name = L"入力ToolStripMenuItem";
			this->入力ToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->入力ToolStripMenuItem->Text = L"入力";
			this->入力ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::入力ToolStripMenuItem_Click);
			// 
			// 一時停止ToolStripMenuItem
			// 
			this->一時停止ToolStripMenuItem->Name = L"一時停止ToolStripMenuItem";
			this->一時停止ToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->一時停止ToolStripMenuItem->Text = L"一時停止";
			this->一時停止ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::一時停止ToolStripMenuItem_Click);
			// 
			// スナップを保存ToolStripMenuItem1
			// 
			this->スナップを保存ToolStripMenuItem1->Name = L"スナップを保存ToolStripMenuItem1";
			this->スナップを保存ToolStripMenuItem1->Size = System::Drawing::Size(142, 22);
			this->スナップを保存ToolStripMenuItem1->Text = L"スナップを保存";
			this->スナップを保存ToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MainForm::スナップを保存ToolStripMenuItem1_Click);
			// 
			// 終了ToolStripMenuItem1
			// 
			this->終了ToolStripMenuItem1->Name = L"終了ToolStripMenuItem1";
			this->終了ToolStripMenuItem1->Size = System::Drawing::Size(142, 22);
			this->終了ToolStripMenuItem1->Text = L"終了";
			this->終了ToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MainForm::終了ToolStripMenuItem1_Click);
			// 
			// dモデルToolStripMenuItem
			// 
			this->dモデルToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
				this->球ToolStripMenuItem,
					this->立方体ToolStripMenuItem, this->円柱ToolStripMenuItem, this->円錐ToolStripMenuItem, this->トーラスToolStripMenuItem, this->正八面体ToolStripMenuItem,
					this->ティーポットToolStripMenuItem
			});
			this->dモデルToolStripMenuItem->Name = L"dモデルToolStripMenuItem";
			this->dモデルToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->dモデルToolStripMenuItem->Text = L"3Dモデル";
			// 
			// 球ToolStripMenuItem
			// 
			this->球ToolStripMenuItem->Name = L"球ToolStripMenuItem";
			this->球ToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->球ToolStripMenuItem->Text = L"球";
			this->球ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::球ToolStripMenuItem_Click);
			// 
			// 立方体ToolStripMenuItem
			// 
			this->立方体ToolStripMenuItem->Name = L"立方体ToolStripMenuItem";
			this->立方体ToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->立方体ToolStripMenuItem->Text = L"立方体";
			this->立方体ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::立方体ToolStripMenuItem_Click);
			// 
			// 円柱ToolStripMenuItem
			// 
			this->円柱ToolStripMenuItem->Name = L"円柱ToolStripMenuItem";
			this->円柱ToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->円柱ToolStripMenuItem->Text = L"円柱";
			this->円柱ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::円柱ToolStripMenuItem_Click);
			// 
			// 円錐ToolStripMenuItem
			// 
			this->円錐ToolStripMenuItem->Name = L"円錐ToolStripMenuItem";
			this->円錐ToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->円錐ToolStripMenuItem->Text = L"円錐";
			this->円錐ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::円錐ToolStripMenuItem_Click);
			// 
			// トーラスToolStripMenuItem
			// 
			this->トーラスToolStripMenuItem->Name = L"トーラスToolStripMenuItem";
			this->トーラスToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->トーラスToolStripMenuItem->Text = L"トーラス";
			this->トーラスToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::トーラスToolStripMenuItem_Click);
			// 
			// ティーポットToolStripMenuItem
			// 
			this->ティーポットToolStripMenuItem->Name = L"ティーポットToolStripMenuItem";
			this->ティーポットToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->ティーポットToolStripMenuItem->Text = L"ティーポット";
			this->ティーポットToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::ティーポットToolStripMenuItem_Click);
			// 
			// ウィンドウToolStripMenuItem
			// 
			this->ウィンドウToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->ウインドウサイズToolStripMenuItem });
			this->ウィンドウToolStripMenuItem->Name = L"ウィンドウToolStripMenuItem";
			this->ウィンドウToolStripMenuItem->Size = System::Drawing::Size(61, 20);
			this->ウィンドウToolStripMenuItem->Text = L"ウィンドウ";
			// 
			// ウインドウサイズToolStripMenuItem
			// 
			this->ウインドウサイズToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->x05ToolStripMenuItem,
					this->x10ToolStripMenuItem
			});
			this->ウインドウサイズToolStripMenuItem->Name = L"ウインドウサイズToolStripMenuItem";
			this->ウインドウサイズToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->ウインドウサイズToolStripMenuItem->Text = L"ウインドウサイズ";
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
			// ヘルプToolStripMenuItem
			// 
			this->ヘルプToolStripMenuItem->Name = L"ヘルプToolStripMenuItem";
			this->ヘルプToolStripMenuItem->Size = System::Drawing::Size(48, 20);
			this->ヘルプToolStripMenuItem->Text = L"ヘルプ";
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
			// 正八面体ToolStripMenuItem
			// 
			this->正八面体ToolStripMenuItem->Name = L"正八面体ToolStripMenuItem";
			this->正八面体ToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->正八面体ToolStripMenuItem->Text = L"正八面体";
			this->正八面体ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::正八面体ToolStripMenuItem_Click);
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
		//	MainFormの設定
		System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void MainForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
		System::Void MainForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e);
		//	ファイル
		System::Void 終了ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		//	ウインドウ
		System::Void x05ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void x10ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		//	コントロール->カメラ
		System::Void 入力ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void 一時停止ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void 終了ToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void スナップを保存ToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e);
		//	コントロール->モード
		System::Void 振動ONToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void デプスマップToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		//	コントロール->3Dモデル	
		System::Void 球ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void 立方体ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void 円柱ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void 円錐ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void トーラスToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void 正八面体ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void ティーポットToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		//	設定
		System::Void シリアルポートToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void serialPort1_DataReceived(System::Object^  sender, System::IO::Ports::SerialDataReceivedEventArgs^  e);
		//	その他
		System::Void setMotorState(void);
		System::Void draw3DObject(int objNum);
};
}

//#include "ARToolKitAdapter.h"
//#include "OpenCVAdapter.h"
#include "ARTKBasedOpenCVWrapper.h"

//----------------------
//	必要なグローバル変数
//----------------------
extern bool		camStop;		//	一時停止中にtrue
extern bool		camIsOpen;		//	カメラが開いている状態でtrue
extern cv::Mat	depthMap;		//	取得したデプスマップ
extern cv::Mat	ZMap;			//	距離
extern bool		serialPorrtIsSet;

System::Void winShowImage(System::Windows::Forms::PictureBox^ picturebox, cv::Mat img);
void lighting(void);