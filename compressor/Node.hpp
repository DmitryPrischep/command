// структура узла для дерева Хаффмана
struct Node {
	char byte;
	int number;
	int weight;

	Node* parent;
	Node* left;
	Node* right;

	Node(char _byte, int _number, int _weight = 0, Node* _parent = nullptr, Node* _left = nullptr, Node* _right = nullptr) :
			byte(_byte), 
			number(_number),
			weight(_weight), 
			parent(_parent),
			left(_left),
			right(_right)
	{}
	~Node() {
		delete left;
		delete right;
	}
};