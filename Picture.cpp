#include "TXLib.h"
#include <conio.h>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


struct Picture
{
    int x;
    int y;
    string adress;
    HDC image;
    int src_width;
    int src_height;
    bool visible;
    string category;
    int width;
    int height;
};

int readFromDirectory(string adress, Picture leftPictures[], int COUNT_PICS)
{
    DIR *dfd;
    struct dirent *dp;
    dfd=opendir(adress.c_str());
    int lastY = 100;

    while((dp=readdir(dfd)) != NULL )
    {
        if (strlen(dp->d_name) > 4)
        {
            leftPictures[COUNT_PICS].y = lastY;
            leftPictures[COUNT_PICS].adress = adress + (string)(dp->d_name);
            COUNT_PICS++;
            lastY += 150;
        }
    }

    closedir(dfd);

    return COUNT_PICS;
}


int getHeight(string adress)
{
    FILE *f1 = fopen(adress.c_str(), "rb");

    unsigned char headerinfo[54];
    fread(headerinfo, sizeof(unsigned char), 54, f1);

    int height = *(int*)&headerinfo[22];

    return height;
}

int getWidth(string adress)
{
    FILE *f1 = fopen(adress.c_str(), "rb");

    unsigned char headerinfo[54];
    fread(headerinfo, sizeof(unsigned char), 54, f1);

    int width = *(int*)&headerinfo[18];

    return width;
}

void drawPicture(Picture pct)
{
    if (pct.visible)
    {
        Win32::TransparentBlt(txDC(), pct.x, pct.y, pct.width, pct.height, pct.image, 0, 0, pct.src_width, pct.src_height, TX_WHITE);
    }
}

void drawAllPictures(Picture leftPictures[], const int COUNT_PICS)
{
    for (int nPict = 0; nPict < COUNT_PICS; nPict++)
    {
        drawPicture(leftPictures[nPict]);
    }
}

void deleteAll(Picture leftPictures[], Picture centerPictures[], const int COUNT_PICS)
{
    for (int nPict = 0; nPict < COUNT_PICS; nPict++)
    {
        txDeleteDC(centerPictures[nPict].image);
        txDeleteDC(leftPictures[nPict].image);
    }
}

void movePicture(Picture centerPictures[], int nomer_vybora)
{
    if (GetAsyncKeyState(VK_LEFT))
    {
        centerPictures[nomer_vybora].x -= 3;
    }
    if (GetAsyncKeyState(VK_RIGHT))
    {
        centerPictures[nomer_vybora].x += 3;
    }
    if (GetAsyncKeyState(VK_UP))
    {
        centerPictures[nomer_vybora].y -= 3;
    }
    if (GetAsyncKeyState(VK_DOWN))
    {
        centerPictures[nomer_vybora].y += 3;
    }

    if (GetAsyncKeyState(VK_OEM_PLUS) && centerPictures[nomer_vybora].width < 600)
    {
        centerPictures[nomer_vybora].width = centerPictures[nomer_vybora].width * 1.02;
        centerPictures[nomer_vybora].height = centerPictures[nomer_vybora].height * 1.02;
    }
    if (GetAsyncKeyState(VK_OEM_MINUS) && centerPictures[nomer_vybora].width > 20)
    {
        centerPictures[nomer_vybora].width = centerPictures[nomer_vybora].width * 0.98;
        centerPictures[nomer_vybora].height = centerPictures[nomer_vybora].height * 0.98;
    }
}



inline int GetFilePointer(HANDLE FileHandle){
    return SetFilePointer(FileHandle, 0, 0, FILE_CURRENT);
}

