#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <list>
#include <array>


using std::string;
using std::cout;
using std::endl;
using std::list;
using std::array;
using std::srand;
using std::rand;
using std::time;


/*
 * Classe que implementa uma tabela Hash. A classe recebe como parâmetros
 * do template as classes das chaves e dos valores
 *
 * Ex: HashTable<string, string> hash_table;
 *
 * Nesse exemplo ambos, chave e valor, são do tipo string.
 *
 */
template<class KeyType, class ValueType>
class HashTable {
 private:
    /* Struct que representa cada entrada da tabela */
    struct Entry {
        int index;
        KeyType key;
        ValueType value;
    };

    /* Número atual de itens dentro da tabela */
    unsigned int entries_n = 0;

    /* Tamanho total da tabela a ser alocada */
    static const int MAX_SIZE = 100;

    /* Um item do tipo Entry vazio. Utilizado como valor default de itens */
    struct Entry DEFAULT_VALUE;

    /* Tabela de ites do tipo Entry com tamanho máximo permitido */
    array<list<Entry>, MAX_SIZE> table;

    /* Método privado para uso exclusivo de debbuging */
    void debbug(struct Entry* entry)
    {
        cout << "[" << entry->index << "]('" << entry->key
             << "', '" << entry->value << "')" << endl;
    }

    /**
    * Método da classe que gera um inteiro randômico
    * entre 0 e MAX_SIZE.
    */
    int randInt()
    {
         return (rand() % MAX_SIZE);
    }

    /*
     * O tão importante método de Hashing
     */
    int hash(KeyType key)
    {
        int counter = 0;

        /* Vamos usar o índice de cada caracter como multiplicador da letra.
         * Palavras que possuem as mesmas letras irão gerar colisão. Para tal
         * iremos considerar a posição da letra dentro da string
         */
        int i = 1;
        for (char& c : key) {
            /* Multiplica pelo índice dentro da string */
            counter += i++ * static_cast<int>(c);
        }

        /* Calculando o modulo do tamanho do array garantimos um índice dentro
         * do range permitido
         */
        auto index = static_cast<int>(counter % MAX_SIZE);

        return index;
    }

 public:

    /*
     * Construtor da tabela Hash
     */
    HashTable()
    {
        this->DEFAULT_VALUE.index = -1;
        /* gera semente aleatória para o método std::rand() */
        srand(time(nullptr));
    }

    /*
     * Busca por uma chave dentro da tabela utilizando a função hash
     */
    ValueType* LookUp(KeyType key)
    {
        int index = this->hash(key);

        /* Caso não encontrado vamos retornar um valor vazio ou nulo */
        if (this->table[index].size() == 0) {
            this->debbug(&this->DEFAULT_VALUE);
            return new ValueType();
        } else {

            /* Se encontrarmos a chave, retornamos seu valor */
            for (auto& e : this->table[index]) {
                if (e.key == key) {
                    this->debbug(&e);
                    return &e.value;
                }
            }

            this->debbug(&this->DEFAULT_VALUE);
            return new ValueType();
        }
    }

    /*
     * Atualiza o valor de uma chave
     */
    bool Update(KeyType key, ValueType value)
    {
        int index = this->hash(key);

        /* Caso não encontrado vamos retornar false */
        if (this->table[index].size() == 0) {
            return false;
        } else {

            /* Se encontrarmos a chave, atualizamos seu valor */
            for (auto& e : this->table[index]) {
                if (e.key == key) {
                    e.value = value;
                    this->debbug(&e);
                    return true;
                }
            }
        }
        return false;
    }

    /*
     * Insere uma nova chave com um valor dentro da tabela hash
     */
    bool Put(KeyType key, ValueType value)
    {
        int index = this->hash(key);

        struct Entry* entry = new Entry();
        entry->index = index;
        entry->key = key;
        entry->value = value;

        /* Verifica se já existe a chave na lista */
        for (auto& e : this->table[index]) {
            if (e.key == key) {
                cout << "Key '" << key << "' already exist" << endl;
                return false;
            }
        }

        /* Caso contrário inserimos a nova chave e seu valor */
        this->table[index].push_front(*entry);
        this->debbug(entry);
        this->entries_n++;
        return true;
    }

    /*
     * Remove um item de dentro tabela através de sua chave
     */
    bool Del(KeyType key)
    {
        int index = this->hash(key);
        if (index == this->DEFAULT_VALUE.index) {
            return false;
        }

        /* Cria-se um iterator e percorre-se a lista em busca da chave */
        auto i = this->table[index].begin();
        for (; i != this->table[index].end(); ++i) {

            if (i->key == key) {
                this->debbug(&*i);
                this->table[index].erase(i);
                this->entries_n--;
                return true;
            }
        }
        return false;
    }
};