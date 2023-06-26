#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Valores de Alpha y Phi
    alpha = 45.0;
    phi = 30.0;

    tX = tY = tZ = 0;

    xC = 0; // 150;
    yC = 0; // 100;
    zC = 0; // 50;

    rX = rY = rZ = false;
    anguloX = anguloY = anguloZ = 0;

    // Inicialización de los timers
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    timer3 = new QTimer(this);
    timer4 = new QTimer(this);

    // Conexión de los timers con las animaciones
    connect(timer1, SIGNAL(timeout()), this, SLOT(animacion1()));
    connect(timer2, SIGNAL(timeout()), this, SLOT(animacion2()));
    connect(timer3, SIGNAL(timeout()), this, SLOT(animacion3()));
    connect(timer3, SIGNAL(timeout()), this, SLOT(animacion4()));
    connect(timer4, SIGNAL(timeout()), this, SLOT(arcoiris()));

    // Establecemos el ancho por defecto de la pluma
    pluma.setWidth(2);

    // Asignamos la figura
    asignarFigura();
}


MainWindow::~MainWindow()
{
    delete ui;
}


// Con ayuda del PaintEvent inicializamos el puerto y se
// proyecta la figura
void MainWindow::paintEvent(QPaintEvent *evt)
{
    Q_UNUSED(evt)
    inicializaPuerto();
    proyeccionFigura();
}


// Se asigna la figura, con todo y su proyección 3D
void MainWindow::asignarFigura()
{
    Punto3D figuraBase[]={{20,60,1,0},{20,44,1,0},{32,44,1,0},
                        {32,50,1,0},{36,50,1,0},{36,64,1,0},
                        {32,64,1,0},{32,70,1,0},{24,70,1,0},
                        {24,60,1,0},{20,60,1,0},{20,30,1,0},
                        {44,30,1,0},{44,40,1,0},{96,40,1,0},
                        {56,40,1,0},{56,28,1,0},{62,28,1,0},
                        {62,40,1,0},{65,40,1,0},{65,45,1,0},
                        {58,45,1,0},{58,65,1,0},{65,65,1,0},
                        {65,70,1,0},{73,70,1,0},{73,65,1,0},
                        {80,65,1,0},{80,45,1,0},{73,45,1,0},
                        {73,40,1,0},{76,40,1,0},{76,28,1,0},
                        {82,28,1,0},{82,40,1,0},{96,40,1,0},
                        {96,30,1,0},{120,30,1,0},{120,44,1,0},
                        {108,44,1,0},{108,50,1,0},{104,50,1,0},
                        {104,64,1,0},{108,64,1,0},{108,70,1,0},
                        {108,76,1,0},{100,76,1,0},{100,70,1,0},
                        {90,70,1,0},{90,74,1,0},{84,74,1,0},
                        {84,86,1,0},{56,86,1,0},{50,86,1,0},
                        {50,80,1,0},{40,80,1,0},{40,76,1,0},
                        {32,76,1,0},{32,70,1,0},{32,76,1,0},
                        {40,76,1,0},{40,70,1,0},{50,70,1,0},
                        {50,74,1,0},{56,74,1,0},{56,74,1,0},
                        {56,86,1,0},{84,86,1,0},{90,86,1,0},
                        {90,80,1,0},{100,80,1,0},{100,76,1,0},
                        {108,76,1,0},{108,70,1,0},{116,70,1,0},
                        {116,60,1,0},{120,60,1,0},{120,44,1,0},
                        {120,30,1,0},{114,30,1,0},{114,24,1,0},
                        {108,24,1,0},{108,12,1,0},{102,12,1,0},
                        {102,12,1,0},{102,4,1,0},{38,4,1,0},
                        {38,12,1,0},{32,12,1,0},{32,24,1,0},
                        {26,24,1,0},{26,30,1,0}, /* Cierre cara frontal*/
                        {26,30,100,1},{26,30,1,0},{20,30,1,0},
                        {20,30,100,1},{20,30,1,0},{20,60,1,0},
                        {20,60,100,1},{20,60,1,0},{24,60,1,0},
                        {24,60,100,1},{24,60,1,0},{24,70,1,0},
                        {24,70,100,1},{24,70,1,0},{32,70,1,0},
                        {32,70,100,1},{32,70,1,0},{32,76,1,0},
                        {32,76,100,1},{32,76,1,0},{40,76,1,0},
                        {40,76,100,1},{40,76,1,0},{40,80,1,0},
                        {40,80,100,1},{40,80,1,0},{50,80,1,0},
                        {50,80,100,1},{50,80,1,0},{50,86,1,0},
                        {50,86,100,1},{50,86,1,0},{90,86,1,0},
                        {90,86,100,1},{90,86,1,0},{90,80,1,0},
                        {90,80,100,1},{90,80,1,0},{100,80,1,0},
                        {100,80,100,1},{100,80,1,0},{100,76,1,0},
                        {100,76,100,1},{100,76,1,0},{108,76,1,0},
                        {108,76,100,1},{108,76,1,0},{108,70,1,0},
                        {108,70,100,1},{108,70,1,0},{116,70,1,0},
                        {116,70,100,1},{116,70,1,0},{116,60,1,0},
                        {116,60,100,1},{116,60,1,0},{120,60,1,0},
                        {120,60,100,1},{120,60,1,0},{120,30,1,0},
                        {120,30,100,1},{120,30,1,0},{114,30,1,0},
                        {114,30,100,1},{114,30,1,0},{114,24,1,0},
                        {114,24,100,1},{114,24,1,0},{108,24,1,0},
                        {108,24,100,1},{108,24,1,0},{108,12,1,0},
                        {108,12,100,1},{108,12,1,0},{102,12,1,0},
                        {102,12,100,1},{102,12,1,0},{102,4,1,0},
                        {102,4,100,1},{102,4,1,0},{38,4,1,0},
                        {38,4,100,1},{38,4,1,0},{38,12,1,0},
                        {38,12,100,1},{38,12,1,0},{32,12,1,0},
                        {32,12,100,1},{32,12,1,0},{32,24,1,0},
                        {32,24,100,1},{32,24,1,0},{26,24,1,0},
                        {26,24,100,1},{26,30,100,1},{20,30,100,1},
                        {20,60,100,1},{24,60,100,1},{24,70,100,1},
                        {32,70,100,1},{32,76,100,1},{40,76,100,1},
                        {40,80,100,1},{50,80,100,1},{50,86,100,1},
                        {90,86,100,1},{90,80,100,1},{100,80,100,1},
                        {100,76,100,1},{108,76,100,1},{108,70,100,1},
                        {116,70,100,1},{116,60,100,1},{120,60,100,1},
                        {120,30,100,1},{114,30,100,1},{114,24,100,1},
                        {108,24,100,1},{108,12,100,1},{102,12,100,1},
                        {102,4,100,1},{38,4,100,1},{38,12,100,1},
                        {32,12,100,1},{32,24,100,1},{26,24,100,1}};

    // Se crea el objeto de la clase Punto3D, con los 218
    // puntos de la figura a crear
    figura = new Punto3D[218];

    // Respaldamos la figura
    for(int i = 0; i < 218; i++)
        figura[i] = figuraBase[i];

    // Se inicializa el puerto
    inicializaPuerto();

    // Se establece el ancho
    ancho = this->size().width() - ui->widget->size().width();  // ui->centralwidget->size().width();
}


