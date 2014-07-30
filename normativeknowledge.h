#ifndef NORMATIVEKNOWLEDGE_H
#define NORMATIVEKNOWLEDGE_H

#include <QObject>

#include "normativeknowledgevariable.h"
#include "individual.h"

// Clase que modela el conocimiento normativo del espacio de creencias
class NormativeKnowledge : public QObject
{
    Q_OBJECT

private:

    // Lista de variables de conocimiento normativo
    QList<NormativeKnowledgeVariable *> NormativeKnowledgeVariableList;

public:

    // Constructor de la clase
    explicit NormativeKnowledge(QObject *parent = 0);


    // Retorna la cantidad de variables en el conocimiento normativo
    int getCountOfVariables();



    // Actualiza el conocimiento normativo a partir de la lista de indivuos
    // seleccionados
    void updateNormativeKnowledge(QList<Individual *> selectedIndividualList);

    // Imprime el conocimiento normativo en forma legible al humano
    void printNormativeKnowledge();

signals:
    
public slots:
    
};

#endif // NORMATIVEKNOWLEDGE_H
