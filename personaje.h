#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QKeyEvent>

class Personaje : public QGraphicsPixmapItem {
public:
    Personaje();  // Constructor para cargar las imágenes del personaje

    // Método para cambiar el sprite (imagen) del personaje
    void cambiarSprite();

    // Método para manejar el movimiento del personaje
    void keyPressEvent(QKeyEvent* event);

private:
    QPixmap sprite;
    QPixmap spriteAlado1;
    QPixmap spriteAlado2;
    QPixmap spriteAbajo1;
    QPixmap spriteAbajo2;
    QPixmap spriteArriba1;
    QPixmap spriteArriba2;
    QPixmap spriteOtrolado1;
    QPixmap spriteOtrolado2;
    QPixmap spriteBomba1;
    QPixmap spriteBomba2;
    bool usandoSprite1;
    void cambiarSprite2(QPixmap sprite1, QPixmap sprite2);
};

#endif // PERSONAJE_H
