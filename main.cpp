#include <iostream>
#include <string>
#include <vector>

#define VERMELHO "\x1b[31m"
#define VERDE "\x1b[32m"
#define ROXO "\x1b[34m"
#define AMARELO "\x1b[33m"
#define RESET "\x1b[0m"

using namespace std;

class vertice{
    private:
        string lable;
        string cor;
        int d;
        int f;
        string nome_seta1;
        string nome_seta2;
        string nome_seta3;
    public:
        vertice(string lable, string cor, int d, int f){
            set_lable(lable);
            set_cor(cor);
            set_d(d);
            set_f(f);
        }
        vertice(){}

        void set_lable(string lable){this->lable = lable;}
        void set_cor(string cor){this->cor = cor;}
        void set_d(int d){this->d = d;}
        void set_f(int f){this->f = f;}
        void set_nome_seta(string nome, int id){
            if(id == 1) nome_seta1 = nome;
            else if(id == 2) nome_seta2 = nome;
            else if(id == 3) nome_seta3 = nome;
        }

        string get_lable(){return lable;}
        string get_cor(){return cor;}
        int get_d(){return d;}
        int get_f(){return f;}
        string get_nome_seta(int id){
            if(id == 1)return nome_seta1;
            else if(id == 2)return nome_seta2;
            else if(id == 3)return nome_seta3;
        }
        int dis;
        vertice * pai;

        vertice * seta1;
        vertice * seta2;
        vertice * seta3;

        vertice * seta4;
        vertice * seta5;
        vertice * seta6;

        vertice * prox;
        vertice * prox_pilha; 
        vertice * prox_fila;
};

int cont = 0;
int tam = 0;
int tam_fila = 0;
int mark = 0;
int processo = 0;
vertice * inicio = NULL;
vertice * fim = NULL;
vertice * topo = NULL;
vertice * inicio_fila = NULL;
vertice * fim_fila = NULL;

string alfa[] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};

void cadastrar(){
    vertice * novo = new(vertice);
    novo->set_lable(alfa[tam]);
    novo->set_cor("Branco");

    novo->seta1 = NULL;novo->seta2 = NULL;novo->seta3 = NULL;
    novo->seta4 = NULL;novo->seta5 = NULL;novo->seta6 = NULL;
    novo->prox = NULL;novo->prox_pilha = NULL;novo->prox_fila = NULL;

    if(inicio == NULL){
        inicio = novo;
        fim = novo;
    }else{
        fim->prox = novo;
        fim = novo;
    }
    tam++;
    system("cls");
    cout <<VERDE<<novo->get_lable()<<" Cadastrado"<<RESET<<"\n\n";
}

void add(vertice * aux){
    vertice * novo = new(vertice);
    novo->set_lable(aux->get_lable());
    novo->set_cor("Branco");

    novo->seta1 = aux->seta4;novo->seta2 = aux->seta5;novo->seta3 = aux->seta6;
    novo->seta4 = NULL;novo->seta5 = NULL;novo->seta6 = NULL;
    novo->prox = NULL;novo->prox_pilha = NULL;

    if(topo == NULL){
        topo = novo;
    }else{
        novo->prox_pilha = topo;
        topo = novo;
    }
}

