
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <string> 

using namespace std;
using namespace cv;

struct nodo{
    int id, X,Y, estado, anillo;
    nodo *ant;
    nodo *sig;
    nodo *adentro;
    nodo *afuera;
};
//Inicio de nodos Principales
nodo *pAnillo1 = NULL;
nodo *pAnillo2 = NULL;
nodo *pAnillo3 = NULL;
nodo *pAnillo4 = NULL;
nodo *pAnillo5 = NULL;
nodo *pAnillo6 = NULL;

//Declaraciones de openCv
Scalar negro = Scalar(210, 207, 202);
Scalar blanco = Scalar(94, 73, 52);

Mat ventana(900, 1700, CV_8UC3, negro);
int Danillo=1;

//prototipo de una funcion
void MouseI(int unax, int unay);

class the_right_moves{
private:
    nodo *inicio;
    
public:
    the_right_moves(void);
    void crearAnillo(nodo **, int, int,int,int);   
    void llenar_tablero(void);
    void dibujar_tableroI(void);
    void ver_punteros(void);
    void limpiar_tablero(void);
    void eliminarTodosElementosListaSimpleRecursiva(nodo *);
    
};
the_right_moves::the_right_moves(void)
{

    // Primero se crean los cuatro anillos
	// doblemente enlazados:
    //(cabeza, #deNodos,#de inicio, radio del circulo)
	crearAnillo(&pAnillo1, 16,1,375,1);
	crearAnillo(&pAnillo2, 16,17,300,2);
	crearAnillo(&pAnillo3, 16,33,225,3);
	crearAnillo(&pAnillo4, 8,49,150,4);
        crearAnillo(&pAnillo5,2,57,75,5);
        crearAnillo(&pAnillo6,2,59,75,6);
        
	// Luego se unen los anillos entre s?, con
	// dobles enlaces, de acuerdo a como se unen
	// los c?rculos en el tablero del juego:
        
	nodo *s1 = pAnillo1;
	nodo *s2 = pAnillo2;
        
	// Este lazo une el anillo m?s externo con el segundo
	// por medio de 4 enlaces:
	for (int i = 1; i <= 4; i++) {
                s1->adentro = s2;
                s2->afuera = s1;
                
                s1 = s1->sig->sig->sig->sig;
                s2 = s2->sig->sig->sig->sig;
        //Dibuja Lineas :v
                Point inicio(s1->X,s1->Y);
                Point fin(s2->X,s2->Y);
                line(ventana,inicio,fin, blanco,2);           
	}  
	// Este lazo une el segundo anillo con el tercero
	// por medio de 16 enlaces:
	s2 = pAnillo2;
	nodo *s3 = pAnillo3;
	for (int i = 1; i <= 16; i++) {
		s2->adentro = s3;
		s3->afuera = s2;
		s2 = s2->sig;
		s3 = s3->sig;
        //Dibuja Lineas :v       
                Point inicio(s2->X,s2->Y);
                Point fin(s3->X,s3->Y);
                line(ventana,inicio,fin, blanco,2);            
	}
	// Este lazo une el tercer anillo con el cuarto
	// por medio de 8 enlaces:
	s3 = pAnillo3;
	nodo *s4 = pAnillo4;
	for (int i = 1; i <= 8; i++) {
		s3->adentro = s4;
		s4->afuera = s3;
		s3 = s3->sig->sig;
		s4 = s4->sig;
         //Dibuja Lineas :v       
                Point inicio(s3->X,s3->Y);
                Point fin(s4->X,s4->Y);
                line(ventana,inicio,fin, blanco,2);                
	}
        
        s4 = pAnillo4;
	nodo *s5 = pAnillo5;
        //Dibuja Lineas :v
        Point inicioH(s5->X,s5->Y);
        Point finH(s5->sig->X,s5->sig->Y);
        line(ventana,inicioH,finH, blanco,2);
        
	for (int i = 1; i <= 2; i++) {
		s4->adentro = s5;
		s5->afuera = s4;
		s4 = s4->sig->sig->sig->sig;
		s5 = s5->sig;
                //Dibuja Lineas :v
                Point inicio(s4->X,s4->Y);
                Point fin(s5->X,s5->Y);
                line(ventana,inicio,fin, blanco,2);
	}
        
        s4 = pAnillo4->sig->sig;
	nodo *s6 = pAnillo6;
        //Dibuja Lineas :v
        Point inicioV(s6->X,s6->Y);
        Point finV(s6->sig->X,s6->sig->Y);
        line(ventana,inicioV,finV, blanco,2);
        
	for (int i = 1; i <= 2; i++) {
		s4->adentro = s6;
		s6->afuera = s4;
		s4 = s4->sig->sig->sig->sig;
		s6 = s6->sig;
                //Dibuja Lineas :v
                Point inicio(s4->X,s4->Y);
                Point fin(s6->X,s6->Y);
                line(ventana,inicio,fin, blanco,2);
                
                
	}        
        line(ventana,Point(900,0),Point(900,900), blanco,3);
	// Finalmente se hace que pInicio sea el
	// puntero base de la estructura ya armada:
	inicio = pAnillo1;
        llenar_tablero();
        dibujar_tableroI();
    
}
void the_right_moves::crearAnillo(nodo **p, int numNodos, int inicio,int radio, int unAnillo)
{
    float u=0;
    
        Point centro = Point(ventana.rows /2, ventana.cols /3.75);
        
        if(Danillo<5){     
            Danillo+=1;
            
        }
        else{
            if(Danillo==5){
            Danillo+=1;
        }
            else{
                if(Danillo==6){
                u=3.14159/2;
                cout<<""<<u;
                Danillo+=1;          
                }
            }
        
        }              
        float angulo = 2 * 3.14159 / numNodos;	
        *p = new nodo;
	nodo *nuevo;
	nodo *s = *p;
 
        for (int i = 2; i <= numNodos; i++) {
                
                nuevo = new nodo;
                s->id = inicio;
                s->X = centro.x + radio*cos(u);
                s->Y = centro.y + radio*sin(u);
                s->estado = 0;
		s->anillo = unAnillo;

		u +=angulo;
          
		s->sig = nuevo;
		s->sig->ant = s;
		s = s->sig;
                
        inicio = inicio+1;
	}
        
        s->id = inicio;
        s->X = centro.x + radio*cos(u);
        s->Y = centro.y + radio*sin(u);
        s->estado = 0;
 	s->anillo = unAnillo;
	s->sig = *p;
	s->sig->ant = s;
        u=0;       
}
void the_right_moves::llenar_tablero(){
    Danillo =0;
    int judaror=1;
    nodo *p =inicio->sig;
    nodo *s =inicio->adentro->sig;
    nodo *q =inicio->adentro->adentro->sig;
    
    if(p!=NULL && q!=NULL && s!=NULL){
        
        do{
            p->estado = 2;
            s->estado = 2;
            q->estado = 2;
            
            p = p -> sig;
            s = s -> sig;
            q = q -> sig;
            judaror+=1;
                    
        }while(judaror<4);
        
        p = p -> sig;
        s = s -> sig;
        q = q -> sig;
        judaror=1;
        
        do{
            p->estado = 1;
            s->estado = 1;
            q->estado = 1;
            
            p = p -> sig;
            s = s -> sig;
            q = q -> sig;
            judaror+=1;
                    
        }while(judaror<4);
        
        p = p -> sig;
        s = s -> sig;
        q = q -> sig;
        judaror=1;
        
        do{
            p->estado = 2;
            s->estado = 2;
            q->estado = 2;
            
            p = p -> sig;
            s = s -> sig;
            q = q -> sig;
            judaror+=1;
                    
        }while(judaror<4);
        
        p = p -> sig;
        s = s -> sig;
        q = q -> sig;
        judaror=1;
        
        do{
            p->estado = 1;
            s->estado = 1;
            q->estado = 1;
            
            p = p -> sig;
            s = s -> sig;
            q = q -> sig;
            judaror+=1;
                    
        }while(judaror<4);
        
        p = p -> sig;
        s = s -> sig;
        q = q -> sig;
        judaror=1;
           
       } 
    else{
	cout << "Lista vacia" << '\n';
    }
    
}
void the_right_moves::dibujar_tableroI(){
    
    float u=0;
    
        Point centro = Point(ventana.rows /2, ventana.cols /3.75);
        
            circle(ventana, centro, 375, blanco, 2);
            circle(ventana, centro, 300, blanco, 2);
            circle(ventana, centro, 225, blanco, 2);
            circle(ventana, centro, 150, blanco, 2);
         
            nodo *o =pAnillo1;
            nodo *p =pAnillo2;
            nodo *q =pAnillo3;
            nodo *r =pAnillo4;
            nodo *s =pAnillo5;
            nodo *t =pAnillo6;
            
             if (o!=NULL && p!=NULL && q!=NULL && r!=NULL && s!=NULL && t!=NULL) {
                do {
                
		Point casilla = Point(o->X, o->Y);
		circle(ventana, casilla, 20, blanco, CV_FILLED);
                if(o->estado==1){
                    circle(ventana, casilla, 15, Scalar(0,0,255), CV_FILLED);
                }
                else{
                    if(o->estado==2){
                       circle(ventana, casilla, 15, Scalar(255,0,0), CV_FILLED); 
                    }
                }
                
                putText(ventana,to_string(o->id),casilla,FONT_HERSHEY_SIMPLEX,0.5,Scalar(255,255,255));
                
                o = o->sig;
                }
                while(o!=pAnillo1);
                do {
                
		Point casilla = Point(p->X, p->Y);
		circle(ventana, casilla, 20, blanco, CV_FILLED);
                if(p->estado==1){
                    circle(ventana, casilla, 15, Scalar(0,0,255), CV_FILLED);
                }
                else{
                    if(p->estado==2){
                       circle(ventana, casilla, 15, Scalar(255,0,0), CV_FILLED); 
                    }
                }
                putText(ventana,to_string(p->id),casilla,FONT_HERSHEY_SIMPLEX,0.5,Scalar(255,255,255));
                
                p = p->sig;
                }
                while(p!=pAnillo2);
                do {
                
		Point casilla = Point(q->X, q->Y);
		circle(ventana, casilla, 20, blanco, CV_FILLED);
                if(q->estado==1){
                    circle(ventana, casilla, 15, Scalar(0,0,255), CV_FILLED);
                }
                else{
                    if(q->estado==2){
                       circle(ventana, casilla, 15, Scalar(255,0,0), CV_FILLED); 
                    }
                }
                putText(ventana,to_string(q->id),casilla,FONT_HERSHEY_SIMPLEX,0.5,Scalar(255,255,255));
                
                q = q->sig;
                }
                while(q!=pAnillo3);
                do {
                
		Point casilla = Point(r->X, r->Y);
		circle(ventana, casilla, 20, blanco, CV_FILLED);
                if(r->estado==1){
                    circle(ventana, casilla, 15, Scalar(0,0,255), CV_FILLED);
                }
                else{
                    if(r->estado==2){
                       circle(ventana, casilla, 15, Scalar(255,0,0), CV_FILLED); 
                    }
                }
                putText(ventana,to_string(r->id),casilla,FONT_HERSHEY_SIMPLEX,0.5,Scalar(255,255,255));
                
                r = r->sig;
                }
                while(r!=pAnillo4);
                do {
                
		Point casilla = Point(s->X, s->Y);
		circle(ventana, casilla, 20, blanco, CV_FILLED);
                if(s->estado==1){
                    circle(ventana, casilla, 15, Scalar(0,0,255), CV_FILLED);
                }
                else{
                    if(s->estado==2){
                       circle(ventana, casilla, 15, Scalar(255,0,0), CV_FILLED); 
                    }
                }
                putText(ventana,to_string(s->id),casilla,FONT_HERSHEY_SIMPLEX,0.5,Scalar(255,255,255));
                
                s = s->sig;
                }
                while(s!=pAnillo5);
                do {
                
		Point casilla = Point(t->X, t->Y);
		circle(ventana, casilla, 20, blanco, CV_FILLED);
                if(t->estado==1){
                    circle(ventana, casilla, 15, Scalar(0,0,255), CV_FILLED);
                }
                else{
                    if(t->estado==2){
                       circle(ventana, casilla, 15, Scalar(255,0,0), CV_FILLED); 
                    }
                }
                putText(ventana,to_string(t->id),casilla,FONT_HERSHEY_SIMPLEX,0.5,Scalar(255,255,255));
                
                t = t->sig;
                }
                while(t!=pAnillo6);
    }
            u=0;
}

