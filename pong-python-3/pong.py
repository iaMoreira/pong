from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *
import sys
import time


xBarra1, yBarra1 = 415, 90
xBarra2, yBarra2 = 20, 90
stepX = stepY = -1      
xMovBall, yMovBall = 210, 110 
role = 0
    

# placar
player1 = player2 = pause = showCongratulation = 0

keyPressed = [0]*255

tInicio=  tFim= tDecorrido = 0
tempo = min = 0

# Players Score
playerScore1 = "score = 0"
playerScore2 = "score = 0"
congratulation = ""
pause = 0
seta = 0
end = c = 0
status = 3
w = 0
s = 0
s1 = 0
s2 = 0 

def main():
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB )
    glutInitWindowSize(1280,720)
    glutCreateWindow('Pong-Ian')
    glutInitWindowPosition(0, 0)

    glClearColor(0.,0.,0.,1.)
    glutDisplayFunc(display)

    glutKeyboardFunc(keyBoardDown)
    glutKeyboardUpFunc(keyBoardUp)

    glutSpecialFunc(specialDown)
    glutSpecialUpFunc(specialUp)

    glutTimerFunc(1, funTime, 1)
    glMatrixMode(GL_PROJECTION)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    gluOrtho2D(0, 450, 0, 250)
    glutMainLoop()

    return

def drawsFiel():

    glColor3ub(255, 255, 255) 

    glLineWidth(10.0)
    glBegin(GL_LINE_LOOP)
    glVertex2f(5, 5)
    glVertex2f(5, 220)
    glVertex2f(440, 220)
    glVertex2f(440, 5)
    glVertex2f(5, 5)
    glVertex2f(440, 5)
    glEnd()
  
    glBegin(GL_LINE_LOOP)
    glVertex2f(225, 5)
    glVertex2f(225, 220)
    glEnd()
    
    glColor3ub(42, 157, 188)

    glLineWidth(6.0)
    glBegin(GL_LINE_LOOP)
    glVertex2f(5, 5)
    glVertex2f(5, 220)
    glVertex2f(440, 220)
    glVertex2f(440, 5)
    glVertex2f(5, 5)
    glVertex2f(440, 5)
    glEnd()

    glBegin(GL_LINE_LOOP)
    glVertex2f(225, 5)
    glVertex2f(225, 220)
    glEnd()

    glColor3ub(0, 41, 80) 

    glLineWidth(4.5)
    glBegin(GL_LINE_LOOP)
    glVertex2f(5, 5)
    glVertex2f(5, 220)
    glVertex2f(440, 220)
    glVertex2f(440, 5)
    glVertex2f(5, 5)
    glVertex2f(440, 5)
    glEnd()

    glBegin(GL_LINE_LOOP)
    glVertex2f(225, 5)
    glVertex2f(225, 220)
    glEnd()

def creditosView():
    global role, status
    glClearColor(0.043, 0.152, 0.247, 0) 
    glClear(GL_COLOR_BUFFER_BIT) 

    glPushMatrix()
    glTranslatef(100, -60 + role, 0)
    glScalef(0.5, 0.5, 0.0) 
    glLineWidth(10)       
    glRasterPos2f(10, 10);  
    drawsText(GLUT_BITMAP_TIMES_ROMAN_24, "PONG")
    glPopMatrix()
    glColor3ub(224, 98, 15)

    printText("THE BEST GAME", 260, -38 + role)

    glColor3ub(255, 255, 255)
    printText("Esse foi um projeto referente a materia de computacao grafica.", 100, 50 + role)
    printText("Version: 4.0  18/01/2018", 150, 40 + role)
    printText("Docente: Dr. prof. Vania Carneiro", 150, 30 + role)
    printText("Dicente: Ian Andrade Moreira.", 150, 20 + role)

   
    if (role < 150):
        role += 0.3
    else:
        status = 3
        role = 0
    return

def display():
    global status, role 
    if status == 1:
        game()
    if status == 2:
        creditosView()
    if status == 3:
        apresentacao()
    if status ==  4:
        tutorial()
    glutSwapBuffers()

def drawsBar(x1, x2, y1, y2):
    glBegin(GL_QUADS)
    glVertex2i(x1, y1)
    glVertex2i(x1, y2)
    glVertex2i(x2, y2)
    glVertex2i(x2, y1)
    glEnd()    

def drawsText(font, text):
    for ch in text :
        glutBitmapCharacter( font , ctypes.c_int( ord(ch) ) )

