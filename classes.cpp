#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Comparable {
  public:
    Comparable(){};
    virtual int compareTo(Comparable *cmp) = 0;
    int id;
};

class Carro: public Comparable {

  public:
    Carro():Comparable(){};
    int compareTo(Comparable *cmp) {
      return (this->id == cmp->id);
    }
};

class Collections{

  public:
    static void sort(vector<Comparable*> v){

      v[0]->id = 122;
      cout << "sort" << '\n';
      
    }
    static int search(vector<Comparable*> v, Comparable *c){
      
      for(int i = 0; i < v.size(); i++){

        cout << "v[i]: " << v[i]->id << '\n';
        if(v[i]->id == c->id) return i;

      }

      return -1;

    }

};

class Animal: public Comparable {
  protected:
    string nome;
    int idade;
  public:
    Animal(string nome, int idade):Comparable(){
      this->nome = nome;
      this->idade = idade;
    };
    virtual void correr() = 0;
    virtual void emitirSom() = 0;
    int compareTo(Comparable *cmp) {
      return 2;
    }
    string toString(){

      string str;
      str += "Nome do animal: ";
      str += nome;
      str += " | Idade: ";
      str += "8";

      return str;
    }
};

class Cachorro: public Animal {
  public:
    Cachorro(string nome, int idade):Animal(nome, idade){};
    void correr(){
      cout << "correr";
    }

    void emitirSom(){
      cout << "auau";
    }
};