// Se proyecta la figura
void MainWindow::proyeccionFigura()
{
   canvas = new QPainter(this);
   canvas->setPen(QPen(QColor(95, 95, 95),3));

   // Línea horizontal, eje X
   canvas->drawLine(0,size().height()-1, ancho,size().height()-1);

   // Línea horizontal, eje Y
   canvas->drawLine(1,0,1,size().height());

   int zx1 = 0;
   int zy1 = 0;
   int zx2 = ancho * cos(radianes(phi));
   int zy2 = ancho * sin(radianes(phi));

   int x1,y1,x2,y2;
   mapeo.mapear(zx1,zy1,x1,y1,L,M);
   mapeo.mapear(zx2,zy2,x2,y2,L,M);

   // Dibujar eje Z
   canvas->drawLine(x1,y1,x2,y2);

   // Aplicar rotación
   int x, y, z;

   for(int i = 0; i < 218; i++) { // 0 = MOVETO3D,   1 = LINETO3D
       x = figura[i].x;
       y = figura[i].y;
       z = figura[i].z;

       if(rX) {
           x = figura[i].x;
           y = redondear((figura[i].y-yC) *cos(radianes(anguloX))+(figura[i].z - zC)*sin(radianes(anguloX))+yC);
           z = redondear(-(figura[i].y-yC)*sin(radianes(anguloX))+(figura[i].z - zC)*cos(radianes(anguloX))+zC);
       } if(rY) {
           y = figura[i].y;
           x = redondear((figura[i].x-xC) *cos(radianes(anguloY))-(figura[i].z - zC)*sin(radianes(anguloY))+xC);
           z = redondear((figura[i].x-xC) *sin(radianes(anguloY))+(figura[i].z - zC)*cos(radianes(anguloY))+zC);
       } if (rZ) {
           z = figura[i].z;
           x = redondear((figura[i].x-xC) *cos(radianes(anguloZ))-(figura[i].y - yC)*sin(radianes(anguloZ))+xC);
           y = redondear((figura[i].x-xC) *sin(radianes(anguloZ))+(figura[i].y - yC)*cos(radianes(anguloZ))+yC);
       }

       if(figura[i].opcion)
           lineto3D(x+tX, y+tY, z+tZ, radianes(alpha), /*qDegreesToRadians*/radianes(phi), i);
       else
           moveto3D(x+tX, y+tY, z+tZ, radianes(alpha), /*qDegreesToRadians*/radianes(phi), i);

       //if(cubo[i].opcion)
           //lineto3D(cubo[i].x+tX , cubo[i].y+tY, cubo[i].z+tZ,radianes(alpha), /*qDegreesToRadians*/radianes(phi), i);
       //else
           //moveto3D(cubo[i].x+tX , cubo[i].y+tY, cubo[i].z+tZ,radianes(alpha), /*qDegreesToRadians*/radianes(phi), i);

    }

    canvas->setPen(pluma);
    dibujarFigura();
    canvas->end();
}


