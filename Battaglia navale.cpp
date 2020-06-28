#include <iostream>
#include <Windows.h>
using namespace std;

enum colors{red=12, blue=9, def=15, green=10};

void Color(colors color)
{
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}


const int DIM = 10;
const int NBARC = 5; //1;

void InizLungBarche(int Lunghezze[NBARC]);
void Inizializza (int C1[DIM][DIM], int C2[DIM][DIM], int CMemo1[DIM][DIM], int CMemo2[DIM][DIM]);      //butta le barche nei rispettivi campi
void Inserisci (int C[DIM][DIM], int Lunghezze[NBARC], int CMemo[DIM][DIM]);      //crea un vettore che contiene le lunghezze di ogni barca del giocatore x
void Visualizza (int C[DIM][DIM], int CMemo[DIM][DIM]);
bool Colpito (int C[DIM][DIM], int rig, int col);
bool Sparo (int CMemo[DIM][DIM], int C[DIM][DIM]);
bool Vivo (int C[DIM][DIM]);

int main()
{

	int Campo1[DIM][DIM], Campo2[DIM][DIM], Spari1[DIM][DIM], Spari2[DIM][DIM];
    int LungBarche [NBARC];
    bool vegeto1, vegeto2;
    bool colpito;

    Color(def);
    cout<<"                            BATTAGLIA NAVALE: 1 VS 1!\n\n";

    Inizializza (Campo1, Campo2, Spari1, Spari2);
    InizLungBarche(LungBarche);

	cout<<"Giocatore 1, tocca a te inserire le barche.\n";
	Inserisci (Campo1, LungBarche, Spari1);
	cout<<endl<<"Questo e' il tuo schieramento\n";
	Visualizza (Campo1, Spari1);
	cout << "Ora tocca al giocatore 2!";
	system("pause>nul");
	system("cls");

	cout<<"                                BATTAGLIA NAVALE: 1 VS 1!\n\n";
	cout<<"Giocatore 2, tocca a te inserire le barche.\n";
	Inserisci (Campo2, LungBarche, Spari2);
	cout<<endl<<"Questo e' il tuo schieramento\n";
	Visualizza (Campo2, Spari2);
	cout << endl << "Ora inizia la battaglia!";
	system("pause>nul");
	system("cls");

	do
	{
		cout<<"Giocatore 1, tocca a te sparare.\n";
		Visualizza (Campo1, Spari1);
		colpito = Sparo (Spari1, Campo2);
		vegeto2 = Vivo (Campo2);
		system("cls");
		cout<<"Situazione giocatore 1:\n\n";
		Visualizza (Campo1, Spari1);
		if(colpito == true)
		{
			cout<<"COLPITO!!\n";
		}
		else
		{
			cout<<"Acqua...\n";
		}
		if (vegeto2 == false)
		{
			cout<<"GIOCATORE 1 WINS!!\n";
	    	system("pause");
			return 0;
		}
		else
		{
			system("pause");
			system("cls");
		}

		cout<<"Giocatore 2, tocca a te sparare.\n";
		Visualizza (Campo2, Spari2);
		colpito = Sparo (Spari2, Campo1);
		vegeto1 = Vivo (Campo1);
		system("cls");
		cout<<"Situazione giocatore 2:\n\n";
		Visualizza (Campo2, Spari2);
		if(colpito == true)
		{
			cout<<"COLPITO!!\n";
		}
		else
		{
			cout<<"Acqua...\n";
		}
		if (vegeto1 == false)
		{
			cout<<"GIOCATORE 2 WINS!!\n";
	    	system("pause>nul");
			return 0;
		}
		else
		{
			system("pause");
			system("cls");
		}

	} while (vegeto1==true && vegeto2==true);

    system("pause");
    return 0;
}

//------------------------------------------------------------------------------ Inizializza

void Inizializza (int C1[DIM][DIM], int C2[DIM][DIM], int CMemo1[DIM][DIM], int CMemo2[DIM][DIM])
{
      for(int i=0; i<DIM; i++)
      {
              for(int j=0; j<DIM; j++)
              {
                      C1 [i][j]=0;
                      C2 [i][j]=0;
                      CMemo1 [i][j]=0;
                      CMemo2 [i][j]=0;
              }
      }
}

//------------------------------------------------------------------------------ Inizializza il vettore che contiene la lunghezza delle barche

void InizLungBarche(int Lunghezze[NBARC])
{
    Lunghezze[0] = 2;
    Lunghezze[1] = 3;
    Lunghezze[2] = 3;
    Lunghezze[3] = 4;
    Lunghezze[4] = 5;
}

//------------------------------------------------------------------------------ Inserisci

