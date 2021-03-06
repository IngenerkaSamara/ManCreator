/// \file main.cpp
/// �������� ����
#include "TXLib.h"
#include "Button.cpp"
#include "Picture.cpp"
#include <iostream>
#include <fstream>
#include <locale>


using namespace std;

const int COUNT_BUTTONS = 7;
///������ ��������
const int LOAD_BUTTON = COUNT_BUTTONS - 3;
///������ ����������
const int SAVE_BUTTON = COUNT_BUTTONS - 2;
///������ �������
const int HELP_BUTTON = COUNT_BUTTONS - 1;

///����� ���������
const int PAGE_REDACTOR = 0;
///����� �������
const int PAGE_HELP = 1;


int main()
{
    txCreateWindow(1300,800);

    txTextCursor (false);
    txDisableAutoPause();

    int COUNT_PICS = 0;
    Picture leftPictures[1000];
    Picture centerPictures[1000];


    int PAGE = PAGE_REDACTOR;


    COUNT_PICS = readFromDirectory("Pictures/������/", leftPictures, COUNT_PICS);
    COUNT_PICS = readFromDirectory("Pictures/���/", leftPictures, COUNT_PICS);
    COUNT_PICS = readFromDirectory("Pictures/�����/", leftPictures, COUNT_PICS);
    COUNT_PICS = readFromDirectory("Pictures/���/", leftPictures, COUNT_PICS);




    //������ � ������
    for (int nPict = 0; nPict < COUNT_PICS; nPict++)
    {
        leftPictures[nPict].x = 10;
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

        if (centerPictures[nPict].category == "������")
        {
            centerPictures[nPict].x = 200;
            centerPictures[nPict].y = 100;
        }
        if (centerPictures[nPict].category == "���")
        {
            centerPictures[nPict].x = 350;
            centerPictures[nPict].y = 380;
        }
        if (centerPictures[nPict].category == "�����")
        {
            centerPictures[nPict].x = 300;
            centerPictures[nPict].y = 270;
        }
        if (centerPictures[nPict].category == "���")
        {
            centerPictures[nPict].x = 300;
            centerPictures[nPict].y = 470;
        }
    }




    Button btn[COUNT_BUTTONS];
    btn[0] = {  50, 0, "����", "���"};
    btn[1] = { 225, 0, "��������", "������"};
    btn[2] = { 400, 0, "�����", "�����"};
    btn[3] = { 575, 0, "���", "���"};
    btn[4] = { 750, 0, "���������", "�"};
    btn[5] = { 925, 0, "���������", "�"};
    btn[6] = {1100, 0, "?", "�"};

    int nomer_vybora = -1;
    bool mouseDown = false;
    int currentX = 0;
    int currentY = 0;


    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetFillColor(TX_YELLOW);
        txClear();

        ///���� �� � ������ ���������
        if (PAGE == PAGE_REDACTOR)
        {
            ///   ��������� ������
            for (int nKnopki = 0; nKnopki < COUNT_BUTTONS; nKnopki++)
            {
                drawButton(btn[nKnopki]);
            }


            drawAllPictures(leftPictures, COUNT_PICS);
            drawAllPictures(centerPictures, COUNT_PICS);


            ///   ����� �������� � ������
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

            //��������
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



            //���� �� ����
            for (int nKnopki = 0; nKnopki < COUNT_BUTTONS - 2; nKnopki++)
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

            //�������
            if (click(btn[HELP_BUTTON]))
            {
                PAGE = PAGE_HELP;
                btn[HELP_BUTTON].text = "�����";
                txSleep(500);
            }

            if (GetAsyncKeyState(VK_SNAPSHOT))
            {
                ScreenCapture(200, 100, 700, 600, "1.bmp", txWindow());
                txMessageBox("��������� � 1.bmp");
            }

            //���������
            if (click(btn[LOAD_BUTTON]))
            {
                string fileName = runFileDialog(false);
                if (fileName != "")
                {
                    for (int nPict = 0; nPict < COUNT_PICS; nPict++)
                    {
                        centerPictures[nPict].visible = false;
                    }

                    char buff[50];              // ���� ����� ��������� �����
                    ifstream fin(fileName);      // ������� ���� ��� ������
                    while (fin.good())
                    {
                        fin.getline(buff, 50); // ������� ������ �� �����
                        int x = atoi(buff);
                        fin.getline(buff, 50); // ������� ������ �� �����
                        int y = atoi(buff);
                        fin.getline(buff, 50); // ������� ������ �� �����
                        string adress = (buff);

                        for (int nPict = 0; nPict < COUNT_PICS; nPict++)
                        {
                            if (centerPictures[nPict].adress == adress)
                            {
                                centerPictures[nPict].x = x;
                                centerPictures[nPict].y = y;
                                centerPictures[nPict].visible = true;
                            }
                        }
                    }
                    fin.close();                //������� ����
                }
            }


            //���������
            if (click(btn[SAVE_BUTTON]))
            {
                string fileName = runFileDialog(true);
                if (fileName != "")
                {
                    ofstream fout; //������ ��� ���� ����������

                    fout.open(fileName); //������� ���� ��� ������

                    for (int nPict = 0; nPict < COUNT_PICS; nPict++)
                    {
                        if (centerPictures[nPict].visible)
                        {
                            fout << centerPictures[nPict].x << endl; //���-�� ��������
                            fout << centerPictures[nPict].y << endl;
                            fout << centerPictures[nPict].adress << endl;
                        }
                    }
                    fout.close();            //������� ����

                    txMessageBox("���������");
                }
            }

        }

        ///���� � ������ �������, ���������� �������
        else if (PAGE == PAGE_HELP)
        {
            txSelectFont("Arial", 46);
            txDrawText(0, 100, txGetExtentX(), txGetExtentY(),
                "����������� ���� ��������.\n"
                "������� ����, ���, ����� � ���� ������\n"
                "�� ����� - ����� ���� ����������� ��������� �������!\n"
                "�������� �������� ���������� � ������, ���� �����\n"
                "��������� �� '+' � ��������� �� '-'. �������� �����\n"
                "��������� � txt-������� � ��������� ������.\n"
                "����� ������� �������� �� ����� �� PrintScreen\n\n"
                "���������: ���� � ����"
                );

            //�������
            drawButton(btn[HELP_BUTTON]);
            if (click(btn[HELP_BUTTON]))
            {
                PAGE = PAGE_REDACTOR;
                btn[HELP_BUTTON].text = "?";
                txSleep(500);
            }
        }

        txSleep(10);
        txEnd();
    }

    deleteAll(leftPictures, centerPictures, COUNT_PICS);

    return 0;
}
