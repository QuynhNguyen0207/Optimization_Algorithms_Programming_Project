#include<iostream>
#include <vector>
#include <string>
#include <cstring>
#include <set>
#include <queue>
using namespace std;

#define RUN_SAMPLE_1
#define RUN_SAMPLE_2
#define RUN_SAMPLE_3
#define RUN_SAMPLE_4
#define RUN_SAMPLE_5
#define RUN_SAMPLE_6
#define RUN_SAMPLE_7

bool DEV = false;
bool DEBUG = false;

void printDebugLineToConsole(bool debug=DEBUG) {
  if(debug){

    cout << endl;
  }
}

void printDebugMsgToConsole(string msg, bool debug=DEBUG, bool print_new_line = true){
  if(debug){
    cout << msg;
    if(print_new_line){
      printDebugLineToConsole(debug);
    }
  }
}

class Edge {

  public:
    int weight = 0;
    int node1;
    int node2;

    Edge(int node1, int node2, int w){
      this->weight = w;
      this->node1 = node1;
      this->node2 = node2;
    }
};

class Compare
{
public:
    bool operator() (Edge a, Edge b)
    {
        return a.weight > b.weight;
    }
};


// C++ program to print all the cycles
// in an undirected graph
const int N = 100000;

const char ELEMENT_SEPARATOR = ',';
const bool CONNECTED = 1;
// const bool UNCONNECTED = 0;

int total_nodes_in_graph = 0;
int total_construction_cost = 0;
int ** build_costs;
int ** destroy_costs;
// variables to be used
// in both functions
/**
 * this graph[N] an array of vectors, which represents the graph.
 * Ex: {
 *    1 -> 3 -> 5 -> 9,
 *    0 -> 5,
 *    3 -> 4 -> 11,
 * ....
 * }
 * */ 
vector<int> graph[N];
int cyclic_nodes[N]; // If a node does not belong to any cycle, mark it as 1. Otherwise, a number greater than 1. 
multiset<int> all_not_visited_nodes; // all nodes which have not been visited yet.
multiset<int> all_not_visited_nodes_input_cache; // all nodes which have not been visited yet.

int connected_node_groups_size = 0;
multiset<int> connected_node_groups[N]; // this is collection of groups of connected nodes.

/**
 * cycles is a vector of vectors. For example:
 *   {1 -> 4 -> 99} -> {2 -> 3} -> {3 -> 11 -> 13 -> 5}
 * or 
 *    {5 -> 6 -> 4 -> 3} -> {10 -> 9 -> 5 -> 6} -> {13 -> 12 -> 11 }
*/
vector<vector<int>> cycles;



void print_non_cyclic_nodes() {
    printDebugMsgToConsole("Non cyclic nodes: ");
    for(int n = 1; n < N; n++){
        if( cyclic_nodes[n] == 1){

            printDebugMsgToConsole(to_string(n) + " ", DEBUG, false);
        }
    }
    printDebugLineToConsole();
}


void print_all_not_visited_nodes(){
  printDebugMsgToConsole("Print all_not_visited_nodes: ");
  for(int n : all_not_visited_nodes) {
    printDebugMsgToConsole(to_string(n) + " ", DEBUG, false);
  }
  printDebugLineToConsole();
}

void mark_node_as_visited(int n){

  cyclic_nodes[n]++;
  
  
  const auto it = all_not_visited_nodes.find(n);
  if (it != all_not_visited_nodes.end()){

    all_not_visited_nodes.erase(it);
  }
}

void add_node_to_latest_connected_node_group(int n) {
  auto pos = connected_node_groups[connected_node_groups_size-1].find(n);
  if(pos == connected_node_groups[connected_node_groups_size-1].end()){

    connected_node_groups[connected_node_groups_size-1].insert(n);
  }
}


