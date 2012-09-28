/****************************************************

  ParkGame

  Desenvolvido por Jonathan Sansalone Pacheco Rolim

  18 de Setembro de 2012

****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <glut.h>

#define W_W 700
#define W_H 700
#define FAST 'f'
#define SLOW 's'
#define LIGHT_ON 1
#define LIGHT_OFF 0
#define MODE_ROTATE 1
#define MODE_TRANSLATE 0
#define MODE_FORWARD 'd'
#define MODE_BACKWARD 'r'
#define MODE_MENU 0
#define MODE_GAME 1
#define MODE_ABOUT 2

void paint(void);
void paintCar(void);
void paintBorder(void);
void paintTracks(void);
void paintOthers(void);
void paintMenu(void);
void paintAbout(void);
int check_colision(void);
void check_angle();
void set_window_size(GLsizei w, GLsizei h);
void translate(int i, float x, float y, int jX, int jY, float qtX, float qtY);
void translateCar();
void translateCarXY(float qtX, float qtY);
void rotate(int i, float x, float y, int jX, int jY, float a);
void special_keys(int key, int x, int y);
void keys(unsigned char key, int x, int y);

float car[86][4] =
{
    // corpo
    {0,0,0,200},
    {0,200,91,200},
    {91,200,91,0},
    {91,0,0,0},
    // roda dianteira esquerda
    {-5,160,0,160},
    {0,160,0,130},
    {0,130,-5,130},
    {-5,130,-5,160},
    // roda traseira esquerda
    {-5,60,0,60},
    {0,60,0,30},
    {0,30,-5,30},
    {-5,30,-5,60},
    // roda dianteira direita
    {91,160,96,160},
    {96,160,96,130},
    {96,130,91,130},
    {91,130,91,160},
    // roda traseira direita
    {91,60,96,60},
    {96,60,96,30},
    {96,30,91,30},
    {91,30,91,60},
    // teto
    {15,130,75,130},
    {75,130,75,45},
    {75,45,15,45},
    {15,45,15,130},
    // parabrisa dianteiro
    {15,130,5,160},
    {5,160,85,160},
    {85,160,75,130},
    {75,130,15,130},
    // parabrisa traseiro
    {15,45,5,30},
    {5,30,85,30},
    {85,30,75,45},
    {75,45,15,45},
    // janela esquerda
    {5,160,15,130},
    {15,130,15,45},
    {15,45,5,30},
    {5,30,5,160},
    // janela direita
    {75,130,85,160},
    {85,160,85,30},
    {85,30,75,45},
    {75,45,75,130},
    // faixa dianteira 1
    {36,200,43,200},
    {43,200,43,160},
    {43,160,36,160},
    {36,160,36,200},
    // faixa dianteira 2
    {46,200,53,200},
    {53,200,53,160},
    {53,160,46,160},
    {46,160,46,200},
    // faixa meio 1
    {36,130,43,130},
    {43,130,43,45},
    {43,45,36,45},
    {36,45,36,130},
    // faixa meio 2
    {46,130,53,130},
    {53,130,53,45},
    {53,45,46,45},
    {46,45,46,130},
    // faixa traseira 1
    {36,30,43,30},
    {43,30,43,0},
    {43,0,36,0},
    {36,0,36,30},
    // faixa traseira 2
    {46,30,53,30},
    {53,30,53,0},
    {53,0,46,0},
    {46,0,46,30},
    // farol traseiro esquerdo
    {13,0,25,0},
    {25,0,25,-4},
    {25,-4,13,-4},
    {13,-4,13,0},
    // farol traseiro direito
    {66,0,78,0},
    {78,0,78,-4},
    {78,-4,66,-4},
    {66,-4,66,0},
    // farol dianteiro esquerdo
    {10,200,22,200},
    {22,200,22,204},
    {22,204,10,204},
    {10,204,10,200},
    // farol dianteiro direito
    {69,200,81,200},
    {81,200,81,204},
    {81,204,69,204},
    {69,204,69,200},
    // raios farol
    {10,208,5,240},
    {16,208,16,242},
    {22,208,27,240},
    {69,208,65,240},
    {75,208,75,242},
    {81,208,86,240}
};

float h_track[4][2] =
{
    {0,0},
    {0,15},
    {280,15},
    {280,0}
};

float d_track[4][2] =
{
    {0,0},
    {15,0},
    {230,-215},
    {215,-215}
};

float v_track[4][2] =
{
    {0,0},
    {30,0},
    {30,-1330},
    {0,-1330}
};

float m_track[4][2] =
{
    {0,0},
    {10,0},
    {10,-1330},
    {0,-1330}
};
float m_track_dotted[4][2] =
{
    {0,0},
    {10,0},
    {10,-66},
    {0,-66}
};

float direction[2] = {0,0};
float angle=0;
float angleAux=0;
float xRef=0;
float yRef=0;
int mode=-1;
char modeDirection = MODE_FORWARD;
int velocity = 10;
int velocityAux = 10;
int light = LIGHT_OFF;
int modeScreen = MODE_GAME;
int RUN = 1;

void paintCar()
{
    int i, j;
    // corpo
    glColor3f(1,90.0f/255.0f,0);
    glBegin(GL_POLYGON);
    for(i=0; i<4; i=i+1)
    {
        glVertex2f(car[i][0]/W_W,car[i][1]/W_W);
        glVertex2f(car[i][2]/W_W,car[i][3]/W_W);
    }
    glEnd();
    // rodas
    glColor3f(0.2,0.2,0.2);
    glBegin(GL_POLYGON);
    for(i=4; i<8; i=i+1)
    {
        glVertex2f(car[i][0]/W_W,car[i][1]/W_W);
        glVertex2f(car[i][2]/W_W,car[i][3]/W_W);
    }
    glEnd();
    glBegin(GL_POLYGON);
    for(i=8; i<12; i=i+1)
    {
        glVertex2f(car[i][0]/W_W,car[i][1]/W_W);
        glVertex2f(car[i][2]/W_W,car[i][3]/W_W);
    }
    glEnd();
    glBegin(GL_POLYGON);
    for(i=12; i<16; i=i+1)
    {
        glVertex2f(car[i][0]/W_W,car[i][1]/W_W);
        glVertex2f(car[i][2]/W_W,car[i][3]/W_W);
    }
    glEnd();
    glBegin(GL_POLYGON);
    for(i=16; i<20; i=i+1)
    {
        glVertex2f(car[i][0]/W_W,car[i][1]/W_W);
        glVertex2f(car[i][2]/W_W,car[i][3]/W_W);
    }
    glEnd();
    // teto
    glColor3f(1,90.0f/255.0f,0.0);
    glBegin(GL_POLYGON);
    for(i=20; i<24; i=i+1)
    {
        glVertex2f(car[i][0]/W_W,car[i][1]/W_W);
        glVertex2f(car[i][2]/W_W,car[i][3]/W_W);
    }
    glEnd();
    // parabrisa dianteiro
    //glColor3f(0.15,0.15,0.15);
    glColor3f(0.0,120.0f/255.0f,1);
    glBegin(GL_POLYGON);
    for(i=24; i<28; i=i+1)
    {
        glVertex2f(car[i][0]/W_W,car[i][1]/W_W);
        glVertex2f(car[i][2]/W_W,car[i][3]/W_W);
    }
    glEnd();
    // parabrisa traseiro
    //glColor3f(0.15,0.15,0.15);
    glColor3f(0.0,120.0f/255.0f,1);
    glBegin(GL_POLYGON);
    for(i=28; i<32; i=i+1)
    {
        glVertex2f(car[i][0]/W_W,car[i][1]/W_W);
        glVertex2f(car[i][2]/W_W,car[i][3]/W_W);
    }
    glEnd();
    // janela direita
    //glColor3f(0.25,0.25,0.25);
    glColor3f(0.0,202.0f/255.0f,1);
    glBegin(GL_POLYGON);
    for(i=32; i<36; i=i+1)
    {
        glVertex2f(car[i][0]/W_W,car[i][1]/W_W);
        glVertex2f(car[i][2]/W_W,car[i][3]/W_W);
    }
    glEnd();
    // janela esquerda
    glColor3f(0.0,202.0f/255.0f,1);
    glBegin(GL_POLYGON);
    for(i=36; i<40; i=i+1)
    {
        glVertex2f(car[i][0]/W_W,car[i][1]/W_W);
        glVertex2f(car[i][2]/W_W,car[i][3]/W_W);
    }
    glEnd();
    // faixa dianteira 1
    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    for(i=40; i<44; i=i+1)
    {
        glVertex2f(car[i][0]/W_W,car[i][1]/W_W);
        glVertex2f(car[i][2]/W_W,car[i][3]/W_W);
    }
    glEnd();
    // faixa dianteira 2
    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    for(i=44; i<48; i=i+1)
    {
        glVertex2f(car[i][0]/W_W,car[i][1]/W_W);
        glVertex2f(car[i][2]/W_W,car[i][3]/W_W);
    }
    glEnd();
    // faixa meio 1
    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    for(i=48; i<52; i=i+1)
    {
        glVertex2f(car[i][0]/W_W,car[i][1]/W_W);
        glVertex2f(car[i][2]/W_W,car[i][3]/W_W);
    }
    glEnd();
    // faixa meio 2
    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    for(i=52; i<56; i=i+1)
    {
        glVertex2f(car[i][0]/W_W,car[i][1]/W_W);
        glVertex2f(car[i][2]/W_W,car[i][3]/W_W);
    }
    glEnd();
    // faixa traseira 1
    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    for(i=56; i<60; i=i+1)
    {
        glVertex2f(car[i][0]/W_W,car[i][1]/W_W);
        glVertex2f(car[i][2]/W_W,car[i][3]/W_W);
    }
    glEnd();
    // faixa traseira 2
    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    for(i=60; i<64; i=i+1)
    {
        glVertex2f(car[i][0]/W_W,car[i][1]/W_W);
        glVertex2f(car[i][2]/W_W,car[i][3]/W_W);
    }
    glEnd();
    // farol traseiro esquerdo
    if(modeDirection == MODE_FORWARD) glColor3f(1,0,0);
    else if(modeDirection == MODE_BACKWARD) glColor3f(1,1,1);
    glBegin(GL_POLYGON);
    for(i=64; i<68; i=i+1)
    {
        glVertex2f(car[i][0]/W_W,car[i][1]/W_W);
        glVertex2f(car[i][2]/W_W,car[i][3]/W_W);
    }
    glEnd();
    // farol traseiro direito
    if(modeDirection == MODE_FORWARD) glColor3f(1,0,0);
    else if(modeDirection == MODE_BACKWARD) glColor3f(1,1,1);
    glBegin(GL_POLYGON);
    for(i=68; i<72; i=i+1)
    {
        glVertex2f(car[i][0]/W_W,car[i][1]/W_W);
        glVertex2f(car[i][2]/W_W,car[i][3]/W_W);
    }
    glEnd();
    // farol dianteiro esquerdo
    glColor3f(1,1,0);
    glBegin(GL_POLYGON);
    for(i=72; i<76; i=i+1)
    {
        glVertex2f(car[i][0]/W_W,car[i][1]/W_W);
        glVertex2f(car[i][2]/W_W,car[i][3]/W_W);
    }
    glEnd();
    // farol dianteiro direito
    glColor3f(1,1,0);
    glBegin(GL_POLYGON);
    for(i=76; i<80; i=i+1)
    {
        glVertex2f(car[i][0]/W_W,car[i][1]/W_W);
        glVertex2f(car[i][2]/W_W,car[i][3]/W_W);
    }
    glEnd();
    // raios de luz do farol
    if(light == LIGHT_ON)
    {
        glColor3f(0.95,0.95,1);
        glBegin(GL_LINES);
        for(i=80; i<86; i=i+1)
        {
            for(j=0; j<4; j=j+2)
            {
                glVertex2f(car[i][j]/W_W,car[i][j+1]/W_W);
            }
        }
        glEnd();
    }
}

void paintBorder()
{
    glColor3f(0.85f,0.85f,0.85f);
    glBegin(GL_QUADS);
    glVertex2f(1.0f,1.0f);
    glVertex2f(-1.0f,1.0f);
    glVertex2f(-1.0f,0.95f);
    glVertex2f(1.0f,0.95f);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(-1.0f,-0.95f);
    glVertex2f(-1.0f,-1.0f);
    glVertex2f(1.0f,-1.0f);
    glVertex2f(1.0f,-0.95f);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(1.0f,1.0f);
    glVertex2f(0.95f,1.0f);
    glVertex2f(0.95f,-1.0f);
    glVertex2f(1.0f,-1.0f);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(-1.0f,1.0f);
    glVertex2f(-0.95f,1.0f);
    glVertex2f(-0.95f,-1.0f);
    glVertex2f(-1.0f,-1.0f);
    glEnd();
    glColor3f(0,0,1);
    glRasterPos2f(-1.0f,-1.0f);
    char* p = (char*) "F3=Menu";
    while(*p != '\0')
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*p++);
    }
}

void paintTracks()
{
    int i, j;
    glColor3f(1,1,0);
    glBegin(GL_QUADS);
    for(j=0; j<600; j=j+150)
    {
        for(i=0; i<4; i=i+1)
        {
            glVertex2f(-0.95f+h_track[i][0]/W_W,-0.95f+(h_track[i][1]+j)/W_W);
        }
    }
    glEnd();
    glBegin(GL_QUADS);
    for(j=0; j<720; j=j+180)
    {
        for(i=0; i<4; i=i+1)
        {
            glVertex2f(-0.95f+(d_track[i][0]+j)/W_W,0.95f+d_track[i][1]/W_W);
        }
    }
    glEnd();
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
    for(i=0; i<4; i=i+1)
    {
        glVertex2f(0.3f+v_track[i][0]/W_W,0.95f+v_track[i][1]/W_W);
    }
    glEnd();
    glBegin(GL_QUADS);
    for(i=0; i<4; i=i+1)
    {
        glVertex2f(0.9f+v_track[i][0]/W_W,0.95f+v_track[i][1]/W_W);
    }
    glEnd();
    glColor3f(1,1,0);
    glBegin(GL_QUADS);
    for(i=0; i<4; i=i+1)
    {
        glVertex2f((0.3f+0.9f)/2.0f+m_track[i][0]/W_W,0.95f+m_track[i][1]/W_W);
    }
    glEnd();
    glBegin(GL_QUADS);
    for(j=0; j<1330; j=j+133)
    {
        for(i=0; i<4; i=i+1)
        {
            glVertex2f((0.3f+0.9f+0.05f)/2.0f+m_track_dotted[i][0]/W_W,0.95f+(m_track_dotted[i][1]-j)/W_W);
        }
    }
    glEnd();
}

void paintOthers()
{
    float pi = 3.14159265;
    float angle = 0;
    float colors[4][3] =
    {
        {1,0,0},
        {1,1,1},
        {1,0,0},
        {1,1,1}
    };
    int i, j, k, l;
    for(k=0; k<900; k=k+300)
    {
        for(j=0,l=0; j<20,l<4; j=j+5,l=l+1)
        {
            glColor3f(colors[l][0],colors[l][1],colors[l][2]);
            glBegin(GL_POLYGON);
            for(i=0; i<100; i=i+1)
            {
                angle = 2*pi*i/100;
                glVertex2f((-100+cos(angle)*(20-j))/W_W, (k-350+sin(angle)*(20-j))/W_W);
            }
            glEnd();
        }
    }
}

void paint()
{
    int i, j;
    if(RUN)
    {
        if(mode == MODE_TRANSLATE)
        {
            translateCar();
            check_colision();
        }
        else if(mode == MODE_ROTATE)
        {
            check_angle();
            xRef = (car[0][0] + car[1][2]) / 2.0f;
            yRef = (car[0][1] + car[1][3]) / 2.0f;
            for(i=0; i<86; i=i+1)
            {
                for(j=0; j<4; j=j+2)
                {
                    rotate(i, car[i][j], car[i][j+1], j, j+1, angle - angleAux);
                }
            }
            angleAux = angle;
        }
        RUN = 0;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    paintBorder();
    paintTracks();
    paintOthers();
    paintCar();
    if(modeScreen == MODE_MENU)
    {
        paintMenu();
    }
    else if(modeScreen == MODE_ABOUT)
    {
        paintAbout();
    }
    glutSwapBuffers();
}

void paintMenu()
{
    glColor3f(1,0,0);
    glBegin(GL_QUADS);
    glVertex2f(-0.5f,0.33f);
    glVertex2f(0.5f,0.33f);
    glVertex2f(0.5f,-0.33f);
    glVertex2f(-0.5f,-0.33f);
    glEnd();
    glColor3f(0,0,1);
    glBegin(GL_QUADS);
    glVertex2f(-0.45f,0.28f);
    glVertex2f(0.45f,0.28f);
    glVertex2f(0.45f,-0.28f);
    glVertex2f(-0.45f,-0.28f);
    glEnd();
    glRasterPos2f(-0.05f,0.29f);
    char* p = (char*) "Menu";
    while(*p != '\0')
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*p++);
    }
    glColor3f(1,1,1);
    glRasterPos2f(-0.43f,0.24f);
    p = (char*) "Setas = Movimentar o carrinho";
    while(*p != '\0')
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*p++);
    }
    glRasterPos2f(-0.43f,0.20f);
    p = (char*) "R = Marcha re";
    while(*p != '\0')
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*p++);
    }
    glRasterPos2f(-0.43f,0.16f);
    p = (char*) "D = Andar para frente";
    while(*p != '\0')
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*p++);
    }
    glRasterPos2f(-0.43f,0.12f);
    p = (char*) "F = Aumentar velocidade";
    while(*p != '\0')
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*p++);
    }
    glRasterPos2f(-0.43f,0.08f);
    p = (char*) "S = Diminuir velocidade";
    while(*p != '\0')
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*p++);
    }
    glRasterPos2f(-0.43f,0.04f);
    p = (char*) "F2 = Acender farol";
    while(*p != '\0')
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*p++);
    }
    glRasterPos2f(-0.43f,0.0f);
    p = (char*) "F3 = Abrir/fechar menu";
    while(*p != '\0')
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*p++);
    }
    glRasterPos2f(-0.43f,-0.04f);
    p = (char*) "F4 = Abrir/fechar janela Sobre";
    while(*p != '\0')
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*p++);
    }
    glRasterPos2f(-0.43f,-0.08f);
    p = (char*) "Esc = Sair";
    while(*p != '\0')
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*p++);
    }
}

void paintAbout()
{
    glColor3f(1,0,0);
    glBegin(GL_QUADS);
    glVertex2f(-0.3f,0.13f);
    glVertex2f(0.3f,0.13f);
    glVertex2f(0.3f,-0.13f);
    glVertex2f(-0.3f,-0.13f);
    glEnd();
    glColor3f(0,0,1);
    glBegin(GL_QUADS);
    glVertex2f(-0.25f,0.08f);
    glVertex2f(0.25f,0.08f);
    glVertex2f(0.25f,-0.08f);
    glVertex2f(-0.25f,-0.08f);
    glEnd();
    glRasterPos2f(-0.05f,0.09f);
    char* p = (char*) "Sobre";
    while(*p != '\0')
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*p++);
    }
    glColor3f(1,1,1);
    glRasterPos2f(-0.23f,0.04f);
    p = (char*) "Autor: Jonathan Sansalone";
    while(*p != '\0')
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*p++);
    }
    glRasterPos2f(-0.23f,0.00f);
    p = (char*) "Data: 27/09/2012";
    while(*p != '\0')
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*p++);
    }
}

void check_angle()
{
    if(angle > 360) angle = angle - 360;
    else if(angle < 0) angle = 360+angle;
}

int check_colision()
{
    /* carro indo para cima
    0,0            0,1                 1,0            1,1
    extremes[1][0],extremes[1][1]      extremes[2][0],extremes[2][1]


    2,0            2,1                 3,0            3,1
    extremes[0][0],extremes[0][1]      extremes[3][0],extremes[3][1]
    */
    int i, j;
    float dist;
    float extremes[4][2] =
    {
        {car[1][0],car[1][1]},
        {car[2][0],car[2][1]},
        {car[0][0],car[0][1]},
        {car[3][0],car[3][1]}
    };


    if(modeDirection == MODE_FORWARD)
    {

        if(extremes[0][0]/W_W >= 0.95f)
        {
            if(extremes[1][0] <= extremes[0][0])
            {
                dist = 0.95f * W_W - extremes[0][0];
                translateCarXY(dist,0);
            }
            else
            {
                dist = 0.95f * W_W - extremes[1][0];
                translateCarXY(dist,0);
            }
        }
        else if(extremes[1][0]/W_W >= 0.95f)
        {
            dist = 0.95f * W_W - extremes[1][0];
            translateCarXY(dist,0);
        }

        if(extremes[0][1]/W_W >= 0.95f)
        {
            if(extremes[1][1] <= extremes[0][1])
            {
                dist = 0.95f * W_W - extremes[0][1];
                translateCarXY(0,dist);
            }
            else
            {
                dist = 0.95f * W_W - extremes[1][1];
                translateCarXY(0,dist);
            }
        }
        else if(extremes[1][1]/W_W >= 0.95f)
        {
            dist = 0.95f * W_W - extremes[1][1];
            translateCarXY(0,dist);
        }

        if(extremes[0][0]/W_W < -0.95f)
        {
            if(extremes[1][0] >= extremes[0][0])
            {
                dist = -(0.95f * W_W) - extremes[0][0];
                translateCarXY(dist,0);
            }
            else
            {
                dist = -(0.95f * W_W) - extremes[1][0];
                translateCarXY(dist,0);
            }
        }
        else if(extremes[1][0]/W_W < -0.95f)
        {
            dist = -(0.95f * W_W) - extremes[1][0];
            translateCarXY(dist,0);
        }

        if(extremes[0][1]/W_W < -0.95f)
        {
            if(extremes[1][1] >= extremes[0][1])
            {
                dist = -(0.95f * W_W) - extremes[0][1];
                translateCarXY(0,dist);
            }
            else
            {
                dist = -(0.95f * W_W) - extremes[1][1];
                translateCarXY(0,dist);
            }
        }
        else if(extremes[1][1]/W_W < -0.95f)
        {
            dist = -(0.95f * W_W) - extremes[1][1];
            translateCarXY(0,dist);
        }

    }
    else if(modeDirection == MODE_BACKWARD)
    {

        if(extremes[2][0]/W_W >= 0.95f)
        {
            if(extremes[3][0] <= extremes[2][0])
            {
                dist = 0.95f * W_W - extremes[2][0];
                translateCarXY(dist,0);
            }
            else
            {
                dist = 0.95f * W_W - extremes[3][0];
                translateCarXY(dist,0);
            }
        }
        else if(extremes[3][0]/W_W >= 0.95f)
        {
            dist = 0.95f * W_W - extremes[3][0];
            translateCarXY(dist,0);
        }

        if(extremes[2][1]/W_W >= 0.95f)
        {
            if(extremes[3][1] <= extremes[2][1])
            {
                dist = 0.95f * W_W - extremes[2][1];
                translateCarXY(0,dist);
            }
            else
            {
                dist = 0.95f * W_W - extremes[3][1];
                translateCarXY(0,dist);
            }
        }
        else if(extremes[3][1]/W_W >= 0.95f)
        {
            dist = 0.95f * W_W - extremes[3][1];
            translateCarXY(0,dist);
        }

        if(extremes[2][0]/W_W < -0.95f)
        {
            if(extremes[3][0] >= extremes[2][0])
            {
                dist = -(0.95f * W_W) - extremes[2][0];
                translateCarXY(dist,0);
            }
            else
            {
                dist = -(0.95f * W_W) - extremes[3][0];
                translateCarXY(dist,0);
            }
        }
        else if(extremes[3][0]/W_W < -0.95f)
        {
            dist = -(0.95f * W_W) - extremes[3][0];
            translateCarXY(dist,0);
        }

        if(extremes[2][1]/W_W < -0.95f)
        {
            if(extremes[3][1] >= extremes[2][1])
            {
                dist = -(0.95f * W_W) - extremes[2][1];
                translateCarXY(0,dist);
            }
            else
            {
                dist = -(0.95f * W_W) - extremes[3][1];
                translateCarXY(0,dist);
            }
        }
        else if(extremes[3][1]/W_W < -0.95f)
        {
            dist = -(0.95f * W_W) - extremes[3][1];
            translateCarXY(0,dist);
        }

    }

}

