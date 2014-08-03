#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <QObject>


// Clase que modela un individuo del espacio de poblacion
class Individual : public QObject
{
    Q_OBJECT

private:

    // lista de parametros de un individuo
    QList<double> parametersList;

    // Valor de desempeno del individuo
    double performanceValue;


public:
    // Constructor de la clase
    explicit Individual(QObject *parent = 0);
    
    // Constructor copia
    Individual(Individual &p);

    // Retorna un numero de canal aleatorio
    int getRandomChannel();

    // Retorna un numero de minChannelTime aleatorio
    double getRandomMinChannelTime();

    // Retorna un numero de maxChannelTime aleatorio
    double getRandomMaxChannelTime();

    // Imprime el individuo en una cadena legible al humano
    void printIndividual();

    // Retorna el individuo como una cadena
    QString getIndividualAsQString();

    // Establece el valor de desempeno del individuo
    void setPerformanceValue(double performance);

    // Calcula el valor de desempeno del individuo
    void calculatePerformanceValue();

    // Retorna el valor de desempeno del individuo
    double getPerformanceValue();

    // Asigna el valor del parametro en la posicion i
    void setParameter(int i, double value);

    // Retorna el valor del parametro en la posicion i
    double getParameter(int i);

    // Retorna el numero de parametros del individuo
    int getNumberOfParameters();

signals:
    
public slots:
    
};

#endif // INDIVIDUAL_H