void Inserisci (int C[DIM][DIM], int Lunghezze[NBARC], int CMemo[DIM][DIM])
{
	int c, r, rtemp, ctemp, direz;
    bool su = true, giu = true, dx = true, sx = true;																			//Ognuna indica la relativa disponibilità nell'andare in quella direzione
    bool ctrldirez = true;

    for(int x=0; x<NBARC; x++)
    {

		cout<<"\nNAVE DA "<<Lunghezze[x]<<"\n\n";														//è sorto il problema del "ehi, il punto di partenza è libero... ma se non c'è abbastanza spazio attorno?!

		do
		{
				do
            	{
                        Visualizza (C, CMemo);

						do
                        {
							    cout<<"Riga: ";																					//Inserisci la riga + controlli
	                        	cin>> r;
	                          	r-=1;																							//trasforma la scala da 1-10 a 0-9
	                          	if(r>9 or r<0)
	                          	{
	                          		cout<<"Posizione non disponibile\n";
								}

						} while(r>9 or r<0);


                        do
                        {
                          	  	cout<<"Colonna: ";																				//Inserisci la colonna + controlli
                          		cin>> c;
	                    		c-=1;																							//trasforma la scala da 1-10 a 0-9
	                    		if(r>9 or r<0)
	                          	{
	                          		cout<<"Posizione non disponibile\n";
								}

						} while(c>9 or c<0);


                          if(C[r][c]==1)
                        {
                                    system("cls");
									cout<<"ERRORE, NON E' POSSIBILE SOVRAPPORRE NAVI. REINSERISCI LE COORDINATE!\n\n";
                        }

            	} while (C[r][c]==1);


    			su = true;																							//azzera le bool in modo da ritornare da capo
				giu = true;
				dx = true;
				sx = true;




				// ctrl su
                for (int i=1; i<Lunghezze[x]; i++)
                {
					 if(r-i>=0 && r-i<=9)
					 {
					 	if(C[r-i][c]==1)
						{
							su = false;
						}
					 }
					 else
					 {
					 	su = false;
					 }
                }



				// ctrl giu
                for (int i=1; i<Lunghezze[x]; i++)
                {

					if(r+i>=0 && r+i<=9)
					{
					 	if(C[r+i][c]==1)
						{
							giu = false;
						}
					}
					else
					{
					 	giu = false;
					}
                }



                // ctrl destra
                for (int i=1; i<Lunghezze[x]; i++)
                {


					if(c+i>=0 && c+i<=9)
					{
					 	if(C[r][c+i]==1)
						{
							dx = false;
						}
					}
					else
					{
					 	dx = false;
					}
                }



				// ctrl sinistra
                for (int i=1; i<Lunghezze[x]; i++)
                {


					 if(c-i>=0 && c-i<=9)
					 {
					 	if(C[r][c-i]==1)
						{
							sx = false;
						}
					 }
					 else
					 {
					 	sx = false;
					 }
                }


        		 if(su == false && giu == false && dx == false && sx == false)
        		 {
                        system("cls");
						cout<<"ERRORE, QUESTO PUNTO DI PARTENZA NON E' DISPONIBILE. REINSERISCI LE COORDINATE!\n\n";
                 }
                 else
                 {
                 	C[r][c]=1;
				 }

		} while (su == false && giu == false && dx == false && sx == false);
//------------------

			   	do																												// reinserisci la direzione finchè ne inserisce una non valida
			   	{
				   ctrldirez = true;

				   do
				   {
					   cout<<"In che direzione vuoi orientare la nave? (su = 1; giu'= 2; dx = 3; sx = 4)\n";							//decicdi il verso
	                   cin>>direz;

	                   if(direz<1 or direz>4)
	                   {
	                   		cout<<"Direzione non disponibile\n";
					   }

	            	} while(direz<1 or direz>4);


				   switch (direz)
	               {
	                        case 1:
	                            if (su == true)
	                            {
										for (int i=0; i<Lunghezze[x]-1; i++)
			                            {
									 		r--;
											 C[r][c]=1;
			                            }
								}
								else
								{
									cout<<"Direzione non disponibile\n\n";
									ctrldirez = false;
								}
								break;

	                        case 2:
	                            if (giu == true)
	                            {
									for (int i=0; i<Lunghezze[x]-1; i++)
		                            {
								 		r++;
										 C[r][c]=1;
		                            }
		                    	}
		                    	else
								{
									cout<<"Direzione non disponibile\n\n";
									ctrldirez = false;
								}
	                           break;

	               			case 3:
	                            if (dx == true)
	                            {
									for (int i=0; i<Lunghezze[x]-1; i++)
		                            {
								 		c++;
										 C[r][c]=1;
		                            }
		                    	}
		                    	else
								{
									cout<<"Direzione non disponibile\n\n";
									ctrldirez = false;
								}
	                            break;

	                       case 4:
	                            if (sx == true)
	                            {
									for (int i=0; i<Lunghezze[x]-1; i++)
		                            {
								 		c--;
										 C[r][c]=1;
		                            }
		                    	}
		                    	else
								{
									cout<<"Direzione non disponibile\n\n";
									ctrldirez = false;
								}
	                           break;
	               }
	    	} while(ctrldirez == false);

			system("cls");
			cout<<"                                BATTAGLIA NAVALE: 1 VS 1!\n\n";

     }
}


