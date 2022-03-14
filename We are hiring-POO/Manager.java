
import java.util.ArrayList;

public class Manager extends Employee {
    ArrayList<Request> cereri;

    public void process(Job job) {
        boolean aprobat = false;
        ArrayList<Request> selectat = new ArrayList<>();
        //selectez din lista cu cereri doar acele cereri ale caror useri doresc acel job si indeplinesc conditiile
        for (Request r : this.cereri) {
            if (job.equals(r.getKey())) {
                if (job.meetsRequirments((User) r.getValue1())) {
                    selectat.add(r);
                }
            }
        }
        //folosesc un bubble sort pentru a-mi sorta elementele din lista
        Request temp;
        for (int i = 0; i < (selectat.size() - 1); i++) {
            for (int j = 0; j < (selectat.size() - i - 1); j++) {
                if (selectat.get(j).getScore() < selectat.get(j + 1).getScore()) {
                    temp = selectat.get(j);
                    selectat.set(j, selectat.get(j + 1));
                    selectat.set(j + 1, temp);
                }
            }
        }
        for (int i = 0; i < job.noPositions; i++) {
            //verific daca user-ul s-a angajat,cautandu-l in toate companiile si departamentele
            for (Company c : Application.getInstance().getCompanys()) {
                for (Department d : c.departments)
                    for (Employee e : d.employers)
                        if (!e.resume.info.getNume().equals(selectat.get(0).getValue1())) {
                            aprobat = true;
                        }
            }
            //convertesc user-ul in emplyer
            Employee employee = ((User) selectat.get(0).getValue1()).convert();
            employee.salariu = job.salariu;
            employee.company = this.company;

            //caut departamentul si bag angajatul acolo
            for (Department d : Application.getInstance().getCompany(this.company).departments) {
                if (d.getJobs().contains(job))
                    d.add(employee);
            }
            selectat.remove(selectat.get(0));
        }
        job.aviable = false;
    }
}