void print_all_connected_node_group() {
  printDebugMsgToConsole("Print all_connected_node_group: ");
  for(multiset<int> s : connected_node_groups){
    if(s.size() == 0){
      continue;
    }

    printDebugMsgToConsole("  . ", DEBUG, false);
    for(int n : s)
    {
      printDebugMsgToConsole(to_string(n) + " ", DEBUG, false);
    }
    printDebugLineToConsole();
  }
}

// Function to mark the vertex with
// different colors for different cycles
void dfs_cycle(int u, int p, int color[], int par[], int &cyclenumber)
{
  add_node_to_latest_connected_node_group(u);
  mark_node_as_visited(u);
  // already (completely) visited vertex.
  if (color[u] == 2)
  {
      return;
  }

  // seen vertex, but was not completely visited -> cycle detected.
  // backtrack based on parents to find the complete cycle.
  if (color[u] == 1)
  {
      vector<int> v;
      cyclenumber++;

      int cur = p;
      v.push_back(cur);
      mark_node_as_visited(cur);

      // backtrack the vertex which are
      // in the current cycle thats found
      while (cur != u)
      {
        cur = par[cur];
        v.push_back(cur);
        mark_node_as_visited(cur);
      }
      cycles.push_back(v); // add the vector of cycle into the main vector of cycles.
      return;
  }
  par[u] = p;

  // partially visited.
  color[u] = 1;

  /**  simple dfs (Depth-First Search) on graph
   * graph[u] is a vector of vertices connected to vertex u.
   * */
  for (int v : graph[u])
  {

      // if it has not been visited previously
      if (v == par[u])
      {
        continue;
      }
      dfs_cycle(v, u, color, par, cyclenumber);
  }

  // completely visited.
  color[u] = 2;
}

// add the edges to the graph
void addEdge(int u, int v)
{
  for(int e : graph[u]){
    if (e == v){
      return;
    }
  }
  graph[u].push_back(v);
  graph[v].push_back(u);
}

// Function to print the cycles
void printCycles(int &cyclenumber)
{

  // print all the vertex with same cycle
  for (int i = 0; i < cyclenumber; i++)
  {
      // Print the i-th cycle
      printDebugMsgToConsole("Cycle Number " + to_string(i + 1) + ": ");
      for (int x : cycles[i])
      {
        printDebugMsgToConsole(to_string(x) + " ", DEBUG, false);
      }
      printDebugLineToConsole();
  }
}

void printGraph() {
  printDebugMsgToConsole("Print Graph Connections: ");
  for(vector<int> v : graph){
    if (v.size() ==0){
      continue;
    }

    for(int n : v){
      printDebugMsgToConsole(to_string(n) + " ", DEBUG, false);
    }
    printDebugLineToConsole();
  }
}
void sample_code() {

  // add edges to create the representation of the graph.
  addEdge(1, 2);
  addEdge(2, 3);
  addEdge(3, 4);
  addEdge(4, 6);
  addEdge(4, 7);
  addEdge(5, 6);
  addEdge(3, 5);
  addEdge(7, 8);
  addEdge(6, 10);
  addEdge(5, 9);
  addEdge(10, 9);
  addEdge(10, 11);
  addEdge(11, 12);
  addEdge(11, 13);
  addEdge(12, 13);

  // arrays required to color the
  // graph, store the parent of node
  int color[N]; // initial values are 0
  int par[N]; // initial values are 0

  // store the numbers of cycle
  int cyclenumber = 0;

  // call DFS to mark the cycles
  dfs_cycle(1, 0, color, par, cyclenumber);

  // function to print the cycles
  printCycles(cyclenumber);
}

void construct_graph(string input) {

  int vector_row_index = 1;
  int vector_col_index = 1;
  
  
  for (char c : input) {
    if (c == ELEMENT_SEPARATOR){
      all_not_visited_nodes.insert(vector_row_index);
      vector_row_index++;
      vector_col_index = 1;
      continue;
    }
    int connection = int(c) - 48;
    if (connection == CONNECTED){

      addEdge(vector_row_index, vector_col_index);
    }
    vector_col_index++;
  }
  all_not_visited_nodes.insert(vector_row_index);
  all_not_visited_nodes_input_cache = all_not_visited_nodes;
}

