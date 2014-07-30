#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>

#include "individual.h"
#include "situationalknowledge.h"
#include "normativeknowledge.h"








inline static bool x_less_than(Individual *p1, Individual *p2)
{
    return p1->getPerformanceValue() < p2->getPerformanceValue();
}




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ************************************************************************
    // parametros de la ejecucion del algoritmo cultural

    // Contador de generaciones
    int generation = 0;

    // Maximo numero de generacion
    int maxGenerations = 3;

    // Porcentaje de aceptacion de individuos
    double acceptPercentage = 20;

    // Numero de individuos de la poblacion
    int population = 10;


    // ************************************************************************

    // Numero de individuos que se aceptaran por generacion
    int numberOfAcceptedIndividuals = (population*acceptPercentage)/100;

    qsrand((uint)QTime::currentTime().msec());

    // Lista para mantener la poblacion
    QList<Individual *> populationList;

    Individual * individuo;

    // Conocimiento situacional
    SituationalKnowledge * sKnowledge = new SituationalKnowledge();

    // Conocimiento normativo
    NormativeKnowledge *nKnowledge = new NormativeKnowledge();
    qDebug("cantidad de variables en conocimiento normativo: %d", nKnowledge->getCountOfVariables());

    qDebug("++++++ conocimiento normativo inicial+++++");
    nKnowledge->printNormativeKnowledge();
    qDebug("++++++++++++++++++++++++++++++++++++++++++");

    // ************************************************************************

    // inicializacion de la poblacion
    for (int i=0; i<population; i++)
    {
        individuo = new Individual();
        individuo->printIndividual();
        populationList.append(individuo);
    }
    qDebug("tamano de la poblacion: %d",populationList.count());
    qDebug("numero de individuos aceptados %d", numberOfAcceptedIndividuals);


    // ordenamiento de la poblacion de menor a mayor valor de desempeno
    // la selecccion sera luego por el final de la cola
    qSort(populationList.begin(), populationList.end(), x_less_than);

    for (int i=0; i<population; i++)
    {
        populationList.at(i)->printIndividual();
    }

    qDebug("tamano de la poblacion: %d",populationList.count());

    // ************************************************************************

    // inicializacion del espacio de creencias

    // para el conocimiento situacional se agregara el individuo con el mejor valor de
    // desempeno
    sKnowledge->addExemplarIndividual(populationList.at(populationList.count()-1));
    qDebug("mejor ejemplar:");
    sKnowledge->getExemplar(0)->printIndividual();
    qDebug("numero de ejemplares en conocimiento situacional: %d",sKnowledge->getCountOfExemplars());


    // para el conocimiento normativo la inicializacion se ejecuta al crear las variables
    // con sus correspondientes valores de restricciones

    QList<Individual *> selectedIndList;
    selectedIndList.append(populationList.at(populationList.count()-1));
    selectedIndList.append(populationList.at(populationList.count()-2));

    nKnowledge->updateNormativeKnowledge(selectedIndList); // falta la lista de individuos
    qDebug("++++++ conocimiento normativo actualizado+++++");
    nKnowledge->printNormativeKnowledge();
    qDebug("++++++++++++++++++++++++++++++++++++++++++++++");


    // la condicion de parada es que el numero de generaciones sea estrictamente menor que el maximo
    // numero de generaciones
    do
    {
        // Evaluar la poblacion en el tiempo t


        // realizar un ordenamiento de la poblacion con respecto al valor de desempeno


        // Ajustar el espacio de creencias con los individuos aceptados


        // Ejecutar variacion en la poblacion con la influencia del espacio de creencias



        // seleccionar individuos



        qDebug("generacion: %d",generation);
        generation++;
    }while(generation < maxGenerations); // fin de la repeticion

    qDebug("evolucionaron %d generaciones",generation);


    delete individuo;

}

MainWindow::~MainWindow()
{
    delete ui;
}
