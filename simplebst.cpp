#ifndef __SIMPLEBST_H__
#define __SIMPLEBST_H__

#include<iostream>
#include<vector>
#include<functional>
#include<fstream>
#include<string.h>

using namespace std;

class SimpleBST {
   
   struct Node{
       
       float elem;
       Node* iz;//left
       Node* der;//right
       
       Node(float elem) : elem(elem), iz(nullptr), der(nullptr){}
   };

   
   Node* raiz;//root

public:
   
   SimpleBST(): raiz(nullptr){}

   ~SimpleBST(){
         clear(raiz);
   }
   
   void agregar(float elem){
        agregar(raiz,elem);
   }

   bool buscar(float elem){
        return buscar(raiz,elem);
   }

   void preorder(function<void(float)> proc){//ese lambda va a recibir un float
        preorder(raiz,proc);
   }
  
   void postorder(function<void(float)> proc){
        postorder(raiz,proc);
   }

    void inorder(function<void(float)> proc){
         inorder(raiz,proc);
    }
    //ESTO ES SOLO PARA DIBUJAR EL ARBOL 
    void view(string filename){//metodo para dibujar un arbol
         if (raiz!=nullptr){
             ofstream file(filename);
             int cont=0;
             file<<"Digraph G {\n";
             generate(raiz,file,cont);
             file<<"}";
         }
    }
private:

   void clear(Node* node){
       if (raiz!=nullptr){
           clear(node->iz);
           clear(node->der);
           delete node;
           node = nullptr; //solo por si acaso, en realidad no debería ir esta linea de código
       }   
   }

   void agregar(Node*& node, float elem){
       if (node==nullptr){
           node = new Node(elem);
       }
       else if (elem<node->elem){
           agregar(node->iz, elem);
       }
       else if (elem>node->elem){//todos los repetidos irían a la derecha, si elimino todo esta linea, excepto el 'else'.
           agregar(node->der, elem);
       }
   }

   bool buscar(Node* node, float elem){
        if (node!=nullptr){
            if (elem==node->elem){
                return true;
            }
            else if (elem<node->elem){
                return buscar(node->iz,elem);
            }
            else{
                return buscar(node->der,elem);
            }
        }
        return false;
   }

       
   void preorder(Node *node,function<void(float)>proc){
        if (node!=nullptr){
            proc(node->elem);
            preorder(node->iz,proc);
            preorder(node->der,proc);
        }  
   }

   void postorder(Node* node, function<void(float)>proc){
        if (node!=nullptr){
            postorder(node->iz,proc);
            postorder(node->der,proc);
            proc(node->elem);
        }        
   }

   void inorder(Node* node, function<void(float)>proc){
        if (node!=nullptr) {
            inorder(node->iz,proc);
            proc(node->elem);
            inorder(node->der,proc);
        }
   }
   void generate(Node *node, ofstream& file,int &cont){
        if (node->iz!=nullptr){
            file <<node->elem <<"->"<<node->iz->elem<<endl;
            generate(node->iz, file,cont);
        }else{
            file <<"null"<<cont<<" [shape=point]\n";
            file<<node->elem<<"->null"<<cont<<endl;
            ++cont;
        }
         
        if (node->der!=nullptr){
            
            file <<node->elem <<"->"<<node->der->elem<<endl;
            
            generate(node->der, file,cont);
        }else{
            
            file <<"null"<<cont<<" [shape=point]\n";
       
            file<<node->elem<<"->null"<<cont<<endl;
         
            ++cont;
        }
    }
};

int main(){
    SimpleBST *bst = new SimpleBST();
    vector<int> v={34, 3,1,67,69,23,4,79,43,20,14,54,12,8,99,15,62,26};
    for (auto num:v){
         bst->agregar(num);
    }

    auto prin=[](float x) {cout << x <<" "; };
    
    bst->postorder(prin); cout<<endl;
    bst->preorder(prin); cout<<endl;
    bst->inorder(prin); cout<<endl;
    
    cout<<bst->buscar(100)<<endl;
    cout<<bst->buscar(4)<<endl;
    bst->view("simplebst.dot");//para mostrar el arbol de forma visual, despues de correrlo, en la termina escribir !cat simplebst.dot
    delete bst;
    return 0;
}


#endif
