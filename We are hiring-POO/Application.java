

import java.util.ArrayList;
import java.util.List;

class Application {

    private final ArrayList<Company> company;
    private final ArrayList<User> users;

    private Application() {
        company = new ArrayList<>();
        users = new ArrayList<>();
    }

    public static Application getInstance() {
        return Lazy.application;
    }

    public ArrayList<Company> getCompanys() {
        return this.company;
    }

    public Company getCompany(String name) {
        for (int i = 0; i < this.company.size(); i++) {
            if (this.company.get(i).nume.equals(name))
                return this.company.get(i);
        }
        return null;
    }

    //functie care imi spune daca un user s-a angajat sau nu
    public boolean contain(User user) {
        for (User u : Application.getInstance().users)
            if (u.equals(user))
                return true;
        return false;
    }

    public void add(Company company) {
        this.company.add(company);
    }

    public void add(User user) {
        this.add(user);
    }

    public boolean remove(Company company) {
        for (int i = 0; i < this.company.size(); i++) {
            if (this.company.get(i).equals(company)) {
                this.company.remove(i);
                return true;
            }
        }
        return false;
    }

    public boolean remove(User user) {
        for (int i = 0; i < this.users.size(); i++) {
            if (this.users.get(i).equals(user)) {
                this.users.remove(i);
                return true;
            }
        }
        return false;
    }

    public ArrayList<Job> getJobs(List<String> companies) {
        ArrayList<Job> joburi = new ArrayList<>();
        for (String name_job : companies) {
            for (Company c : Application.getInstance().getCompanys()) {
                if (c.nume.equals(name_job)) {
                    for (Job job : c.getJobs()) {
                        joburi.add(job);
                    }
                }
            }
        }
        return joburi;
    }

    private static class Lazy {
        private static final Application application = new Application();
    }
}
