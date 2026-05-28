#include <iostream>
#include <fstream>
#include <vector> 

using namespace std;

struct esperanzaVida {
    string pais;
    string codigo;
    int year;
    double esperanza;
};

typedef double tMatrizEvo[5][100];


struct Registro {
    string pais;
    string codigo;
    int any;
    double valor;
    string continente;
};

//Enric Pegueroles Llonch 21/5/2026

    struct poblacion {
    string pais;
    string codigo;
    int any;
    int habitantes;
};

typedef double tMatriuPoblacio[4][4];

void CargarFichero(vector<esperanzaVida>& esperanza, vector<Registro>& v, vector<poblacion>& lista) {
    ifstream fin1("life_expectancy.txt");
    ifstream fin2("gdp_per_capita.txt");
	ifstream fin3("population.txt");
	
	esperanzaVida esp;
	Registro reg;
	poblacion p;
    
	while (fin1 >> esp.pais >> esp.codigo >> esp.year >> esp.esperanza) {
        esperanza.push_back(esp);
    }
    
   
    while (fin2 >> reg.pais >> reg.codigo >> reg.any >> reg.valor >> reg.continente) {
        v.push_back(reg);
    }
    
    
    while (fin3 >> p.pais >> p.codigo >> p.any >> p.habitantes) {
        lista.push_back(p);
    }

    fin1.close();
	fin2.close();
	fin3.close();
}

void MenuMarcGuti() {
	cout<<"Esperanza de vida" << endl << endl;
	cout<<"  	MENU	 " << endl;
	cout<<"1.  DAR DE ALTA UN DATO" << endl;
	cout<<"2.  DAR DE BAJA UN DATO" << endl;
	cout<<"3.  BUSCAR UN DATO" << endl;
	cout<<"4.  MODIFICAR UN DATO" << endl;
	cout<<"5.  ESTADISTICAS DE VALORES MAXIMOS Y MINIMOS (HISTORICOS)" << endl;
	cout<<"6.  ESTADISTICAS DE VALORES MAXIMOS Y MINIMOS (POR AÑO SELECCIONADO)" << endl;
	cout<<"7.  GENERAR INFORME DE ESPERANZA DE VIDA (POR AÑO SELECCIONADO)" << endl;
	cout<<"8.  ESTADISTICAS DE CRECIMIENTO O DECRECIMIENTO DE ESPERANZA DE VIDA EN UN INTERVALO" << endl;
	cout<<"9. TABLA COMPARATIVA" << endl;
	cout<<"10. GUARDAR Y SALIR" << endl;
}

void PausaMarcGuti() {
	cout << endl << "Presiona Intro para continuar...";
	cin.ignore();
	cin.get();
	system("cls");
}

string IsoSelecMarcGuti() {
	string iso;
	cout << "Introduce el codigo ISO del pais: " << endl;
	cin >> iso;
	return iso;
}

int YearSelecMarcGuti() {
	int year;
	cout << "Introduce el año: " << endl;
	cin >> year;
	return year;
}

void IntervaloSelecMarcGuti(int& a1, int& a2) {
	cout << "Año inicial: "; 
	cin >> a1;
    cout << "Año final: "; 
	cin >> a2;
}

int BuscarMarcGuti(const vector<esperanzaVida>& lista, string codigo, int a) {
    int indice = 0;
    int pos = -1;
    bool encontrado = false;
    
    while (indice < lista.size() && !encontrado) {
        if (lista[indice].codigo == codigo && lista[indice].year == a) {
            encontrado = true;
            pos = indice; 
        } else {
            indice++;
        }
    }
    return pos;
}

void AltaMarcGuti(vector<esperanzaVida>& lista, string codigo, int a) {
    if (BuscarMarcGuti(lista, codigo, a) != -1) {
        cout << "Error: El registro ya existe para ese pais y año." << endl;
    } 
	else {
        esperanzaVida insertar;
        insertar.codigo = codigo;
        insertar.year = a;
        cout << "Introduce el nombre del pais: "; cin >> insertar.pais;
        cout << "Introduce el valor de esperanza de vida: "; cin >> insertar.esperanza;
        
        lista.push_back(insertar);
        cout << "Registro añadido" << endl;
    }
}

void BajaMarcGuti(vector<esperanzaVida>& lista, string codigo, int year) {
    if (BuscarMarcGuti(lista, codigo, year) == -1) {
        cout << "No se ha encontrado el registro para eliminar." << endl;
    } 
	else {
       lista[BuscarMarcGuti(lista, codigo, year)] = lista[lista.size() - 1];
       lista.pop_back(); 
       cout << "Registro eliminado correctamente." << endl;
    }
}

