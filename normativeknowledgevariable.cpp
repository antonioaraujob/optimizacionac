#include "normativeknowledgevariable.h"

NormativeKnowledgeVariable::NormativeKnowledgeVariable(QObject *parent) :
    QObject(parent)
{
    lowerBound = 0;
    upperBound = 0;
    lowerBoundPerformance = 0;
    upperBoundPerformance = 0;
}

NormativeKnowledgeVariable::NormativeKnowledgeVariable(int type)
{
    if (type == 0)
    {
        lowerBound = 1;
        upperBound = 11;
        lowerBoundPerformance = 0;
        upperBoundPerformance = 0;
    }
    if (type == 1)
    {
        lowerBound = 0;
        upperBound = 10;
        lowerBoundPerformance = 0;
        upperBoundPerformance = 0;
    }
    if (type == 2)
    {
        lowerBound = 10;
        upperBound = 100;
        lowerBoundPerformance = 0;
        upperBoundPerformance = 0;
    }
}

NormativeKnowledgeVariable::NormativeKnowledgeVariable(double lower, double upper, double pLower, double pUpper)
{
    lowerBound = lower;
    upperBound = upper;
    lowerBoundPerformance = pLower;
    upperBoundPerformance = pUpper;
}

void NormativeKnowledgeVariable::setLowerBound(double lower)
{
    lowerBound = lower;
}

double NormativeKnowledgeVariable::getLowerBound()
{
    return lowerBound;
}

void NormativeKnowledgeVariable::setUpperBound(double upper)
{
    upperBound = upper;
}

double NormativeKnowledgeVariable::getUpperBound()
{
    return upperBound;
}

void NormativeKnowledgeVariable::setLowerBoundPerformance(double lowerPerformance)
{
    lowerBoundPerformance = lowerPerformance;
}

double NormativeKnowledgeVariable::getLowerBoundPerformance()
{
    return lowerBoundPerformance;
}

void NormativeKnowledgeVariable::setUpperBoundPerformance(double upperPerformance)
{
    upperBoundPerformance = upperPerformance;
}

double NormativeKnowledgeVariable::getUpperBoundPerformance()
{
    return upperBoundPerformance;
}

QString NormativeKnowledgeVariable::printVariable()
{
    return QString(QString::number(lowerBound)+" "+QString::number(upperBound)+" "+
                   QString::number(lowerBoundPerformance)+" "+QString::number(upperBoundPerformance));
}
