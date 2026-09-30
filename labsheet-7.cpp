#include <iostream>
#include <string>
using namespace std;

// ================= HUFFMAN TREE =================

struct HuffmanNode
{
    char data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;
};

// Create new node
HuffmanNode* createNode(char data, int freq)
{
    HuffmanNode* temp = new HuffmanNode;

    temp->data = data;
    temp->freq = freq;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

// Print Huffman codes
void printCodes(HuffmanNode* root, string code)
{
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL)
    {
        cout << root->data << " : " << code << endl;
        return;
    }

    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

// Find two smallest nodes
void findSmallestNodes(HuffmanNode* nodes[], int size,
                       int& first, int& second)
{
    first = -1;
    second = -1;

    for (int i = 0; i < size; i++)
    {
        if (nodes[i] == NULL)
            continue;

        if (first == -1 ||
            nodes[i]->freq < nodes[first]->freq)
        {
            second = first;
            first = i;
        }
        else if (second == -1 ||
                 nodes[i]->freq < nodes[second]->freq)
        {
            second = i;
        }
    }
}

// Huffman Encoding
void huffman()
{
    int n;

    cout << "\n===== HUFFMAN ENCODING =====\n";
    cout << "Enter number of characters: ";
    cin >> n;

    if (n <= 0 || n > 50)
    {
        cout << "Invalid number of characters.\n";
        return;
    }

    HuffmanNode* nodes[50];

    for (int i = 0; i < n; i++)
    {
        char ch;
        int freq;

        cout << "Enter character " << i + 1 << ": ";
        cin >> ch;

        cout << "Enter frequency: ";
        cin >> freq;

        nodes[i] = createNode(ch, freq);
    }

    int size = n;

    while (size > 1)
    {
        int first, second;

        findSmallestNodes(nodes, size, first, second);

        HuffmanNode* newNode =
            createNode('#',
                       nodes[first]->freq +
                       nodes[second]->freq);

        newNode->left = nodes[first];
        newNode->right = nodes[second];

        nodes[first] = newNode;
        nodes[second] = nodes[size - 1];

        size--;
    }

    cout << "\nHuffman Codes:\n";
    printCodes(nodes[0], "");
}


// ================= OPTIMAL MERGE =================

// Find two smallest files
void findSmallestFiles(int files[], int n,
                       int& first, int& second)
{
    first = -1;
    second = -1;

    for (int i = 0; i < n; i++)
    {
        if (first == -1 ||
            files[i] < files[first])
        {
            second = first;
            first = i;
        }
        else if (second == -1 ||
                 files[i] < files[second])
        {
            second = i;
        }
    }
}

// Optimal Merge Pattern
void optimalMerge()
{
    int n;

    cout << "\n===== OPTIMAL MERGE PATTERN =====\n";
    cout << "Enter number of files: ";
    cin >> n;

    if (n <= 0 || n > 50)
    {
        cout << "Invalid number of files.\n";
        return;
    }

    int files[50];

    cout << "Enter file sizes:\n";

    for (int i = 0; i < n; i++)
    {
        cin >> files[i];
    }

    int totalCost = 0;

    cout << "\nMerge Sequence:\n";

    while (n > 1)
    {
        int first, second;

        findSmallestFiles(files, n, first, second);

        int mergeCost =
            files[first] + files[second];

        cout << files[first]
             << " + "
             << files[second]
             << " = "
             << mergeCost << endl;

        totalCost = totalCost + mergeCost;

        files[first] = mergeCost;

        // Remove second file
        for (int i = second; i < n - 1; i++)
        {
            files[i] = files[i + 1];
        }

        n--;
    }

    cout << "\nMinimum Total Merge Cost = "
         << totalCost << endl;
}


// ================= MAIN =================

int main()
{
    huffman();
    optimalMerge();

    return 0;
}   