def game():

    global tInicio,tFim,tDecorrido, min, tempo
   
    glColor3ub(3, 24,  55)
    glClearColor(0.043, 0.152, 0.247, 0)
    glClear(GL_COLOR_BUFFER_BIT)
    
    drawsFiel()

    glColor3ub(214, 98, 15) 
    glPushMatrix()
    glTranslated(xBarra1, yBarra1, 0.0) 
    drawsBar(0, 10, 0, 60)
    glPopMatrix()

    glColor3ub(38, 255, 166)
    glPushMatrix()
    glTranslated(xBarra2, yBarra2, 0.0)
    drawsBar(0, 10, 0, 60)
    glPopMatrix()

    glColor3ub(255, 255, 255)
    glPushMatrix()
    glTranslated(xMovBall, yMovBall, 0.0)
    drawsBar(0, 10, 0, 10)
    glPopMatrix()

    printText(playerScore2, 10, 225)
    printText(playerScore1, 400, 225)

    if (c):

        tempo = time.time() - tInicio -60*min
        # tempo = (((tFim - tInicio) / (CLOCKS_PER_SEC / 1000)) / 60) -60*min
        w =""
        if(tempo >= 60):
            min+=1
        if(tempo > 10):
            w =  "0%d:%d" % (min, tempo)
        else:
            w = "0%d:0%d" % (min, tempo)
        printText(w, 210, 230)

    if (not showCongratulation):
    
        #  show champion player
        glColor3ub(255, 255, 255)
        glPushMatrix()
        glTranslatef(170, 230, 0)
        glScalef(0.1, 0.1, 0.1) 
        glLineWidth(2)          
        drawsText(GLUT_BITMAP_TIMES_ROMAN_24, congratulation)
        glPopMatrix()
    return

def printText(string, x,  y):

    glPushMatrix()
    glTranslatef(x, y, 0)
    glScalef(0.05, 0.05, 0)
    glLineWidth(1.7)
    glRasterPos2f(10, 10)
    drawsText(GLUT_BITMAP_TIMES_ROMAN_24, string)
    glPopMatrix()

def keyBoardDown(tecla,  x,  y):
    global status, yBarra2,keyPressed,w,s, c, end, pause, showCongratulation, congratulation
    i = ord(tecla)
    
    keyPressed.insert(i,1)
    if (ord(tecla) == ord('s')):
        s = 1

    if( ord(tecla) == ord('w')):
        w = 1

    if (i == ord(' ') and pause == 1):
        pause = 0
    
    elif((tecla) == ord(' ') and pause == 0):
        pause = 1
    
    if ( i == 13 and seta % 5 == 0):
        status = 1
        c = 1
        end = 0
        pause = 0
        congratulation = ' '
        showCongratulation = 0

    if( i == 13 and seta % 5 == 1):
        status = 4
   
    if (i == 13 and seta % 5 == 3):
        status = 2
   
    if ( i == 13 and seta % 5 == 4):
        keyPressed.insert(27, 1)
   
    if( i == ord(' ') and status == 4 ):
        status = 3
    return

def keyBoardUp( tecla,  x,  y):
    global keyPressed,w,s
    keyPressed.insert(ord(tecla), 0)
    if (ord(tecla) == ord('s')):
        s = 0
    if( ord(tecla) == ord('w')):
        w = 0
    return

def specialDown( tecla,  x,  y):
    global seta, keyPressed, yBarra1,s1,s2

    if( tecla == GLUT_KEY_UP):
        s1 = 1
    if (tecla == GLUT_KEY_DOWN ):
        s2 = 1
        
    if (tecla == GLUT_KEY_UP):
        keyPressed.insert(250,1)
        if (seta == 0):
            seta += 4
        else:
            seta-=1
    
    if (tecla == GLUT_KEY_DOWN):
        keyPressed.insert(251,1)
        seta +=1
    return

def specialUp(tecla,  x,  y):
    global keyPressed,s1,s2

    if( tecla == GLUT_KEY_UP):
        s1 = 0
    if (tecla == GLUT_KEY_DOWN ):
        s2 = 0

    if (tecla == GLUT_KEY_UP):
        keyPressed.insert(250,0)
    
    if (tecla == GLUT_KEY_DOWN):
        keyPressed.insert(251,0)
    return

def funTime( value):
    global keyPressed

    if (status == 1):
        moveBall()
        movePlayers()

    if (keyPressed[27]):
        exit(0)

    glutPostRedisplay() 
    glutTimerFunc(1, funTime, 1)

