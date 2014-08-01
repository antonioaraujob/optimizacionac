#ifndef POPULATIONSELECTION_H
#define POPULATIONSELECTION_H

#include <QObject>

#include "individual.h"


// Clase que modela el operador de seleccion
class PopulationSelection : public QObject
{
    Q_OBJECT

private:

    // Lista de la nueva poblacion despues de realizada la seleccion
    QList<Individual *> newPopulation;


public:

    // Constructor
    explicit PopulationSelection(QObject *parent = 0);
    
    // Constructor de la clase
    PopulationSelection(QList<Individual *> population2p);

    void doSelection(QList<Individual *> population2p);

    // Retorna la nueva poblacion despues de realizada la seleccion
    QList<Individual *> getSelectedPopulation();

    // Retorna un entero aleatorio entre 1 el valor high
    int getRandom(int high);




signals:
    
public slots:
    
};

#endif // POPULATIONSELECTION_H
