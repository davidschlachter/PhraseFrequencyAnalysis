#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <time.h>

#include "graph.cpp"

using namespace std;

int main(int argc, char *argv[]){

    ifstream instream;
    instream.open("C://Users//Owner//David//myfiles//GitRepository//source.txt");
    if (instream.fail()) {
        cout << "Error opening file" << endl;
        return EXIT_FAILURE;
    } else
        cout << "Source file opened successfully" << endl;


    ofstream outstream;
    outstream.open("C://Users//Owner//David//myfiles//GitRepository//sourceFiltered.txt");
    if (instream.fail()) {
        cout << "Error writing file" << endl;
        return EXIT_FAILURE;
    } else
        cout << "Output file opened successfully" << endl;


    Graph<string> test2;
    char currentStr[256];
    int counter=0, edgeCounter=0;

    time_t rawtime;
    clock_t t;
    t = clock();
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    printf("Starting program run at: %s", asctime(timeinfo));

    while(!instream.eof()){
        instream.getline(currentStr,256); //retrieves c-string object
        string prevString="", currentString; // string object to hold converted c-string

        // convert c-string to a string object
        for (int i=0; i <= strlen(currentStr) ; i++){
            currentString +=currentStr[i];
        }

        prevString = currentString;
        test2.addVertex(currentString);
        counter++;
        if(prevString != ""){
            test2.addEdge(prevString, currentString);
            edgeCounter++;
        }
    }
    time (&rawtime);
    timeinfo = localtime (&rawtime);

    t= clock()-t;
    printf("Program finished at:     %s", asctime(timeinfo));
    printf("It took me %d clicks (%f seconds).\n", t, ((float)t)/CLOCKS_PER_SEC);
    cout << "# of vertices examined: " << counter << "  # of edges: " << edgeCounter << endl;
    cout << "# of vertices in graph: " << test2.getNumberVertices()<<endl;

/**
    // DEFINE THE START AND END POINTS
    string startVertex = "the";
    string destiVertex = "person";


    cout << "Paths from \'" << startVertex
         << "\' to \'"<< destiVertex << "\'" << endl;
    cout << "BFS: "; BFS(test,startVertex,destiVertex);
    cout << "DFS: "; DFS(test,startVertex,destiVertex);
    cout << endl;

    vector<vector<string> > paths;
    getPaths(test,startVertex,destiVertex, paths);

    cout << "# of \'possible paths\': " << paths.size() << endl;
    cout << "List of lengths of each path vector: " << endl;
    for(int i = 0; i < paths.size(); i++){
        if( i !=0 && i < paths.size())
            cout << ", ";
        cout << paths.at(i).size()-1;
    }
    cout << endl;
    cout << "Displaying all paths: "<<endl;
    for(int i = 0; i < paths.size(); i++){
        for(int j = 0; j < paths.at(i).size(); j++){
            cout << paths[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl << endl;
*/
    return EXIT_SUCCESS;
}
