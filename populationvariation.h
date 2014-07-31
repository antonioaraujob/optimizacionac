#ifndef POPULATIONVARIATION_H
#define POPULATIONVARIATION_H

#include <QObject>
#include <QList>

#include "individual.h"
#include "situationalknowledge.h"
#include "normativeknowledge.h"



// Clase que modela la variacion de la poblacion para cada generacion
class PopulationVariation : public QObject
{
    Q_OBJECT

private:

    // Lista que mantiene la poblacion original mas los hijos generados
    QList<Individual *> newPopulation;

public:

    // Constructor de la clase
    explicit PopulationVariation(QObject *parent = 0);
    
    // Constructor de la clase
    PopulationVariation(QList<Individual *> population, SituationalKnowledge * sKnowledge, NormativeKnowledge * nKnowledge);


    // Retorna la nueva poblacion luego de la variacion
    QList<Individual *> getNewPopulation();

    // Retorna un entero para seleccionar de cual tipo de conocimiento ejercer influencia
    // 0 - seleccionar conocimiento situacional
    // 1 - seleccionar conocimiento normativo
    int selectKnowledgeInfluence();

    // Retorna un hijo a partir de un padre y de la influencia situacional
    Individual * situationalInfluence(Individual * father, SituationalKnowledge * sKnowledge);

    // Retorna un hijo a partir de un padre y de la influencia normativa
    Individual * normativeInfluence(Individual * father, NormativeKnowledge * nKnowledge);

    // Retorna un numero aletorio entre a y b
    int getRandom(int low, int high);

    // Ejecuta una mutacion gausiana de un parametro de un individuo
    int mutateIndividualParameter(int mean, int std);

signals:
    
public slots:
    
};

#endif // POPULATIONVARIATION_H
