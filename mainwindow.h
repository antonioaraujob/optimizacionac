#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "individual.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
private:

    // Lista de la poblacion de individuos
    QList<Individual *> populationList;


    // Contador de generaciones
    int generation;

    // Maximo numero de generacion
    int maxGenerations;

    // Porcentaje de aceptacion de individuos
    double acceptedPercentage;

    // Numero de individuos de la poblacion
    int population;

    // Numero de individuos que se aceptaran por generacion
    int numberOfAcceptedIndividuals;

    // Imprime la poblacion
    void printPopulation();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    // Inicializa la poblacion de individuos de tamano nPopulation
    QList<Individual *> initializePopulation(int nPopulation);

    // Reliza el proceso de evaluacion de los individuos de la poblacion
    void evaluatePopulation();


    QList<Individual *> AcceptedPopulation();
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
