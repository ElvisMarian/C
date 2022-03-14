

public class Constraint {

    int min_constraint;
    int max_constraint;

    public Constraint(int min_constraint, int max_constraint) {
        this.min_constraint = min_constraint;
        this.max_constraint = max_constraint;
    }

    public int getMin_constraint() {
        return min_constraint;
    }

    public void setMin_constraint(int min_constraint) {
        this.min_constraint = min_constraint;
    }

    public int getMax_constraint() {
        return max_constraint;
    }

    public void setMax_constraint(int max_constraint) {
        this.max_constraint = max_constraint;
    }

    @Override
    public String toString() {
        return "Constraint{" +
                "min_constraint=" + min_constraint +
                ", max_constraint=" + max_constraint +
                '}';
    }
}