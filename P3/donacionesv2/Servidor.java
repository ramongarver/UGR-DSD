import java.rmi.*;
import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.net.MalformedURLException;
import java.util.ArrayList;

public class Servidor {
    public static void main(String[] args) {
        // Creación e instalación del gestor de seguridad
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }

        try {
            // Lanzamiento del ligador RMI
            Registry reg = LocateRegistry.createRegistry(1099);

            // Número de donatarios
            int numeroDonatarios = Integer.parseInt(args[0]); // Número de donatarios

            // Asignación de un nombre a cada donatario
            ArrayList<String> donatariosNombres = new ArrayList<String>();
            for (int i = 0; i < numeroDonatarios; i++) {
                donatariosNombres.add("donatario" + i);
            }

            // Formación para cada donatario del vector con los nombres de los donatarios réplicas
            ArrayList<ArrayList<String>> donatariosReplicas = new ArrayList<ArrayList<String>>();
            for (int i = 0; i < numeroDonatarios; i++) {
                donatariosReplicas.add(new ArrayList<String>());
                for (int j = 0; j < numeroDonatarios; j++) {
                    if (!donatariosNombres.get(j).equals("donatario" + i)) {
                        donatariosReplicas.get(i).add("donatario" + j);
                    }
                }
            }

            // Formación del vector de donatarios y rebind de cada uno de ellos
            ArrayList<Donatario> donatarios = new ArrayList<Donatario>();
            for (int i = 0; i < numeroDonatarios; i++) {
                donatarios.add(new Donatario(donatariosNombres.get(i), donatariosReplicas.get(i)));
                Naming.rebind(donatariosNombres.get(i), donatarios.get(i));
            }

            System.out.println("Servidor preparado");
        } catch (RemoteException | MalformedURLException e) {
            System.out.println("Exception: " + e.getMessage());
        }
    }
}