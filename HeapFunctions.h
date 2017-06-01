class Node
{
  public:
    char character;
    int frequency;
    Node* left;
    Node* right;

  Node()
  {
    this->character = (char)NULL;
    this->frequency = 0;
    this->left = NULL;
    this->right = NULL;
  }

  Node(char character, int frequency)
  {
    this->character = character;
    this->frequency = frequency;
    this->left = NULL;
    this->right = NULL;
  }
};

void printInorder(Node* node)
{
    if (node == NULL)
        return;

    cout<<endl<<"Node: "<<node->character<<" ";
    if(node->left != NULL)
      cout<<"Left son: "<<node->left->character;

    if(node->right != NULL)
      cout<<" Right son: "<<node->right->character<<endl;

    printInorder (node->left);
    printInorder (node->right);
}
