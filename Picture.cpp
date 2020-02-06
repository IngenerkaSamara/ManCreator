#include "TXLib.h"

struct Picture
{
    int x;
    int y;
    HDC image;
    int width;
    int height;
    bool visible;
    string category;
};

void drawPicture(Picture pct)
{
    if (pct.visible)
    {
        Win32::TransparentBlt(txDC(), pct.x, pct.y, 100, 100, pct.image, 0, 0, pct.width, pct.height, TX_WHITE);
    }
}

void drawPicture2(Picture pct)
{
    if (pct.visible)
    {
        Win32::TransparentBlt(txDC(), pct.x, pct.y, pct.width, pct.height, pct.image, 0, 0, pct.width, pct.height, TX_WHITE);
    }
}

void drawAllLeftPictures(Picture leftPictures[], const int COUNT_PICS)
{
    for (int nPict = 0; nPict < COUNT_PICS; nPict++)
    {
        drawPicture(leftPictures[nPict]);
    }
}

void drawAllCenterPictures(Picture centerPictures[], const int COUNT_PICS)
{
    for (int nPict = 0; nPict < COUNT_PICS; nPict++)
    {
        drawPicture2(centerPictures[nPict]);
    }
}


