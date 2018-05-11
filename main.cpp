
#include <iostream>
#include <GL/glut.h>
#include <cstdlib>
#include <vector> 
#include <math.h>

int width = 500;
int height = 500;

enum drawMode{
  cube, pyramid
};

enum rotateDir{
  right, left
};

enum rotateAxis{
  xAxis, yAxis, zAxis
};

GLint moving = 0;

//typedef GLfloat Point[3];
typedef std::vector<GLfloat> Point;

typedef struct Obj{
  std::vector<Point> points;
}Obj;

Obj obj; 

drawMode drawMode; 
Point click; 

void test() {
   std::cout <<"here"; 
   fflush(stdout);
}

// the current version  is 3x3
Point multMatrix(Point point, std::vector<Point> matrix){
  Point aux;
  aux.push_back(point[0]);
  aux.push_back(point[1]);
  aux.push_back(point[2]);
  aux.push_back(1.0);
  point[0] = matrix[0][0]*aux[0] +  matrix[0][1]*aux[1] + matrix[0][2]*aux[2] + matrix[0][3]*aux[3];
  point[1] = matrix[1][0]*aux[0] +  matrix[1][1]*aux[1] + matrix[1][2]*aux[2] + matrix[1][3]*aux[3];
  point[2] = matrix[2][0]*aux[0] +  matrix[2][1]*aux[1] + matrix[2][2]*aux[2] + matrix[2][3]*aux[3];
  std::cout<<"\n\n"<< point[0] << point[1] << point[2];
  
  return point;
}


void rotate(rotateDir dir, rotateAxis axis){
  Point mPoint;
  std::vector<Point> matrix;
  GLfloat x, y, z;
  GLfloat rad, sine, cosine; 
  const GLfloat angle = 10;
  if(dir == right){
    rad = 2*M_PI*(angle)/360.0;
  }else{
    rad = 2*M_PI*(-angle)/360.0;
  }
  sine = sin(rad);
  cosine = cos(rad);
  x = 0;
  y = 0;
  z = 0;
  switch(axis){
    case xAxis:
      x = 1;
    break;
    case yAxis:
      y = 1;
    break;
    case zAxis:
      z = 1;
    break;
  }
  mPoint.push_back(x*x*(1-cosine)+cosine);
  mPoint.push_back(x*y*(1-cosine)-z*sine);
  mPoint.push_back(x*z*(1-cosine)+y*sine);
  mPoint.push_back(0.0);
  matrix.push_back(mPoint);

  mPoint[0] = y*x*(1-cosine)+z*sine;
  mPoint[1] = y*y*(1-cosine)+cosine;
  mPoint[2] = y*z*(1-cosine)-x*sine;
  mPoint[3] = 0.0;
  matrix.push_back(mPoint);

  mPoint[0] = z*x*(1-cosine)-y*sine;
  mPoint[1] = z*y*(1-cosine)+x*sine;
  mPoint[2] = z*z*(1-cosine)+cosine;
  mPoint[3] = 0.0;
  matrix.push_back(mPoint);

  mPoint[0] = 0.0;
  mPoint[1] = 0.0;
  mPoint[2] = 0.0;
  mPoint[3] = 1.0;
  matrix.push_back(mPoint);

  for(GLint i = 0; i < obj.points.size(); i++){
    obj.points[i] = multMatrix(obj.points[i], matrix);
  }

}

void scale(GLfloat ds){
  Point mPoint;
  std::vector<Point> matrix;

  mPoint.push_back(ds);
  mPoint.push_back(0.0);
  mPoint.push_back(0.0);
  mPoint.push_back(0.0);
  matrix.push_back(mPoint);

  mPoint[0] = 0.0;
  mPoint[1] = ds;
  mPoint[2] = 0.0;
  mPoint[3] = 0.0;
  matrix.push_back(mPoint);

  mPoint[0] = 0.0;
  mPoint[1] = 0.0;
  mPoint[2] = ds;
  mPoint[3] = 0.0;
  matrix.push_back(mPoint);

   mPoint[0] = 0.0;
  mPoint[1] = 0.0;
  mPoint[2] = 0.0;
  mPoint[3] = 1.0;
  matrix.push_back(mPoint);

  for(GLint i = 0; i < obj.points.size(); i++){
    obj.points[i] = multMatrix(obj.points[i], matrix);
  }
  std::cout << "\n ponto zero = " <<obj.points[0][0];  
}

