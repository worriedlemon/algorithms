#include "flownetwork.h"

// Finding some new 
double FindFlowToAdd(FlowNetwork& graph, size_t currentVertex, size_t drain, bool* visitedVertexes)
{
    static double** capacities = graph.GetValues(), lowestCapacity = INF;

    // If vertex is a drain then it has no outcome, no need to calculate possible flows
    if (currentVertex == drain) return (lowestCapacity == INF ? 0 : lowestCapacity);

    // Current vertex is marked as visited
    visitedVertexes[currentVertex] = true;

    // Processing all vertexes from source to drain
    for (size_t processedVertex = 0; processedVertex <= drain; processedVertex++)
    {
        // This vertex should not be visited, and has a non-zero capacity
        if (!visitedVertexes[processedVertex] && capacities[currentVertex][processedVertex] > 0)
        {
            // Finding minimal edge (with lowest capacity)
            if (capacities[currentVertex][processedVertex] < lowestCapacity)
            {
                lowestCapacity = capacities[currentVertex][processedVertex];
            }

            // Recursively continuing processing this path
            double foundFlow = FindFlowToAdd(graph, processedVertex, drain, visitedVertexes);

            // If found flow is zero, then algorithm can not add more throughput to network
            if (foundFlow > 0)
            {
                capacities[currentVertex][processedVertex] -= foundFlow;
                capacities[processedVertex][currentVertex] += foundFlow;
                return foundFlow;
            }
        }
    }
    return 0;
}

// Ford-Fulkerson algorithm for finding the max flow in flow network
double FordFulkerson(FlowNetwork& graph)
{
    // Copying the network for algorithm
    FlowNetwork current = FlowNetwork(graph);

    const size_t SOURCE = 0, DRAIN = current.GetSize() - 1;

    // Maximum flow is zero at the start
    double foundFlow = -1, maximumFlow = 0;

    // Maximizing flow by finding paths
    for (maximumFlow = 0; foundFlow != 0; maximumFlow += foundFlow) {
        // Creating an array of visited vertexes (used for debugging a path)
        bool* visitedVertexes = new bool[DRAIN + 1] { false };
        foundFlow = FindFlowToAdd(current, SOURCE, DRAIN, visitedVertexes);
        delete[] visitedVertexes;
    }

    return maximumFlow;
}