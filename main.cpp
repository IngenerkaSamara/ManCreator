#include "TXLib.h"
#include "Button.cpp"
#include "Picture.cpp"
#include <iostream>
#include <locale>

using namespace std;

const int COUNT_BUTTONS = 5;


int main()
{
    txCreateWindow(1200,800);


    const int COUNT_PICS = 12;
    Picture leftPictures[COUNT_PICS];
    leftPictures[0] = {0, 100, "Pictures/Волосы/Волосы1.bmp"};
    leftPictures[1] = {0, 250, "Pictures/Волосы/Волосы2.bmp"};
    leftPictures[2] = {0, 400, "Pictures/Волосы/Волосы3.bmp"};
    leftPictures[3] = {0, 100, "Pictures/Нос/Нос1.bmp"};
    leftPictures[4] = {0, 250, "Pictures/Нос/Нос2.bmp"};
    leftPictures[5] = {0, 400, "Pictures/Нос/Нос3.bmp"};
    leftPictures[6] = {0, 100, "Pictures/Глаза/Глаза1.bmp"};
    leftPictures[7] = {0, 250, "Pictures/Глаза/Глаза2.bmp"};
    leftPictures[8] = {0, 400, "Pictures/Глаза/Глаза3.bmp"};
    leftPictures[9] = {0, 100, "Pictures/Рот/Рот1.bmp"};
    leftPictures[10] = {0, 250, "Pictures/Рот/Рот2.bmp"};
    leftPictures[11] = {0, 400, "Pictures/Рот/Рот3.bmp"};



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
    centerPictures[9] = {300, 470};
    centerPictures[10] = {300, 470};
    centerPictures[11] = {300, 470};

    //Ширина и высота
    for (int nPict = 0; nPict < COUNT_PICS; nPict++)
    {
        leftPictures[nPict].width = 100;
        leftPictures[nPict].height = 100;
        leftPictures[nPict].src_width = getWidth(leftPictures[nPict].adress);
        leftPictures[nPict].src_height = getHeight(leftPictures[nPict].adress);
        leftPictures[nPict].image = txLoadImage(leftPictures[nPict].adress.c_str());
        leftPictures[nPict].visible = false;

        string stroka = leftPictures[nPict].adress;
        int pos_x = stroka.find("/");
        int pos_y = stroka.find("/", pos_x + 1);
        leftPictures[nPict].category = stroka.substr(pos_x + 1, pos_y - pos_x - 1);


        centerPictures[nPict].category = leftPictures[nPict].category;
        centerPictures[nPict].visible = false;
        centerPictures[nPict].adress = leftPictures[nPict].adress;
        centerPictures[nPict].image = leftPictures[nPict].image;
        centerPictures[nPict].src_width = leftPictures[nPict].src_width;
        centerPictures[nPict].src_height = leftPictures[nPict].src_height;
        centerPictures[nPict].width = centerPictures[nPict].src_width;
        centerPictures[nPict].height = centerPictures[nPict].src_height;
    }



    Button btn[COUNT_BUTTONS];
    btn[0] = {100, 0, "Овал лица", ""};
    btn[1] = {300, 0, "Носы", "Нос"};
    btn[2] = {500, 0, "Прически", "Волосы"};
    btn[3] = {700, 0, "Глаза", "Глаза"};
    btn[4] = {900, 0, "Рты", "Рот"};

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
        for (int nKnopki = 0; nKnopki < COUNT_BUTTONS; nKnopki++)
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

            movePicture(centerPictures, nomer_vybora);
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
        for (int nKnopki = 0; nKnopki < COUNT_BUTTONS; nKnopki++)
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

    deleteAll(leftPictures, centerPictures, COUNT_PICS);

    return 0;
}
