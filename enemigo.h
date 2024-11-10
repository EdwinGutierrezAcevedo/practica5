#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class enemigo : public QGraphicsPixmapItem {
public:
    enemigo();  // Constructor para cargar las imágenes del enemigo
    void moverX();  // Método para mover el enemigo
    void moverY();  // Método para mover el enemigo

private:
    QPixmap spriteEnemigo1;  // Primera imagen del enemigo
    QPixmap spriteEnemigo2;  // Segunda imagen del enemigo
    bool usandoSprite1=true;  // Controla cuál sprite está usando el enemigo
    bool moverDerecha=true;  // Controla la dirección del movimiento
    bool moverArriba=true;
};

#endif // ENEMIGO_H
