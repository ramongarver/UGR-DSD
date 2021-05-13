import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IDonatarioCliente extends Remote {
    String registrar(int id) throws RemoteException;
    String logear(int id) throws RemoteException;

    void donar(int id, double valorDonacion) throws RemoteException;
    double subtotalDonadoPor(int id) throws RemoteException;
    double subtotalDonado(int id) throws RemoteException;
    double totalDonado(int id) throws RemoteException;
}