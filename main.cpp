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
    int width;
    int height;
};


void drawPicture(Picture pct)
{
    Win32::TransparentBlt(txDC(), pct.x, pct.y, 100, 100, pct.image, 0, 0, pct.width, pct.height, TX_WHITE);
}


int main()
{
    txCreateWindow(1200,800);


    Picture leftPictures[10];
    leftPictures[0] = {100, 100, txLoadImage("Pictures/Íîñ/Íîñ1.bmp"), 126, 104};
    leftPictures[1] = {100, 250, txLoadImage("Pictures/Íîñ/Íîñ2.bmp"), 100, 100};
    leftPictures[2] = {100, 400, txLoadImage("Pictures/Íîñ/Íîñ3.bmp"), 100, 100};
    leftPictures[3] = {100, 100, txLoadImage("Pictures/Âîëîñû/Âîëîñû1.bmp"), 400, 283};
    leftPictures[4] = {100, 250, txLoadImage("Pictures/Âîëîñû/Âîëîñû2.bmp"), 400, 309};
    leftPictures[5] = {100, 400, txLoadImage("Pictures/Âîëîñû/Âîëîñû3.bmp"), 448, 558};



    Button btn[10];
    btn[0] = {100, 0, "Îâàë ëèöà"};
    btn[1] = {300, 0, "Óøè"};
    btn[2] = {500, 0, "Ïðè÷åñêè"};
    btn[3] = {700, 0, "Ãëàçà"};

    bool nosVisible = false;
    bool volosyVisible = false;

    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetFillColor(TX_YELLOW);
        txClear();


        //Ðèñîâàíèå êíîïîê
        for (int nKnopki = 0; nKnopki < 4; nKnopki++)
        {
            drawButton(btn[nKnopki]);
        }


        //Íîñû
        if (txMouseButtons() == 1 &&
            txMouseX() >= btn2.x &&
            txMouseX() <= btn2.x + 200 &&
            txMouseY() >= btn2.y &&
            txMouseY() <= btn2.y + 100)
        {
            nosVisible = true;
            volosyVisible = false;
        }

        if (nosVisible)
        {
            drawPicture(leftPictures[0]);
            drawPicture(leftPictures[1]);
            drawPicture(leftPictures[2]);
        }
        if (volosyVisible)
        {
            drawPicture(leftPictures[3]);
            drawPicture(leftPictures[4]);
            drawPicture(leftPictures[5]);
        }


        //Âîëîñû
        if (txMouseButtons() == 1 &&
            txMouseX() >= btn3.x &&
            txMouseX() <= btn3.x + 200 &&
            txMouseY() >= btn3.y &&
            txMouseY() <= btn3.y + 100)
        {
            nosVisible = false;
            volosyVisible = true;
        }

        txSleep(10);
        txEnd();
    }


    return 0;
}
