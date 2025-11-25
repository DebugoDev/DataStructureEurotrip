#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>

#include "include/Dijkstra.h"
#include "include/Graph.h"
#include "include/Kruskal.h"

using namespace std;

#define RESET "\033[0m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"

void printSeparator(const string &title = "", char symbol = '=', int width = 100, string color = CYAN)
{
    cout << color;
    if (title.empty())
        cout << string(width, symbol) << endl;

    else
    {
        int padding = (width - title.length() - 2) / 2;
        cout << string(padding, symbol) << " " << title << " " << string(padding, symbol) << endl;
    }

    cout << endl;
    cout << RESET;
}

void printAdjacencyMatrix(const Graph &graph, const string &criteria_)
{
    int n = graph.getNumVertices();

    printSeparator(criteria_, '-', 100, BLUE);

    cout << setw(12) << " ";
    for (int i = 0; i < n; i++)
        cout << setw(10) << graph.getVertexName(i).substr(0, 8);

    cout << endl;

    for (int i = 0; i < n; i++)
    {
        cout << setw(12) << graph.getVertexName(i).substr(0, 10);

        for (int j = 0; j < n; j++)
        {
            double weight = numeric_limits<double>::infinity();

            for (const Edge &edge : graph.getAdjacents(i))
            {
                if (edge.getTarget() == j)
                {
                    weight = edge.getWeight(criteria_);
                    break;
                }
            }

            if (weight == numeric_limits<double>::infinity())
                cout << setw(10) << "-";
            else
                cout << setw(10) << fixed << setprecision(1) << weight;
        }
        cout << endl;
    }
    cout << endl;
}

Graph createEurotripGraph()
{
    Graph graph(10);

    graph.setVertexName(0, "Brasil");
    graph.setVertexName(1, "Lisboa");
    graph.setVertexName(2, "Porto");
    graph.setVertexName(3, "Madrid");
    graph.setVertexName(4, "Barcelona");
    graph.setVertexName(5, "Paris");
    graph.setVertexName(6, "Torre Eiffel");
    graph.setVertexName(7, "Berlim");
    graph.setVertexName(8, "Roma");
    graph.setVertexName(9, "Coliseu");

    graph.addBidirectionalEdge(0, 1, 7600, 10.0, 700); // Brasil - Lisboa
    graph.addBidirectionalEdge(0, 3, 8000, 10.5, 750); // Brasil - Madrid
    graph.addBidirectionalEdge(0, 9, 9000, 12.0, 800); // Brasil - Coliseu
    graph.addBidirectionalEdge(1, 2, 310, 2.5, 30);    // Lisboa - Porto
    graph.addBidirectionalEdge(1, 3, 640, 1.2, 120);   // Lisboa - Madrid
    graph.addBidirectionalEdge(2, 6, 300, 1.0, 120);   // Porto - Eiffel
    graph.addBidirectionalEdge(2, 9, 290, 1.1, 200);   // Porto - Coliseu
    graph.addBidirectionalEdge(3, 4, 620, 2.5, 70);    // Madrid - Barcelona
    graph.addBidirectionalEdge(4, 5, 830, 1.5, 100);   // Barcelona - Paris
    graph.addBidirectionalEdge(4, 7, 1500, 2.8, 150);  // Barcelona - Berlim
    graph.addBidirectionalEdge(5, 6, 4, 0.1, 5);       // Paris - Eiffel
    graph.addBidirectionalEdge(5, 7, 1050, 2.0, 150);  // Paris - Berlim
    graph.addBidirectionalEdge(7, 8, 1180, 2.3, 160);  // Berlim - Roma
    graph.addBidirectionalEdge(8, 9, 2, 0.1, 2);       // Roma - Coliseu
    graph.addBidirectionalEdge(8, 6, 280, 0.8, 120);   // Roma - Torre Eiffel

    return graph;
}

double normalize(double value, double minValue, double maxValue)
{
    if (maxValue - minValue == 0)
        return 0.0;
    return (value - minValue) / (maxValue - minValue);
}