void set_window_size(GLsizei w, GLsizei h)
{
    glutReshapeWindow(W_W,W_H);
}

void translate(int i, float x, float y, int jX, int jY, float qtX, float qtY)
{

    int k, j;
    float vector[1][3] = {0.0f,0.0f,1.0f};

    float mA[1][3] = {x,y,1};

    float mB[3][3] =
    {
        {1.0f,     0.0f,      0.0f},
        {0.0f,     1.0f,      0.0f},
        {qtX,      qtY,       1.0f}
    };

    for(k=0; k<3; k=k+1)
    {
        for(j=0; j<3; j=j+1)
        {
            vector[0][k] = vector[0][k] + (mA[0][j] * mB[j][k]);
        }
    }

    vector[0][2] = 1.0f;

    car[i][jX] = vector[0][0];
    car[i][jY] = vector[0][1];

}

void rotate(int i, float x, float y, int jX, int jY, float a)
{

    int k, j;
    float vector[1][3] = {0.0f,0.0f,1.0f};

    float mA[1][3] = {x-xRef,y-yRef,1};
    float mB[3][3] =
    {
        {cos(a*(3.14159265/180)),       sin(a*(3.14159265/180)),  0},
        {-sin(a*(3.14159265/180)),      cos(a*(3.14159265/180)),  0},
        {0.0f,                          0.0f,                     1.0f}
    };

    for(k=0; k<3; k=k+1)
    {
        for(j=0; j<3; j=j+1)
        {
            vector[0][k] = vector[0][k] + (mA[0][j] * mB[j][k]);
        }
    }

    vector[0][2] = 1.0f;

    car[i][jX] = vector[0][0] + xRef;
    car[i][jY] = vector[0][1] + yRef;

}

