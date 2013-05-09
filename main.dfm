object Form1: TForm1
  Left = 267
  Top = 155
  AlphaBlendValue = 127
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  ClientHeight = 512
  ClientWidth = 768
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
end
