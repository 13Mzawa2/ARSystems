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
	private: System::Windows::Forms::ToolStripMenuItem^  スナップを保存ToolStripMenuItem;


	private: System::Windows::Forms::ToolStripMenuItem^  終了ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  編集ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  設定ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  コントロールToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ウィンドウToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ヘルプToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::ToolStripMenuItem^  シリアルポートToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  開くToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  閉じるToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ボーレートToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ポートToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aRToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aRマーカーToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  カメラパラメータToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  モードToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  モデル表示ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  oNToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  oFFToolStripMenuItem;
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

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>


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
			this->スナップを保存ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->終了ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->編集ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->設定ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->シリアルポートToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->開くToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->閉じるToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ボーレートToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ポートToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aRToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aRマーカーToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->カメラパラメータToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->コントロールToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->モードToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->モデル表示ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->oNToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->oFFToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->実験モードToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->カメラToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->入力ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->一時停止ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->スナップを保存ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->終了ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ウィンドウToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ウインドウサイズToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->x05ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->x10ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ヘルプToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->振動子位置表示ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
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
			this->ファイルToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->モデルを開くToolStripMenuItem,
					this->スナップを保存ToolStripMenuItem, this->終了ToolStripMenuItem
			});
			this->ファイルToolStripMenuItem->Name = L"ファイルToolStripMenuItem";
			this->ファイルToolStripMenuItem->Size = System::Drawing::Size(53, 20);
			this->ファイルToolStripMenuItem->Text = L"ファイル";
			// 
			// モデルを開くToolStripMenuItem
			// 
			this->モデルを開くToolStripMenuItem->Name = L"モデルを開くToolStripMenuItem";
			this->モデルを開くToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->モデルを開くToolStripMenuItem->Text = L"モデルを開く";
			// 
			// スナップを保存ToolStripMenuItem
			// 
			this->スナップを保存ToolStripMenuItem->Name = L"スナップを保存ToolStripMenuItem";
			this->スナップを保存ToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->スナップを保存ToolStripMenuItem->Text = L"スナップを保存";
			// 
			// 終了ToolStripMenuItem
			// 
			this->終了ToolStripMenuItem->Name = L"終了ToolStripMenuItem";
			this->終了ToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->終了ToolStripMenuItem->Text = L"終了";
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
			this->シリアルポートToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->開くToolStripMenuItem1,
					this->閉じるToolStripMenuItem, this->ボーレートToolStripMenuItem, this->ポートToolStripMenuItem
			});
			this->シリアルポートToolStripMenuItem->Name = L"シリアルポートToolStripMenuItem";
			this->シリアルポートToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->シリアルポートToolStripMenuItem->Text = L"シリアルポート";
			// 
			// 開くToolStripMenuItem1
			// 
			this->開くToolStripMenuItem1->Name = L"開くToolStripMenuItem1";
			this->開くToolStripMenuItem1->Size = System::Drawing::Size(121, 22);
			this->開くToolStripMenuItem1->Text = L"開く";
			// 
			// 閉じるToolStripMenuItem
			// 
			this->閉じるToolStripMenuItem->Name = L"閉じるToolStripMenuItem";
			this->閉じるToolStripMenuItem->Size = System::Drawing::Size(121, 22);
			this->閉じるToolStripMenuItem->Text = L"閉じる";
			// 
			// ボーレートToolStripMenuItem
			// 
			this->ボーレートToolStripMenuItem->Name = L"ボーレートToolStripMenuItem";
			this->ボーレートToolStripMenuItem->Size = System::Drawing::Size(121, 22);
			this->ボーレートToolStripMenuItem->Text = L"ボーレート";
			// 
			// ポートToolStripMenuItem
			// 
			this->ポートToolStripMenuItem->Name = L"ポートToolStripMenuItem";
			this->ポートToolStripMenuItem->Size = System::Drawing::Size(121, 22);
			this->ポートToolStripMenuItem->Text = L"ポート";
			// 
			// aRToolStripMenuItem
			// 
			this->aRToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->aRマーカーToolStripMenuItem,
					this->カメラパラメータToolStripMenuItem
			});
			this->aRToolStripMenuItem->Name = L"aRToolStripMenuItem";
			this->aRToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->aRToolStripMenuItem->Text = L"AR";
			// 
			// aRマーカーToolStripMenuItem
			// 
			this->aRマーカーToolStripMenuItem->Name = L"aRマーカーToolStripMenuItem";
			this->aRマーカーToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->aRマーカーToolStripMenuItem->Text = L"ARマーカー";
			// 
			// カメラパラメータToolStripMenuItem
			// 
			this->カメラパラメータToolStripMenuItem->Name = L"カメラパラメータToolStripMenuItem";
			this->カメラパラメータToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->カメラパラメータToolStripMenuItem->Text = L"カメラパラメータ";
			// 
			// コントロールToolStripMenuItem
			// 
			this->コントロールToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->モードToolStripMenuItem,
					this->カメラToolStripMenuItem
			});
			this->コントロールToolStripMenuItem->Name = L"コントロールToolStripMenuItem";
			this->コントロールToolStripMenuItem->Size = System::Drawing::Size(73, 20);
			this->コントロールToolStripMenuItem->Text = L"コントロール";
			// 
			// モードToolStripMenuItem
			// 
			this->モードToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->モデル表示ToolStripMenuItem,
					this->振動子位置表示ToolStripMenuItem, this->実験モードToolStripMenuItem
			});
			this->モードToolStripMenuItem->Name = L"モードToolStripMenuItem";
			this->モードToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->モードToolStripMenuItem->Text = L"モード";
			// 
			// モデル表示ToolStripMenuItem
			// 
			this->モデル表示ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->oNToolStripMenuItem,
					this->oFFToolStripMenuItem
			});
			this->モデル表示ToolStripMenuItem->Name = L"モデル表示ToolStripMenuItem";
			this->モデル表示ToolStripMenuItem->Size = System::Drawing::Size(158, 22);
			this->モデル表示ToolStripMenuItem->Text = L"モデル表示";
			// 
			// oNToolStripMenuItem
			// 
			this->oNToolStripMenuItem->Checked = true;
			this->oNToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->oNToolStripMenuItem->Name = L"oNToolStripMenuItem";
			this->oNToolStripMenuItem->Size = System::Drawing::Size(97, 22);
			this->oNToolStripMenuItem->Text = L"ON";
			// 
			// oFFToolStripMenuItem
			// 
			this->oFFToolStripMenuItem->Name = L"oFFToolStripMenuItem";
			this->oFFToolStripMenuItem->Size = System::Drawing::Size(97, 22);
			this->oFFToolStripMenuItem->Text = L"OFF";
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
			this->入力ToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->入力ToolStripMenuItem->Text = L"入力";
			// 
			// 一時停止ToolStripMenuItem
			// 
			this->一時停止ToolStripMenuItem->Name = L"一時停止ToolStripMenuItem";
			this->一時停止ToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->一時停止ToolStripMenuItem->Text = L"一時停止";
			// 
			// スナップを保存ToolStripMenuItem1
			// 
			this->スナップを保存ToolStripMenuItem1->Name = L"スナップを保存ToolStripMenuItem1";
			this->スナップを保存ToolStripMenuItem1->Size = System::Drawing::Size(152, 22);
			this->スナップを保存ToolStripMenuItem1->Text = L"スナップを保存";
			// 
			// 終了ToolStripMenuItem1
			// 
			this->終了ToolStripMenuItem1->Name = L"終了ToolStripMenuItem1";
			this->終了ToolStripMenuItem1->Size = System::Drawing::Size(152, 22);
			this->終了ToolStripMenuItem1->Text = L"終了";
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
			this->ウインドウサイズToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->ウインドウサイズToolStripMenuItem->Text = L"ウインドウサイズ";
			// 
			// x05ToolStripMenuItem
			// 
			this->x05ToolStripMenuItem->Name = L"x05ToolStripMenuItem";
			this->x05ToolStripMenuItem->Size = System::Drawing::Size(123, 22);
			this->x05ToolStripMenuItem->Text = L"320x240";
			// 
			// x10ToolStripMenuItem
			// 
			this->x10ToolStripMenuItem->Checked = true;
			this->x10ToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->x10ToolStripMenuItem->Name = L"x10ToolStripMenuItem";
			this->x10ToolStripMenuItem->Size = System::Drawing::Size(123, 22);
			this->x10ToolStripMenuItem->Text = L"640x480";
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
			// 振動子位置表示ToolStripMenuItem
			// 
			this->振動子位置表示ToolStripMenuItem->Name = L"振動子位置表示ToolStripMenuItem";
			this->振動子位置表示ToolStripMenuItem->Size = System::Drawing::Size(158, 22);
			this->振動子位置表示ToolStripMenuItem->Text = L"振動子位置表示";
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
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void MainForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
};
}