void translateCar()
{
    int i, j;
    for(i=0; i<86; i=i+1)
    {
        for(j=0; j<4; j=j+2)
        {
            if(modeDirection == MODE_FORWARD)translate(i, car[i][j], car[i][j+1], j, j+1, direction[1], direction[0]);
            else if(modeDirection == MODE_BACKWARD)translate(i, car[i][j], car[i][j+1], j, j+1, -direction[1], -direction[0]);
        }
    }
}

void translateCarXY(float qtX, float qtY)
{
    int i, j;
    for(i=0; i<86; i=i+1)
    {
        for(j=0; j<4; j=j+2)
        {
            translate(i, car[i][j], car[i][j+1], j, j+1, qtX, qtY);
        }
    }
}

void special_keys(int key, int x, int y)
{
    float cosseno, seno;
    cosseno = cos(angle*(3.14159265/180));
    seno = sin(angle*(3.14159265/180));
    if(key == GLUT_KEY_UP)
    {
        if(modeDirection == MODE_FORWARD)
        {
            mode = MODE_TRANSLATE;
            direction[1] = velocity * -seno;
            direction[0] = velocity * cosseno;
            RUN = 1;
        }
        else
        {
            direction[1] = 0;
            direction[0] = 0;
        }
    }
    else if(key == GLUT_KEY_LEFT)
    {
        mode = MODE_ROTATE;
        angle = angle + 1.0f;
        RUN = 1;
    }
    else if(key == GLUT_KEY_RIGHT)
    {
        mode = MODE_ROTATE;
        angle = angle - 1.0f;
        RUN = 1;
    }
    else if (key == GLUT_KEY_DOWN)
    {
        if(modeDirection == MODE_BACKWARD)
        {
            mode = MODE_TRANSLATE;
            direction[1] = velocity * -seno;
            direction[0] = velocity * cosseno;
            RUN = 1;
        }
        else
        {
            direction[1] = 0;
            direction[0] = 0;
        }
    }
    else if(key == GLUT_KEY_F2)
    {
        light = !light;
    }
    else if(key == GLUT_KEY_F3)
    {
        if(modeScreen == MODE_GAME || modeScreen == MODE_ABOUT) modeScreen = MODE_MENU;
        else modeScreen = MODE_GAME;
    }
    else if(key == GLUT_KEY_F4)
    {
        if(modeScreen == MODE_GAME || modeScreen == MODE_MENU) modeScreen = MODE_ABOUT;
        else modeScreen = MODE_GAME;
    }
    glutPostRedisplay();
}

