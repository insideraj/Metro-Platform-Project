#include<iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <sstream>
#include<climits>
using namespace std;
class Graph_M {
public:
    unordered_map<string,unordered_map<string, int>> adjList;
    class DijkstraPair {
    public:
        string vname;
        string psf;
        int cost;

        bool operator<(const DijkstraPair& o) const {
            return cost > o.cost;  // Min-heap based on cost
        }
    };
    void addVertex(string vertex){
        adjList[vertex] = unordered_map<string,int>();
    }
    void addEdge(string u,string v,int wt){
        adjList[u][v] = wt;
        adjList[v][u] = wt;
    }
    void displayStations(){
        cout << "List of Stations are :- \n";
        for(auto vertex:adjList){
            cout << vertex.first << endl;
        }
    }
    void displaymap(){
        cout << "Metro Map being Displayed :-" << endl;
        for(auto vertex:adjList){
            cout << vertex.first << "->" << endl;
            for(auto neb:vertex.second){
                cout << neb.first << "(" << neb.second << "km)" << endl;
            }
        }
    }
    bool containsVertex(string vertex) {
        return adjList.find(vertex) != adjList.end();
    }
    bool haspath(string sor,string dest,unordered_map<string,bool> processed){
        if(sor==dest){
            return true;
        }
        processed[sor] = true;
        for(auto neb:adjList[sor]){
            if(!processed[neb.first]){
                if(haspath(neb.first, dest, processed)){
                    return true;
                }
            }
        }
        return false;
    }
    int dijkstra(string sor,string dest,bool istime){
        int val = 0;
        unordered_map<string, DijkstraPair> mp;
        priority_queue<DijkstraPair> q;
        for(auto v:adjList){
            DijkstraPair np;
            np.vname = v.first;
            np.cost = INT_MAX;
            np.psf = "";
            mp[v.first] = np;
            if (v.first == sor) {
                np.cost = 0;
                np.psf = v.first;
            }
            q.push(np);
            mp[v.first] = np;
        }

        while(!q.empty()){
            DijkstraPair temp = q.top();
            q.pop();
            if(temp.vname==dest){
                val = temp.cost;
                return val;
            }
            for(auto neb:adjList[temp.vname]){
                if(mp.find(neb.first)!=mp.end()){
                    int oc = mp[neb.first].cost;
                    int nc;
                    if(istime){
                        nc = temp.cost + 120 + 40 * (neb.second);
                    }
                    else{
                        nc = temp.cost + neb.second;
                    }
                    if(nc<oc){
                    DijkstraPair ne = mp[neb.first];
                    ne.cost = nc;
                    ne.psf = ne.psf + " " + neb.first;
                    q.push(ne);
                    mp[neb.first] = ne;
                }

                }
                
            }
        
        }
    return val;
    }