def movePlayers():
    
    global yBarra1, yBarra2, keyPressed,w,s,s1,s2
    if (w and (yBarra2 != 160)):
        yBarra2 += 1
    if (s and (yBarra2 != 5)):
        yBarra2 -= 1
    if (s1 and ( yBarra1 != 160)):
        yBarra1 += 1
    if (s2 and (yBarra1 != 5)):
        yBarra1 -= 1

def moveBall():
    global pause,status,end, player1,player2, xBarra1, xBarra2,yMovBall, xMovBall, yBarra1, yBarra2, yMovBall, stepY, stepX,showCongratulation, playerScore1, playerScore2
   
    if (not end):
    
        if ((player1 >= 10 or player2 >= 10) and abs(player1 - player2) > 1):
       
            congratulation =  (player1 > player2) if "Parabens jogador 2" else "Parabens jogador 1"
            showCongratulation = 1
            end = 1
            c = 0
       

        if (xMovBall >= 440):
          
            xMovBall = xBarra2 + 10
            yMovBall = yBarra2 + 30
            player2+=1
            playerScore2 = "score = %d" % player2
            return

        if (xMovBall <= 5):
       
            # Mix_PlayChannel( -1, laser, 0 )
            xMovBall = xBarra1 - 10
            yMovBall = yBarra1 + 30
            player1+=1
            playerScore1 = "score = %d" % (player1)
            return
       

        if (xMovBall + 8 > xBarra1 and yMovBall <= yBarra1 + 60 and yMovBall + 10 >= yBarra1):
       
            xMovBall += 2
            
            if(yMovBall > yBarra1+30):
                yMovBall += 2
                stepY = 1
           
            else:
                yMovBall -= 2
                stepY = 1
           
            return
       
        if (xMovBall < xBarra2 + 8 and yMovBall <= yBarra2 + 60 and yMovBall + 10 >= yBarra2):
       
            stepY *= -1
            xMovBall -= 2
            if(yMovBall > yBarra2+30):
                yMovBall += 2
            else:
                yMovBall -= 2
            return
       


        if (yMovBall >= 210):
            stepY *= -1

        if (yMovBall <= 5):
            stepY *= -1
        direction()

        if (xMovBall + 10 >= xBarra1 and yMovBall <= yBarra1 + 60 and yMovBall >= yBarra1):
        
             stepX *= -1
             stepY *= -1
             xMovBall -= 2
             return
        

        if (xMovBall <= xBarra2 + 10 and yMovBall <= yBarra2 + 60 and yMovBall >= yBarra2):
        
             stepX *= -1
             stepY *= -1
             xMovBall += 2
             return
        
        if (pause == 0):
            showCongratulation = 0
            yMovBall += stepY
            xMovBall += stepX
       
        
    elif (pause == 1):
        end = 0
        pause = 0
        status = 2
        showCongratulation = 0
        xMovBall = 215
        yMovBall = 110
        player1 = 0
        player2 = 0
        playerScore1 = "score = %d" % player1
        playerScore2 = "score = %d" % player2

def positionSetColor(x):

    if (seta % 5 == x):
        glColor3ub(46, 237, 100)
    else:
        glColor3ub(8, 194, 67)

def positionSetColor2(x):

    if (seta % 5 == x):
        glColor3ub(255, 255, 255)
    else:
        glColor3ub(0, 0, 0)

def drawsBarChrom(x1, x2, y1, y2):

    glBegin(GL_QUADS)
    glVertex2i(x1, y1)
    glColor3ub(6, 139, 34)
    glVertex2i(x1-5, y2)
    glVertex2i(x2+5, y2)
    glColor3ub(18, 255, 88)
    glVertex2i(x2, y1)
    glEnd()

def apresentacao():

    global tInicio
    
    glClearColor(0.043, 0.152, 0.247, 0)
    glClear(GL_COLOR_BUFFER_BIT) 
    glColor3ub(255, 255, 255)

    #  STRING PONG
    glPushMatrix()
    glTranslatef(110, 160, 0)
    glScalef(0.5, 0.5, 0.0) 
    glLineWidth(10)
    glRasterPos2f(10, 10)
    drawsText(GLUT_BITMAP_TIMES_ROMAN_24, "PONG")
    glPopMatrix()
    
    glColor3ub(224, 98, 15) 
    printText("THE BEST GAME", 268, 182)

    #MENU
    positionSetColor(0)
    drawsBarChrom(185, 260, 120, 135)
    positionSetColor2(0)
    printText("PLAY", 215, 125)

    positionSetColor(1)
    drawsBarChrom(185, 260, 100, 115)
    positionSetColor2(1)
    printText("TUTORIAL", 210, 105)

    positionSetColor(2)
    drawsBarChrom(185, 260, 80, 95)
    positionSetColor2(2)
    printText("OPTIONS", 210, 85)

    positionSetColor(3)
    drawsBarChrom(185, 260, 60, 75)
    positionSetColor2(3)
    printText("CREDITS", 210, 65)

    positionSetColor(4)
    drawsBarChrom(185, 260, 40, 55)
    positionSetColor2(4)
    printText("EXIT", 215, 45)
    
    tInicio = time.time()   
    