void keys(unsigned char key, int x, int y)
{
    if(key == MODE_FORWARD && modeDirection != MODE_FORWARD)
    {
        mode = MODE_ROTATE;
        modeDirection = MODE_FORWARD;
    }
    else if(key == MODE_BACKWARD && modeDirection != MODE_BACKWARD)
    {
        mode = MODE_ROTATE;
        modeDirection = MODE_BACKWARD;
    }
    else if(key == FAST)
    {
        velocity++;
        printf("velocity is %d\n",velocity);
    }
    else if(key == SLOW)
    {
        velocity--;
        if(velocity < 1) velocity = 1;
        printf("velocity is %d\n",velocity);
    }
    else if(key == 27)
    {
        exit(0);
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    int i, j;
    glutInit(&argc, argv);
    glutInitWindowSize(W_W,W_H);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Park Game");
    glutDisplayFunc(paint);
    glutKeyboardFunc(keys);
    glutReshapeFunc(set_window_size);
    glutSpecialFunc(special_keys);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0,1.0,-1.0,1.0);
    glClearColor(0.5,0.5,0.5,0.0);
    for(i=0; i<86; i=i+1)
    {
        for(j=0; j<4; j=j+2)
        {
            translate(i, car[i][j], car[i][j+1], j, j+1, 500, -650);
        }
    }
    glutMainLoop();
    return 0;
}
