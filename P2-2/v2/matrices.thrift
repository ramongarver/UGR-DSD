exception InvalidOperation {
    1: string why,
}

typedef list<list<double>> Matrix

service Matrices {
    void ping(),

    Matrix sumarMatrices(1: Matrix m1, 2: Matrix m2) throws (1: InvalidOperation io),
    Matrix restarMatrices(1: Matrix m1, 2: Matrix m2) throws (1: InvalidOperation io),
    Matrix multiplicarMatrices(1: Matrix m1, 2: Matrix m2) throws (1: InvalidOperation io),
}