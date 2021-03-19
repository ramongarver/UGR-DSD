struct point {
    double x;
    double y;
    double z;
};

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
		point rotate(point p, double x_angle, double y_angle, double z_angle) = 9;
	} = 1;
} = 0x20000000;
