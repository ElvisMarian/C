

import java.util.ArrayList;

abstract class Department {
    ArrayList<Employee> employers;
    ArrayList<Job> aviable_jobs;

    public abstract double getTotalSalaryBudget();

    public ArrayList<Job> getJobs() {
        return this.aviable_jobs;
    }

    public void add(Employee employee) {
        this.employers.add(employee);
    }

    public void remove(Employee employee) {
        this.employers.remove(employee);
    }

    public void add(Job job) {
        this.aviable_jobs.add(job);
    }

    public ArrayList<Employee> getEmployees() {
        return this.employers;
    }
}