void ModificarMarcGuti(vector<esperanzaVida>& lista, string codigo, int year) {
    int pos = BuscarMarcGuti(lista, codigo, year);
    if (pos == -1) {
        cout << "Error: No existe ese registro." << endl;
    } 
	else {
        cout << "Valor actual: " << lista[pos].esperanza << endl;
        cout << "Introduce el nuevo valor de esperanza de vida: ";
        cin >> lista[pos].esperanza;
        cout << "Modificacion realizada." << endl;
    }
}

void MinMaxHistoricoMarcGuti(const vector<esperanzaVida>& lista) {
    int posMax = 0;
    int posMin = 0;

    for (int i = 1; i < lista.size(); i++) {
        if (lista[i].esperanza > lista[posMax].esperanza) {
            posMax = i;
        }
        if (lista[i].esperanza < lista[posMin].esperanza) {
            posMin = i;
        }
    }

    cout << "VALOR MAXIMO: " << lista[posMax].pais << " (" << lista[posMax].year << ") ESPERANZA:  " << lista[posMax].esperanza << " años." << endl;
    cout << "VALOR MINIMO: " << lista[posMin].pais << " (" << lista[posMin].year << ") ESPERANZA: " << lista[posMin].esperanza << " años." << endl;
}

void GuardarFicheroMarcGuti(const vector<esperanzaVida>& lista){
	ofstream fout("life_expectancy.txt"); 
    for (int i = 0; i < lista.size(); i++) {
        fout << lista[i].pais << " " << lista[i].codigo << " " << lista[i].year << " " << lista[i].esperanza << endl;
    }
    fout.close();
    cout << "Cambios guardados en el archivo correctamente." << endl;
}

void MaxMinPorYearMarcGuti(const vector<esperanzaVida>& lista, int year) {
    int posMax = -1;
    int posMin = -1;

    for (int i = 0; i < lista.size(); i++) {
        if (lista[i].year == year) {
            if (posMax == -1) {
                posMax = i;
                posMin = i;
            } else {
                if (lista[i].esperanza > lista[posMax].esperanza) posMax = i;
                if (lista[i].esperanza < lista[posMin].esperanza) posMin = i;
            }
        }
    }

    if (posMax != -1) {
        cout << "Resultados para el año " << year << ":" << endl;
        cout << "- Pais con mas esperanza: " << lista[posMax].pais << " (" << lista[posMax].esperanza << ")" << endl;
        cout << "- Pais con menos esperanza: " << lista[posMin].pais << " (" << lista[posMin].esperanza << ")" << endl;
    } else {
        cout << "No se han encontrado datos para el año " << year << "." << endl;
    }
}

void GenerarInformeYearMarcGuti(const vector<esperanzaVida>& lista, int year) {
    bool hayDatos = false;
    
    ofstream fout("informe_life_expectancy.txt");
    
    fout << "	 INFORME DE ESPERANZA DE VIDA DEL " << year << " 	" << endl;
    
    for (int i = 0; i < lista.size(); i++) {
        if (lista[i].year == year) {
            fout << lista[i].pais << " (" << lista[i].codigo << "): " << lista[i].esperanza << " años." << endl;
            hayDatos = true;
        }
    }

    if (!hayDatos) {
        cout << "No se han encontrado datos en este año para realizar el informe." << endl;
    }
}

void PorcentajeCrecimientoMarcGuti(vector<esperanzaVida>& lista, string codigo, int a1, int a2) {
    double porcentaje, v1, v2;

    v1 = BuscarMarcGuti(lista, codigo, a1);
    v2 = BuscarMarcGuti(lista, codigo, a2);
	
    if (lista[v1].esperanza != -1.0 && lista[v2].esperanza != -1.0) {
        // Formula del percentatge: ((Vfinal - Vinicial) / Vinicial) * 100
        porcentaje = ((lista[v2].esperanza - lista[v1].esperanza) / lista[v1].esperanza) * 100;
        if (porcentaje < 0){
        	cout << "La esperanza de vida en " << codigo << " ha decrecido en un " << -porcentaje << "% entre " << a1 << " y " << a2 << "." << endl;
		}
		else if (porcentaje == 0){
			cout << "La esperanza de vida en " << codigo << " se ha mantenido estable (" << porcentaje << "%) entre " << a1 << " y " << a2 << "." << endl;
		}
		else{
			cout << "La esperanza de vida en " << codigo << " ha crecido en un " << porcentaje << "% entre " << a1 << " y " << a2 << "." << endl;
		}
    } else {
        cout << "Error: No se han encontrado datos para uno de los años especificados." << endl;
    }
}

