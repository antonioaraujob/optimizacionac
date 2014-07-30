#ifndef NORMATIVEKNOWLEDGEVARIABLE_H
#define NORMATIVEKNOWLEDGEVARIABLE_H

#include <QObject>


// Clase que modela una variable del conocimiento normativo del espacio de creencias

class NormativeKnowledgeVariable : public QObject
{
    Q_OBJECT

private:

    // Limite inferior de la variable del conocimiento normativo
    double lowerBound;

    // Limite superior de la variable del conocimiento normativo
    double upperBound;

    // Valor de desempeno del limite inferior de la variable del conocimiento normativo
    double lowerBoundPerformance;

    // Valor de desempeno del limite superior de la variable del conocimiento normativo
    double upperBoundPerformance;


public:

    // Constructor de la clase
    explicit NormativeKnowledgeVariable(QObject *parent = 0);
    
    // Constructor que recibe como parametro el tipo de variable:
    // 0 para variable de canal
    // 1 para variable de MinChannelTime
    // 2 para varibale de MaxChannelTime
    NormativeKnowledgeVariable(int type);

    // Constructor que recibe como parametros los valores lower, upper y sus correspondientes
    // valores de desempeno
    NormativeKnowledgeVariable(double lower, double upper, double pLower, double pUpper);

    // Establece el limite inferior de la variable
    void setLowerBound(double lower);

    // Retorna el limite inferior de la variable
    double getLowerBound();

    // Establece el limite superio de la variable
    void setUpperBound(double upper);

    // Retorna el limite superio de la variable
    double getUpperBound();

    // Establece el desempeno del limite inferior de la variable
    void setLowerBoundPerformance(double lowerPerformance);

    // Retorna el valor de desempeno del limite inferior de la variable
    double getLowerBoundPerformance();

    // Establece el desempeno del limite superior de la variable
    void setUpperBoundPerformance(double upperPerformance);

    // Retorna el valor de desempeno del limite superior de la variable
    double getUpperBoundPerformance();

    // Imprime en una cadena legible al humano el contenido de la variable
    QString printVariable();

signals:
    
public slots:
    
};

#endif // NORMATIVEKNOWLEDGEVARIABLE_H
