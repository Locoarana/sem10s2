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

    
    
    void eliminar(float elem){

         remove(elem);
    }
    
    void mayor(){

         max();
    }
    
    void menor(){
         min();
    }

    void invertir(float elem){
         invertir(raiz,elem);
    } 
    
    void suma(){
        int s = sum(raiz);
        cout<<"\nLa suma total es: "<<s<<endl;
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

    void remove(float v){
         //Encontrar elemento a eliminar
         Node* aux=raiz;
         Node* auxpadre=nullptr; //el padre del elemento q queremos eliminar
         bool hijoiz; // ¿aux es hijo izquierdo del padre?.
         while (aux!=nullptr){
               if (v==aux->elem){
                   break;
               }
               else if (v<aux->elem){
                   auxpadre=aux;
                   hijoiz=true;
                   aux = aux->iz;
               }else {
                   auxpadre=aux;
                   hijoiz=false;
                   aux=aux->der;
               }

         }
         if (aux==nullptr) return; //no se encontró el elemento a eliminar.
        
         //Ahora eliminamos en caso no tenga hijo izquierdo

         if (aux->iz==nullptr){//no tiene hijo izquierdo, sube el derecho.
             if (auxpadre==nullptr){ //el elemento a eliminar es la raiz
                 raiz=aux->der;
             }else if (hijoiz){
                 auxpadre->iz=aux->der;   //el elemento a eliminar es el izquierdo de auxpadre
             }else {            //es el derecho de parent
                 auxpadre->der=aux->der;
             }
             delete aux;
             return;
         }
         //En caso si exista hijo izquierdo, buscamos al mayor de dicho sub árbol.
         Node* aux2 = aux->iz;
         Node* aux2padre=aux;
         hijoiz=true;
         while (aux2->der!=nullptr){
             aux2padre=aux;
             hijoiz=false;
	     aux2 =aux2->der;
         }
         aux->elem = aux2->elem;//reemplezamos el elemento.
         if (hijoiz){
             aux2padre->iz=aux2->iz;
         }else {
             aux2padre->der=aux2->der;
         }
         delete aux2;
    }

    void max(){ 
         Node* Aux = raiz;
         while(Aux->der!=nullptr){
              Aux=Aux->der;
         }
         cout<<"El maximo valor es: "<<Aux->elem<<endl;
    }
    
    void min(){
         Node* Aux=raiz;
         while(Aux->iz!=nullptr){
              Aux=Aux->iz;
         }
         
         cout<<"El mínimo valor es: "<<Aux->elem<<endl;
    }

    void invertir(Node*& node, float elem){
      if (node==nullptr){
          node = new Node(elem);
      }else if (elem<node->elem){
          invertir(node->der, elem);
      }
      else if (elem>node->elem){
          invertir(node->iz, elem);
      }  
    }    
    
        
    float sum(Node *node){
        
        if (node!=nullptr){
           float centro=node->elem;
           float izq=sum(node->iz);
           float der=sum(node->der);
           return centro+izq+der;
        }
        return 0;
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
    bst->eliminar(54);
    
    cout<<"--------------------------------------------------------------------"<<endl;
    bst->inorder(prin);cout<<endl;
    bst->mayor();
    bst->menor();
    cout<<"-----------------Invertido------------------------------------------"<<endl;
    SimpleBST *bst2=new SimpleBST();
    vector<int> v2={34, 3,1,67,69,23,4,79,43,20,14,54,12,8,99,15,62,26};
    for (auto num : v2){
         bst2->invertir(num);
    }
    bst2->postorder(prin); cout<<endl;
    bst2->preorder(prin); cout<<endl;
    bst2->inorder(prin); cout<<endl;

    bst2->suma();
    delete bst;
    delete bst2;
    return 0;
}


#endif
