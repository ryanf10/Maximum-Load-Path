#include<iostream>
#include<climits>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

typedef pair<int,int> pii; 

bool comparator(pii a, pii b){
    return a.first > b.first;
}

int n;

void djikstra(int from, vector<pii> adjacencyList[], int dad[], int wt[]){
    vector<pii> fringes;
    int *status = (int*)calloc(n, sizeof(int));
    
    wt[from] = INT_MAX;
    status[from] = 2;
    
    for(int i = 0; i < adjacencyList[from].size(); i++){
        int next = adjacencyList[from].at(i).first;
        int cost = adjacencyList[from].at(i).second;
        status[next] = 1;
        wt[next] = cost;
        dad[next] = from;
        fringes.push_back({wt[next],next});
        sort(fringes.begin(),fringes.end(),comparator);
    }

    while(fringes.size()){
        pii tempNow = fringes.at(0);
        int now = tempNow.second;
        fringes.erase(fringes.begin());
        status[now] = 2;

        for(int i = 0; i < adjacencyList[now].size(); i++){
            int next = adjacencyList[now].at(i).first;
            int cost = adjacencyList[now].at(i).second;
            
            if(status[next] == 0){
                status[next] = 1;
                wt[next] = min(wt[now],cost);
                dad[next] = now;
                fringes.push_back({wt[next],next});
                sort(fringes.begin(),fringes.end(),comparator);
            }else if(status[next] == 1 && wt[next] < min(wt[now],cost)){
                wt[next] = min(wt[now],cost);
                dad[next] = now;
                for(int i = 0; i < fringes.size(); i++){
                    if(fringes[i].second == next){
                        fringes[i].first = wt[next];
                        break;
                    }
                }
                sort(fringes.begin(),fringes.end(),comparator);
            }
        }
        
    }
}

void printPath(int dad[], int ind){
    if(ind == -1){
        return;
    }else{
        printPath(dad,dad[ind]);
        cout << ind << endl;
    }
}

int main(){
    int edgeCount, from, to;
    cout << "Jumlah node:"; cin >> n;
    cout << "Jumlah edge:"; cin >> edgeCount;
    cout << "Asal:"; cin >> from;
    cout << "Tujuan:"; cin >> to;

    vector<pii> adjacencyList[n]; //{to, distance}

    int *dad = (int*)calloc(n,sizeof(int));
    int *wt = (int*)calloc(n,sizeof(int));
    

    for(int i = 0; i < n; i++){
        dad[i] = -1;
        wt[i] = -1;
    }

    int vertex1, vertex2, distance;
    cout << "Input Edge :" << endl;
    for(int i = 0; i < edgeCount; i++){
        cin >> vertex1 >> vertex2 >> distance;
        adjacencyList[vertex1].push_back({vertex2, distance});
        adjacencyList[vertex2].push_back({vertex1, distance});
    }

    djikstra(from,adjacencyList,dad,wt);
    cout << "Maximum Load Path: "<< wt[to] << endl;

    cout << "Path:" << endl;
    printPath(dad,to);
}

/*
8
11 
0 
7
0 1 4
0 3 3
0 4 2
1 6 1
2 3 6
2 4 4
2 7 3
4 6 5
5 6 4
5 7 1
6 7 6
*/