//-------------------------------------------------------------------------------------------- Visualizza

void Visualizza (int C[DIM][DIM], int CMemo[DIM][DIM])
{

	cout<<"     Campo di battaglia         Memo colpi sparati\n";
	cout<<"    ";
	for (int i=0; i<DIM; i++)
	{
		cout<<i+1<<" ";
	}
	cout<<"      ";
	for (int i=0; i<DIM; i++)
	{
		cout<<i+1<<" ";
	}
	cout<<endl<<endl;

	for(int i=0; i<DIM; i++)			//visualizzazione matrice combattimento
	{
		if(i<DIM-1)
		{
			cout<<i+1<<"   "; 			//spazi dopo i numeri delle righe
		}
		else
		{
			cout<<i+1<<"  ";			//spazi dopo i numeri delle righe
		}

		for(int j=0; j<DIM; j++)
		{
			if(C[i][j] == 0)
			{
                Color(blue);
                cout<<C[i][j]<<" ";			//la tua acqua e i relativi spazi
                Color(def);
            }

            if(C[i][j] == 1)
			{
                Color(def);
                cout<<C[i][j]<<" ";			//le tue navi
            }

            if(C[i][j] == 2)
			{
                Color(red);
                cout<<C[i][j]<<" ";			//le caselle del campo di battaglia (pezzi delle tue navi che sono stati colpiti) e i relativi spazi
                Color(def);
            }

            if(C[i][j] == 3)
			{
                Color(green);
                cout<<C[i][j]<<" ";			//L'avversario ha sparato qui in acqua e i relativi spazi
                Color(def);
            }
        }

		cout<<"   ";

		if(i<DIM-1)
		{
			cout<<i+1<<"   "; 			//spazi dopo i numeri delle righe dall'1 al 9
		}
		else
		{
			cout<<i+1<<"  ";			//spazio dopo il numero 10
		}

		for(int j=0; j<DIM; j++)
		{
			if(CMemo[i][j] == 0)
			{
                Color(blue);
                cout<<CMemo[i][j]<<" ";			//le caselle del Memo dell'acqua e i relativi spazi
    		    Color(def);
            }

            if(CMemo[i][j] == 2)
			{
                Color(red);
                cout<<CMemo[i][j]<<" ";			//Pezzi avversari che hai colpito e i relativi spazi
    		    Color(def);
            }

			if(CMemo[i][j] == 3)
			{
                Color(green);
                cout<<CMemo[i][j]<<" ";			//Li dove hai sparato c'è dell'acqua
    		    Color(def);
            }
        }

		cout<<endl;
	}
}

//----------------------------------------------------------------------------------------------------------------- Fase d'attacco

bool Sparo (int CMemo[DIM][DIM], int C[DIM][DIM])
{
     int r, c;
     bool colpito;

     cout<<"FASE D'ATTACCO\n";

     do
     {
     		 do
		     {
					 cout<<"Riga: ";
				     cin>> r;
				     r-=1;

		 	 } while (r<0 or r>9);

     		 do
		     {
				     cout<<"Colonna: ";
					 cin>> c;
					 c-=1;

			 } while (r<0 or r>9);

	 } while(CMemo[r][c]==3 or CMemo[r][c]==2);   						// controlla che non abbia già sparato in quel punto

	 colpito = Colpito (C, r, c);
	 if (colpito == true)													//Cmemo ha 3 stati: 0.Non hai ancora sparato li  1.hai sparato e hai beccato un pezzo di barca  2.hai sparato nell'acqua
	 {
	 	C[r][c] = 2;
		CMemo [r][c] = 2;
		return colpito;
		//cout<<"COLPITO!!\n";
	 }
     else
     {
     	C[r][c] = 3;
     	CMemo [r][c] = 3;
     	return colpito;
     	//cout<<"Acqua...\n";
	 }

}

//-----------------------------------------------------------------------------------------------------------------Colpito o no

bool Colpito (int C[DIM][DIM], int rig, int col)
{
     bool colpo=false;
     if(C[rig][col] == 1)
     {
            colpo=true;
     }
     return colpo;
}

//-------------------------------------------------------------------------------------------------------------------- Vivo o no

bool Vivo (int C[DIM][DIM])
{
	bool vivo = false;

	for (int i=0; i<DIM; i++)
	{
		for(int j=0; j<DIM; j++)
		{
			if (C[i][j]==1)
			{
				vivo = true;
				return vivo;
			}
		}
	}
	return vivo;
}