void tablaEvoMarcGuti(vector<esperanzaVida>& lista, int a1, int a2) {
    tMatrizEvo matriz;
    string codigos[5];
    int numYears, valorEsperanza;

    cout << "	 CONFIGURACION DE LA TABLA COMPARATIVA" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "Introduce el codigo del pais " << i + 1 << ": ";
        cin >> codigos[i];
    }

    numYears = a2 - a1 + 1;

    if (numYears > 100 || numYears <= 0) {
        cout << "Error: El rango de años debe de ser entre 1 i 100." << endl;
        return;
    }

    for (int f = 0; f < 5; f++) {
        for (int c = 0; c < numYears; c++) {
			valorEsperanza = BuscarMarcGuti(lista, codigos[f], a1 + c);
			matriz[f][c] = lista[valorEsperanza].esperanza;
        }
    }

    cout << endl << "	EVOLUCION DE LA ESPERANZA DE VIDA (" << a1 << "-" << a2 << ")" << endl;
    
    cout << "ISO  |";
    for (int j = 0; j < numYears; j++) {
        cout << "  " << a1 + j << "  |";
    }
	 cout << endl;
    for (int f = 0; f < 5; f++) {
        cout << codigos[f] << "  |";
        for (int c = 0; c < numYears; c++) {
            if (matriz[f][c] != -1.0) {
                cout << matriz[f][c] << " |";

            } else {
                cout << "  N/D   |";
            }
        }
        cout << endl;
    }
}

void programaMarcGuti(vector<esperanzaVida>& listaDatos) {  
	string isoPaisBuscar;
	int menu, yearBuscar, intervalo1, intervalo2;
	
	menu = 0;
	
	while(menu != 10){
		system("cls");
		MenuMarcGuti();
		cin>> menu;
		if (menu == 1){
			system("cls");
			isoPaisBuscar = IsoSelecMarcGuti();
		    yearBuscar = YearSelecMarcGuti();
			AltaMarcGuti(listaDatos, isoPaisBuscar, yearBuscar);
			PausaMarcGuti();
		}
		else if (menu == 2){
			system("cls");
			isoPaisBuscar = IsoSelecMarcGuti();
		    yearBuscar = YearSelecMarcGuti();
			BajaMarcGuti(listaDatos, isoPaisBuscar, yearBuscar);
			PausaMarcGuti();
		}
		else if (menu == 3){
			system("cls");
			isoPaisBuscar = IsoSelecMarcGuti();
		    yearBuscar = YearSelecMarcGuti();
		    
		    int encontrado = BuscarMarcGuti(listaDatos, isoPaisBuscar, yearBuscar);
		
		    if (encontrado != -1) {
		        cout << "Resultado busqueda: La esperanza en " << isoPaisBuscar << " el año " << yearBuscar << " era de " << listaDatos[encontrado].esperanza << endl << endl;
		    } else {
		        cout << "No se ha encontrado registro de " << isoPaisBuscar << " el año " << yearBuscar << endl << endl;
		    }
			PausaMarcGuti();
		}
		else if (menu == 4){
			system("cls");
			isoPaisBuscar = IsoSelecMarcGuti();
		    yearBuscar = YearSelecMarcGuti();
			ModificarMarcGuti(listaDatos, isoPaisBuscar, yearBuscar);
			PausaMarcGuti();
		}
		else if (menu == 5){
			system("cls");
			MinMaxHistoricoMarcGuti(listaDatos);
			PausaMarcGuti();
		}
		else if (menu == 6){
			system("cls");
		    yearBuscar = YearSelecMarcGuti();
			MaxMinPorYearMarcGuti(listaDatos, yearBuscar);
			PausaMarcGuti();
		}
		else if (menu == 7){
			system("cls");
			yearBuscar = YearSelecMarcGuti();
			GenerarInformeYearMarcGuti(listaDatos, yearBuscar);
			PausaMarcGuti();
		}
		else if (menu == 8){
			system("cls");
			isoPaisBuscar = IsoSelecMarcGuti();
			IntervaloSelecMarcGuti(intervalo1, intervalo2);
			PorcentajeCrecimientoMarcGuti(listaDatos, isoPaisBuscar, intervalo1, intervalo2);
			PausaMarcGuti();	
		}
		else if (menu == 9){
			system("cls");
			IntervaloSelecMarcGuti(intervalo1, intervalo2);
			while (intervalo2-intervalo1 > 10){
				system("cls");
				cout << "Para la correcta visualizacion de los datos, el intervalo no pude exceder los 10 años" << endl;
				PausaMarcGuti();
				system("cls");
				IntervaloSelecMarcGuti(intervalo1, intervalo2);
			}
			system("cls");
			tablaEvoMarcGuti(listaDatos, intervalo1, intervalo2);
			PausaMarcGuti();	
		}
		else if (menu == 10){
			system("cls");
			GuardarFicheroMarcGuti(listaDatos);
			cout << "Saliendo del programa... " << endl;
		}
	}	
}

