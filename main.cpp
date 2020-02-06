#include "TXLib.h"
#include "Button.cpp"
#include "Picture.cpp"



int main()
{
    txCreateWindow(1200,800);


    const int COUNT_PICS = 9;
    Picture leftPictures[COUNT_PICS];
    leftPictures[0] = {0, 100, txLoadImage("Pictures/Нос/Нос1.bmp"), 126, 104, false, "Нос"};
    leftPictures[1] = {0, 250, txLoadImage("Pictures/Нос/Нос2.bmp"), 100, 100, false, "Нос"};
    leftPictures[2] = {0, 400, txLoadImage("Pictures/Нос/Нос3.bmp"), 100, 100, false, "Нос"};
    leftPictures[3] = {0, 100, txLoadImage("Pictures/Волосы/Волосы1.bmp"), 400, 283, false, "Волосы"};
    leftPictures[4] = {0, 250, txLoadImage("Pictures/Волосы/Волосы2.bmp"), 400, 309, false, "Волосы"};
    leftPictures[5] = {0, 400, txLoadImage("Pictures/Волосы/Волосы3.bmp"), 448, 558, false, "Волосы"};
    leftPictures[6] = {0, 100, txLoadImage("Pictures/Глаза/Глаза1.bmp"), 250, 125, false, "Глаза"};
    leftPictures[7] = {0, 250, txLoadImage("Pictures/Глаза/Глаза2.bmp"), 250, 134, false, "Глаза"};
    leftPictures[8] = {0, 400, txLoadImage("Pictures/Глаза/Глаза3.bmp"), 250, 100, false, "Глаза"};



    Picture centerPictures[COUNT_PICS];
    centerPictures[0] = {350, 380, txLoadImage("Pictures/Нос/Нос1.bmp"), 126, 104, false, "Нос"};
    centerPictures[1] = {350, 380, txLoadImage("Pictures/Нос/Нос2.bmp"), 100, 100, false, "Нос"};
    centerPictures[2] = {350, 380, txLoadImage("Pictures/Нос/Нос3.bmp"), 100, 100, false, "Нос"};
    centerPictures[3] = {200, 100, txLoadImage("Pictures/Волосы/Волосы1.bmp"), 400, 283, false, "Волосы"};
    centerPictures[4] = {200, 100, txLoadImage("Pictures/Волосы/Волосы2.bmp"), 400, 309, false, "Волосы"};
    centerPictures[5] = {200, 100, txLoadImage("Pictures/Волосы/Волосы3.bmp"), 448, 558, false, "Волосы"};
    centerPictures[6] = {300, 270, txLoadImage("Pictures/Глаза/Глаза1.bmp"), 250, 125, false, "Глаза"};
    centerPictures[7] = {300, 270, txLoadImage("Pictures/Глаза/Глаза2.bmp"), 250, 134, false, "Глаза"};
    centerPictures[8] = {300, 270, txLoadImage("Pictures/Глаза/Глаза3.bmp"), 250, 100, false, "Глаза"};



    Button btn[10];
    btn[0] = {100, 0, "Овал лица", ""};
    btn[1] = {300, 0, "Носы", "Нос"};
    btn[2] = {500, 0, "Прически", "Волосы"};
    btn[3] = {700, 0, "Глаза", "Глаза"};


    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetFillColor(TX_YELLOW);
        txClear();


        //Рисование кнопок
        for (int nKnopki = 0; nKnopki < 4; nKnopki++)
        {
            drawButton(btn[nKnopki]);
        }


        drawAllLeftPictures(leftPictures, COUNT_PICS);
        drawAllCenterPictures(centerPictures, COUNT_PICS);


        for (int nPict = 0; nPict < COUNT_PICS; nPict++)
        {
            if (txMouseButtons() == 1 &&
                leftPictures[nPict].visible &&
                txMouseX() >= leftPictures[nPict].x &&
                txMouseX() <= leftPictures[nPict].x + 100 &&
                txMouseY() >= leftPictures[nPict].y &&
                txMouseY() <= leftPictures[nPict].y + 100)
            {

                for (int n1 = 0; n1 < COUNT_PICS; n1++)
                {
                    if (centerPictures[n1].category == centerPictures[nPict].category)
                    {
                        centerPictures[n1].visible = false;
                    }
                }

                centerPictures[nPict].visible = !centerPictures[nPict].visible;
                txSleep(100);
            }
        }



        //Клик на носы
        for (int nKnopki = 0; nKnopki < 4; nKnopki++)
        {
            if (click(btn[nKnopki]))
            {
                for (int nPict = 0; nPict < COUNT_PICS; nPict++)
                {
                    leftPictures[nPict].visible = false;
                    if (leftPictures[nPict].category == btn[nKnopki].category)
                    {
                        leftPictures[nPict].visible = true;
                    }
                }
            }
        }



        txSleep(10);
        txEnd();
    }


    return 0;
}
