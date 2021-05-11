import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.server.UnicastRemoteObject;
import java.rmi.RemoteException;
import java.rmi.NotBoundException;
import java.net.MalformedURLException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.TreeMap;

public class Donatario extends UnicastRemoteObject implements IDonatarioCliente, IDonatarioServidor {
    // Atributos
    private double subtotal; // Valor total de donaciones realizadas al donatario
    private HashMap<Integer, Double> registros; // Clientes registrados en el donatario
    private String nombreDonatario; // Nombre del donatario
    private ArrayList<String> nombreReplicas; // Nombre de la réplica

    // Constructor
    public Donatario(String nombreDonatario, ArrayList<String> nombreReplicas) throws RemoteException {
        super();
        this.subtotal = 0;
        this.registros = new HashMap<Integer, Double>();
        this.nombreDonatario = nombreDonatario;
        this.nombreReplicas = nombreReplicas;
    }

    public IDonatarioServidor replicaRegistro(int id) {
        IDonatarioServidor replica = null;
        boolean registrado = false;

        try {
            if (this.estaRegistrado(id)) {
                registrado = true;
                replica = this;
            } else {
                for (int i = 0; i < nombreReplicas.size() && !registrado; i++) {
                    replica = this.getReplica(nombreReplicas.get(i));
                    registrado = replica.estaRegistrado(id);
                }
            }
            if (!registrado)
                replica = null;
        }
        catch (RemoteException e) {
            System.out.println("Exception: " + e.getMessage());
        }

        return replica;
    }

    public IDonatarioServidor replicaMenorNumeroRegistros() throws RemoteException {
        IDonatarioServidor replica = this;
        IDonatarioServidor auxReplica = null;

        for (int i = 0; i < this.nombreReplicas.size(); i++) {
            auxReplica = replica.getReplica(replica.getNombreReplicas().get(i));
            if (replica.getNumeroRegistros() > auxReplica.getNumeroRegistros())
                replica = auxReplica;
        }

        return replica;
    }

    public TreeMap<String, ArrayList<Integer>> getClientesRegistrados() {
        TreeMap<String, ArrayList<Integer>> clientesRegistrados = new TreeMap<String, ArrayList<Integer>>(); // Nombre réplica - Registrados en réplica
        String nombre; // Nombre de cada réplica
        ArrayList<Integer> registrados; // Registrados en cada réplica
        IDonatarioServidor replica; // Referencia a la réplica

        try {
            for (int i = -1; i < this.nombreReplicas.size(); i++) {
                if (i == -1) {
                    nombre = this.getNombreDonatario();
                    replica = this;
                }
                else {
                    nombre = this.getNombreReplicas().get(i);
                    replica = this.getReplica(nombre);
                }
                registrados = new ArrayList<Integer>(replica.getRegistros().keySet());

                clientesRegistrados.put(nombre, registrados);
            }
        } catch (RemoteException e) {
            System.out.println("Exception: " + e.getMessage());
        }

        return clientesRegistrados;
    }

    public double getSumaSubtotales() throws RemoteException {
        IDonatarioServidor replica;
        double sumaSubtotales = 0.0;

        for (int i = -1; i < nombreReplicas.size(); i++) {
            if (i == -1) replica = this;
            else replica = this.getReplica(nombreReplicas.get(i));
            sumaSubtotales += replica.getSubtotal();
        }

        return sumaSubtotales;
    }

    // Métodos de la interfaz IDonatarioCliente
    public String registrar(int id) throws RemoteException {
        IDonatarioServidor replica = this.replicaRegistro(id);
        String nombreServidor;

        if (replica != null) {
            System.out.println("El cliente " + id + " ya está registrado");
            nombreServidor = "RE" + replica.getNombreDonatario();
        }
        else {
            replica = this.replicaMenorNumeroRegistros();
            replica.confirmarRegistro(id);
            System.out.println("Registrado cliente " + id + " en " + replica.getNombreDonatario());
            nombreServidor = replica.getNombreDonatario();
        }

        System.out.println(this.getClientesRegistrados());

        return nombreServidor;
    }

    public String logear(int id) throws RemoteException {
        IDonatarioServidor replica = this.replicaRegistro(id);
        String nombreServidor;

        if (replica != null) {
            nombreServidor = replica.getNombreDonatario();
            System.out.println("Logeado cliente " + id + " en " + replica.getNombreDonatario());
        }
        else {
            nombreServidor = "NRE" + this.getNombreDonatario();
            System.out.println("Cliente " + id + " no registrado");
        }

        return nombreServidor;
    }

    public void donar(int id, double valorDonacion) throws RemoteException {
        IDonatarioServidor replica = this.replicaRegistro(id);

        if (replica != null) {
            replica.addDonacion(id, valorDonacion);
            System.out.println("Realizada donación de " + valorDonacion + " por cliente " + id);
        }
        else {
            System.out.println("No se puede realizar la donación: Cliente no registrado");
        }
    }

    public double subtotalDonadoPor(int id) throws RemoteException {
        System.out.println("Solicitado subtotal de donaciones realizadas por el cliente " + id + ": " + this.registros.get(id));
        return this.registros.get(id);
    }

    public double subtotalDonado(int id) throws RemoteException {
        System.out.println("Solicitado subtotal de donaciones en " + this.nombreDonatario + ": " + this.subtotal);
        return this.subtotal;
    }

    public double totalDonado(int id) throws RemoteException {
        IDonatarioServidor replica = this.replicaRegistro(id);
        double totalDonado = -1.0;

        if (replica != null) {
            if (replica.getRegistros().get(id) > 0.0) {
                totalDonado = this.getSumaSubtotales();
                System.out.println("Solicitado total de donaciones: " + totalDonado);
            }
            else {
                System.out.println("No se puede consultar el total de donaciones: El cliente " + id + " no ha realizado ninguna donación");
            }
        }
        else {
            System.out.println("No se puede consultar el total de donaciones: Cliente no registrado");
        }

        return totalDonado;
    }

    // Métodos de la interfaz IDonatarioServidor
    public String getNombreDonatario() throws RemoteException {
        return this.nombreDonatario;
    }

    public ArrayList<String> getNombreReplicas() {
        return this.nombreReplicas;
    }

    public int getNumeroRegistros() throws RemoteException {
        return this.registros.size();
    }

    public HashMap<Integer, Double> getRegistros() {
        return this.registros;
    }

    public boolean estaRegistrado(int id) throws RemoteException {
        return this.registros.containsKey(id);
    }

    public void confirmarRegistro(int id) throws RemoteException {
        this.registros.put(id, 0.0);
    }

    public void addDonacion(int id, double valorDonacion) throws RemoteException {
        this.subtotal += valorDonacion;
        this.registros.computeIfPresent(id, (key, val) -> val + valorDonacion);
    }

    public double getSubtotal() throws RemoteException {
        return this.subtotal;
    }

    public IDonatarioServidor getReplica(String nombreReplica) throws RemoteException {
        IDonatarioServidor replica = null;

        try {
            Registry reg = LocateRegistry.getRegistry("127.0.0.1", 1099);
            replica = (IDonatarioServidor) reg.lookup(nombreReplica);
        } catch (NotBoundException | RemoteException e) {
            System.out.println("Exception: " + e.getMessage());
        }

        return replica;
    }
}