int buscar_por_paisMarcPuig(const vector<Registro>& v) {
    string pais_buscado;
    cout << "Introduce el nombre del pais que quieres buscar: ";
    cin >> pais_buscado;

    for (int i = 0; i < v.size(); i++) {
        if (v[i].pais == pais_buscado) {
            return i;
        }
    }
    return -1;
}

void modificar_valorMarcPuig(vector<Registro>& v) {
    string pais_modificar;
    cout << "Introduce el nombre del pais que quieres modificar: ";
    cin >> pais_modificar;

    int pos = -1;
    for (int i = 0; i < v.size(); i++) {
        if (v[i].pais == pais_modificar) {
            pos = i;
        }
    }

    if (pos != -1) {
        double nuevo_valor;
        cout << "Valor actual de " << v[pos].pais << " es " << v[pos].valor << endl;
        cout << "Introduce el nuevo valor: ";
        cin >> nuevo_valor;
        v[pos].valor = nuevo_valor;
        cout << "Valor modificado correctamente." << endl;
    } else {
        cout << "El pais no se encuentra en la base de datos." << endl;
    }
}

void borrar_registroMarcPuig(vector<Registro>& v) {
    string pais_borrar;
    cout << "Introduce el nombre del pais que quieres borrar: ";
    cin >> pais_borrar;

    int pos = -1;
    for (int i = 0; i < v.size(); i++) {
        if (v[i].pais == pais_borrar) {
            pos = i;
        }
    }

    if (pos != -1) {
        for (int i = pos; i < v.size() - 1; i++) {
            v[i] = v[i + 1];
        }
        v.pop_back();
        cout << "Registro eliminado correctamente." << endl;
    } else {
        cout << "El pais no se encuentra en la base de datos." << endl;
    }
}

double valor_maximoMarcPuig(const vector<Registro>& v) {
    double ma = v[0].valor;
    for (int i = 0; i < v.size(); i++) {
        if (v[i].valor > ma) ma = v[i].valor;
    }
    return ma;
}

double valor_minimoMarcPuig(const vector<Registro>& v) {
    double mi = v[0].valor;
    for (int i = 0; i < v.size(); i++) {
        if (v[i].valor < mi) mi = v[i].valor;
    }
    return mi;
}

double calcular_mediaMarcPuig(const vector<Registro>& v) {
    double suma = 0;
    for (int i = 0; i < v.size(); i++) {
        suma = suma + v[i].valor;
    }
    return suma / v.size();
}

int contar_por_continenteMarcPuig(const vector<Registro>& v) {
    string cont_buscado;
    cout << "Introduce el continente para contar sus registros (ej. Asia): ";
    cin >> cont_buscado;

    int cont = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i].continente == cont_buscado) cont++;
    }
    return cont;
}

void mostrar_por_anyMarcPuig(const vector<Registro>& v) {
    int any_buscado;
    cout << "Introduce el any que quieres filtrar para ver sus datos: ";
    cin >> any_buscado;

    for (int i = 0; i < v.size(); i++) {
        if (v[i].any == any_buscado) {
            cout << v[i].pais << " " << v[i].valor << endl;
        }
    }
}

void programaMarcPuig(vector<Registro>& v_datos) {
    
    int opcion = 0;
    

    while (opcion != 8) {
		cout<<"PIB per capita" << endl << endl;
        cout << " MENU PRINCIPAL " << endl;
        cout << "1. Cargar fichero de datos" << endl;
        cout << "2. Buscar posicion de un pais" << endl;
        cout << "3. Modificar valor de un pais" << endl;
        cout << "4. Borrar un registro de pais" << endl;
        cout << "5. Mostrar estadisticas (Max, Min, Media)" << endl;
        cout << "6. Contar registros por continente" << endl;
        cout << "7. Mostrar registros de un any" << endl;
        cout << "8. Salir del programa" << endl;
        cout << "Seleccione una opcion (1-8): ";
        cin >> opcion;


        switch (opcion) {
            case 1:
            	system("cls");
                break;

            case 2:
            	system("cls");
                if (v_datos.size() > 0) {
                    int pos = buscar_por_paisMarcPuig(v_datos);
                    if (pos != -1) {
                        cout << "Encontrado en el indice: " << pos << " | Valor: " << v_datos[pos].valor << endl;
                    } else {
                        cout << "No se ha encontrado el pais." << endl;
                    }
            } else cout << "Base de datos vacia. Cargue el fichero primero (Opcion 1)." << endl;
                break;

            case 3:
            	system("cls");
                if (v_datos.size() > 0) {
                    modificar_valorMarcPuig(v_datos);
                } else cout << "Base de datos vacia. Cargue el fichero primero (Opcion 1)." << endl;
                    break;

            case 4:
            	system("cls");
                if (v_datos.size() > 0) {
                    borrar_registroMarcPuig(v_datos);
                } else cout << "Base de datos vacia. Cargue el fichero primero (Opcion 1)." << endl;
                    break;

            case 5:
            	system("cls");
                if (v_datos.size() > 0) {
                    cout << "Valor mas alto: " << valor_maximoMarcPuig(v_datos) << endl;
                    cout << "Valor mas bajo: " << valor_minimoMarcPuig(v_datos) << endl;
                    cout << "Media de valores: " << calcular_mediaMarcPuig(v_datos) << endl;
                } else cout << "Base de datos vacia. Cargue el fichero primero (Opcion 1)." << endl;
                    break;

            case 6:
            	system("cls");
                if (v_datos.size() > 0) {
                    int total_c = contar_por_continenteMarcPuig(v_datos);
                    cout << "Total de registros en ese continente: " << total_c << endl;
                } else cout << "Base de datos vacia. Cargue el fichero primero (Opcion 1)." << endl;
                    break;

            case 7:
            	system("cls");
                if (v_datos.size() > 0) {
                    mostrar_por_anyMarcPuig(v_datos);
                } else cout << "Base de datos vacia. Cargue el fichero primero (Opcion 1)." << endl;
                    break;

            case 8:
            	system("cls");
                cout << "Saliendo de la aplicacion..." << endl;
                break;

            default:
            	system("cls");
                cout << "Opcion incorrecta. Introduzca un numero del 1 al 8." << endl;
                break;
        }
    }
}

