#include <cstdlib>
#include "TXLib.h"
#include "button.cpp"
#include "file.cpp"
#include "mapoject.cpp"
#include <fstream>
#include <string>
#include <iostream>
#include <dirent.h>
#include <Windows.h>
#include <string>
using namespace std;
        //selected category
char* selectCateg(char* selected_category ,Button buttons[], int COUNT_BTN)
{
	for(int j =0; j < COUNT_BTN;j++)
	{
		if (buttons[j].Click())
		{
			selected_category = buttons[j].category;
			txSleep(200);
		}
	}
	return selected_category;
}

               //draw from size of display
void  drawfromCurrentX(MapObject pictures[], int COUNT_PICTURES,int CURRENT_X)
{
    for (int nomer_picture = 0; nomer_picture < COUNT_PICTURES; nomer_picture++)
	{
		pictures[nomer_picture].drawMapObject(CURRENT_X);
	}
}

        //take the coordinates from the file when loading
int readPics(string adress, MapObject variants[], int COUNT_VARIANTS)
{

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (adress.c_str())) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL) {
      if ((string)ent->d_name != ".")
      if ((string)ent->d_name != "..")
      {
        variants[COUNT_VARIANTS] ={adress + (string)ent->d_name};
        COUNT_VARIANTS = COUNT_VARIANTS + 1;
        }
      }
      closedir (dir);
    }

    return COUNT_VARIANTS;
}