def direction():
    
    global  player1,player2, xBarra1, xBarra2,yMovBall, xMovBall, yBarra1, yBarra2, yMovBall, stepY, stepX,showCongratulation
   
    if(xMovBall > 120):
      
        if (xMovBall + 10 >= xBarra1 and yMovBall <= yBarra1 + 60 and yMovBall + 10 >= yBarra1 + 50):

            stepY = 1.8
            xMovBall -= 2
            stepX = -1
            return
        


        if (xMovBall + 10 >= xBarra1 and yMovBall <= yBarra1 + 50 and yMovBall + 10 >= yBarra1 + 35):
        
            stepY = 1
            xMovBall -= 2
            stepX = -1.8
            return
        
        
        if (xMovBall + 10 >= xBarra1 and yMovBall <= yBarra1 + 35 and yMovBall + 10 >= yBarra1 + 25):
        
            stepY = 0
            xMovBall -= 2
            stepX = -2

            return
        
        if (xMovBall + 10 >= xBarra1 and yMovBall <= yBarra1 + 25 and yMovBall + 10 >= yBarra1 + 10):

            stepY = -1
            xMovBall -= 2
            stepX = -1.8
            return
        

        if (xMovBall + 10 >= xBarra1 and yMovBall <= yBarra1 + 10 and yMovBall + 10 >= yBarra1):
            
            stepY = -1.8
            xMovBall -= 2
            stepX = -1
            return
        


    else:
        
        if (xMovBall <= xBarra2 + 10 and yMovBall <= yBarra2 + 60 and yMovBall + 10 >= yBarra2 + 50):      
            
            stepY = 1.8
            stepX = 1
            xMovBall += 2
            return
        

        if (xMovBall <= xBarra2 + 10 and yMovBall <= yBarra2 + 50 and yMovBall + 10 >= yBarra2 + 35):
                   
            stepX = 1.8
            xMovBall += 2
            return
        

        if (xMovBall <= xBarra2 + 10 and yMovBall <= yBarra2 + 35 and yMovBall + 10 >= yBarra2+25 ):
        
            stepY = 0
            stepX = 2
            xMovBall += 2
            return
        


        if (xMovBall <= xBarra2 + 10 and yMovBall <= yBarra2 + 25 and yMovBall + 10 >= yBarra2 + 10):
        
            stepY = -1
            stepX = 1.8
            xMovBall += 2
            return
        

        if (xMovBall <= xBarra2 + 10 and yMovBall <= yBarra2 + 10 and yMovBall + 10 >= yBarra2 ):
        
            stepY = -1.8
            stepX = 1
            xMovBall += 2
            return
              
def tutorial():

    glClearColor(0.043, 0.152, 0.247, 0) 
    glClear(GL_COLOR_BUFFER_BIT) 

    glColor3ub(255, 255, 255)

    glPushMatrix()
    glTranslatef(160, 220, 0)
    glScalef(0.1, 0.1, 0.0)
    glLineWidth(2)          
    drawsText(GLUT_BITMAP_TIMES_ROMAN_24, "TUTORIAL")
    glPopMatrix()
    

    printText("*PLAYER 1", 170, 200)
    printText("W - UP RACKET", 170, 180)
    printText("S - DOWM RACKET", 170, 170)
    printText("*PLAYER 2", 170, 150)
    printText("^", 168.5, 133)
    printText("| - UP RACKET", 170, 130)
    printText("| - DOWM RACKET", 170, 120)

    glPushMatrix()
    glTranslatef(168.5, 121, 0)
    glScalef(0.05, 0.05, 0.0)
    glRotatef(180, 1, 0, 0)
    glLineWidth(1)
    drawsText(GLUT_BITMAP_TIMES_ROMAN_24, "^")
    glPopMatrix()
    


if __name__ == '__main__': main()
