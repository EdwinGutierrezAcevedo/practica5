#include "bomba.h"
#include "enemigo.h"
#include "personaje.h"
#include <QList>
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
extern QGraphicsPixmapItem* spritePuerta;
Bomba::Bomba(QPointF posicion, QGraphicsScene* scene) : scene(scene), usandoSprite1(true) {
    spriteBomba1 = QPixmap(":/new/prefix1/bomba1.png").scaled(40, 40, Qt::KeepAspectRatio);
    spriteBomba2 = QPixmap(":/new/prefix1/bomba2.png").scaled(40, 40, Qt::KeepAspectRatio);
    spriteExplosion = QPixmap(":/new/prefix1/explosion.png").scaled(120, 120, Qt::KeepAspectRatio);
    spriteDestruccionEnemigo = QPixmap(":/new/prefix1/enemigoDestruido.png").scaled(40, 40, Qt::KeepAspectRatio);
    setPos(posicion);
    // Agregar el sprite de la puerta a la escena
    QPixmap puerta(":/new/prefix1/puerta.png");
    spritePuerta = new QGraphicsPixmapItem(puerta.scaled(40, 40, Qt::KeepAspectRatio));
    spritePuerta->setPos(920, 480); // Establecer la posición de la puerta
    spritePuerta->setOpacity(0);
    spritePuerta->setData(0,"puerta");
    scene->addItem(spritePuerta);
    QPixmap mejora(":/new/prefix1/mejora.png");
    spriteMejora = new QGraphicsPixmapItem(mejora.scaled(40, 40, Qt::KeepAspectRatio));
    spriteMejora->setPos(760, 440); // Establecer la posición de la puerta
    spriteMejora->setOpacity(0);
    spriteMejora->setData(0,"mejora");
    scene->addItem(spriteMejora);
    temporizador = new QTimer(this);
    connect(temporizador, &QTimer::timeout, this, &Bomba::alternarSprite);
    temporizador->start(500);  // Cambiar sprite cada 500 ms

    // Temporizador para la explosión
    QTimer::singleShot(4000, this, &Bomba::explotar);  // Explotar después de 4 segundos
}

void Bomba::alternarSprite() {
    if (usandoSprite1) {
        setPixmap(spriteBomba2);
    } else {
        setPixmap(spriteBomba1);
    }
    usandoSprite1 = !usandoSprite1;
}


void Bomba::explotar() {
    temporizador->stop();  // Detener la animación de la bomba

    // Crear el efecto de explosión usando el sprite de la explosión
    QGraphicsPixmapItem* explosion = new QGraphicsPixmapItem(spriteExplosion);
    int x,y;
    x=pos().x() - 40;
    y=pos().y() - 40;

    explosion->setPos(x, y);  // Ajustar la posición de la explosión
    scene->addItem(explosion);

    qDebug() << "La bomba ha explotado en " << pos();

    // Verificar colisiones con la explosión
    QList<QGraphicsItem*> colisiones = explosion->collidingItems();
    for (QGraphicsItem* item : colisiones) {
        if (item->data(0).toString() == "enemigo") {
            qDebug() << "La explosión ha colisionado con un enemigo";
            QGraphicsPixmapItem* spriteDestruccion = new QGraphicsPixmapItem(spriteDestruccionEnemigo);
            spriteDestruccion->setPos(item->pos());
            scene->addItem(spriteDestruccion);
            scene->removeItem(item);
            QTimer::singleShot(500, this, [item, spriteDestruccion, this]() {
                scene->removeItem(spriteDestruccion);
                delete spriteDestruccion;
            });
        } else if (Personaje* personaje = dynamic_cast<Personaje*>(item)) {
            qDebug() << "La explosión ha colisionado con el personaje";
            personaje->setMuerto();  // Matar al personaje
        } if (item->data(0).toString() == "muro") {
            qDebug() << "La explosión ha colisionado con un muro";
            scene->removeItem(item);
        } else if (item->data(0).toString() == "pared") {
            qDebug() << "La explosión ha colisionado con una pared";
            continue;  // No eliminar la pared ni mostrar la explosión en esta posición
        }if (item->data(0).toString() == "muroPuerta") {
            qDebug() << "La explosión ha colisionado con la puerta";
            scene->removeItem(item);
            //item->setOpacity(0); // Hacer invisible el muro
            spritePuerta->setOpacity(1); // Hacer visible la puerta


        }if (item->data(0).toString() == "muroMejora") {
            qDebug() << "La explosión ha colisionado con la mejora";
            scene->removeItem(item);
            //item->setOpacity(0); // Hacer invisible el muro
            spriteMejora->setOpacity(1); // Hacer visible la mejora
    }

    // Hacer la bomba invisible y eliminar sus colisiones
    this->setOpacity(0);
    //this->setEnabled(false);
    this->setData(0, "");

    // Temporizador para hacer desaparecer la explosión después de 1 segundo
    QTimer::singleShot(500, this, [explosion, this]() {
        scene->removeItem(explosion);
        delete explosion;
    });
}