//agregar busquedas complejas

void MenuEnric();
int busquedaEnric(vector<poblacion> lista);
void altaEnric(vector<poblacion>& lista);
void baixaEnric(vector<poblacion>& lista);
void mostrarBusquedaEnric(vector<poblacion> lista);
void modificarEnric(vector<poblacion>& lista);
void minMaxEnric(vector<poblacion> lista);
void evolucionPaisEnric(vector<poblacion> lista);
void crecimientoPaisEnric(vector<poblacion> lista);
void guardarFicheroEnric(vector<poblacion> lista);
// el menu debe ser un recorrido
// si es un recorrido no hace falta el trobat
// mejorar algunas funcinalidades y que incluyan varias entidades
// mejorar lasconsultas y mensajes de error
void programaEnric(vector<poblacion>& listaDatos) {
    int menu = 0;

    cout << "Datos cargados: " << listaDatos.size() << endl;

    MenuEnric();
    cin >> menu;

    if (menu == 1) {
    	system("cls");
        altaEnric(listaDatos);
        guardarFicheroEnric(listaDatos);
        }

    else if (menu == 2) {
    	system("cls");
        baixaEnric(listaDatos);
        guardarFicheroEnric(listaDatos);
        }

    else if (menu == 3) {
    	system("cls");
        mostrarBusquedaEnric(listaDatos);
        }

    else if (menu == 4) {
    	system("cls");
        modificarEnric(listaDatos);
        guardarFicheroEnric(listaDatos);
        }

    else if (menu == 5) {
    	system("cls");
        minMaxEnric(listaDatos);
        }

    else if (menu == 6) {
    	system("cls");
        evolucionPaisEnric(listaDatos);
        }

    else if (menu == 7) {
    	system("cls");
        crecimientoPaisEnric(listaDatos);
        }

    else {
    	system("cls");
        cout << "Saliendo del programa..." << endl;
        }

    system("pause");
}

// agregar breve descripcion en cada subprograma,autor y fecha

void MenuEnric() {
    cout << "Desarrollo global y poblacion mundial" << endl;
    cout << " MENU " << endl;
    cout << "1. DAR DE ALTA UN DATO" << endl;
    cout << "2. DAR DE BAJA UN DATO" << endl;
    cout << "3. BUSCAR UN DATO" << endl;
    cout << "4. MODIFICAR UN DATO" << endl;
    cout << "5. ESTADISTICAS DE VALORES MAXIMOS Y MINIMOS" << endl;
    cout << "6. MOSTRAR EVOLUCION DE UN PAIS" << endl;
    cout << "7. CRECIMIENTO ENTRE DOS ANYOS" << endl;
    cout << "8. PULSA CUALQUIER OTRA TECLA PARA SALIR" << endl;
    }

int busquedaEnric(vector<poblacion> lista) {
    cout << "Introduce el codigo del pais que quieres buscar: " << endl;
    string codigoB;
    cin >> codigoB;

    cout << "Introduce el anyo que quieres buscar: " << endl;
    int anyB;
    cin >> anyB;

    bool trobat = false;
    int dim = lista.size();
    int i = 0;
    while(!trobat && i < dim) {
        if (lista[i].codigo == codigoB && lista[i].any == anyB) {
            trobat = true;
            return i;
            }
        i++;
        }

    return -1;
}

