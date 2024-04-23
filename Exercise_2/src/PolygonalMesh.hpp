#pragma once
#include <iostream>
#include <vector>
#include <Eigen/Eigen>

using namespace std;
using namespace Eigen;

namespace PolMeshLibrary{

struct PolygonalMesh{
    unsigned int NumberCell0s = 0;
    vector<unsigned int> IdCell0s;
    vector<Vector2d> CoordinateCells0s;  // si memorizza nodi in vector
    map<unsigned int, Vector2d> CoordinateId;
    map<unsigned int, list<unsigned int>> MarkerCell0s;   // si memorizza i marker

    unsigned int NumberCell1s = 0;
    vector<unsigned int> IdCell1s;
    vector<Vector2i> VerticesCell1s; // si memorizza i vertici in vettori
    map<unsigned int, list<unsigned int>> MarkerCell1s;

    unsigned int NumberCell2s = 0;
    vector<unsigned int> IdCell2s;
    vector<vector<unsigned int>> VerticesCell2s; // vettore di vettori
    vector<vector<unsigned int>> EdgesCell2s;    // vettore di vettori

    double tol = numeric_limits<double>::epsilon(); // precisione
    double tol_aree = tol*tol/2;
};
};

