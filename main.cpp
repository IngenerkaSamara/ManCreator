#include "TXLib.h"
#include "Button.cpp"
#include "Picture.cpp"



int main()
{
    txCreateWindow(1200,800);


    const int COUNT_PICS = 9;
    Picture leftPictures[COUNT_PICS];
    leftPictures[0] = {0, 100, txLoadImage("Pictures/���/���1.bmp"), 126, 104, false, "���"};
    leftPictures[1] = {0, 250, txLoadImage("Pictures/���/���2.bmp"), 100, 100, false, "���"};
    leftPictures[2] = {0, 400, txLoadImage("Pictures/���/���3.bmp"), 100, 100, false, "���"};
    leftPictures[3] = {0, 100, txLoadImage("Pictures/������/������1.bmp"), 400, 283, false, "������"};
    leftPictures[4] = {0, 250, txLoadImage("Pictures/������/������2.bmp"), 400, 309, false, "������"};
    leftPictures[5] = {0, 400, txLoadImage("Pictures/������/������3.bmp"), 448, 558, false, "������"};
    leftPictures[6] = {0, 100, txLoadImage("Pictures/�����/�����1.bmp"), 250, 125, false, "�����"};
    leftPictures[7] = {0, 250, txLoadImage("Pictures/�����/�����2.bmp"), 250, 134, false, "�����"};
    leftPictures[8] = {0, 400, txLoadImage("Pictures/�����/�����3.bmp"), 250, 100, false, "�����"};



    Picture centerPictures[COUNT_PICS];
    centerPictures[0] = {350, 380, txLoadImage("Pictures/���/���1.bmp"), 126, 104, false, "���"};
    centerPictures[1] = {350, 380, txLoadImage("Pictures/���/���2.bmp"), 100, 100, false, "���"};
    centerPictures[2] = {350, 380, txLoadImage("Pictures/���/���3.bmp"), 100, 100, false, "���"};
    centerPictures[3] = {200, 100, txLoadImage("Pictures/������/������1.bmp"), 400, 283, false, "������"};
    centerPictures[4] = {200, 100, txLoadImage("Pictures/������/������2.bmp"), 400, 309, false, "������"};
    centerPictures[5] = {200, 100, txLoadImage("Pictures/������/������3.bmp"), 448, 558, false, "������"};
    centerPictures[6] = {300, 270, txLoadImage("Pictures/�����/�����1.bmp"), 250, 125, false, "�����"};
    centerPictures[7] = {300, 270, txLoadImage("Pictures/�����/�����2.bmp"), 250, 134, false, "�����"};
    centerPictures[8] = {300, 270, txLoadImage("Pictures/�����/�����3.bmp"), 250, 100, false, "�����"};



    Button btn[10];
    btn[0] = {100, 0, "���� ����", ""};
    btn[1] = {300, 0, "����", "���"};
    btn[2] = {500, 0, "��������", "������"};
    btn[3] = {700, 0, "�����", "�����"};


    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetFillColor(TX_YELLOW);
        txClear();


        //��������� ������
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



        //���� �� ����
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
