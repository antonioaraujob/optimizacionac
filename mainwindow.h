#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "individual.h"

namespace Ui {
class MainWindow;
}

// Clase que modela la ventana principal del programa
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
private:

    Ui::MainWindow *ui;

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

    // Desviacion estandar para la mutacion
    int mutationSTd;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    // Inicializa la poblacion de individuos de tamano nPopulation
    QList<Individual *> initializePopulation(int nPopulation);

    // Reliza el proceso de evaluacion de los individuos de la poblacion
    void evaluatePopulation();

    // Retorna la lista de individuos aceptados de la poblacion
    QList<Individual *> AcceptedPopulation();
    
    // Retorna el valor de la generacion actual
    int getGenerationCount();

    // Retorna el numero maximo de generaciones
    int getMaxGenerations();

    // Retorna el tamano de la poblacion
    int getPopulationSize();

    // Retorna el porcentaje de aceptacion de individuos
    double getAcceptedPercentage();

    // Retorna el numero de individuos aceptados
    int getAcceptedIndividuals();

    // Retorna la desviacion estandar para la distribucion normal de la mutacion
    double getMutationStd();

    // Retorna verdadero si todos los campos de la ventana son validos
    bool validateFields();

    // Imprime la poblacion
    void printPopulation();

private slots:

    // Slot para ejecutar el algoritmo cultural
    void executeAlgorithm();



};

#endif // MAINWINDOW_H
