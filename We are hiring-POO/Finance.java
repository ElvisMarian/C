
import java.util.ArrayList;

public class Finance extends Department {
    public Finance(ArrayList<Employee> employees, ArrayList<Job> job) {
        this.employers = employees;
        this.aviable_jobs = job;
    }

    @Override
    public double getTotalSalaryBudget() {
        double TotalSalaryBudget = 0;
        int xp_in_department;
        for (Employee e : this.employers) {
            //daca se afla in departamentul finance atunci ultimul
            // element adaugat in lista de experience este
            //pentru jobul din acel departament,deci iau data
            // de final-cea de inceput si aflu vechimea
            xp_in_department = e.resume.experience.get(0).sfarsit.getYear() - e.resume.experience.get(0).inceput.getYear();
            if (xp_in_department < 1)
                TotalSalaryBudget += e.salariu - e.salariu / 10;
            else
                TotalSalaryBudget += e.salariu - (e.salariu * 16) / 100;
        }
        return TotalSalaryBudget;
    }

    @Override
    public String toString() {
        return super.toString();
    }
}
