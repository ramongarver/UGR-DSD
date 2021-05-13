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
    private ArrayList<String> nombreReplicas; // Nombre de las réplicas

    // Constructor

    /**
     * Inicializar un objeto Donatario
     * @param nombreDonatario
     * @param nombreReplicas
     * @throws RemoteException
     */
    public Donatario(String nombreDonatario, ArrayList<String> nombreReplicas) throws RemoteException {
        super();
        this.subtotal = 0;
        this.registros = new HashMap<Integer, Double>();
        this.nombreDonatario = nombreDonatario;
        this.nombreReplicas = nombreReplicas;
    }

    // Métodos utilidades (no pertenecientes a ninguna interfaz)

    /**
     * Saber si un cliente identificado por id está registrado en el sistema y, en caso afirmativo, dónde
     * @param id del cliente
     * @return null si el cliente no está registrado en el sistema
     * @return referencia a la réplica en la que el cliente está registrado
     */
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

    /**
     * Obtener una referencia a la réplica con menor número de registros
     * @return replica con menor número de registros;
     * @throws RemoteException
     */
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

    /**
     * Obtener información de los clientes registrados en cada réplica en orden
     * @return clientesRegistrados
     */
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

    /**
     * Obtener la suma total de las donaciones del sistema, suma de las donaciones subtotales almacenadas en cada réplica
     * @return sumaSubtotales
     * @throws RemoteException
     */
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

    /**
     * Registrar a un cliente en la réplica correspondiente si no está registrado
     * @param id del cliente
     * @return nombreServidor REnombreDonatario si está registrado
     * @return nombreServidor nombreReplica si no está registrado
     * @throws RemoteException
     */
    public synchronized String registrar(int id) throws RemoteException {
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

    /**
     * Logear a un cliente en la réplica correspondiente si está registrado
     * @param id del cliente
     * @return nombreServidor nombreReplica si está registrado
     * @return nombreServidor NREnombreDonatario si no está registrado.
     * @throws RemoteException
     */
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

    /**
     * Donar una determinada cantidad si el cliente está registrado (exclusión mutua)
     * @param id del cliente
     * @param valorDonacion
     * @throws RemoteException
     */
    public synchronized void donar(int id, double valorDonacion) throws RemoteException {
        IDonatarioServidor replica = this.replicaRegistro(id);

        if (replica != null) {
            replica.addDonacion(id, valorDonacion);
            System.out.println("Realizada donación de " + valorDonacion + " por cliente " + id);
        }
        else {
            System.out.println("No se puede realizar la donación: Cliente no registrado");
        }
    }

    /**
     * Obtener el subtotal donado por un cliente determinado
     * @param id del cliente
     * @return cantidad donada por el cliente id
     * @throws RemoteException
     */
    public double subtotalDonadoPor(int id) throws RemoteException {
        System.out.println("Solicitado subtotal de donaciones realizadas por el cliente " + id + ": " + this.registros.get(id));
        return this.registros.get(id);
    }

    /**
     * Obtener el subtotal donado en la réplica en la que está registrado el cliente
     * @param id del cliente
     * @return subtotal
     * @throws RemoteException
     */
    public double subtotalDonado(int id) throws RemoteException {
        System.out.println("Solicitado subtotal de donaciones en " + this.nombreDonatario + ": " + this.subtotal);
        return this.subtotal;
    }

    /**
     * Obtener el total donado
     * @param id del cliente
     * @return Suma de los subtotales de las diferentes réplicas
     * @throws RemoteException
     */
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

    /**
     * Obtener el nombre del donatario
     * @return nombreDonatario
     * @throws RemoteException
     */
    public String getNombreDonatario() throws RemoteException {
        return this.nombreDonatario;
    }

    /**
     * Obtener el nombre de las réplicas
     * @return nombreReplicas
     * @throws RemoteException
     */
    public ArrayList<String> getNombreReplicas() throws RemoteException {
        return this.nombreReplicas;
    }

    /**
     * Obtener el número de registros
     * @return tamaño de registros
     * @throws RemoteException
     */
    public int getNumeroRegistros() throws RemoteException {
        return this.registros.size();
    }

    /**
     * Obtener los registros
     * @return registros
     * @throws RemoteException
     */
    public HashMap<Integer, Double> getRegistros() throws RemoteException {
        return this.registros;
    }

    /**
     * Saber si un cliente está registrado en la réplica
     * @param id del cliente
     * @return bool registros contiene la clave del cliente
     * @throws RemoteException
     */
    public boolean estaRegistrado(int id) throws RemoteException {
        return this.registros.containsKey(id);
    }

    /**
     * Confirmar registro de un cliente. Añadir cliente a registros
     * @param id del cliente
     * @throws RemoteException
     */
    public void confirmarRegistro(int id) throws RemoteException {
        this.registros.put(id, 0.0);
    }

    /**
     * Añadir valor donado al subtotal y actualizar el total donado del cliente
     * @param id del cliente
     * @param valorDonacion
     * @throws RemoteException
     */
    public void addDonacion(int id, double valorDonacion) throws RemoteException {
        this.subtotal += valorDonacion;
        this.registros.computeIfPresent(id, (key, val) -> val + valorDonacion);
    }

    /**
     * Obtener subtotal donado en la réplica
     * @return subtotal donado en la réplica
     * @throws RemoteException
     */
    public double getSubtotal() throws RemoteException {
        return this.subtotal;
    }

    /**
     * Obtener referencia a una réplica dado su nombre
     * @param nombreReplica
     * @return referencia a la réplica
     * @throws RemoteException
     */
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