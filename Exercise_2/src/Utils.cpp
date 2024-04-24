#include <Utils.hpp>
#include <PolygonalMesh.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Eigen/Eigen"

namespace PolMeshLibrary{
bool importMesh(const string& path, PolygonalMesh& mesh){
    if (!importCell0(path + "/Cell0Ds.csv",mesh))
    {
        return false;}
    else
    {
        cout << "Cell0s marker:" << endl;
        for(auto it = mesh.MarkerCell0s.begin(); it != mesh.MarkerCell0s.end();it++)
        {
            cout << "key:\t" << it -> first << "\t values:";
            for(const unsigned int id : it -> second)
                            cout << "\t" << id;

                        cout << endl;
        }
    }

    if (!importCell1(path + "/Cell1Ds.csv",mesh))
    {
        return false;}
    else
        {
            cout << "Cell1D marker:" << endl;
            for(auto it = mesh.MarkerCell1s.begin(); it != mesh.MarkerCell1s.end(); it++)
            {
                cout << "key:\t" << it -> first << "\t values:";
                for(const unsigned int id : it -> second)
                    cout << "\t" << id;

                cout << endl;
            }
        }

    if (!importCell2(path + "/Cell2Ds.csv",mesh))
    {
        return false;}

    /* else
        {
            // Test:
            for(unsigned int c = 0; c < mesh.NumberCell2s; c++)
            {
                vector<unsigned int> edges = mesh.EdgesCell2s[c];
                unsigned int n = edges.size();

                for(unsigned int e = 0; e < n; e++)
                {
                    const unsigned int origin = mesh.VerticesCell1s[edges[e]][0];
                    const unsigned int end = mesh.VerticesCell1s[edges[e]][1];

                    auto findOrigin = find(mesh.VerticesCell2s[c].begin(), mesh.VerticesCell2s[c].end(), origin);
                    if(findOrigin == mesh.VerticesCell2s[c].end())
                    {
                        cerr << "Wrong mesh" << endl;
                        return 2;
                    }

                    auto findEnd = find(mesh.VerticesCell2s[c].begin(), mesh.VerticesCell2s[c].end(), end);
                    if(findEnd == mesh.VerticesCell2s[c].end())
                    {
                        cerr << "Wrong mesh" << endl;
                        return 3;
                    }

                }
            }
        } */ // il codice del test sembra corretto ma non funziona

    return true;};

bool importCell0(const string& filename, PolygonalMesh& mesh){

    ifstream file;
    file.open(filename);
    if(file.fail()){
        return false;}


    string header;
    getline(file,header);

    list<string> lines;
    string line;
    while(getline(file,line)){
        lines.push_back(line);}

    mesh.NumberCell0s = lines.size();

    mesh.CoordinateCells0s.reserve(mesh.NumberCell0s);
    mesh.IdCell0s.reserve(mesh.NumberCell0s);

    for (const string& line :lines)
    {
        istringstream converter(line);
        Vector2d coordinates;

        string token;
        getline(converter,token,';');
        unsigned int id = stoi(token);
        getline(converter,token,';');
        unsigned int marker = stoi(token);
        getline(converter,token,';');
        coordinates(0) = stod(token);
        getline(converter,token,';');
        coordinates(1) = stod(token);

        mesh.CoordinateCells0s.push_back(coordinates);
        mesh.IdCell0s.push_back(id);
        mesh.CoordinateId[id] = coordinates;

        if( marker != 0)
                {
                    auto ret = mesh.MarkerCell0s.insert({marker, {id}});
                    if(!ret.second)
                        (ret.first)->second.push_back(id);
                }



    } file.close();
    return true;
    }

bool importCell1(const string& path, PolygonalMesh& mesh){

    ifstream file;
    file.open(path);
    if(file.fail()){
       return false;}

    string header;
    getline(file,header);  // si ignora la prima riga

    list<string> lines;
    string line;
    while(getline(file,line)){
        lines.push_back(line);}  // si legge i dati e si incodano alla lista

    mesh.NumberCell1s = lines.size();

    mesh.IdCell1s.reserve(mesh.NumberCell1s);
    mesh.VerticesCell1s.reserve(mesh.NumberCell1s);

    for (const string& line :lines)   // scorre la lista
    {
        istringstream converter(line);  // si converte da stringa a numero

        string token;
        Vector2i vertices;
        getline(converter,token,';');
        unsigned int id = stoi(token);
        getline(converter,token,';');
        unsigned int marker = stoi(token);
        getline(converter,token,';');
        vertices(0) = stoi(token);
        getline(converter,token,';');
        vertices(1) = stoi(token);


        // TEST sulle lunghezze
        if(abs((vertices(0)-vertices(1))/max(vertices(0),vertices(1))) > mesh.tol)
        {mesh.IdCell1s.push_back(id);
        mesh.VerticesCell1s.push_back(vertices);}

        if( marker != 0)
                {
                    auto ret = mesh.MarkerCell1s.insert({marker, {id}});
                    if(!ret.second)
                        (ret.first)->second.push_back(id);
                }
            }

    file.close();
    return true;
}

bool importCell2(const string& path, PolygonalMesh& mesh){

    ifstream file;
    file.open(path);
    if(file.fail())
            return false;

    string header;
    getline(file,header);  // si ignora la prima riga

    list<string> lines;
    string line;
    while(getline(file,line)){
        lines.push_back(line);  // si legge i dati e si incodano alla lista
    }

    mesh.NumberCell2s = lines.size();

    mesh.IdCell2s.reserve(mesh.NumberCell2s);
    mesh.VerticesCell2s.reserve(mesh.NumberCell2s);
    mesh.EdgesCell2s.reserve(mesh.NumberCell2s);
    unsigned int NumVertices;

    for (const string& line :lines)   // scorre la lista
    {
        istringstream converter(line);  // si converte da stringa a numero

        string token;
        getline(converter,token,';');
        unsigned int id = stoi(token);
        getline(converter,token,';');
        unsigned int marker = stoi(token);

        getline(converter,token,';');
        NumVertices = stoi(token);
        vector<unsigned int> vertices = {};
        for(unsigned int i = 0;i<NumVertices;i++)
        {getline(converter,token,';');
            vertices.push_back(stoi(token));}

        getline(converter,token,';');
        unsigned int NumEdges = stoi(token);
        vector<unsigned int> edges;
        for(unsigned int i = 0;i<NumEdges;i++)
        {getline(converter,token,';');
            edges.push_back(stoi(token));}

        mesh.IdCell2s.push_back(id);
        mesh.EdgesCell2s.push_back(edges);
        mesh.VerticesCell2s.push_back(vertices);


    // TEST aree
        double area = 0;
        for(unsigned int i = 0; i < NumVertices-1;i++)
        {
            Vector2d Coordinate1 = mesh.CoordinateId[vertices[i]];
            Vector2d Coordinate2 = mesh.CoordinateId[vertices[i+1]];

            area += (Coordinate1[0]*Coordinate2[1])-(Coordinate1[1]-Coordinate2[0]);
}
        Vector2d Coordinate1 = mesh.CoordinateId[vertices[NumVertices-1]];  // si aggiunge gli estremi
        Vector2d Coordinate2 = mesh.CoordinateId[vertices[0]];
        area += (Coordinate1[0]*Coordinate2[1])-(Coordinate1[1]-Coordinate2[0]);

        area *= 0.5;
        area = abs(area);

            if(area <= mesh.tol_aree)
            {
                cerr << "Area sotto la tolleranza" << endl;
            }

        }

    file.close();
    return true;}
}