void ver(){
    vertice * aux = inicio;
    while(aux != NULL){
        cout <<aux->get_lable() << " - ";
        if(aux->seta1!=NULL)
            if(aux->get_nome_seta(1) == "Arvore")cout << VERDE"--> " << aux->seta1->get_lable()<<RESET << " - ";
            else if(aux->get_nome_seta(1) == "Retorno")cout << AMARELO"--> " << aux->seta1->get_lable()<<RESET << " - ";
            else if(aux->get_nome_seta(1) == "Avanco")cout << VERMELHO"--> " << aux->seta1->get_lable()<<RESET << " - ";
            else if(aux->get_nome_seta(1) == "Cruzamento")cout << ROXO"--> " << aux->seta1->get_lable()<<RESET << " - ";
        if(aux->seta2!=NULL)
            if(aux->get_nome_seta(2) == "Arvore")cout << VERDE"--> " << aux->seta2->get_lable()<<RESET << " - ";
            else if(aux->get_nome_seta(2) == "Retorno")cout << AMARELO"--> " << aux->seta2->get_lable()<<RESET << " - ";
            else if(aux->get_nome_seta(2) == "Avanco")cout << VERMELHO"--> " << aux->seta2->get_lable()<<RESET << " - ";
            else if(aux->get_nome_seta(2) == "Cruzamento")cout << ROXO"--> " << aux->seta2->get_lable()<<RESET << " - ";
        if(aux->seta3!=NULL)
            if(aux->get_nome_seta(3) == "Arvore")cout << VERDE"--> " << aux->seta3->get_lable()<<RESET << " - ";
            else if(aux->get_nome_seta(3) == "Retorno")cout << AMARELO"--> " << aux->seta3->get_lable()<<RESET << " - ";
            else if(aux->get_nome_seta(3) == "Avanco")cout << VERMELHO"--> " << aux->seta3->get_lable()<<RESET << " - ";
            else if(aux->get_nome_seta(3) == "Cruzamento")cout << ROXO"--> " << aux->seta3->get_lable()<<RESET << " - ";
           
        if(aux->seta1 == NULL)cout <<"\t\t\t    df: " << aux->get_d()<<"/"<<aux->get_f();
        else if(aux->seta2 == NULL)cout <<"\t\t    df: " << aux->get_d()<<"/"<<aux->get_f();
        else if(aux->seta3 == NULL)cout << "\t    df: " << aux->get_d()<<"/"<<aux->get_f();
        else cout << "df: " << aux->get_d()<<"/"<<aux->get_f();
        cout << endl;
        aux = aux->prox;
    }
    cout << VERDE "\nVERDE -> ARVORE"<<RESET<<endl;
    cout << AMARELO "AMARELO -> RETORNO"<<RESET<<endl;
    cout << VERMELHO "VERMELHO -> AVANCO"<<RESET<<endl;
    cout << ROXO "ROXO -> CRUZAMENTO"<<RESET<<endl;
    cout<<"\nMark = "<<mark<<"\n\n";
}

void ver_setas(){
    vertice * aux = inicio;
    while(aux != NULL){
        aux->set_cor("Branco");
        cout <<aux->get_lable() << " - ";
        if(aux->seta1!=NULL){
            cout << VERDE"--> " << aux->seta1->get_lable()<<RESET << " - ";
            if(aux->seta2 != NULL){
                cout << VERDE"--> " << aux->seta2->get_lable()<<RESET << " - ";
                if(aux->seta3 != NULL)
                    cout << VERDE"--> " << aux->seta3->get_lable()<<RESET << " - ";
            }
        }
        cout << endl;
        aux = aux->prox;
    }
    cout << endl;
}

void ver_pilha(){
    vertice * aux = topo;
    while(aux != NULL){
        cout <<aux->get_lable() << " - ";
        if(aux->seta1!=NULL){
            cout << VERDE"--> " << aux->seta1->get_lable()<<RESET << " - ";
            if(aux->seta2 != NULL){
                cout << VERDE"--> " << aux->seta2->get_lable()<<RESET << " - ";
                if(aux->seta3 != NULL)
                    cout << VERDE"--> " << aux->seta3->get_lable()<<RESET << " - ";
            }
        }
        cout << endl;
        aux = aux->prox_pilha;
    }
    cout << endl;
}

void deletar_tudo(){
    vertice * aux = inicio;
    while(aux != NULL){
        inicio = inicio->prox;
        free(aux);
        aux = inicio;
    }
    tam = 0;
    mark = 0;
    inicio = NULL;
}

void inverte_ligacao(string a, string x){
    vertice * aux = inicio;

    while(aux->get_lable() != x){
        aux = aux->prox;
    }
    if(aux->get_lable() == x){
        vertice * aux2 = inicio;
        while(aux2->get_lable() != a){
            aux2 = aux2->prox;
        }
        if(aux2->get_lable() == a){
            if(aux->seta4 == NULL) aux->seta4 = aux2;
            else if(aux->seta5 == NULL) aux->seta5 = aux2;
            else if(aux->seta6 == NULL) aux->seta6 = aux2;
        }
    }
}

