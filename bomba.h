#ifndef BOMBA_H
#define BOMBA_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QTimer>
#include <QObject>

class Bomba : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Bomba(QPointF posicion, QGraphicsScene* scene);  // Constructor para crear la bomba

private slots:
    void alternarSprite();  // Slot para alternar los sprites de la bomba
    void explotar();  // Slot para manejar la explosión

private:
    QPixmap spriteBomba1;  // Primera imagen de la bomba
    QPixmap spriteBomba2;  // Segunda imagen de la bomba
    QPixmap spriteExplosion;  // Imagen de la explosión
    QPixmap spriteDestruccionEnemigo;
    QGraphicsPixmapItem* spritePuerta;
    QGraphicsPixmapItem* spriteMejora;
    QTimer* temporizador;  // Temporizador para alternar los sprites y para la explosión
    QGraphicsScene* scene;  // Referencia a la escena
    bool usandoSprite1;  // Controla cuál sprite está usando la bomba
};

#endif // BOMBA_H