void the_right_moves::limpiar_tablero()
{
  if(inicio){
        eliminarTodosElementosListaSimpleRecursiva(inicio);
        inicio = NULL;
  }
}

void the_right_moves::eliminarTodosElementosListaSimpleRecursiva(nodo *p)
{
    if(p->sig){
        eliminarTodosElementosListaSimpleRecursiva(p->sig);
    }
    delete(p);
}

void the_right_moves::ver_punteros()
{  
    nodo *p =pAnillo1;
    nodo *s =pAnillo2;
    nodo *q =pAnillo3;
    nodo *r =pAnillo4;
    nodo *m =pAnillo5;
    nodo *t =pAnillo6;

    if (p!=NULL && q!=NULL && r!=NULL && s!=NULL && t!=NULL && m!=NULL) {
        
        do {
            cout << "\nantertior " << p ->ant->id<< "\t ";
            cout << p -> id << "\t";
            cout << "siguiente " << p ->sig->id << "\t ";
            cout <<"estado "<< p ->estado<< "\t ";
            cout << "X " << p ->X << "\t ";
            cout << "Y " << p ->Y<< "\t ";
	    cout << "anillo " << p ->anillo<< "\t ";
            p = p -> sig;
	}
        while(p!=pAnillo1);
        do {
            cout << "\nantertior " << s ->ant->id<< "\t ";
            cout << s -> id << "\t";
            cout << "siguiente " << s ->sig->id << "\t ";
            cout <<"estado "<< s ->estado<< "\t ";
            cout << "X " << s ->X << "\t ";
            cout << "Y " << s ->Y<< "\t ";
	cout << "anillo " << s ->anillo<< "\t ";
            s = s -> sig;
	}

        while(s!=pAnillo2);
        do {
            cout << "\nantertior " << q ->ant->id<< "\t ";
            cout << q -> id << "\t";
            cout << "siguiente " << q ->sig->id << "\t ";
            cout <<"estado "<< q ->estado<< "\t ";
            cout << "X " << q ->X << "\t ";
            cout << "Y " << q ->Y<< "\t ";
	cout << "anillo " << q ->anillo<< "\t ";
            q = q -> sig;
	}
        while(q!=pAnillo3);
        do {
            cout << "\nantertior " << r ->ant->id<< "\t ";
            cout << r -> id << "\t";
            cout << "siguiente " << r ->sig->id << "\t ";
            cout <<"estado "<< r ->estado<< "\t ";
            cout << "X " << r ->X << "\t ";
            cout << "Y " << r ->Y<< "\t ";
	cout << "anillo " << r ->anillo<< "\t ";
            r = r -> sig;
	}
        while(r!=pAnillo4);
        do {
            cout << "\nantertior " << m ->ant->id<< "\t ";
            cout << m -> id << "\t";
            cout << "siguiente " << m ->sig->id << "\t ";
            cout <<"estado "<< m ->estado << "\t ";
            cout << "X " << m ->X << "\t ";
            cout << "Y " << m ->Y<< "\t ";
cout << "anillo " << m ->anillo<< "\t ";        
    cout << "afuera " << m ->afuera->id<< "\t ";
            
	m = m -> sig;
	}
        while(m!=pAnillo5);
        do {
            cout << "\nantertior " << t ->ant->id<< "\t ";
            cout << t -> id << "\t";
            cout << "siguiente " << t ->sig->id << "\t ";
            cout <<"estado "<< t ->estado << "\t ";
            cout << "X " << t ->X << "\t ";
            cout << "Y " << t ->Y<< "\t ";
cout << "anillo " << t ->anillo<< "\t ";            
cout << "afuera " << t ->afuera->id<< "\t ";
            t = t-> sig;
            
	}
        while(t!=pAnillo6);
    }
    else{
	cout << "Lista vacia" << '\n';
    }   

}
void onMouse(int event, int x, int y, int, void*) {
    //the_right_moves Tablero;
    int unax, unay;
    unax =x;
    unay =y;
    
	if (event == CV_EVENT_LBUTTONUP){
             
            //Tablero.ver_punteros(); 
            MouseI(unax, unay);
        }
}