void altaEnric(vector<poblacion>& lista) {
    poblacion p;

    cout << "Introduce el nombre del pais, el codigo, el anyo y los habitantes: " << endl;
    cin >> p.pais >> p.codigo >> p.any >> p.habitantes;

    lista.push_back(p);

    cout << "Registro anyadido correctamente." << endl;
    }

void baixaEnric(vector<poblacion>& lista) {
    int dim = lista.size();
    int pos = busquedaEnric(lista);

    if (pos == -1) {
        cout << "No se ha encontrado el registro." << endl;
        }
    else {
        for (int i = pos; i < dim - 1; i++) {
        lista[i] = lista[i + 1];
        }

        lista.pop_back();

        cout << "Registro eliminado correctamente." << endl;
    }
}

void mostrarBusquedaEnric(vector<poblacion> lista) {
    int pos = busquedaEnric(lista);

    if (pos == -1) {
        cout << "No se ha encontrado el registro." << endl;
        }
    else {
        cout << "Pais: " << lista[pos].pais << endl;
        cout << "Codigo: " << lista[pos].codigo << endl;
        cout << "Anyo: " << lista[pos].any << endl;
        cout << "Habitantes: " << lista[pos].habitantes << endl;
        }
}

void modificarEnric(vector<poblacion>& lista) {
    int pos = busquedaEnric(lista);

    if (pos == -1) {
        cout << "No se ha encontrado el registro." << endl;
        }
    else {
        cout << "Introduce la nueva poblacion: " << endl;
        cin >> lista[pos].habitantes;

        cout << "Registro modificado correctamente." << endl;
    }
}

void minMaxEnric(vector<poblacion> lista) {
    int posMax = 0;
    int posMin = 0;
    int dim = lista.size();

    if (dim == 0) {
        cout << "No hay datos cargados." << endl;
        }
    else {
        for (int i = 1; i < dim; i++) {
        if (lista[i].habitantes > lista[posMax].habitantes) {
        posMax = i;
        }

        if (lista[i].habitantes < lista[posMin].habitantes) {
            posMin = i;
        }
    }

        cout << "VALOR MAXIMO: " << endl;
        cout << lista[posMax].pais << " " << lista[posMax].codigo << " ";
        cout << lista[posMax].any << " " << lista[posMax].habitantes << endl;

        cout << "VALOR MINIMO: " << endl;
        cout << lista[posMin].pais << " " << lista[posMin].codigo << " ";
        cout << lista[posMin].any << " " << lista[posMin].habitantes << endl;
        }
}

void evolucionPaisEnric(vector<poblacion> lista) {
    cout << "Introduce el codigo del pais: " << endl;
    string codigoB;
    cin >> codigoB;

    bool trobat = false;
    int dim = lista.size();

    for (int i = 0; i < dim; i++) {
        if (lista[i].codigo == codigoB) {
            cout << lista[i].any << " -> " << lista[i].habitantes << endl;
            trobat = true;
        }
    }

    if (!trobat) {
        cout << "No se han encontrado datos de este pais." << endl;
        }
}

void crecimientoPaisEnric(vector<poblacion> lista) {
    cout << "Introduce el codigo del pais: " << endl;
    string codigoB;
    cin >> codigoB;

    cout << "Introduce el anyo inicial: " << endl;
    int anyInicial;
    cin >> anyInicial;

    cout << "Introduce el anyo final: " << endl;
    int anyFinal;
    cin >> anyFinal;

    bool trobatInicial = false;
    bool trobatFinal = false;
    int poblacionInicial = 0;
    int poblacionFinal = 0;
    int dim = lista.size();
    int i = 0;
    while(i < dim) {
        if (lista[i].codigo == codigoB && lista[i].any == anyInicial) {
            poblacionInicial = lista[i].habitantes;
            trobatInicial = true;
        }

        if (lista[i].codigo == codigoB && lista[i].any == anyFinal) {
            poblacionFinal = lista[i].habitantes;
            trobatFinal = true;
        }
        i++;
        }

    if (trobatInicial && trobatFinal) {
        cout << "Poblacion inicial: " << poblacionInicial << endl;
        cout << "Poblacion final: " << poblacionFinal << endl;
        cout << "Crecimiento: " << poblacionFinal - poblacionInicial << endl;
        }
    else {
    cout << "No se han encontrado todos los datos necesarios." << endl;
    }
}

void guardarFicheroEnric(vector<poblacion> lista) {
    ofstream fout("population_modificado.txt");
    int dim = lista.size();

    for (int i = 0; i < dim; i++) {
        fout << lista[i].pais << " ";
        fout << lista[i].codigo << " ";
        fout << lista[i].any << " ";
        fout << lista[i].habitantes << endl;
    }

    fout.close();

    cout << "Datos guardados correctamente." << endl;
}

