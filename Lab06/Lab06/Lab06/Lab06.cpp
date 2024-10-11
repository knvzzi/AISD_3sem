#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <Windows.h>
using namespace std;

unordered_map<char, int> freq;

struct Node 
{
	char ch;
	int freq;
	Node* left, * right;
};

Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();  

	node->ch = ch; 
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

struct comp  
{
	bool operator()(Node* l, Node* r) 
	{
		return l->freq > r->freq; 
	}
};

void encode(Node* root, string str, unordered_map<char, string>& huffmanCode) 
{
	if (root == nullptr) 
		return;

	if (!root->left && !root->right) { 
		huffmanCode[root->ch] = str; 
	}

	encode(root->left, str + "0", huffmanCode); 
	encode(root->right, str + "1", huffmanCode);
}


void buildHuffmanTree(string text)
{
	for (char ch : text) { 
		freq[ch]++;
	}

	cout << "\nКоличество повторей букв в строке:" << endl;
	for (auto pair : freq) {
		cout << pair.first << " - " << pair.second << endl;
	}

	priority_queue<Node*, vector<Node*>, comp> pq;

	for (auto pair : freq)  
	{
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	} 

	while (pq.size() != 1)  
	{
		Node* left = pq.top(); pq.pop();
		Node* right = pq.top(); pq.pop(); 
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right)); 
	}

	
	Node* root = pq.top();

	unordered_map<char, string> huffmanCode; 
	encode(root, "", huffmanCode); 

	cout << "Код символов по алгоритму Хаффмана" << endl;
	for (auto pair : huffmanCode) {
		cout << pair.first << " - " << pair.second << '\n';
	}

	string str = "";
	for (char ch : text) {
		str += huffmanCode[ch];
	}

	cout <<"\nВыходная последовательность:\n"<< str << '\n';
}



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string text = "Казанцева Татьяна Игоревна";
	cout <<"Кодируемая строка:\n"<< text << "\n\n";

	buildHuffmanTree(text);

	return 0;
}