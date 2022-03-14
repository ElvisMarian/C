

import java.util.ArrayList;

class Company {
    String nume;
    Manager manager;
    ArrayList<Department> departments;
    ArrayList<Recruiter> recruiter;

    public Company(String nume, Manager manager, ArrayList<Department> departments, ArrayList<Recruiter> recruiter) {
        this.nume = nume;
        this.manager = manager;
        this.departments = departments;
        this.recruiter = recruiter;
    }

    public void add(Department department) {
        this.departments.add(department);
    }

    public void add(Recruiter recruiter) {
        this.recruiter.add(recruiter);
    }

    public void add(Employee employee, Department department) {
        department.employers.add(employee);
    }

    public void remove(Employee employee) {
        for (Department d : this.departments)
            for (Employee e : d.employers)
                if (e.equals(employee))
                    d.employers.remove(employee);
    }

    public void remove(Department department) {
        for (Department d : this.departments) {
            if (d.equals(department)) {
                department.employers.clear();
                this.remove(department);
                break;
            }
        }
    }

    public void remove(Recruiter recruiter) {
        for (Recruiter r : this.recruiter)
            if (r.equals(recruiter))
                this.recruiter.remove(recruiter);
    }

    public void move(Department source, Department destination) {
        for (Employee d1 : source.employers) {
            destination.employers.add((d1));
        }
        source.employers.clear();
    }

    public void move(Employee employee, Department newDepartment) {
        for (Department d : this.departments) {
            for (Employee e : d.employers)
                if (e.equals(employee))
                    d.employers.remove(employee);

            if (d.equals(newDepartment))
                d.employers.add(employee);
        }
    }

    public boolean contains(Department department) {
        for (Department d : this.departments)
            if (d.equals(department))
                return true;
        return false;
    }

    public boolean contains(Employee employee) {
        for (Department d : this.departments)
            for (Employee e : d.employers)
                if (e.equals(employee))
                    return true;
        return false;
    }

    public Recruiter getRecruiter(User user) {
        Recruiter potrivit = new Recruiter(null, 0);
        int maxim = -1;
        //caut in lista de recruiteri
        for (Recruiter r : this.recruiter) {
            //il caut pe cel mai departat
            if (maxim <= user.getDegreeInFriendship(r)) {
                if (maxim == user.getDegreeInFriendship(r)) {
                    if (potrivit.rating > r.rating)
                        continue;
                }
                maxim = user.getDegreeInFriendship(r);
                potrivit = r;
            }
        }
        return potrivit;
    }

    public ArrayList<Job> getJobs() {
        ArrayList<Job> job = new ArrayList<>();

        for (Department d : this.departments)
            for (Job j : d.aviable_jobs)
                if (j.aviable == true)
                    job.add(j);
        return job;
    }

    @Override
    public String toString() {
        return "Company{" +
                "nume='" + nume + '\'' +
                ", manager=" + manager +
                ", departments=" + departments +
                ", recruiter=" + recruiter +
                '}';
    }
}
