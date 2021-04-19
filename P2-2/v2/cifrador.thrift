service Cifrador {
	void ping(),

    string cifrar(1: string password)
    string descifrar(2: string password)
}