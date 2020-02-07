object Form2: TForm2
  Left = 536
  Top = 226
  BorderIcons = [biSystemMenu]
  BorderStyle = bsToolWindow
  Caption = 'O programie'
  ClientHeight = 220
  ClientWidth = 281
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 88
    Width = 257
    Height = 25
    AutoSize = False
    Caption = 'Wykonawca:  Katarzyna Niemiec'
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Cambria'
    Font.Style = []
    ParentFont = False
    Layout = tlCenter
  end
  object Label2: TLabel
    Left = 8
    Top = 128
    Width = 257
    Height = 25
    AutoSize = False
    Caption = 'Data wydania: 10.02.2020'
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Cambria'
    Font.Style = []
    ParentFont = False
    Layout = tlCenter
  end
  object Label3: TLabel
    Left = 7
    Top = 8
    Width = 250
    Height = 25
    AutoSize = False
    Caption = 'Nazwa:   PingPong '
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Cambria'
    Font.Style = []
    ParentFont = False
    Layout = tlCenter
  end
  object Label4: TLabel
    Left = 7
    Top = 48
    Width = 258
    Height = 25
    AutoSize = False
    Caption = 'Wersja:   v.1. '
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Cambria'
    Font.Style = []
    ParentFont = False
    Layout = tlCenter
  end
  object Button1: TButton
    Left = 104
    Top = 176
    Width = 75
    Height = 25
    Cursor = crHandPoint
    Caption = 'OK'
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Cambria'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = Button1Click
  end
end