    string getpath(string sor,string dest,bool istime){
        unordered_map<string, DijkstraPair> mp;
        priority_queue<DijkstraPair> q;
        for(auto v:adjList){
            DijkstraPair np;
            np.vname = v.first;
            np.cost = INT_MAX;
            np.psf = v.first;
            mp[v.first] = np;
            if (v.first == sor) {
                np.cost = 0;
                np.psf = v.first;
            }
            q.push(np);
            mp[v.first] = np;
        }

        while(!q.empty()){
            DijkstraPair temp = q.top();
            q.pop();
            if(temp.vname==dest){
                return mp[temp.vname].psf;
            }
            for(auto neb:adjList[temp.vname]){
                if(mp.find(neb.first)!=mp.end()){
                    int oc = mp[neb.first].cost;
                    int nc;
                    if(istime){
                        nc = temp.cost + 120 + 40 * (neb.second);
                    }
                    else {
                    nc = temp.cost + neb.second;
                }
                    if(nc<oc){
                    DijkstraPair ne = mp[neb.first];
                    ne.cost = nc;
                    ne.psf = temp.psf + "->" + neb.first;
                    q.push(ne);
                    mp[neb.first] = ne;
                }

                }
                
            }
        
        }
    return "";
    }
    static void createMetroMap(Graph_M& g) {
        g.addVertex("Noida Sector 62~B");
        g.addVertex("Botanical Garden~B");
        g.addVertex("Yamuna Bank~B");
        g.addVertex("Rajiv Chowk~BY");
        g.addVertex("Vaishali~B");
        g.addVertex("Moti Nagar~B");
        g.addVertex("Janak Puri West~BO");
        g.addVertex("Dwarka Sector 21~B");
        g.addVertex("Huda City Center~Y");
        g.addVertex("Saket~Y");
        g.addVertex("Vishwavidyalaya~Y");
        g.addVertex("Chandni Chowk~Y");
        g.addVertex("New Delhi~YO");
        g.addVertex("AIIMS~Y");
        g.addVertex("Shivaji Stadium~O");
        g.addVertex("DDS Campus~O");
        g.addVertex("IGI Airport~O");
        g.addVertex("Rajouri Garden~BP");
        g.addVertex("Netaji Subhash Place~PR");
        g.addVertex("Punjabi Bagh West~P");

        g.addEdge("Noida Sector 62~B", "Botanical Garden~B", 8);
        g.addEdge("Botanical Garden~B", "Yamuna Bank~B", 10);
        g.addEdge("Yamuna Bank~B", "Vaishali~B", 8);
        g.addEdge("Yamuna Bank~B", "Rajiv Chowk~BY", 6);
        g.addEdge("Rajiv Chowk~BY", "Moti Nagar~B", 9);
        g.addEdge("Moti Nagar~B", "Janak Puri West~BO", 7);
        g.addEdge("Janak Puri West~BO", "Dwarka Sector 21~B", 6);
        g.addEdge("Huda City Center~Y", "Saket~Y", 15);
        g.addEdge("Saket~Y", "AIIMS~Y", 6);
        g.addEdge("AIIMS~Y", "Rajiv Chowk~BY", 7);
        g.addEdge("Rajiv Chowk~BY", "New Delhi~YO", 1);
        g.addEdge("New Delhi~YO", "Chandni Chowk~Y", 2);
        g.addEdge("Chandni Chowk~Y", "Vishwavidyalaya~Y", 5);
        g.addEdge("New Delhi~YO", "Shivaji Stadium~O", 2);
        g.addEdge("Shivaji Stadium~O", "DDS Campus~O", 7);
        g.addEdge("DDS Campus~O", "IGI Airport~O", 8);
        g.addEdge("Moti Nagar~B", "Rajouri Garden~BP", 2);
        g.addEdge("Punjabi Bagh West~P", "Rajouri Garden~BP", 2);
        g.addEdge("Punjabi Bagh West~P", "Netaji Subhash Place~PR", 3);
    }

    };

    int main(){
        Graph_M g;
        g.createMetroMap(g);
        cout << "\n\n\t****WELCOMT TO THE DELHI METRO PLATFORM****\n\n";
        cout << "\t\t\t****MENU****\t\t\t\n";
        cout << "1.LIST ALL THE STATIONS IN THE MAP\n";
        cout << "2.SHOW THE METRO MAP\n";
        cout << "3.GET SHORTEST DISTANCE BETWEEN 'SOURCE' STATION TO 'DESTINATION' STATION\n";
        cout << "4.GET SHORTEST TIME BETWEEN 'SOURCE' STATION TO 'DESTINATION' STATION\n";
        cout << "5.GET SHORTEST PATH(DISTANCE) BETWEEN 'SOURCE' STATION TO 'DESTINATION' STATION\n";
        cout << "6.GET SHORTEST PATH(TIME) BETWEEN 'SOURCE' STATION TO 'DESTINATION' STATION\n";
        cout << "7.IS THERE A PATH BETWEEN 'SOURCE' STATION AND 'DESTINATION' STATION\n";
        cout << "8.EXIT THE MENU\n";

        while(true){
            int choice;
            cout << "ENTER YOUR CHOICE \n";
            cin >> choice;

            if (choice == 8) {
            cout << "\t\t\t*******THANK YOU*******\n";
            break;
        }
        switch (choice) {
            case 1: {
                g.displayStations();
                break;
            }
            case 2: {
                g.displaymap();
                break;
            }
            case 3: {
                string src, dest;
                cout << "ENTER THE SOURCE STATION: ";
                cin >> ws;
                getline(cin, src);
                cout << "ENTER THE DESTINATION STATION: ";
                getline(cin, dest);
                if(g.adjList.find(src)==g.adjList.end()||g.adjList.find(dest)==g.adjList.end()){
                    cout << "INVALID STATION! PLEASE TRY AGAIN\n";
                    break;
                }
            
                int distance = g.dijkstra(src, dest, false);
                cout << "THE SHORTEST DISTANCE FROM " << src << " TO " << dest << " IS " << distance << "KM.\n";
                break;
            }
            case 4: {
                string src, dest;
                cout << "ENTER THE SOURCE STATION: ";
                cin >> ws;
                getline(cin, src);
                cout << "ENTER THE DESTINATION STATION: ";
                getline(cin, dest);
                if(g.adjList.find(src)==g.adjList.end()||g.adjList.find(dest)==g.adjList.end()){
                    cout << "INVALID STATION! PLEASE TRY AGAIN\n";
                    break;
                }
                int time = g.dijkstra(src, dest, true);
                cout << "THE SHORTEST TIME FROM " << src << " TO " << dest << " IS " << time << " MINUTES.\n";
                break;
            }
            case 5: {
                string src, dest;
                cout << "ENTER THE SOURCE STATION: ";
                cin >> ws;
                getline(cin, src);
                cout << "ENTER THE DESTINATION STATION: ";
                getline(cin, dest);
                if(g.adjList.find(src)==g.adjList.end()||g.adjList.find(dest)==g.adjList.end()){
                    cout << "INVALID STATION! PLEASE TRY AGAIN\n";
                    break;
                }
                string path = g.getpath(src, dest, false);
                cout << "THE SHORTEST DISTANCE PATH FROM " << src << " TO " << dest << " IS: " << path << "\n";
                break;
            }
            case 6: {
                string src, dest;
                cout << "ENTER THE SOURCE STATION: ";
                cin >> ws;
                getline(cin, src);
                cout << "ENTER THE DESTINATION STATION: ";
                getline(cin, dest);
                if(g.adjList.find(src)==g.adjList.end()||g.adjList.find(dest)==g.adjList.end()){
                    cout << "INVALID STATION! PLEASE TRY AGAIN\n";
                    break;
                }
                string path = g.getpath(src, dest, true);
                cout << "THE SHORTEST TIME PATH FROM " << src << " TO " << dest << " IS: " << path << "\n";
                break;
            }
            case 7: {
                 string src, dest;
                cout << "ENTER THE SOURCE STATION: ";
                cin >> ws;
                getline(cin, src);
                cout << "ENTER THE DESTINATION STATION: ";
                getline(cin, dest);
                unordered_map<string, bool> m;
                if(g.haspath(src,dest,m)){
                    cout << "There exist a path press 5(distance efficient) or 6(time efficient) to know the path\n";
                }
                    
            }
                default:
                cout << "INVALID CHOICE! PLEASE ENTER A VALID CHOICE (1 to 7).\n";
        }

        cout << "\n***********************************************************\n";
    }

    return 0;
        }
    