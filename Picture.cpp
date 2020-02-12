#include "TXLib.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include<stdio.h>
#include<stdlib.h>

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
