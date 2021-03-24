struct point {
    double x;
    double y;
    double z;
};

typedef double vect<32>;
typedef vect matrix<32>;

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

		vect sumarvectores(vect v1, vect v2) = 9;
		vect restarvectores(vect v1, vect v2) = 10;
		vect multiplicarvectores(vect v1, vect v2) = 11;
		vect dividirvectores(vect v1, vect v2) = 12;

		matrix sumarmatrices(matrix m1, matrix m2) = 13;
		matrix restarmatrices(matrix m1, matrix m2) = 14;
		matrix multiplicarmatrices(matrix m1, matrix m2) = 15;

        string cifrar(string password) = 16;
		string descifrar(string password) = 17;
	} = 1;
} = 0x20000000;
