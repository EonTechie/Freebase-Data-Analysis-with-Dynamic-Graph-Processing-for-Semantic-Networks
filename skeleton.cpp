/* Filiz Yıldız 
   Graduate School Number : 504231538
   Computer Engineering Department 
   BLG223E Data Structures Course
   2024 Spring Semester
   Project - 3 
*/

#include <iostream>  // Include the standard input-output stream library
#include <vector>    // Include the vector container library
#include <fstream>   // Include the file stream library
#include <map>       // Include the map container library
#include <queue>     // Include the queue container library
#include <sstream>   // Include the string stream library
#include <algorithm> // Include the algorithm library for sorting and other functions

using namespace std; // Use the standard namespace

// Define the structure for a Node in the graph
struct Node {
    string MID; // Freebase ID for each node
    vector<Node*> adj; // Adjacent nodes (neighbors)
    vector<string> relation; // Relationships with these neighbors
};

// Define maps for quick access
map<string, Node*> graph_map = {}; // Map for quick access from MID to Node pointer
map<string, string> graph_name = {}; // Map for quick access from MID to name

// Function to print the neighbors of a node given its MID
void printNeighbors(const string& MID) {
    // Check if the MID exists in the graph
    if (graph_map.find(MID) != graph_map.end()) {
        string name = graph_name[MID]; // Get the name associated with the MID
        Node* node = graph_map[MID]; // Get the node associated with the MID
        cout << node->adj.size() << " neighbors" << endl; // Print the number of neighbors
        cout << "Neighbors of " << MID << " (" << (name.empty() ? "has no name" : name) << "):" << endl;
        // Iterate through the neighbors
        for (int i = 0; i < node->adj.size(); i++) {
            Node* neighbor = node->adj[i]; // Get the neighbor node
            string neighbor_name = graph_name[neighbor->MID]; // Get the neighbor's name
            if (neighbor_name.empty()) {
                cout << "Neighbor MID: " << neighbor->MID << " has no name." << endl; // Print if no name is found
            } else {
                cout << neighbor->MID << " " << neighbor_name << endl; // Print the MID and name of the neighbor
            }
        }
    } else {
        cout << "MID not found" << endl; // Print if the MID is not found
    }
}

// Function to print the top 10 central entities based on degree centrality
void printTopCentralEntities() {
    vector<pair<int, string>> centrality; // Vector to store the degree centrality
    // Iterate through the graph_map
    for (auto it = graph_map.begin(); it != graph_map.end(); it++) {
        centrality.push_back(make_pair(it->second->adj.size(), it->first)); // Push the size of adjacency list and MID
    }
    sort(centrality.rbegin(), centrality.rend()); // Sort in descending order of degree
    // Print the top 10 central entities
    for (int i = 0; i < 10 && i < centrality.size(); i++) {
        string mid = centrality[i].second; // Get the MID
        string name = graph_name[mid]; // Get the name
        cout << mid << " " << name << " with degree " << centrality[i].first << endl; // Print MID, name, and degree
    }
}

// Function to find the shortest path between two nodes using BFS
void findShortestPath(const string& MID1, const string& MID2) {
    // Check if both MIDs exist in the graph
    if (graph_map.find(MID1) == graph_map.end() || graph_map.find(MID2) == graph_map.end()) {
        cout << "One or both MIDs not found" << endl;
        return;
    }

    queue<Node*> q; // Queue for BFS
    map<Node*, Node*> prev; // Map to store the previous node in the path
    map<Node*, bool> visited; // Map to keep track of visited nodes

    Node* start = graph_map[MID1]; // Start node
    Node* end = graph_map[MID2]; // End node

    q.push(start); // Push the start node to the queue
    visited[start] = true; // Mark the start node as visited
    prev[start] = nullptr; // Initialize the start node's previous node as null

    bool found = false; // Flag to indicate if the path is found

    // BFS loop
    while (!q.empty() && !found) {
        Node* current = q.front(); // Get the front node of the queue
        q.pop(); // Remove the front node from the queue

        // Iterate through the neighbors of the current node
        for (Node* neighbor : current->adj) {
            if (!visited[neighbor]) { // If the neighbor is not visited
                visited[neighbor] = true; // Mark the neighbor as visited
                prev[neighbor] = current; // Set the current node as the previous node for the neighbor
                q.push(neighbor); // Push the neighbor to the queue

                if (neighbor == end) { // If the neighbor is the end node
                    found = true; // Set the flag to true
                    break; // Break the loop
                }
            }
        }
    }

    // If no path is found
    if (!found) {
        cout << "No path found between " << MID1 << " and " << MID2 << endl;
        return;
    }

    vector<string> path; // Vector to store the path
    // Construct the path from end to start
    for (Node* at = end; at != nullptr; at = prev[at]) {
        path.push_back(at->MID); // Add the MID to the path
    }
    reverse(path.begin(), path.end()); // Reverse the path to get it from start to end

    cout << "Shortest Distance: " << path.size() - 1 << endl; // Print the distance
    cout << "Shortest path between " << MID1 << " and " << MID2 << ":" << endl; // Print the path
    // Print each node in the path
    for (const string& mid : path) {
        cout << mid << " " << graph_name[mid] << endl;
    }
}

