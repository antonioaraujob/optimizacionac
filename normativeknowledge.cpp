#include "normativeknowledge.h"
#include "normativeknowledgevariable.h"

NormativeKnowledge::NormativeKnowledge(QObject *parent) :
    QObject(parent)
{

    // crear 33 variables de conocimiento normativo y agregarlas a la lista

    NormativeKnowledgeVariable * nkVariable;

    for (int i=0; i<11; i++)
    {
        // variable canal
        nkVariable = new NormativeKnowledgeVariable(0);
        NormativeKnowledgeVariableList.append(nkVariable);

        // variable MinChannelTime
        nkVariable = new NormativeKnowledgeVariable(1);
        NormativeKnowledgeVariableList.append(nkVariable);

        // variable MaxChannelTime
        nkVariable = new NormativeKnowledgeVariable(2);
        NormativeKnowledgeVariableList.append(nkVariable);
    }

}



int NormativeKnowledge::getCountOfVariables()
{
    return NormativeKnowledgeVariableList.count();
}



void NormativeKnowledge::updateNormativeKnowledge(QList<Individual *> selectedIndividualList)
{
    Individual * auxIndividual1;

    double loweri=0;
    double upperi=0;
    double performanceLoweri=0;
    double performanceUpperi=0;

    bool first = true;

    for (int i=0;i<33;i++)
    {
        for (int j=0;j<selectedIndividualList.count();j++)
        {
            auxIndividual1 = selectedIndividualList.at(j);

            if (first){
                loweri=auxIndividual1->getParameter(i);
                upperi=auxIndividual1->getParameter(i);
                performanceLoweri=auxIndividual1->getPerformanceValue();
                performanceUpperi=auxIndividual1->getPerformanceValue();
                first = false;
                continue;
            }
            if (auxIndividual1->getParameter(i) < loweri)
            {
                loweri = auxIndividual1->getParameter(i);
                performanceLoweri = auxIndividual1->getPerformanceValue();
            }
            if (auxIndividual1->getParameter(i) > upperi)
            {
                upperi = auxIndividual1->getParameter(i);
                performanceUpperi = auxIndividual1->getPerformanceValue();
            }

        }

        // actualizar los valores en la variable i del conocimiento normativo
        NormativeKnowledgeVariable * newVariable = new NormativeKnowledgeVariable(loweri, upperi, performanceLoweri, performanceUpperi);
        NormativeKnowledgeVariableList.replace(i, newVariable);

        first = true;
    }
}


void NormativeKnowledge::printNormativeKnowledge()
{


    for (int i=0;i<33;i++)
    {
        qDebug(qPrintable(NormativeKnowledgeVariableList.at(i)->printVariable()));
    }
}




