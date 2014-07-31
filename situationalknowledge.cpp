#include "situationalknowledge.h"

SituationalKnowledge::SituationalKnowledge(QObject *parent) :
    QObject(parent)
{

    // inicializar el conocimiento situacional

}




void SituationalKnowledge::addExemplarIndividual(Individual *exemplar)
{
    exemplarList.append(exemplar);
}

Individual * SituationalKnowledge::getExemplar(int id)
{
    return exemplarList.at(id);
}


int SituationalKnowledge::getCountOfExemplars()
{
    return exemplarList.count();
}


void SituationalKnowledge::updateSituationalKnowledge(QList<Individual *> bestIndividualsList)
{
    // inicialmente se esta reemplazando el individuo con el mejor de la lista
    exemplarList.replace(0,bestIndividualsList.at(bestIndividualsList.count()-1));


}
