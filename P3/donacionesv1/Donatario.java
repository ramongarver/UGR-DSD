import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.server.UnicastRemoteObject;
import java.rmi.RemoteException;
import java.rmi.NotBoundException;
import java.net.MalformedURLException;
import java.util.HashMap;

public class Donatario extends UnicastRemoteObject implements IDonatarioCliente, IDonatarioServidor {
    // Atributos
    private double subtotal; // Valor total de donaciones realizadas al donatario
    private HashMap<Integer, Double> registros; // Clientes registrados en el donatario
    private String nombreDonatario; // Nombre del donatario
    private String nombreReplica; // Nombre de la réplica

    // Constructor
    public Donatario(String nombreDonatario, String nombreReplica) throws RemoteException {
        super();
        this.subtotal = 0;
        this.registros = new HashMap<Integer, Double>();
        this.nombreDonatario = nombreDonatario;
        this.nombreReplica = nombreReplica;
    }

    // Métodos de la interfaz IDonatarioCliente
    public String registrar(int id) throws RemoteException {
        IDonatarioServidor replica = this.getReplica(nombreReplica);
        String nombreServidor;

        if (this.estaRegistrado(id)) {
            System.out.println("El cliente " + id + " ya está registrado");
            nombreServidor = "RE" + this.nombreDonatario;
        }
        else if (replica.estaRegistrado(id)) {
            System.out.println("El cliente " + id + " ya está registrado");
            nombreServidor = "RE" + this.nombreReplica;
        }
        else if (this.getNumeroRegistros() <= replica.getNumeroRegistros()) {
            this.confirmarRegistro(id);
            System.out.println("Registrado cliente " + id + " en " + this.nombreDonatario);
            nombreServidor = this.nombreDonatario;
        }
        else {
            replica.confirmarRegistro(id);
            System.out.println("Registrado cliente " + id + " en " + this.nombreReplica);
            nombreServidor = this.nombreReplica;
        }

        System.out.println("Registrados en " + this.nombreDonatario + ": " + this.getNumeroRegistros());
        System.out.println("Registrados en " + this.nombreReplica + ": " + replica.getNumeroRegistros());

        return nombreServidor;
    }

    public String logear(int id) throws RemoteException {
        IDonatarioServidor replica = this.getReplica(nombreReplica);
        String nombreServidor;

        if (this.estaRegistrado(id)) {
            nombreServidor = this.nombreDonatario;
            System.out.println("Logeado cliente " + id + " en " + this.nombreDonatario);
        }
        else if (replica.estaRegistrado(id)) {
            nombreServidor = this.nombreReplica;
            System.out.println("Logeado cliente " + id + " en " + this.nombreReplica);
        }
        else {
            nombreServidor = "NRE" + this.nombreDonatario;
            System.out.println("Cliente " + id + " no registrado");
        }

        return nombreServidor;
    }

    public void donar(int id, double valorDonacion) throws RemoteException {
        IDonatarioServidor replica = this.getReplica(nombreReplica);
        if (this.estaRegistrado(id)) {
            this.addDonacion(id, valorDonacion);
            System.out.println("Realizada donación de " + valorDonacion + " por cliente " + id);
        }
        else if (replica.estaRegistrado(id)) {
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
        IDonatarioServidor replica = this.getReplica(nombreReplica);
        double totalDonado = -1.0;

        if (this.estaRegistrado(id)) {
            if (this.registros.get(id) > 0.0) {
                totalDonado = this.subtotal + this.getReplica(nombreReplica).getSubtotal();
                System.out.println("Solicitado total de donaciones: " + totalDonado);
            }
            else {
                System.out.println("No se puede consultar el total de donaciones: El cliente " + id + " no ha realizado ninguna donación");
            }
        }
        else if (replica.estaRegistrado(id)) {
            if (replica.getRegistros().get(id) > 0.0) {
                totalDonado = this.subtotal + this.getReplica(nombreReplica).getSubtotal();
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