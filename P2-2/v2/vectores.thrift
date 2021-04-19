exception InvalidOperation {
    1: string why,
}

typedef list<double> Vector

service Vectores {
    void ping(),

	Vector sumarVectores(1: Vector v1, 2: Vector v2) throws (1: InvalidOperation io),
    Vector restarVectores(1: Vector v1, 2: Vector v2) throws (1: InvalidOperation io),
	Vector multiplicarVectores(1: Vector v1, 2: Vector v2) throws (1: InvalidOperation io),
    Vector dividirVectores(1: Vector v1, 2: Vector v2) throws (1: InvalidOperation io),
}