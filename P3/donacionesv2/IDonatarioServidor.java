import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.HashMap;

public interface IDonatarioServidor extends Remote {
    String getNombreDonatario() throws RemoteException;
    ArrayList<String> getNombreReplicas() throws RemoteException;

    int getNumeroRegistros() throws RemoteException;
    HashMap<Integer, Double> getRegistros() throws RemoteException;
    boolean estaRegistrado(int id) throws RemoteException;
    void confirmarRegistro(int id) throws RemoteException;

    void addDonacion(int id, double valorDonacion) throws RemoteException;
    double getSubtotal() throws RemoteException;

    IDonatarioServidor getReplica(String nombreReplica) throws RemoteException;
}