int main()
{
    Graph graph = createEurotripGraph();

    cout << endl
         << "As vertices definidas foram: ";
    for (int i = 0; i < graph.getNumVertices(); ++i)
    {
        if (i)
            cout << ", ";
        cout << graph.getVertexName(i);
    }
    cout << endl
         << "Total de vertices: " << graph.getNumVertices() << endl;

    cout << endl;

    printSeparator("GRAFO ORIGINAL", '=', 100);
    graph.printGraph();
    cout << endl;

    printSeparator("MATRIZES DE ADJACENCIA", '=', 100);

    printAdjacencyMatrix(graph, "COST");
    printAdjacencyMatrix(graph, "DISTANCE");
    printAdjacencyMatrix(graph, "TIME");

    printSeparator("CAMINHOS MINIMOS - DIJKSTRA", '=', 100);

    int source = 0;
    int target = 9;

    printSeparator("MENOR CUSTO (EUR)", '-', 100, BLUE);
    DijkstraResult resultCost = Dijkstra::run(graph, source, "COST");
    Dijkstra::printResult(graph, resultCost, source, target);
    cout << endl;

    printSeparator("MENOR DISTANCIA (KM)", '-', 100, BLUE);
    DijkstraResult resultDistance = Dijkstra::run(graph, source, "DISTANCE");
    Dijkstra::printResult(graph, resultDistance, source, target);
    cout << endl;

    printSeparator("MENOR TEMPO (HORAS)", '-', 100, BLUE);
    DijkstraResult resultTime = Dijkstra::run(graph, source, "TIME");
    Dijkstra::printResult(graph, resultTime, source, target);
    cout << endl;

    printSeparator("ARVORE GERADORA MINIMA (AGM) - KRUSKAL", '=', 100);

    printSeparator("AGM DE MENOR CUSTO", '-', 100, BLUE);
    KruskalResult mstCost = Kruskal::run(graph, "COST");
    Kruskal::printResult(graph, mstCost);
    cout << endl;

    printSeparator("AGM DE MENOR DISTANCIA", '-', 100, BLUE);
    KruskalResult mstDistance = Kruskal::run(graph, "DISTANCE");
    Kruskal::printResult(graph, mstDistance);
    cout << endl;

    printSeparator("AGM DE MENOR TEMPO", '-', 100, BLUE);
    KruskalResult mstTime = Kruskal::run(graph, "TIME");
    Kruskal::printResult(graph, mstTime);
    cout << endl;

    printSeparator("ANALISE COMPARATIVA DOS RESULTADOS", '=', 100);

    vector<int> pathCost = Dijkstra::rebuildPath(resultCost, target);
    vector<int> pathDistance = Dijkstra::rebuildPath(resultDistance, target);
    vector<int> pathTime = Dijkstra::rebuildPath(resultTime, target);

    double costByCost, distByCost, timeByCost;
    double costByDist, distByDist, timeByDist;
    double costByTime, distByTime, timeByTime;

    Dijkstra::calculatePathCosts(graph, pathCost, distByCost, timeByCost, costByCost);
    Dijkstra::calculatePathCosts(graph, pathDistance, distByDist, timeByDist, costByDist);
    Dijkstra::calculatePathCosts(graph, pathTime, distByTime, timeByTime, costByTime);

    cout << "COMPARACAO DE CAMINHOS MINIMOS:" << endl
         << endl;
    cout << fixed << setprecision(2);

    cout << setw(25) << "Criterio"
         << setw(15) << "Custo (EUR)"
         << setw(18) << "Distancia (km)"
         << setw(15) << "Tempo (h)" << endl;
    cout << string(73, '-') << endl;

    cout << setw(25) << "Otimizado por CUSTO"
         << setw(15) << costByCost
         << setw(18) << distByCost
         << setw(15) << timeByCost << endl;

    cout << setw(25) << "Otimizado por DISTANCIA"
         << setw(15) << costByDist
         << setw(18) << distByDist
         << setw(15) << timeByDist << endl;

    cout << setw(25) << "Otimizado por TEMPO"
         << setw(15) << costByTime
         << setw(18) << distByTime
         << setw(15) << timeByTime << endl;

    cout << endl;

    cout << "COMPARACAO DE ARVORES GERADORAS MINIMAS:\n"
         << endl;
    cout << setw(25) << "Criterio AGM"
         << setw(15) << "Custo (EUR)"
         << setw(18) << "Distancia (km)"
         << setw(15) << "Tempo (h)" << endl;
    cout << string(73, '-') << endl;

    cout << setw(25) << "AGM por CUSTO"
         << setw(15) << mstCost.totalCost
         << setw(18) << mstCost.totalDistance
         << setw(15) << mstCost.totalTime << endl;

    cout << setw(25) << "AGM por DISTANCIA"
         << setw(15) << mstDistance.totalCost
         << setw(18) << mstDistance.totalDistance
         << setw(15) << mstDistance.totalTime << endl;

    cout << setw(25) << "AGM por TEMPO"
         << setw(15) << mstTime.totalCost
         << setw(18) << mstTime.totalDistance
         << setw(15) << mstTime.totalTime << endl;

    cout << endl;

    printSeparator("CONCLUSOES", '=', 100);

    double minCost = min(costByCost, min(costByDist, costByTime));
    double maxCost = max(costByCost, max(costByDist, costByTime));

    double minDist = min(distByCost, min(distByDist, distByTime));
    double maxDist = max(distByCost, max(distByDist, distByTime));

    double minTime = min(timeByCost, min(timeByDist, timeByTime));
    double maxTime = max(timeByCost, max(timeByDist, timeByTime));

    double weightCost = 1.0 / 3.0, weightDist = 1.0 / 3.0,  weightTime = 1.0 / 3.0;

    double scoreCost = weightCost * normalize(costByCost, minCost, maxCost) +
                       weightDist * normalize(distByCost, minDist, maxDist) +
                       weightTime * normalize(timeByCost, minTime, maxTime);

    double scoreDist = weightCost * normalize(costByDist, minCost, maxCost) +
                       weightDist * normalize(distByDist, minDist, maxDist) +
                       weightTime * normalize(timeByDist, minTime, maxTime);

    double scoreTime = weightCost * normalize(costByTime, minCost, maxCost) +
                       weightDist * normalize(distByTime, minDist, maxDist) +
                       weightTime * normalize(timeByTime, minTime, maxTime);

    string bestCriterion = "CUSTO";
    double bestScore = scoreCost;

    if (scoreDist < bestScore)
    {
        bestCriterion = "DISTANCIA";
        bestScore = scoreDist;
    }
    if (scoreTime < bestScore)
    {
        bestCriterion = "TEMPO";
        bestScore = scoreTime;
    }

    cout << "AVALIACAO DE CUSTO-BENEFICIO:\n" << endl;

    cout << setw(15) << "Criterio"
         << setw(20) << "Pontuacao (0-1)" << endl;
    cout << string(40, '-') << endl;

    cout << setw(15) << "Custo"
         << setw(20) << scoreCost << endl;

    cout << setw(15) << "Distancia"
         << setw(20) << scoreDist << endl;

    cout << setw(15) << "Tempo"
         << setw(20) << scoreTime << endl;

    cout << endl;

    cout << "Melhor custo-beneficio geral: " << bestCriterion << "." << endl;
    cout << "Esse criterio obteve o melhor equilibrio entre os tres fatores.\n" << endl;

    return 0;
}