//BUSQUEDA AMB WHILE
int BuscarPIB(const vector<Registro>& v, string iso, int any) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i].codigo == iso && v[i].any == any) return i;
    }
    return -1;
}

// Cerca en el vector de Poblacio BUSQUEDA AMB WHILE
int BuscarPob(const vector<poblacion>& v, string iso, int any) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i].codigo == iso && v[i].any == any) return i;
    }
    return -1;
}

void CalcularPIBTotal(const vector<Registro>& vPIB, const vector<poblacion>& vPob) {
    string isoPaisBuscar;
    int yearBuscar;
    
	isoPaisBuscar = IsoSelecMarcGuti();
	yearBuscar = YearSelecMarcGuti();
	
    int posPIB = BuscarPIB(vPIB, isoPaisBuscar, yearBuscar);
    int posPob = BuscarPob(vPob, isoPaisBuscar, yearBuscar);

    if (posPIB != -1 && posPob != -1) {
        double total = vPIB[posPIB].valor * vPob[posPob].habitantes;
        cout << "El PIB Total de " << isoPaisBuscar << " l'year " << yearBuscar << " va ser de: " << total << " USD." << endl;
    } else {
        cout << "Dades no trobades en un dels fitxers." << endl;
    }
}

void DetectarParadojasSalud(const vector<esperanzaVida>& vEsp, const vector<Registro>& vPIB, int year) {
    double sumaPIB = 0;
    int comptador = 0;
    for (int i = 0; i < vPIB.size(); i++) {
        if (vPIB[i].any == year) {
            sumaPIB += vPIB[i].valor;
            comptador++;
        }
    }
    double mitjanaPIB = (comptador > 0) ? (sumaPIB / comptador) : 0;

    cout << "--- PAISOS AMB SISTEMA DE SALUT EFICIENT (" << year << ") ---" << endl;
    for (int i = 0; i < vEsp.size(); i++) {
        if (vEsp[i].year == year && vEsp[i].esperanza > 80.0) {
            int posPIB = BuscarPIB(vPIB, vEsp[i].codigo, year);
            if (posPIB != -1 && vPIB[posPIB].valor < mitjanaPIB) {
                cout << "- " << vEsp[i].pais << ": Esperanca " << vEsp[i].esperanza << " years (PIB: " << vPIB[posPIB].valor << ")" << endl;
            }
        }
    }
}

void EsperanzaPonderadaMundial(const vector<esperanzaVida>& vEsp, const vector<poblacion>& vPob, int year) {
    double sumaPonderada = 0;
    long long sumaPoblacio = 0;

    for (int i = 0; i < vEsp.size(); i++) {
        if (vEsp[i].year == year) {
            int posPob = BuscarPob(vPob, vEsp[i].codigo, year);
            if (posPob != -1) {
                sumaPonderada += (vEsp[i].esperanza * vPob[posPob].habitantes);
                sumaPoblacio += vPob[posPob].habitantes;
            }
        }
    }

    if (sumaPoblacio > 0) {
        cout << "L'esperanca de vida ponderada mundial l'year " << year << " va ser de: " << (sumaPonderada / sumaPoblacio) << " years." << endl;
    } else {
        cout << "No s'han trobat dades per a l'year " << year << "." << endl;
    }
}

void MejorPaisBienestar(const vector<esperanzaVida>& vEsp, const vector<Registro>& vPIB, const vector<poblacion>& vPob, int year) {
    int posMillor = -1;
    double maxRatio = -1;

    for (int i = 0; i < vEsp.size(); i++) {
        if (vEsp[i].year == year) {
            int posPIB = BuscarPIB(vPIB, vEsp[i].codigo, year);
            int posPob = BuscarPob(vPob, vEsp[i].codigo, year);

            if (posPIB != -1 && posPob != -1 && vPob[posPob].habitantes > 10000000) {
                // Ratio simple: (PIB / 1000) + Esperança
                double ratio = (vPIB[posPIB].valor / 1000.0) + vEsp[i].esperanza;
                if (ratio > maxRatio) {
                    maxRatio = ratio;
                    posMillor = i;
                }
            }
        }
    }

    if (posMillor != -1) {
        cout << "El país destacat l'year " << year << " (pobl > 10M) es: " << vEsp[posMillor].pais << endl;
    }
}

void InformeGigantesDemo(const vector<esperanzaVida>& vEsp, const vector<Registro>& vPIB, const vector<poblacion>& vPob, int year) {
    double llindar;
    cout << "Introdueix llindar de poblacio (ex. 100000000): "; cin >> llindar;

    cout << "\nPAIS | POBLACIO | PIB PER CAPITA | ESPERANCA" << endl;
    cout << "---------------------------------------------------" << endl;
    for (int i = 0; i < vPob.size(); i++) {
        if (vPob[i].any == year && vPob[i].habitantes > llindar) {
            int posEsp = BuscarMarcGuti(vEsp, vPob[i].codigo, year);
            int posPIB = BuscarPIB(vPIB, vPob[i].codigo, year);
            
            if (posEsp != -1 && posPIB != -1) {
                cout << vPob[i].codigo << " | " << vPob[i].habitantes << " | " << vPIB[posPIB].valor << " | " << vEsp[posEsp].esperanza << endl;
            }
        }
    }
}