void build_cycles_and_non_cyclic_nodes(int & cyclenumber) {
  int color[N]; // initial values are 0
  memset(color, 0, N);
  int par[N]; // initial values are 0
  memset(par, 0, N);

  // call DFS to mark the cycles
  while(!all_not_visited_nodes.empty()){
    auto  cur = all_not_visited_nodes.begin();
    connected_node_groups_size++;
    dfs_cycle(*cur, 0, color, par, cyclenumber);

  }
}

int calculate_destruction_cost_between_two_nodes(int node1, int node2){
  return destroy_costs[node1-1][node2-1];
}

int calculate_build_cost_between_two_nodes(int node1, int node2){

  return build_costs[node1-1][node2-1];
}



int find_single_cycle_destruction_with_minimum_cost(vector<int> cycle, int& disconnected_node1, int& disconnected_node2){
  printDebugMsgToConsole("...doing find_single_cycle_destruction_with_minimum_cost");
  if(cycle.size() < 2){
    // a cycle must have at least 3 nodes, consisting of the main node and the ones in its vector <cycle>.
    // otherwise, do not process.
    return -1;
  }

  int min_destroy_cost = calculate_destruction_cost_between_two_nodes(cycle.front(), cycle.back());
  disconnected_node1 = cycle.front();
  disconnected_node2 = cycle.back();

  printDebugMsgToConsole("min_destroy_cost=" + to_string(min_destroy_cost) + " at. " + to_string(disconnected_node1) + " and " + to_string(disconnected_node2));
  int prev_node = cycle.front();
  int new_destroy_cost = -1;

  printDebugMsgToConsole("print cycle: ", DEBUG, false);
  for(int n : cycle){
    printDebugMsgToConsole(to_string(n) + " -> ", DEBUG, false);
  }
  printDebugLineToConsole();

  for(int cur_node : cycle){

    printDebugMsgToConsole("...looping at cur_node=" + to_string(cur_node));
    if (cur_node == prev_node)
    {
      prev_node = cur_node;
      continue;
    }
    new_destroy_cost = calculate_destruction_cost_between_two_nodes(prev_node, cur_node);
    printDebugMsgToConsole("new_destroy_cost: " + to_string(new_destroy_cost));
    if(new_destroy_cost < min_destroy_cost){
      min_destroy_cost = new_destroy_cost;
      disconnected_node1 = cur_node;
      disconnected_node2 = prev_node;
    }

    prev_node = cur_node;
  }

  printDebugMsgToConsole("...end of find_single_cycle_destruction_with_minimum_cost");
  return min_destroy_cost;
}

void destroy_single_cycle_with_minimum_cost(vector<int> cycle, int& disconnected_node1, int& disconnected_node2){
  if(cycle.size() < 2){
    // a cycle must have at least 3 nodes, consisting of the main node and the ones in its vector <cycle>.
    // otherwise, do not process.
    return;
  }

  int min_destroy_cost = calculate_destruction_cost_between_two_nodes(cycle.front(), cycle.back());
  printDebugMsgToConsole("Min destroy cost between " + to_string(cycle.front()) + " and "  + to_string(cycle.back()) + " is " + to_string(min_destroy_cost));
  int prev_node = cycle.front();
  int new_destroy_cost = -1;
  for(int cur_node : cycle){
    if (cur_node == prev_node)
    {
      prev_node = cur_node;
      continue;
    }
    new_destroy_cost = calculate_destruction_cost_between_two_nodes(prev_node, cur_node);
    printDebugMsgToConsole("new_destroy_cost between " + to_string(cur_node) + " and " + to_string(prev_node) + " is " + to_string(new_destroy_cost));
    
    min_destroy_cost = (new_destroy_cost > 0) ? min(new_destroy_cost, min_destroy_cost) : new_destroy_cost;
    printDebugMsgToConsole("updated min_destroy_cost: " + to_string(min_destroy_cost) );
    prev_node = cur_node;
  }

  total_construction_cost += min_destroy_cost;
}

