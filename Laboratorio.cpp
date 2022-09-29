#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <typeinfo>

using namespace std;

template <class H>
class NodoBST //CLASSE NODO ALBERO BINARIO
{
	private:
		H data;
		NodoBST *pa;
        NodoBST *sx;
        NodoBST *dx;
        
    public:
    	NodoBST()
		{
		}
		NodoBST(H d)
    	{
    		data=d;
    		sx=NULL;
    		dx=NULL;
			pa=NULL;
		}

		friend ostream& operator<<( ostream &out, NodoBST<H> n)
		{
			out << n.get_data();
			return out;
		}
		
		void set_data(H d) { data=d; }
		H get_data() { return data; }
		
		void set_sx(NodoBST *s ) { sx=s; }
		NodoBST* get_sx() { return sx; }
		
		void set_dx(NodoBST *d ) { dx=d; }
		NodoBST* get_dx() { return dx; }

		void set_pa(NodoBST *p ) { pa=p; }
		NodoBST* get_pa() { return pa; }
};

template <class H>
class BST //CLASSE ALBERO BINARIO
{
	private:
		NodoBST<H> *radice;
		H h,k;
		
	public:
		BST()
		{
			radice=NULL;
		}
		BST(H a, H b)
		{
			radice=NULL;
			h=a;
			k=b;
		}

		void set_h(H d) { h=d; }
		H get_h() { return h; }

		void set_k(H d) { k=d; }
		H get_k() { return k; }

		void set_radice(H d)
		{ 
			NodoBST<H> *n = new NodoBST<H>;
			n->set_data(d); 
			n->set_pa(NULL);	
			n->set_dx(NULL); 
			n->set_sx(NULL); 			
			radice=n;
		}
		NodoBST<H>* get_radice() { return radice; }
		
		// STAMPA ALBERO
		void preorder() { cout << "\tElementi Albero - preorder:\n"; preorder(radice); }
		void preorder(NodoBST<H> *n)
		{
			if(n!=NULL)
			{
				cout << n << " data: " << n->get_data() << " pa: " << n->get_pa() << " sx: " << n->get_sx() << " dx: " << n->get_dx() << "\n";
				preorder(n->get_sx());
				preorder(n->get_dx());
			}
		}
		
		//INSERIMENTO NODO
		void inserisci(H d) 
		{
			if(radice==NULL) { NodoBST<H> *t = new NodoBST<H>;	t->set_data(d);	t->set_sx(NULL); t->set_dx(NULL); t->set_pa(NULL); radice=t; return; }
			inserisci(radice, d); 
		}
		void inserisci(NodoBST<H> *n, H d)
		{
			if( d <= n->get_data() )
			{
				if( n->get_sx()==NULL )
				{ 
					NodoBST<H> *t = new NodoBST<H>;
					t->set_data(d);
					t->set_sx(NULL);
					t->set_dx(NULL);

					n->set_sx(t);
					t->set_pa(n);
					
					return;
           		}
				//cout << "\nsx: " << n->get_sx();
				inserisci(n->get_sx(),d); 
         	}
			else
			{
				if( n->get_dx()==NULL )
				{ 
					NodoBST<H> *t = new NodoBST<H>;
					t->set_data(d);
					t->set_sx(NULL);
					t->set_dx(NULL);

					n->set_dx(t);
					t->set_pa(n);
					
					return;
           		}
				//cout << "\ndx: " << n->get_dx();
				inserisci(n->get_dx(),d); 
         	}
		}

		NodoBST<H>* find(H a)
		{
			NodoBST<H> *n = new NodoBST<H>;
			n=radice;
			while( n!=NULL ) //trova il nodo 
			{
				//cout << "n: " << n << " data: " << n->get_data() << " pa: " << n->get_pa() << " sx: " << n->get_sx() << " dx: " << n->get_dx() << "\n";
				if( n->get_data() == a ) { return n; }
				if( a < n->get_data() ) { n=n->get_sx(); } 
				if( a > n->get_data() ) { n=n->get_dx(); } 
			}
		}