void translate(GLfloat dx, GLfloat dy, GLfloat dz){
  Point mPoint;
  std::vector<Point> matrix;

  mPoint.push_back(1.0);
  mPoint.push_back(0.0);
  mPoint.push_back(0.0);
  mPoint.push_back(dx);
  matrix.push_back(mPoint);

  mPoint[0] = 0.0;
  mPoint[1] = 1.0;
  mPoint[2] = 0.0;
  mPoint[3] = dy;
  matrix.push_back(mPoint);

  mPoint[0] = 0.0;
  mPoint[1] = 0.0;
  mPoint[2] = 1.0;
  mPoint[3] = dz;
  matrix.push_back(mPoint);

   mPoint[0] = 0.0;
  mPoint[1] = 0.0;
  mPoint[2] = 0.0;
  mPoint[3] = 1;
  matrix.push_back(mPoint);

  for(GLint i = 0; i < obj.points.size(); i++){
    obj.points[i] = multMatrix(obj.points[i], matrix);
  }
}


void drawPyramid(){
  const GLint P_SIZE = 1;
  std::vector<Point> newPoints;
  Point point; 

  point.push_back(0.0);
  point.push_back(0.0);
  point.push_back(0.0);
  newPoints.push_back(point);
  point[0] = P_SIZE;
  point[1] = 0.0;
  point[2] = 0.0;
  newPoints.push_back(point);

    point[0] = 0.0;
  point[1] = 0.0;
  point[2] = 0.0;
  newPoints.push_back(point);
  point[0] = 0.0;
  point[1] = P_SIZE;
  point[2] = 0.0;
  newPoints.push_back(point);


    point[0] = P_SIZE;
  point[1] = 0.0;
  point[2] = 0.0;
  newPoints.push_back(point);
  point[0] = P_SIZE;
  point[1] = P_SIZE;
  point[2] = 0.0;
  newPoints.push_back(point);

    point[0] = 0.0;
  point[1] = P_SIZE;
  point[2] = 0.0;
  newPoints.push_back(point);
  point[0] = P_SIZE;
  point[1] = P_SIZE;
  point[2] = 0.0;
  newPoints.push_back(point);

    point[0] = 0.0;
  point[1] = 0.0;
  point[2] = 0.0;
  newPoints.push_back(point);
  point[0] = P_SIZE/2.0;
  point[1] = P_SIZE/2.0;
  point[2] = P_SIZE;
  newPoints.push_back(point);

  point[0] = 0.0;
  point[1] = P_SIZE;
  point[2] = 0.0;
  newPoints.push_back(point);
  point[0] = P_SIZE/2.0;
  point[1] = P_SIZE/2.0;
  point[2] = P_SIZE;
  newPoints.push_back(point);

  point[0] = P_SIZE;
  point[1] = 0.0;
  point[2] = 0.0;
  newPoints.push_back(point);
  point[0] = P_SIZE/2.0;
  point[1] = P_SIZE/2.0;
  point[2] = P_SIZE;
  newPoints.push_back(point);

  point[0] = P_SIZE;
  point[1] = P_SIZE;
  point[2] = 0.0;
  newPoints.push_back(point);
  point[0] = P_SIZE/2.0;
  point[1] = P_SIZE/2.0;
  point[2] = P_SIZE;
  newPoints.push_back(point);



  point[0] = 0.5;
  point[1] = 0.5;
  point[2] = 0.5;
  newPoints.push_back(point);

  obj.points = newPoints;

  translate(-0.5 ,-0.5,-0.5);
}


