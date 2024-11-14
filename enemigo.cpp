#include "enemigo.h"

enemigo::enemigo() {
    spriteEnemigo1 = QPixmap(":/new/prefix1/enemigo1.png");
    spriteEnemigo2 = QPixmap(":/new/prefix1/enemigo2.png");
    spriteEnemigo1 = spriteEnemigo1.scaled(40, 40, Qt::KeepAspectRatio);
    spriteEnemigo2 = spriteEnemigo2.scaled(40, 40, Qt::KeepAspectRatio);
    setPixmap(spriteEnemigo1);

    // Inicializar el sprite actual y la dirección del movimiento

}

void enemigo::moverX() {
    QPointF nuevaPos = pos();  // Inicializo en posición actual del personaje
    QPointF pos_original = nuevaPos;

    // Actualizar la posición del enemigo
    if (moverDerecha) {
        nuevaPos.setX(nuevaPos.x() + 1);
    } else {
        nuevaPos.setX(nuevaPos.x() - 1);
    }
    setPos(nuevaPos);

    // Alternar entre las dos imágenes para simular el movimiento
    if (usandoSprite1) {
        setPixmap(spriteEnemigo2);
    } else {
        setPixmap(spriteEnemigo1);
    }
    usandoSprite1 = !usandoSprite1;  // Alternar el estado

    // Verificar colisiones
    QList<QGraphicsItem*> colisiones = collidingItems();
    bool colisionConPared = false;

    for (QGraphicsItem* item : colisiones) {
        if (item->data(0).toString() == "pared"||item->data(0).toString() == "muro"||item->data(0).toString() == "bomba") {
            colisionConPared = true;
            break;
        }
        if (Personaje* personaje = dynamic_cast<Personaje*>(item)) {
            personaje->setMuerto();
            return; // Terminar el movimiento del enemigo
        }
    }

    // Si colisiona con una pared, cambiar de dirección
    if (colisionConPared) {
        moverDerecha = !moverDerecha;
        setPos(pos_original);  // Revertir el movimiento
    }
}

void enemigo::moverY() {
    QPointF nuevaPos = pos();  // Inicializo en posición actual del personaje
    QPointF pos_original = nuevaPos;

    // Actualizar la posición del enemigo
    if (moverArriba) {
        nuevaPos.setY(nuevaPos.y() + 1);
    } else {
        nuevaPos.setY(nuevaPos.y() - 1);
    }
    setPos(nuevaPos);

    // Alternar entre las dos imágenes para simular el movimiento
    if (usandoSprite1) {
        setPixmap(spriteEnemigo2);
    } else {
        setPixmap(spriteEnemigo1);
    }
    usandoSprite1 = !usandoSprite1;  // Alternar el estado

    // Verificar colisiones
    QList<QGraphicsItem*> colisiones = collidingItems();
    bool colisionConPared = false;

    for (QGraphicsItem* item : colisiones) {
        if (item->data(0).toString() == "pared"||item->data(0).toString() == "muro"||item->data(0).toString() == "bomba") {
            colisionConPared = true;
            break;

        }
        if (Personaje* personaje = dynamic_cast<Personaje*>(item)) {
            personaje->setMuerto();
            return; // Terminar el movimiento del enemigo
        }
    }

    // Si colisiona con una pared, cambiar de dirección
    if (colisionConPared) {
        moverArriba = !moverArriba;
        setPos(pos_original);  // Revertir el movimiento
    }
}
