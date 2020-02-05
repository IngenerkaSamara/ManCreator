#include "TXLib.h"

struct Button
{
    int x;
    int y;
    const char* text;

    void drawButton()
    {
        txSetColor(TX_BLACK, 4);
        txSetFillColor(TX_YELLOW);
        txSelectFont("Comic Sans MS", 40);
        txRectangle(x, y, x + 200, y + 100);
        txDrawText (x, y, x + 200, y + 100, text);
    }
};

void drawButton(Button btn)
{
    txSetColor(TX_BLACK, 4);
    txSetFillColor(TX_YELLOW);
    txSelectFont("Comic Sans MS", 40);
    txRectangle(btn.x, btn.y, btn.x + 200, btn.y + 100);
    txDrawText (btn.x, btn.y, btn.x + 200, btn.y + 100, btn.text);
}



struct Picture
{
    int x;
    int y;
    HDC image;
};


int main()
{
    txCreateWindow(1200,800);

    HDC nos1 = txLoadImage("Pictures/Нос/Нос1.bmp");
    HDC nos2 = txLoadImage("Pictures/Нос/Нос2.bmp");
    HDC nos3 = txLoadImage("Pictures/Нос/Нос3.bmp");


    HDC volosy1 = txLoadImage("Pictures/Волосы/Волосы1.bmp");
    HDC volosy2 = txLoadImage("Pictures/Волосы/Волосы2.bmp");
    HDC volosy3 = txLoadImage("Pictures/Волосы/Волосы3.bmp");

    Button btn1 = {100, 0, "Овал лица"};
    Button btn2 = {300, 0, "Уши"};
    Button btn3 = {500, 0, "Прически"};
    Button btn4 = {700, 0, "Глаза"};

    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetFillColor(TX_YELLOW);
        txClear();

        txTransparentBlt(txDC(), 0, 100, 126, 104, nos1, 0, 0, TX_WHITE);
        txTransparentBlt(txDC(), 0, 250, 100, 100, nos2, 0, 0, TX_WHITE);
        txTransparentBlt(txDC(), 0, 400, 100, 100, nos3, 0, 0, TX_WHITE);

        txSetColor(TX_BLACK);
        txSelectFont("Comic Sans MS", 60);
        txTextOut(200,700, "1");

        drawButton(btn1);
        drawButton(btn2);
        drawButton(btn3);
        drawButton(btn4);


        if (txMouseButtons() == 1 &&
            txMouseX() >= 500 &&
            txMouseX() <= 700 &&
            txMouseY() >= 0 &&
            txMouseY() <= 100)
        {
            txTransparentBlt(txDC(), 100, 100, 400, 283, volosy1, 0, 0, TX_WHITE);
        }

        txSleep(10);
        txEnd();
    }

    txDeleteDC(nos1);
    txDeleteDC(nos2);
    txDeleteDC(nos3);
    txDeleteDC(volosy1);
    txDeleteDC(volosy2);
    txDeleteDC(volosy3);

    return 0;
}
