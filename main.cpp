    #include <iostream>
    #include <vector>
    #include <ctime>
    #include <cstdio>
    #include <cstdlib>
    #include <unistd.h>
    #include <dos.h>
    #include <windows.h>
    #include <conio.h>
    #include <algorithm>    // std::sort

    using namespace std;

    struct caballo
    {
        float velocidad; // velocidad del caballo
        float peso_conductor; // peso de conductor que influencia 1 /peso
        float n_vuelta; //nnumero de vuelta en la que va
        float destreza; // deacuerdo a destreza 1 2 3
        float distancia_actual; //distancia en la que va
        int id_caballo;
    };
    struct apuesta
    {
        string nombre; // nombre del que apuesta
        int apuestas[3]; // puede apostar o a los 3 o solo a 1 o solo a dos    (0 0 1) (0 1 1) (1 1 1) (primera pos / segunda pos / tercera pos)

    };
    class Carreras
    {
    public:
        Carreras(int n_caballos_);
        void apostar(); //funcion apostar
        void fun_carrera(int n_vueltas); // fun carrera
        void resultados();
        void ordenar();
        void jugar(int n_vueltas);
    private:
        vector<caballo> competidores; // vector de competidores
        vector<apuesta> apostadores;
        int monto;
        int n_caballos;
    };
    Carreras::Carreras(int n_caballos_) // inicializo caballos
    {
         srand(time(NULL));
        n_caballos = n_caballos_;
        for(int i = 0 ; i < n_caballos; ++i)
        {
            caballo cab;
            cab.destreza = rand()%2 + 1.0;// numeros aleatorios de 1 2 3
            cab.n_vuelta= 0.0;
            cab.peso_conductor = 50.0 + rand()%10; // numeros aleatorios de 50 a 60
            cab.velocidad = 45.0 +rand()%10;  //velocidad del caballo
            cab.distancia_actual = 0.0;
            cab.id_caballo =i+1;    //id que se identificara el caballo
            competidores.push_back(cab); // se inserta al array cada competidor  (caballo)
        }
        monto = 0;
    }
    void Carreras::jugar(int n_vueltas) // inicia el juego con n_vuletas de caballo
    {
        apostar();

        fun_carrera(n_vueltas);
        ordenar();
        resultados();

    }
    void Carreras::apostar()
    {
        cout<< "haga su apuesta=========> a que caballo desea apostar"<<endl;

        string fin_apuesta;
        string nombre;
        while(fin_apuesta != "fin")
        {
            int a1 = 0,a2 = 0,a3 = 0;
            int tipo = 0;
            cout<<"Escribir su nombre "<<endl;
            cin >> nombre;
            cout<<"Escribir tipo de Apuesta"<<endl;
            cout <<"Tipo 1 = Solo Un Caballo Monto 100"<<endl;
            cout <<"Tipo 2 = Dos Caballos Monto 150"<<endl;
            cout <<"Tipo 3 = Tres Caballos Monto 200"<<endl;
            cin >> tipo;
            cout <<"-------------------------------------------------"<<endl;
            cout<<"Escribir Numero de caballo al que desea apostar"<<endl;
            if(tipo == 1 || tipo == 2 || tipo == 3){
                cout<<" Primer puesto"<<endl;
                cin >> a1;

            }
            if( tipo == 2 || tipo == 3){
                cout<<" Segundo puesto"<<endl;
                cin >> a2;
            }
            if( tipo == 3){
                cout<<" Tercer puesto"<<endl;
                cin >> a3;

            }
            monto += tipo*50 + 50; // deacuerdo al tipo se incrementa el monto
             cout <<"-------------------------------------------------"<<endl;
            cout << "desea hacer otra apuesta? Para terminar escriba fin de lo contrario s"<<endl;
            cin >>fin_apuesta;
            apuesta ap;
            ap.nombre = nombre;
            ap.apuestas[0] = a1;
            ap.apuestas[1] = a2;
            ap.apuestas[2] = a3;
            apostadores.push_back(ap); // agregamos cada apostador al array
        }
        return;
    }
    void Carreras::fun_carrera(int n_vueltas)
    {

       // while(i < 10){
        for(int j = 1 ; j <= n_vueltas ; ++j){
             cout <<"---------------------------vuelta numero"<<j<<"---------------------------"<<endl;

             for(int i = 0 ; i < n_caballos ; ++i)
             {
                 competidores[i].n_vuelta =j; //actualizamos n_vuelta en la que va

                    //distancia = numero de vueltas/la vuelta que va cada competidor * (la destreza + 1 /peso del conductor  + velocidad del caballo )
                 int distancia_real = float(n_vueltas/competidores[i].n_vuelta)*(competidores[i].destreza + 1/competidores[i].peso_conductor + competidores[i].velocidad);//funcion para que corra no se si esta bien esta fucnion
                 //velocidad se autoincrementa
                 competidores[i].distancia_actual = competidores[i].distancia_actual + distancia_real ;

                 cout<<"numero de vuelta: "<<j << " distancia en la que va->"<<competidores[i].distancia_actual <<endl ;
             }
             //Sleep(2000);

        }


         //i++;
        //}
    }
    void Carreras::ordenar () // funcion ordenar con el mas simple buble sort
    {
          int i, j, flag = 1;    // set flag to 1 to start first pass
          int temp;             // holding variable
          int numLength = competidores.size( );
          for(i = 1; (i <= numLength) && flag; i++)
         {
              flag = 0;
              for (j=0; j < (numLength -1); j++)
             {      //ordena ascendentemente  1 2 3 4 5 6
                   if (competidores[j+1].distancia_actual > competidores[j].distancia_actual)      // ascending order simply changes to <
                  {
                      //copeamos a un temp competidores en la posicion j
                      caballo cab_temp;
                      cab_temp.destreza = competidores[j].destreza;
                      cab_temp.distancia_actual = competidores[j].distancia_actual;
                      cab_temp.n_vuelta = competidores[j].n_vuelta;
                      cab_temp.velocidad = competidores[j].velocidad;
                      cab_temp.id_caballo = competidores[j].id_caballo;
                        // copeamos en competidores posicion j  lo que hay en j +1
                      competidores[j].destreza = competidores[j+1].destreza ;
                      competidores[j].distancia_actual = competidores[j+1].distancia_actual;
                      competidores[j].n_vuelta = competidores[j+1].n_vuelta;
                      competidores[j].velocidad = competidores[j+1].velocidad;
                      competidores[j].id_caballo = competidores[j+1].id_caballo;
                        //copeamos a j +1 lo que hay en temp
                      competidores[j+1].destreza = cab_temp.destreza ;
                      competidores[j+1].distancia_actual = cab_temp.distancia_actual;
                      competidores[j+1].n_vuelta = cab_temp.n_vuelta;
                      competidores[j+1].velocidad = cab_temp.velocidad;
                      competidores[j+1].id_caballo = cab_temp.id_caballo;

                        flag = 1;               // indicates that a swap occurred.
                   }
              }
         }

    }
    void Carreras::resultados()
    {
        cout <<endl<<endl <<"----------------RESULTADOS DE LA CARRERA----------------"<<endl;
        cout <<"primer puesto -> Caballo numero "<<competidores[9].id_caballo <<endl;
        cout <<"segundo puesto -> Caballo numero "<<competidores[8].id_caballo <<endl;
        cout <<"tercer puesto -> Caballo numero "<<competidores[7].id_caballo <<endl;
        int primero = 100,segundo = 200,tercero = 300; // inicializamos primero segundo tercero con valores altos diferentes

        for(int i = 0 ; i <apostadores.size();++i)
        {
            if(competidores[n_caballos-1].id_caballo == apostadores[i].apuestas[0])  // Preguntamos quien acerto el primero y actualizamos
            {
                primero = i;

            }
            else if(competidores[n_caballos-2].id_caballo == apostadores[i].apuestas[1] ) // Preguntamos quien gano el segundo y actualizamos
            {
                segundo = i;

            }
            else if(competidores[n_caballos-3].id_caballo == apostadores[i].apuestas[2]) // preguntamos por el tercero y actualizamos
            {
                tercero = i;

            }
        }
        if(primero == segundo && segundo == tercero){
            cout << "jugador  "<<apostadores[primero].nombre<<"ganaste 45 % equivalente a "<<(float)monto *45.0/100.0<<endl; // si el primero es el mismo que el segundo y el tercero gana 45 %
        }
        else if(primero == segundo){
            cout << "jugador  "<<apostadores[primero].nombre<<"ganaste 30 % equivalente a"<<(float)monto *30.0/100.0<<endl; // si el segundo es el mismo que el primero gana 30 %
        }
        else if(primero <100 ){
            cout << "jugador  "<<apostadores[primero].nombre<<"ganaste 25 % equivalente a"<<(float)monto *25.0/100.0<<endl; // si solo gana el primero 25 %
        }
        else{cout <<"nadie gano";}

    }
    int main()
    {

        Carreras car(10); //numero de caballos = 10 caballos
        car.jugar(10); // numero de vueltas = 10
        return 0;
    }
