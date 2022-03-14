
import java.util.ArrayList;

class UserFactory {

    public static Department createUDepartment(String nume, ArrayList<Employee> employees, ArrayList<Job> job) {
        if (nume.equals("IT")) {
            return new IT(employees, job);
        }
        if (nume.equals("Management")) {
            return new Management(employees, job);

        } else if (nume.equals("Marketing")) {
            return new Marketing(employees, job);

        } else if (nume.equals("Finance")) {
            return new Finance(employees, job);
        }
        throw new IllegalArgumentException();
    }
}
