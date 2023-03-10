//Amanda Yun, akyun, 1903241, pa2

Files Submitted:
List.c
List.h
Graph.c
Graph.h
GraphTest.c
FindPath.c
Makefile
README

In this assignment, we created a program that performs breath first search on a list of vertices. 
The FindPath.c programs reads in a file, where the first line is always the number of vertices or the order. the following lines consist of two integers, the first being the source and the latter being the destination. We add those vertices into the graph using the function addEdge and increment the size of the graph by one. When we use addEdge, the connection is created in both directions (source to the destination and destination to the source). We can also choose to add an arc, which only links the source to the destination. Once we have edges and arcs added, we can call BFS on a vertex which finds the vertex's parent. We can then call getPath, which finds the shortest path to a destination. We then output the results to the out file. If there is no connection between the vertices, then we print that. If there is, then we print the path and how many vertices apart from each other they are. 