void destroy_single_cycle_with_minimum_cost(vector<int> cycle){
  int node1;
  int node2;
  destroy_single_cycle_with_minimum_cost(cycle, node1, node2);
}

void delete_direct_connection(int n1, int to_delete_node){
  int i = 0;
  bool matched = false;
  printDebugMsgToConsole("...delete_direct_connection at graph[" + to_string(n1) + "].size(): " + to_string(graph[n1].size()));
  for(i=0; i < (int)graph[n1].size(); i++){
    if(graph[n1][i] == to_delete_node){
      matched = true;
      break;
    }
  }

  if(matched){

    graph[n1].erase(graph[n1].begin() + i);
  }
}

void delete_connection_in_graph(int n1, int n2) {
  delete_direct_connection(n1, n2);
  delete_direct_connection(n2, n1);
}

bool cycleContainsConnection(vector<int> cycle, int n1, int n2){
  if(n1 == cycle.front() && n2 == cycle.back()){
    return true;
  }else if (n2 == cycle.front() && n1 == cycle.back())
  {
    return true;
  }

  int prev = cycle.front();
  for(int cur : cycle){
    if(cur == prev){
      continue;
    }
    if(n1 == cur && n2 == prev){
      return true;
    }else if (n2 == cur && n1 == prev)
    {
      return true;
    }
    prev = cur;
  }
  
  return false;
}

void break_the_least_cost_connection_among_non_broken_cycles(vector<vector<int>>& non_broken_cycles){

  int min_node1, min_node2;
  int broken_cycle_index = 0;
  int min_destruction_cost = -1;
  printDebugMsgToConsole("non_broken_cycles.size(): " + to_string(non_broken_cycles.size()));
  for(int i=0; i < (int)non_broken_cycles.size(); i++){
    
    printDebugMsgToConsole("...looping break_the_least_cost_connection_among_non_broken_cycles at step-i: " + to_string(i));

    vector<int> cur_cycle = non_broken_cycles[i];
    int node1, node2;
    int cur_min_cost = find_single_cycle_destruction_with_minimum_cost(cur_cycle, node1, node2);
    printDebugMsgToConsole("node1: " + to_string(node1));
    printDebugMsgToConsole("node2: " + to_string(node2));
    if(min_destruction_cost < 0 
      || cur_min_cost < min_destruction_cost){
      min_node1 = node1;
      min_node2 = node2;
      min_destruction_cost = cur_min_cost;
      broken_cycle_index = i;
      printDebugMsgToConsole("current broken_cycle_index=" + to_string(broken_cycle_index));
      printDebugMsgToConsole("current min_node1=" + to_string(min_node1));
      printDebugMsgToConsole("current min_node2=" + to_string(min_node2));
      printDebugMsgToConsole("current min_destruction_cost=" + to_string(min_destruction_cost));
    }
    printDebugMsgToConsole("end of i=" + to_string(i));
  }
  
  total_construction_cost += min_destruction_cost;
  non_broken_cycles.erase(non_broken_cycles.begin() + broken_cycle_index);
  
  // delete cycles containing connection(min_node1, min_node2) out of non_broken_cycles
  vector<vector<int>> new_non_broken_cycles;
  for(vector<int> c : non_broken_cycles){

    if(!cycleContainsConnection(c, min_node1, min_node2)){

      new_non_broken_cycles.push_back(c);
    }
  }
  non_broken_cycles = new_non_broken_cycles;

  delete_connection_in_graph(min_node1, min_node2);
  printDebugMsgToConsole("min_destruction_cost of deleted connection: " + to_string(min_destruction_cost));
  printDebugMsgToConsole("end of break_the_least_cost_connection_among_non_broken_cycles");
}

