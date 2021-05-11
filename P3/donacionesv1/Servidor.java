import java.rmi.*;
import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.net.MalformedURLException;

public class Servidor {
    public static void main(String[] args) {
        // Creación e instalación del gestor de seguridad
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }

        try {
            // Lanzamiento del ligador RMI
            Registry reg = LocateRegistry.createRegistry(1099);

            // Creación de dos instancias de Donatario
            Donatario donatario1 = new Donatario("donatario1", "donatario2");
            Donatario donatario2 = new Donatario("donatario2", "donatario1");

            // Registro de los objetos remotos en el ligador
            Naming.rebind("donatario1", donatario1);
            Naming.rebind("donatario2", donatario2);

            System.out.println("Servidor preparado");
        } catch (RemoteException | MalformedURLException e) {
            System.out.println("Exception: " + e.getMessage());
        }
    }
}