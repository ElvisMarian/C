
import java.util.ArrayList;

public class Marketing extends Department {
    public Marketing(ArrayList<Employee> employees, ArrayList<Job> job) {
        this.employers = employees;
        this.aviable_jobs = job;
    }

    @Override
    public double getTotalSalaryBudget() {
        double TotalSalaryBudget = 0;
        for (Employee e : this.employers) {
            if (e.salariu > 5000)
                TotalSalaryBudget += e.salariu - e.salariu / 10;
            else if (e.salariu < 3000) {
                TotalSalaryBudget += e.salariu;
            } else
                TotalSalaryBudget += e.salariu - (e.salariu * 16) / 100;
        }
        return TotalSalaryBudget;
    }
}
