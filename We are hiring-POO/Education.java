

import com.sun.media.sound.InvalidDataException;

import java.util.Date;

class Education implements Comparable<Education> {

    Date start_date;
    Date end_date;
    String name;
    String level;
    Double grade;

    public Education(Date start_date, Date end_date, String name, String level, Double grade) throws InvalidDataException {
        if (start_date != null & end_date != null) {
            if (start_date.after(end_date))
                throw new InvalidDataException();
        }
        this.start_date = start_date;
        this.end_date = end_date;
        this.name = name;
        this.level = level;
        this.grade = grade;
    }

    @Override
    public int compareTo(Education obj) {
        if (this.end_date != null && obj.end_date != null) {
            if (this.start_date.before(obj.start_date) || this.start_date.equals(obj.start_date))
                return 1;
            else
                return -1;
        } else {
            //pt sortarea descrescatoare this e data pe care o introduc si parametrul e obicetul cu care compar
            //daca data mea e inainte de data altui obiect merg mai departe pana cand nu mai e asa.
            if (this.end_date.before(obj.end_date))
                return 1;
            else if (this.end_date.equals(obj.end_date)) {
                if (this.grade >= obj.grade)
                    return 1;
                else
                    return -1;
            }
        }
        return 0;
    }

    @Override
    public String toString() {
        return "Education{" +
                "start_date=" + start_date +
                ", end_date=" + end_date +
                ", name='" + name + '\'' +
                ", level='" + level + '\'' +
                ", grade=" + grade +
                '}';
    }
}
