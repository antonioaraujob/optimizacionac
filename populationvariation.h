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
    // population: lista de la poblacion actual
    // sKnowledge: conocimiento situacional
    // sKnowledge: conocimiento normativo
    // std: desviacion estandar para la distribucion normal de la mutacion
    PopulationVariation(QList<Individual *> population, SituationalKnowledge * sKnowledge, NormativeKnowledge * nKnowledge, int std);



    void doVariation(QList<Individual *> population, SituationalKnowledge * sKnowledge, NormativeKnowledge * nKnowledge, double std);

    // Retorna la nueva poblacion luego de la variacion.
    // Esta poblacion es de tamano 2P y se pasara a la clase PoplationSelection
    QList<Individual *> getNewPopulation();

    // Retorna un entero para seleccionar de cual tipo de conocimiento ejercer influencia
    // 0 - seleccionar conocimiento situacional
    // 1 - seleccionar conocimiento normativo
    int selectKnowledgeInfluence();

    // Retorna un hijo a partir de un padre y de la influencia situacional
    // father: individuo padre
    // sKnowledge: conocimiento situacional
    // std: desviacion estandar para la mutacion gausiana
    Individual * situationalInfluence(Individual * father, SituationalKnowledge * sKnowledge, double std);

    // Retorna un hijo a partir de un padre y de la influencia normativa
    // father: individuo padre
    // sKnowledge: conocimiento situacional
    // std: desviacion estandar para la mutacion gausiana
    Individual * normativeInfluence(Individual * father, NormativeKnowledge * nKnowledge, double std);

    // Retorna un numero aletorio entre a y b
    int getRandom(int low, int high);

    // Ejecuta una mutacion gausiana de un parametro de un individuo
    int mutateIndividualParameter(int index, int mean, double std);

    // Retorna verdadero si el parametro a revisar de un individuo corresponde a un canal
    bool isThisParameterAChannel(int index);

    // Retorna verdadero si el parametro a revisar de un individuo corresponde a un MinChannelTime
    bool isThisParameterAMinChannelTime(int index);

    // Retorna verdadero si el parametro a revisar de un individuo corresponde a un MaxChannelTime
    bool isThisParameterAMaxChannelTime(int index);

signals:
    
public slots:
    
};

#endif // POPULATIONVARIATION_H
