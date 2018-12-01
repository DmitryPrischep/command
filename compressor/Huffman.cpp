#include <string>
#include <map>
#include <list>
#include <vector>

#include <iostream>
using namespace std;

class Decoder {
    struct Node {
        unsigned count; char ch; Node* l; Node* r;
    public:
        Node(unsigned q, char c, Node* ls, Node* rs) : count(q), ch(c), l(ls), r(rs) {}
        Node(unsigned q, char c) : Node(q, c, nullptr, nullptr) {}
        Node(Node* ls, Node* rs) : Node(ls->count + rs->count, '\0', ls, rs) {}
        ~Node() { delete l; delete r; }
        friend ostream& operator<<(ostream& os, const Node& node) { return os << node.count << ": " << node.ch;}
    };

    string raw_string{};
    string encoded_string{};

    list<Node*> tree{};

    map<char, vector<int>> symbols{};
    map<char, unsigned> frequency{};

    vector<int> code{};

public:
    Decoder(const string& str) : raw_string(str) { initialize(); }

    size_t countSymbols() const { return symbols.size(); }
    size_t encodedStringLength() const { return encoded_string.size(); }
    
    void printCodes() const {
        for (const auto& pr : symbols) {
            cout << pr.first << ": ";
            for (const auto& code : pr.second)
                cout << code;
            cout << endl;
        }
    }
    const string& encodedString() const { return encoded_string; }

protected:
    void initialize() {
        for (auto c : raw_string)
            ++frequency[c];

        for (const auto& pr : frequency)
            tree.push_back(new Node(pr.second, pr.first));

        build_tree();
        encode_symbols(symbols, code, tree.front());
        encode_string();
    }

    void build_tree() {
        if (tree.size() == 1) {
            code.push_back(0);
        }

        while (tree.size() != 1) {
            tree.sort([](const Node* l, const Node* r) { return l->count < r->count; });

            Node* sonLeft = tree.front();
            tree.pop_front();
            Node* sonRight = tree.front();
            tree.pop_front();

            tree.push_back(new Node(sonLeft, sonRight));
        }
    }
    void encode_symbols(map<char, vector<int>>& sym_code, vector<int>& code, Node* root) {
        if (root->l) {
            code.push_back(0);
            encode_symbols(sym_code, code, root->l);
        }

        if (root->r) {
            code.push_back(1);
            encode_symbols(sym_code, code, root->r);
        }

        if (root->l == nullptr && root->r == nullptr) {
            sym_code.insert({ root->ch, code });
        }

        if (!code.empty())
            code.pop_back();
    }

    void encode_string() {
        for (const auto& ch : raw_string) {
            auto it = symbols.lower_bound(ch);
            if (it != symbols.end())
                for (const auto& code : it->second)
                    encoded_string += to_string(code);
        }
    }
};

int main()
{
    string rawstring{};
    cin >> rawstring;

    Decoder decode(rawstring);

    cout << decode.countSymbols() << ' ' << decode.encodedStringLength() << endl;
    decode.printCodes();
    cout << decode.encodedString() << endl;

    return 0;
}