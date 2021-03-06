//---------------------------------------------------------------------------
#include <iostream>
#include <vcl.h>
#include <string>
#include <vector>
#pragma hdrstop
#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{}

std::string __fastcall TForm1::GetAlphabet()
{
        if(RadioButton1->Checked)
                return "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        else if(RadioButton2->Checked)
                //alphabet = "�����帺��賿��������������������������å�Ũ���Ȳ������������������������";
                return "��������������������������������";
        else
                return "�����帺��賿��������������������������å�Ũ���Ȳ������������������������abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

        // ������ �����-������� �������
        //alphabet+=" -_.,()!?";
}
//---------------------------------------------------------------------------

std::string Encipherment(std::string text, std::string primarykey, std::string alphabet)
{ 
        // ��������� ���� (��������� ����+��������)
        std::string key = primarykey+text.substr(0,text.length() - primarykey.length());

        // ����������
        std::string result="";
        int index1, index2, text_len = text.length(), alph_len = alphabet.length();
        for(int i=0;i<text_len;i++)
        {
                // ������ � ������ �-��� ������ ������
                if((index1 = alphabet.find(text[i],0)) != -1)
                {
                        // ������ � ������ �-��� ������ �����
                        if((index2 = alphabet.find(key[i],0)) != -1)
                        {
                                index1 += index2;
                                index1 %= alph_len;
                                result += alphabet[index1];
                        }
                        // ���� ������ ������� ���� � ������
                        else
                        {
                                key.erase(i,1);
                                i--;
                        }
                }
                // ���� ������ ������� ���� � ������
                else
                {
                        text.erase(i,1);
                        text_len--;
                        i--;
                }
        }
        return result;
}
//---------------------------------------------------------------------------

std::string Decipherment(std::string text, std::string key, std::string alphabet)
{
        // �������������
        std::string result="";
        int index1, index2, text_len = text.length(), alph_len = alphabet.length();
        for(int i=0;i<text_len;i++)
        {
                // ������ � ������ �-��� ������ ������
                if((index1 = alphabet.find(text[i],0)) != -1)
                {
                        // ������ � ������ �-��� ������ �����
                        if((index2 = alphabet.find(key[i],0)) != -1)
                        {
                                index1-=index2;
                                while(index1<0)
                                        index1+=alph_len;
                                result += alphabet[index1];
                                key += alphabet[index1];
                        }
                        // ���� ������ ������� ���� � ������
                        else
                        {
                                key.erase(i,1);
                                i--;
                        }
                }
                // ���� ������ ������� ���� � ������
                else
                {
                        text.erase(i,1);
                        text_len--;
                        i--;
                }
        }
        return result;
}

//---------------����������--------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
        // ���������� �������� �����
        std::string txt = Memo1->Text.c_str();
        std::string pr_key = Edit2->Text.c_str();

        std:string res = Encipherment(txt,pr_key,GetAlphabet());

        //��������� ����������
        Form2->Memo1->Text = res.c_str();
        Form2->ShowModal();
}

//--------------�������������------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
        // ���������� �������� �����
        std::string txt = Memo1->Text.c_str();
        std::string pr_key = Edit2->Text.c_str();

        std:string res = Decipherment(txt,pr_key,GetAlphabet());

        //��������� ����������
        Form2->Memo1->Text = res.c_str();
        Form2->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormShow(TObject *Sender)
{
        //Get_blablabla();
}
//---------------------------------------------------------------------------

