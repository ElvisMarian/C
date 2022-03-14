

public class Employee extends Consumer {
    String company;
    double salariu;

    Employee(String company, double salariu) {
        this.company = company;
        this.salariu = salariu;
    }

    Employee() {
        this.company = "Liber profesionist";
        this.salariu = 0.0;
    }

    @Override
    public String toString() {
        return "Employee{" +
                "company='" + company + '\'' +
                ", salariu=" + salariu +
                '}';
    }
}
