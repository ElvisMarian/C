
import java.util.List;

class User extends Consumer {
    List<String> fav_company;

    public User(List<String> fav_company) {
        this.fav_company = fav_company;
    }

    public Employee convert() {
        Employee employer = new Employee();
        employer.resume = this.resume;
        employer.cunoscuti = this.cunoscuti;
        return employer;
    }

    public int nr_ani_experienta() {
        int ani = 0, luni = 0;

        //daca incepe in  luna 10 si termina in luna 3 atunci va da cu - si trebuie sa scad din ani
        for (Experience exp : this.resume.experience) {
            ani += exp.sfarsit.getYear() - exp.inceput.getYear();
            if (exp.sfarsit.getMonth() - exp.inceput.getMonth() < 0) {
                ani--;
                luni += exp.sfarsit.getMonth() + 12 - exp.inceput.getMonth();
            }
            if (luni >= 12) {
                luni -= 12;
                ani++;
            }
        }
        if (luni >= 3)
            ani++;
        return ani;
    }

    public Double getTotalScore() {
        return ((double) this.nr_ani_experienta() * 1.5) + this.meanGPA();
    }
}