void drawCube(){
  const GLfloat CUBE_SIZE = 1;
  std::vector<Point> newPoints;
  Point point; 

  point.push_back(0.0);
  point.push_back(0.0);
  point.push_back(0.0);
  newPoints.push_back(point);
  point[0] = CUBE_SIZE;
  point[1] = 0.0;
  point[2] = 0.0;
  newPoints.push_back(point);

  point[0] = 0.0;
  point[1] = 0.0;
  point[2] = 0.0;
  newPoints.push_back(point);
  point[0] = 0.0;
  point[1] = CUBE_SIZE;
  point[2] = 0.0;
  newPoints.push_back(point);

  point[0] = 0.0;
  point[1] = 0.0;
  point[2] = 0.0;
  newPoints.push_back(point);
  point[0] = 0.0;
  point[1] = 0.0;
  point[2] = CUBE_SIZE;
  newPoints.push_back(point);

  point[0] = CUBE_SIZE;
  point[1] = 0.0;
  point[2] = 0.0;
  newPoints.push_back(point);
  point[0] = CUBE_SIZE;
  point[1] = CUBE_SIZE;
  point[2] = 0.0;
  newPoints.push_back(point);

  point[0] = CUBE_SIZE;
  point[1] = 0.0;
  point[2] = 0.0;
  newPoints.push_back(point);
  point[0] = CUBE_SIZE;
  point[1] = 0.0;
  point[2] = CUBE_SIZE;
  newPoints.push_back(point);

  point[0] = 0.0;
  point[1] = CUBE_SIZE;
  point[2] = 0.0;
  newPoints.push_back(point);
  point[0] = CUBE_SIZE;
  point[1] = CUBE_SIZE;
  point[2] = 0.0;
  newPoints.push_back(point);

  point[0] = 0.0;
  point[1] = CUBE_SIZE;
  point[2] = 0.0;
  newPoints.push_back(point);
  point[0] = 0.0;
  point[1] = CUBE_SIZE;
  point[2] = CUBE_SIZE;
  newPoints.push_back(point);

  point[0] = 0.0;
  point[1] = 0.0;
  point[2] = CUBE_SIZE;
  newPoints.push_back(point);
  point[0] = 0.0;
  point[1] = CUBE_SIZE;
  point[2] = CUBE_SIZE;
  newPoints.push_back(point);

  point[0] = 0.0;
  point[1] = 0.0;
  point[2] = CUBE_SIZE;
  newPoints.push_back(point);
  point[0] = CUBE_SIZE;
  point[1] = 0.0;
  point[2] = CUBE_SIZE;
  newPoints.push_back(point);

  point[0] = 0.0;
  point[1] = CUBE_SIZE;
  point[2] = CUBE_SIZE;
  newPoints.push_back(point);
  point[0] = CUBE_SIZE;
  point[1] = CUBE_SIZE;
  point[2] = CUBE_SIZE;
  newPoints.push_back(point);

  point[0] = CUBE_SIZE;
  point[1] = 0.0;
  point[2] = CUBE_SIZE;
  newPoints.push_back(point);
  point[0] = CUBE_SIZE;
  point[1] = CUBE_SIZE;
  point[2] = CUBE_SIZE;
  newPoints.push_back(point);

  point[0] = CUBE_SIZE;
  point[1] = CUBE_SIZE;
  point[2] = 0.0;
  newPoints.push_back(point);
  point[0] = CUBE_SIZE;
  point[1] = CUBE_SIZE;
  point[2] = CUBE_SIZE;
  newPoints.push_back(point);

  point[0] = 0.5;
  point[1] = 0.5;
  point[2] = 0.5;
  newPoints.push_back(point);

  obj.points = newPoints;

  translate(-0.5 ,-0.5,-0.5);


/*
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(CUBE_SIZE, 0, 0);
  glEnd();
  glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(0, CUBE_SIZE, 0);
  glEnd();
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, CUBE_SIZE);
  glEnd();

    glBegin(GL_LINES);
    glVertex3f(CUBE_SIZE, 0, 0);
    glVertex3f(CUBE_SIZE, CUBE_SIZE, 0);
  glEnd();
    glBegin(GL_LINES);
    glVertex3f(CUBE_SIZE, 0, 0);
    glVertex3f(CUBE_SIZE, 0, CUBE_SIZE);
  glEnd();

      glBegin(GL_LINES);
    glVertex3f(0, CUBE_SIZE, 0);
    glVertex3f(CUBE_SIZE, CUBE_SIZE, 0);
  glEnd();
    glBegin(GL_LINES);
    glVertex3f(0, CUBE_SIZE, 0);
    glVertex3f(0, CUBE_SIZE, CUBE_SIZE);
  glEnd();


      glBegin(GL_LINES);
    glVertex3f(0, 0, CUBE_SIZE);
    glVertex3f(0, CUBE_SIZE, CUBE_SIZE);
  glEnd();
    glBegin(GL_LINES);
    glVertex3f(0, 0, CUBE_SIZE);
    glVertex3f(CUBE_SIZE, 0, CUBE_SIZE);
  glEnd();
  
  glBegin(GL_LINES);
    glVertex3f(CUBE_SIZE, 0, CUBE_SIZE);
    glVertex3f(CUBE_SIZE, CUBE_SIZE, CUBE_SIZE);
  glEnd();
    glBegin(GL_LINES);
    glVertex3f(0, CUBE_SIZE, CUBE_SIZE);
    glVertex3f(CUBE_SIZE, CUBE_SIZE, CUBE_SIZE);
  glEnd();
    glBegin(GL_LINES);
    glVertex3f(CUBE_SIZE, CUBE_SIZE, 0);
    glVertex3f(CUBE_SIZE, CUBE_SIZE, CUBE_SIZE);
  glEnd();
*/
}

  void drawObj(){
    glColor3f(0.0, 0.0, 0.0);
    for(GLint i = 0; i < obj.points.size()/2; i++){
      glBegin(GL_LINES);
        glVertex3f(obj.points[2*i][0], obj.points[2*i][1], obj.points[2*i][2]);
        glVertex3f(obj.points[2*i+1][0], obj.points[2*i+1][1], obj.points[2*i+1][2]);
      glEnd();
    std::cout << "point "<<obj.points[i][0] <<"point "<<obj.points[i][1] <<"point "<<obj.points[i][2] << "\n";
    fflush(stdout);      
    }
  }


