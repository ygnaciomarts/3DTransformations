#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QtGui>
#include <QColorDialog>
#include "mapeo.h"
#include <math.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

const double PI = 3.141592653589793;

#define radianes(g) (double(g) * M_PI / 180.0)
#define redondear(val) (int)(val+0.5);

struct Punto3D
{
    // POR DEFAULT SUS ATRIBUTOS SON PUBLICOS
    int x,y,z;
    bool opcion;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent *evt);
    void asignarFigura();
    void proyeccionFigura();
    void dibujarFigura();
    void inicializaPuerto();

    void lineto3D(int x, int y, int z, float alpha, float phi, int i );
    void moveto3D(int x, int y, int z, float alpha, float phi, int i );

    void keyPressEvent(QKeyEvent *event);


private slots:
    void on_dialAlpha_sliderMoved(int position);

    void on_dialPhi_valueChanged(int value);

    void on_checkBox_clicked();

    void arcoiris();

    void animacion1();

    void animacion2();

    void animacion3();

    void animacion4();

    void on_btnAnimacion1_clicked();

    void on_btnAnimacion2_clicked();

    void on_btnAnimacion3_clicked();

    void on_btnDetenerA1_clicked();

    void on_btnDetenerA2_clicked();

    void on_btnDetenerA3_clicked();

    void on_btnArcoiris_clicked();

    void on_dialGrosor_valueChanged(int value);

    void on_btnDetenerArcoiris_clicked();

    void on_btnMasColores_clicked();

    void on_btnReset_clicked();

private:
    Ui::MainWindow *ui;

    QPainter *canvas;
    QPointF puntosFigura[218]; // Se usará para dibujar
    Punto3D *figura;
    Mapeo mapeo;
    QTimer *timer1, *timer2, *timer3, *timer4, *timer5;
    QPen pluma;

    int L, M;
    int ancho;
    float alpha, phi;

    int tX, tY, tZ;

    int xC, yC, zC;

    bool rX, rY, rZ;

    int anguloX, anguloY, anguloZ;

};
#endif // MAINWINDOW_H






