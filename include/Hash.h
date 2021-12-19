#include <list>

using namespace std;

class Hash
{
private:
    int balde;
    list<int> *table;

public:
    Hash(int v);
    void insert(string x);
    void del(int key);
    int hashfunction(string x) { return (static_cast<int>(x) % balde); }
    void displayhash();
};