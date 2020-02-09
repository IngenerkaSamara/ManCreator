#include "TXLib.h"
#include "Button.cpp"
#include "Picture.cpp"



int main()
{
    txCreateWindow(1200,800);


    const int COUNT_PICS = 9;
    Picture leftPictures[COUNT_PICS];
    leftPictures[0] = {0, 100, "Pictures/Волосы/Волосы1.bmp", txLoadImage("Pictures/Волосы/Волосы1.bmp"), 0, 0, false, "Волосы"};
    leftPictures[1] = {0, 250, "Pictures/Волосы/Волосы2.bmp", txLoadImage("Pictures/Волосы/Волосы2.bmp"), 0 , 0, false, "Волосы"};
    leftPictures[2] = {0, 400, "Pictures/Волосы/Волосы3.bmp", txLoadImage("Pictures/Волосы/Волосы3.bmp"), 448, 558, false, "Волосы"};
    leftPictures[3] = {0, 100, "Pictures/Нос/Нос1.bmp", txLoadImage("Pictures/Нос/Нос1.bmp"), 126, 104, false, "Нос"};
    leftPictures[4] = {0, 250, "Pictures/Нос/Нос2.bmp", txLoadImage("Pictures/Нос/Нос2.bmp"), 100, 100, false, "Нос"};
    leftPictures[5] = {0, 400, "Pictures/Нос/Нос3.bmp", txLoadImage("Pictures/Нос/Нос3.bmp"), 100, 100, false, "Нос"};
    leftPictures[6] = {0, 100, "Pictures/Глаза/Глаза1.bmp", txLoadImage("Pictures/Глаза/Глаза1.bmp"), 250, 125, false, "Глаза"};
    leftPictures[7] = {0, 250, "Pictures/Глаза/Глаза2.bmp", txLoadImage("Pictures/Глаза/Глаза2.bmp"), 250, 134, false, "Глаза"};
    leftPictures[8] = {0, 400, "Pictures/Глаза/Глаза3.bmp", txLoadImage("Pictures/Глаза/Глаза3.bmp"), 250, 100, false, "Глаза"};



    Picture centerPictures[COUNT_PICS];
    centerPictures[0] = {200, 100};
    centerPictures[1] = {200, 100};
    centerPictures[2] = {200, 100};
    centerPictures[3] = {350, 380};
    centerPictures[4] = {350, 380};
    centerPictures[5] = {350, 380};
    centerPictures[6] = {300, 270};
    centerPictures[7] = {300, 270};
    centerPictures[8] = {300, 270};

    //Ширина и высота
    for (int nPict = 0; nPict < COUNT_PICS; nPict++)
    {
        leftPictures[nPict].width = 100;
        leftPictures[nPict].height = 100;
        leftPictures[nPict].src_width = getWidth(leftPictures[nPict].adress);
        leftPictures[nPict].src_height = getHeight(leftPictures[nPict].adress);
        centerPictures[nPict].category = leftPictures[nPict].category;
        centerPictures[nPict].visible = false;
        centerPictures[nPict].adress = leftPictures[nPict].adress;
        centerPictures[nPict].image = leftPictures[nPict].image;
        centerPictures[nPict].src_width = leftPictures[nPict].src_width;
        centerPictures[nPict].src_height = leftPictures[nPict].src_height;
        centerPictures[nPict].width = centerPictures[nPict].src_width;
        centerPictures[nPict].height = centerPictures[nPict].src_height;
    }



    Button btn[10];
    btn[0] = {100, 0, "Овал лица", ""};
    btn[1] = {300, 0, "Носы", "Нос"};
    btn[2] = {500, 0, "Прически", "Волосы"};
    btn[3] = {700, 0, "Глаза", "Глаза"};

    int nomer_vybora = -1;
    bool mouseDown = false;
    int currentX = 0;
    int currentY = 0;


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


        drawAllPictures(leftPictures, COUNT_PICS);
        drawAllPictures(centerPictures, COUNT_PICS);


        //Выбор картинки в центре
        for (int nPict = 0; nPict < COUNT_PICS; nPict++)
        {
            if (txMouseButtons() == 1 &&
                centerPictures[nPict].visible &&
                txMouseX() >= centerPictures[nPict].x &&
                txMouseX() <= centerPictures[nPict].x + centerPictures[nPict].width &&
                txMouseY() >= centerPictures[nPict].y &&
                txMouseY() <= centerPictures[nPict].y + centerPictures[nPict].height)
            {
                nomer_vybora = nPict;
                currentX = centerPictures[nPict].x - txMouseX();
                currentY = centerPictures[nPict].y - txMouseY();
                mouseDown = false;
            }
        }

        //Движение
        if (nomer_vybora >= 0)
        {
            if (txMouseButtons() == 1 && !mouseDown)
            {
                centerPictures[nomer_vybora].x = txMouseX() + currentX;
                centerPictures[nomer_vybora].y = txMouseY() + currentY;
            }
            else if (txMouseButtons() != 1)
            {
                mouseDown = true;
            }

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


    for (int nPict = 0; nPict < COUNT_PICS; nPict++)
    {
        txDeleteDC(centerPictures[nPict].image);
        txDeleteDC(leftPictures[nPict].image);
    }


    return 0;
}
