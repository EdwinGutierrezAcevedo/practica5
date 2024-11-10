#include "personaje.h"

#include <QApplication>  // Necesario para cerrar la aplicación
#include <QDebug> // para imprimnir logs en consola. No necesaria si usas otars librerias de Qt
Personaje::Personaje() {
    // Cargar las dos imágenes del personaje
    sprite=QPixmap(":/new/prefix1/spriteBomberman.png");
    sprite = sprite.scaled(40, 40, Qt::KeepAspectRatio);
    spriteAlado1 = QPixmap(":/new/prefix1/spriteBombermanAlado1.png");
    spriteAlado1 = spriteAlado1.scaled(40, 40, Qt::KeepAspectRatio);
    spriteAlado2 = QPixmap(":/new/prefix1/spriteBombermanAlado2.png");
    spriteAlado2 = spriteAlado2.scaled(40, 40, Qt::KeepAspectRatio);
    spriteAbajo1 = QPixmap(":/new/prefix1/spriteBombermanAbajo1.png");
    spriteAbajo1 = spriteAbajo1.scaled(40, 40, Qt::KeepAspectRatio);
    spriteAbajo2 = QPixmap(":/new/prefix1/spriteBombermanAbajo2.png");
    spriteAbajo2 = spriteAbajo2.scaled(40, 40, Qt::KeepAspectRatio);
    spriteArriba1 = QPixmap(":/new/prefix1/spriteBombermanArriba1.png");
    spriteArriba1 = spriteArriba1.scaled(40, 40, Qt::KeepAspectRatio);
    spriteArriba2 = QPixmap(":/new/prefix1/spriteBombermanArriba2.png");
    spriteArriba2 = spriteArriba2.scaled(40, 40, Qt::KeepAspectRatio);
    spriteOtrolado1 = QPixmap(":/new/prefix1/spriteBombermanOtrolado1.png");
    spriteOtrolado1 = spriteOtrolado1.scaled(40, 40, Qt::KeepAspectRatio);
    spriteOtrolado2 = QPixmap(":/new/prefix1/spriteBombermanOtrolado2.png");
    spriteOtrolado2 = spriteOtrolado2.scaled(40, 40, Qt::KeepAspectRatio);
    spriteBomba1= QPixmap(":/new/prefix1/bomba1.png");
    spriteBomba1= spriteBomba1.scaled(40, 40, Qt::KeepAspectRatio);
    spriteBomba2= QPixmap(":/new/prefix1/bomba2.png");
    spriteBomba2= spriteBomba2.scaled(40, 40, Qt::KeepAspectRatio);



    if (spriteAlado1.isNull() || spriteAlado2.isNull()) {
        qDebug() << "Error: No se pudo cargar una o ambas imágenes del personaje";
    }
    // Inicialmente mostrar la primera imagen
    setPixmap(sprite);
    usandoSprite1 = true;  // Empieza usando la primera imagen

    // Hacer que el personaje pueda recibir eventos de teclado
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

void Personaje::cambiarSprite2(QPixmap sprite1,QPixmap sprite2) {
    // Alternar entre las dos imágenes para simular el movimiento
    if (usandoSprite1) {
        setPixmap(sprite2);
    } else {
        setPixmap(sprite1);
    }
    usandoSprite1 = !usandoSprite1;  // Alternar el estado

}

// Funcion para que no se salga de delimitadores.
void Personaje::keyPressEvent(QKeyEvent* event) {
    // Guardar la posición actual del personaje
    QPointF nuevaPos = pos(); // Inicializo en posición actual del personaje
    QPointF pos_original = nuevaPos;

    // Verificar qué tecla se presionó y calcular la nueva posición
    switch (event->key()) {
    case Qt::Key_Left:
        nuevaPos.setX(nuevaPos.x() - 10);
        cambiarSprite2(spriteAlado1,spriteAlado2);
        break;
    case Qt::Key_Right:
        nuevaPos.setX(nuevaPos.x() + 10);
        cambiarSprite2(spriteOtrolado1,spriteOtrolado2);
        break;
    case Qt::Key_Up:
        nuevaPos.setY(nuevaPos.y() - 10);
        cambiarSprite2(spriteArriba1,spriteArriba2);
        break;
    case Qt::Key_Down:
        nuevaPos.setY(nuevaPos.y() + 10);
        cambiarSprite2(spriteAbajo1,spriteAbajo2);

        break;   
    case Qt::Key_Space:

        cambiarSprite2(spriteBomba1,spriteBomba2);

        break;
    case Qt::Key_Escape:
        qDebug() << "Se presionó ESC. Cerrando la aplicación...";
        QApplication::quit();  // Cerrar la aplicación
        return;
    default:
        return;
    }

    // Mover temporalmente el personaje a la nueva posición para verificar colisiones
    setPos(nuevaPos);

    // Verificar si colisiona con algún objeto etiquetado como "pared"
    QList<QGraphicsItem*> colisiones = collidingItems();
    bool colisionConPared = false;

    for (QGraphicsItem* item : colisiones) {
        if (item->data(0).toString() == "pared"||item->data(0).toString() == "muro") {
            //item->setOpacity(1.0); // se hacen visibles las pareced
            colisionConPared = true;
            break;
        }
    }

    // Si colisiona con una pared, revertir el movimiento
    if (colisionConPared) {
        qDebug() << "Colisión detectada con una pared";
        setPos(pos_original);  // Revertir el movimiento
    }

}
