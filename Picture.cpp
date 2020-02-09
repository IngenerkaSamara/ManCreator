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
