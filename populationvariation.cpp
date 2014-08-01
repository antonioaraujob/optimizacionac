#include "populationvariation.h"

#include <random>
#include <chrono>


PopulationVariation::PopulationVariation(QObject *parent) :
    QObject(parent)
{

    newPopulation.clear();

}



PopulationVariation::PopulationVariation(QList<Individual *> population, SituationalKnowledge * sKnowledge,
                    NormativeKnowledge * nKnowledge, int std)
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
            offspring = situationalInfluence(father, sKnowledge, std);

        }else
        {
            // conocimiento normativo
            offspring = normativeInfluence(father, nKnowledge, std);

        }
        // agregar el individuo padre y el individuo hijo a la lista newPopulation
        // newPopulation sera de tamano 2p
        newPopulation.append(father);
        newPopulation.append(offspring);

    }
}

void PopulationVariation::doVariation(QList<Individual *> population, SituationalKnowledge * sKnowledge,
                    NormativeKnowledge * nKnowledge, double std)
{
    newPopulation.clear();

    Individual * father;
    Individual * offspring;

    qDebug(" ----- doVariation: tamano inicial de newPopulation %d", newPopulation.count());

    // recorrer la lista de poblacion
    for (int i=0; i<population.count(); i++)
    {

        father = population.at(i);

        // seleccionar un conocimiento para la influencia
        int influenceSource = selectKnowledgeInfluence();

        if ( influenceSource == 0)
        {
            // conocimiento situacional
            offspring = situationalInfluence(father, sKnowledge, std);

        }else
        {
            // conocimiento normativo
            offspring = normativeInfluence(father, nKnowledge, std);

        }
        // agregar el individuo padre y el individuo hijo a la lista newPopulation
        // newPopulation sera de tamano 2p
        newPopulation.append(father);
        newPopulation.append(offspring);

        //qDebug(" ----- doVariation: tamano de newPopulation %d", newPopulation.count());
    }
    qDebug(" ----- doVariation: tamano final de newPopulation %d", newPopulation.count());
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
        //qDebug("se debe aplicar influencia del conocimiento normativo");
        return 1;

    }else
    {
        //qDebug("se debe aplicar influencia del conocimiento situacional");
        return 0;
    }
}



Individual * PopulationVariation::situationalInfluence(Individual * father,
                                                       SituationalKnowledge * sKnowledge, double std)
{
    //qDebug("   situationalInfluence");
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
            // offspring = mutate(father)
            //qDebug("se debe mutar parametro con valor %f",father->getParameter(i));
            offspring->setParameter(i, mutateIndividualParameter(i, father->getParameter(i), std));
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
                                                     NormativeKnowledge * nKnowledge, double std)
{
    //qDebug("   normativeInfluence");
    Individual * offspring = new Individual();
    NormativeKnowledgeVariable * nkVariable;

    for (int i=0; i<father->getNumberOfParameters(); i++)
    {
        nkVariable = nKnowledge->getNormativeKnowledgeVariable(i);
        if ( ( father->getParameter(i) < nkVariable->getLowerBound() ) ||
             ( father->getParameter(i) > nkVariable->getUpperBound()) )
        {
            offspring->setParameter(i,getRandom(nkVariable->getLowerBound(),nkVariable->getUpperBound()));
        }else
        {
            // offspring = mutate(father)
            //qDebug("se debe mutar parametro con valor %f",father->getParameter(i));
            offspring->setParameter(i, mutateIndividualParameter(i, father->getParameter(i), std));
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



int PopulationVariation::mutateIndividualParameter(int index, int mean, double std)
{
    // mean representa el parametro sobre el cual se va a mutar
    // std la desviacion estandar de la distribucion normal

    // tomado de http://www.cplusplus.com/reference/random/normal_distribution/

    std::default_random_engine generator;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);

    std::normal_distribution<double>  distribution(mean,std);

    double yi = distribution(generator);

    //qDebug("--Mutar parametro de individuo--");
    //qDebug("   valor de la distribucion normal: %d, %d", mean, std);
    //qDebug(qPrintable(QString::number(yi)));

    // redondear el yi
    int intYi = qRound(yi);

    if (isThisParameterAChannel(index))
    {
        //qDebug("   isThisParameterAChannel(index)");
        if (intYi < 1)
        {
            intYi = 1;
            //qDebug("   el canal mutado esta por debajo del limite (index %d)",index);
        }
        if (intYi > 11)
        {
            intYi = 11;
            //qDebug("   el canal mutado esta por encima del limite (index %d)", index);
        }
        //qDebug(qPrintable("   channel despues de mutado: "+QString::number(intYi)));
    }

    if (isThisParameterAMinChannelTime(index))
    {
        //qDebug("   isThisParameterAMinChannelTime(index)");
        if (intYi < 0)
        {
            intYi = 0;
            //qDebug("   el minChannelTime mutado esta por debajo del limite (index %d)", index);
        }
        if (intYi > 10)
        {
            intYi = 10;
            //qDebug("   el minChannelTime mutado esta por encima del limite (index %d)", index);
        }
        //qDebug(qPrintable("   minChannelTime despues de mutado: "+QString::number(intYi)));
    }

    if (isThisParameterAMaxChannelTime(index))
    {
        //qDebug("   isThisParameterAMaxChannelTime(index)");
        if (intYi < 10)
        {
            intYi = 10;
            //qDebug("   el maxChannelTime mutado esta por debajo del limite (index %d)", index);
        }
        if (intYi > 100)
        {
            intYi = 100;
            //qDebug("   el maxChannelTime mutado esta por encima del limite (index %d)", index);
        }
        //qDebug(qPrintable("   maxChannelTime despues de mutado: "+QString::number(intYi)));
    }

    //qDebug("----return----");
    return intYi;
}


bool PopulationVariation::isThisParameterAChannel(int index)
{
    if ( (index == 0) || (index == 3) || (index == 6) || (index == 9) || (index == 12) ||
         (index == 15) || (index == 18) || (index == 21) || (index == 24) || (index == 27) || (index == 30) )
    {
        return true;
    }
    else
    {
        return false;
    }
}



bool PopulationVariation::isThisParameterAMinChannelTime(int index)
{
    if ( (index == 1) || (index == 4) || (index == 7) || (index == 10) || (index == 13) ||
         (index == 16) || (index == 19) || (index == 22) || (index == 25) || (index == 28) || (index == 31) )
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool PopulationVariation::isThisParameterAMaxChannelTime(int index)
{
    if ( (index == 2) || (index == 5) || (index == 8) || (index == 11) || (index == 14) ||
         (index == 17) || (index == 20) || (index == 23) || (index == 26) || (index == 29) || (index == 32) )
    {
        return true;
    }
    else
    {
        return false;
    }
}



