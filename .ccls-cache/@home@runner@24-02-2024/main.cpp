#include <iostream>
#include <stdlib.h>

using namespace std;

class Vertex {
public:
  Vertex() { next = nullptr; }
  float getValue() { return value; }
  void setValue(float value) { this->value = value; }
  Vertex *getNext() { return next; }
  void setNext(Vertex *next) { this->next = next; }

private:
  Vertex *next;
  float value;
};

class List {
public:
  List();
  ~List();
  void append(float value);
  void insertAt(int pos, float value);
  void insertAtFirst(float value);
  void removeFirst();
  void removeAt(int pos);
  void removeValue(float value);
  void removeLast();
  void print();

private:
  Vertex *head, *tail;
};

class Stack {
public:
  Stack();
  void push(float value);
  void pop();
  void getTop();
  void print();

private:
  Vertex *top;
};

class Menu {
public:
  Menu();
  void showMenu();
  int getOption() { return option; };
  void setOption(int opt) { option = opt; }

private:
  int option;
};

List::List() {
  head = nullptr;
  tail = nullptr;
}

List::~List() {}

void List::insertAtFirst(float value) {
  Vertex *vtx = new Vertex();
  vtx->setValue(value);
  if (head != nullptr) {
    vtx->setNext(head);
    head = vtx;
  } else {
    head = vtx;
    tail = vtx;
  }
}

void List::append(float value) {
  if (head != nullptr) {
    Vertex *vtx = new Vertex();
    vtx->setValue(value);
    tail->setNext(vtx);
    tail = vtx;
  } else {
    insertAtFirst(value);
  }
}

void List::insertAt(int pos, float value) {
  if (head != nullptr && pos > 1) {
    Vertex *post = head;
    Vertex *pre = new Vertex();
    Vertex *vtx = new Vertex();
    vtx->setValue(value);
    for (int i = 1; i <= pos - 1; i++) {
      if (post == tail && i == pos - 1) {
        append(value);
        return;
      }
      if (post == nullptr) {
        cout
            << "Esta posicion no existe, el elemento sera ingresado al final..."
            << endl;
        append(value);
        return;
      }
      pre = post;
      post = post->getNext();
    }
    vtx->setNext(post);
    pre->setNext(vtx);
  } else {
    if (pos < 1) {
      cout << "La posicion ingresada no es valida, ingrese otra posicion..."
           << endl;
      return;
    }
    insertAtFirst(value);
  }
}

void List::removeFirst() {
  Vertex *vtx = head;
  if (head != nullptr) {
    if (head == tail) {
      head = nullptr;
      tail = nullptr;
      cout << "0" << endl;
    } else {
      head = head->getNext();
      delete vtx;
    }
  } else {
    cout << "La lista no tiene elementos..." << endl;
  }
}

void List::removeLast() {
  if (head != nullptr) {
    if (head == tail) {
      removeFirst();
    } else {
      Vertex *pre = head;
      while (pre->getNext() != tail) {
        pre = pre->getNext();
      }
      pre->setNext(nullptr);
      delete tail;
      tail = pre;
    }
  } else {
    cout << "La lista no tiene elementos..." << endl;
  }
}

void List::removeAt(int pos) {
  if (head != nullptr && pos >= 1) {
    if (pos == 1) {
      removeFirst();
    } else {
      Vertex *pre = head;
      for (int i = 1; i < pos - 1; i++) {
        pre = pre->getNext();
        if (pre == nullptr) {
          cout << "La posicion ingresada no es valida, no se puede eliminar..."
               << endl;
          return;
        }
      }
      Vertex *del = pre->getNext();
      Vertex *aft = del->getNext();
      pre->setNext(aft);
      if (del == tail) {
        tail = pre;
      }
      delete del;
    }
  } else {
    cout << "La lista esta vacia o la posicion no es valida" << endl;
  }
}

void List::removeValue(float value) {
  if (head != nullptr) {
    if (head->getValue() == value) {
      removeFirst();
      return;
    }
    if (head == tail && head->getValue() != value) {
      cout << "El valor no se encuentra en la lista..." << endl;
      return;
    }
    Vertex *pre = head;
    while (pre->getNext()->getValue() != value) {
      pre = pre->getNext();
      if (pre->getNext() == nullptr) {
        cout << "El valor ingresado no se encuentra en la lista..." << endl;
        return;
      }
    }

    Vertex *del = pre->getNext();
    Vertex *aft = del->getNext();
    pre->setNext(aft);
    if (del == tail) {
      tail = pre;
    }
    delete del;
  } else {
    cout << "La lista esta vacia" << endl;
  }
}

