/// \file Button.cpp
/// Кнопка
#include "TXLib.h"

///Кнопка
struct Button
{
    ///Левая граница (ширина 150)
    int x;
    ///Верхняя граница (высота 80)
    int y;
    ///Текст
    const char* text;
    ///Категория
    string category;
};

///Рисование кнопки
void drawButton(Button btn)
{
    txSetColor(TX_BLACK, 4);
    txSetFillColor(TX_YELLOW);
    txSelectFont("Comic Sans MS", 32);
    txRectangle(btn.x, btn.y, btn.x + 150, btn.y + 80);
    txDrawText (btn.x, btn.y, btn.x + 150, btn.y + 80, btn.text);
}

///Клик на кнопку
bool click(Button btn)
{
    if (txMouseButtons() == 1 &&
        txMouseX() >= btn.x &&
        txMouseX() <= btn.x + 150 &&
        txMouseY() >= btn.y &&
        txMouseY() <= btn.y + 80)
    {
        return true;
    }
    else
    {
        return false;
    }
}

///Диалог открытия / сохранения файла
string runFileDialog(bool isSave)
{
    string fileName = "";

    OPENFILENAME ofn;       // common dialog box structure
    TCHAR szFile[260] = { 0 };       // if using TCHAR macros

    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = txWindow();
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = ("Text\0*.TXT\0");
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (isSave)
    {
        if (GetSaveFileName(&ofn) == TRUE)
        {
            fileName = ofn.lpstrFile;

            if (fileName.find(".txt") > 1000)
            {
                fileName = fileName + ".txt";
            }
        }
    }
    else
    {
        if (GetOpenFileName(&ofn) == TRUE)
        {
            fileName = ofn.lpstrFile;
        }
    }

    return fileName;
}
