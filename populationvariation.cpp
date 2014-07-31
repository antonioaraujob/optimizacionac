#include "populationvariation.h"

#include <random>


PopulationVariation::PopulationVariation(QObject *parent) :
    QObject(parent)
{


}



PopulationVariation::PopulationVariation(QList<Individual *> population, SituationalKnowledge * sKnowledge,
                    NormativeKnowledge * nKnowledge)
{
    Individual * father;
    Individual * offspring;

    // recorrer la lista de poblacion
    for (int i=0; i<population.count(); i++)
    {

        father = population.at(i);

        // seleccionar un conocimiento para la influencia
        if (selectKnowledgeInfluence() == 0)
        {
            // conocimiento situacional
            offspring = situationalInfluence(father, sKnowledge);

        }else
        {
            // conocimiento normativo
            offspring = normativeInfluence(father, nKnowledge);

        }
        // agregar el individuo padre y el individuo hijo a la lista newPopulation
        newPopulation.append(father);
        newPopulation.append(offspring);

    }
}



QList<Individual *> PopulationVariation::getNewPopulation()
{
    return newPopulation;
}


int PopulationVariation::selectKnowledgeInfluence()
{
    int knowledgeInfluenceProbability = 50;

    int low = 1;
    int high = 100;
    int random = qrand() % ((high + 1) - low) + low;

    if (random < knowledgeInfluenceProbability)
    {
        qDebug("aplicar influencia del conocimiento normativo");
        return 1;

    }else
    {
        qDebug("aplicar influencia del conocimiento situacional");
        return 0;
    }
}



Individual * PopulationVariation::situationalInfluence(Individual * father,
                                                       SituationalKnowledge * sKnowledge)
{
    Individual * offspring = new Individual();
    Individual * bestExemplar = sKnowledge->getExemplar();

    for (int i=0; i<father->getNumberOfParameters(); i++)
    {
        if (father->getParameter(i) < bestExemplar->getParameter(i)){
            offspring->setParameter(i,getRandom(father->getParameter(i),bestExemplar->getParameter(i)));
        }else if (father->getParameter(i) > bestExemplar->getParameter(i))
        {
            offspring->setParameter(i,getRandom(bestExemplar->getParameter(i), father->getParameter(i)));
        }
        else
        {
            // ojo en la mutacion debe cumplirse:  1 <= channel <= 11
            //
            // offspring = mutate(father)
        }
    }
    return offspring;

/*
    for dimension i=1 to n
        if (xi < gbi)`
            yi=random(xi,gbi)
        else if (xi > gbi)
            yi=random(gbi, xi)
        else
            yi=mutate(xi)
            // generate a value around xi
        endif
    endfor
*/




}


Individual * PopulationVariation::normativeInfluence(Individual * father,
                                                     NormativeKnowledge * nKnowledge)
{
    Individual * offspring = new Individual();
    NormativeKnowledgeVariable * nkVariable;

    for (int i=0; i<father->getNumberOfParameters(); i++)
    {
        nkVariable = nKnowledge->getNormativeKnowledgeVariable(i);
        if ( (nkVariable->getLowerBound() <= father->getParameter(i) ) || ( father->getParameter(i) <= nkVariable->getUpperBound()) ){
            offspring->setParameter(i,getRandom(nkVariable->getLowerBound(),nkVariable->getUpperBound()));
        }else
        {
            // ojo en la mutacion debe cumplirse:  1 <= channel <= 11
            //
            // offspring = mutate(father)
        }
    }
    return offspring;

/*
for dimension i=1 to n
    if (xi no pertenece a (li, ui))
        yi=random(li, ui)
    else
        yi=mutate(xi)
        // generate a value around xi
    endif
endfor
*/


}


int PopulationVariation::getRandom(int low, int high)
{
    return qrand() % ((high + 1) - low) + low;
}



int PopulationVariation::mutateIndividualParameter(int mean, int std)
{
    std::default_random_engine generator;
    //std::uniform_int_distribution<int> distribution(mean,std);
    std::normal_distribution<double>  distribution(mean,std);

    for (int i=0; i<10; i++)
    {
        double val = distribution(generator);
        qDebug(qPrintable(QString::number(val)));
    }

    return 1;
}
