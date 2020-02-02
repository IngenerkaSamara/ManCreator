#include "TXLib.h"

int main()
{
    txCreateWindow(1200,800);

    HDC nos1 = txLoadImage("Нос1.bmp");
    HDC nos2 = txLoadImage("Нос2.bmp");
    HDC nos3 = txLoadImage("Нос3.bmp");

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

        txSleep(10);
        txEnd();
    }

    txDeleteDC(nos1);
    txDeleteDC(nos2);
    txDeleteDC(nos3);

    return 0;
}
