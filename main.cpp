#include "Test.h"
#include <iostream>
#include <algorithm>
#include "HeapFunctions.h"
using namespace std;

void printInfo(Node* node)
{
  cout<<"Character: "<<node->character<<" with frequency: "<<node->frequency<<endl;
}

Node* pop_front(std::vector<Node*>* vec)
{
  if((vec->size() == 0))
  {
    exit(-1);
  }
  Node* node = vec->at(0);
  vec->erase(vec->begin());
  return node;
}

//Quicksort adapted from: https://encrypted.google.com/search?hl=en&q=swap()%20elements%20of%20vector%20in%20C%2B%2B#hl=en&q=quicksort+C%2B%2B

int partition (vector<Node*>* arr, int low, int high)
{
    Node* pivot = arr->at(high);
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
    {
        Node* comp = arr->at(j);
        if (comp->frequency <= pivot->frequency)
        {
            i++;
            iter_swap(arr->begin() + (i), arr->begin() + j);
        }
    }
    iter_swap(arr->begin() + (i + 1), arr->begin() + high);
    return (i + 1);
}

void quickSort(vector<Node*>* arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void sort_vector(vector<Node*>* nodes)
{
  quickSort(nodes, 0, nodes->size() - 1);
}

void insert_to_min_heap(std::vector<Node*>* nodes, Node* internal_node)
{
  for(unsigned int i = 0; i < nodes->size(); ++i)
  {
    Node* current = nodes->at(i);
    if(current->frequency >= internal_node->frequency)
    {
      nodes->insert(nodes->begin() + i, internal_node);
      return;
    }
  }
  nodes->insert(nodes->end(), internal_node);
}

void printNodesVector(std::vector<Node*>* nodes)
{
  for(unsigned int i = 0; i < nodes->size(); ++i)
  {
    printInfo(nodes->at(i));
  }
}

void build_heap(std::vector<Node*>* nodes) {
  while(nodes->size() > 1)
  {
    Node* leftNode = pop_front(nodes);
    Node* rightNode = pop_front(nodes);

    int new_freq = leftNode->frequency + rightNode->frequency;
    Node* internal = new Node(' ', new_freq);
    internal->left = leftNode;
    internal->right = rightNode;
    insert_to_min_heap(nodes, internal);
  }
}


void backtracking(Node* current_node, string code, map<char,string>* codes)
{
  if(!current_node)
    return;

  if(current_node->character != ' ')
  {
    (*codes)[current_node->character] = code;
  }

  backtracking(current_node->left, code+"0", codes);
  backtracking(current_node->right, code+"1", codes);
}

map<char,string> getHuffman(vector<char> characters, vector<int> frequencies)
{
  map<char,string> answer;
  vector<Node*>* nodes = new std::vector<Node*>();
  for(unsigned int i = 0; i < characters.size(); ++i)
  {
    nodes->push_back(new Node(characters[i], frequencies[i]));
  }

  sort_vector(nodes);
  build_heap(nodes);
  backtracking(nodes->at(0), "", &answer);
  free(nodes);
  return answer;
}

int main ()
{
    test();
    return 0;
}