void reset_prior_to_defecting_cycles(){
  
  all_not_visited_nodes.clear();
  all_not_visited_nodes = all_not_visited_nodes_input_cache;

  connected_node_groups_size = 0;
  for(int i = 0; i < N; i++){
    connected_node_groups[i].clear();
  }
  memset(cyclic_nodes, 0, sizeof(cyclic_nodes));

  for(vector<int> v : cycles){
    v.clear();
  }
  cycles.clear();
}

void destroy_all_cycles_with_minimum_cost(int & cyclenumber) {
  print_all_connected_node_group();
  printDebugMsgToConsole("...Destroying-_all_cycles_with_minimum_cost:");
  // 1. break all cycles
  vector<vector<int>>  non_broken_cycles = cycles;

  printDebugMsgToConsole("non_broken_cycles.size()=" + to_string(non_broken_cycles.size()));
  while(non_broken_cycles.size() > 0){
    break_the_least_cost_connection_among_non_broken_cycles(non_broken_cycles);
  }

  printDebugMsgToConsole("Completed break_the_least_cost_connection_among_non_broken_cycles");

  // 2. run dfs_cycle again to establish separate groups of nodes.
  // FIXME TODO
  int cycle_number = 0 ;
  reset_prior_to_defecting_cycles();
  build_cycles_and_non_cyclic_nodes(cycle_number);
  print_all_connected_node_group();
  printDebugMsgToConsole("XXX #cycles: " + to_string(cycles.size()));

  while(cycles.size() > 0){

    // break cycles
    vector<vector<int>>  non_broken_cycles = cycles;
    while(non_broken_cycles.size() > 0){
      break_the_least_cost_connection_among_non_broken_cycles(non_broken_cycles);
    }
    // Repeat detecting cycles
    cycle_number = 0 ;
    reset_prior_to_defecting_cycles();
    build_cycles_and_non_cyclic_nodes(cycle_number);
    print_all_connected_node_group();
    printDebugMsgToConsole("XXX #cycles: " + to_string(cycles.size()));
  }
}

int get_cost(char c){
  if ( int(c) - int('Z') > 0 ){
    // c is lower case
    return  int(c) - int('Z') + 19;
  } else {
    // c is upper case
    return int(c) - int('A');
  }
}

void construct_build_cost_matrix(string build_string) {
  build_costs = new int*[total_nodes_in_graph];
  for(int i=0; i<total_nodes_in_graph; i++){
    build_costs[i] = new int[total_nodes_in_graph];
  }

  int row_index = 0;
  int col_index = 0;
  for(char c : build_string){
    if(c == ELEMENT_SEPARATOR){
      row_index++;
      col_index = 0;
      continue;
    }
    int cost = get_cost(c);
    build_costs[row_index][col_index++] = cost;
  }
}


void construct_destroy_cost_matrix(string destroy_string) {
  destroy_costs = new int*[total_nodes_in_graph];
  for(int i=0; i<total_nodes_in_graph; i++){
    destroy_costs[i] = new int[total_nodes_in_graph];
  }

  int row_index = 0;
  int col_index = 0;
  for(char c : destroy_string){
    if(c == ELEMENT_SEPARATOR){
      row_index++;
      col_index = 0;
      continue;
    }
    int cost = get_cost(c);
    destroy_costs[row_index][col_index++] = cost;
  }
}

void print_costs(int ** costs){

  for(int i = 0; i < total_nodes_in_graph; i++){
    for (int j=0; j < total_nodes_in_graph; j++){
      printDebugMsgToConsole(to_string(costs[i][j]) + " ", DEBUG, false);
    }
    printDebugLineToConsole();
  }
}

int calculate_minimum_cost_between_two_separate_groups(int i, int j){
  int min_cost = -1;
  //multiset<int>
  for(int n : connected_node_groups[i]){
    for(int m : connected_node_groups[j]){
      if (n == m) {
        continue;
      }
      int cur_cost = calculate_build_cost_between_two_nodes(n, m);
      min_cost = (min_cost < 0) ? cur_cost : min(min_cost, cur_cost);
    }
  }
  return min_cost;
}




