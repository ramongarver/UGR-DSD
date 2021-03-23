struct point {
    double x;
    double y;
    double z;
};

typedef double vect<32>;
typedef string password<32>;

program CALCULADORAPROG {
	version CALCULADORAVER {
		int sumar (int a, int b) = 1;
		int restar (int a, int b) = 2;
		int multiplicar (int a, int b) = 3;
		int dividir (int a, int b) = 4;
		int potencia (int a, int b) = 5;
		double raizcuadrada (double a) = 6;
		point transladar(point p, double x, double y, double z) = 7;
		point escalar(point p, double x, double y, double z) = 8;
		vect sumarVectores(vect v1, vect v2) = 9;
		vect restarVectores(vect v1, vect v2) = 10;
		vect multiplicarVectores(vect v1, vect v2) = 11;
		vect dividirVectores(vect v1, vect v2) = 12;
        string cifrar(string password) = 13;
		string descifrar(string password) = 14;
	} = 1;
} = 0x20000000;
