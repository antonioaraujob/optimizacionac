#ifndef SITUATIONALKNOWLEDGE_H
#define SITUATIONALKNOWLEDGE_H

#include <QObject>

#include "individual.h"


// Clase que modela el conocimiento situacional del espacio de creencias

class SituationalKnowledge : public QObject
{
    Q_OBJECT

private:

    // Lista de individuos ejemplares del conocimiento situacional
    QList<Individual*> exemplarList;

public:

    // Constructor de la clase
    explicit SituationalKnowledge(QObject *parent = 0);
    

    // Agrega un individuo ejemplar al conocimiento situacional
    void addExemplarIndividual(Individual *exemplar);

    // Retorna un individuo ejemplar del conocimiento situacional
    Individual * getExemplar(int id=0);

    // Retorna el numero de ejemplares en el conocimiento situacional
    int getCountOfExemplars();

signals:
    
public slots:
    
};

#endif // SITUATIONALKNOWLEDGE_H
