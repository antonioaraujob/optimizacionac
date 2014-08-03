#include "populationselection.h"

// Funcion de comparacion de individuos con respecto al valor de desempeno
inline static bool x_less_than(Individual *p1, Individual *p2)
{
    return p1->getPerformanceValue() < p2->getPerformanceValue();
}

PopulationSelection::PopulationSelection(QObject *parent) :
    QObject(parent)
{
    newPopulation.clear();
}


PopulationSelection::PopulationSelection(QList<Individual *> population2p)
{
    //int populationSize = population2p.count()/2;

    qSort(population2p.begin(), population2p.end(), x_less_than);

    qDebug("==============PopulationSelection::PopulationSelection============");

    for (int i=(population2p.count()/2); i<(population2p.count()); i++)
    //for (int i=populationSize; i>0; i--)
    {
        population2p.at(i)->printIndividual();

        newPopulation.append(population2p.at(i));

    }
    qDebug("==================================================================");
}

void PopulationSelection::doSelection(QList<Individual *> population2p)
{
    newPopulation.clear();

    int populationSize = population2p.count()/2;
    qDebug("   doSelection: populationSize %d", populationSize);

    qSort(population2p.begin(), population2p.end(), x_less_than);
    qDebug("==============PopulationSelection::PopulationSelection============");
    for (int i=(population2p.count()/2); i<(population2p.count()); i++)
    {
        qDebug("   valor de i: %d",i);
        //population2p.at(i)->printIndividual();

        newPopulation.append(population2p.at(i));

    }
    qDebug("   tamano de newPopulation: %d", newPopulation.count());
    qDebug("==================================================================");

}

QList<Individual *> PopulationSelection::getSelectedPopulation()
{
    return newPopulation;
}

int PopulationSelection::getRandom(int high)
{
    // el rango es 1 <= channel <= 11
    int low = 1;
    //int high = 11;
    return qrand() % ((high + 1) - low) + low;
}