void MouseI(int unax, int unay) {
    int Xizquierda=0,Xderecha=0, Yarriba=0,Yabajo=0;
    
        nodo *o = pAnillo1;
        nodo *p = pAnillo2;
        nodo *q = pAnillo3;
        nodo *r = pAnillo4;
        nodo *s = pAnillo5;
        nodo *t = pAnillo6;
    
    if(o!=NULL && p!=NULL && q!=NULL&& r!=NULL && s!=NULL && t!=NULL){
        do{
            Xizquierda = (o->X)-15;
            Xderecha =(o->X)+15;
            Yabajo = (o->Y)-15;
            Yarriba =(o->Y)+15;
        
            if(unax>Xizquierda && unax<Xderecha){
                if(unay>Yabajo && unay <Yarriba){
                    cout<<"dentro de "<<o->id<<endl;
                }
            }
            o = o-> sig;               
        }while(o!=pAnillo1);  
        do{
            Xizquierda = (p->X)-15;
            Xderecha =(p->X)+15;
            Yabajo = (p->Y)-15;
            Yarriba =(p->Y)+15;
        
            if(unax>Xizquierda && unax<Xderecha){
                if(unay>Yabajo && unay <Yarriba){
                    cout<<"dentro de "<<p->id<<endl;
                }
            }
            p = p-> sig;               
        }while(p!=pAnillo2);  
        do{
            Xizquierda = (q->X)-15;
            Xderecha =(q->X)+15;
            Yabajo = (q->Y)-15;
            Yarriba =(q->Y)+15;
        
            if(unax>Xizquierda && unax<Xderecha){
                if(unay>Yabajo && unay <Yarriba){
                    cout<<"dentro de "<<q->id<<endl;
                }
            }
            q = q-> sig;               
        }while(q!=pAnillo3); 
        do{
            Xizquierda = (r->X)-15;
            Xderecha =(r->X)+15;
            Yabajo = (r->Y)-15;
            Yarriba =(r->Y)+15;
        
            if(unax>Xizquierda && unax<Xderecha){
                if(unay>Yabajo && unay <Yarriba){
                    cout<<"dentro de "<<r->id<<endl;
                }
            }
            r = r-> sig;               
        }while(r!=pAnillo4); 
        do{
            Xizquierda = (s->X)-15;
            Xderecha =(s->X)+15;
            Yabajo = (s->Y)-15;
            Yarriba =(s->Y)+15;
        
            if(unax>Xizquierda && unax<Xderecha){
                if(unay>Yabajo && unay <Yarriba){
                    cout<<"dentro de "<<s->id<<endl;
                }
            }
            s= s-> sig;               
        }while(s!=pAnillo5);
        
        do{
            Xizquierda = (t->X)-15;
            Xderecha =(t->X)+15;
            Yabajo = (t->Y)-15;
            Yarriba =(t->Y)+15;
        
            if(unax>Xizquierda && unax<Xderecha){
                if(unay>Yabajo && unay <Yarriba){
                    cout<<"dentro de "<<t->id<<endl;
                }
            }
            t = t-> sig;               
        }while(t!=pAnillo6);
        
          
       } 
    else{
	cout << "Error" << '\n';
    }   
}


 
int main(void) {
    the_right_moves Tablero;
    
    namedWindow("Tablero");   
    setMouseCallback("Tablero",onMouse);
    
    
        cout<<"antes\n";
        Tablero.ver_punteros();
        cout<<"despues\n";
        imshow("Tablero", ventana);
	waitKey(0);
   
    return 0;
}

