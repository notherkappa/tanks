object Form2: TForm2
  Left = 468
  Top = 169
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Map Editor'
  ClientHeight = 512
  ClientWidth = 968
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  OnClick = FormClick
  OnMouseMove = FormMouseMove
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 768
    Top = 0
    Width = 193
    Height = 201
    Caption = 'Palette'
    TabOrder = 0
    OnClick = GroupBox1Click
  end
  object GroupBox2: TGroupBox
    Left = 768
    Top = 200
    Width = 193
    Height = 201
    Caption = 'Sprites'
    TabOrder = 1
    object LabeledEdit1: TLabeledEdit
      Left = 32
      Top = 16
      Width = 121
      Height = 21
      EditLabel.Width = 28
      EditLabel.Height = 13
      EditLabel.Caption = 'Name'
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 0
    end
    object Button1: TButton
      Left = 152
      Top = 12
      Width = 33
      Height = 25
      Caption = 'ADD'
      TabOrder = 1
      OnClick = Button1Click
    end
    object LabeledEdit2: TLabeledEdit
      Left = 32
      Top = 40
      Width = 25
      Height = 21
      EditLabel.Width = 18
      EditLabel.Height = 13
      EditLabel.Caption = 'Left'
      EditLabel.Layout = tlCenter
      LabelPosition = lpLeft
      LabelSpacing = 3
      MaxLength = 3
      TabOrder = 2
      Text = '0'
    end
    object LabeledEdit3: TLabeledEdit
      Left = 80
      Top = 40
      Width = 25
      Height = 21
      EditLabel.Width = 19
      EditLabel.Height = 13
      EditLabel.Caption = 'Top'
      LabelPosition = lpLeft
      LabelSpacing = 3
      MaxLength = 3
      TabOrder = 3
      Text = '0'
    end
    object CheckBox1: TCheckBox
      Left = 112
      Top = 42
      Width = 65
      Height = 17
      Caption = 'Animate'
      Checked = True
      State = cbChecked
      TabOrder = 4
    end
    object ListBox1: TListBox
      Left = 0
      Top = 96
      Width = 193
      Height = 105
      Color = clBtnFace
      ItemHeight = 13
      TabOrder = 5
    end
    object LabeledEdit4: TLabeledEdit
      Left = 56
      Top = 64
      Width = 129
      Height = 21
      EditLabel.Width = 46
      EditLabel.Height = 13
      EditLabel.Caption = 'Animation'
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 6
    end
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = 'sprite'
    Filter = 'Sprites|*.sprite'
    FilterIndex = 0
    InitialDir = 'sprites'
    Left = 776
    Top = 264
  end
end
