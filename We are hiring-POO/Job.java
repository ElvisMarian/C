
import java.util.ArrayList;

public class Job {
    String name_job;
    String name_company;
    boolean aviable;
    Constraint anul_absolvirii;
    Constraint ani_experienta;
    Constraint medie_academica;
    ArrayList<User> lista_candidati; //lista de candidati
    int noPositions;
    double salariu;


    public void apply(User user) {

        if (this.aviable == false)
            return;
        Recruiter potrivit = new Recruiter(null, 0);
        //parcurg lista de companii
        for (Company c : Application.getInstance().getCompanys()) {
            //daca gasesc compania caut recruiter-ul potrivit
            if (c.nume.equals(this.name_company))
                potrivit = c.getRecruiter(user);
        }
        potrivit.evaluate(this, user);
    }

    public boolean meetsRequirments(User user) {
        return this.anul_absolvirii.min_constraint <= user.getGraduationYear()
                && this.anul_absolvirii.max_constraint >= user.getGraduationYear()
                && this.ani_experienta.min_constraint <= user.nr_ani_experienta()
                && this.ani_experienta.max_constraint >= user.nr_ani_experienta()
                && this.medie_academica.min_constraint <= user.meanGPA()
                && this.medie_academica.max_constraint >= user.meanGPA();
    }


}
