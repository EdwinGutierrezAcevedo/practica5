#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "personaje.h" // personaje
#include "enemigo.h"

#include <QGraphicsRectItem> // Paquete para uso de rectangulos desde Qt.
#include <QGraphicsPixmapItem> //Paquete para imagenes.
#include <QTimer> // Para el temporizador

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Configurar la interfaz visual desde el archivo .ui
    ui->setupUi(this);

    // Inicializar la escena
    scene = new QGraphicsScene(this);

    // Agregar la imagen de fondo como parte de la escena
    QPixmap bk =  QPixmap(":/new/prefix1/fondo.png").scaled(1080,600,Qt::KeepAspectRatio);
    QGraphicsPixmapItem* fondo = new QGraphicsPixmapItem(bk);
    if (bk.isNull()) {
        qDebug() << "Error: No se pudo cargar la imagen del fondo.";
    } else {
        qDebug() << "Imagen del fondo cargada correctamente.";
    }
    fondo->setPos(0, 0);  // Posicionar la imagen en el origen de la escena
    scene->addItem(fondo);  // Agregar el fondo a la escena

    // Configurar la escena y agregar las "paredes"
    crearEscena();

    // Asignar la escena al QGraphicsView que definiste en el archivo .ui
    ui->graphicsView->setScene(scene);

    // Desactivar las barras de scroll
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Ajustar la vista al tamaño de la escena
    ui->graphicsView->setFixedSize(1200, 800);

    // Crear y agregar el personaje a la escena
    Personaje* personaje = new Personaje();
    personaje->setPos(40, 40);  // Posicionar el personaje en el centro de la escena
    scene->addItem(personaje);

    // Crear y agregar el enemigo a la escena
    enemigo* enemigo1 = new enemigo();
    enemigo1->setPos(400, 200);
    scene->addItem(enemigo1);
    enemigo* enemigo2 = new enemigo();
    enemigo2->setPos(200, 400);
    scene->addItem(enemigo2);

    // Crear y configurar el temporizador para mover el enemigo
    QTimer* timer = new QTimer(this);
    timer->start(10);

    QObject::connect(timer, &QTimer::timeout, [enemigo1]() {
        enemigo1->moverX();
    });
    QObject::connect(timer, &QTimer::timeout, [enemigo2]() {
        enemigo2->moverY();
    });
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::crearBloques(QGraphicsScene* scene, const QPixmap& texturaBloques) {

    QBrush brush(texturaBloques.scaled(40, 40, Qt::KeepAspectRatio));

    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 6; ++j) {
            QGraphicsRectItem* bloque = scene->addRect(80 + i * 80, 80 + j * 80, 40, 40);
            bloque->setBrush(brush);
            bloque->setData(0, "pared");
        }
    }
}

void MainWindow::crearBloquesDestruibles(QGraphicsScene* scene, const QPixmap& texturaBloques) {

    QBrush brush(texturaBloques.scaled(40, 40, Qt::KeepAspectRatio));

    for (int i = 0; i < 8; i++) {
        for (int j = 1; j < 4; ++j) {
            QGraphicsRectItem* bloque = scene->addRect(120*i + 80, j*120+80, 40, 40);
            bloque->setBrush(brush);
            bloque->setData(0, "muro");
        }
    }
    // for (int k = 1; k < 4; ++k) {
       //  QGraphicsRectItem* bloque = scene->addRect(120, 120*k+80, 40, 40);
       //  bloque->setBrush(brush);
       //  bloque->setData(0, "muro");
   //  }
}

void MainWindow::crearEscena() {
    scene->setSceneRect(0, 0, 1100, 800);
    // Crear "paredes" como rectángulos
    QGraphicsRectItem* paredSuperior = scene->addRect(0, 0, 1000, 40);   // Pared superior
    QGraphicsRectItem* paredInferior = scene->addRect(0, 560, 960, 40); // Pared inferior
    QGraphicsRectItem* paredIzquierda = scene->addRect(0, 40, 40, 560); // Pared izquierda
    QGraphicsRectItem* paredDerecha = scene->addRect(960, 40, 40, 560); // Pared derecha

    QPixmap texturaBloques(":/new/prefix1/bomber-man-destacada.jpg");
    QBrush brush(texturaBloques.scaled(40,40,Qt::KeepAspectRatio));  // Crear un pincel con la textura cargada
    paredSuperior->setBrush(brush);
    paredInferior->setBrush(brush);
    paredIzquierda->setBrush(brush);
    paredDerecha->setBrush(brush);

    // Hacer que las paredes sean detectables para colisiones
    paredSuperior->setData(0, "pared");  // Etiquetar cada pared como "pared"
    paredInferior->setData(0, "pared");
    paredIzquierda->setData(0, "pared");
    paredDerecha->setData(0, "pared");
    QPixmap texturaBloquesDestruibles(":/new/prefix1/bloque.png");

    // Crear bloques en fila y columna
    crearBloques(scene, texturaBloques);
    crearBloquesDestruibles(scene, texturaBloquesDestruibles);
}