// Se dibuja la figura
void MainWindow::dibujarFigura()
{
    for(int i = 0; i < 217; i++)
        canvas->drawLine(puntosFigura[i].x(), puntosFigura[i].y(), puntosFigura[i+1].x(), puntosFigura[i+1].y());

    canvas->setRenderHint(QPainter::Antialiasing, true);
}


// Se inicializa el puerto
void MainWindow::inicializaPuerto()
{
     mapeo.ventana(0,0,this->size().width()-ancho,size().height());
     mapeo.puerto(0,0,size().width()-ancho, size().height());
     L = 0;
     M = size().height();
}


// Método LineTo3D
void MainWindow::lineto3D(int x, int y, int z, float alpha, float phi, int i)
{
     int xp, yp;
     int longitud; // Segmento L
     float tanAlpha;

     if((tanAlpha = tan(alpha)) != 0)
         longitud = (int)(z / tanAlpha);
     else
         longitud = 0;

     xp = x + longitud * cos(phi);
     yp = y + longitud * sin(phi);

     // Mapear los valores proyectados
     int x1, y1;
     mapeo.mapear(xp,yp,x1,y1,L,M);
     puntosFigura[i].setX(x1);
     puntosFigura[i].setY(y1);
}


// Método MoveTo3D
void MainWindow::moveto3D(int x, int y, int z, float alpha, float phi, int i)
{
    canvas->setRenderHint(QPainter::Antialiasing, true);

    int xp, yp;
    int longitud; // Segmento L
    float tanAlpha;

    if((tanAlpha = tan(alpha)) != 0)
        longitud = (int)(z / tanAlpha);
    else
        longitud = 0;

    xp = x + longitud * cos(phi);
    yp = y + longitud * sin(phi);

    // Mapear los valores proyectados
    int x1, y1;
    mapeo.mapear(xp,yp,x1,y1,L,M);
    puntosFigura[i].setX(x1);
    puntosFigura[i].setY(y1);
}


// Método KeyPressEvent, con el cual se
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Home)
        tX -= 5;
    if(event->key() == Qt::Key_End)
        tX += 5;
    if(event->key() == Qt::Key_Up)
        tY += 5;
    if(event->key() == Qt::Key_Down)
        tY -= 5;
    if(event->key() == Qt::Key_9)
        tZ += 5;
    if(event->key() == Qt::Key_0)
        tZ -= 5;

    // Rotación
    if(event->key() == Qt::Key_X) {
        anguloX+=5; rX=true; rY=false; rZ=false;
    }
    if(event->key() == Qt::Key_C) {
        anguloX-=5; rX=true; rY=false; rZ=false;
    }
    if(event->key() == Qt::Key_Y) {
        anguloY+=5; rX=false; rY=true; rZ=false;
    }
    if(event->key() == Qt::Key_T) {
        anguloY-=5; rX = false; rY = true; rZ = false;
    }
    if(event->key() == Qt::Key_Z) {
        anguloZ+=5; rX = false; rY = false; rZ = true;
    }
    if(event->key() == Qt::Key_A) {
        anguloZ-=5; rX = false; rY = false; rZ = true;
    }

    repaint();
}


// Dial que cambia el valor de Alpha
void MainWindow::on_dialAlpha_sliderMoved(int position)
{
     alpha = position;
     ui->lcdNumber->display(position);
     inicializaPuerto();
     update();
}


// Dial que cambia el valor de Phi
void MainWindow::on_dialPhi_valueChanged(int value)
{
    this->phi = value;
    ui->lcdNumber_2->display(value);
    inicializaPuerto();
    repaint();
}


// CheckBox que activa/desactiva el widget para poder
// hacer uso del teclado
void MainWindow::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked())
        ui->widget->setEnabled(false);
    else
        ui->widget->setEnabled(true);
}