void ligacao(string a, string x, string y, string z){
    vertice * aux = inicio;
    string b;
    if(y != "-" && x > y){b = x; x = y; y = b;}
    if(z != "-" && y > z){b = y; y = z; z = b;}
    if(y != "-" && x > y){b = x; x = y; y = b;}
    
    while(aux->get_lable() != a){
        aux = aux->prox;
    }
    if(aux->get_lable() == a){
        vertice * aux1 = inicio;
        vertice * aux2 = inicio;
        vertice * aux3 = inicio;
        if(x != "-"){
            while(aux1->get_lable() != x)
                aux1 = aux1->prox;
            if(aux1->get_lable() == x)
                aux->seta1 = aux1;
                inverte_ligacao(a, x);
            if(y != "-"){
                while(aux2->get_lable() != y)
                    aux2 = aux2->prox;
                if(aux2->get_lable() == y)
                    aux->seta2 = aux2;
                    inverte_ligacao(a, y);
                if(z != "-"){
                    while(aux3->get_lable() != z)
                        aux3 = aux3->prox;
                    if(aux3->get_lable() == z)
                        aux->seta3 = aux3;
                        inverte_ligacao(a, z);
                }
            }
        }
    }
}

void dfs_visit(vertice * aux){
    if(aux->get_cor() == "Branco"){
        aux->set_cor("Cinza");
        mark++;
        aux->set_d(mark);
        if(aux->seta1!=NULL){
            if(aux->seta1->get_cor() == "Branco"){
                aux->set_nome_seta("Arvore", 1);
                dfs_visit(aux->seta1);
            }
            else if(aux->seta1->get_cor() == "Cinza")aux->set_nome_seta("Retorno", 1);
            else if(aux->seta1->get_cor() == "Preto"){
                if(aux->get_d() < aux->seta1->get_f())
                    aux->set_nome_seta("Avanco", 1);
                else aux->set_nome_seta("Cruzamento", 1);
            }

            if(aux->seta2!=NULL){
                if(aux->seta2->get_cor() == "Branco"){
                    aux->set_nome_seta("Arvore", 2);
                    dfs_visit(aux->seta2);
                }
                else if(aux->seta2->get_cor() == "Cinza")aux->set_nome_seta("Retorno", 2);
                else if(aux->seta2->get_cor() == "Preto"){
                if(aux->get_d() < aux->seta2->get_f())
                    aux->set_nome_seta("Avanco", 2);
                else aux->set_nome_seta("Cruzamento", 2);
            }
                if(aux->seta3!=NULL){
                    if(aux->seta3->get_cor() == "Branco"){
                        aux->set_nome_seta("Arvore", 3);
                        dfs_visit(aux->seta3);
                    }
                    else if(aux->seta3->get_cor() == "Cinza")aux->set_nome_seta("Retorno", 3);
                    else if(aux->seta3->get_cor() == "Preto"){
                        if(aux->get_d() < aux->seta3->get_f())
                            aux->set_nome_seta("Avanco", 3);
                        else aux->set_nome_seta("Cruzamento", 3);
                    }
                }    
            }
        }
    }
    aux->set_cor("Preto");
    if(processo == 0)add(aux);
    mark++;
    aux->set_f(mark);
}
/*
void add_fila(vertice * aux){
    vertice * novo = new(vertice);
    novo->set_cor("Branco");
    novo->seta1 = aux->seta1;
    novo->seta2 = aux->seta2;
    novo->seta3 = aux->seta3;
    novo->prox_fila = NULL;
    
    if(inicio_fila == NULL){
        inicio_fila = novo;
        fim_fila = novo;
    }else{
        fim_fila->prox_fila = novo;
        fim_fila = novo;
    }
    tam_fila++;
}

vertice * desinfileirar(){
    vertice * aux = inicio;
    if(tam_fila == 1){
        inicio_fila = NULL;
        fim_fila = NULL;
        tam_fila--;
        return aux;
    }else{
        inicio_fila = inicio_fila->prox_fila;
        tam_fila--;
        return aux;
    }
}


void ver_filas(){
    vertice * aux = inicio_fila;
    while(aux != NULL){
        cout << aux->get_lable() << " - ";
        cout << aux->dis <<" - "<<aux->pai->get_lable()<<endl;
        aux = aux->prox_fila;
    }
}

void bfs(vertice * aux){
    vertice * aux2 = inicio;
    while(aux2 != NULL){
        aux2->set_cor("Branco");
        aux2 = aux2->prox;
    }
    aux->set_cor("Cinza"); aux->dis = 0; aux->pai = NULL;
    add_fila(aux);
    while(inicio_fila != NULL){
        aux2 = desinfileirar();
        if(aux2->seta1 != NULL){
            if(aux2->seta1->get_cor() == "Branco"){
                aux2->seta1->set_cor("Cinza");
                aux2->seta1->dis = aux2->dis + 1;
                aux2->seta1->pai = aux2;
                add_fila(aux2->seta1);
            }
            if(aux2->seta2 != NULL){
                if(aux2->seta2->get_cor() == "Branco"){
                    aux2->seta2->set_cor("Cinza");
                    aux2->seta2->dis = aux2->dis + 1;
                    aux2->seta2->pai = aux2;
                    add_fila(aux2->seta2);
                }
                if(aux2->seta3 != NULL){
                    if(aux2->seta3->get_cor() == "Branco"){
                        aux2->seta3->set_cor("Cinza");
                        aux2->seta3->dis = aux2->dis + 1;
                        aux2->seta3->pai = aux2;
                        add_fila(aux2->seta3);
                    }
                }
            }
        }
        aux2->set_cor("Preto");
    }
    ver_filas();
}
*/

