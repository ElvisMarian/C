
import java.util.ArrayList;

public class IT extends Department {
    public IT(ArrayList<Employee> employees, ArrayList<Job> job) {
        this.employers = employees;
        this.aviable_jobs = job;
    }

    @Override
    public double getTotalSalaryBudget() {
        double TotalSalaryBudget = 0;
        for (Employee e : this.employers) {
            TotalSalaryBudget += e.salariu;
        }
        return TotalSalaryBudget;
    }
}
