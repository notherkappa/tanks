object Form1: TForm1
  Left = 490
  Top = 152
  AlphaBlendValue = 127
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  ClientHeight = 512
  ClientWidth = 952
  Color = clBtnFace
  TransparentColorValue = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyPress = FormKeyPress
  OnMouseMove = FormMouseMove
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 772
    Top = 0
    Width = 185
    Height = 513
    Caption = 'Statistic'
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 16
      Width = 45
      Height = 20
      Caption = 'Level: '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 8
      Top = 40
      Width = 76
      Height = 20
      Caption = 'Lives Left: '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel
      Left = 8
      Top = 64
      Width = 76
      Height = 20
      Caption = 'SCORES: '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label4: TLabel
      Left = 16
      Top = 152
      Width = 142
      Height = 29
      Caption = 'GAME OVER'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -24
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      Visible = False
    end
    object Label5: TLabel
      Left = 96
      Top = 84
      Width = 30
      Height = 20
      Caption = 'HP: '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object ProgressBar1: TProgressBar
      Left = 8
      Top = 88
      Width = 81
      Height = 17
      Min = 0
      Max = 100
      Smooth = True
      TabOrder = 0
    end
  end
  object RenderTestTimerr: TTimer
    Interval = 1
    OnTimer = RenderTestTimerrTimer
    Left = 8
    Top = 8
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 1
    OnTimer = Timer1Timer
    Left = 40
    Top = 8
  end
  object GTimer: TTimer
    Enabled = False
    Interval = 1
    OnTimer = GTimerTimer
    Left = 72
    Top = 8
  end
  object Timer2: TTimer
    OnTimer = Timer2Timer
    Left = 104
    Top = 8
  end
end
