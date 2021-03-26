typedef string password<32>;

program CIFRADORPROG {
        version CIFRADORVER {
            string cifrarfinal(string password) = 1;
            string descifrarfinal(string password) = 2;
        } = 1;
} = 0x20000001;