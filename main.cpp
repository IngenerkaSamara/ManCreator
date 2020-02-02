#include "TXLib.h"

void drawButton(int x, int y, const char* text)
{
    txSetColor(TX_BLACK, 4);
    txSetFillColor(TX_YELLOW);
    txSelectFont("Comic Sans MS", 40);
    txRectangle(x, y, x + 200, y + 100);
    txDrawText (x, y, x + 200, y + 100, text);
}

int main()
{
    txCreateWindow(1200,800);

    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetFillColor(TX_WHITE);
        txClear();

        txSetColor(TX_BLACK);
        txSelectFont("Comic Sans MS", 60);
        txTextOut(200,700, "1");


        drawButton(100, 0, "Уши");
        drawButton(300, 0, "Прически");


        txSleep(10);
        txEnd();
    }

    return 0;
}
