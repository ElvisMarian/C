
import java.util.ArrayList;

public class Management extends Department {

    public Management(ArrayList<Employee> employees, ArrayList<Job> job) {
        this.employers = employees;
        this.aviable_jobs = job;
    }

    @Override
    public double getTotalSalaryBudget() {
        double TotalSalaryBudget = 0;
        for (Employee e : this.employers) {
            TotalSalaryBudget += e.salariu - (e.salariu * 16) / 100;
        }
        return TotalSalaryBudget;
    }
}