// Main function
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <part> [args...]" << endl; // Print usage message
        return 1;
    }

    string part = argv[1]; // Get the part of the task

    // Open the freebase file
    ifstream infile("freebase.tsv");
    if (!infile.is_open()) {
        cerr << "Error: Could not open file freebase.tsv" << endl; // Print error message if file cannot be opened
        return 1;
    }

    string line; // Variable to store each line from the file
    // Read each line from the file
    while (getline(infile, line)) {
        string ent1 = line.substr(0, line.find("\t")); // Get the first entity (MID1)
        string remain = line.substr(line.find("\t") + 1, line.length() - ent1.length()); // Get the remaining part of the line
        string relationship = remain.substr(0, remain.find("\t")); // Get the relationship
        remain = remain.substr(remain.find("\t") + 1, remain.length() - relationship.length()); // Update the remaining part
        string ent2 = remain.substr(0, remain.find("\r")); // Get the second entity (MID2)

        Node* ent1_node, * ent2_node; // Pointers to the nodes for MID1 and MID2

        // If MID1 is not in the graph, create a new node and add it to the graph
        if (graph_map.find(ent1) == graph_map.end()) {
            ent1_node = new Node;
            ent1_node->MID = ent1;
            graph_map[ent1] = ent1_node;
        } else {
            ent1_node = graph_map[ent1]; // If MID1 is already in the graph, get the existing node
        }

        // If MID2 is not in the graph, create a new node and add it to the graph
        if (graph_map.find(ent2) == graph_map.end()) {
            ent2_node = new Node;
            ent2_node->MID = ent2;
            graph_map[ent2] = ent2_node;
        } else {
            ent2_node = graph_map[ent2]; // If MID2 is already in the graph, get the existing node
        }

        // Add the relationship between the nodes
        ent1_node->adj.push_back(ent2_node); // Add ent2_node to the adjacency list of ent1_node
        ent1_node->relation.push_back(relationship); // Add the relationship to the relation list of ent1_node
        ent2_node->adj.push_back(ent1_node); // Add ent1_node to the adjacency list of ent2_node
        ent2_node->relation.push_back(relationship); // Add the relationship to the relation list of ent2_node
    }

    // Open the mid2name file
    ifstream infile2("mid2name.tsv");
    if (!infile2.is_open()) {
        cerr << "Error: Could not open file mid2name.tsv" << endl; // Print error message if file cannot be opened
        return 1;
    }

    // Read each line from the file
    while (getline(infile2, line)) {
        line.erase(remove(line.begin(), line.end(), '\r'), line.end()); // Remove \r characters
        string MID = line.substr(0, line.find("\t")); // Get the MID
        string remain = line.substr(line.find("\t") + 1, line.length() - MID.length()); // Get the remaining part
        string name = remain.substr(0, remain.find("\t")); // Get the name

        graph_name[MID] = name; // Add the name to the graph_name map
    }

    // Determine which part of the task to perform
    if (part == "part1") {
        if (argc != 3) {
            cout << "Usage: " << argv[0] << " part1 <MID>" << endl; // Print usage message if arguments are incorrect
            return 1;
        }
        string MID = argv[2]; // Get the MID from the arguments
        printNeighbors(MID); // Call the function to print neighbors
    } else if (part == "part2") {
        printTopCentralEntities(); // Call the function to print top central entities
    } else if (part == "part3") {
        if (argc != 4) {
            cout << "Usage: " << argv[0] << " part3 <MID1> <MID2>" << endl; // Print usage message if arguments are incorrect
            return 1;
        }
        string MID1 = argv[2]; // Get the first MID from the arguments
        string MID2 = argv[3]; // Get the second MID from the arguments
        findShortestPath(MID1, MID2); // Call the function to find the shortest path
    } else {
        cout << "Invalid part: " << part << endl; // Print error message if part is invalid
        return 1;
    }

    return 0; // Return 0 to indicate successful execution
}