bool SaveBMPFile(char *filename, HBITMAP bitmap, HDC bitmapDC, int width, int height){
    bool Success=0;
    HBITMAP OffscrBmp=NULL;
    HDC OffscrDC=NULL;
    LPBITMAPINFO lpbi=NULL;
    LPVOID lpvBits=NULL;
    HANDLE BmpFile=INVALID_HANDLE_VALUE;
    BITMAPFILEHEADER bmfh;
    if ((OffscrBmp = CreateCompatibleBitmap(bitmapDC, width, height)) == NULL)
        return 0;
    if ((OffscrDC = CreateCompatibleDC(bitmapDC)) == NULL)
        return 0;
    HBITMAP OldBmp = (HBITMAP)SelectObject(OffscrDC, OffscrBmp);
    BitBlt(OffscrDC, 0, 0, width, height, bitmapDC, 0, 0, SRCCOPY);
    if ((lpbi = (LPBITMAPINFO)(new char[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)])) == NULL)
        return 0;
    ZeroMemory(&lpbi->bmiHeader, sizeof(BITMAPINFOHEADER));
    lpbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    SelectObject(OffscrDC, OldBmp);
    if (!GetDIBits(OffscrDC, OffscrBmp, 0, height, NULL, lpbi, DIB_RGB_COLORS))
        return 0;
    if ((lpvBits = new char[lpbi->bmiHeader.biSizeImage]) == NULL)
        return 0;
    if (!GetDIBits(OffscrDC, OffscrBmp, 0, height, lpvBits, lpbi, DIB_RGB_COLORS))
        return 0;
    if ((BmpFile = CreateFile(filename,
                        GENERIC_WRITE,
                        0, NULL,
                        CREATE_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL)) == INVALID_HANDLE_VALUE)
        return 0;
    DWORD Written;
    bmfh.bfType = 19778;
    bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
    if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
        return 0;
    if (Written < sizeof(bmfh))
        return 0;
    if (!WriteFile(BmpFile, &lpbi->bmiHeader, sizeof(BITMAPINFOHEADER), &Written, NULL))
        return 0;
    if (Written < sizeof(BITMAPINFOHEADER))
        return 0;
    int PalEntries;
    if (lpbi->bmiHeader.biCompression == BI_BITFIELDS)
        PalEntries = 3;
    else PalEntries = (lpbi->bmiHeader.biBitCount <= 8) ?
                      (int)(1 << lpbi->bmiHeader.biBitCount) : 0;
    if(lpbi->bmiHeader.biClrUsed)
    PalEntries = lpbi->bmiHeader.biClrUsed;
    if(PalEntries){
    if (!WriteFile(BmpFile, &lpbi->bmiColors, PalEntries * sizeof(RGBQUAD), &Written, NULL))
        return 0;
        if (Written < PalEntries * sizeof(RGBQUAD))
            return 0;
    }
    bmfh.bfOffBits = GetFilePointer(BmpFile);
    if (!WriteFile(BmpFile, lpvBits, lpbi->bmiHeader.biSizeImage, &Written, NULL))
        return 0;
    if (Written < lpbi->bmiHeader.biSizeImage)
        return 0;
    bmfh.bfSize = GetFilePointer(BmpFile);
    SetFilePointer(BmpFile, 0, 0, FILE_BEGIN);
    if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
        return 0;
    if (Written < sizeof(bmfh))
        return 0;


    CloseHandle (BmpFile);

    delete [] (char*)lpvBits;
    delete [] lpbi;

    DeleteDC (OffscrDC);
    DeleteObject (OffscrBmp);


    return 1;
}

bool ScreenCapture(int x, int y, int width, int height, char *filename, HWND hwnd) {


    HDC hDC = Win32::GetDC(hwnd);
    HDC hDc = CreateCompatibleDC(hDC);


    HBITMAP hBmp = CreateCompatibleBitmap(hDC, width, height);


    HGDIOBJ old= SelectObject(hDc, hBmp);
    BitBlt(hDc, 0, 0, width, height, hDC, x, y, SRCCOPY);

    bool ret = SaveBMPFile(filename, hBmp, hDc, width, height);


    SelectObject(hDc, old);

    DeleteObject(hBmp);

    DeleteDC (hDc);
    ReleaseDC (hwnd, hDC);

    return ret;
}