		int findfrom(NodoBST<H> *start ,H a)
		{
			int r=0;
			bool up=false;
			NodoBST<H> *n = new NodoBST<H>;
			n=start;

			//cout << "k: " << k << " h: " << h << "\n";

			while( n!=NULL )
			//for(int i=0; i<10; i++)
			{
				if( n->get_data()==start->get_data() ) r=0;
				if( n->get_data() == a ) { return r; }
				if( a < n->get_data() && n->get_sx()!=NULL && ( !up || n==radice ) ) 
				{ 
					//cout << "sx\n";
					 n=n->get_sx(); r++; up=false; 
				} 
				else 
				{
					if( a > n->get_data() && n->get_dx()!=NULL && ( !up || n==radice )  ) 
					{ 
						//cout << "dx\n"; 
						n=n->get_dx(); r++; up=false; 
					} 
					else 
					{ 
						if( n->get_pa()!=NULL )
						{ 
							//cout << "pa\n"; 
							n=n->get_pa(); r++; up=true;
						}
						else
						{ 
							cout << "\nPORO DIO\n"; 
							cout << n << " data: " << n->get_data() << " pa: " << n->get_pa() << " sx: " << n->get_sx() << " dx: " << n->get_dx() << "\n";
						}
					} 
				}

			}
			return -1;

		}

		int get_distanza()
		{
			NodoBST<H> *a = new NodoBST<H>;
			//NodoBST<H> *b = new NodoBST<H>;
			a=find(k); //cout << a << " ";
			return findfrom(a,h);			
		}

};

/*
BST – distanze
Si implementi una classe BST, attraverso l'utilizzo dei template, contenente elementi di tipo generico H. La
classe dovrà implementare la procedura di inserimento di un nuovo elemento, una visita che permette di
visualizzare il contenuto del BST, ed una procedura int distanzaChiavi(H k, H h) che, prese in
input due chiavi k e h, sia in grado di calcolare la distanza tra i nodi che contengono k e h rispettivamente.
L'input è suddiviso in 6 task, uno per ogni riga. Ogni riga del file di input è formata da 3+N elementi. Il primo
elemento è una stringa che identifica il tipo di dato che dovrà essere contenuto all'interno dell'albero. Il
secondo elemento è un valore intero N, il quale rappresenta il numero delle operazioni di inserimento che
dovranno essere effettuate nella struttura dati. Seguono N stringhe che rappresentano, nell'ordine dato, le
operazioni da svolgere all'interno dell'albero. Nell specifico un inserimento di un valore "v" viene identificato
dall stringa "ins:" seguita dal valore "v". Gli ultimi due elementi della sequenza sono i valori k ed h, i quali
rappresentano le chiavi contenute nei nodi per i quali si vuole calcolare la distanza.
Il metodo main deve leggere il contenuto del file input.txt, istanziare un BST per ciascun task, visualizzarne il
contenuto ed eseguire l’operazione
Esempio:
Input: int 6 ins:10 ins:5 ins:15 ins:13 ins:22 ins:7 7 15
Output: 3
*/


int main()
{
	BST<int> IBST[3]; 
	BST<char> CBST[3];
	int ib=0,cb=0;

	ifstream file;
	file.open("input.txt");
	string line;
	if(file.is_open())
	{
		while(getline(file, line) )
		{

			string token, type, operation, data;
			int n;
			stringstream ss(line);

			cout << "INPUT:\t";

			getline(ss, token,' ');
			type=token;
			cout << "tipo: " << type;

			getline(ss, token,' ');
			n=atoi( token.c_str() );
			cout << "\tN: " << n << "\t\t";

			if( type=="int" ) //int
			{
				for(int i=0; i<n; i++)
				{
					getline(ss, token,' ');
					stringstream sstoken(token);
						getline(sstoken, operation,':');
						getline(sstoken, data,' ');

						cout << operation << " " << data << ", ";
						IBST[ib].inserisci( atoi( data.c_str() ) );
				}
					
					getline(ss, token,' ');
					IBST[ib].set_k( atoi( token.c_str() ));
					getline(ss, token,' ');
					IBST[ib].set_h( atoi( token.c_str() ));

					cout << "k: " <<IBST[ib].get_k() << " h: " <<IBST[ib].get_h() << "\n\n";

					//IBST[ib].preorder(); cout << "\n";
					cout << "OUTPUT:\t" << IBST[ib].get_distanza() << "\n\n\n";

					ib++;		
			}
			else if( type=="char" ) //char
			{
				for(int i=0; i<n; i++)
				{
					getline(ss, token,' ');
					stringstream sstoken(token);
						getline(sstoken, operation,':');
						getline(sstoken, data,' ');
						
						cout << operation << " " << data << ", ";
						CBST[cb].inserisci( data[0] );
				}
					
					getline(ss, token,' ');
					CBST[cb].set_k( token[0] );
					getline(ss, token,' ');
					CBST[cb].set_h( token[0] );

					cout << "k: " <<CBST[cb].get_k() << " h: " <<CBST[cb].get_h() << "\n\n";

					//CBST[cb].preorder(); cout << "\n"; 
					cout << "OUTPUT:\t" << CBST[cb].get_distanza() << "\n\n\n";
					
					cb++;
			}
		}

	}
}