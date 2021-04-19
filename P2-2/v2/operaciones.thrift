struct Power {
    1: required i32 base,
    2: required i32 exponente,
}

enum Operation {
    SUMAR = 1,
    RESTAR = 2,
    MULTIPLICAR = 3,
    DIVIDIR = 4,
    POTENCIA = 5,
    RAIZ = 6,
}

struct Calculo {
    1: required i32 num1,
    2: optional i32 num2,
    3: required Operation operation,
    4: required double result = 0,
}

typedef list<Calculo> Calculos

struct Point {
    1: required double x,
    2: required double y,
    3: required double z,
}

exception InvalidOperation {
    1: string why,
}

service Operaciones {
	void ping(),

	i32 suma(1: i32 num1, 2: i32 num2),
	i32 resta(1: i32 num1, 2: i32 num2),
	i32 multiplicacion(1: i32 num1, 2: i32 num2),
	i32 division(1: i32 num1, 2: i32 num2) throws (1: InvalidOperation io),
	i32 potencia (1: Power p) throws (1: InvalidOperation io),
	double raizCuadrada(1: double num) throws (1: InvalidOperation io),

    Calculos resolverCalculos(1: Calculos calculos) throws (1: InvalidOperation io),

    Point transladar(1: Point p, 2: double x, 3: double y, 4: double z),
    Point escalar(1: Point p, 2: double x, 3: double y, 4: double z),
}