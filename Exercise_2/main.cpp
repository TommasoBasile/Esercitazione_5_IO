#include "Utils.hpp"
#include "PolygonalMesh.hpp"

using namespace PolMeshLibrary;
using namespace std;
using namespace Eigen;

int main()
{ PolygonalMesh mesh;
    string path = "Mesh";

    if (! importMesh(path,mesh)){
        cerr << "Errore nell'imparare la mesh." << endl;
        return 1;
    }
  return 0;
}