int main()
{
    txCreateWindow(1200,800);
    txDisableAutoPause();

    HDC background = txLoadImage("Album/Background.bmp");


    int CURRENT_X = 0;
    const int WIDTH_MENU = 200;

    const int COUNT_BTN = 11;
    Button buttons[COUNT_BTN];
    buttons[0] = {  0,0, "Дома", "House"};
    buttons[1] = {90,0, "Люди","people" };
    buttons[2] = {180,0, "Животные","Animals"};
    buttons[3] = {270,0, "Памятники", "Pamatnik"};
    buttons[4] = {360,0, "Здания", "building"};
    buttons[5] = {430,0, "On",""};
    buttons[6] = {500,0, "Off",""};
    buttons[7] = {570,0, "?",""};
    buttons[8] = {650,0, "Включить в \nслучае \nсмерти Ленина",""} ;
    buttons[9] = {750,0, "Загрузить",""};
    buttons[10] = {850,0, "Сохранение",""};
    int COUNT_VARIANTS = 0;
    MapObject variants[1000];


    COUNT_VARIANTS = readPics("Album/building/", variants, COUNT_VARIANTS);
    COUNT_VARIANTS = readPics("Album/Pamatnik/", variants, COUNT_VARIANTS);
    COUNT_VARIANTS = readPics("Album/people/", variants, COUNT_VARIANTS);
    COUNT_VARIANTS = readPics("Album/Animals/", variants, COUNT_VARIANTS);
    COUNT_VARIANTS = readPics("Album/House/", variants, COUNT_VARIANTS);




              //find category name
    for (int i = 0; i < COUNT_VARIANTS; i++)
    {
        string str = variants[i].adress;
        int fpos = str.find("/");
        int spos = str.find("/", fpos + 1);
        variants[i].category = str.substr(fpos + 1, spos - fpos -1);

        for (int k = 0; k < COUNT_BTN; k++)
        {
            if (buttons[k].category == variants[i].category)
            {
                variants[i].y = buttons[k].countPics * 150;
                buttons[k].countPics = buttons[k].countPics + 1;
            }
        }


        variants[i].visible = true;
        variants[i].text = "";
        variants[i].picture = txLoadImage (variants[i].adress.c_str());
        variants[i].width = get_widht (variants[i].adress);
        variants[i].hight= get_height (variants[i].adress) ;


        if (variants[i].width > 1.3* variants[i].hight)
        {
            variants[i].x = 1010;
            variants[i].x2 = variants[i].x + 140;
            variants[i].y2 = variants[i].y + 100;
        }

        else if (1.3 * variants[i].width < variants[i].hight)
        {
            variants[i].x = 1110;
            variants[i].x2 = variants[i].x + 90;
            variants[i].y2 = variants[i].y + 140;
        }

        else
        {
            variants[i].x = 1010;
            variants[i].x2 = variants[i].x + 100;
            variants[i].y2 = variants[i].y + 100;
        }

    }

    int COUNT_PICTURES = 0;
    MapObject pictures[100];

    char *selected_category = "";
    int nomer_kartinki = -100;
    int nomer_varianta = -100;
           //all about arrows
    MapObject arrowLeft  = { "Album/Arrows/Left.bmp",    0, 700,  100, 800};
    MapObject arrowRight = { "Album/Arrows/Right.bmp", 900, 700, 1000, 800};
    arrowLeft.visible = true;
    arrowLeft.picture = txLoadImage (arrowLeft.adress.c_str());
    arrowLeft.width = get_widht (arrowLeft.adress);
    arrowLeft.hight= get_height (arrowLeft.adress);
    arrowLeft.text= "";

    arrowRight.visible = true;
    arrowRight.picture = txLoadImage (arrowRight.adress.c_str());
    arrowRight.width = get_widht (arrowRight .adress);
    arrowRight.hight= get_height (arrowRight.adress);
    arrowRight.text= "";



    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetFillColor(TX_WHITE);
        txClear();
        for (int nomer = -2; nomer <= 2; nomer = nomer + 1)
        {
            txBitBlt(txDC(), CURRENT_X + 5632 * nomer, 0, 5632, txGetExtentY(), background);
        }
        arrowLeft.drawMapObject(0);
        arrowRight.drawMapObject(0);

        txSetColor(TX_BLACK);
        txSelectFont("Comic Sans MS", 60);
        txTextOut(200,700, "Конструктор деревни");
                   //right menu
        txSetFillColor(TX_BLACK);
        txRectangle(txGetExtentX() - WIDTH_MENU, 0, txGetExtentX(), txGetExtentY());


        drawButtons (buttons, COUNT_BTN);
        //draw pictures
		drawfromCurrentX(pictures, COUNT_PICTURES,CURRENT_X);
        // black menu
        txSetFillColor(TX_BLACK);
        txRectangle(txGetExtentX() - WIDTH_MENU, 0, txGetExtentX(), txGetExtentY());

        drawVariants (COUNT_VARIANTS, variants, selected_category );
        txSetColor(TX_WHITE);
        txSelectFont("Comic Sans MS", 26);
        txTextOut(1000,700, "Выберите че-нить");

        //select a picture
        nomer_kartinki = selectPics(COUNT_PICTURES, pictures, CURRENT_X, nomer_kartinki);

        //Click on menu button
        selected_category = selectCateg(selected_category , buttons, COUNT_BTN - 3);
             //Shrek music
        if (buttons[5].Click())
        {
            txPlaySound("Music\\somebody.wav");
        }        //off all music
        else if (buttons[6].Click())
        {
            txPlaySound(NULL);
        }
         //info
        else if (buttons[7].Click())
        {
            txSleep(500);
            bool stop = false;
            while (stop == false)
            {
            	txSetFillColor(TX_WHITE);
            	txSetColor(TX_BLACK);
                txRectangle (0, 0,1200,800);
                txSelectFont("Arial", 30);
                txDrawText(0, 0,1200,800,
                    "Приветствую в справке\n"
                    " \n"
                    " Поздровляю ! Вы имеете честь узреть нашу программу по созданию деревни своей мечты.  "
                    " \n   Тут сбудутся все твои самые скрытые желания. Посмотри , сверху есть вкладки открой любую и ты увидешь чудо ,"
                    " \n  картинки справа могут появлятся и на главаном экране. Поле для построек реально большое ! Мы проверяли и это было долго."
                    " \n    И так , если после всего этого вы не знаете как работает наш конструктор, то именно для тебя , мой туповатый друг мы написали Справку"
                    " \n    , кстати сейчас ты смотришь прямо в неё."
                    "     ( Чтоб выбрать предмет нажми на него левой кнопкой мыши )\n"
                    " \n    1 - у нас есть удаление , выбери предмет который хочешь УНИЧТОЖИТЬ и нажми Delete"
                    " \n    2 - на On и Off ты можешь включать и выключать музыку"
                    " \n    3 - выбери от дома до здания и перенеси объект на экран"
                    " \n    4 - нажав на кнопку R(К) ты можешь отзеркалить выбранный предмет\n"
                    " \n"
                    " \n Чтоб закрыть нажмите на любую точку >>"
                    " \n"
                    " Разработчики:\n"
                    "Никита, Илья, Ярослав, Иван");

                if (txMouseButtons() == 1 &&
                    txMouseX() > 0 &&
                    txMouseX() < 1200 &&
                    txMouseY() > 0 &&
                    txMouseY() < 800)
                {
                    stop = true;
                }

                txSleep(50);
            }
        }        //load old project
        else if (buttons[9].Click())
        {
            string stroka_x;
            string stroka_y;
            string stroka_adress;

            string newNameFile = selectFile(txWindow(), false);
            ifstream file(newNameFile);

            while (file.good())
            {
                getline(file,stroka_x);
                getline(file,stroka_y);
                getline(file,stroka_adress);


                pictures[COUNT_PICTURES].x = atoi(stroka_x.c_str());
                pictures[COUNT_PICTURES].y = atoi(stroka_y.c_str());
                pictures[COUNT_PICTURES].adress = stroka_adress;

                pictures[COUNT_PICTURES].width = get_widht (pictures[COUNT_PICTURES].adress);
                pictures[COUNT_PICTURES].hight= get_height (pictures[COUNT_PICTURES].adress) ;
                pictures[COUNT_PICTURES].x2 = pictures[COUNT_PICTURES].x + pictures[COUNT_PICTURES].width /3;
                pictures[COUNT_PICTURES].y2 = pictures[COUNT_PICTURES].y + pictures[COUNT_PICTURES].hight /3;
                pictures[COUNT_PICTURES].visible = true;
                pictures[COUNT_PICTURES].text = "";
                pictures[COUNT_PICTURES].picture = txLoadImage ( pictures[COUNT_PICTURES].adress.c_str());

                COUNT_PICTURES++;
            }

            file.close();
        }      //save project
        else if (buttons[10].Click())
        {
            string newNameFile = selectFile(txWindow(), true);
            ofstream file1(newNameFile);

            for (int nomer_picture = 0; nomer_picture < COUNT_PICTURES; nomer_picture++)
            {
                file1 << pictures[nomer_picture].x << endl;
                file1 << pictures[nomer_picture].y << endl;
                file1 << pictures[nomer_picture].adress << endl;
            }

            file1.close();
        }       //vkl when lenin was died
        else if(buttons[8].Click())
        {
            txPlaySound("Music\\gimn.wav");
        }

        if (GetAsyncKeyState(VK_SNAPSHOT))
        {
            ScreenCapture(220, 50, 1230, 984, "1.bmp", NULL);
            txMessageBox("Сохранено в 1.bmp");
        }

        //Click on variant
        if (!(txMouseButtons() == 1 && pictures[nomer_kartinki].clicked))
        {
            for (int i = 0; i < COUNT_VARIANTS; i++)
            {
                if (variants[i].Click(0) &&
                    selected_category == variants[i].category)
                {
                    int new_x = -CURRENT_X + random(0,844);
                    int new_y = 600 ;
                    MapObject tmp = {
                        variants[i].adress,
                        new_x,
                        new_y,
                        new_x + variants[i].width/3,
                        new_y + variants[i].hight/3,
                        variants[i].category,
                        variants[i].picture,
                        variants[i].width,
                        variants[i].hight,
                        "",
                        true
                    };

                    pictures[COUNT_PICTURES] = tmp;
                    COUNT_PICTURES++;
                    txSleep(200);
                }
            }
        }
        // zerkalo dly kartinki
        if(nomer_kartinki >= 0   &&GetAsyncKeyState('R') )
        {
            string category = pictures[nomer_kartinki].category;
            string adress = pictures[nomer_kartinki].adress;
            int categorySt = adress.find(category);
            int categorySz = category.size();

            adress = adress.replace(categorySt, categorySz, category + "z");
            if(adress.find("zz") < adress.size())
            {
                adress = adress.replace(adress.find("zz"), 2, "");
            }

            pictures[nomer_kartinki].adress = adress;

            pictures[nomer_kartinki].picture = txLoadImage(adress.c_str());
            txSleep(100);
        }

        //Click on picture
        if (pictures[nomer_kartinki].Click(CURRENT_X) && (txMouseX() < txGetExtentX() - 300))
        {
            for (int k = 0; k < COUNT_PICTURES; k++)
            {
                pictures[k].clicked = false;
            }
            pictures[nomer_kartinki].clicked = true;
        }

        //Выбранная картинка движется за мышкой
        if ((txMouseButtons() & 1) && pictures[nomer_kartinki].clicked && txMouseY() > 60)
        {
            int width = pictures[nomer_kartinki].x2  - pictures[nomer_kartinki].x;
            pictures[nomer_kartinki].x = txMouseX() - CURRENT_X - width /2 ;
            pictures[nomer_kartinki].x2 = pictures[nomer_kartinki].x + width ;
            int high = pictures[nomer_kartinki].y2 - pictures[nomer_kartinki].y;
            pictures[nomer_kartinki].y = txMouseY() - high / 2 ;
            pictures[nomer_kartinki].y2 = pictures[nomer_kartinki].y + high ;
        }

        //при отпускании мышки сбрасывается выбор картинки
        if (!(txMouseButtons() & 1) && pictures[nomer_kartinki].clicked)
        {
            pictures[nomer_kartinki].clicked = false;
        }

        //Deleting picture
        if (nomer_kartinki >= 0 && GetAsyncKeyState(VK_DELETE))
        {
            pictures[nomer_kartinki] = pictures[COUNT_PICTURES - 1];
            COUNT_PICTURES -= 1 ;
            nomer_kartinki = - 100 ;
        }

        //Camera moving
        if (arrowRight.Click(0))
        {
            CURRENT_X -= 10;
        }
        else if (arrowLeft.Click(0))
        {
            CURRENT_X += 10;
        }
                      //plus or minus size of selected picture
        if (nomer_kartinki >= 0 && GetAsyncKeyState(VK_OEM_MINUS) &&
            pictures[nomer_kartinki].x2 - pictures[nomer_kartinki].x > 30)
           {
             pictures[nomer_kartinki].x2 = pictures[nomer_kartinki].x +
             (pictures[nomer_kartinki].x2-pictures[nomer_kartinki].x)*0.97;
             pictures[nomer_kartinki].y2 = pictures[nomer_kartinki].y +
             (pictures[nomer_kartinki].y2-pictures[nomer_kartinki].y)*0.97;
           }
        if (nomer_kartinki >= 0 && GetAsyncKeyState(VK_OEM_PLUS))
           {
            pictures[nomer_kartinki].x2 = pictures[nomer_kartinki].x +
             (pictures[nomer_kartinki].x2-pictures[nomer_kartinki].x)*1.03;
            pictures[nomer_kartinki].y2 = pictures[nomer_kartinki].y +
             (pictures[nomer_kartinki].y2-pictures[nomer_kartinki].y)*1.03;
           }


        txSleep(10);
        txEnd();
    }

    DeleteAllPictures(COUNT_VARIANTS, variants, background );
    DeleteAllPictures(COUNT_VARIANTS, pictures, background );
    txDeleteDC (arrowLeft.picture);
    txDeleteDC (arrowLeft.picture);

    return 0;
}
