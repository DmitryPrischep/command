//#include <cstdef>

typedef std::uint_fast8_t byte_t;

//A bit type declaration. Yep, I know it's not a really bit.
//This type was introduced specially to increase code readability.
typedef std::uint_fast8_t bit_t;


struct Node {
	byte_t byte;
	int number;
	int weight;

	Node* parent;
	Node* left;
	Node* right;

	Node(byte_t _byte,
		int _number,
		int _weight = 0, 
		Node* _parent = nullptr, 
		Node* _left = nullptr, 
		Node* _right = nullptr) :
			byte(_byte),
			number(_number),
			weight(_weight),
			parent(_parent),
			left(_left),
			right(_right)
	{}
};