void ver_novas_seta(){
    vertice * aux = inicio;
    while(aux != NULL){
        cout <<aux->get_lable() << " - ";
        if(aux->seta4!=NULL){
            cout << VERDE"--> " << aux->seta4->get_lable()<<RESET << " - ";
            if(aux->seta5 != NULL){
                cout << VERDE"--> " << aux->seta5->get_lable()<<RESET << " - ";
                if(aux->seta6 != NULL)
                    cout << VERDE"--> " << aux->seta6->get_lable()<<RESET << " - ";
            }
        }
        cout << endl;
        aux = aux->prox;
    }
    cout << endl;
}

void dfs(vertice * aux){
    while(aux != NULL){
        if(aux->get_cor() == "Branco"){
            dfs_visit(aux);
        }  
        aux = aux->prox;
    }
}


void comp(vertice * aux){
    while(aux != NULL){
        if(aux->get_cor() == "Branco"){
            cont ++;
            dfs_visit(aux);
        }  
        aux = aux->prox_pilha;
    }
}

int main(){
    int opc = 1;

    string a,x,y,z;
    while(opc != 0){
        cout << "[ 1 ] Cadastrar"<<endl;
        cout << "[ 2 ] Ligar Vertices"<<endl;
        cout << "[ 3 ] Dfs"<<endl;
        cout << "[ 4 ] Ver"<<endl;
        cout << "[ 5 ] Deletar Tudo"<<endl;
        cout << "[ 6 ] Ver Pilha"<<endl;
        cout << "[ 7 ] Componentes Conexas"<<endl;
        cout << "[ 0 ] Sair"<<endl<<">> ";
        cin >> opc;
        switch(opc){
        case 1:
            cadastrar();
            break;
        case 2:
            system("cls");
            
            cout << "Digite - caso nao tenha ligacao"<< endl;
            cout << "Vertice: ";
            cin>>a;
            cout<<"Ligar em:\n";
            cout<<"- ";
            cin>>x;
            cout<<"- ";
            cin>>y;
            cout<<"- ";
            cin>>z;
            ligacao(a,x,y,z);
            system("cls");
            cout<<VERMELHO<<"Vertices ligados "<<RESET<<endl;
            break;
        case 3:
            mark = 0;
            system("cls");
            dfs(inicio);
            ver();
            break;
        case 4:
            system("cls");
            ver_setas();
            break;
        case 5:
            system("cls");
            deletar_tudo();
            break;
        case 6:
            ver_pilha();
            break;
        case 7:
            processo = 1;
            comp(topo);
            cout << cont/2 << endl;
        case 8:
            break;
        default:
            break;
        }
    }
    deletar_tudo();
    return 0;
}