void GenerarMatrizRiquezaLongevidad(const vector<esperanzaVida>& vEsp, const vector<Registro>& vPIB, const vector<poblacion>& vPob, int year) {
    tMatriuPoblacio matriu;

    for (int i = 0; i < vPob.size(); i++) {
        if (vPob[i].any == year) {
            int posPIB = BuscarPIB(vPIB, vPob[i].codigo, year);
            int posEsp = BuscarMarcGuti(vEsp, vPob[i].codigo, year);

            if (posPIB != -1 && posEsp != -1) {
                int f, c;
                // Determinació de fila (Rangs PIB)
                if (vPIB[posPIB].valor < 5000) f = 0;
                else if (vPIB[posPIB].valor < 15000) f = 1;
                else if (vPIB[posPIB].valor < 35000) f = 2;
                else f = 3;

                // Determinació de columna (Rangs Esperança)
                if (vEsp[posEsp].esperanza < 60) c = 0;
                else if (vEsp[posEsp].esperanza < 70) c = 1;
                else if (vEsp[posEsp].esperanza < 80) c = 2;
                else c = 3;

                matriu[f][c] += vPob[i].habitantes; // Suma de població a la cel·la
            }
        }
    }

    cout << "\nMATRIU DE DISTRIBUCIO DE POBLACIO MUNDIAL (" << year << ")" << endl;
    cout << "Rangs: PIB (Files) / Esperanca (Cols)" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << matriu[i][j] << endl;
        }
        cout << endl;
    }
}

int main () {
	vector<esperanzaVida> listaDatosEsp;
	vector<Registro> v_datos;
	vector<poblacion> listaDatosPob;
	
	CargarFichero(listaDatosEsp, v_datos, listaDatosPob);
	
	int op, yearBuscar; 
	
	op = 0;

    while (op != 10) {
		cout<<"Desarollo global y bienestar social" << endl << endl;
        cout << "MENU GENERAL	" << endl;
        cout << "1. Esperanza de vida"<< endl;
        cout << "2. PIB"<< endl;
        cout << "3. Poblacion"<< endl;
        cout << "Analisis de datos:"<< endl;
        cout << "4. PIB Total de un pais en año concreto"<< endl;
        cout << "5. Paradojas de salud"<< endl;
        cout << "6. Esperanza de vida ponderada"<< endl;
        cout << "7. Ranking de bienestar"<< endl;
        cout << "8. Informe de gigantes demograficos"<< endl;
        cout << "9. Matriz Riqueza vs Longevidad"<< endl;
        cout << "10. Salir"<< endl;

        cin >> op;

        if (op == 1){
        	system("cls");
        	programaMarcGuti(listaDatosEsp);
		} 
        else if (op == 2){
        	system("cls");
        	programaMarcPuig(v_datos);
		} 
        else if (op == 3){
        	system("cls");
			programaEnric(listaDatosPob);
		}
		else if (op == 4){
        	system("cls");
			CalcularPIBTotal(v_datos, listaDatosPob);
			PausaMarcGuti();
		}
		else if (op == 5){
        	system("cls");
			yearBuscar = YearSelecMarcGuti();
			DetectarParadojasSalud(listaDatosEsp, v_datos, yearBuscar);
			PausaMarcGuti();
		}
		else if (op == 6){
        	system("cls");
        	yearBuscar = YearSelecMarcGuti();
			EsperanzaPonderadaMundial(listaDatosEsp, listaDatosPob, yearBuscar);
			PausaMarcGuti();
		}
		else if (op == 7){
        	system("cls");
        	yearBuscar = YearSelecMarcGuti();
			MejorPaisBienestar(listaDatosEsp, v_datos, listaDatosPob, yearBuscar);
			PausaMarcGuti();
		}
		else if (op == 8){
        	system("cls");
        	yearBuscar = YearSelecMarcGuti();
			InformeGigantesDemo(listaDatosEsp, v_datos, listaDatosPob, yearBuscar);
			PausaMarcGuti();
		}
		else if (op == 9){
        	system("cls");
        	yearBuscar = YearSelecMarcGuti();
			GenerarMatrizRiquezaLongevidad(listaDatosEsp, v_datos, listaDatosPob, yearBuscar);
			PausaMarcGuti();
		}
		else if (op == 10){
			system("cls");
			cout << "Saliendo del programa... " << endl;
		} 
    }

    return 0;
}

