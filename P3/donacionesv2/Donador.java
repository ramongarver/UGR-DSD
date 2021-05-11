import java.rmi.*;
import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.net.MalformedURLException;
import java.lang.Math;
import java.util.Scanner;

public class Donador {
    public static void mostrarBienvenida() {
        System.out.println("--- Bienvenido al sistema de donaciones ---");
    }

    public static void mostrarMenuInicial() {
        System.out.println("||-- Login --||");
        System.out.println(
                "R - Registrarse\n" +
                "L - Logearse\n" +
                "S - Salir");
        System.out.print("¿Qué desea hacer?: ");
    }

    public static void mostrarMenuClienteLogeado() {
        System.out.println("||-- Acciones --||");
        System.out.println(
                "D - Donar\n" +
                "P - Consultar donaciones por mí\n" +
                "R - Consultar donaciones en réplica\n" +
                "C - Consultar donaciones totales\n" +
                "L - Cerrar sesión\n" +
                "S - Salir");
        System.out.print("¿Qué desea hacer?: ");
    }

    public static void main(String[] args) {
        // Creación e instalación del gestor de seguridad
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }

        try {
            Scanner scanner = new Scanner (System.in);
            int id = -1;
            boolean continuar = true;
            boolean logeado = false;
            String opcion = "";

            // Obtención de forma aleatoria el servidor en el que se va a realizar
            // la petición de registro
            String servidor = "donatario" + (int)((Math.random()*2)+1);

            // Creación del stub para el cliente
            Registry reg = LocateRegistry.getRegistry("127.0.0.1", 1099);
            IDonatarioCliente donatario = (IDonatarioCliente) reg.lookup(servidor);

            while (continuar) {
                mostrarBienvenida();
                mostrarMenuInicial();
                opcion = scanner.nextLine().toUpperCase();

                switch (opcion) {
                    case "R":
                        System.out.print("Introduzca el id con el que se quiere registrar: ");
                        id = Integer.parseInt(scanner.nextLine());
                        servidor = donatario.registrar(id);
                        if (servidor.substring(0, 2).equals("RE")) {
                            servidor = servidor.substring(2);
                            System.out.println("Ya registrado cliente " + id + " en " + servidor);
                        }
                        else {
                            System.out.println("Solicitando registro en: " + servidor);
                        }
                        break;
                    case "L":
                        System.out.print("Introduzca el id con el que se quiere logear: ");
                        id = Integer.parseInt(scanner.nextLine());
                        servidor = donatario.logear(id);
                        if (servidor.substring(0, 3).equals("NRE")) {
                            System.out.println("Cliente " + id + " no registrado");
                        }
                        else {
                            donatario = (IDonatarioCliente) reg.lookup(servidor);
                            logeado = true;
                            System.out.println("Logeado cliente " + id + " en " + servidor);
                        }
                        break;
                    case "S":
                        continuar = false;
                        break;
                }

                while (logeado) {
                    mostrarMenuClienteLogeado();
                    opcion = scanner.nextLine().toUpperCase();

                    switch (opcion) {
                        case "D":
                            // Obtención de forma aleatoria del valor de la donación
                            double donacion = Math.round((Math.random()*10)*100.0)/100.0;
                            // Donación
                            donatario.donar(id, donacion);
                            System.out.println("Donación realizada: " + donacion);
                            break;
                        case "P":
                            System.out.println("Total donado por mí: " + donatario.subtotalDonadoPor(id));
                            break;
                        case "R":
                            System.out.println("Subtotal donado en la réplica " + servidor + ": " + donatario.subtotalDonadoPor(id));
                            break;
                        case "C":
                            double totalDonado = donatario.totalDonado(id);
                            if (totalDonado == -1.0) {
                                System.out.println("No se puede obtener el total donado hasta que no se realice una donación");
                            }
                            else {
                                System.out.println("Total donado: " + totalDonado);
                            }
                            break;
                        case "L":
                            logeado = false;
                            break;
                        case "S":
                            logeado = false;
                            continuar = false;
                            break;
                    }
                }
            }
        } catch(NotBoundException | RemoteException e) {
            System.err.println("Exception del sistema: " + e);
        }
        System.exit(0);
    }
}