// Animación 1
void MainWindow::animacion1()
{
    static bool subir = true;
    static bool regreso = true;
    static int i = 0;

    if(subir) {
        tZ+=1;
        i++;

        if(i==250) {
            subir = false;
            regreso = true;
            i = 0;
        }
    } if(!subir && regreso) {
        i++;
        anguloX+=5;

        if(i==5) {
            regreso = false;
            i = 0;
        }
    } if(!subir && !regreso) {
        i++;
        tZ-=1;

        if(i==250) {
            i = 0;
            subir = true;
        }
    }
    repaint();
}


// Animación 2
void MainWindow::animacion2()
{
    alpha = 30;
    phi = 15;

    static bool subir = true;
    static bool regreso = true;
    static int i = 0;

    if(subir) {
        anguloY-=5;
        i++;

        if(i==60) {
            subir = false;
            regreso = true;
            i = 0;
            anguloY+=5;
        }
    } if(!subir && regreso) {
        i = 0;
        regreso=false;
    } if(!subir && !regreso) {
        i++;
        anguloY+=5;

        if(i==75) {
            i = 0;
            subir = true;
            anguloY-=5;
        }
    }
    rX=false; rY=true; rZ=false;

    repaint();
}


// Animación 3
void MainWindow::animacion3() {
    static bool limite = true;
    static int i = 0;

    if(limite) {
        tX+=1;
        i++;

        if(i==ancho-125) {
            limite = false;
            i = 0;
            phi+=10;
            anguloX+=15;
        }
    } if(!limite) {
        tX-=1;
        i++;

        if(i==ancho-125) {
            limite = true;
            i = 0;
            phi+=10;
            anguloX+=15;
        }
    }
    repaint();
}


// Animación 4
void MainWindow::animacion4()
{
    static bool subir = true;
    static bool regreso = true;
    static int i = 0;

    if(subir) {
        tY+=1;
        i++;

        if(i==this->height()-100) {
            subir = false;
            regreso = true;
            i=0;
            phi+=10;
            anguloX+=15;
        }
    } if(!subir && regreso) {
        i++;
        anguloX+=5;

        if(i==5) {
            regreso = false;
            i=0;
            phi+=10;
        }
    } if(!subir && !regreso) {
        i++;
        tY-=1;

        if(i==this->height()-100) {
            i = 0;
            subir = true;
            phi+=10;
            anguloX+=15;
        }
    }

    ui->lcdNumber_2->display(phi);
    repaint();
}


// Método "arcoíris", el cual, simula la estrella de la
// saga de videojuegos, aplicando el efecto arcoíris en
// el borde de la figura con ayuda de un timer
void MainWindow::arcoiris() {
    if(timer4->isActive()) {
        pluma.setColor(
                    QColor(rand()%ui->vsIntensidadR->value(),
                           rand()%ui->vsIntensidadG->value(),
                           rand()%ui->vsIntensidadB->value()
                           )
                    );
        repaint();
    }
}


// Inicialización de los timers que usarán las
// animaciones
void MainWindow::on_btnAnimacion1_clicked()
{
    timer1->start(4);
}


void MainWindow::on_btnAnimacion2_clicked()
{
    timer2->start(30);
}


void MainWindow::on_btnAnimacion3_clicked()
{
    timer3->start(4);

    alpha = 80;
    phi = 65;
}


// Se detienen los timers de las animaciones
void MainWindow::on_btnDetenerA1_clicked()
{
    timer1->stop();
}


void MainWindow::on_btnDetenerA2_clicked()
{
    timer2->stop();
}


void MainWindow::on_btnDetenerA3_clicked()
{
    timer3->stop();
}


void MainWindow::on_btnArcoiris_clicked()
{
    timer4->start(80);
}


void MainWindow::on_btnDetenerArcoiris_clicked()
{
    timer4->stop();
}


// Dial que cambia el grosor de la figura
void MainWindow::on_dialGrosor_valueChanged(int value)
{
    pluma.setWidth(value);
    update();
}


// Botón que abre un selector de colores para el
// borde de la figura
void MainWindow::on_btnMasColores_clicked()
{
    QColor seleccionaColor = QColorDialog::getColor(
                Qt::white,
                this,
                "Selecciona un color"
                );

    if(seleccionaColor.isValid()) {
        pluma.setColor(seleccionaColor);
    }
}


// Botón que pone la figura 3D en su posición original
// y detiene las animaciones que pudiesen estar en curso
void MainWindow::on_btnReset_clicked()
{
    tZ = tY = tX = anguloX = anguloY = anguloZ = 0;
    alpha = 45.0;
    phi = 30.0;

    if(timer1->isActive())
        timer1->stop();
    if(timer2->isActive())
        timer2->stop();
    if(timer3->isActive())
        timer3->stop();
    if(timer4->isActive())
        timer4->stop();

    pluma.setColor(Qt::black);
    pluma.setWidth(2);
    ui->lcdNumber_2->display(0);

    asignarFigura();
    update();
}

