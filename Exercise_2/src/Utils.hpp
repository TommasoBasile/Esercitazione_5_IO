#pragma once
#include <iostream>
#include "PolygonalMesh.hpp"

using namespace std;

namespace PolMeshLibrary{

bool importMesh(const string& path, PolygonalMesh& mesh);
bool importCell0(const string& path, PolygonalMesh& mesh);
bool importCell1(const string& path, PolygonalMesh& mesh);
bool importCell2(const string& path, PolygonalMesh& mesh);
};