void List::print() {
  if (head != nullptr) {
    Vertex *vtx = head;
    while (vtx != nullptr) {
      cout << vtx->getValue();
      vtx = vtx->getNext();
      if (vtx != nullptr) {
        cout << "  ->  ";
      }
    }
    cout << "\nHead = " << head->getValue() << "\nTail = " << tail->getValue()
         << endl;
  } else {
    cout << "La lista esta vacia" << endl;
  }
}

Stack::Stack(){
  top = nullptr;
};

void Stack::print() {
  if (top != nullptr) {
    Vertex *vtx = top;
    while (vtx != nullptr) {
      cout << vtx->getValue();
      vtx = vtx->getNext();
      if (vtx != nullptr) {
        cout << " -> ";
      }
    }
    cout << "\nTop = " << top->getValue() << endl;
  } else {
    cout << "La pila esta vacia" << endl;
  }
}


void Stack::pop(){
  if(top != nullptr){
    Vertex *vtx = top;
    top = top->getNext();
    delete(vtx);    
  }else{
    cout<< "La pila esta vacia" << endl;
  }
}

void Stack::push(float value){
  Vertex *vtx = new Vertex();
  vtx->setValue(value);
  if (top != nullptr) {
    vtx->setNext(top);
    top = vtx;
  } else {
    top = vtx;
  }
}

void Stack::getTop(){
  if(top != nullptr){
    cout << "Top = " << top->getValue() << endl;
  }else{
    cout<< "La pila esta vacia " << endl;
  }
}

Menu::Menu(){};

void Menu::showMenu() {
  List *list = new List();
  Stack *stack = new Stack();

  do {
    float value;
    int pos;
    cout << "\n----------------------------------\n" << endl;
    cout << "1. Insertar al inicio" << endl;
    cout << "2. Insertar al final" << endl;
    cout << "3. Insertar en posicion" << endl;
    cout << "4. Eliminar al inicio" << endl;
    cout << "5. Eliminar al final" << endl;
    cout << "6. Eliminar en posicion" << endl;
    cout << "7. Eliminar por valor" << endl;
    cout << "8. Imprimir lista" << endl;
    cout << "9. Insertar al inicio de la pila" << endl;
    cout << "10. Eliminar al inicio de la pila" << endl;
    cout << "11. Top" << endl;
    cout << "12. Imprimir pila" << endl;
    cout << "13. Salir" << endl;
    cout << "\n----------------------------------\n" << endl;
    cout << "Ingrese una opcion: ";
    cin >> option;
    cout << "\n----------------------------------\n" << endl;
    switch (option) {
    case 1:

      cout << "Ingrese el valor a insertar: ";
      cin >> value;
      list->insertAtFirst(value);
      break;
    case 2:
      cout << "Ingrese el valor a insertar: ";
      cin >> value;
      list->append(value);
      break;
    case 3:
      cout << "Ingrese la posicion a insertar: ";
      cin >> pos;
      cout << "Ingrese el valor a insertar: ";
      cin >> value;
      list->insertAt(pos, value);
      break;
    case 4:
      list->removeFirst();
      break;
    case 5:
      list->removeLast();
      break;
    case 6:
      cout << "Ingrese la posicion a eliminar: ";
      cin >> pos;
      list->removeAt(pos);
      break;
    case 7:
      cout << "Ingrese el valor a eliminar: ";
      cin >> value;
      list->removeValue(value);
      break;
    case 8:
      list->print();
      break;
    case 9:
      cout << "Ingrese el valor a insertar: ";
      cin >> value;
      stack->push(float (value));
      break;
    case 10:
      stack->pop();
      break;
    case 11:
      stack->getTop();
      break;
    case 12: 
      stack->print();
      break;
    case 13:
      cout << "Saliendo..." << endl;
      return;
      break;
    default:
      cout << "Opcion no valida, intente de nuevo..." << endl;
      break;
    }
    option = 0;
  } while (option != 13);
}

int main() {
  Menu *menu = new Menu();
  menu->showMenu();
  /*Stack *stack = new Stack();
  stack->push(1);
  stack->push(2);
  stack->push(3);
  stack->pop();
  stack->print();*/
  return 0;
}
