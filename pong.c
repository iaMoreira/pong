/**
    CS-11 Asn 6
    test.c
    Purpose: To create a game using OpenGL.

    @author Ian Moreira
    @version 4.0 18/01/18
*/

#include <GL/glut.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Mix_Music *musica = NULL; //- música de fundo
Mix_Chunk *beep = NULL;  //- efeito sonoro mixável.
Mix_Chunk *beep2 = NULL;  //- efeito sonoro mixável.
Mix_Chunk *laser =NULL;


// Variáveis para movimentação dos objetos
int xBarra1 = 415, yBarra1 = 90;
int xBarra2 = 20, yBarra2 = 90;
float stepX = -1, stepY = -1;         // variável que altera a a bola
float xMovBall = 210, yMovBall = 110; // valores da posição da bola

// placar
int player1 = 0, player2 = 0, pause = 0, showCongratulation = 0;

// variaveis resposaveis por identificar todas as teclas
_Bool keyPressed[256] = {0};

//Variável para teste de direção
int down = 0;

// time.h
clock_t tInicio, tFim, tDecorrido;
int tempo = 0, min =0;

// Players Score
char playerScore1[10] = "score = 0";
char playerScore2[10] = "score = 0";
char congratulation[20] = "";

int seta = 0, end = 0, status = 3, c = 0;

void drawsBar(int x1, int x2, int y1, int y2);
void initialize(void);
void draws(void);
void drawsFiel();
void drawsText(void *font, char *string);
void draws(void);
void AlteraTamanhoJanela(GLsizei w, GLsizei h);
void keyBoardDown(unsigned char tecla, int x, int y);
void keyBoardUp(unsigned char tecla, int x, int y);
void specialDown(GLint tecla, int x, int y);
void specialUp(GLint tecla, int x, int y);
void moveBall();
void movePlayers();
void funTime(int value);
void apresentacao();
void printText(char *string, int x, int y);
void creditosView();
void jogo();
void tutorial();
void direction();

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);

    glutInitWindowPosition(0, 0);
    glutCreateWindow("IAN");
    glutDisplayFunc(draws);
    glutReshapeFunc(AlteraTamanhoJanela);

    // Registra a função para tratamento das teclas ASCII
    glutKeyboardFunc(keyBoardDown);
    glutKeyboardUpFunc(keyBoardUp);

    // Registra a função para tratamento das teclas NÂO ASCII
    glutSpecialFunc(specialDown);
    glutSpecialUpFunc(specialUp);

    glutTimerFunc(1000 / 60, funTime, 1);
    initialize();
    glutMainLoop();
}

void drawsBar(int x1, int x2, int y1, int y2)
{

    glBegin(GL_QUADS);
    glVertex2i(x1, y1);
    glVertex2i(x1, y2);
    glVertex2i(x2, y2);
    glVertex2i(x2, y1);
    glEnd();
}

void initialize(void)
{
    // Define a janela de visualização 2D
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 450, 0, 250); //Exibição Bidimensional

    SDL_Init(SDL_INIT_AUDIO);
    atexit(SDL_Quit);
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 1024 ); //- inicializa SDL_Mixer
    atexit(Mix_CloseAudio);
    //musica = Mix_LoadMUS("Jocelyn Flores.mp3");
    musica = Mix_LoadMUS("Take On Me 8 Bit .mp3");
    beep = Mix_LoadWAV("Beep1.wav");
    beep2 = Mix_LoadWAV("Beep2.wav");
    laser = Mix_LoadWAV("Laser.wav");
    Mix_PlayMusic( musica, -1 );


}

