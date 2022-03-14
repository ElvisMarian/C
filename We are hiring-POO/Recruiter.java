
public class Recruiter extends Employee {
    double rating = 5;

    Recruiter(String company, double salariu) {
        super(company, salariu);
        //fac angajarea in departamentul IT al companiei
        for (Company c : Application.getInstance().getCompanys()) {
            if (c.nume.equals(this.company)) {
                for (Department d : c.departments) {
                    if (d.getClass().getSimpleName().equals(IT.class.getSimpleName()))
                        c.add(this, d);
                }
            }
        }
    }

    public int evaluate(Job job, User user) {
        double score = (this.rating * user.getTotalScore());
        this.rating += 0.1;
        Request<Job, Consumer> request = new Request<Job, Consumer>(job, user, this, score);
        Company company = Application.getInstance().getCompany(job.name_company);
        company.manager.cereri.add(request);
        return 0;
    }

}

class Request<K, V> {
    private final K key;
    private final V value1;
    private final V value2;
    private final Double score;

    public Request(K key, V value1, V value2, Double score) {
        this.key = key;
        this.value1 = value1;
        this.value2 = value2;
        this.score = score;
    }

    public K getKey() {
        return key;
    }

    public V getValue1() {
        return value1;
    }

    public V getValue2() {
        return value2;
    }

    public Double getScore() {
        return score;
    }

    public String toString() {
        return "Key: " + key + " ; Value1: " + value1 + " ; Value2: " + value2 + " ; Score: " + score;
    }
}

