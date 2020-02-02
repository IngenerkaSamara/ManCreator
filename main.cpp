#include "TXLib.h"

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

        txSleep(10);
        txEnd();
    }

    return 0;
}