void build_connection_for_all_separated_node_groups(){
  printDebugMsgToConsole("...doing build_connection_for_all_separated_node_groups");
  int groups_count = 0;
  for (multiset<int> s : connected_node_groups){
    if(s.size() == 0){
      break;
    }
    groups_count++;
  }
  int groups_build_costs[groups_count][groups_count]; // contain minimum build cost between any two groups of nodes.
  for(int i=0; i<groups_count; i++){
    for(int j=0; j<groups_count; j++){
      groups_build_costs[i][j] = -1;
    }
  }

  printDebugMsgToConsole("groups_count: " + to_string(groups_count));

  
  int connected_groups[groups_count]; // init with default value 0.
  for (int i=0; i< groups_count; i++){
    connected_groups[i] = 0;
  }

  priority_queue<Edge, vector<Edge>, Compare> minq;

  for(int i=0; i<groups_count; i++){
    for(int j=i+1; j<groups_count; j++){
      if(groups_build_costs[j][i] >= 0){
        groups_build_costs[i][j] = groups_build_costs[j][i];
      }else{
        groups_build_costs[i][j] = calculate_minimum_cost_between_two_separate_groups(i, j);

        Edge new_edge =  Edge(i, j, groups_build_costs[i][j]);
        minq.push(new_edge);
      }
    }
  }

  int connected_group_count = 0;
  while(connected_group_count < groups_count && !minq.empty()) {
    Edge curEdge = minq.top();
    minq.pop();
    
    if (connected_groups[curEdge.node1] != 0 && connected_groups[curEdge.node2] != 0 ) {
      // already added to total cost, so skip this.
      continue;
    }
    total_construction_cost += curEdge.weight;
    if (connected_groups[curEdge.node1] == 0){
      connected_groups[curEdge.node1] = 1;
      connected_group_count++;
    }

    if (connected_groups[curEdge.node2] == 0){
      connected_groups[curEdge.node2] = 1;
      connected_group_count++;
    }
  }
}


void process_test_case(string input, string build_string, string destroy_string, bool print=true) {
  
  construct_graph(input);
  printGraph();
  total_nodes_in_graph = all_not_visited_nodes.size();
  printDebugMsgToConsole("total_nodes_in_graph: " + to_string(total_nodes_in_graph));

  construct_build_cost_matrix(build_string);
  if(print){

    printDebugMsgToConsole("Print Build Costs: ");
    print_costs(build_costs);
  }

  construct_destroy_cost_matrix(destroy_string);
  if(print){
  
    printDebugMsgToConsole("Print Destroy Costs: ");
    print_costs(destroy_costs);
  }

  // store the numbers of cycle
  int cyclenumber = 0;

  // call DFS to mark the cycles
  build_cycles_and_non_cyclic_nodes(cyclenumber);

  // function to print the cycles
  if(print){

    printCycles(cyclenumber);
  }

  // destroy cycles with minimum cost
  destroy_all_cycles_with_minimum_cost(cyclenumber);

  // connect all separated groups of nodes

  build_connection_for_all_separated_node_groups();
}

void assignment_sample_1() {
  string input = "000,000,000";
  string build = "ABD,BAC,DCA";
  string destroy = "ABD,BAC,DCA";
  process_test_case(input, build, destroy);
}

void assignment_sample_2() {
  // print all cycled detected
  string input = "011,101,110";
  string build = "ABD,BAC,DCA";
  string destroy = "ABD,BAC,DCA";
  process_test_case(input, build, destroy);
}

void assignment_sample_3()
{
  string input = "011000,101000,110000,000011,000101,000110";
  string build = "ABDFFF,BACFFF,DCAFFF,FFFABD,FFFBAC,FFFDCA";
  string destroy = "ABDFFF,BACFFF,DCAFFF,FFFABD,FFFBAC,FFFDCA";
  process_test_case(input, build, destroy);
}

