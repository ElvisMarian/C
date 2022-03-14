
import java.util.Date;
import com.sun.media.sound.InvalidDataException;

public class Experience implements Comparable<Experience> {
    Date inceput;
    Date sfarsit;
    String position;
    String company;

    public Experience(Date inceput, Date sfarsit, String position, String company) throws InvalidDataException {
        if (inceput != null & sfarsit != null) {
            if (inceput.after(sfarsit))
                throw new InvalidDataException();
        }
        this.inceput = inceput;
        this.sfarsit = sfarsit;
        this.position = position;
        this.company = company;
    }

    @Override
    public int compareTo(Experience obj) {
        if (this.sfarsit != null & obj.sfarsit != null)
            return this.company.compareTo(obj.company);
        else {
            if (this.sfarsit.before(obj.sfarsit) || this.sfarsit.equals(obj.sfarsit))
                return 1;
            else
                return -1;
        }
    }
}