/**
 * @desc Desenha eixos de um sistema de coordenadas.
 * @param {float*} basePoint Ponto de origem de um sistema de coordenadas.
 * @param {float*} i Primeiro versor.
 * @param {float*} j Segundo versor.
 * @param {float*} k Terceiro versor.
 */
void drawAxes(float *basePoint, float *i, float *j, float *k)
{
  float currentColor[4];
  /** Armazena cor atual */
  glGetFloatv(GL_CURRENT_COLOR, currentColor);  
  /** Desenha versores */
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_LINES);
    glVertex3f(basePoint[0], basePoint[1], basePoint[2]);
    glVertex3f(i[0], i[1], i[2]);
  glEnd();
  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_LINES);
    glVertex3f(basePoint[0], basePoint[1], basePoint[2]);
    glVertex3f(j[0], j[1], j[2]);
  glEnd();
  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_LINES);
    glVertex3f(basePoint[0], basePoint[1], basePoint[2]);
    glVertex3f(k[0], k[1], k[2]);
  glEnd();
  /** Retorna para cor anterior */
  glColor3f(currentColor[0], currentColor[1], currentColor[2]);
}

/**
 * @desc Desenha as coordenadas globais.
 */
void drawWCAxes()
{
  float *basePoint, *i, *j, *k;
  basePoint = new float[3];
  basePoint[0] = basePoint[1] = basePoint[2] = 0.0;
  i = new float[3];
  i[0] = 5.0;
  i[1] = i[2] = 0.0;
  j = new float[3];
  j[0] = j[2] = 0.0;
  j[1] = 5.0;
  k = new float[3];
  k[0] = k[1] = 0.0;
  k[2] = 5.0;
  drawAxes(basePoint, i, j, k);
}

/**
 * @desc Fun��o de callback para desenho na tela.
 */