void assignment_sample_4()
{
  string input = "0";
  string build = "A";
  string destroy = "A";
  process_test_case(input, build, destroy);
}

void assignment_sample_5()
{
  string input = "0001,0001,0001,1110";
  string build = "AfOj,fAcC,OcAP,jCPA";
  string destroy = "AWFH,WAxU,FxAV,HUVA";
  process_test_case(input, build, destroy);
}

void assignment_sample_6()
{
  string input = "0000000000,0000000011,0001010000,0010010000,0000001000,0011000000,0000100000,0000000011,0100000101,0100000110";
  string build = "AhPEqkSFMM,hAfKPtsDad,PfAyGQkaqN,EKyAeLpRpm,qPGeASfNwo,ktQLSAnCAK,SskpfnAdJS,FDaRNCdAZz,MaqpwAJZAn,MdNmoKSznA ";
  string destroy = "AgTqWWxEYH,gAXPgjzIRA,TXAleTmWvT,qPlAQkwxRO,WgeQAqgbJJ,WjTkqAiTzl,xzmwgiAuHb,EIWxbTuAwk,YRvRJzHwAn,HATOJlbknA";
  process_test_case(input, build, destroy);
}

void assignment_sample_7()
{
  string input = "0111111,1011111,1101111,1110111,1111011,1111101,1111110";
  string build = "AzvpNrk,zAFfVLm,vFAaDFn,pfaAESX,NVDEAco,rLFScAx,kmnXoxA";
  string destroy = "AzeGcYA,zAgCTsQ,egAPSNK,GCPANfu,cTSNAIz,YsNfIAt,AQKuztA";
  process_test_case(input, build, destroy);
}

bool check_unit_test_result(int& total_testcases_count, int expected, int actual){

  total_testcases_count++;
  printDebugMsgToConsole("  .Expected: ", true, false);
  printDebugMsgToConsole(to_string(expected), true);
  printDebugMsgToConsole("  .Actual:   ", true, false);
  printDebugMsgToConsole(to_string(actual), true);
  string result_value = (expected == actual) ? "Passed" : "Failed";
  printDebugMsgToConsole("  .Result: " + result_value, true);
  return expected == actual;
}