void drawsFiel()
{
     glColor3ub(255, 255, 255); //Especifica a cor de desenho
    // Limites da área do jogo
    glLineWidth(50.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(5, 5);
    glVertex2f(5, 220);
    glVertex2f(440, 220);
    glVertex2f(440, 5);
    glVertex2f(5, 5);
    glVertex2f(440, 5);
    glEnd();
  
    glBegin(GL_LINE_LOOP);
    glVertex2f(225, 5);
    glVertex2f(225, 220);
    glEnd();
    
    glColor3ub(42, 157, 188); //Especifica a cor de desenho
    // Limites da área do jogo
    glLineWidth(6.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(5, 5);
    glVertex2f(5, 220);
    glVertex2f(440, 220);
    glVertex2f(440, 5);
    glVertex2f(5, 5);
    glVertex2f(440, 5);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(225, 5);
    glVertex2f(225, 220);
    glEnd();

    glColor3ub(0, 41, 80); //Especifica a cor de desenho
    // Limites da área do jogo
    glLineWidth(4.5);
    glBegin(GL_LINE_LOOP);
    glVertex2f(5, 5);
    glVertex2f(5, 220);
    glVertex2f(440, 220);
    glVertex2f(440, 5);
    glVertex2f(5, 5);
    glVertex2f(440, 5);
    glEnd();

    //Linha da divisoria
    glBegin(GL_LINE_LOOP);
    glVertex2f(225, 5);
    glVertex2f(225, 220);
    glEnd();
}

void drawsText(void *font, char *string)
{
    // Exibe caractere a caractere
    while (*string)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *string++);
}

void draws(void)
{
    switch (status)
    {
    case 1:
        jogo();
        break;
    case 2:
        creditosView();
        break;
    case 3:
        apresentacao();
        break;
    case 4:
        tutorial();
    }
    glutSwapBuffers();
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Evita a divisao por zero
    if (h == 0)
        h = 1;

    // Especifica as dimensões da Viewport
    glViewport(0, 0, w, h);

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Estabelece a janela de seleção (left, right, bottom, top)
    if (w <= h)
        gluOrtho2D(0.0f, 250.0f, 0.0f, 250.0f * h / w);
    else
        gluOrtho2D(0.0f, 250.0f * w / h, 0.0f, 250.0f);
}

void keyBoardDown(unsigned char tecla, int x, int y)
{
    keyPressed[tecla] = 1;
    if (tecla == ' ' && pause == 1)
    {
        pause = 0;
    }
    else if (tecla == ' ' && pause == 0)
    {
        pause = 1;
    }
    if (tecla == 13 && seta % 5 == 0)
    {
        status = 1;
        c = 1;
        end = 0;
        pause = 0;
        sprintf(congratulation, "%c", ' ');
        showCongratulation = 0;
    }

    if(tecla == 13 && seta %5 == 1){
        status =4;
    }
    if (tecla == 13 && seta % 5 == 3)
        status = 2;
    if (tecla == 13 && seta % 5 == 4)
        keyPressed[27] = 1;
    if(tecla == ' ' && status == 4 )
        status =3;
    
}

void keyBoardUp(unsigned char tecla, int x, int y)
{
    keyPressed[tecla] = 0;
}

void specialDown(GLint tecla, int x, int y)
{
    if (tecla == GLUT_KEY_UP)
    {
        keyPressed[250] = 1;
        if (seta == 0)
            seta += 4;
        else
            seta--;
    }
    if (tecla == GLUT_KEY_DOWN)
    {
        keyPressed[251] = 1;
        seta++;
    }
}

void specialUp(GLint tecla, int x, int y)
{
    if (tecla == GLUT_KEY_UP)
    {
        keyPressed[250] = 0;
    }
    if (tecla == GLUT_KEY_DOWN)
    {
        keyPressed[251] = 0;
    }
}

void moveBall()
{

    if (!end)
    {
        if ((player1 >= 10 || player2 >= 10) && abs(player1 - player2) > 1)
        {
            (player1 > player2) ? sprintf(congratulation, "Parabens jogador 2") : sprintf(congratulation, "Parabens jogador 1");
            showCongratulation = 1;
            end = 1;
            c = 0;
        }

        // Points scored by players
        if (xMovBall >= 440)
        {   
            Mix_PlayChannel( -1, laser, 0 );
            xMovBall = xBarra2 + 10;
            yMovBall = yBarra2 + 30;
            player2++;
            sprintf(playerScore2, "score = %i", player2);
            return;
        }

        if (xMovBall <= 5)
        {
            Mix_PlayChannel( -1, laser, 0 );
            xMovBall = xBarra1 - 10;
            yMovBall = yBarra1 + 30;
            player1++;
            sprintf(playerScore1, "score = %i", player1);
            return;
        }

        if (xMovBall + 8 > xBarra1 && yMovBall <= yBarra1 + 60 && yMovBall + 10 >= yBarra1)
        {
            xMovBall += 2;
            if(yMovBall > yBarra1+30){
                yMovBall += 2;
                stepY = 1;
            }
            else{
                yMovBall -= 2;
                stepY = 1;
            }
            return;
        }
        if (xMovBall < xBarra2 + 8 && yMovBall <= yBarra2 + 60 && yMovBall + 10 >= yBarra2)
        {
            stepY *= -1;
            xMovBall -= 2;
            if(yMovBall > yBarra2+30)
                yMovBall += 2;
            else
                yMovBall -= 2;
            return;
        }

        // Collision of the sides of the fiel ( Verifica se a bola bateu nas paredes e inverte os Y)

        if (yMovBall >= 210)
            stepY *= -1;

        if (yMovBall <= 5)
            stepY *= -1;
        direction();

        // if (xMovBall + 10 >= xBarra1 && yMovBall <= yBarra1 + 60 && yMovBall >= yBarra1)
        // {
        //     stepX *= -1;
        //     stepY *= -1;
        //     xMovBall -= 2;
        //     return;
        // }

        // if (xMovBall <= xBarra2 + 10 && yMovBall <= yBarra2 + 60 && yMovBall >= yBarra2)
        // {
        //     stepX *= -1;
        //     stepY *= -1;
        //     xMovBall += 2;
        //     return;
        // }
        if (pause == 0)
        {
            showCongratulation = 0;
            yMovBall += stepY;
            xMovBall += stepX;
        }

        /* Verifica se ta pausada e vai sumando as variavéis que determinan as direções
        e  a distancia */
    }
    else if (pause == 1)
    {
        end = 0;
        pause = 0;
        status = 2;
        showCongratulation = 0;
        xMovBall = 215;
        yMovBall = 110;
        player1 = 0;
        player2 = 0;
        sprintf(playerScore1, "score = %i", player1);
        sprintf(playerScore2, "score = %i", player2);
    }
}

void movePlayers()
{
    if (keyPressed['w'] && (yBarra2 != 160))
    { // Moverá a barra do player 2 para cima
        yBarra2 += 1;
    }
    if (keyPressed['s'] && (yBarra2 != 5))
    {
        yBarra2 -= 1;
    }
    if (keyPressed[250] && (yBarra1 != 160))
    { //o programa deverá ser finalizado
        yBarra1 += 1;
    }

    if (keyPressed[251] && (yBarra1 != 5))
    { //o programa deverá ser finalizado
        yBarra1 -= 1;
    }
}

void funTime(int value)
{

    if (status == 1)
    {
        moveBall();
        movePlayers();
    }
    if (keyPressed[27])
        exit(0);

    glutPostRedisplay(); //manda rederizar a cena
    glutTimerFunc(1, funTime, 1);
}

void printText(char *string, int x, int y)
{

    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(0.05, 0.05, 0); // diminui o tamanho do fonte
    glLineWidth(1.7);          // define a espessura da linha
    glRasterPos2f(10, 10);
    drawsText(GLUT_BITMAP_TIMES_ROMAN_24, string);
    glPopMatrix();
}

void positionSetColor(int x)
{
    if (seta % 5 == x)
        glColor3ub(46, 237, 100);
    else
        glColor3ub(8, 194, 67);
}

void positionSetColor2(int x)
{
    if (seta % 5 == x)
        glColor3ub(255, 255, 255);
    else
        glColor3ub(0, 0, 0);
}
void jogo()
{
    glColor3ub(3, 24,  55);
    glClearColor(0.043, 0.152, 0.247, 0); //Especifica um cor para o fundo
    glClear(GL_COLOR_BUFFER_BIT);      //Manda limpar o fundo

    // draws a área do jogo
    drawsFiel();

    glColor3ub(214, 98, 15); //Especifica a cor de desenho
    glPushMatrix();
    glTranslated(xBarra1, yBarra1, 0.0); // Posiciona o desenho na tela
    drawsBar(0, 10, 0, 60);
    glPopMatrix();

    glColor3ub(38, 255, 166); //Especifica a cor de desenho
    glPushMatrix();
    glTranslated(xBarra2, yBarra2, 0.0);
    drawsBar(0, 10, 0, 60);
    glPopMatrix();

    glColor3ub(255, 255, 255); //Especifica a cor de desenho
    glPushMatrix();
    glTranslated(xMovBall, yMovBall, 0.0);
    drawsBar(0, 10, 0, 10);
    glPopMatrix();

    printText(playerScore2, 10, 225);

    printText(playerScore1, 400, 225);

    if (c)
    {
        tFim = clock();
        tempo = (((tFim - tInicio) / (CLOCKS_PER_SEC / 1000)) / 60) -60*min;
        char w[10];
        if(tempo == 60){
            min++;
            tempo-=60;
        }
        if(tempo >9)
            sprintf(w, "0%i:%i",min, tempo);
        else
            sprintf(w, "0%i:0%i",min, tempo);
                
        glPushMatrix();
        glTranslatef(210, 230, 0);
        glScalef(0.1, 0.1, 0.1); // diminui o tamanho do fonte
        glLineWidth(2);          // define a espessura da linha
        drawsText(GLUT_STROKE_ROMAN, w);
        glPopMatrix();
    }

    if (!showCongratulation)
    {
        // show champion player
        glColor3ub(255, 255, 255);
        glPushMatrix();
        glTranslatef(170, 230, 0);
        glScalef(0.1, 0.1, 0.1); // diminui o tamanho do fonte
        glLineWidth(2);          // define a espessura da linha
        drawsText(GLUT_STROKE_ROMAN, congratulation);
        glPopMatrix();
    }
}
void drawsBarChrom(int x1, int x2, int y1, int y2)
{

    glBegin(GL_QUADS);
    glVertex2i(x1, y1);
    glColor3ub(6, 139, 34);
    glVertex2i(x1-5, y2);
    glVertex2i(x2+5, y2);
    glColor3ub(18, 255, 88);
    glVertex2i(x2, y1);
    glEnd();
}

void apresentacao()
{

    // glColor3ub(61, 255, 28);
    // glClearColor(1, 1, 1, 0);     //Especifica um cor para o fundo
    glClearColor(0.043, 0.152, 0.247, 0); //Especifica um cor para o fundo
  
  //  glClearColor(0.23, 1.0, 0.109, 0); //Especifica um cor para o fundo
    glClear(GL_COLOR_BUFFER_BIT); //Manda limpar o fundo
   
    glColor3ub(255, 255, 255);


    // STRING PONG
    glPushMatrix();
    glTranslatef(110, 160, 0);
    glScalef(0.5, 0.5, 0.0); // diminui o tamanho do fonte
    glLineWidth(10);         // define a espessura da linha
    drawsText(GLUT_BITMAP_TIMES_ROMAN_24, "PONG");
    glPopMatrix();
    
    glColor3ub(224, 98, 15); //Especifica a cor de desenho
    printText("THE BEST GAME", 268, 182);

    //MENU
    positionSetColor(0);
    drawsBarChrom(185, 260, 120, 135);
    positionSetColor2(0);
    printText("PLAY", 215, 125);

    positionSetColor(1);
    drawsBarChrom(185, 260, 100, 115);
    positionSetColor2(1);
    printText("TUTORIAL", 210, 105);

    positionSetColor(2);
    drawsBarChrom(185, 260, 80, 95);
    positionSetColor2(2);
    printText("OPTIONS", 210, 85);

    positionSetColor(3);
    drawsBarChrom(185, 260, 60, 75);
    positionSetColor2(3);
    printText("CREDITS", 210, 65);

    positionSetColor(4);
    drawsBarChrom(185, 260, 40, 55);
    positionSetColor2(4);
    printText("EXIT", 215, 45);


    
    tInicio = clock();
}

void creditosView()
{
    static float role = 0;
    glClearColor(0.043, 0.152, 0.247, 0); //Especifica um cor para o fundo
    glClear(GL_COLOR_BUFFER_BIT); //Manda limpar o fundo

     // STRING PONG
    glPushMatrix();
    glTranslatef(100, -60 + role, 0);
    glScalef(0.5, 0.5, 0.0); // diminui o tamanho do fonte
    glLineWidth(10);         // define a espessura da linha
    drawsText(GLUT_BITMAP_TIMES_ROMAN_24, "PONG");
    glPopMatrix();
    glColor3ub(224, 98, 15); //Especifica a cor de desenho
   
    printText("THE BEST GAME", 260, -38 + role);

    glColor3ub(255, 255, 255);
    printText("Esse foi um projeto referente a materia de computacao grafica.", 100, 50 + role);
    printText("Version: 4.0  18/01/2018", 150, 40 + role);
    printText("Docente: Dr. prof. Vania Carneiro", 150, 30 + role);
    printText("Dicente: Ian Andrade Moreira.", 150, 20 + role);

   
    if (role < 150)
        role += 0.3;
    else
    {
        status = 3;
        role = 0;
    }
}

void direction()
{
    if(xMovBall > 120){
      
        if (xMovBall + 10 >= xBarra1 && yMovBall <= yBarra1 + 60 && yMovBall + 10 >= yBarra1 + 50)
        {
            Mix_PlayChannel( -1, beep, 0 );
            stepY = 1.8;
            xMovBall -= 2;
            stepX = -1;
            return;
        }


        if (xMovBall + 10 >= xBarra1 && yMovBall <= yBarra1 + 50 && yMovBall + 10 >= yBarra1 + 35)
        {
             Mix_PlayChannel( -1, beep, 0 );
            stepY = 1;
            xMovBall -= 2;
            stepX = -1.8;
            return;
        }
        
        if (xMovBall + 10 >= xBarra1 && yMovBall <= yBarra1 + 35 && yMovBall + 10 >= yBarra1 + 25)
        {
            Mix_PlayChannel( -1, beep, 0 );
            stepY = 0;
            xMovBall -= 2;
            stepX = -2;

            return;
        }
        if (xMovBall + 10 >= xBarra1 && yMovBall <= yBarra1 + 25 && yMovBall + 10 >= yBarra1 + 10)
        {
            Mix_PlayChannel( -1, beep, 0 );
            stepY = -1;
            xMovBall -= 2;
            stepX = -1.8;
            return;
        }

        if (xMovBall + 10 >= xBarra1 && yMovBall <= yBarra1 + 10 && yMovBall + 10 >= yBarra1)
        {   
            Mix_PlayChannel( -1, beep, 0 );
            stepY = -1, 8;
            xMovBall -= 2;
            stepX = -1;
            return;
        }


    }else{
        
        if (xMovBall <= xBarra2 + 10 && yMovBall <= yBarra2 + 60 && yMovBall + 10 >= yBarra2 + 50)
        {
            Mix_PlayChannel( -1, beep2, 0 );
            stepY = 1.8;
            stepX = 1;
            xMovBall += 2;
            return;
        }

        if (xMovBall <= xBarra2 + 10 && yMovBall <= yBarra2 + 50 && yMovBall + 10 >= yBarra2 + 35)
        {
             Mix_PlayChannel( -1, beep2, 0 );
            stepY = 1;
            stepX = 1.8;
            xMovBall += 2;
            return;
        }

        if (xMovBall <= xBarra2 + 10 && yMovBall <= yBarra2 + 35 && yMovBall + 10 >= yBarra2+25 )
        {
            Mix_PlayChannel( -1, beep2, 0 );
            stepY = 0;
            stepX = 2;
            xMovBall += 2;
            return;
        }


        if (xMovBall <= xBarra2 + 10 && yMovBall <= yBarra2 + 25 && yMovBall + 10 >= yBarra2 + 10)
        {
            Mix_PlayChannel( -1, beep2, 0 );
            stepY = -1;
            stepX = 1.8;
            xMovBall += 2;
            return;
        }

        if (xMovBall <= xBarra2 + 10 && yMovBall <= yBarra2 + 10 && yMovBall + 10 >= yBarra2 )
        {
            Mix_PlayChannel( -1, beep2, 0 );
            stepY = -1.8;
            stepX = 1;
            xMovBall += 2;
            return;
        }
        
    }



}

void tutorial()
{

    glClearColor(0.043, 0.152, 0.247, 0); //Especifica um cor para o fundo
    glClear(GL_COLOR_BUFFER_BIT); //Manda limpar o fundo

    glColor3ub(255, 255, 255);

    glPushMatrix();
    glTranslatef(160, 220, 0);
    glScalef(0.1, 0.1, 0.0); // diminui o tamanho do fonte
    glLineWidth(2);          // define a espessura da linha
    drawsText(GLUT_BITMAP_TIMES_ROMAN_24, "TUTORIAL");
    glPopMatrix();
    

    printText("*PLAYER 1", 170, 200);
    printText("W - UP RACKET", 170, 180);
    printText("S - DOWM RACKET", 170, 170);
    printText("*PLAYER 2", 170, 150);
    printText("^", 168.5, 133);
    printText("| - UP RACKET", 170, 130);
    printText("| - DOWM RACKET", 170, 120);

    glPushMatrix();
    glTranslatef(168.5, 121, 0);
    glScalef(0.05, 0.05, 0.0); // diminui o tamanho do fonte
    glRotatef(180, 1, 0, 0);
    glLineWidth(1); // define a espessura da linha
    drawsText(GLUT_BITMAP_TIMES_ROMAN_24, "^");
    glPopMatrix();
    
}