void displayCallback()
{
  /** Limpa a janela APENAS uma vez */
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(1.0f, 0.0f, 0.0f);
  /** Desenha a janela mais a esquerda */
  glViewport(0, 0, width, height);
  glLoadIdentity();
  gluLookAt(3.0, 2.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  drawWCAxes();
  glRotatef(-90.0, 1.0, 0.0, 0.0);
//glutWireCone(1.0, 2.0, 4, 4);
 /* switch(drawMode){
    case cube:
      drawCube();
      break;
    case pyramid:
      drawPyramid();
      break;
  }*/
  drawObj();
  /** Desenha a janela mais a direita */
  /*glViewport(width/2, 0, width/2, height);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  drawWCAxes();
  glRotatef(-90.0, 1.0, 0.0, 0.0);
  //glutWireCone(1.0, 2.0, 4, 4);
drawObj();
  /** Dispara os comandos APENAS uma vez */
  glFlush();
}

/**
 * @desc Fun��o de callback para reshape.
 * @param {int} w Nova largura da janela.
 * @param {int} h Nova altura da janela.
 */
void reshapeCallback(int w, int h)
{
  /** Atualiza os valores da janela */
  width = w;
  height = h;
  /** Define o volume de vista */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, (GLfloat) width/(GLfloat) height, 1.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
}



void menuHandler(GLint item_number)
{
  glutPostRedisplay();
  switch(item_number){
    case 0:
      drawMode = cube;
      drawCube();
      break;
    case 1:
      drawMode = pyramid;
      drawPyramid();
      break;
  }

}

void createMenu(){
  GLint menu_id = glutCreateMenu(menuHandler);  
  glutAddMenuEntry("Cubo", 0);
  glutAddMenuEntry("Piramide", 1);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

}

void mouseHandler(GLint button, GLint action, GLint x, GLint y){
  if(action == GLUT_DOWN){
    click[0]= x;
    click[1]= y;
    moving = 1; 
  }else{
    moving = 0;
  }
}
void movingHanlder(GLint x, GLint y){
  if(moving){
    GLfloat x0, y0, z0;
    x0 = obj.points[obj.points.size()-1][0];
    y0 = obj.points[obj.points.size()-1][1];
    z0 = obj.points[obj.points.size()-1][2];
    //translate(-x0, -y0, -z0);
    translate((x-click[0])/5000.0, (y-click[1])/5000.0, z0);
    displayCallback();
  }
}


void keybordHandler(GLubyte key, GLint x, GLint y){
  GLint m = glutGetModifiers();
  GLfloat x0, y0, z0;
  x0 = obj.points[obj.points.size()-1][0];
  y0 = obj.points[obj.points.size()-1][1];
  z0 = obj.points[obj.points.size()-1][2];
  std::cout <<  "center" << x0 << y0 << z0 <<"\n";
  if(m == GLUT_ACTIVE_SHIFT){  
    if(key == 43){ // + 
      translate(-x0, -y0, -z0);
      scale(2.0);
      translate(x0, y0, z0);
    }
  }
    else if(key == 45){ // -
      translate(-x0, -y0, -z0);
      scale(1/2.0);
      translate(x0, y0, z0);
    }
    else if(key == 120){ //x
      translate(-x0, -y0, -z0);
      rotate(right, xAxis);
      translate(x0, y0, z0);
    }else if(key == 121){ //y
      translate(-x0, -y0, -z0);
      rotate(right, yAxis);
      translate(x0, y0, z0);
    }else if(key == 122){ //z
      translate(-x0, -y0, -z0);
      rotate(right, zAxis);
      translate(x0, y0, z0);
    }
    if(key == 88){ //x
      translate(-x0, -y0, -z0);
      rotate(left, xAxis);
      translate(x0, y0, z0);
    }else if(key == 89){ //y
      translate(-x0, -y0, -z0);
      rotate(left, yAxis);
      translate(x0, y0, z0);
    }else if(key == 90){ //z
      translate(-x0, -y0, -z0);
      rotate(left, zAxis);
      translate(x0, y0, z0);
    }
  
  displayCallback();
}

int main(int argc, char **argv){

  GLint screen_height, screen_width;
  /** Passo 1: Inicializa fun��es GLUT */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  screen_width  = glutGet(GLUT_SCREEN_WIDTH),
  screen_height = glutGet(GLUT_SCREEN_HEIGHT); 
  glutInitWindowPosition(screen_width/2 - width/2, screen_height/2 - height/2);
  glutInitWindowSize(width, height);
  glutCreateWindow("Pratica 2");
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  /** Passo 2: Registra callbacks da OpenGl */
  glutDisplayFunc(displayCallback);
  glutReshapeFunc(reshapeCallback);
  glutMouseFunc(mouseHandler);
  glutKeyboardFunc(keybordHandler);
  glutMotionFunc(movingHanlder);
 // glutmo
  createMenu();
  click.push_back(0);
  click.push_back(0);
  /** Passo 3: Executa o programa */
  glutMainLoop();
  return 0;
}