void reset_all_global_variables() {

  total_nodes_in_graph = 0;
  total_construction_cost = 0;
  connected_node_groups_size = 0;
  delete [] build_costs;
  delete [] destroy_costs;
  for(int i=0; i<N; i++)
  {
    graph[i].clear();
  }
  memset(cyclic_nodes, 0, sizeof(cyclic_nodes));
  all_not_visited_nodes.clear(); 

  for(int i = 0; i < N; i++){
    connected_node_groups[i].clear();
  }


  for(vector<int> v : cycles){
    v.clear();
  }
  cycles.clear();
}
void run_all_unit_tests() {
  
  printDebugMsgToConsole("*** START OF UNIT TESTS ***", true);
  DEBUG = false;

  int total_tests = 0;
  bool result = false;
  int passed_count = 0;

  reset_all_global_variables();
#ifdef RUN_SAMPLE_1
  printDebugMsgToConsole("- Running Test on Sample 1:", true);
  assignment_sample_1();
  result = check_unit_test_result(total_tests, 3, total_construction_cost);
  passed_count = (result) ? passed_count + 1 : passed_count;
  printDebugLineToConsole(true);

  reset_all_global_variables();
#endif

#ifdef RUN_SAMPLE_2
  printDebugMsgToConsole("- Running Test on Sample 2:", true);
  assignment_sample_2();
  result = check_unit_test_result(total_tests, 1, total_construction_cost);
  passed_count = (result) ? passed_count + 1 : passed_count;
  printDebugLineToConsole(true);

  reset_all_global_variables();
#endif

#ifdef RUN_SAMPLE_3
  printDebugMsgToConsole("- Running Test on Sample 3:", true);
  assignment_sample_3();
  result = check_unit_test_result(total_tests, 7, total_construction_cost);
  passed_count = (result) ? passed_count + 1 : passed_count;
  printDebugLineToConsole(true);

  reset_all_global_variables();
#endif

#ifdef RUN_SAMPLE_4
  printDebugMsgToConsole("- Running Test on Sample 4:", true);
  assignment_sample_4();
  result = check_unit_test_result(total_tests, 0, total_construction_cost);
  passed_count = (result) ? passed_count + 1 : passed_count;
  printDebugLineToConsole(true);

  reset_all_global_variables();
#endif

#ifdef RUN_SAMPLE_5
  printDebugMsgToConsole("- Running Test on Sample 5:", true);
  assignment_sample_5();
  result = check_unit_test_result(total_tests, 0, total_construction_cost);
  passed_count = (result) ? passed_count + 1 : passed_count;
  printDebugLineToConsole(true);

  reset_all_global_variables();
#endif

#ifdef RUN_SAMPLE_6
  printDebugMsgToConsole("- Running Test on Sample 6:", true);
  assignment_sample_6();
  result = check_unit_test_result(total_tests, 65, total_construction_cost);
  passed_count = (result) ? passed_count + 1 : passed_count;
  printDebugLineToConsole(true);

  reset_all_global_variables();
#endif

#ifdef RUN_SAMPLE_7
  printDebugMsgToConsole("- Running Test on Sample 6:", true);
  assignment_sample_7();
  result = check_unit_test_result(total_tests, 233, total_construction_cost);
  passed_count = (result) ? passed_count + 1 : passed_count;
  printDebugLineToConsole(true);

  reset_all_global_variables();
#endif
  
  printDebugMsgToConsole("--> FINAL TEST PASSING RATE: " + to_string(passed_count) + " / " + to_string(total_tests) , true);
  printDebugMsgToConsole("*** END OF UNIT TESTS ***", true);
}

void run_test_case(int testcase){
  switch(testcase){
    case 1:
        assignment_sample_1();
        break;
    case 2:
        assignment_sample_2();
        break;
    case 3:
        assignment_sample_3();
        break;
    case 4:
        assignment_sample_4();
        break;
    case 5:
        assignment_sample_5();
        break;
    case 6:
        assignment_sample_6();
        break;
    case 7:
        assignment_sample_7();
        break;
    default:
        // sample_code();
        run_all_unit_tests();
        // break;
        return;
  }
  // printGraph();
  print_non_cyclic_nodes();
  print_all_not_visited_nodes();
  print_all_connected_node_group();
  printDebugMsgToConsole("total_construction_cost is: " + to_string(total_construction_cost), true, true);
  return;
}

int do_main_for_dev(int argc, char** argv)
{
    printDebugMsgToConsole("You have entered " + to_string(argc) + " arguments:");
 
    for (int i = 0; i < argc; ++i)
    {
        printDebugMsgToConsole(" .argument-" + to_string(i) + ": " + argv[i]);
    }

    int testcase = 1;
    if (argc == 2) {
        testcase = stoi(argv[1]);
    }
    printDebugMsgToConsole("testcase chosen is " + to_string(testcase));
    run_test_case(testcase);
    return 0;
}

int do_main_for_submit(){

  string input_strings;
  getline(cin, input_strings);

  int first_pos = input_strings.find(" ");
  int substr_len = first_pos;
  string graph_string = input_strings.substr(0, substr_len);

  int second_pos = input_strings.find(" ", first_pos+1);
  string build_string = input_strings.substr(first_pos+1, substr_len);


  string destroy_string = input_strings.substr(second_pos+1);
  bool print_debug_log = false;
  process_test_case(graph_string, build_string, destroy_string, print_debug_log);
  return 0;
}


int main(int argc, char** argv){
  if(DEV){
    // FOR DEV & TEST
    do_main_for_dev(argc, argv);
  }else {

    do_main_for_submit();
    cout << total_construction_cost << endl;
  }
  return 0;
}